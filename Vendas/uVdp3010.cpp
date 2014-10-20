/*
Módulo: Vendas
Função: Relatório Orçamento
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uDataModule.h"
#pragma hdrstop
#include "uVdp3010.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVdp3010::TVdp3010(TComponent* Owner)
	: TfrmRelatBase01(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TVdp3010::CnsOrcamentoAfterOpen(TDataSet *DataSet)
{
	CnsProdutos->Active = true;
	CnsPagtos->Active = true;
}
//---------------------------------------------------------------------------

