/*
Módulo: Produtos
Função: Cadastro Unidades de Medida
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
#include "uPrd1003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd1003(void) {
   AddAppForm("Prd1003","Unidades de Medida",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd1003",__classid(TPrd1003));
}
#pragma startup RegisterPrd1003
//---------------------------------------------------------------------------
__fastcall TPrd1003::TPrd1003(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->DataSource = DsCadUnidMedida;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1003::ValidInsert(bool &bValid)
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
void __fastcall TPrd1003::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1003::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_produto" \
			" WHERE cod_unid_medida = " + QuotedStr(cod_unid_medida->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem produtos cadastrados para esta unidade de medida. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1003::VerificaCampos()
{
	if(!cod_unid_medida->Text.Length()) {
		MessageBox(Handle, "Digite o código da unidade de medida!",Caption.c_str(),APP_ATENTION);
		cod_unid_medida->SetFocus();
		return false;
	}
	if(!den_unid_medida->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da unidade de medida!",Caption.c_str(),APP_ATENTION);
		den_unid_medida->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1003::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_unid_medida FROM tbl_unid_medida" \
			" WHERE cod_unid_medida = " + QuotedStr(cod_unid_medida->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Unidade de medida já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_unid_medida->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
