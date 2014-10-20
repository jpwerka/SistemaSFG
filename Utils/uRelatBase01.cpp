//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "frxPreview.hpp"
#include "uSfgDinForms.hpp"
#pragma hdrstop
#include "uRelatBase01.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmRelatBase01::TfrmRelatBase01(TComponent* Owner)
        : TForm(Owner)
{
   TfrxPictureView *Logotipo;
   TfrxMemoView *Memo;
   TfrxPageFooter *RodPagina;
	double height;
   String rptTitle;

   Logotipo = dynamic_cast<TfrxPictureView*>(RpRelatBase->FindObject("Logotipo"));
   if (Logotipo) {
   try {
   if (AppConfig->Images->Logotipo != NULL) {
      if (AppConfig->Images->Logotipo->Picture != NULL) {
         if (AppConfig->Images->Logotipo->Picture->Graphic != NULL) {
            Logotipo->Picture->Assign(AppConfig->Images->Logotipo->Picture);
         } else if (AppConfig->Images->Logotipo->Picture->Bitmap != NULL) {
            Logotipo->Picture->Assign(AppConfig->Images->Logotipo->Picture);
         }
      }
   }
   } __finally {}
   }
   Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("CabLivre01"));
	if (AppConfig->Reports->CabLivre01.Length() > 0) {
      Memo->Memo->Text = AppConfig->Reports->CabLivre01;
	} else {
		Memo->Memo->Text = "";
	}
   Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("CabLivre02"));
	if (AppConfig->Reports->CabLivre02.Length() > 0) {
		Memo->Memo->Text = AppConfig->Reports->CabLivre02;
	} else {
		Memo->Memo->Text = "";
	}
   Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("CabLivre03"));
	if (AppConfig->Reports->CabLivre03.Length() > 0) {
		Memo->Memo->Text = AppConfig->Reports->CabLivre03;
	} else {
		Memo->Memo->Text = "";
	}
   RodPagina = dynamic_cast<TfrxPageFooter*>(RpRelatBase->FindObject("RodPagina"));
	height = RodPagina->Height;
   Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("Cidade"));
	Memo->Memo->Text = AppConfig->Reports->RodCidade;
	if (AppConfig->Reports->RodLivre01.Length() > 0) {
      Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("RodLivre01"));
		Memo->Memo->Text = AppConfig->Reports->RodLivre01;
      Memo->Visible = true;
		RodPagina->Height += height;
		Memo->Top = (RodPagina->Height - height);
	}
	if (AppConfig->Reports->RodLivre02.Length() > 0) {
      Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("RodLivre02"));
		Memo->Memo->Text = AppConfig->Reports->RodLivre02;
      Memo->Visible = true;
		RodPagina->Height += height;
		Memo->Top = (RodPagina->Height - height);
	}
   Memo = dynamic_cast<TfrxMemoView*>(RpRelatBase->FindObject("Titulo"));
   rptTitle = Memo->Text;
   rptTitle = rptTitle.SubString(1,rptTitle.Length()-2);
   RpRelatBase->ReportOptions->Name = rptTitle;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRelatBase01::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmRelatBase01::RpRelatBaseBeginDoc(TObject *Sender)
{
   String clsName;
   TfrxReport *pRelatBase = (TfrxReport*)RpRelatBase;
   clsName = pRelatBase->Owner->ClassName();
   clsName = clsName.SubString(2,clsName.Length());

   //TSfgPreview *SfgPreview; // = new TSfgPreview(Application);
   TForm *pForm;
   if (AppCreatePreview != NULL) {
      pForm = AppCreatePreview();
   } else {
   //SfgCreateForm(Application, __classid(TSfgPreview), &pForm);
      SfgCreateForm(Application, PreviewReportClass, &pForm);
   }
   //Application->CreateForm(PreviewReportClass, &pForm);
   pRelatBase->Preview = (TfrxPreview*)pForm->FindComponent("PrewRelat");
   pForm->Caption = UpperCase(clsName);
   pForm->Show();
}
//---------------------------------------------------------------------------



