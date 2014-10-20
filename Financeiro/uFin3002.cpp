/*
Módulo: Financeiro
Função: Consulta Contas à Pagar (Filtros)
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
#include "uSfgBrowseSup.h"
#include "uSfgBrowseFin.h"
#include "uFin3003.h"
#include "uFin3004.h"
#include "uFin3006.h"
#include "uFin3005.h"
#pragma hdrstop
#include "uFin3002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin3002(void) {
   AddAppForm("Fin3002","Consulta Contas à Pagar",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin3002",__classid(TFin3002));
}
#pragma startup RegisterFin3002
//---------------------------------------------------------------------------
__fastcall TFin3002::TFin3002(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_fornecedor->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_fornecedor") {
		cod_fornecedorExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::data_iniExit(TObject *Sender)
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
void __fastcall TFin3002::data_fimExit(TObject *Sender)
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
void __fastcall TFin3002::cod_fornecedorExit(TObject *Sender)
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
void __fastcall TFin3002::btPesqFornecedorClick(TObject *Sender)
{
	pEditRet = cod_fornecedor;
	SfgBrowse::EscolheFornecedor(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btPesqPlanoContaIniClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_ini;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btPesqPlanoContaFimClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_fim;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btPesqCentroCustoIniClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_ini;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btPesqCentroCustoFimClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_fim;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = "SELECT * FROM cns_conta_pagar WHERE 1=1";
	if (cod_fornecedor->Text.Length()) {
		SQL += " AND cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
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
			SQL += " ORDER BY cod_fornecedor, cod_conta_pagar";
			ConsultaPorFornecedor(SQL,dt_data_ini, dt_data_fim);
			break;
		case 1:
			SQL += " ORDER BY ord_situacao, cod_conta_pagar";
			ConsultaPorSitacao(SQL,dt_data_ini, dt_data_fim);
			break;
		case 2:
			SQL += " ORDER BY cod_plano_conta, cod_conta_pagar";
			ConsultaPorContaContabil(SQL,dt_data_ini, dt_data_fim);
			break;
		case 3:
			SQL += " ORDER BY cod_centro_custo, cod_conta_pagar";
			ConsultaPorCentroCusto(SQL,dt_data_ini, dt_data_fim);
			break;
		default:
			SQL += " ORDER BY cod_fornecedor, cod_conta_pagar";
			ConsultaPorFornecedor(SQL,dt_data_ini, dt_data_fim);
	}
	//Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::ConsultaPorFornecedor(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3003 *Fin3003;
	Fin3003 = new TFin3003(Application);
	Fin3003->QyForContaPagar->Close();
	Fin3003->QyForContaPagar->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3003->QyForContaPagar->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3003->QyForContaPagar->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3003->QyForContaPagar->Active = true;
   if(Fin3003->RpRelatBase->PrepareReport(true))
      Fin3003->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::ConsultaPorSitacao(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3004 *Fin3004;
	Fin3004 = new TFin3004(Application);
	Fin3004->QySitContaPagar->Close();
	Fin3004->QySitContaPagar->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3004->QySitContaPagar->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3004->QySitContaPagar->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3004->QySitContaPagar->Active = true;
   if(Fin3004->RpRelatBase->PrepareReport(true))
      Fin3004->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::ConsultaPorContaContabil(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3005 *Fin3005;
	Fin3005 = new TFin3005(Application);
	Fin3005->QyCntContaPagar->Close();
	Fin3005->QyCntContaPagar->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3005->QyCntContaPagar->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3005->QyCntContaPagar->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3005->QyCntContaPagar->Active = true;
   if(Fin3005->RpRelatBase->PrepareReport(true))
      Fin3005->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TFin3002::ConsultaPorCentroCusto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TFin3006 *Fin3006;
	Fin3006 = new TFin3006(Application);
	Fin3006->QyCctContaPagar->Close();
	Fin3006->QyCctContaPagar->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Fin3006->QyCctContaPagar->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Fin3006->QyCctContaPagar->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Fin3006->QyCctContaPagar->Active = true;
   if(Fin3006->RpRelatBase->PrepareReport(true))
      Fin3006->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------


