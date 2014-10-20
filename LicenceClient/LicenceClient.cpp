//---------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <winsock2.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma argsused
//---------------------------------------------------------------------------
struct SfgData {
    SOCKET AppClientSocket;
    HANDLE SfgThread;
    DWORD  SfgThreadId;
    char Host[15];
    int Port;
};

DWORD WINAPI SfgThreadFunction( LPVOID lpParam );
void SfgLicenceSvcCon(char *MsgError, SfgData *pSfgData);
bool LicenceSendRecvMsg(char *MsgBuffer, char *MsgError, SfgData *pSfgData);
bool OpenFileLog(DWORD dwFlagCreate);
void WriteFileLog(char *LogMsg);
//---------------------------------------------------------------------------

int WaitTable[] = {50,6000,2000,10,10000,650,4560,1250,200,7000};

char *ProgramsName[10];
char *ProgramsTitle[10];

#define MAX_THREADS 10
#define MAX_PROGRAM 10
#define MAX_MSG_BUFFER 500
#define SFG_NOT_MESSAGE  0x00000000
#define SFG_ADD_CLIENT   0x00000001
#define SFG_ADD_PROGRAM  0x00000002
#define SFG_DEL_CLIENT   0x00000003
#define SFG_DEL_PROGRAM  0x00000004
#define SFG_GET_NUM_CLT  0x00000005
#define SFG_GET_CLIENT   0x00000006
#define SFG_GET_NUM_PRG  0x00000007
#define SFG_GET_PROGRAM  0x00000008
#define SFG_SIGN_CLIENT  0x00000009
#define SFG_RET_LIC_OK   0x00000001
#define SFG_RET_LIC_NO   0xFFFFFFFF
#define SFG_MIN_MSG_RET  0x00000014

HANDLE SfgSocketSemaphore;

