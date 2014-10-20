//---------------------------------------------------------------------------
#ifndef uSfgMsgOptionH
#define uSfgMsgOptionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
extern PACKAGE int SfgMsgOption(String strMsg, TMsgDlgType DlgType, TStrings *DlgButtons,
    const String strCaption = NULL,
    const int DefaultButton = -1,
    const int CancelButton = -1);
#endif
