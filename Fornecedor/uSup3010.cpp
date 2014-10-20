/*
Módulo: Compras - Fornecedor
Função: Relatório Fornecedores x Endereço
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uSup3010.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup3010(void) {
   AddAppForm("Sup3010","Fornecedor x Estado x Cidade",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup3010",__classid(TSup3010));
}
#pragma startup RegisterSup3010
//---------------------------------------------------------------------------
__fastcall TSup3010::TSup3010(TComponent* Owner)
		  : TfrmRelatBase01(Owner)
{
   if(RpRelatBase->PrepareReport(true))
      RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
