//---------------------------------------------------------------------------
#ifndef uMainH
#define uMainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ExtCtrls.hpp>
#include <ActnList.hpp>
#include <StdActns.hpp>
#include "uFrmLogin.h"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "ThemeMgrDB.hpp"
//---------------------------------------------------------------------------
class SfgMenuExec;
class TFrmMain : public TForm
{
private:
	friend class TFrmLogin;
__published:	// IDE-managed Components
   TImageList *ImageMenu;
	TBevel *Bevel1;
   TActionList *ActionMenu;
   TWindowCascade *wndCascata;
   TWindowClose *wndClose;
   TWindowTileHorizontal *wndTileHorz;
   TWindowTileVertical *wndTileVert;
   TWindowMinimizeAll *wndMinimize;
   TZReadOnlyQuery *CnsMenu;
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormPaint(TObject *Sender);
	void __fastcall execMenuExecute(TObject *Sender);
	void __fastcall execMenuSobre(TObject *Sender);
private:	// User declarations
   bool bCreateAtuDB;
   TThemeManagerDB *ThemeManagerDB;
	bool __fastcall TerminarForms();
	void __fastcall CarregarImages();
	void __fastcall CarregarReports();
	void __fastcall CarregarServerSMTP();
   void __fastcall CarregaMenu(TMenu *pMenu, TMenuItem *pParentItem, bool &bMenu);
   TForm* __fastcall CreateForm(SfgMenuExec *MenuExec, String sTitle);
   long __fastcall CreateFormEx(LPARAM lParam);
   void __fastcall AppEventsMessage(tagMSG &Msg, bool &Handled);
   void __fastcall SubClassWndProc(Messages::TMessage &Message);
	void __fastcall HackFormClose(TObject *Sender, TCloseAction &Action);
   bool __fastcall ValidSchemaDB();
public:		// User declarations
   TFrmLogin *FrmLogin;
	__fastcall TFrmMain(TComponent* Owner);
	__fastcall TFrmMain(TComponent* Owner, SfgArgs *AppArgs);
	__fastcall ~TFrmMain();
	bool __fastcall FormIsLoadActive(String sFormName);
	void __fastcall ActiveForm(TForm* pForm);
   void __fastcall CriarMenu();
   void __fastcall LoadSfgModulos();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmMain *FrmMain;
TForm* SfgAppCreatePreview();
//---------------------------------------------------------------------------
#endif
