/*
Módulo: Financeiro
Função: Consulta Contas à Receber (Filtros)
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
#include "uSfgBrowseFin.h"
#include "uFin3008.h"
#include "uFin3009.h"
#include "uFin3011.h"
#include "uFin3010.h"
#pragma hdrstop
#include "uFin3007.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin3007(void) {
   AddAppForm("Fin3007","Consulta Contas à Receber",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin3007",__classid(TFin3007));
}
#pragma startup RegisterFin3007
//---------------------------------------------------------------------------
__fastcall TFin3007::TFin3007(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_cliente->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::data_iniExit(TObject *Sender)
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
void __fastcall TFin3007::data_fimExit(TObject *Sender)
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
void __fastcall TFin3007::cod_clienteExit(TObject *Sender)
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
void __fastcall TFin3007::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btPesqPlanoContaIniClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_ini;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btPesqPlanoContaFimClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_fim;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btPesqCentroCustoIniClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_ini;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btPesqCentroCustoFimClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_fim;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = "SELECT * FROM cns_conta_receber WHERE 1=1";
	if (cod_cliente->Text.Length()) {
		SQL += " AND cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if (cod_plano_conta_ini->Text.Length()) {
		SQL += " AND cod_plano_conta >= " + QuotedStr(cod_plano_conta_ini->Text);
	}
	if (cod_plano_conta_fim->Text.Length()) {
		SQL += " AND cod_plano_conta <= " + QuotedStr(cod_plano_conta_fim->Text);
	}
	if (cod_centro_custo_ini->Text.Length()) {
		SQL += " AND cod_centro_custo >= " + QuotedStr(cod_centro_custo_ini->Text);
	}
	if (cod_centro_custo_fim->Text.Length()) {
		SQL += " AND cod_centro_custo <= " + QuotedStr(cod_centro_custo_fim->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		SQL += " AND data_cadastro >= :data_ini";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		SQL += " AND data_cadastro <= :data_fim";
	} __finally {}
	}
	//Verifica se foram selecionadas todas as situações
	if (!(ckPendente->Checked &&
			ckAndamento->Checked &&
			ckLiquidado->Checked &&
			ckCancelado->Checked)) {
		str_situacao = "";
		//Faz uma junção de cada situação.
		if (ckPendente->Checked)
			str_situacao += (str_situacao.Length())? ",'P'":"'P'";
		if (ckAndamento->Checked)
			str_situacao += (str_situacao.Length())? ",'A'":"'A'";
		if (ckLiquidado->Checked)
			str_situacao += (str_situacao.Length())? ",'L'":"'L'";
		if (ckCancelado->Checked)
			str_situacao += (str_situacao.Length())? ",'C'":"'C'";
		SQL += " AND ies_situacao IN (" + str_situacao + ")";
	}
	switch (rbAgrupamento->ItemIndex) {
		case 0:
			SQL += " ORDER BY cod_cliente, cod_conta_receber";
			ConsultaPorCliente(SQL,dt_data_ini, dt_data_fim);
			break;
		case 1:
			SQL += " ORDER BY ord_situacao, cod_conta_receber";
			ConsultaPorSitacao(SQL,dt_data_ini, dt_data_fim);
			break;
		case 2:
			SQL += " ORDER BY cod_plano_conta, cod_conta_receber";
			ConsultaPorContaContabil(SQL,dt_data_ini, dt_data_fim);
			break;
		case 3:
			SQL += " ORDER BY cod_centro_custo, cod_conta_receber";
			ConsultaPorCentroCusto(SQL,dt_data_ini, dt_data_fim);
			break;
		default:
			SQL += " ORDER BY cod_cliente, cod_conta_receber";
			ConsultaPorCliente(SQL,dt_data_ini, dt_data_fim);
	}
	//Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::ConsultaPorCliente(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3008 *Fin3008;
	Fin3008 = new TFin3008(Application);
	Fin3008->QyForContaReceber->Close();
	Fin3008->QyForContaReceber->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3008->QyForContaReceber->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3008->QyForContaReceber->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3008->QyForContaReceber->Active = true;
   if(Fin3008->RpRelatBase->PrepareReport(true))
      Fin3008->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::ConsultaPorSitacao(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3009 *Fin3009;
	Fin3009 = new TFin3009(Application);
	Fin3009->QySitContaReceber->Close();
	Fin3009->QySitContaReceber->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3009->QySitContaReceber->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3009->QySitContaReceber->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3009->QySitContaReceber->Active = true;
   if(Fin3009->RpRelatBase->PrepareReport(true))
      Fin3009->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::ConsultaPorContaContabil(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3010 *Fin3010;
	Fin3010 = new TFin3010(Application);
	Fin3010->QyCntContaReceber->Close();
	Fin3010->QyCntContaReceber->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3010->QyCntContaReceber->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3010->QyCntContaReceber->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3010->QyCntContaReceber->Active = true;
   if(Fin3010->RpRelatBase->PrepareReport(true))
      Fin3010->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3007::ConsultaPorCentroCusto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3011 *Fin3011;
	Fin3011 = new TFin3011(Application);
	Fin3011->QyCctContaReceber->Close();
	Fin3011->QyCctContaReceber->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3011->QyCctContaReceber->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3011->QyCctContaReceber->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3011->QyCctContaReceber->Active = true;
   if(Fin3011->RpRelatBase->PrepareReport(true))
      Fin3011->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------


