/*
Módulo: Compras - Fornecedor
Função: Consulta Lista de Telefones dos Fornecedores
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSup3020.h"
#pragma hdrstop
#include "uSup2020.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup2020(void) {
   AddAppForm("Sup2020","Telefones dos Fornecedores",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup2020",__classid(TSup2020));
}
#pragma startup RegisterSup2020
//---------------------------------------------------------------------------
__fastcall TSup2020::TSup2020(TComponent* Owner)
        : TForm(Owner)
{
	String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::FormShow(TObject *Sender)
{
  QyFoneFornec->Active = true;
  TODOS->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::AClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'A*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::BClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'B*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::CClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'C*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::DClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'D*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::EClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'E*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::FClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'F*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::GClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'G*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::HClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'H*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::IClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'I*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::JClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'J*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::KClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'K*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::LClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'L*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::MClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'M*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::NClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'N*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::OClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'O*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::PClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'P*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::QClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'Q*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::RClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'R*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::SClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'S*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::TClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'T*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::UClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'U*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::VClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'V*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::WClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'W*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::XClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'X*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::YClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'Y*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::ZClick(TObject *Sender)
{
  QyFoneFornec->Filter = "den_fornecedor LIKE 'Z*'";
  QyFoneFornec->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::TODOSClick(TObject *Sender)
{
  QyFoneFornec->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TSup2020::BtRelatClick(TObject *Sender)
{
  TSup3020 *Sup3020 = new TSup3020(Owner);
  if(QyFoneFornec->Filtered){
    Sup3020->QyFoneFornec->Filter = QyFoneFornec->Filter;
    Sup3020->QyFoneFornec->Filtered = true;
  }
   if(Sup3020->RpRelatBase->PrepareReport(true))
      Sup3020->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
