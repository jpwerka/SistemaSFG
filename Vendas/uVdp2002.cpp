/*
Módulo: Vendas
Função: Análise Pedidos de Venda (Integração Excel)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uVdp2002.h"
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVdp2002::TVdp2002(TComponent* Owner, String SQL)
	: TfrmBase01(Owner)
{
	TSfgAnaToExcel *pExcel;
	OleAnalise->DoVerb(ovPrimary);
try {
	SQL = "SELECT pv.cod_pedido_venda, pv.cod_cliente, pv.den_cliente,"\
					" DATE(pv.data_cadastro) AS 'data_cadastro', YEAR(pv.data_cadastro) AS 'ano', MONTH(pv.data_cadastro) AS 'mes',"\
					" pv.ies_situacao, pv.den_situacao, pv.den_forma_pagto,"\
					" pv.valor_total, pv.valor_recebido, pv.cod_centro_custo, pv.cod_plano_conta,"\
               " pv.cod_representante, pv.den_representante"\
			 " FROM cns_pedido_venda pv " + SQL + \
          " ORDER BY pv.cod_pedido_venda";
	pExcel = new TSfgAnaToExcel();
	pExcel->DadosSheet = "Dados";
	pExcel->PivotSheet = "Análise Vendas";
	pExcel->PivotTable = "analise_vendas";
   pExcel->ShowProgress = true;
   pExcel->DataSet->AfterOpen = &DataSetAfterOpen;
	if (pExcel->SetContainer(OleAnalise)) {
		pExcel->QueryToExcel(AppConnection,SQL);
	}
} __finally {
	delete pExcel;
}
}
//---------------------------------------------------------------------------
void __fastcall TVdp2002::FormClose(TObject *Sender, TCloseAction &Action)
{
	if (OleAnalise->State == osUIActive) {
		OleAnalise->Close();
	}
	TfrmBase01::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2002::DataSetAfterOpen(TDataSet* DataSet)
{
   ((TFloatField*)DataSet->FieldByName("valor_total"))->currency = true;
   ((TFloatField*)DataSet->FieldByName("valor_recebido"))->currency = true;
}
//---------------------------------------------------------------------------


