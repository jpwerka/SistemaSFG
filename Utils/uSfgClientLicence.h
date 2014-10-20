//---------------------------------------------------------------------------
#ifndef uSfgClientLicenceH
#define uSfgClientLicenceH
//---------------------------------------------------------------------------
#define SFG_SIGNED_TIME  2*60*1000  //2 Minutos
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
//---------------------------------------------------------------------------
class PACKAGE TSfgClientLicence : public TObject
{
private:
   char FRetMsgOK[21];
   char FOSUserName[255];
   DWORD FOSUserNameLenght;
private:
   bool __fastcall LicenceSendRecvMsg(int iLastMsg, String &sMsgError);
public:
   bool __fastcall LicenceAddClient();
   bool __fastcall LicenceDelClient();
   bool __fastcall LicenceAddProgram(char*, char*);
   bool __fastcall LicenceDelProgram(char*);
public:		// User declarations
   HANDLE AppEndSignEvent;
   HANDLE AppSocketSemaphore;
public:
   __fastcall TSfgClientLicence();
   __fastcall ~TSfgClientLicence();
   static bool __fastcall LicenceValidFile();
   static char* __fastcall GetFirstSerial(char *ErrorMsg);
};
//---------------------------------------------------------------------------
extern PACKAGE TSfgClientLicence *AppClientLicence;
//---------------------------------------------------------------------------
#endif
