//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowseFin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolhePlanoConta(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
   String sSQL;
	DynamicArray<String> FieldDefs;
	FieldDefs.Length = 4;
	FieldDefs[0] = "cod_plano_conta|ftString|15|Plano Conta|1";
	FieldDefs[1] = "den_plano_conta|ftString|45|Denominação";
	FieldDefs[2] = "tipo_plano_conta|ftString|1|Tipo";
	FieldDefs[3] = "cod_plano_conta_pai|ftString|15|Conta Pai";
	sSQL = "SELECT cod_plano_conta, den_plano_conta, tipo_plano_conta, cod_plano_conta_pai" \
	        " FROM tbl_plano_conta" \
	       " ORDER BY cod_plano_conta";
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   CreateFieldDefs(FieldDefs,frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheCentroCusto(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_centro_custo",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------

