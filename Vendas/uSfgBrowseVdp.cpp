//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowseVdp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolheCliente(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_cliente",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheRepresentante(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_representante",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheFormaPagto(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_forma_pagto",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------

