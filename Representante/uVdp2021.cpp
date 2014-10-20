/*
Módulo: Vendas - Representantes
Função: Consulta Lista de Telefone dos Representantes
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uVdp3022.h"
#pragma hdrstop
#include "uVdp2021.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp2021(void) {
   AddAppForm("Vdp2021","Telefone dos Representantes",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp2021",__classid(TVdp2021));
}
#pragma startup RegisterVdp2021
//---------------------------------------------------------------------------
__fastcall TVdp2021::TVdp2021(TComponent* Owner)
        : TForm(Owner)
{
	String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::FormShow(TObject *Sender)
{
  QyFoneRepresentante->Active = true;
  TODOS->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::AClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'A*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::BClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'B*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::CClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'C*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::DClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'D*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::EClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'E*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::FClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'F*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::GClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'G*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::HClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'H*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::IClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'I*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::JClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'J*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::KClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'K*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::LClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'L*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::MClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'M*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::NClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'N*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::OClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'O*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::PClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'P*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::QClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'Q*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::RClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'R*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::SClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'S*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::TClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'T*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::UClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'U*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::VClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'V*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::WClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'W*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::XClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'X*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::YClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'Y*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::ZClick(TObject *Sender)
{
  QyFoneRepresentante->Filter = "den_representante LIKE 'Z*'";
  QyFoneRepresentante->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::TODOSClick(TObject *Sender)
{
  QyFoneRepresentante->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2021::BtRelatClick(TObject *Sender)
{
  TVdp3022 *Vdp3022 = new TVdp3022(Owner);
  if(QyFoneRepresentante->Filtered){
    Vdp3022->QyFoneRepresentante->Filter = QyFoneRepresentante->Filter;
    Vdp3022->QyFoneRepresentante->Filtered = true;
  }
   if(Vdp3022->RpRelatBase->PrepareReport(true))
      Vdp3022->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
