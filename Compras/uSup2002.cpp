/*
Módulo: Compras
Função: Análise Pedidos de Compra (Integração Excel)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uSup2002.h"
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSup2002::TSup2002(TComponent* Owner, String SQL)
	: TfrmBase01(Owner)
{
	TSfgAnaToExcel *pExcel;
	OleAnalise->DoVerb(ovPrimary);
try {
	SQL = "SELECT pc.cod_pedido_compra, pc.cod_fornecedor, pc.den_fornecedor,"\
					" DATE(pc.data_cadastro) AS 'data_cadastro', YEAR(pc.data_cadastro) AS 'Ano', MONTH(pc.data_cadastro) AS 'mes',"\
					" pc.ies_situacao, pc.den_situacao, pc.den_forma_pagto,"\
					" pc.valor_total, pc.valor_pago, pc.cod_centro_custo, pc.cod_plano_conta"\
			 " FROM cns_pedido_compra pc " + SQL + \
          " ORDER BY pc.cod_pedido_compra";
	pExcel = new TSfgAnaToExcel();
	pExcel->DadosSheet = "Dados";
	pExcel->PivotSheet = "Análise Compras";
	pExcel->PivotTable = "analise_compras";
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
void __fastcall TSup2002::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (OleAnalise->State == osUIActive) {
		OleAnalise->Close();
	}
	TfrmBase01::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
void __fastcall TSup2002::DataSetAfterOpen(TDataSet* DataSet)
{
   ((TFloatField*)DataSet->FieldByName("valor_total"))->currency = true;
   ((TFloatField*)DataSet->FieldByName("valor_pago"))->currency = true;
}
//---------------------------------------------------------------------------


