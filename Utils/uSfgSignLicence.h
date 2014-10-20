//---------------------------------------------------------------------------
#ifndef uSfgSignLicenceH
#define uSfgSignLicenceH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
class PACKAGE TSfgSignLicence : public TThread
{
private:
   char FRetMsgOK[21];
   String FErrorMsg;
private:
   void __fastcall CreateMsgEndApp(void);
   bool __fastcall LicenceSignClient(String &sMsgError);
protected:
   void __fastcall Execute();
public:
   __fastcall TSfgSignLicence(bool CreateSuspended);
};
//---------------------------------------------------------------------------
class TSfgEndApplication : public TThread
{            
private:
   void __fastcall AppTerminate(void);
protected:
   void __fastcall Execute();
public:
   __fastcall TSfgEndApplication(bool CreateSuspended);
};
//---------------------------------------------------------------------------
class TSfgMsgEndApp : public TForm
{
private:
   TImage *Image;
   TLabel *ErrorMsg;
   TLabel *TimeMsg;
   TTimer *MsgTimer;
   int iSeconds;
protected:
   void __fastcall MsgTimerTimer(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
public:
   __fastcall TSfgMsgEndApp(TComponent* Owner, String sMsgError);
};
//---------------------------------------------------------------------------
extern PACKAGE TSfgSignLicence *AppSignLicence;
//---------------------------------------------------------------------------
#endif
