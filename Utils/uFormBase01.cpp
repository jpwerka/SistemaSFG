//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#pragma hdrstop
#include "uFormBase01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFormBase01(void) {
   FormBaseClass = __classid(TfrmBase01);
}
#pragma startup RegisterFormBase01
//---------------------------------------------------------------------------
__fastcall TfrmBase01::TfrmBase01(TComponent* Owner)
	: TForm(Owner)
{
	Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
	Tolltips->CreateToolTips();
   AssignImage(AppConfig->Images->Logotipo,Logotipo);
	String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
	AppDummyMethod = &DummyMethod;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBase01::DummyMethod(void *pVoid)
{
   int iNivel = *(int*)pVoid;
   SetPermissao(iNivel);
}

//---------------------------------------------------------------------------
void __fastcall TfrmBase01::FormDestroy(TObject *Sender)
{
	delete Tolltips;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBase01::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


