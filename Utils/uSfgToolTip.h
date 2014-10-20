//---------------------------------------------------------------------------
#ifndef uSfgToolTipH
#define uSfgToolTipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
#define TTS_STANDARD  0
#define SWP_FLAGS     SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOMOVE

enum TTStyle {
   TTStandardIfActive = TTS_STANDARD,                   //suppress if parent form is not active
   TTBalloonIfActive = TTS_BALLOON,                     //suppress if parent form is not active
   TTStandardAlways = TTS_STANDARD | TTS_ALWAYSTIP,    //display even if parent form is not active
   TTBalloonAlways = TTS_BALLOON | TTS_ALWAYSTIP,      //display even if parent form is not active
   TTNone = -1                                          //kill tooltip (this is simply treated as illegal)
};

enum TTIcon {
   TTIconNone = 0,
   TTIconInfo = 1,         /* i in white balloon */
   TTIconWarning = 2,      /* ! in yellow triangle */
   TTIconError = 3        /* x in red circle */
};

//LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam);

class PACKAGE SfgToolTips : public System::TObject
{
private:
   HWND FHandle;
   TForm* FParent;
   String FTitle;
   TTStyle FStyle;
   TTIcon FIcon;
   bool FCenter;
   long FHoverTime;
   long FPopupTime;
   TColor FFontColor;
   TColor FBackColor;
public:
   __fastcall SfgToolTips(TForm *Parent,
      const String VTitle = "",
      const TTIcon VIcon = TTIconNone,
      const bool VCenter = false,
      const TColor VFontColor = clInfoText,
      const TColor VBackColor = clInfoBk,
      const long VHoverTime = -1,
      const long VPopupTime = -1,
      const TTStyle VStyle = TTBalloonAlways);
   __fastcall ~SfgToolTips();
   __property HWND Handle  = { read=FHandle};
   __property String Title  = { read=FTitle, write=SetTitle };
   __property TTIcon Icon  = { read=FIcon, write=SetIcon };
   __property TTStyle Style  = { read=FStyle, write=FStyle };
   __property bool Center  = { read=FCenter, write=FCenter };
   __property TColor FontColor  = { read=FFontColor, write=SetFontColor };
   __property TColor BackColor  = { read=FBackColor, write=SetBackColor };
   __property long HoverTime  = { read=FHoverTime, write=SetHoverTime };
   __property long PopupTime  = { read=FPopupTime, write=SetPopupTime };
   bool __fastcall AddToolTip(TWinControl *Ct);
   bool __fastcall AddToolTip(TWinControl *Ct, RECT Rt, UINT Id, String Dica);
   TOOLINFO __fastcall GetToolTip(UINT Id);
   TOOLINFO __fastcall DelToolTip(UINT Id);
   HWND __fastcall CreateToolTips();
   void __fastcall SetToolTipText(UINT Id, String Value);
private:
   int __fastcall SetToolTips(TWinControl* Pai);
   char* __fastcall BreakLine(String Tip);
   void __fastcall SetFontColor(TColor Value);
   void __fastcall SetBackColor(TColor Value);
   void __fastcall SetIcon(TTIcon Value);
   void __fastcall SetTitle(String Value);
   void __fastcall SetText(String Value);
   void __fastcall SetHoverTime(long Value);
   void __fastcall SetPopupTime(long Value);
};
//extern HHOOK FHook;
#endif
