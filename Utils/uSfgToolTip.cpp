//---------------------------------------------------------------------------
#pragma hdrstop
#include "uSfgToolTip.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall SfgToolTips::SfgToolTips(TForm *Parent, const String VTitle, const TTIcon VIcon,
                        const bool VCenter, const TColor VFontColor, const TColor VBackColor,
                        const long VHoverTime, const long VPopupTime, const TTStyle  VStyle)
{
  FParent = Parent;
  if(VTitle == "")
     FTitle = FParent->Caption;
  else
     FTitle = VTitle;
  FIcon = VIcon;
  FCenter = VCenter;
  FStyle = VStyle;
  FHoverTime = VHoverTime;
  FPopupTime = VPopupTime;
  FFontColor = VFontColor;
  FBackColor = VBackColor;
}
//---------------------------------------------------------------------------
__fastcall SfgToolTips::~SfgToolTips()
{
  if(FHandle)
     DestroyWindow(FHandle);
}
//---------------------------------------------------------------------------
HWND __fastcall SfgToolTips::CreateToolTips()
{
  if(FHandle)
  {
     DestroyWindow(FHandle);
     FHandle = NULL;
  }
  FHandle = CreateWindowEx(WS_EX_TOOLWINDOW, TOOLTIPS_CLASS, (LPSTR) NULL,
        FStyle, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, FParent->Handle, (HMENU) NULL, HInstance, NULL);

  if (FHandle == NULL)
      return NULL;

  SendMessage(FHandle, WM_SETFONT,(WPARAM)FParent->Font->Handle,MAKELPARAM(TRUE, 0));  SendMessage(FHandle, TTM_SETTITLE, Icon, int(FTitle.c_str()));
  SendMessage(FHandle, TTM_SETTIPTEXTCOLOR, ColorToRGB(FFontColor), 0);
  SendMessage(FHandle, TTM_SETTIPBKCOLOR, ColorToRGB(FBackColor), 0);
  SendMessage(FHandle, TTM_SETDELAYTIME, TTDT_INITIAL, FHoverTime);
  SendMessage(FHandle, TTM_SETDELAYTIME, TTDT_AUTOPOP, FPopupTime);
  FParent->Tag = (int)this;
  SetToolTips(FParent);
  return FHandle;
}
//-------------------------------------------------------------------------------------
void __fastcall SfgToolTips::SetFontColor(TColor Value)
{
  if(FFontColor == Value) return;
  if(FHandle) 
     SendMessage(FHandle, TTM_SETTIPTEXTCOLOR, ColorToRGB(Value), 0);
  FFontColor = Value;    
}
//-------------------------------------------------------------------------------------
void __fastcall SfgToolTips::SetBackColor(TColor Value)
{
  if(FBackColor == Value) return;
  if(FHandle) 
     SendMessage(FHandle, TTM_SETTIPBKCOLOR, ColorToRGB(Value), 0);
  FBackColor = Value;    
}
//-------------------------------------------------------------------------------------
void __fastcall SfgToolTips::SetIcon(TTIcon Value)
{
  if(FIcon == Value) return;
  if(FHandle) 
     SendMessage(FHandle, TTM_SETTITLE, Value, int(FTitle.c_str()));
  FIcon = Value;
}
//----------------------------------------------------------------------------
void __fastcall SfgToolTips::SetTitle(String Value)
{
  if(FTitle == Value) return;
  if(FHandle)
     SendMessage(FHandle, TTM_SETTITLE, FIcon, int(Value.c_str()));
  FTitle = Value;
}
//----------------------------------------------------------------------------
void __fastcall SfgToolTips::SetToolTipText(UINT Id, String Value)
{
  TOOLINFO ToolInfo = GetToolTip(Id);
  ToolInfo.cbSize = sizeof(TOOLINFO);
  ToolInfo.lpszText = BreakLine(Value);
  if(FHandle)
	  SendMessage(FHandle, TTM_UPDATETIPTEXT, 0,int(&ToolInfo));
}
//----------------------------------------------------------------------------
void __fastcall SfgToolTips::SetHoverTime(long Value)
{
  if(FHoverTime == Value) return;
  if(FHandle) 
     SendMessage(FHandle, TTM_SETDELAYTIME, TTDT_INITIAL, Value);
  FHoverTime = Value;    
}
//----------------------------------------------------------------------------
void __fastcall SfgToolTips::SetPopupTime(long Value)
{
  if(FPopupTime == Value) return;
  if(FHandle) 
     SendMessage(FHandle, TTM_SETDELAYTIME, TTDT_AUTOPOP, Value);
  FPopupTime = Value;    
}
//---------------------------------------------------------------------------
bool __fastcall SfgToolTips::AddToolTip(TWinControl *Ct)
{
  try{
    if(Ct->Hint.Length())
    {
      Ct->ShowHint = false;
      //Adiciona a dica personalizada
      TOOLINFO ti;

      ti.cbSize = sizeof(TOOLINFO);
      ti.uFlags = TTF_IDISHWND;
      ti.hwnd = FParent->Handle;
      ti.uId = (UINT)Ct->Handle;
      ti.hinst = 0;
		ti.lpszText = BreakLine(Ct->Hint);
		SendMessage(FHandle, TTM_ADDTOOL, 0,(LPARAM)(LPTOOLINFO) &ti);
	 }
  }
  catch(...){return false;}
  return true;
}
//---------------------------------------------------------------------------
bool __fastcall SfgToolTips::AddToolTip(TWinControl *Ct, RECT Rt, UINT Id, String Dica)
{
  try{
    if(Dica.Length())
    {
      Ct->ShowHint = false;
      //Adiciona a dica personalizada
      TOOLINFO ti;

      ti.cbSize = sizeof(TOOLINFO);
      ti.uFlags = 0;
      ti.hwnd = Ct->Handle;
      ti.rect = Rt;
      ti.uId = Id;
      ti.hinst = 0;
      ti.lpszText = BreakLine(Dica);
		SendMessage(FHandle, TTM_ADDTOOL, 0,(LPARAM)(LPTOOLINFO) &ti);
	 }
  }
  catch(...){return false;}
  return true;
}
//---------------------------------------------------------------------------
TOOLINFO __fastcall SfgToolTips::GetToolTip(UINT Id)
{
  int i;
  int Count;
  TOOLINFO ti;
  Count = SendMessage(Handle,TTM_GETTOOLCOUNT,0,0);
  ZeroMemory(&ti,sizeof(TOOLINFO));
  ti.cbSize = sizeof(TOOLINFO);

  for(i=0;i<Count;i++)
  {
    if(SendMessage(Handle,TTM_ENUMTOOLS,(UINT)i,(LPARAM)(LPTOOLINFO)&ti))
    {
      if(ti.uId == Id)
        return ti;
    }
  }
  return ti;
}
//---------------------------------------------------------------------------
TOOLINFO __fastcall SfgToolTips::DelToolTip(UINT Id)
{
  int i;
  int Count;
  TOOLINFO ti;
  Count = SendMessage(Handle,TTM_GETTOOLCOUNT,0,0);
  ZeroMemory(&ti,sizeof(TOOLINFO));
  ti.cbSize = sizeof(TOOLINFO);

  for(i=0;i<Count;i++)
  {
    if(SendMessage(Handle,TTM_ENUMTOOLS,(UINT)i,(LPARAM)(LPTOOLINFO)&ti))
    {
      if(ti.uId == Id)
      {
        SendMessage(Handle,TTM_DELTOOL,0,(LPARAM)(LPTOOLINFO)&ti);
        return ti;
      }
    }
  }
  return ti;
}
//---------------------------------------------------------------------------
int __fastcall SfgToolTips::SetToolTips(TWinControl* Pai)
{
  int i,j;
  TControl *Ct;
  char *pText;

  j = Pai->ControlCount;
  for(i=0; i<j;i++)
  {
   try{
    Ct = Pai->Controls[i];
    if(Ct == NULL) continue;
    if(InheritsFrom(Ct->ClassType(),__classid(TWinControl)))
    {
     try{
       if(Pai->ContainsControl(Ct))
          SetToolTips((TWinControl*)Ct);
     }
     __finally{}
     try{
       if(Ct->Hint.Length())
       {
			Ct->ShowHint = false;
			//Adiciona a dica personalizada
			TOOLINFO ti;
			ti.cbSize = sizeof(TOOLINFO);
			ti.uFlags = TTF_IDISHWND;
			ti.hwnd = FParent->Handle;
         ti.uId = (UINT)((TWinControl*)Ct)->Handle;
			ti.hinst = 0;
			ti.lpszText = BreakLine(Ct->Hint);
			SendMessage(FHandle, TTM_ADDTOOL, 0,(LPARAM)(LPTOOLINFO) &ti);
		 }
	  }
     __finally{}
    }
   }
__finally{}
 }
 return 1;
}
//---------------------------------------------------------------------------
char* __fastcall SfgToolTips::BreakLine(String Tip)
{
   char *ToolText;
//  if (ToolText != NULL) {
//		delete ToolText;
//  }
  //char *Temp = new char[Tip.Length()];
  ToolText = new char[Tip.Length()+1];
  int I, J;
  ToolText = Tip.c_str();
  J = Tip.Length();
  for(I =0;I < J;I++){
	  if(ToolText[I] == '|')
		 ToolText[I] = char(13);
  }
  return ToolText;
  //return StringReplace(Tip,"|",char(13), TReplaceFlags() << rfReplaceAll).c_str();
}
//---------------------------------------------------------------------------
HHOOK FHook;
// GetMsgProc - monitors the message stream for mouse messages intended
//     for a control window in the dialog box.
// Returns a message-dependent value.
// nCode - hook code
// wParam - message flag (not used)
// lParam - address of an MSG structure
LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    MSG *lpMsg;
    HWND hWnd;
    SfgToolTips *pTTp;

    lpMsg = (MSG *) lParam;
