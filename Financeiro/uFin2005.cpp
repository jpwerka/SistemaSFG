/*
Módulo: Financeiro
Função: Análise de Contas à Receber (Integração Excel)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFin2005.h"
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFin2005::TFin2005(TComponent* Owner, String SQL)
	: TfrmBase01(Owner)
{
	TSfgAnaToExcel *pExcel;
	OleAnalise->DoVerb(ovPrimary);
try {
	SQL = "SELECT cr.cod_conta_receber, cr.cod_cliente, cr.den_cliente,"\
					" DATE(cr.data_cadastro) AS 'data_cadastro', YEAR(cr.data_cadastro) AS 'Ano', MONTH(cr.data_cadastro) AS 'mes',"\
					" cr.ies_situacao, cr.den_situacao, cr.den_forma_pagto,"\
					" cr.valor_total, cr.valor_recebido, cr.cod_centro_custo, cr.cod_plano_conta"\
					" FROM cns_conta_receber cr " + SQL +\
               " ORDER BY cr.cod_conta_receber";
	pExcel = new TSfgAnaToExcel();
	pExcel->DadosSheet = "Dados";
	pExcel->PivotSheet = "Análise Contas à Receber";
	pExcel->PivotTable = "analise_contas_receber";
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
void __fastcall TFin2005::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (OleAnalise->State == osUIActive) {
		OleAnalise->Close();
	}
	TfrmBase01::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
void __fastcall TFin2005::DataSetAfterOpen(TDataSet* DataSet)
{
   ((TFloatField*)DataSet->FieldByName("valor_total"))->currency = true;
   ((TFloatField*)DataSet->FieldByName("valor_recebido"))->currency = true;
}
//---------------------------------------------------------------------------

