/*
Módulo: Vendas - Clientes
Função: Cadastro Natureza Operação
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uObf1006.h"
#pragma hdrstop
#include "uObf1002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterObf1002(void) {
   AddAppForm("Obf1002","Natureza Operação",APP_MODULO_FISCAL);
   AddAppFormClass("TObf1002",__classid(TObf1002));
}
#pragma startup RegisterObf1002
//---------------------------------------------------------------------------
__fastcall TObf1002::TObf1002(TComponent* Owner)
	: TfrmBase02(Owner)
{
  CarregarCST();
  SfgToolbar->DataSource = DsNaturezaOperacao;
  SfgToolbar->ValidInsert = &ValidInsert;
  SfgToolbar->ValidUpdate = &ValidUpdate;
  SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TObf1002::CarregarCST()
{
   ObfCST::LoadCSTICMS(cod_cst_icms_padrao,CST_ICMS_AMBOS);
   ObfCST::LoadCSTIPI(cod_cst_ipi_padrao,CST_IPI_AMBOS);
   ObfCST::LoadCSTPIS(cod_cst_pis_padrao);
   ObfCST::LoadCSTCOFINS(cod_cst_cofins_padrao);
}
//---------------------------------------------------------------------------
void __fastcall TObf1002::ValidInsert(bool &bValid)
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
void __fastcall TObf1002::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1002::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_nota_fiscal" \
			" WHERE natureza_operacao = " + QuotedStr(cod_natureza_operacao->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem notas fiscais cadastradas para esta natureza de operação. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TObf1002::VerificaCampos()
{
	if(!cod_natureza_operacao->Text.Length()) {
		MessageBox(Handle, "Digite o código da natureza de operação!",Caption.c_str(),APP_ATENTION);
		cod_natureza_operacao->SetFocus();
		return false;
	}
	if(!den_natureza_operacao->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da natureza de operação!",Caption.c_str(),APP_ATENTION);
		den_natureza_operacao->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TObf1002::ValidaCampos()
{
	String sSQL;
	sSQL = "SELECT cod_natureza_operacao FROM tbl_natureza_operacao" \
			" WHERE cod_natureza_operacao = " + cod_natureza_operacao->Text;
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		MessageBox(Handle, "Natureza de operação já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_natureza_operacao->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1002::FormClose(TObject *Sender, TCloseAction &Action)
{
   ObfCST::UnloadCST(cod_cst_icms_padrao);
   ObfCST::UnloadCST(cod_cst_ipi_padrao);
   ObfCST::UnloadCST(cod_cst_pis_padrao);
   ObfCST::UnloadCST(cod_cst_cofins_padrao);
   TfrmBase01::FormClose(Sender, Action);
}
//---------------------------------------------------------------------------
void __fastcall TObf1002::percentual_icmsKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(percentual_icms->Text, Key);
}
//---------------------------------------------------------------------------

