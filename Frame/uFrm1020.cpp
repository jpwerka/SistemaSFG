/*
Módulo: Frame - Empresas
Função: Cadastro Empresas
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
#include "uFrm1020.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1020(void) {
   AddAppForm("Frm1020","Empresas");
   AddAppFormClass("TFrm1020",__classid(TFrm1020));
}
#pragma startup RegisterFrm1020
//---------------------------------------------------------------------------
__fastcall TFrm1020::TFrm1020(TComponent* Owner)
   : TfrmBase02(Owner)
{
  CarregarRegimeTributario();
  CarregarEstado();
  SfgToolbar->DataSource = DsCadEmpresa;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
  //SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::ValidInsert(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
	if (!ValidaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::CarregarRegimeTributario()
{
   regime_tributario->Clear();
   regime_tributario->AddItem("Simples Nacional","1");
   regime_tributario->AddItem("Simples Nacional - excesso de sublimite de receita bruta","2");
   regime_tributario->AddItem("Regime Normal","3");
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::ValidDelete(bool &bValid)
{
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::CarregarEstado()
{
  TZQuery *QyUF = new TZQuery(this);
try
{
  QyUF->SQL->Text = "SELECT cod_uf FROM tbl_uf ORDER BY cod_uf";
  QyUF->Connection = AppConnection;
  QyUF->Active = true;
  while(!QyUF->Eof) {
    cod_uf->AddItem(QyUF->FieldByName("cod_uf")->AsString,NULL);
    QyUF->Next();
  }
}__finally{delete(QyUF);}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::cod_ufChange(TObject *Sender)
{
   if(cod_uf->ReadOnly)
      return;
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
   cod_cidade->SetTableItems(true);
	cod_cidade->Field->Clear();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1020::VerificaCampos()
{
	if(cod_empresa->Text.Length() < 2) {
		MessageBox(Handle, "Digite o código da empresa com 02 digitos!",Caption.c_str(),APP_ATENTION);
		cod_empresa->SetFocus();
		return false;
	}
	if(!razao_social->Text.Length()) {
		MessageBox(Handle, "Digite a razão social da empresa!",Caption.c_str(),APP_ATENTION);
		razao_social->SetFocus();
		return false;
	}
	if(cnpj->Text.Trim().Length()) {
		if(!Validacoes::ValidarCNPJ(cnpj->Text)){
			MessageBox(Handle, "O valor informado não é um CNPJ válido!",
						Caption.c_str(),APP_ATENTION);
			cnpj->SetFocus();
			return false;
		}
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1020::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_empresa FROM tbl_empresa" \
			" WHERE cod_empresa = " + QuotedStr(cod_empresa->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Empresa já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_empresa->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::QyCadEmpresaAfterScroll(TDataSet *DataSet)
{
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
	cod_cidade->SetTableItems(true);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1020::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "regime_tributario") {
      ComboBox->Clear();
      ComboBox->Items->Assign(regime_tributario->Items);
   } else
   if (Filter->Field->FieldName == "cod_uf") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_uf->Items);
   }
}
//---------------------------------------------------------------------------



