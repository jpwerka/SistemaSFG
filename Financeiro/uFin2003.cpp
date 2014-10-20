/*
Módulo: Financeiro
Função: Análise de Contas à Pagar (Integração Excel)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFin2003.h"
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFin2003::TFin2003(TComponent* Owner, String SQL)
	: TfrmBase01(Owner)
{
	TSfgAnaToExcel *pExcel;
	OleAnalise->DoVerb(ovPrimary);
try {
	SQL = "SELECT cp.cod_conta_pagar, cp.cod_fornecedor, cp.den_fornecedor,"\
					" DATE(cp.data_cadastro) AS 'data_cadastro', YEAR(cp.data_cadastro) AS 'Ano', MONTH(cp.data_cadastro) AS 'mes',"\
					" cp.ies_situacao, cp.den_situacao, cp.den_forma_pagto,"\
					" cp.valor_total, cp.valor_pago, cp.cod_centro_custo, cp.cod_plano_conta"\
					" FROM cns_conta_pagar cp " + SQL + \
          " ORDER BY cp.cod_conta_pagar";
	pExcel = new TSfgAnaToExcel();
	pExcel->DadosSheet = "Dados";
	pExcel->PivotSheet = "Análise Contas à Pagar";
	pExcel->PivotTable = "analise_contas_pagar";
   pExcel->ShowProgress = true;
   pExcel->DataSet->AfterOpen = &DataSetAfterOpen;
	if (pExcel->SetContainer(OleAnalise)) {
		pExcel->QueryToExcel(AppConnection,SQL);
	}
} __finally
{
	delete pExcel;
}
}
//---------------------------------------------------------------------------
void __fastcall TFin2003::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (OleAnalise->State == osUIActive) {
		OleAnalise->Close();
	}
	TfrmBase01::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
void __fastcall TFin2003::DataSetAfterOpen(TDataSet* DataSet)
{
   ((TFloatField*)DataSet->FieldByName("valor_total"))->currency = true;
   ((TFloatField*)DataSet->FieldByName("valor_pago"))->currency = true;
}
//---------------------------------------------------------------------------

