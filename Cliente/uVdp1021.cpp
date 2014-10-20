/*
Módulo: Vendas - Clientes
Função: Cadastro Estados
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
#include "uVdp1021.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1021(void) {
   AddAppForm("Vdp1021","Estados",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1021",__classid(TVdp1021));
}
#pragma startup RegisterVdp1021
//---------------------------------------------------------------------------
__fastcall TVdp1021::TVdp1021(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->DataSource = DsCadEstado;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1021::ValidInsert(bool &bValid)
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
void __fastcall TVdp1021::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1021::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_cidade" \
			" WHERE cod_uf = " + QuotedStr(cod_uf->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem cidades cadastradas para este estado. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1021::VerificaCampos()
{
	if(!cod_uf->Text.Length()) {
		MessageBox(Handle, "Digite o código do estado!",Caption.c_str(),APP_ATENTION);
		cod_uf->SetFocus();
		return false;
	}
	if(!den_uf->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do estado!",Caption.c_str(),APP_ATENTION);
		den_uf->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1021::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_uf FROM tbl_uf" \
			" WHERE cod_uf = " + QuotedStr(cod_uf->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Estado já cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_uf->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