try{
    if(Screen->ActiveForm == NULL)
		return (CallNextHookEx(FHook, nCode, wParam, lParam));

	 if (nCode < 0 || !(IsChild(Screen->ActiveForm->Handle, lpMsg->hwnd)))
        return (CallNextHookEx(FHook, nCode, wParam, lParam));

    if(Screen->ActiveForm->Tag > 0)
      pTTp =  (SfgToolTips *)Screen->ActiveForm->Tag;
    else
      pTTp =  (SfgToolTips *)NULL;
    if(pTTp == NULL)
      return 0;

    switch (lpMsg->message) {
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            if (pTTp->Handle != NULL) {

                MSG msg;

                msg.lParam = lpMsg->lParam;
                msg.wParam = lpMsg->wParam;
                msg.message = lpMsg->message;
                msg.hwnd = lpMsg->hwnd;
                SendMessage(pTTp->Handle, TTM_RELAYEVENT, 0,
                    (LPARAM) (LPMSG) &msg);
            }
            break;
        default:
            break;
	 }
}
catch(...){
  MessageBox(NULL,"Erro inesperado nas dicas!","Mensagem de Erro",MB_OK|MB_ICONSTOP);
  }
    return (CallNextHookEx(FHook, nCode, wParam, lParam));
}
//---------------------------------------------------------------------------
void InstallSfgToolTipHook(void) {
  // Install a hook procedure to monitor the message stream for mouse
  // messages intended for the controls in the dialog box.
  FHook = SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)&GetMsgProc,
        (HINSTANCE) NULL, GetCurrentThreadId());
}
void UninstallSfgToolTipHook(void) {
   UnhookWindowsHookEx(FHook);
}
//---------------------------------------------------------------------------
#pragma startup InstallSfgToolTipHook
#pragma exit UninstallSfgToolTipHook
//---------------------------------------------------------------------------

