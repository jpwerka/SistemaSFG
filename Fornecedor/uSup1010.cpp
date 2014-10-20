/*
Módulo: Compras - Fornecedor
Função: Cadastro Fornecedor
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgWorkEdition.h"
#pragma hdrstop
#include "uSup1010.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup1010(void) {
   AddAppForm("Sup1010","Fornecedor",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup1010",__classid(TSup1010));
}
#pragma startup RegisterSup1010
//---------------------------------------------------------------------------
__fastcall TSup1010::TSup1010(TComponent* Owner)
   : TfrmBase02(Owner)
{
   CarregarTipoPessoa();
   CarregarEstado();
   SfgToolbar->DataSource = DsCadFornecedor;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
   QyCadFornecedor->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;
   UseCodAuto = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_fornecedor');")) == "S");
	if (UseCodAuto) {
      TStrings *pStrings = SfgToolbar->WorkEdition->ListControls;
	   pStrings->Delete(pStrings->IndexOf("cod_fornecedor"));
	   cod_fornecedor->ReadOnly = true;
	   cod_fornecedor->Color = AppConfig->Colors->Disabled;
   }
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::ValidInsert(bool &bValid)
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
void __fastcall TSup1010::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_fornecedor_produto"\
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Fornecedor possui produtos relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	SQL = "SELECT DISTINCT 1 FROM tbl_pedido_compra"\
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Fornecedor possui pedidos de compra relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
//#ifdef USE_FINANCEIRO
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_pagar"\
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Fornecedor possui contas a pagar relacionadas. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
//#endif
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::CarregarTipoPessoa()
{
   tipo_pessoa->Clear();
   tipo_pessoa->AddItem("Pessoa Física","F");
   tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::CarregarEstado()
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
void __fastcall TSup1010::cod_ufChange(TObject *Sender)
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
bool __fastcall TSup1010::VerificaCampos()
{
	if (!UseCodAuto) {
	   if(!cod_fornecedor->Text.Length()) {
         MessageBox(Handle, "Digite o código do fornecedor!",Caption.c_str(),APP_ATENTION);
         cod_fornecedor->SetFocus();
         return false;
      }
	}
   if(!den_fornecedor->Text.Length()) {
      MessageBox(Handle, "Digite a denominação do fornecedor!",Caption.c_str(),APP_ATENTION);
      den_fornecedor->SetFocus();
      return false;
   }
	if(cpf_cnpj->Text.Trim().Length()) {
      if (QyCadFornecedor->FieldByName("tipo_pessoa")->AsString == "F") {
		   if(!Validacoes::ValidarCPF(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CPF válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      } else {
		   if(!Validacoes::ValidarCNPJ(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CNPJ válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      }
	}
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSup1010::ValidaCampos()
{
	String sSQL;
	if (!UseCodAuto) {
	   sSQL = "SELECT cod_fornecedor FROM tbl_fornecedor" \
	   		" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	   if(ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
	   	MessageBox(Handle, "Fornecedor já cadastrado!",Caption.c_str(),APP_ATENTION);
	   	cod_fornecedor->SetFocus();
	   	return false;
	   }
   } else { //Deve buscar o próximo código do cliente
      String ProxCod = "";
      if (!ValidacoesDB::GetProxCod(AppConnection,"prox_cod_fornecedor",ProxCod)) {
   		MessageBox(Handle, "Erro ao buscar próximo código do fornecedor!",Caption.c_str(),APP_ATENTION);
         return false;
      }
      QyCadFornecedor->FieldByName("cod_fornecedor")->AsString = ProxCod;
   }
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_nasc_fund);
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::QyCadFornecedorAfterScroll(TDataSet *DataSet)
{
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
	cod_cidade->SetTableItems(true);
   TipoPessoaChange(tipo_pessoa->Field);
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCadFornecedor->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCadFornecedor->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::btObsClick(TObject *Sender)
{
   TPoint pt;
   pt.x = 0;
   pt.y = 0;
   pt = grpInfo->ClientToParent(pt,this);
	grpObs->Top = pt.y;
	grpObs->Left = pt.x;
	grpObs->Show();
	observacao->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSup1010::grpObsExit(TObject *Sender)
{
   grpObs->Hide();
}
//---------------------------------------------------------------------------

