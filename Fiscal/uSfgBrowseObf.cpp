//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowseObf.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolheNaturezaOperacao(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_natureza_operacao",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
	delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------




