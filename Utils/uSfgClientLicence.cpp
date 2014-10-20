//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#include "uSfgSignLicence.h"
#include "uSfgCriptoLic.h"
#include <time.h>
#pragma hdrstop
#include "uSfgClientLicence.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
TSfgClientLicence *AppClientLicence = NULL;
//---------------------------------------------------------------------------
//bool __fastcall OpenFileLog(DWORD dwFlagCreate);
//void __fastcall WriteFileLog(char *LogMsg);
//HANDLE hFileLog;
//---------------------------------------------------------------------------
const char* SfgAddClientMsg  = {"0x%08X0x%08X%03d%s%03d%s"};
const char* SfgAddProgramMsg = {"0x%08X0x%08X%03d%s%03d%s"};
const char* SfgDelProgramMsg = {"0x%08X0x%08X%03d%s"};
const char* SfgDelClientMsg  = {"0x%08X0x%08X"};
const char* SfgMainProgram   = {"Menu"};
const char* SfgMainTitle     = {"Sistema SFG"};
//---------------------------------------------------------------------------
__fastcall TSfgClientLicence::TSfgClientLicence()
   : TObject()
{
   AppSignLicence = NULL;
   AppEndSignEvent = NULL;
   AppSocketSemaphore = NULL;
   //Buscando o usu�rio do sistema operacional
   FOSUserNameLenght = 255;
   ZeroMemory(FOSUserName,255*sizeof(char));
   if (!GetUserName(FOSUserName, &FOSUserNameLenght)) {
      strcpy(FOSUserName,"Indefinido");
      FOSUserNameLenght = 11;
   }
   FOSUserNameLenght--;
   //Montando a string que dever� ser retornada sempre que o server retornar SFG_RET_LIC_OK
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(FRetMsgOK,21*sizeof(char));
   wsprintf(FRetMsgOK,"0x%08X0x%08X",GetCurrentProcessId(),SFG_RET_LIC_OK);
}
//---------------------------------------------------------------------------
__fastcall TSfgClientLicence::~TSfgClientLicence()
{
   //Avisa a threads que a aplica��o foi finalizada
   if (AppEndSignEvent != NULL) {
      SetEvent(AppEndSignEvent);
      CloseHandle(AppEndSignEvent);
   }
   //Finaliza o sem�foro que cuida da leitura do Socket
   if (AppSocketSemaphore != NULL) {
      CloseHandle(AppSocketSemaphore);
   }
   //Se a thread existir e estiver rodando deve derrubar a mesma
   if (AppSignLicence != NULL) {
      delete AppSignLicence;
   }
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceAddClient()
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o usu�rio do sistema operacional
   //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o usu�rio do sistema SFG

   String sMsgError;
   //Deve calcular o tamanho da mensagem que deve enviar
   int iSfgUser = AppUser->Usuario.Length();

   //Se nunca enviou uma mensagem deve pr�-alocar a mem�ria
   if (AppLicenceSvr->MsgBuffer == NULL) {
      AppLicenceSvr->MsgBuffer = (char*)HeapAlloc(GetProcessHeap(),0,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   }

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   //Formatando a mensagem para o servidor de licen�as
   wsprintf(AppLicenceSvr->MsgBuffer,
            SfgAddClientMsg,
            GetCurrentProcessId(),
            SFG_ADD_CLIENT,
            FOSUserNameLenght,
            FOSUserName,
            iSfgUser,
            AppUser->Usuario.c_str());

   //Se n�o puder adicionar um cliente tamb�m retorna
   if (!LicenceSendRecvMsg(SFG_ADD_CLIENT,sMsgError)) {
      SfgDataCenter->CloseClientSocket();
      MessageBox(NULL,sMsgError.c_str(),"Servidor de Licen�as",APP_ERROR);
      return false;
   }
   //Deve recuperar as informa��es sobre a licen�a
   //Mensagem de retorno deve enviar o c�digo do identificador, n�mero de licen�as, validade, cliente e denomina��o
   char Info[100];
   int iNumber;
   //Identificador
   for (int i=0;i<16;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+20];
   Info[16] = '\0';
   AppLicence->IdLicence = Info;
   //N�mero de licen�as
   for (int i=0;i<10;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+36];
   Info[10] = '\0';
   sscanf( Info, "%i", &iNumber );
   AppLicence->NumLicence = iNumber;
   //Validade
   for (int i=0;i<10;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+46];
   Info[10] = '\0';
   sscanf( Info, "%i", &iNumber );
   int iYear, iMonth, iDay;
   iYear = HIWORD(iNumber);
   iMonth = HIBYTE(LOWORD(iNumber));
   iDay = LOBYTE(LOWORD(iNumber));
try {
   AppLicence->Validade = EncodeDate(iYear,iMonth,iDay);
} catch(...) {
   AppLicence->Validade = 0;
}
   //C�digo do cliente
   for (int i=0;i<15;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+56];
   Info[15] = '\0';
   AppLicence->CodCliente = Info;
   //Denomina��o do cliente
   for (int i=0;i<3;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+71];
   Info[3] = '\0';
   iNumber = atoi(Info);
   for (int i=0;i<iNumber;i++)
      Info[i] = AppLicenceSvr->MsgBuffer[i+74];
   Info[iNumber] = '\0';
   AppLicence->DenCliente = Info;

   //Criando o evento que ser� respons�vel por sinalizar o fim da aplica��o para as threads
   AppEndSignEvent = CreateEvent(NULL,true,false,NULL);
   //Criando o sem�foro que ser� respons�vel por controlar a comunica��o do Socket
   AppSocketSemaphore = CreateSemaphore(NULL,1,1,NULL);
   //Criando Thread que ser� respons�vel por sinalizar ao servidor de licen�as
   AppSignLicence = new TSfgSignLicence(false);

   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceDelClient()
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal

   String sMsgError;
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   //Formatando a mensagem para o servidor de licen�as
   wsprintf(AppLicenceSvr->MsgBuffer,
            SfgDelClientMsg,
            GetCurrentProcessId(),
            SFG_DEL_CLIENT);

   if (!LicenceSendRecvMsg(SFG_DEL_CLIENT,sMsgError)) {
      sMsgError += "\nPode ocorrer que sua licen�a n�o seja liberada imediatamente.";
      MessageBox(NULL,sMsgError.c_str(),"Servidor de Licen�as",APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceAddProgram(char *cSfgProgram, char *cSfgTitle)
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o c�digo do programa do sistema SFG
   //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o t�tulo do programa do sistema SFG

   String sMsgError;
   //Deve calcular o tamanho da mensagem que deve enviar
   int iSfgProgram = strlen(cSfgProgram);
   int iSfgTitle = strlen(cSfgTitle);

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   //Formatando a mensagem para o servidor de licen�as
   wsprintf(AppLicenceSvr->MsgBuffer,
            SfgAddProgramMsg,
            GetCurrentProcessId(),
            SFG_ADD_PROGRAM,
            iSfgProgram,
            cSfgProgram,
            iSfgTitle,
            cSfgTitle);

   if (!LicenceSendRecvMsg(SFG_ADD_PROGRAM,sMsgError)) {
      MessageBox(NULL,sMsgError.c_str(),"Servidor de Licen�as",APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceDelProgram(char *cSfgProgram)
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //NNNC[N] -> Tamanho seguido da string de caracteres que indicam o c�digo do programa do sistema SFG

   String sMsgError;
   //Deve calcular o tamanho da mensagem que deve enviar
   int iSfgProgram = strlen(cSfgProgram);
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   //Formatando a mensagem para o servidor de licen�as
   wsprintf(AppLicenceSvr->MsgBuffer,
            SfgDelProgramMsg,
            GetCurrentProcessId(),
            SFG_DEL_PROGRAM,
            iSfgProgram,
            cSfgProgram);

   if (!LicenceSendRecvMsg(SFG_DEL_PROGRAM,sMsgError)) {
      MessageBox(NULL,sMsgError.c_str(),"Servidor de Licen�as",APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceSendRecvMsg(int iLastMsg, String &sMsgError)
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //Pega o usu�rio do sistema operacional
   bool bRetMsg = true;
   long lPreviousCount;
   char cRetBuffer[21];
try {
   //Espera pela libera��o do semaforo por 5 segundos
   WaitForSingleObject(AppSocketSemaphore,5000);
   //Envia a mensagem para o servidor de licen�as
   AppLicenceSvr->LastMsg = iLastMsg;
   SfgDataCenter->ClientSocketSend();
   SfgDataCenter->ClientSocketRead();
} catch (Exception &e) {
   sMsgError = "Ocorreu o seguinte erro ao tentar comunica��o com o servidor de licen�as:\n";
   sMsgError += e.Message;
   bRetMsg = false;
}
   if (!bRetMsg) {
      //Libera o semaforo deste processo
      ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
      return false;
   }

   if (AppLicenceSvr->MsgBuffer == NULL) {
      sMsgError = "N�o foi poss�vel receber a resposta do servidor de licen�as!";
      //Libera o semaforo deste processo
      ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
      return false;
   }
   //Se o tamanho da mensagem de retorno � menor do 20 - erro
   if (strlen(AppLicenceSvr->MsgBuffer) < SFG_MIN_MSG_RET) {
      sMsgError = "Resposta do servidor de licen�as no formato desconhecido!";
      //Libera o semaforo deste processo
      ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
      return false;
   }
   //Deve validar a mensagem de retorno
   for (int i=0; i < 20; i++)
      cRetBuffer[i] = AppLicenceSvr->MsgBuffer[i];
   cRetBuffer[20] = '\0';
   //Deve ter retonado o PID do processo + OK ambos formato HEX
   //Se o retorno foi negativo, deve mostrar a mensagem retornada
   if (strcmp(cRetBuffer,FRetMsgOK) != 0) {
      sMsgError = &AppLicenceSvr->MsgBuffer[23];
      //Libera o semaforo deste processo
      ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
      return false;
   }
   //Libera o semaforo deste processo
   ReleaseSemaphore(AppSocketSemaphore,1,&lPreviousCount);
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgClientLicence::LicenceValidFile()
{
   String sMsgError;
   char ErrorMsg[255];

   if (AppLicence->CodCliente.Length() != SFG_SIZE_CODCLI) {
      sMsgError = "N�o foi passado o c�digo do cliente ou o mesmo n�o est� no formato correto." \
                  "\nVerifique a sess�o [LicenceClient] do arquivo de conex�o.";
      MessageBox(NULL,sMsgError.c_str(),"Arquivo de Licen�as",APP_ERROR);
      return false;
   }
   //Deve verificar se o arquivo de licen�as est� OK
   if (!SfgLoadLicenceFile(ErrorMsg)) {
      sMsgError = "O sistema est� parametrizado para utilizar arquivo de licen�a local.\n" \
                  "Por�m ocorreu o seguinte problema ao carregar o arquivo de licen�as:\n";
      sMsgError += ErrorMsg;
      MessageBox(NULL,sMsgError.c_str(),"Arquivo de Licen�as",APP_ERROR);
      return false;
   }
   if (AppLicence->CodCliente != CodCliente) {
      sMsgError = "O arquivo de licen�as encontrado n�o � valido para o c�digo de cliente informado." \
                  "\nVerifique a sess�o [LicenceClient] do arquivo de conex�o.";
      MessageBox(NULL,sMsgError.c_str(),"Arquivo de Licen�as",APP_ERROR);
      return false;
   }
   AppLicence->DenCliente = DenCliente;
   AppLicence->IdLicence = SerialLic;
   AppLicence->NumLicence = NumberLic;
   int iYear, iMonth, iDay;
   iYear = HIWORD(ValidadeLic);
   iMonth = HIBYTE(LOWORD(ValidadeLic));
   iDay = LOBYTE(LOWORD(ValidadeLic));
try {
   AppLicence->Validade = EncodeDate(iYear,iMonth,iDay);
} catch(...) {
   AppLicence->Validade = 0;
}
   if ((int)AppLicence->Validade == 0) {
      MessageBox(NULL,"N�o foi poss�vel determinar a validade da licen�a de uso do sistema!","Arquivo de Licen�as",APP_ERROR);
      return false;
   }
   if (AppLicence->Validade < Date()) {
      sMsgError = "O arquivo de licen�as encontrado est� com a validade expirada. Validade: " + FormatDateTime("dd/mm/yyyy",AppLicence->Validade);
      MessageBox(NULL,sMsgError.c_str(),"Arquivo de Licen�as",APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
char* __fastcall TSfgClientLicence::GetFirstSerial(char *ErrorMsg)
{
   return GetFirstSerialLic(ErrorMsg);
}
////---------------------------------------------------------------------------
//bool __fastcall OpenFileLog(DWORD dwFlagCreate)
//{
//	char bfPath[MAX_PATH];
//   char *pPath;
//	ZeroMemory( bfPath, sizeof(char)*MAX_PATH);
//
//	if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
//		pPath = strrchr(bfPath,'\\');
//      pPath++;
//	} else {
//      pPath = bfPath;
//   }
//   wsprintf(pPath,"SfgLicenceSvc.log");
//   //Abre o arquivo de licen�a para validar o sistema
//   hFileLog = CreateFile(bfPath,    // create "SfgLicenceSvc.log"
//             GENERIC_WRITE,                 // open for write
//             FILE_SHARE_READ|FILE_SHARE_WRITE,             // shared file other proccess
//             NULL,                         // no security
//             dwFlagCreate,                  // open always, if not exists create it
//             FILE_ATTRIBUTE_NORMAL,        // normal file
//             NULL);                        // no attr. template
//
//   if (hFileLog == INVALID_HANDLE_VALUE) {
//      return false;
//   }
//   return true;
//}
////---------------------------------------------------------------------------
//void __fastcall WriteFileLog(char *LogMsg)
//{
//   //__int64 iFileSize = 0;
//   int iSize;
//   time_t sttime;
//   struct tm * timeinfo;
//   char *DateLogMsg;
//   DWORD dwBytesWritten, dwPos;
//
//   /*if (GetFileSizeEx(hFileLog,(LARGE_INTEGER*)&iFileSize)) {
//      //Se chegou no limite deve limpar o arquivo de LOG
//      if (iMaxSizeLog <= iFileSize) {
//         if (!OpenFileLog(CREATE_ALWAYS))
//            return;
//      }
//   }*/
//   //Pega a hora corrente
//   time(&sttime);
//   //convert to local time
//   timeinfo = localtime ( &sttime );
//   iSize = strlen(LogMsg) + 1;
//   iSize +=24; //Alocando mais o espa�o para a data [dd/mm/yyyy hh:mm:ss] e o fim de linha
//   DateLogMsg = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSize*sizeof(char)); //new char[iSizeT];
//   wsprintf(DateLogMsg,
//                  "[%02d/%02d/%04d %02d:%02d:%02d] %s\r\n",
//                  timeinfo->tm_mday,
//                  timeinfo->tm_mon + 1,
//                  timeinfo->tm_year + 1900,
//                  timeinfo->tm_hour,
//                  timeinfo->tm_min,
//                  timeinfo->tm_sec,
//                  LogMsg);
//
//   dwPos = SetFilePointer(hFileLog, 0, NULL, FILE_END);
//   iSize = strlen(DateLogMsg);
//   LockFile(hFileLog, dwPos, 0, dwPos + iSize*sizeof(char), 0);
//   WriteFile(hFileLog, DateLogMsg, iSize*sizeof(char), &dwBytesWritten, NULL);
//   UnlockFile(hFileLog, dwPos, 0, dwPos + iSize*sizeof(char), 0);
//   HeapFree(GetProcessHeap(),0,DateLogMsg);
//}
////---------------------------------------------------------------------------







