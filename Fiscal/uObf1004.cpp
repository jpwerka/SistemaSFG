//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uObf1004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TObf1004::TObf1004(TComponent* Owner)
   : TForm(Owner)
{
   QyEmpresa->Active = true;
   if (AppUser->CodEmpresa.Length() > 0) {
      QyEmpresa->Locate("cod_empresa",AppUser->CodEmpresa,TLocateOptions());
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1004::btOKClick(TObject *Sender)
{
   AppUser->CodEmpresa = QyEmpresa->FieldByName("cod_empresa")->AsString;
   this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