const char *ErrSktConnMsg = {"Não foi possível conectar com o servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktSendMsg = {"Não foi possível enviar a mensagem ao servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktRecvMsg = {"Não foi possível receber a mensagem do servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};

const char* SfgAddClientMsg  = {"0x%08X0x%08X%03d%s%03d%s"};
const char* SfgAddProgramMsg = {"0x%08X0x%08X%03d%s%03d%s"};
const char* SfgDelProgramMsg = {"0x%08X0x%08X%03d%s"};
const char* SfgDelClientMsg  = {"0x%08X0x%08X"};

const char* SfgAddClientLog  = {"Adicionando Novo Client: %s (%s) Processo: %d OS User: %s SFG User: %s"};
const char* SfgDelClientLog  = {"Excluindo Client: %s (%s) Processo: %d OS User: %s SFG User: %s"};
const char* SfgDelClientALog = {"Excluindo Client: %s (%s) Processo: %d Cliente desconhecido"};
const char* SfgAddProgramLog = {"Adicionando Programa: %s (%s) Processo: %d Programa: %s - %s"};
const char* SfgDelProgramLog = {"Removendo Programa: %s (%s) Processo: %d Programa: %s"};

HANDLE *hThreadArray;
HANDLE hFileLog = NULL;
char OSUserName[255];
DWORD OSUserNameLenght;
//char MsgBuffer[MAX_MSG_BUFFER];
//char LogBuffer[MAX_MSG_BUFFER];
//char MsgError[MAX_MSG_BUFFER];
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
   char *Host;
   int Port = 4596;
   char MsgError[255];
   int i=0;
   int iRandom = 0;
   bool bCreate = false;
   char cBuffer[255];
   int iMaxClientes = 10;
   SfgData *pSfgData = NULL;

   ProgramsName[0] = "VDP1000";
   ProgramsName[1] = "FRM1001";
   ProgramsName[2] = "SUP3002";
   ProgramsName[3] = "VDP1020";
   ProgramsName[4] = "FIN1001";
   ProgramsName[5] = "VDP2001";
   ProgramsName[6] = "FRM1002";
   ProgramsName[7] = "SUP2020";
   ProgramsName[8] = "VDP2020";
   ProgramsName[9] = "FIN2001";
   ProgramsTitle[0] = "Pedidos de Venda";
   ProgramsTitle[1] = "Configurações do Sistema";
   ProgramsTitle[2] = "Consulta Pedidos de Compra";
   ProgramsTitle[3] = "Cadastro Clientes";
   ProgramsTitle[4] = "Cadastro Plano de Contas";
   ProgramsTitle[5] = "Análise Pedidos de Venda";
   ProgramsTitle[6] = "Cadastro Usuários";
   ProgramsTitle[7] = "Lista de Telefones dos Fornecedores";
   ProgramsTitle[8] = "Lista de Telefone dos Clientes";
   ProgramsTitle[9] = "Movimentações Caixa";

   printf("Informe o Host: ");
	gets(cBuffer);
   Host = (char*)malloc((strlen(cBuffer)+1)*sizeof(char));
   strcpy(Host,cBuffer);

   printf("Informe a Porta: ");
	gets(cBuffer);
   Port = atoi(cBuffer);

   printf("Informe o Numero de Clientes: ");
	gets(cBuffer);
   iMaxClientes = atoi(cBuffer);

   OpenFileLog(OPEN_ALWAYS);

   //Criando o semáforo que será responsável por controlar a comunicação do Socket
   SfgSocketSemaphore = CreateSemaphore(NULL,1,1,NULL);

   /* initialize random seed: */
   srand ( time(NULL) );

   //Buscando o usuário do sistema operacional
   OSUserNameLenght = 255;
   ZeroMemory(OSUserName,255*sizeof(char));
   if (!GetUserName(OSUserName, &OSUserNameLenght)) {
      strcpy(OSUserName,"Indefinido");
      OSUserNameLenght = 11;
   }
   OSUserNameLenght--;

   hThreadArray = (void**)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, iMaxClientes * sizeof(HANDLE));

   while (i < iMaxClientes) {
      iRandom = rand() % 10;
      //Espera por um tempo randomico
      Sleep(WaitTable[iRandom]);
      //Espera pela liberação do semaforo por 0.5 segundos
      WaitForSingleObject(SfgSocketSemaphore,500);
      //Se não criou a Thread deve criar a mesma
      if (!bCreate) {
         bCreate = true;
         pSfgData = (SfgData*) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(SfgData));

         if( pSfgData == NULL ) {
           // If the array allocation fails, the system is out of memory
           // so there is no point in trying to print an error message.
           // Just terminate execution.
            ExitProcess(2);
         }

         strcpy(pSfgData->Host,Host);
         pSfgData->Port = Port;

         hThreadArray[i] = CreateThread(
            NULL,                   // default security attributes
            0,                      // use default stack size
            SfgThreadFunction,       // thread function name
            pSfgData,               // argument to thread function
            CREATE_SUSPENDED,       // use default creation flags
            &pSfgData->SfgThreadId); // returns the thread identifier

         pSfgData->SfgThread = hThreadArray[i];
      }
      //Tenta estabelecer uma conexão com o servidor de licenças
      SfgLicenceSvcCon(MsgError, pSfgData);

      if (pSfgData->AppClientSocket != INVALID_SOCKET) {
         bCreate = false;
         ResumeThread(hThreadArray[i]);
         i++;
      } else {
         printf(MsgError);
      }

   }

    // Wait until all threads have terminated.

    WaitForMultipleObjects(iMaxClientes, hThreadArray, TRUE, INFINITE);

    // Close all thread handles and free memory allocations.

    for(int i=0; i<iMaxClientes; i++)
    {
        CloseHandle(hThreadArray[i]);
        //if(pDataArray[i] != NULL)
        //{
        //    HeapFree(GetProcessHeap(), 0, pDataArray[i]);
        //    pDataArray[i] = NULL;    // Ensure address is not reused.
        //}
    }

    return 0;
}
//---------------------------------------------------------------------------
char* SysErrorMessage(DWORD ErrorCode) {
	DWORD dwRes;
	LPVOID lpMsgBuf;
	dwRes = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		(ErrorCode == 0)?GetLastError():ErrorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL);
	//Mostra a mensagem.
	if(dwRes != 0)
		return (char*)lpMsgBuf;
	else
		return NULL;
}
//---------------------------------------------------------------------------
void SfgLicenceSvcCon(char *MsgError, SfgData *pSfgData)
{
   int iSizeMsg = 0;
   int iErrorCode = 0;
   // Initialize Winsock.
   WSADATA wsaData;
   pSfgData->AppClientSocket = INVALID_SOCKET;

   iErrorCode = WSAStartup( MAKEWORD(2,2), &wsaData );
   if ( iErrorCode != NO_ERROR ) {
      wsprintf(MsgError, ErrSktConnMsg, pSfgData->Host, pSfgData->Port, iErrorCode,SysErrorMessage(iErrorCode));
      return;
   }
   // Create a socket.
   pSfgData->AppClientSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( pSfgData->AppClientSocket == INVALID_SOCKET ) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, pSfgData->Host, pSfgData->Port, iErrorCode,SysErrorMessage(iErrorCode));
      WSACleanup();
      return;
   }

   // Connect to a server.
   sockaddr_in ServerAddress;

   ServerAddress.sin_family = AF_INET;
   ServerAddress.sin_addr.s_addr = inet_addr( pSfgData->Host );
   ServerAddress.sin_port = htons( pSfgData->Port );

   if ( connect( pSfgData->AppClientSocket, (SOCKADDR*) &ServerAddress, sizeof(ServerAddress) ) == SOCKET_ERROR) {
      pSfgData->AppClientSocket = INVALID_SOCKET;
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, pSfgData->Host, pSfgData->Port, iErrorCode,SysErrorMessage(iErrorCode));
	   WSACleanup();
      return;
   }

   return;
}
//---------------------------------------------------------------------------
DWORD WINAPI SfgThreadFunction( LPVOID lpParam )
{
    SfgData *pSfgData = (SfgData*)lpParam;
    long lPreviousCount;
    char MsgBuffer[MAX_MSG_BUFFER];
    char LogBuffer[MAX_MSG_BUFFER];
    char MsgError[MAX_MSG_BUFFER];
    int iNumPrograms = 0;
    int iAdd, iDel;
    int iRandom = 0;
    int Programs[MAX_PROGRAM];

   for (int i=0;i<MAX_PROGRAM;i++)
      Programs[i] = 0;

   iAdd = iDel = 0;
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(MsgBuffer,MAX_MSG_BUFFER*sizeof(char));
   //Formatando a mensagem para o servidor de licenças
   wsprintf(MsgBuffer,
            SfgAddClientMsg,
            pSfgData->SfgThreadId,
            SFG_ADD_CLIENT,
            OSUserNameLenght,
            OSUserName,
            11,
            "TesteStress");

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(LogBuffer,MAX_MSG_BUFFER*sizeof(char));
   //Formatando a mensagem para o servidor de licenças
   wsprintf(LogBuffer,
            SfgAddClientLog,
            "127.0.0.1",
            "localhost",
            pSfgData->SfgThreadId,
            OSUserName,
            "TesteStress");

   //Espera pela liberação do semaforo por 5 segundos
   WaitForSingleObject(SfgSocketSemaphore,5000);

   //Grava no arquivo de LOG as informações da conexão
   WriteFileLog(LogBuffer);

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(MsgError,MAX_MSG_BUFFER*sizeof(char));

   if (!LicenceSendRecvMsg(MsgBuffer, MsgError,pSfgData)) {
      //Grava no arquivo de LOG as informações da conexão
      WriteFileLog(MsgError);
      //Libera o semaforo deste processo
      ReleaseSemaphore(SfgSocketSemaphore,1,&lPreviousCount);
      return 0;
   }
   ReleaseSemaphore(SfgSocketSemaphore,1,&lPreviousCount);

   while ((iNumPrograms < MAX_PROGRAM) || (iAdd > 0)) {
      iRandom = rand() % 10;
      iDel = rand() % 100;
      //Espera por um tempo randomico
      Sleep(WaitTable[iRandom]);
      //Se nunca adicinou um programa deve adicionar um
      if ((iAdd == 0 || (iDel%2==0)) && (iNumPrograms < MAX_PROGRAM)) {
         //Se o programa já estiver na lista não adiciona
         if (Programs[iRandom] == 1)
            continue;
         //Zerando o buffer, caso tenha alguma mensagem
         ZeroMemory(MsgBuffer,MAX_MSG_BUFFER*sizeof(char));
         //Formatando a mensagem para o servidor de licenças
         wsprintf(MsgBuffer,
                  SfgAddProgramMsg,
                  pSfgData->SfgThreadId,
                  SFG_ADD_PROGRAM,
                  strlen(ProgramsName[iRandom]),
                  ProgramsName[iRandom],
                  strlen(ProgramsTitle[iRandom]),
                  ProgramsTitle[iRandom]);

         //Zerando o buffer, caso tenha alguma mensagem
         ZeroMemory(LogBuffer,MAX_MSG_BUFFER*sizeof(char));
         //Formatando a mensagem para o servidor de licenças
         wsprintf(LogBuffer,
                  SfgAddProgramLog,
                  "127.0.0.1",
                  "localhost",
                  pSfgData->SfgThreadId,
                  ProgramsName[iRandom],
                  ProgramsTitle[iRandom]);
         
         //Espera pela liberação do semaforo por 5 segundos
         WaitForSingleObject(SfgSocketSemaphore,5000);
         
         //Grava no arquivo de LOG as informações da conexão
         WriteFileLog(LogBuffer);
         
         //Zerando o buffer, caso tenha alguma mensagem
         ZeroMemory(MsgError,MAX_MSG_BUFFER*sizeof(char));
         
         if (!LicenceSendRecvMsg(MsgBuffer, MsgError,pSfgData)) {
            //Grava no arquivo de LOG as informações da conexão
            WriteFileLog(MsgError);
         } else {
            iNumPrograms++;
            iAdd++;
            Programs[iRandom] = 1;
         }
         ReleaseSemaphore(SfgSocketSemaphore,1,&lPreviousCount);
      } else { //Deve excluir um programa da lista
         //Porém, somente se o programa a ser excluído estiver na lista
         if (Programs[iRandom] == 1) {
            //Zerando o buffer, caso tenha alguma mensagem
            ZeroMemory(MsgBuffer,MAX_MSG_BUFFER*sizeof(char));
            //Formatando a mensagem para o servidor de licenças
            wsprintf(MsgBuffer,
                     SfgDelProgramMsg,
                     pSfgData->SfgThreadId,
                     SFG_DEL_PROGRAM,
                     strlen(ProgramsName[iRandom]),
                     ProgramsName[iRandom]);

            //Zerando o buffer, caso tenha alguma mensagem
            ZeroMemory(LogBuffer,MAX_MSG_BUFFER*sizeof(char));
            //Formatando a mensagem para o servidor de licenças
            wsprintf(LogBuffer,
                     SfgDelProgramLog,
                     "127.0.0.1",
                     "localhost",
                     pSfgData->SfgThreadId,
                     ProgramsName[iRandom]);
                                 
            //Espera pela liberação do semaforo por 5 segundos
            WaitForSingleObject(SfgSocketSemaphore,5000);
            
            //Grava no arquivo de LOG as informações da conexão
            WriteFileLog(LogBuffer);
            
            //Zerando o buffer, caso tenha alguma mensagem
            ZeroMemory(MsgError,MAX_MSG_BUFFER*sizeof(char));
            
            if (!LicenceSendRecvMsg(MsgBuffer, MsgError,pSfgData)) {
               //Grava no arquivo de LOG as informações da conexão
               WriteFileLog(MsgError);
            } else {
               iAdd--;
               Programs[iRandom] = 0;
            }
            ReleaseSemaphore(SfgSocketSemaphore,1,&lPreviousCount);
         }
      }
   }
   iRandom = rand() % 10;
   //Espera por um tempo randomico
   Sleep(WaitTable[iRandom]);

   //Excluindo o cliente
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(MsgBuffer,MAX_MSG_BUFFER*sizeof(char));
   //Formatando a mensagem para o servidor de licenças
   wsprintf(MsgBuffer,
            SfgDelClientMsg,
            pSfgData->SfgThreadId,
            SFG_DEL_CLIENT);

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(LogBuffer,MAX_MSG_BUFFER*sizeof(char));
   //Formatando a mensagem para o servidor de licenças
   wsprintf(LogBuffer,
            SfgDelClientLog,
            "127.0.0.1",
            "localhost",
            pSfgData->SfgThreadId,
            OSUserName,
            "TesteStress");

   //Espera pela liberação do semaforo por 5 segundos
   WaitForSingleObject(SfgSocketSemaphore,5000);

   //Grava no arquivo de LOG as informações da conexão
   WriteFileLog(LogBuffer);

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(MsgError,MAX_MSG_BUFFER*sizeof(char));

   if (!LicenceSendRecvMsg(MsgBuffer, MsgError,pSfgData)) {
      //Grava no arquivo de LOG as informações da conexão
      WriteFileLog(MsgError);
   }
   ReleaseSemaphore(SfgSocketSemaphore,1,&lPreviousCount);

   shutdown(pSfgData->AppClientSocket,SD_BOTH);
   closesocket(pSfgData->AppClientSocket);
   HeapFree(GetProcessHeap(),0,pSfgData);
   return 1;
}

