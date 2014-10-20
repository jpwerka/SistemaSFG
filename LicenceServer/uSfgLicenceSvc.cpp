//---------------------------------------------------------------------------
#include "Registry.hpp"
#include "uSfgLicenceSvc.h"
#include "uSfgCriptoLic.h"
#include <time.h>
#include "strsafe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSfgLicenceSvc *SfgLicenceSvc;
//---------------------------------------------------------------------------
__fastcall TSfgLicenceSvc::TSfgLicenceSvc(TComponent* Owner)
   : TService(Owner)
{
   iNumLicence = 0;
   iPortSocket = 4596;
   bLogEnabled = true;
   iMaxSizeLog = 1024*1024; // 1 MB
   sCodCliente = "";
   hFileLog = NULL;
   AppSocketSemaphore = NULL;
   LockSocket = NULL;
   ClientsInfo = NULL;
}
//---------------------------------------------------------------------------
TServiceController __fastcall TSfgLicenceSvc::GetServiceController(void)
{
   return (TServiceController) ServiceController;
}
//---------------------------------------------------------------------------
void __stdcall ServiceController(unsigned CtrlCode)
{
   SfgLicenceSvc->Controller(CtrlCode);
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServiceAfterInstall(TService *Sender)
{
  TRegistry *Description = new TRegistry(KEY_READ|KEY_WRITE);
  try
  {
    Description->RootKey = HKEY_LOCAL_MACHINE;
    // False because we do not want to create it if it doesn't exist
    Description->OpenKey("SYSTEM\\CurrentControlSet\\Services\\" + Name ,false);
    Description->WriteString("Description","Serviço para controle de licenças do sistema SFG.");
    Description->CloseKey();
  }
  __finally
  {
    delete Description;
  }
}
//---------------------------------------------------------------------------
bool __fastcall TSfgLicenceSvc::ReadConfiguration(char *LogMsg)
{
   bool bRetorno = true;
	char bfPath[MAX_PATH];
   char *pPath;
   WIN32_FIND_DATA FindFileData;
   HANDLE hFind;
	ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

	if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
		pPath = strrchr(bfPath,'\\');
      pPath++;
	} else {
      pPath = bfPath;
   }
   StringCchCopy(pPath,strlen("SfgLicenceSvc.ini")+1,"SfgLicenceSvc.ini");
   hFind = FindFirstFile(bfPath, &FindFileData);
   if (hFind == INVALID_HANDLE_VALUE) {
      if (GetLastError() == ERROR_FILE_NOT_FOUND) {
         StringCbCopy(LogMsg,255,"Não foi possível encontrar o arquivo: SfgLicenceSvc.ini");
      } else {
         StringCbPrintf(LogMsg, 255,
               "Ocorreu o seguinte erro ao tentar encontrar o arquivo: SfgLicenceSvc.ini\n%s",
               SysErrorMessage(GetLastError()));;
      }
      return false;
   }
	TIniFile *Cfg = new TIniFile(bfPath);
try {
	try {
      if (Cfg->SectionExists("LogFile")) {
		   // Arquivo de LOG habilitado?
		   bLogEnabled = Cfg->ReadBool("LogFile","enabled",true);
		   // Tamanho máximo do arquivo de LOG
		   iMaxSizeLog = Cfg->ReadInteger("LogFile","maxsize",1024);
         iMaxSizeLog = (iMaxSizeLog * 1024);
      }
      if (Cfg->SectionExists("LicenceServer")) {
		   // Porta de conexão
		   iPortSocket = Cfg->ReadInteger("LicenceServer","port",4596);
         //Código do cliente para validar contra a licença
         sCodCliente = Cfg->ReadString("LicenceServer","cliente","");
      } else {
         StringCbCopy(LogMsg,255,"Não foi possível encontrar a sessão [LicenceServer] no arquivo: SfgLicenceSvc.ini");
		   bRetorno = false;
      }
	}
	catch(Exception &e) {
      StringCbPrintf(LogMsg, 255,
               "Ocorreu o seguinte erro ao tentar recuperar as informações de conexão:\n%s",
               e.Message.c_str());
		bRetorno = false;
      iPortSocket = 4596;
      bLogEnabled = true;
      iMaxSizeLog = 1024*1024; // 1 MB
      sCodCliente = "";
	}
} // end try
__finally {
   delete Cfg;
}
	return bRetorno;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServiceStart(TService *Sender, bool &Started)
{
   char ErrorMsg[255];
   bool bReadCfg = false;

   Started = false;
   //Deve efetuar a leitua das configurações de servidor de licenças
   bReadCfg = ReadConfiguration(ErrorMsg);
   //Se não conseguir abrir um arquivo para logar as informações retorna
   if (bLogEnabled) {
      if (!OpenFileLog(OPEN_ALWAYS))
         return;
   }
   if (!bReadCfg) {
      if (bLogEnabled) {
         WriteFileLog(ErrorMsg);
         CloseHandle(hFileLog);
      }
      return;
   }
   if (sCodCliente.Length() != SFG_SIZE_CODCLI) {
      if (bLogEnabled) {
         WriteFileLog("Não foi passado o código do cliente ou o mesmo não está no formato correto.");
         CloseHandle(hFileLog);
      }
      return;
   }
   //Deve verificar se o arquivo de licenças está OK
   if (!SfgLoadLicenceFile(ErrorMsg)) {
      if (bLogEnabled) {
         WriteFileLog(ErrorMsg);
         CloseHandle(hFileLog);
      }
      return;
   }
   if (sCodCliente != CodCliente) {
      if (bLogEnabled) {
         WriteFileLog("O arquivo de licenças encontrado não é valido para o código de cliente informado.");
         CloseHandle(hFileLog);
      }
      return;
   }
   int iYear, iMonth, iDay;
   iYear = HIWORD(ValidadeLic);
   iMonth = HIBYTE(LOWORD(ValidadeLic));
   iDay = LOBYTE(LOWORD(ValidadeLic));
   Validade = EncodeDate(iYear,iMonth,iDay);
   if (Validade < Date()) {
      if (bLogEnabled) {
         String sMsg = "O arquivo de licenças encontrado está com a validade expirada. Validade: " + FormatDateTime("dd/mm/yyyy",Validade);
         WriteFileLog(sMsg.c_str());
         CloseHandle(hFileLog);
      }
      return;
   }
   //Inicia o serviço, "zerando" todas as informações
   iNumLicence = NumberLic;
   ClientsInfo = new TList();
   SocketTimer->Interval = SFG_SIGNED_TIME;
   Started = true;
   //Criando o semáforo que será responsável por controlar a comunicação do Socket
   AppSocketSemaphore = CreateSemaphore(NULL,1,1,NULL);
   LockSocket = new TCriticalSection();
   if (bLogEnabled)
      WriteFileLog("Serviço de licenças iniciado com sucesso.");
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServiceStop(TService *Sender, bool &Stopped)
{
   SfgClientInfo *pClientInfo;
   //Deve desconectar os clientes que estão conectados no servidor de licenças
   //Porém, antes deve perguntar se deseja desconectar os clientes
   //Então deve disparar uma mensagem para todos os clientes que o servidor
   //de licenças está sendo parado.
   //Aqui deve verificar se o cliente já está logado
   Stopped = false;
   for (int i=0; i < ClientsInfo->Count; i++) {
      pClientInfo = (SfgClientInfo*)ClientsInfo->Items[i];
      RemoveClientInfo(&pClientInfo);
      i--;
   }
   delete ClientsInfo;
   HeapFree(GetProcessHeap(),0,CodCliente);
   HeapFree(GetProcessHeap(),0,DenCliente);
   HeapFree(GetProcessHeap(),0,SerialLic);
   Stopped = true;
   WriteFileLog("Serviço de licenças parado com sucesso.");
   CloseHandle(hFileLog);
   CloseHandle(AppSocketSemaphore);
   delete LockSocket;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServiceExecute(TService *Sender)
{
   //Deve iniciar o SeverSocket dentro do serviço que será responsável por
   //Receber as mensagens do sistema cliente que está executando o sistema SFG
   try {
      iNumLicence = NumberLic;
      ServerSocket->Port = iPortSocket; // WWW port
      ServerSocket->Active = true;
      SocketTimer->Enabled = true;
      while (!Terminated)
         ServiceThread->ProcessRequests(true);
      SocketTimer->Enabled = false;
      ServerSocket->Active = false;
   }
   __finally {/*Não faz nada*/}
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServerSocketListen(TObject *Sender,
      TCustomWinSocket *Socket)
{
   char SocketMsg[255];
   struct hostent *hostPtr = gethostbyname(Socket->LocalHost.c_str());
   struct in_addr *addr_ptr = (struct in_addr *)*hostPtr->h_addr_list;

   if (bLogEnabled) {
      StringCbPrintf(SocketMsg,255,
                     "Servidor de licenças escutando em: %s (%s) na porta: %d.",
                     inet_ntoa(*addr_ptr),
                     hostPtr->h_name,
                     Socket->LocalPort);
      WriteFileLog(SocketMsg);
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::ServerSocketClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{
   char *Buffer = NULL;
   char *pInfo, *pInfoAux;
   int iLength, iProcessID, iMessageID;
   long lPreviousCount;
   SfgClientInfo *pClientInfo = NULL;
   //Pegando o que foi recebido do cliente
   iLength = Socket->ReceiveLength();
   iProcessID = 0;
   iMessageID = 0;
   //Deve receber a mensagem do client no seguinte formato:
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //Conteúdo da mensagem pode variar de acordo com a mensagem recebida
   //Será descrito em detalhes na função que irá interpretar as mesmas
   if (iLength > 0) {
      try {
         Buffer = (char *)malloc(iLength*sizeof(char));
         Socket->ReceiveBuf((void *)Buffer, iLength);
      }
      __finally {
         //free(Buffer);
      }
   } else {
      return;
   }
   pInfo = (char *)malloc(11*sizeof(char));

   iLength = 10;
   pInfoAux = Buffer;
   StringCchCopy(pInfo,iLength+1,pInfoAux);
   sscanf( pInfo, "%i", &iProcessID );
   if (iProcessID == 0) {
      char cMsgErr[86];
      StringCbPrintf(cMsgErr,86,"0x%08X0x%08X%03d%s",iProcessID,SFG_RET_LIC_NO,62,"Não foi passado o PID do processo para o servidor de licenças.");
      Socket->SendBuf(cMsgErr,86);
      free(pInfo);
      free(Buffer);
      return;
   }

   pInfoAux += iLength;
   StringCchCopy(pInfo,iLength+1,pInfoAux);
   sscanf( pInfo, "%i", &iMessageID );
   if (iMessageID == 0) {
      char cMsgErr[85];
      StringCbPrintf(cMsgErr,85,"0x%08X0x%08X%03d%s",iProcessID,SFG_RET_LIC_NO,61,"Não foi passado o ID da mensagem para o servidor de licenças.");
      Socket->SendBuf(cMsgErr,85);
      free(pInfo);
      free(Buffer);
      return;
   }

   pInfoAux += iLength;
   free(pInfo);

   //Espera pela liberação do semaforo por 0.5 segundos
   WaitForSingleObject(AppSocketSemaphore,500);
   LockSocket->Enter();

   //Aqui deve verificar se o cliente já está logado
   for (int i=0; i < ClientsInfo->Count; i++) {
      pClientInfo = (SfgClientInfo*)ClientsInfo->Items[i];
      if ((pClientInfo->RemoteAddress == Socket->RemoteAddress) &&
          (pClientInfo->ProcessID == iProcessID)) {
         break;
      }
      pClientInfo = NULL;
   }
   //Processa a mensagem de acordo com ID recebido
   ProcessMessage(iProcessID, iMessageID, &pClientInfo, Socket, &pInfoAux);
   free(Buffer);
   LockSocket->Release();
   //Libera o semaforo deste processo
   ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::SocketTimerTimer(TObject *Sender)
{
   SfgClientInfo *pClientInfo = NULL;
   long lPreviousCount = 0;
   double NowSigned = Now();
   //Espera pela liberação do semaforo por 0.5 segundos
   WaitForSingleObject(AppSocketSemaphore,500);
   LockSocket->Enter();
   //Deve verificar a ultima atualização para os clients verificando se ainda estão conectados
   for (int i=0; i < ClientsInfo->Count; i++) {
      pClientInfo = (SfgClientInfo*)ClientsInfo->Items[i];
      //Se passou mais tempo que o máximo previsto sem o cliente interagir
      //Provavelmente que o processo caiu ou foi derrubado, deve "matar" o client
      if (double((NowSigned - pClientInfo->LastSigned)*(1000*60*60*24)) > (double)SFG_SIGNED_TIME) {
         //Grava no arquivo de LOG as informações da conexão
         if (bLogEnabled) {
            String sMsgLog = "Removendo Client Inativo: " + \
                             pClientInfo->RemoteAddress + " (" + \
                             pClientInfo->RemoteHost + ")" + \
                             " Processo: " + IntToStr(pClientInfo->ProcessID) + \
                             " OS User: " + pClientInfo->OsUser + \
                             " SFG User: " + pClientInfo->SfgUser;
            WriteFileLog(sMsgLog.c_str());
         }
         RemoveClientInfo(&pClientInfo);
         iNumClients--;
         i--;
      }
   }
   LockSocket->Release();
   //Libera o semaforo deste processo
   ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
}
//---------------------------------------------------------------------------
bool __fastcall TSfgLicenceSvc::OpenFileLog(DWORD dwFlagCreate)
{
	char bfPath[MAX_PATH];
   char *pPath;
	ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

	if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
		pPath = strrchr(bfPath,'\\');
      pPath++;
	} else {
      pPath = bfPath;
   }
   StringCchCopy(pPath,strlen("SfgLicenceSvc.log")+1,"SfgLicenceSvc.log");
   //Abre o arquivo de licença para validar o sistema
   hFileLog = CreateFile(bfPath,    // create "SfgLicenceSvc.log"
             GENERIC_WRITE,                 // open for write
             FILE_SHARE_READ|FILE_SHARE_WRITE,             // shared file other proccess
             NULL,                         // no security
             dwFlagCreate,                  // open always, if not exists create it
             FILE_ATTRIBUTE_NORMAL,        // normal file
             NULL);                        // no attr. template

   if (hFileLog == INVALID_HANDLE_VALUE) {
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::WriteFileLog(char *LogMsg)
{
   __int64 iFileSize = 0;
   int iSize;
   time_t sttime;
   struct tm * timeinfo;
   char *DateLogMsg;
   DWORD dwBytesWritten, dwPos;

   if (GetFileSizeEx(hFileLog,(LARGE_INTEGER*)&iFileSize)) {
      //Se chegou no limite deve limpar o arquivo de LOG
      if (iMaxSizeLog <= iFileSize) {
         if (!OpenFileLog(CREATE_ALWAYS))
            return;
      }
   }
   //Pega a hora corrente
   time(&sttime);
   //convert to local time
   timeinfo = localtime ( &sttime );
   iSize = strlen(LogMsg) + 1;
   iSize +=24; //Alocando mais o espaço para a data [dd/mm/yyyy hh:mm:ss] e o fim de linha
   DateLogMsg = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSize*sizeof(char)); //new char[iSizeT];
   StringCbPrintf(DateLogMsg,iSize,
                  "[%02d/%02d/%04d %02d:%02d:%02d] %s\r\n",
                  timeinfo->tm_mday,
                  timeinfo->tm_mon + 1,
                  timeinfo->tm_year + 1900,
                  timeinfo->tm_hour,
                  timeinfo->tm_min,
                  timeinfo->tm_sec,
                  LogMsg);

   dwPos = SetFilePointer(hFileLog, 0, NULL, FILE_END);
   iSize = strlen(DateLogMsg);
   LockFile(hFileLog, dwPos, 0, dwPos + iSize*sizeof(char), 0);
   WriteFile(hFileLog, DateLogMsg, iSize*sizeof(char), &dwBytesWritten, NULL);
   UnlockFile(hFileLog, dwPos, 0, dwPos + iSize*sizeof(char), 0);
   HeapFree(GetProcessHeap(),0,DateLogMsg);
}
//---------------------------------------------------------------------------
bool __fastcall TSfgLicenceSvc::ProcessMessage(int ProcessID, int MessageID,
      SfgClientInfo **ClientInfo, TCustomWinSocket *Socket, char **MsgBuffer,
      const bool bPostMsg)
{
   String sMsgLog;
   char cMsgOK[21];

   switch ( MessageID ) {
      case SFG_ADD_CLIENT:
      //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o usuário do sistema operacional
      //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o usuário do sistema SFG
      {
         bool bAddClient = false;
         if (*ClientInfo == NULL) { //Isto indica que não achou o client
            if (iNumClients >= iNumLicence) {
               char cMsgErr[53];
               StringCbPrintf(cMsgErr,53,"0x%08X0x%08X%03d%s",ProcessID,SFG_RET_LIC_NO,29,"Número de licenças excedidos.");
               Socket->SendBuf(cMsgErr,53);
               return false;
            }
            //Ainda possui licenças de uso, adiciona um novo client
            iNumClients++;
            //Adiciona o client na listagem
            AddClientInfo(ClientInfo,MsgBuffer);
            bAddClient = true;
         }
         //Preenche as informações da conexão
         (*ClientInfo)->SocketHandle = Socket->SocketHandle;
         (*ClientInfo)->RemoteAddress = Socket->RemoteAddress;
         (*ClientInfo)->RemoteHost = Socket->RemoteHost;
         (*ClientInfo)->ProcessID = ProcessID;
         (*ClientInfo)->LastSigned = Now();
         //Posta a mensagem de retorno
         if (bPostMsg) {
            char cMsgRet[255];
            ZeroMemory(cMsgRet,255*sizeof(char));
            //Mensagem de retorno deve enviar o código do identificador, número de licenças, validade, cliente e denominação
            StringCbPrintf(cMsgRet,255,"0x%08X0x%08X%s0x%08X0x%08X%s%03d%s",ProcessID,SFG_RET_LIC_OK,SerialLic,NumberLic,ValidadeLic,CodCliente,strlen(DenCliente),DenCliente);
            Socket->SendBuf(cMsgRet,strlen(cMsgRet));
         }
         if (bAddClient && bLogEnabled) {
            //Grava no arquivo de LOG as informações da conexão
            sMsgLog = "Adicionando Novo Client: " + \
                     (*ClientInfo)->RemoteAddress + " (" + \
                     (*ClientInfo)->RemoteHost + ")" + \
                     " Processo: " + IntToStr(ProcessID) + \
                     " OS User: " + (*ClientInfo)->OsUser + \
                     " SFG User: " + (*ClientInfo)->SfgUser;
            WriteFileLog(sMsgLog.c_str());
         }

      }
      break;

      case SFG_ADD_PROGRAM:
      //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o código do programa do sistema SFG
      //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o título do programa do sistema SFG
      {
         if (*ClientInfo == NULL) { //Isto indica que não achou o client
            char cMsgErr[103];
            StringCbPrintf(cMsgErr,103,"0x%08X0x%08X%03d%s",ProcessID,SFG_RET_LIC_NO,79,"Não foi passado o cliente para solicitar liçença antes da abertura do programa.");
            Socket->SendBuf(cMsgErr,103);
            return false;
         }
         SfgClientProgram *pClientProgram = NULL;
         //Adiciona o programa na listagem
         AddClientProgram(ClientInfo,MsgBuffer,&pClientProgram);
         (*ClientInfo)->LastSigned = Now();
         if (bPostMsg) {
            StringCbPrintf(cMsgOK,21,"0x%08X0x%08X",ProcessID,SFG_RET_LIC_OK);
            Socket->SendBuf(cMsgOK,21);
         }
         //Grava no arquivo de LOG as informações da conexão
         if (bLogEnabled) {
            sMsgLog = "Adicionando Programa: " + \
                       (*ClientInfo)->RemoteAddress + " (" + \
                       (*ClientInfo)->RemoteHost + ")" + \
                       " Processo: " + IntToStr(ProcessID) + \
                       " Programa: " + pClientProgram->ProgramName + \
                       " - " + pClientProgram->ProgramTitle;
            WriteFileLog(sMsgLog.c_str());
         }
      }
      break;

      case SFG_DEL_CLIENT:
      //Não possui mensagem específica
      {
         if (*ClientInfo == NULL) { //Isto indica que não achou o client, então não há o que deletar
            StringCbPrintf(cMsgOK,21,"0x%08X0x%08X",ProcessID,SFG_RET_LIC_OK);
            Socket->SendBuf(cMsgOK,21);
            //Grava no arquivo de LOG as informações da conexão
            if (bLogEnabled) {
               sMsgLog = "Excluindo Client: " + \
                          Socket->RemoteAddress + " (" + \
                          Socket->RemoteHost + ")" + \
                          " Processo: " + IntToStr(ProcessID) + \
                          " Cliente desconhecido";
            }
         } else { //Caso contrário deve excluir o client
            if (bLogEnabled) {
               sMsgLog = "Excluindo Client: " + \
                          (*ClientInfo)->RemoteAddress + " (" + \
                          (*ClientInfo)->RemoteHost + ")" + \
                          " Processo: " + IntToStr(ProcessID) + \
                          " OS User: " + (*ClientInfo)->OsUser + \
                          " SFG User: " + (*ClientInfo)->SfgUser;
            }
            RemoveClientInfo(ClientInfo);
            iNumClients--;
         }
         if (bPostMsg) {
            StringCbPrintf(cMsgOK,21,"0x%08X0x%08X",ProcessID,SFG_RET_LIC_OK);
            Socket->SendBuf(cMsgOK,21);
         }
         if (bLogEnabled) {
            WriteFileLog(sMsgLog.c_str());
         }
      }
      break;

      case SFG_DEL_PROGRAM:
      //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o código do programa do sistema SFG
      {
         if (*ClientInfo == NULL) { //Isto indica que não achou o client, então não há o que deletar
            return ProcessMessage(ProcessID,SFG_DEL_CLIENT,ClientInfo,Socket,MsgBuffer);
         }
         //Caso contrário deve retirar o programa da lista de clientes
         RemoveClientProgram(ClientInfo,MsgBuffer);
         (*ClientInfo)->LastSigned = Now();
         //Grava no arquivo de LOG as informações da conexão
         if (bLogEnabled) {
            sMsgLog = "Removendo Programa: " + \
                       (*ClientInfo)->RemoteAddress + " (" + \
                       (*ClientInfo)->RemoteHost + ")" + \
                       " Processo: " + IntToStr(ProcessID) + \
                       " Programa: " + *MsgBuffer;
            WriteFileLog(sMsgLog.c_str());
         }
         if (bPostMsg) {
            StringCbPrintf(cMsgOK,21,"0x%08X0x%08X",ProcessID,SFG_RET_LIC_OK);
            Socket->SendBuf(cMsgOK,21);
         }
      }
      break;

      case SFG_SIGN_CLIENT:
      {
         if (*ClientInfo == NULL) { //Isto indica que não achou o client
            char cMsgErr[76];
            StringCbPrintf(cMsgErr,76,"0x%08X0x%08X%03d%s",ProcessID,SFG_RET_LIC_NO,52,"Não foi possível encontrar o cliente para sinalizar.");
            Socket->SendBuf(cMsgErr,76);
            return false;
         }
         (*ClientInfo)->LastSigned = Now();
         if (bPostMsg) {
            StringCbPrintf(cMsgOK,21,"0x%08X0x%08X",ProcessID,SFG_RET_LIC_OK);
            Socket->SendBuf(cMsgOK,21);
         }
      }
      break;

      case SFG_GET_NUM_CLT:
      //Não possui mensagem específica
      break;
      case SFG_GET_CLIENT:
      //NxNNNNNNNN -> Identificador do index do client no formato Hexadecimal
      break;
      case SFG_GET_NUM_PRG:
      //NxNNNNNNNN -> Identificador da posição de memória do client no formato Hexadecimal
      break;
      case SFG_GET_PROGRAM:
      //NxNNNNNNNN -> Identificador da posição de memória do client no formato Hexadecimal
      //NxNNNNNNNN -> Identificador da posição de memória do program no formato Hexadecimal
      break;
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::AddClientInfo(SfgClientInfo **ClientInfo, char **MsgBuffer)
{
   char cNum[4];
   char *pInfo;
   int iSize = 0;
   //Cria a nova estrtura do ClientInfo
   *ClientInfo = new SfgClientInfo();
   (*ClientInfo)->LastSigned = Now();
   (*ClientInfo)->Programs = new TList();
   ClientsInfo->Add((*ClientInfo));

   //Usuário do sistema operacional
   *MsgBuffer += iSize;
   StringCchCopy(cNum,4,*MsgBuffer);
   iSize = atoi(cNum);
   pInfo = (char*)malloc((iSize+1)*sizeof(char));
   *MsgBuffer += 3;
   StringCchCopy(pInfo,iSize+1,*MsgBuffer);
   (*ClientInfo)->OsUser = pInfo;
   free(pInfo);
   //Usuário do sistema SFG
   *MsgBuffer += iSize;
   StringCchCopy(cNum,4,*MsgBuffer);
   iSize = atoi(cNum);
   pInfo = (char*)malloc((iSize+1)*sizeof(char));
   *MsgBuffer += 3;
   StringCchCopy(pInfo,iSize+1,*MsgBuffer);
   (*ClientInfo)->SfgUser = pInfo;
   free(pInfo);
   *MsgBuffer += iSize;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::AddClientProgram(SfgClientInfo **ClientInfo, char **MsgBuffer, SfgClientProgram **ClientProgram)
{
   char cNum[4];
   char *pInfo;
   int iSize = 0;
   SfgClientProgram *pClientProgram = NULL;

   //Criando uma nova estrutura de programa do sistema SFG
   pClientProgram = new SfgClientProgram();
   pClientProgram->ClientInfo = *ClientInfo;
   (*ClientInfo)->Programs->Add(pClientProgram);
   *ClientProgram = pClientProgram;

   //Código do programa do sistema SFG
   StringCchCopy(cNum,4,*MsgBuffer);
   iSize = atoi(cNum);
   pInfo = (char*)malloc((iSize+1)*sizeof(char));
   *MsgBuffer += 3;
   StringCchCopy(pInfo,iSize+1,*MsgBuffer);
   pClientProgram->ProgramName = pInfo;
   free(pInfo);
   //Título do programa do sistema SFG
   *MsgBuffer += iSize;
   StringCchCopy(cNum,4,*MsgBuffer);
   iSize = atoi(cNum);
   pInfo = (char*)malloc((iSize+1)*sizeof(char));
   *MsgBuffer += 3;
   StringCchCopy(pInfo,iSize+1,*MsgBuffer);
   pClientProgram->ProgramTitle = pInfo;
   free(pInfo);
   *MsgBuffer += iSize;
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::RemoveClientInfo(SfgClientInfo **ClientInfo)
{
   TList *Programs;
   SfgClientProgram *pClientProgram = NULL;

   if (*ClientInfo == NULL) //Isto indica que não achou o client, então não há o que deletar
      return;
       
   //Deve deletar a lista de programas do usuário
   Programs = (*ClientInfo)->Programs;
   for (int i=0; i < Programs->Count; i++) {
       pClientProgram = (SfgClientProgram*)Programs->Items[i];
       delete pClientProgram;
   }
   Programs->Clear();
   delete Programs;

   int iIndex = ClientsInfo->IndexOf((*ClientInfo));
   if (iIndex >= 0)
      ClientsInfo->Delete(iIndex);

/*   String  sMsgLog = "Deletando Client: " + \
                       (*ClientInfo)->RemoteAddress + " (" + \
                       (*ClientInfo)->RemoteHost + ")" + \
                       " Processo: " + IntToStr((*ClientInfo)->ProcessID);
            this->ServerSocket->Socket->Lock();
            WriteFileLog(sMsgLog.c_str());
            this->ServerSocket->Socket->Unlock(); */
   delete (*ClientInfo);
}
//---------------------------------------------------------------------------
void __fastcall TSfgLicenceSvc::RemoveClientProgram(SfgClientInfo **ClientInfo, char **MsgBuffer)
{
   char cNum[4];
   char *pInfo;
   int iSize = 0;
   int iIndex = 0;
   TList *Programs;
   SfgClientProgram *pClientProgram = NULL;

   //Código do programa do sistema SFG
   StringCchCopy(cNum,4,*MsgBuffer);
   iSize = atoi(cNum);
   pInfo = (char*)malloc((iSize+1)*sizeof(char));
   *MsgBuffer += 3;
   StringCchCopy(pInfo,iSize+1,*MsgBuffer);
   free(pInfo);
   //Aqui apenas zera o fim do buffer, para poder recuperar o programa
   pInfo = *MsgBuffer;
   pInfo[iSize] = '\0';
   //Deve percorrer a lista de programas do cliente e excluir o recebido
   Programs = (*ClientInfo)->Programs;
   for (iIndex=0; iIndex < Programs->Count; iIndex++) {
      pClientProgram = (SfgClientProgram*)Programs->Items[iIndex];
      if (pClientProgram->ProgramName == pInfo) {
         break;
      }
      pClientProgram = NULL;
   }
   if (pClientProgram != NULL) {
      delete pClientProgram;
      Programs->Delete(iIndex);
   }
}
//---------------------------------------------------------------------------



