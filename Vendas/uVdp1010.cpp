/*
Módulo: Vendas
Função: Cadastro Formas de Pagamento
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgVdpCustom.h"
#pragma hdrstop
#include "uVdp1010.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1010(void) {
   AddAppForm("Vdp1010","Formas de Pagamento",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1010",__classid(TVdp1010));
}
#pragma startup RegisterVdp1010
//---------------------------------------------------------------------------
__fastcall TVdp1010::TVdp1010(TComponent* Owner)
	: TfrmBase02(Owner)
{
  SfgToolbar->DataSource = DsCadFormaPagto;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   if(hSfgVdpCustom) {
      SfgVdp1010AfterCreate = (PSfgVdp1010AfterCreate)GetProcAddress(hSfgVdpCustom,"SfgVdp1010AfterCreate");
      if (SfgVdp1010AfterCreate)
         SfgVdp1010AfterCreate(this);
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1010::ValidInsert(bool &bValid)
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
void __fastcall TVdp1010::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1010::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_pedido_venda" \
			" WHERE cod_forma_pagto = " + cod_forma_pagto->Text;
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Forma de pagamento já utilizada no cadastro de orçamentos. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_pagar" \
			" WHERE cod_forma_pagto = " + cod_forma_pagto->Text;
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Forma de pagamento já utilizada no cadastro de contas à pagar. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_receber" \
			" WHERE cod_forma_pagto = " + cod_forma_pagto->Text;
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Forma de pagamento já utilizada no cadastro de contas à receber. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1010::VerificaCampos()
{
	if(!cod_forma_pagto->Text.Length()) {
		MessageBox(Handle, "Digite o código da forma de pagamento!",Caption.c_str(),APP_ATENTION);
		cod_forma_pagto->SetFocus();
		return false;
	}
	if(!den_forma_pagto->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da forma de pagamento!",Caption.c_str(),APP_ATENTION);
		den_forma_pagto->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1010::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_forma_pagto FROM tbl_forma_pagto" \
			" WHERE cod_forma_pagto = " + cod_forma_pagto->Text;
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Forma de pagamento já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_forma_pagto->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------

