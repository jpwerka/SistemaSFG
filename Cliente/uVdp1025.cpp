/*
Módulo: Vendas - Clientes
Função: Cadastro Classificação Cliente
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
#include "uVdp1025.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1025(void) {
   AddAppForm("Vdp1025","Classificação Cliente",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1025",__classid(TVdp1025));
}
#pragma startup RegisterVdp1025
//---------------------------------------------------------------------------
__fastcall TVdp1025::TVdp1025(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->AfterCreateFields = &AfterCreateFields;
  SfgToolbar->DataSource = DsClassCliente;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1025::AfterCreateFields(TDataSet *DataSet)
{
   //Marcando campo como auto incremento
   QyClassCliente->FieldByName("cod_classificacao")->AutoGenerateValue = arAutoInc;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1025::ValidInsert(bool &bValid)
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
void __fastcall TVdp1025::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1025::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_cliente" \
			" WHERE cod_classificacao = " + QuotedStr(cod_classificacao->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem clientes cadastrados para esta classificação. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1025::VerificaCampos()
{
	if(!den_classificacao->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da classificação!",Caption.c_str(),APP_ATENTION);
		den_classificacao->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1025::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
