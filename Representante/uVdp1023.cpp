/*
Módulo: Vendas - Representantes
Função: Cadastro Representantes
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
#include "uSfgVdpCustom.h"
#include "uSfgWorkEdition.h"
#pragma hdrstop
#include "uVdp1023.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1023(void) {
   AddAppForm("Vdp1023","Representantes",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1023",__classid(TVdp1023));
}
#pragma startup RegisterVdp1023
//---------------------------------------------------------------------------
__fastcall TVdp1023::TVdp1023(TComponent* Owner)
   : TfrmBase02(Owner)
{
   CarregarTipoPessoa();
   CarregarEstado();
   SfgToolbar->DataSource = DsCadRepresentante;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
   QyCadRepresentante->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   //if(hSfgVdpCustom) {
   //   SfgVdp1023AfterCreate = (PSfgVdp1023AfterCreate)GetProcAddress(hSfgVdpCustom,"SfgVdp1023AfterCreate");
   //   if (SfgVdp1023AfterCreate)
   //      SfgVdp1023AfterCreate(this);
   //}
   UseCodAuto = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_representa');")) == "S");
	if (UseCodAuto) {
      TStrings *pStrings = SfgToolbar->WorkEdition->ListControls;
	   pStrings->Delete(pStrings->IndexOf("cod_representante"));
	   cod_representante->ReadOnly = true;
	   cod_representante->Color = AppConfig->Colors->Disabled;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::ValidInsert(bool &bValid)
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
void __fastcall TVdp1023::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_pedido_venda" \
			" WHERE cod_representante = " + QuotedStr(cod_representante->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Representante possui pedidos de venda relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::CarregarTipoPessoa()
{
   tipo_pessoa->Clear();
   tipo_pessoa->AddItem("Pessoa Física","F");
   tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::CarregarEstado()
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
void __fastcall TVdp1023::cod_ufChange(TObject *Sender)
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
bool __fastcall TVdp1023::VerificaCampos()
{
	if (!UseCodAuto) {
      if(!cod_representante->Text.Length()) {
		   MessageBox(Handle, "Digite o código do representante!",Caption.c_str(),APP_ATENTION);
		   cod_representante->SetFocus();
		   return false;
      }
	}
	if(!den_representante->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do representante!",Caption.c_str(),APP_ATENTION);
		den_representante->SetFocus();
		return false;
	}
	if(cpf_cnpj->Text.Trim().Length()) {
      if (QyCadRepresentante->FieldByName("tipo_pessoa")->AsString == "F") {
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
bool __fastcall TVdp1023::ValidaCampos()
{
	String SQL;
	if (!UseCodAuto) {
   	SQL = "SELECT cod_representante FROM tbl_representante" \
   			" WHERE cod_representante = " + QuotedStr(cod_representante->Text);
   	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
   		MessageBox(Handle, "Representante já cadastrado!",Caption.c_str(),APP_ATENTION);
   		cod_representante->SetFocus();
   		return false;
   	}
   } else { //Deve buscar o próximo código do representante
      String ProxCod = "";
      if (!ValidacoesDB::GetProxCod(AppConnection,"prox_cod_representa",ProxCod)) {
   		MessageBox(Handle, "Erro ao buscar próximo código do representante!",Caption.c_str(),APP_ATENTION);
         return false;
      }
      QyCadRepresentante->FieldByName("cod_representante")->AsString = ProxCod;
   }
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_nasc_fund);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::QyCadRepresentanteAfterScroll(TDataSet *DataSet)
{
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
	cod_cidade->SetTableItems(true);
   TipoPessoaChange(tipo_pessoa->Field);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::perc_comissaoKeyPress(TObject *Sender, char &Key)
{
   Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCadRepresentante->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCadRepresentante->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::grpObsExit(TObject *Sender)
{
   grpObs->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1023::btObsClick(TObject *Sender)
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


