/*
Módulo: Produtos
Função: Cadastro Famílias
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
#include "uPrd1002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd1002(void) {
   AddAppForm("Prd1002","Famílias",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd1002",__classid(TPrd1002));
}
#pragma startup RegisterPrd1002
//---------------------------------------------------------------------------
__fastcall TPrd1002::TPrd1002(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->DataSource = DsCadFamilia;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1002::ValidInsert(bool &bValid)
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
void __fastcall TPrd1002::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1002::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_produto" \
			" WHERE cod_familia = " + cod_familia->Text;
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem produtos cadastrados para esta família. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1002::VerificaCampos()
{
	if(!cod_familia->Text.Length() || (long)cod_familia->Field->Value <= 0) {
		MessageBox(Handle, "Digite o código da familia!",Caption.c_str(),APP_ATENTION);
		cod_familia->SetFocus();
		return false;
	}
	if(!den_familia->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da família!",Caption.c_str(),APP_ATENTION);
		den_familia->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TPrd1002::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_familia FROM tbl_familia" \
			" WHERE cod_familia = " + cod_familia->Text;
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Família já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_familia->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------

