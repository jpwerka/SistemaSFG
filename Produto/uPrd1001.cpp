/*
Módulo: Produtos
Função: Cadastro Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uPrd1001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd1001(void) {
   AddAppForm("Prd1001","Produtos",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd1001",__classid(TPrd1001));
}
#pragma startup RegisterPrd1001
//---------------------------------------------------------------------------
__fastcall TPrd1001::TPrd1001(TComponent* Owner)
   : TfrmBase02(Owner)
{
  TipoProduto = new TStringList();
  pgDetItem->ActivePageIndex = 0;
  CarregarTipoProduto();
  CarregarOrigemMercadoria();
  SfgToolbar->DataSource = DsProduto;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
  SfgToolbar->BeforeFilterEdit = &BeforeFilterEdit;
  SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
}
//---------------------------------------------------------------------------
__fastcall TPrd1001::~TPrd1001() {
   SfgComboObject *ComboObject;
   for(int i = 0; i < TipoProduto->Count; i++) {
      ComboObject = (SfgComboObject*)TipoProduto->Objects[i];
      delete ComboObject;
   }
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::ValidInsert(bool &bValid)
{
	if (!VerificaCampos()) {
      bValid = false;
      return;
	}
	if (!ValidaCampos()) {
      bValid = false;
      return;
   }
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::ValidUpdate(bool &bValid)
{
	if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_fornecedor_produto" \
			" WHERE cod_produto = " + QuotedStr(cod_produto->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Produto já relacionado a um fornecedor. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1001::VerificaCampos()
{
	if(!cod_produto->Text.Length()) {
		MessageBox(Handle, "Digite o código do produto!",Caption.c_str(),APP_ATENTION);
		cod_familia->SetFocus();
		return false;
	}
	if(!den_produto->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do produto!",Caption.c_str(),APP_ATENTION);
		den_produto->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1001::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_produto FROM tbl_produto" \
			" WHERE cod_produto = " + QuotedStr(cod_produto->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Produto já cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_produto->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::CarregarTipoProduto()
{
   TipoProduto->Clear();
   TipoProduto->AddObject("Produto",(TObject*)new SfgComboObject(Variant("P")));
   TipoProduto->AddObject("Serviço",(TObject*)new SfgComboObject(Variant("S")));
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::CarregarOrigemMercadoria()
{
   origem_mercadoria->Clear();
   origem_mercadoria->AddItem("Nacional, exceto as indicadas nos códigos 3 a 5",Variant(0));
   origem_mercadoria->AddItem("Estrangeira - Importação direta, exceto a indicada no código 6",Variant(1));
   origem_mercadoria->AddItem("Estrangeira - Adquirida no mercado interno, exceto a indicada no código 7",Variant(2));
   origem_mercadoria->AddItem("Nacional, mercadoria ou bem com Conteúdo de Importação superior a 40%",Variant(3));
   //origem_mercadoria->AddItem("Nacional, cuja produção tenha sido feita em conformidade com os processos produtivos básicos de que tratam as legislações citadas nos Ajustes",Variant(4));
   origem_mercadoria->AddItem("Nacional, produção feita em conformidade com processos das legislações citadas nos Ajustes",Variant(4));
   origem_mercadoria->AddItem("Nacional, mercadoria ou bem com Conteúdo de Importação inferior ou igual a 40%",Variant(5));
   origem_mercadoria->AddItem("Estrangeira - Importação direta, sem similar nacional, constante em lista da CAMEX",Variant(6));
   origem_mercadoria->AddItem("Estrangeira - Adquirida no mercado interno, sem similar nacional, constante em lista da CAMEX",Variant(7));
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::BeforeFilterEdit(SfgFilter *Filter, SfgMfEdit &EditCmp)
{
   if ((Filter->Field->FieldName == "cod_familia") ||
       (Filter->Field->FieldName == "cod_unid_medida") ||
       (Filter->Field->FieldName == "ies_tipo_produto") ||
       (Filter->Field->FieldName == "origem_mercadoria")) {
      EditCmp = smeComboBox;
   }
}
//---------------------------------------------------------------------------
void __fastcall TPrd1001::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "cod_familia") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_familia->Items);
   } else
   if (Filter->Field->FieldName == "cod_unid_medida") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_unid_medida->Items);
   } else
   if (Filter->Field->FieldName == "ies_tipo_produto") {
      ComboBox->Clear();
      ComboBox->Items->AddStrings(TipoProduto);
   } else
   if (Filter->Field->FieldName == "origem_mercadoria") {
      ComboBox->Clear();
      ComboBox->Items->Assign(origem_mercadoria->Items);
   }
}
//---------------------------------------------------------------------------









