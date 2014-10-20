//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowseFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolheGrupo(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_grupo",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheUsuario(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_usuario",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------