//---------------------------------------------------------------------------
bool LicenceSendRecvMsg(char *MsgBuffer, char *MsgError, SfgData *pSfgData)
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal
   //Pega o usuário do sistema operacional

   int iSizeMsg = 0;
   int iErrorCode = 0;
   char cBuffer[MAX_MSG_BUFFER];

   iSizeMsg = strlen(MsgBuffer);
   if (send(pSfgData->AppClientSocket, MsgBuffer, iSizeMsg, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktSendMsg, pSfgData->Host, pSfgData->Port, iErrorCode, SysErrorMessage(iErrorCode));
      return false;
   }
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(MsgBuffer,MAX_MSG_BUFFER*sizeof(char));

   if (recv(pSfgData->AppClientSocket, MsgBuffer, MAX_MSG_BUFFER, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktRecvMsg, pSfgData->Host, pSfgData->Port, iErrorCode,SysErrorMessage(iErrorCode));
      return false;
   }

   if (MsgBuffer == NULL) {
      strcpy(MsgError,"Não foi possível receber a resposta do servidor de licenças!");
      return false;
   }
   //Se o tamanho da mensagem de retorno é menor do 20 - erro
   if (strlen(MsgBuffer) < 20) {
      strcpy(MsgError,"Resposta do servidor de licenças no formato desconhecido!");
      return false;
   }
   //Deve validar a mensagem de retorno, vai retonar SFG_RET_LIC_NO
   //Pois o cliente não está conectado, porém se conseguiu comunicação
   //Isto já indica que está OK o servidor de licenças
   char cRet[21]; //O retorno deve estar no formato HEX com 10
   for (int i=0; i < 20; i++)
      cRet[i] = MsgBuffer[i];
   cRet[20] = '\0';

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(cBuffer,MAX_MSG_BUFFER*sizeof(char));
   wsprintf(cBuffer,"0x%08X0x%08X",pSfgData->SfgThreadId,SFG_RET_LIC_OK);
   if (strcmp(cRet,cBuffer) != 0) {
      strcpy(MsgError,&MsgBuffer[23]);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool OpenFileLog(DWORD dwFlagCreate)
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
   wsprintf(pPath,"SfgLicenceClt.log");
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
void WriteFileLog(char *LogMsg)
{
   int iSize;
   time_t sttime;
   struct tm * timeinfo;
   char *DateLogMsg;
   DWORD dwBytesWritten, dwPos;

   //Pega a hora corrente
   time(&sttime);
   //convert to local time
   timeinfo = localtime ( &sttime );
   iSize = strlen(LogMsg) + 1;
   iSize +=24; //Alocando mais o espaço para a data [dd/mm/yyyy hh:mm:ss] e o fim de linha
   DateLogMsg = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSize*sizeof(char)); //new char[iSizeT];
   wsprintf(DateLogMsg,
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
   printf(DateLogMsg);
   HeapFree(GetProcessHeap(),0,DateLogMsg);
}
//---------------------------------------------------------------------------






