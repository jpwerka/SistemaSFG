/*
Módulo: Vendas
Função: Consulta Amostragem por Representante (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgBrowseVdp.h"
#include "uCVdp3100.h"
#pragma hdrstop
#include "uCVdp3101.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "uSfgBrowseVdp"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterCVdp3101(void) {
   AddAppForm("CVdp3101","Amostragem x Representante",APP_MODULO_VENDAS);
   AddAppFormClass("TCVdp3101",__classid(TCVdp3101));
}
#pragma startup RegisterCVdp3101
//---------------------------------------------------------------------------
__fastcall TCVdp3101::TCVdp3101(TComponent* Owner)
	: TfrmBase01(Owner)
{
   den_representante->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_representante") {
		cod_representanteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::data_iniExit(TObject *Sender)
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
void __fastcall TCVdp3101::data_fimExit(TObject *Sender)
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
void __fastcall TCVdp3101::btPesqRepresentanteClick(TObject *Sender)
{
	pEditRet = cod_representante;
	SfgBrowse::EscolheRepresentante(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::cod_representanteExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_representante->Text.Length() <= 0) {
		den_representante->Text = "";
		return;
	}
	SQL = "SELECT den_representante FROM tbl_representante" \
			" WHERE cod_representante = " + QuotedStr(cod_representante->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Representante não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_representante->SetFocus();
	} else {
		den_representante->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::btRelatorioClick(TObject *Sender)
{
	String sSQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	sSQL = "\
SELECT r.cod_representante, r.den_representante,\
       v.cod_pedido_venda, v.data_cadastro,\
       v.ies_situacao, v.valor_total\
  FROM tbl_pedido_venda v,\
       tbl_representante r\
 WHERE v.cod_cliente = r.cod_representante\
   AND v.cod_forma_pagto = " + VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_numero('forma_pagto_sem_finc');"));

	if (cod_representante->Text.Length()) {
		sSQL += " AND r.cod_representante = " + QuotedStr(cod_representante->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		sSQL += " AND v.data_cadastro >= :data_ini";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		sSQL += " AND v.data_cadastro <= :data_fim";
	} __finally {}
	}
	//Verifica se foram selecionadas todas as situações
	if (!(ckAberto->Checked &&
			ckFechado->Checked &&
			ckCancelado->Checked)) {
		str_situacao = "";
		//Faz uma junção de cada situação.
		if (ckAberto->Checked)
			str_situacao += (str_situacao.Length())? ",'A'":"'A'";
		if (ckFechado->Checked)
			str_situacao += (str_situacao.Length())? ",'F'":"'F'";
		if (ckCancelado->Checked)
			str_situacao += (str_situacao.Length())? ",'C'":"'C'";
		sSQL += " AND v.ies_situacao IN (" + str_situacao + ")";
	}
	sSQL += " ORDER BY r.cod_representante, v.cod_pedido_venda";
	ConsultaPorRepresentante(sSQL,dt_data_ini, dt_data_fim);
	//Close();
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TCVdp3101::ConsultaPorRepresentante(String sSQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TCVdp3100 *CVdp3100;
	CVdp3100 = new TCVdp3100(Application);
	CVdp3100->CnsPedidoVenda->Active = false;
	CVdp3100->CnsPedidoVenda->SQL->Text = sSQL;
	if ((int)dt_data_ini != 0) {
		CVdp3100->CnsPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		CVdp3100->CnsPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	CVdp3100->CnsPedidoVenda->Active = true;
   if(CVdp3100->RpRelatBase->PrepareReport(true))
      CVdp3100->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------

