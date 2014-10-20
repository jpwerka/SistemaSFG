//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowsePrd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolheFamilia(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	String sSQL;
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   sSQL = GetBrowseSQL("tbl_familia",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
	delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheProduto(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	String sSQL;
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   sSQL = GetBrowseSQL("tbl_produto",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------




