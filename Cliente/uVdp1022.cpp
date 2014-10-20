/*
Módulo: Vendas - Clientes
Função: Cadastro Cidades
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgWorkEdition.h"
#pragma hdrstop  
#include "uVdp1022.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1022(void) {
   AddAppForm("Vdp1022","Cidades",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1022",__classid(TVdp1022));
}
#pragma startup RegisterVdp1022
//---------------------------------------------------------------------------
__fastcall TVdp1022::TVdp1022(TComponent* Owner)
	: TfrmBase02(Owner)
{
   CarregarEstado();
   SfgToolbar->DataSource = DsCadCidade;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
   UseCodAuto = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_cidade');")) == "S");
	if (UseCodAuto) {
      TStrings *pStrings = SfgToolbar->WorkEdition->ListControls;
	   pStrings->Delete(pStrings->IndexOf("cod_cidade"));
	   cod_cidade->ReadOnly = true;
	   cod_cidade->Color = AppConfig->Colors->Disabled;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1022::CarregarEstado()
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
void __fastcall TVdp1022::ValidInsert(bool &bValid)
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
void __fastcall TVdp1022::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1022::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_fornecedor" \
			" WHERE cod_cidade = " + QuotedStr(cod_cidade->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem fornecedores cadastradas para esta cidade. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1022::VerificaCampos()
{
	if (!UseCodAuto) {
	   if(!cod_cidade->Text.Length()) {
		   MessageBox(Handle, "Digite o código da cidade!",Caption.c_str(),APP_ATENTION);
		   cod_cidade->SetFocus();
		   return false;
      }
	}
	if(!den_cidade->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do cidade!",Caption.c_str(),APP_ATENTION);
		den_cidade->SetFocus();
		return false;
	}
   if (cod_ibge->Text.Length()) {
	   String SQL = "SELECT cod_cidade FROM tbl_cidade" \
	   		" WHERE cod_ibge = " + cod_ibge->Text;
      if (QyCadCidade->State == dsEdit) {
         SQL = SQL + " AND cod_cidade != " +  QuotedStr(cod_cidade->Text);
      }
	   if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
	   	MessageBox(Handle, "Código IBGE da cidade já cadastrado!",Caption.c_str(),APP_ATENTION);
	   	cod_ibge->SetFocus();
	   	return false;
	   }
   }
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1022::ValidaCampos()
{
	String SQL;
   if (!UseCodAuto) {
	   SQL = "SELECT cod_cidade FROM tbl_cidade" \
	   		" WHERE cod_cidade = " + QuotedStr(cod_cidade->Text);
	   if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
	   	MessageBox(Handle, "Cidade já cadastrada!",Caption.c_str(),APP_ATENTION);
	   	cod_cidade->SetFocus();
	   	return false;
	   }
   } else { //Deve buscar o próximo código da cidade
      String ProxCod = "";
      if (!ValidacoesDB::GetProxCod(AppConnection,"prox_cod_cidade",ProxCod)) {
   		MessageBox(Handle, "Erro ao buscar próximo código da cidade!",Caption.c_str(),APP_ATENTION);
         return false;
      }
      QyCadCidade->FieldByName("cod_cidade")->AsString = ProxCod;
   }
	return true;
}
//---------------------------------------------------------------------------
