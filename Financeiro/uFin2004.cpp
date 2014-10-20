/*
Módulo: Financeiro
Função: Análise de Contas à Receber (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uSfgToExcel.h"
#pragma hdrstop
#include "uFin2004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin2004(void) {
   AddAppForm("Fin2004","Análise de Contas à Receber",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin2004",__classid(TFin2004));
}
#pragma startup RegisterFin2004
//---------------------------------------------------------------------------
__fastcall TFin2004::TFin2004(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_cliente->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::data_iniExit(TObject *Sender)
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
void __fastcall TFin2004::data_fimExit(TObject *Sender)
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
void __fastcall TFin2004::cod_clienteExit(TObject *Sender)
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
void __fastcall TFin2004::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btPesqPlanoContaIniClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_ini;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btPesqPlanoContaFimClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_fim;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btPesqCentroCustoIniClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_ini;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btPesqCentroCustoFimClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_fim;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btProcessarClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = " WHERE 1=1";
	if (cod_cliente->Text.Length()) {
		SQL += " AND cr.cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if (cod_plano_conta_ini->Text.Length()) {
		SQL += " AND cr.cod_plano_conta >= " + QuotedStr(cod_plano_conta_ini->Text);
	}
	if (cod_plano_conta_fim->Text.Length()) {
		SQL += " AND cr.cod_plano_conta <= " + QuotedStr(cod_plano_conta_fim->Text);
	}
	if (cod_centro_custo_ini->Text.Length()) {
		SQL += " AND cr.cod_centro_custo >= " + QuotedStr(cod_centro_custo_ini->Text);
	}
	if (cod_centro_custo_fim->Text.Length()) {
		SQL += " AND cr.cod_centro_custo <= " + QuotedStr(cod_centro_custo_fim->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		DateTimeToString(str_data_ini,"yyyy-mm-dd hh:nn:ss",dt_data_ini);
		SQL += " AND (cr.data_cadastro >= {ts '"+str_data_ini+"'})";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		DateTimeToString(str_data_fim,"yyyy-mm-dd hh:nn:ss",dt_data_fim);
		SQL += " AND (cr.data_cadastro <= {ts '"+str_data_fim+"'})";
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
		SQL += " AND cr.ies_situacao IN (" + str_situacao + ")";
	}
	ExportToExcel(SQL);
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin2004::ExportToExcel(String Where)
{
   String SQL;
   TSfgAnaToExcel *pExcel = new TSfgAnaToExcel();
   SfgPivotFdPageList *PageFields = new SfgPivotFdPageList();
   SfgPivotFdRowList *RowFields = new SfgPivotFdRowList();
   SfgPivotFdDataList *DataFields = new SfgPivotFdDataList();

   SfgPivotFdPage *PageField = NULL;
   SfgPivotFdRow *RowField = NULL;
   SfgPivotFdData *DataField = NULL;

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"cod_cliente");
   wcscpy(PageField->Caption, L"Código Cliente");
   PageField->FieldType = ftString;
   PageFields->push_back(PageField);

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"den_cliente");
   wcscpy(PageField->Caption, L"Denominação Cliente");
   PageField->FieldType = ftString;
   PageFields->push_back(PageField);

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"ano");
   wcscpy(PageField->Caption, L"Ano");
   PageField->FieldType = ftInteger;
   PageFields->push_back(PageField);

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"mes");
   wcscpy(PageField->Caption, L"Mês");
   PageField->FieldType = ftInteger;
   PageFields->push_back(PageField);

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"cod_centro_custo");
   wcscpy(PageField->Caption, L"Centro Custo");
   PageField->FieldType = ftString;
   PageFields->push_back(PageField);

   PageField = new SfgPivotFdPage();
   wcscpy(PageField->FieldName, L"cod_plano_conta");
   wcscpy(PageField->Caption, L"Plano Conta");
   PageField->FieldType = ftString;
   PageFields->push_back(PageField);

   RowField = new SfgPivotFdRow();
   wcscpy(RowField->FieldName, L"data_cadastro");
   wcscpy(RowField->Caption, L"Data Cadastro");
   RowField->FieldType = ftDate;
   RowFields->push_back(RowField);

   RowField = new SfgPivotFdRow();
   wcscpy(RowField->FieldName, L"den_situacao");
   wcscpy(RowField->Caption, L"Situação");
   RowField->FieldType = ftString;
   RowFields->push_back(RowField);

   RowField = new SfgPivotFdRow();
   wcscpy(RowField->FieldName, L"den_forma_pagto");
   wcscpy(RowField->Caption, L"Forma Pagto");
   RowField->FieldType = ftString;
   RowFields->push_back(RowField);

   DataField = new SfgPivotFdData();
   wcscpy(DataField->FieldName, L"cod_conta_receber");
   wcscpy(DataField->Caption, L"Conta Receber");
   DataField->FieldType = ftInteger;
   DataField->FieldFunction = 0xFFFFEFF0; //xlCount
   DataFields->push_back(DataField);

   DataField = new SfgPivotFdData();
   wcscpy(DataField->FieldName, L"valor_total");
   wcscpy(DataField->Caption, L"Valor Total");
   DataField->FieldType = ftCurrency;
   DataField->FieldFunction = 0xFFFFEFC3; //xlSum
   DataFields->push_back(DataField);

   DataField = new SfgPivotFdData();
   wcscpy(DataField->FieldName, L"valor_recebido");
   wcscpy(DataField->Caption, L"Valor Recebido");
   DataField->FieldType = ftCurrency;
   DataField->FieldFunction = 0xFFFFEFC3; //xlSum
   DataFields->push_back(DataField);

try {
	SQL = "SELECT cr.cod_conta_receber, cr.cod_cliente, cr.den_cliente,"\
					" DATE(cr.data_cadastro) AS 'data_cadastro', YEAR(cr.data_cadastro) AS 'Ano', MONTH(cr.data_cadastro) AS 'mes',"\
					" cr.ies_situacao, cr.den_situacao, cr.den_forma_pagto,"\
					" cr.valor_total, cr.valor_recebido, cr.cod_centro_custo, cr.cod_plano_conta"\
					" FROM cns_conta_receber cr " + Where +\
               " ORDER BY cr.cod_conta_receber";
	pExcel = new TSfgAnaToExcel();
	pExcel->DadosSheet = "Dados";
	pExcel->PivotSheet = "Análise Contas à Receber";
	pExcel->PivotTable = "analise_contas_receber";
   pExcel->ShowProgress = true;
   pExcel->FileName = pExcel->GetExcelFileName(this);
   pExcel->DataSet->AfterOpen = &DataSetAfterOpen;
   //Inicia a comunicação com o Excel
   if (pExcel->StartExcel()) {
      //Listando os registro para o Excel
      if (pExcel->QueryToExcel(AppConnection,SQL))
         pExcel->GeneratePivotTable(PageFields, RowFields, DataFields);
      pExcel->FinishExcel();
   }
} __finally {
	delete pExcel;
}

   SfgPivotFdPageList::iterator iPg = PageFields->begin();
   for(; iPg != PageFields->end(); ++iPg)
      delete (*iPg);
   delete PageFields;

   SfgPivotFdRowList::iterator iRw = RowFields->begin();
   for(; iRw != RowFields->end(); ++iRw)
      delete (*iRw);
   delete RowFields;

   SfgPivotFdDataList::iterator iDt = DataFields->begin();
   for(; iDt != DataFields->end(); ++iDt) 
      delete (*iDt);
   delete DataFields;

}
//---------------------------------------------------------------------------
void __fastcall TFin2004::DataSetAfterOpen(TDataSet* DataSet)
{
   ((TFloatField*)DataSet->FieldByName("valor_total"))->currency = true;
   ((TFloatField*)DataSet->FieldByName("valor_recebido"))->currency = true;
}
//---------------------------------------------------------------------------



