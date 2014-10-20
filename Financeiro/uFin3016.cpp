/*
Módulo: Financeiro
Função: Consulta Pagamento x Fornecedor (Filtros)
Autor.: Jackson Patrick Werka
Data..: 28/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgBrowseSup.h"
#include "uSfgBrowseFin.h"
#include "uFin3017.h"
#pragma hdrstop
#include "uFin3016.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin3016(void) {
   AddAppForm("Fin3016","Consulta Pagamento x Fornecedor",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin3016",__classid(TFin3016));
}
#pragma startup RegisterFin3016
//---------------------------------------------------------------------------
__fastcall TFin3016::TFin3016(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_fornecedor->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_fornecedor") {
		cod_fornecedorExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::data_iniExit(TObject *Sender)
{
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;

	if (data_ini->Text.Length()) {
		if (!Validacoes::IsDate(data_ini->EditText)) {
			data_ini->SetFocus();
			return;
		}
	} else {
		return;
	}
	if(data_fim->Text.Length() <= 0 ) {
		return;
	}
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
	} __finally {}
	if (dt_data_ini > dt_data_fim) {
		MessageBox(Handle, "A data inicial deve ser menor ou igual a data final!",Caption.c_str(),APP_ATENTION);
		data_ini->SetFocus();
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::data_fimExit(TObject *Sender)
{
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;

	if (data_fim->Text.Length()) {
		if (!Validacoes::IsDate(data_fim->EditText)) {
			data_fim->SetFocus();
			return;
		}
	} else {
		return;
	}
	if(data_ini->Text.Length() <= 0) {
		return;
	}
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
	} __finally {}
	if (dt_data_ini > dt_data_fim) {
		MessageBox(Handle, "A data final deve ser maior ou igual a data inicial!",Caption.c_str(),APP_ATENTION);
		data_fim->SetFocus();
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::cod_fornecedorExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_fornecedor->Text.Length() <= 0) {
		den_fornecedor->Text = "";
		return;
	}
	SQL = "SELECT den_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Fornecedor não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_fornecedor->SetFocus();
	} else {
		den_fornecedor->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::btPesqFornecedorClick(TObject *Sender)
{
	pEditRet = cod_fornecedor;
	SfgBrowse::EscolheFornecedor(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	dt_data_ini = dt_data_fim = 0;

	SQL = "\
SELECT tbl_fornecedor.cod_fornecedor, tbl_fornecedor.den_fornecedor,\
       pagto.cod_conta_pagar, pagto.seq_parcela, pagto.valor_parcela,\
       pagto.data_vencimento, pagto.data_pagamento, pagto.ies_pago,\
       pagto.valor_pago, pagto.valor_desconto, pagto.valor_acrescimo, pagto.valor_multa\
  FROM tbl_conta_pagar_pagto pagto\
 INNER JOIN tbl_conta_pagar conta\
    ON conta.cod_conta_pagar = pagto.cod_conta_pagar\
 INNER JOIN tbl_fornecedor\
    ON tbl_fornecedor.cod_fornecedor = conta.cod_fornecedor";

	if (cod_fornecedor->Text.Length()) {
		SQL += " AND conta.cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		SQL += " AND pagto.data_vencimento >= :data_ini";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		SQL += " AND pagto.data_vencimento <= :data_fim";
	} __finally {}
	}
	//Verifica se foram selecionadas todas as situações
   if (gbSituacao->ItemIndex == 1) { //Paga
      SQL += " AND pagto.ies_pago = 'S'";
   } else
   if (gbSituacao->ItemIndex == 2) { //Pendente
      SQL += " AND pagto.ies_pago = 'N'";
   } else
   if (gbSituacao->ItemIndex == 3) { //Em Atraso
      SQL += " AND pagto.ies_pago = 'N'";
      SQL += " AND pagto.data_vencimento < :data_atual";
   }
   SQL += "  ORDER BY tbl_fornecedor.cod_fornecedor, pagto.cod_conta_pagar, pagto.seq_parcela";
   ConsultaPorFornecedor(SQL,dt_data_ini,dt_data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3016::ConsultaPorFornecedor(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3017 *Fin3017 = new TFin3017(Application);
	Fin3017->QyPagtoFornecedor->Active = false;
	Fin3017->QyPagtoFornecedor->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3017->QyPagtoFornecedor->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3017->QyPagtoFornecedor->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
   if (gbSituacao->ItemIndex == 3) { //Em Atraso
		Fin3017->QyPagtoFornecedor->ParamByName("data_atual")->AsDateTime = Date();
	}
	Fin3017->QyPagtoFornecedor->Active = true;
   if(Fin3017->RpRelatBase->PrepareReport(true))
      Fin3017->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------



