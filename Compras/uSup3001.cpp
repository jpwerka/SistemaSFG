/*
Módulo: Compras
Função: Relatório Pedido de Compra
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uDataModule.h"
#pragma hdrstop
#include "uSup3001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSup3001::TSup3001(TComponent* Owner)
	: TfrmRelatBase01(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TSup3001::CnsCompraAfterOpen(TDataSet *DataSet)
{
	CnsProdutos->Active = true;
	CnsPagtos->Active = true;
}
//---------------------------------------------------------------------------

