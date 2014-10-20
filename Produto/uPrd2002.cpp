/*
Módulo: Produtos
Função: Consulta Lista de Produtos x Familia
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
#include "uPrd3002.h"
#pragma hdrstop
#include "uPrd2002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd2002(void) {
   AddAppForm("Prd2002","Lista de Produtos x Família",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd2002",__classid(TPrd2002));
}
#pragma startup RegisterPrd2002
//---------------------------------------------------------------------------
__fastcall TPrd2002::TPrd2002(TComponent* Owner)
	: TForm(Owner)
{
   String clsName;
	clsName = this->ClassName();
	clsName = clsName.SubString(2,clsName.Length());
	Caption = UpperCase(clsName) + " - " + this->Caption;
   TbCnsProduto->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::FormClose(TObject *Sender, TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::AClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'A*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::BClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'B*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::CClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'C*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::DClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'D*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::EClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'E*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::FClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'F*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::GClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'G*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::HClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'H*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::IClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'I*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::JClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'J*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::KClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'K*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::LClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'L*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::MClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'M*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::NClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'N*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::OClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'O*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::PClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'P*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::QClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'Q*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::RClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'R*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::SClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'S*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::TClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'T*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::UClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'U*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::VClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'V*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::WClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'W*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::XClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'X*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::YClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'Y*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::ZClick(TObject *Sender)
{
  TbCnsProduto->Filter = "den_familia LIKE 'Z*'";
  TbCnsProduto->Filtered = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::TODOSClick(TObject *Sender)
{
  TbCnsProduto->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::BtRelatClick(TObject *Sender)
{
  TPrd3002 *Prd3002 = new TPrd3002(Owner);
  if(TbCnsProduto->Filtered){
	 Prd3002->TbCnsProduto->Filter = TbCnsProduto->Filter;
	 Prd3002->TbCnsProduto->Filtered = true;
  }
  if (Prd3002->RpRelatBase->PrepareReport(true))
     Prd3002->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TPrd2002::grdCnsProdutoDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_ativo") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdCnsProduto,-1,-1,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------

