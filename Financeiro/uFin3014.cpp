/*
Módulo: Financeiro
Função: Consulta Recebimento x Cliente (Filtros)
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
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uFin3015.h"
#pragma hdrstop
#include "uFin3014.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin3014(void) {
   AddAppForm("Fin3014","Consulta Recebimento x Cliente",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin3014",__classid(TFin3014));
}
#pragma startup RegisterFin3014
//---------------------------------------------------------------------------
__fastcall TFin3014::TFin3014(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_cliente->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::data_iniExit(TObject *Sender)
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
void __fastcall TFin3014::data_fimExit(TObject *Sender)
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
void __fastcall TFin3014::cod_clienteExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_cliente->Text.Length() <= 0) {
		den_cliente->Text = "";
		return;
	}
	SQL = "SELECT den_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(cod_cliente->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Cliente não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
	} else {
		den_cliente->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	dt_data_ini = dt_data_fim = 0;

	SQL = "\
SELECT tbl_cliente.cod_cliente, tbl_cliente.den_cliente,\
       pagto.cod_conta_receber, pagto.seq_parcela, pagto.valor_parcela,\
       pagto.data_vencimento, pagto.data_recebimento, pagto.ies_recebido,\
       pagto.valor_recebido, pagto.valor_desconto, pagto.valor_acrescimo, pagto.valor_multa\
  FROM tbl_conta_receber_pagto pagto\
 INNER JOIN tbl_conta_receber conta\
    ON conta.cod_conta_receber = pagto.cod_conta_receber\
 INNER JOIN tbl_cliente\
    ON tbl_cliente.cod_cliente = conta.cod_cliente";

	if (cod_cliente->Text.Length()) {
		SQL += " AND conta.cod_cliente = " + QuotedStr(cod_cliente->Text);
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
   if (gbSituacao->ItemIndex == 1) { //Recebida
      SQL += " AND pagto.ies_recebido = 'S'";
   } else
   if (gbSituacao->ItemIndex == 2) { //Pendente
      SQL += " AND pagto.ies_recebido = 'N'";
   } else
   if (gbSituacao->ItemIndex == 3) { //Em Atraso
      SQL += " AND pagto.ies_recebido = 'N'";
      SQL += " AND pagto.data_vencimento < :data_atual";
   }
   SQL += "  ORDER BY tbl_cliente.cod_cliente, pagto.cod_conta_receber, pagto.seq_parcela";
   ConsultaPorCliente(SQL,dt_data_ini,dt_data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3014::ConsultaPorCliente(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3015 *Fin3015 = new TFin3015(Application);
	Fin3015->QyRecebtoCliente->Active = false;
	Fin3015->QyRecebtoCliente->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3015->QyRecebtoCliente->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3015->QyRecebtoCliente->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
   if (gbSituacao->ItemIndex == 3) { //Em Atraso
		Fin3015->QyRecebtoCliente->ParamByName("data_atual")->AsDateTime = Date();
	}
	Fin3015->QyRecebtoCliente->Active = true;
   if(Fin3015->RpRelatBase->PrepareReport(true))
      Fin3015->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------



