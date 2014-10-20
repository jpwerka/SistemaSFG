/*
Módulo: Produtos
Função: Consulta Lista de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgDrawCmp.h"
#include "uPrd3001.h"
#pragma hdrstop
#include "uPrd2001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd2001(void) {
   AddAppForm("Prd2001","Lista de Produtos",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd2001",__classid(TPrd2001));
}
#pragma startup RegisterPrd2001
//---------------------------------------------------------------------------
__fastcall TPrd2001::TPrd2001(TComponent* Owner)
        : TForm(Owner)
{
	String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
   TbCnsProduto->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::AClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'A*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::BClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'B*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::CClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'C*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::DClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'D*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::EClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'E*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::FClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'F*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::GClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'G*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::HClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'H*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::IClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'I*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::JClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'J*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::KClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'K*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::LClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'L*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::MClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'M*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::NClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'N*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::OClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'O*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::PClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'P*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::QClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'Q*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::RClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'R*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::SClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'S*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::TClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'T*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::UClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'U*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::VClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'V*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::WClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'W*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::XClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'X*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::YClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'Y*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::ZClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_produto LIKE 'Z*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::TODOSClick(TObject *Sender)
{
  TbCnsProduto->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::BtRelatClick(TObject *Sender)
{
  TPrd3001 *Prd3001 = new TPrd3001(Owner);
  if(TbCnsProduto->Filtered){
	 Prd3001->TbCnsProduto->Filter = TbCnsProduto->Filter;
    Prd3001->TbCnsProduto->Filtered = true;
  }
  if(Prd3001->RpRelatBase->PrepareReport(true))
     Prd3001->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TPrd2001::grdCnsProdutoDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_ativo") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdCnsProduto,-1,-1,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------

