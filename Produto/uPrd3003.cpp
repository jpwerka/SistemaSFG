/*
Módulo: Produtos
Função: Relatório Estoque de Produtos (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uPrd3004.h"
#pragma hdrstop
#include "uPrd3003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd3003(void) {
   AddAppForm("Prd3003","Estoque de Produtos",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd3003",__classid(TPrd3003));
}
#pragma startup RegisterPrd3003
//---------------------------------------------------------------------------
__fastcall TPrd3003::TPrd3003(TComponent* Owner)
		  : TfrmBase01(Owner)
{
	den_familia->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::BtOKClick(TObject *Sender)
{
	String SQL;
	SQL = "SELECT p.cod_familia, f.den_familia,"\
					" p.cod_produto, p.den_produto,"\
					" p.qtd_estoque, p.qtd_estoque_min,"\
					" (p.preco_custo * p.qtd_estoque) valor_estoque,"\
					" p.cod_unid_medida"\
			 " FROM tbl_produto p, tbl_familia f"\
			" WHERE p.cod_familia = f.cod_familia"\
			  " AND p.controla_estoque= 'S'";
	if(cod_familia->Text.Length()) {
		SQL += " AND p.cod_familia = " + cod_familia->Text;
	}
	if(cod_produto_ini->Text.Length()) {
		SQL += " AND p.cod_produto >= " + QuotedStr(cod_produto_ini->Text);
	}
	if(cod_produto_fim->Text.Length()) {
		SQL += " AND p.cod_produto <= " + QuotedStr(cod_produto_fim->Text);
	}
	if(Abaixo->Checked) {
		SQL += " AND (p.qtd_estoque < p.qtd_estoque_min)";
	}
	SQL += " ORDER BY p.cod_familia,p.cod_produto";
	TPrd3004 *Prd3004 = new TPrd3004(Owner);
	Prd3004->QyEstoque->Close();
	Prd3004->QyEstoque->SQL->Text = SQL;
	Prd3004->QyEstoque->Active = true;
   if(Prd3004->RpRelatBase->PrepareReport(true))
      Prd3004->RpRelatBase->ShowPreparedReport();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::cod_familiaExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_familia->Text.Length() <= 0) {
		den_familia->Text = "";
		return;
	}
	SQL = "SELECT den_familia FROM tbl_familia" \
			" WHERE cod_familia = " + QuotedStr(cod_familia->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Família não cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_familia->SetFocus();
	} else {
		den_familia->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::btSearchFamiliaClick(TObject *Sender)
{
	pEditRet = cod_familia;
	SfgBrowse::EscolheFamilia(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::btSearchProdutoIniClick(TObject *Sender)
{
	pEditRet = cod_produto_ini;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::btSearchProdutoFimClick(TObject *Sender)
{
	pEditRet = cod_produto_fim;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_familia") {
		cod_familiaExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::BtCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrd3003::execPesquisaExecute(TObject *Sender)
{
	if (Screen->ActiveControl == NULL)
     return;
	if(Screen->ActiveControl->InheritsFrom(__classid(TEdit))) {
		pEditRet = (TEdit*)Screen->ActiveControl;
		if(pEditRet->Name == "cod_familia") {
			SfgBrowse::EscolheFamilia(this,&SearchReturn);
		} else if(pEditRet->Name == "cod_produto_ini") {
			SfgBrowse::EscolheProduto(this,&SearchReturn);
		} else if(pEditRet->Name == "cod_produto_fim") {
			SfgBrowse::EscolheProduto(this,&SearchReturn);
		}
	}
}
//---------------------------------------------------------------------------

