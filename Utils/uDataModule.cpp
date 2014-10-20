//---------------------------------------------------------------------------
#include <vcl.h>
#include <IniFiles.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataBase.h"
#pragma hdrstop
#include "uDataModule.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSfgDataCenter *SfgDataCenter = NULL;
TZConnection *AppConnection = NULL;
SOCKET AppClientSocket = INVALID_SOCKET;
//---------------------------------------------------------------------------
const char *SvcKeyLicence = {"LicenceServer"};
const char *CliKeyLicence = {"LicenceClient"};
const char *NoKeyLicenceMsg = {"Não foi encontrado a seção [%s] no arquivo de conexão:\n%s"};
const char *ErrSktConnMsg = {"Não foi possível conectar com o servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktSendMaxMsg = {"Não foi possível delimitar o tamanho máximo da mensagem a ser enviada para o servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktRecvMaxMsg = {"Não foi possível delimitar o tamanho máximo da mensagem a ser recebida do servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktSendMsg = {"Não foi possível enviar a mensagem ao servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktRecvMsg = {"Não foi possível receber a mensagem do servidor de licenças.\nHost: %s Porta: %d Erro Nº: %d\n%s"};
const char *ErrSktGeneralMsg = {"Ocorreu um erro genérico ao comunicar-se com servidor de licenças.\nHost: %s Porta: %d Erro Nº %d"};
//---------------------------------------------------------------------------
__fastcall TSfgDataCenter::TSfgDataCenter(TComponent* Owner)
	: TDataModule(Owner)
{
   this->ExistDataBase = false;
   this->IsLicenceOK = false;
   this->InTransaction = false;
   AppDB = new SfgDB();
   AppLicence = new SfgLicence();
   AppLicence->UseServer = true;
   AppLicence->CodCliente = "";
   AppLicence->DenCliente = "";
   AppLicence->Validade = 0;
   AppLicence->IdLicence = "";
   AppLicence->NumLicence = 0;
   AppLicenceSvr = new SfgLicenceSvr();
   AppLicenceSvr->Address = "";
   AppLicenceSvr->Port = 0;
   AppLicenceSvr->LastMsg = 0;
   AppLicenceSvr->MsgBuffer = NULL;
   AppLicenceSvr->ClientSocket = NULL;
   AppLicenceSvr->OnReceiveMessage = NULL;
   ::AppConnection = this->AppConnection;
   AppConnection->Connected = false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::ValidLicence()
{
   //Deve carregar os parametros do servidor de licenças
   if (!LerLicenceServer())
      return false;

   //Tenta efetivar a conexão com o servidor de licenças
   if (AppLicence->UseServer) {
      if (!OpenClientSocket()) {
         return false;
      } else {
         this->IsLicenceOK = true;
      }
   } else {
      //Deve carregar os parametros do cliente de licenças
      if (!LerLicenceClient())
         return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::ValidDatabase()
{
	//Deve carregar os parâmetros de inicialização do banco de dados
	if (!LerConnections())
      return false;
   //Valida para verificar se o banco de dados existe
   AppConnection->Database = "";
   AppConnection->Catalog = "";
try {
   AppConnection->Connected = true;
} catch (Exception &e) {
   String sMsg = "Ocorreo o seguinte erro ao tentar conectar no servidor de banco de dados:\n";
   sMsg += e.Message;
   MessageBox(NULL,sMsg.c_str(),"Conexão Banco de Dados",APP_ERROR);
   return false;
}
   if (!ExistDatabase(AppDB->Database)) {
      String sMsg = "Não existe o banco de dados " + QuotedStr(AppDB->Database) +\
                   " no servidor " + QuotedStr(AppDB->Host) + ".";
      MessageBox(NULL,sMsg.c_str(),"Conexão Banco de Dados",APP_ERROR);
      AppConnection->Connected = false;
   } else {
      AppConnection->Connected = false;
      AppConnection->Database = AppDB->Database;
      AppConnection->Catalog = AppDB->Database;
      try {
         AppConnection->Connected = true;
      } catch (Exception &e) {
         String sMsg = "Ocorreu o seguinte erro ao tentar conectar no servidor de banco de dados:\n";
         sMsg += e.Message;
         MessageBox(NULL,sMsg.c_str(),"Conexão Banco de Dados",APP_ERROR);
         return false;
      }
      this->ExistDataBase = true;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::LerConnections()
{
	String Msg;
	String User;
	String Password;
	String PathIni;
	PathIni = ExtractFilePath(Application->ExeName) + "connection.ini";
	TIniFile *Cfg = new TIniFile(PathIni);
try {
	try {
      if (!Cfg->SectionExists(AppArgs->Database)) {
         Msg = Format(NoKeyLicenceMsg, ARRAYOFCONST((AppArgs->Database,PathIni)));
			MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
			return false;
      }
		// Protocolo de comunicação
		AppConnection->Protocol = Cfg->ReadString(AppArgs->Database,"protocol","mysql");
		// Host de conexão
		AppConnection->HostName = Cfg->ReadString(AppArgs->Database,"hostname","localhost");
      AppDB->Host = AppConnection->HostName;
		// Porta de conexão
		AppConnection->Port = Cfg->ReadInteger(AppArgs->Database,"port",3306);
      AppDB->Port = AppConnection->Port;
		// Banco de dados padrão
		//AppConnection->Database = Cfg->ReadString(AppArgs->Database,"database","");
      AppDB->Database = Cfg->ReadString(AppArgs->Database,"database","");
		if (AppDB->Database.Length() <= 0) {
			MessageBox(NULL,"Não foi passado o banco de dados padrão para conexão!", "Mensagem de Erro", APP_ERROR);
			return false;
		}
		User = Cfg->ReadString(AppArgs->Database,"user","root");
		AppConnection->User = DecryptText(User.c_str());;
      AppDB->User = AppConnection->User;
		Password = Cfg->ReadString(AppArgs->Database,"password","");
		if(Password.Length()) {
			Password = DecryptText(Password.c_str());
			AppConnection->Password = Password;
		} else {
         AppConnection->Password = "";
      }
      AppDB->Password = AppConnection->Password;
      AppDB->Connection = (void*)AppConnection;
	}
	catch(Exception &e){
		Msg = "Ocorreu o seguinte erro ao tentar recuperar as informações de conexão:\n";
		Msg = Msg + e.Message;
		MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
		return false;
	}
}
__finally{delete Cfg;}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::LerLicenceServer()
{
	String sMsg = "";
	String sPathIni = ExtractFilePath(Application->ExeName) + "connection.ini";
	TIniFile *Cfg = new TIniFile(sPathIni);
try {
	try {
      if (!Cfg->SectionExists(SvcKeyLicence)) {
         sMsg = Format(NoKeyLicenceMsg, ARRAYOFCONST((SvcKeyLicence,sPathIni)));
			MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
			return false;
      }
		// Utiliza servidor de licenças
		AppLicence->UseServer = Cfg->ReadBool(SvcKeyLicence,"useserver",true);
		// Host de conexão
		AppLicenceSvr->Address = Cfg->ReadString(SvcKeyLicence,"address","127.0.0.1");
		// Porta de conexão
		AppLicenceSvr->Port = Cfg->ReadInteger(SvcKeyLicence,"port",4596);
	}
	catch(Exception &e){
		sMsg = "Ocorreu o seguinte erro ao tentar recuperar as informações do servidor de licenças:\n";
		sMsg = sMsg + e.Message;
		MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
		return false;
	}
}
__finally{delete Cfg;}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::LerLicenceClient()
{
	String sMsg = "";
	String sPathIni = ExtractFilePath(Application->ExeName) + "connection.ini";
	TIniFile *Cfg = new TIniFile(sPathIni);
try {
	try {
      if (!Cfg->SectionExists(CliKeyLicence)) {
         sMsg = Format(NoKeyLicenceMsg, ARRAYOFCONST((CliKeyLicence,sPathIni)));
			MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
			return false;
      }
		//Código do cliente para validar contra a licença
      AppLicence->CodCliente = Cfg->ReadString(CliKeyLicence,"cliente","");
	}
	catch(Exception &e){
		sMsg = "Ocorreu o seguinte erro ao tentar recuperar as informações do cliente de licenças:\n";
		sMsg = sMsg + e.Message;
		MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
		return false;
	}
}
__finally{delete Cfg;}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::ClientSocketRead()
{
   String sMsg;
   int iErrorCode = 0;
   //Aqui deve fazer a leitura das mensagens
   //Se nunca recebeu uma mensagem deve pré-alocar a memória
   if (AppLicenceSvr->MsgBuffer == NULL) {
      AppLicenceSvr->MsgBuffer = (char*)HeapAlloc(GetProcessHeap(),0,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   }
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));

   if (AppClientSocket == INVALID_SOCKET)
      return false;

   if (recv(AppClientSocket, AppLicenceSvr->MsgBuffer, SFG_MAX_SIZE_MSG, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktSendMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      throw Exception(sMsg);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::ClientSocketSend()
{
   String sMsg;
   int iErrorCode = 0;
   int iSizeMsg = 0;
   //Aqui deve fazer o envio das mensagens
   if (AppClientSocket == INVALID_SOCKET)
      return false;

   iSizeMsg = strlen(AppLicenceSvr->MsgBuffer);
   iSizeMsg = (iSizeMsg > SFG_MAX_SIZE_MSG) ? SFG_MAX_SIZE_MSG : iSizeMsg;
   if (send(AppClientSocket, AppLicenceSvr->MsgBuffer, iSizeMsg, 0) == SOCKET_ERROR) {
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktRecvMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      throw Exception(sMsg);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::OpenClientSocket()
{
   String sMsg;
   int iSendBufSize = 0;
   int iErrorCode = 0;
   // Initialize Winsock.
   WSADATA wsaData;
   int iResult = WSAStartup( MAKEWORD(2,2), &wsaData );
   if ( iResult != NO_ERROR ) {
      sMsg = Format(ErrSktConnMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iResult,SysErrorMessage(iResult))));
      MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
      return false;
   }
   // Create a socket.
   AppClientSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
   if ( AppClientSocket == INVALID_SOCKET ) {
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktConnMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
      WSACleanup();
      return false;
   }

   // Connect to a server.
   sockaddr_in ServerAddress;

   ServerAddress.sin_family = AF_INET;
   ServerAddress.sin_addr.s_addr = inet_addr( AppLicenceSvr->Address.c_str() );
   ServerAddress.sin_port = htons( AppLicenceSvr->Port );

   if ( connect( AppClientSocket, (SOCKADDR*) &ServerAddress, sizeof(ServerAddress) ) == SOCKET_ERROR) {
      AppClientSocket = INVALID_SOCKET;
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktConnMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	   WSACleanup();
      return false;
   }

   //Delimita o tamanho da mensagem a ser enviada para o Socket
   iSendBufSize = SFG_MAX_SIZE_MSG;
   if (setsockopt(AppClientSocket,SOL_SOCKET,SO_SNDBUF,(char *)&iSendBufSize,sizeof(iSendBufSize)) == -1)
   {
      AppClientSocket = INVALID_SOCKET;
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktSendMaxMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
      return false;
   }
   //Delimita o tamanho da mensagem a ser recebida pelo Socket
   iSendBufSize = SFG_MAX_SIZE_MSG;
   if (setsockopt(AppClientSocket,SOL_SOCKET,SO_RCVBUF,(char *)&iSendBufSize,sizeof(iSendBufSize)) == -1)
   {
      AppClientSocket = INVALID_SOCKET;
      iErrorCode = WSAGetLastError();
      sMsg = Format(ErrSktRecvMaxMsg, ARRAYOFCONST((AppLicenceSvr->Address,AppLicenceSvr->Port,iErrorCode,SysErrorMessage(iErrorCode))));
      MessageBox(NULL,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
      return false;
   }
   AppLicenceSvr->ClientSocket = (void*)AppClientSocket;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::CloseClientSocket()
{
   if (AppClientSocket != INVALID_SOCKET) {
      shutdown(AppClientSocket,SD_BOTH);
      closesocket(AppClientSocket);
   }
   AppClientSocket = INVALID_SOCKET;
   AppLicenceSvr->ClientSocket = NULL;
   return true;
}
//---------------------------------------------------------------------------
//void __fastcall TSfgDataCenter::WaitForSocket()
//{
//   while (true) {
//      Application->ProcessMessages();
//      if (!bWaitSocket)
//         break;
//   }
//}
////---------------------------------------------------------------------------
//void __fastcall TSfgDataCenter::SetSocketToWait(bool bWait)
//{
//   bWaitSocket = bWait;
//}
//---------------------------------------------------------------------------
void __fastcall TSfgDataCenter::DataModuleDestroy(TObject *Sender)
{
   CloseClientSocket();
   HeapFree(GetProcessHeap(),0,AppLicenceSvr->MsgBuffer);
   if (AppLicenceSvr != NULL) delete AppLicenceSvr;
   if (AppDB != NULL) delete AppDB;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::StartTrans()
{
   if (InTransaction) {
      MessageBox(NULL,"O sistema já está em transação. Não é permitido abrir uma nova.","Mensagem de Erro",APP_ERROR);
      return false;
   }
   QyTransaction->SQL->Text = "START TRANSACTION";
try {
   QyTransaction->ExecSQL();
} catch (...) {
   return false;
}
   InTransaction = true;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::CommitTrans()
{
   if (!InTransaction) {
      return true;
   }
   QyTransaction->SQL->Text = "COMMIT";
try {
   QyTransaction->ExecSQL();
} catch (...) {
   return false;
}
   InTransaction = false;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgDataCenter::RollbackTrans()
{
   if (!InTransaction) {
      return true;
   }
   QyTransaction->SQL->Text = "ROLLBACK";
try {
   QyTransaction->ExecSQL();
} catch (...) {
   return false;
}
   InTransaction = false;
   return true;
}
//---------------------------------------------------------------------------






