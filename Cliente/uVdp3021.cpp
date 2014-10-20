/*
Módulo: Vendas - Clientes
Função: Relatório Clientes x Endereço
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
#include "uVdp3021.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp3021(void) {
   AddAppForm("Vdp3021","Cliente x Estado x Cidade",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp3021",__classid(TVdp3021));
}
#pragma startup RegisterVdp3021
//---------------------------------------------------------------------------
__fastcall TVdp3021::TVdp3021(TComponent* Owner)
        : TfrmRelatBase01(Owner)
{
   if(RpRelatBase->PrepareReport(true))
      RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------

