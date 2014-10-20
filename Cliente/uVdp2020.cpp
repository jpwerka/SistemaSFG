/*
Módulo: Vendas - Clientes
Função: Consulta Lista de Telefone dos Clientes
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uVdp3020.h"
#pragma hdrstop
#include "uVdp2020.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp2020(void) {
   AddAppForm("Vdp2020","Telefone dos Clientes",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp2020",__classid(TVdp2020));
}
#pragma startup RegisterVdp2020
//---------------------------------------------------------------------------
__fastcall TVdp2020::TVdp2020(TComponent* Owner)
        : TForm(Owner)
{
	String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::FormShow(TObject *Sender)
{
  QyFoneCliente->Active = true;
  TODOS->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::AClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'A*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::BClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'B*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::CClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'C*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::DClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'D*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::EClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'E*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::FClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'F*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::GClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'G*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::HClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'H*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::IClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'I*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::JClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'J*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::KClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'K*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::LClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'L*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::MClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'M*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::NClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'N*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::OClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'O*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::PClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'P*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::QClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'Q*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::RClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'R*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::SClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'S*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::TClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'T*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::UClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'U*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::VClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'V*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::WClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'W*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::XClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'X*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::YClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'Y*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::ZClick(TObject *Sender)
{
  QyFoneCliente->Filter = "den_cliente LIKE 'Z*'";
  QyFoneCliente->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::TODOSClick(TObject *Sender)
{
  QyFoneCliente->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2020::BtRelatClick(TObject *Sender)
{
  TVdp3020 *Vdp3020 = new TVdp3020(Owner);
  if(QyFoneCliente->Filtered){
    Vdp3020->QyFoneCliente->Filter = QyFoneCliente->Filter;
    Vdp3020->QyFoneCliente->Filtered = true;
  }
   if(Vdp3020->RpRelatBase->PrepareReport(true))
      Vdp3020->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
