//---------------------------------------------------------------------------
#ifndef uSfgLicenceSvcH
#define uSfgLicenceSvcH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <ScktComp.hpp>
#include <ExtCtrls.hpp>

#define SFG_SIGNED_TIME  3*10*1000  //3 Minutos
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
#define SFG_SIZE_CODCLI  0x0000000F
#define SFG_MAX_SIZE_MSG 0x00000400
//---------------------------------------------------------------------------
struct _SfgClientInfo;
typedef struct _SfgClientProgram {
   _SfgClientInfo *ClientInfo;
   String ProgramName;
   String ProgramTitle;
   //_SfgClientProgram *prew;
   //_SfgClientProgram *next;
} SfgClientProgram;

typedef struct _SfgClientInfo {
   int SocketHandle;
   String RemoteAddress;
   String RemoteHost;
   int ProcessID;
   double LastSigned;
   String OsUser;
   String SfgUser;
   TList *Programs;
   //_SfgClientProgram *Programs;
   //_SfgClientInfo *prew;
   //_SfgClientInfo *next;
} SfgClientInfo;
//---------------------------------------------------------------------------
class TSfgLicenceSvc : public TService
{
__published:    // IDE-managed Components
   TServerSocket *ServerSocket;
   TTimer *SocketTimer;
   void __fastcall ServiceAfterInstall(TService *Sender);
   void __fastcall ServiceStart(TService *Sender, bool &Started);
   void __fastcall ServiceStop(TService *Sender, bool &Stopped);
   void __fastcall ServiceExecute(TService *Sender);
   void __fastcall ServerSocketClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
   void __fastcall SocketTimerTimer(TObject *Sender);
   void __fastcall ServerSocketListen(TObject *Sender,
          TCustomWinSocket *Socket);
private:        // User declarations
   bool bLogEnabled;
   __int64 iMaxSizeLog;
   int iPortSocket;
   int iNumLicence;
   int iNumClients;
   HANDLE hFileLog;
   TList *ClientsInfo;
   String sCodCliente;
   TDateTime Validade;
   HANDLE AppSocketSemaphore;
   TCriticalSection *LockSocket;
private:
   bool __fastcall ReadConfiguration(char *LogMsg);
   bool __fastcall OpenFileLog(DWORD dwFlagCreate);
   void __fastcall WriteFileLog(char *LogMsg);
   bool __fastcall ProcessMessage(int iProcessID, int MessageID, SfgClientInfo **ClientInfo,
          TCustomWinSocket *Socket, char **MsgBuffer, const bool bPostMsg = true);
   void __fastcall AddClientInfo(SfgClientInfo **ClientInfo, char **MsgBuffer);
   void __fastcall AddClientProgram(SfgClientInfo **ClientInfo, char **MsgBuffer, SfgClientProgram **ClientProgram);
   void __fastcall RemoveClientInfo(SfgClientInfo **ClientInfo);
   void __fastcall RemoveClientProgram(SfgClientInfo **ClientInfo, char **MsgBuffer);
public:         // User declarations
	__fastcall TSfgLicenceSvc(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);
	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TSfgLicenceSvc *SfgLicenceSvc;
//---------------------------------------------------------------------------
#endif
