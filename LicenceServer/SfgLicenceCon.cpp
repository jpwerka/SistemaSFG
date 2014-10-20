//---------------------------------------------------------------------------
#include <windows.h>
#include <winsock2.h>
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------
//extern "C" bool __declspec(dllexport) WINAPI SfgLicenceSvcCon(char *Host, int Port, char *MsgError);
extern "C" BOOL __declspec(dllexport) WINAPI SfgLicenceSvcCon(char *Host, int Port, char *MsgError);
const char *ErrSktConnMsg = {"Não foi possível conectar com o servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktSendMsg = {"Não foi possível enviar a mensagem ao servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktRecvMsg = {"Não foi possível receber a mensagem do servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
   return 1;
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
BOOL WINAPI SfgLicenceSvcCon(char *Host, int Port, char *MsgError)
{
   int iSizeMsg = 0;
   int iErrorCode = 0;
   // Initialize Winsock.
   WSADATA wsaData;
   SOCKET AppClientSocket;
   iErrorCode = WSAStartup( MAKEWORD(2,2), &wsaData );
   if ( iErrorCode != NO_ERROR ) {
      wsprintf(MsgError, ErrSktConnMsg, Host, Port, iErrorCode,SysErrorMessage(iErrorCode));
      return false;
   }
   // Create a socket.
   AppClientSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( AppClientSocket == INVALID_SOCKET ) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, Host, Port, iErrorCode,SysErrorMessage(iErrorCode));
      WSACleanup();
      return false;
   }

   // Connect to a server.
   sockaddr_in ServerAddress;

   ServerAddress.sin_family = AF_INET;
   ServerAddress.sin_addr.s_addr = inet_addr( Host );
   ServerAddress.sin_port = htons( Port );

   if ( connect( AppClientSocket, (SOCKADDR*) &ServerAddress, sizeof(ServerAddress) ) == SOCKET_ERROR) {
      AppClientSocket = INVALID_SOCKET;
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, Host, Port, iErrorCode,SysErrorMessage(iErrorCode));
	   WSACleanup();
      return false;
   }

   // Send and receive data.
   char cBuffer[255];

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(cBuffer,255*sizeof(char));
   wsprintf(cBuffer,"0x%08X0x%08X",GetCurrentProcessId(),9);

   iSizeMsg = strlen(cBuffer);
   if (send(AppClientSocket, cBuffer, iSizeMsg, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, Host, Port, iErrorCode,SysErrorMessage(iErrorCode));
	   WSACleanup();
      return false;
   }
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(cBuffer,255*sizeof(char));

   if (recv(AppClientSocket, cBuffer, 255, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      wsprintf(MsgError, ErrSktConnMsg, Host, Port, iErrorCode,SysErrorMessage(iErrorCode));
	   WSACleanup();
      return false;
   }

   if (cBuffer == NULL) {
      strcpy(MsgError,"Não foi possível receber a resposta do servidor de licenças!");
      return false;
   }
   //Se o tamanho da mensagem de retorno é menor do 20 - erro
   if (strlen(cBuffer) < 20) {
      strcpy(MsgError,"Resposta do servidor de licenças no formato desconhecido!");
      return false;
   }
   //Deve validar a mensagem de retorno, vai retonar SFG_RET_LIC_NO
   //Pois o cliente não está conectado, porém se conseguiu comunicação
   //Isto já indica que está OK o servidor de licenças
   char cRet[21]; //O retorno deve estar no formato HEX com 10
   for (int i=0; i < 20; i++)
      cRet[i] = cBuffer[i];
   cRet[20] = '\0';

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(cBuffer,255*sizeof(char));
   wsprintf(cBuffer,"0x%08X0x%08X",GetCurrentProcessId(),-1);
   if (strcmp(cRet,cBuffer) != 0) {
      strcpy(MsgError,"Resposta do servidor de licenças no formato desconhecido!");
      return false;
   }
   shutdown(AppClientSocket,SD_BOTH);
   closesocket(AppClientSocket);
   return true;
}
//---------------------------------------------------------------------------
