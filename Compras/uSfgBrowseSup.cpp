//---------------------------------------------------------------------------
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowseSup.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace SfgBrowse {
//---------------------------------------------------------------------------
void EscolheFornecedor(TForm *pParent, SfgBrowseReturn OnBrowseReturn)
{
   TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   String sSQL = GetBrowseSQL("tbl_fornecedor",frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
void EscolheProdutoFornecedor(TForm *pParent, String Fornecedor, SfgBrowseReturn OnBrowseReturn)
{
   String sSQL;
	sSQL = "SELECT p.cod_produto, p.den_produto, p.ies_ativo" \
           " FROM tbl_fornecedor_produto f, tbl_produto p" \
          " WHERE f.cod_fornecedor = "+ QuotedStr(Fornecedor) + \
            " AND p.cod_produto = f.cod_produto" \
          " ORDER BY p.cod_produto";
   TSfgMetaTable *MetaTable = AddMetaTable("tbl_produto");
	TfrmBrowse *frmBrowse = new TfrmBrowse(Application);
   CreateFieldDef(MetaTable->FieldByName("cod_produto"),frmBrowse->DataSet);
   CreateFieldDef(MetaTable->FieldByName("den_produto"),frmBrowse->DataSet);
   CreateFieldDef(MetaTable->FieldByName("ies_ativo"),frmBrowse->DataSet);
   CreateFields(frmBrowse->DataSet);
	frmBrowse->SQL = sSQL;
	frmBrowse->OnBrowseReturn = OnBrowseReturn;
	frmBrowse->ShowModal();
   delete frmBrowse;
}
//---------------------------------------------------------------------------
}; //End namespace SfgBrowse
//---------------------------------------------------------------------------

