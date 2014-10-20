/*
Módulo: Financeiro
Função: Cadastro Centro de Custo
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
#include "uFin1006.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1006(void) {
   AddAppForm("Fin1006","Centros de Custo",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1006",__classid(TFin1006));
}
#pragma startup RegisterFin1006
//---------------------------------------------------------------------------
__fastcall TFin1006::TFin1006(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->DataSource = DsCentroCusto;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TFin1006::ValidInsert(bool &bValid)
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
void __fastcall TFin1006::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1006::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_pagar" \
			" WHERE cod_centro_custo = " + QuotedStr(cod_centro_custo->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem contas à pagar cadastradas para estes centro de custo. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_receber" \
			" WHERE cod_centro_custo = " + QuotedStr(cod_centro_custo->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem contas à receber cadastradas para estes centro de custo. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TFin1006::VerificaCampos()
{
	if(!cod_centro_custo->Text.Length()) {
		MessageBox(Handle, "Digite o código do centro de custo!",Caption.c_str(),APP_ATENTION);
		cod_centro_custo->SetFocus();
		return false;
	}
	if(!den_centro_custo->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do centro de custo!",Caption.c_str(),APP_ATENTION);
		den_centro_custo->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFin1006::ValidaCampos()
{
	String sSQL;
	sSQL = "SELECT cod_centro_custo FROM tbl_centro_custo" \
			" WHERE cod_centro_custo = " + QuotedStr(cod_centro_custo->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		MessageBox(Handle, "Centro de custo já cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_centro_custo->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------

