/*
Módulo: Vendas
Função: Consulta Produtos Pedidos de Venda (Filtros)
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
#include "uSfgBrowseVdp.h"
#include "uSfgBrowsePrd.h"
#include "uVdp3012.h"
#pragma hdrstop
#include "uVdp3011.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp3011(void) {
   AddAppForm("Vdp3011","Consulta Produtos x Venda",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp3011",__classid(TVdp3011));
}
#pragma startup RegisterVdp3011
//---------------------------------------------------------------------------
__fastcall TVdp3011::TVdp3011(TComponent* Owner)
	: TfrmBase01(Owner)
{
   den_cliente->Color = AppConfig->Colors->Disabled;
   den_representante->Color = AppConfig->Colors->Disabled;
   den_forma_pagto->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	} else if(pEditRet->Name == "cod_representante") {
		cod_representanteExit(pEditRet);
	} else if(pEditRet->Name == "forma_pagto") {
		forma_pagtoExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::data_iniExit(TObject *Sender)
{
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;

	if (data_ini->Text.Length()) {
		if (!Validacoes::IsDate(data_ini->EditText)) {
			data_ini->SetFocus();
			return;
		}
	} else {
		return;
	}
	if(data_fim->Text.Length() <= 0 ) {
		return;
	}
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
	} __finally {}
	if (dt_data_ini > dt_data_fim) {
		MessageBox(Handle, "A data inicial deve ser menor ou igual a data final!",Caption.c_str(),APP_ATENTION);
		data_ini->SetFocus();
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::data_fimExit(TObject *Sender)
{
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;

	if (data_fim->Text.Length()) {
		if (!Validacoes::IsDate(data_fim->EditText)) {
			data_fim->SetFocus();
			return;
		}
	} else {
		return;
	}
	if(data_ini->Text.Length() <= 0) {
		return;
	}
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
	} __finally {}
	if (dt_data_ini > dt_data_fim) {
		MessageBox(Handle, "A data final deve ser maior ou igual a data inicial!",Caption.c_str(),APP_ATENTION);
		data_fim->SetFocus();
		return;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::cod_clienteExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_cliente->Text.Length() <= 0) {
		den_cliente->Text = "";
		return;
	}
	SQL = "SELECT den_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(cod_cliente->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Cliente não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
	} else {
		den_cliente->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btPesqFormaPagtoClick(TObject *Sender)
{
	pEditRet = forma_pagto;
	SfgBrowse::EscolheFormaPagto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btPesqProdutoIniClick(TObject *Sender)
{
	pEditRet = cod_produto_ini;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btPesqProdutoFimClick(TObject *Sender)
{
	pEditRet = cod_produto_fim;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btPesqRepresentanteClick(TObject *Sender)
{
	pEditRet = cod_representante;
	SfgBrowse::EscolheRepresentante(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::cod_representanteExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_representante->Text.Length() <= 0) {
		den_representante->Text = "";
		return;
	}
	SQL = "SELECT den_representante FROM tbl_representante" \
			" WHERE cod_representante = " + QuotedStr(cod_representante->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Representante não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_representante->SetFocus();
	} else {
		den_representante->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::forma_pagtoExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(forma_pagto->Text.Length() <= 0) {
		den_forma_pagto->Text = "";
		return;
	}
	SQL = "SELECT den_forma_pagto FROM tbl_forma_pagto" \
			" WHERE cod_forma_pagto = " + QuotedStr(forma_pagto->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Forma de pagamento não cadastrada!",Caption.c_str(),APP_ATENTION);
		forma_pagto->SetFocus();
	} else {
		den_forma_pagto->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = 
"SELECT pagto.cod_forma_pagto, pagto.den_forma_pagto,\
       pvi.cod_produto, prd.den_produto,\
       sum(pvi.qtd_produto) total_produto,\
       sum(pvi.qtd_produto * pvi.preco_venda) valor_total\
  FROM tbl_pedido_venda pv\
 INNER JOIN tbl_pedido_venda_item pvi\
    ON pv.cod_pedido_venda = pvi.cod_pedido_venda\
 INNER JOIN tbl_produto prd\
    ON prd.cod_produto = pvi.cod_produto\
 INNER JOIN tbl_forma_pagto pagto\
    ON pagto.cod_forma_pagto = pv.cod_forma_pagto";


	if (cod_cliente->Text.Length()) {
		SQL += " AND pv.cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if (cod_representante->Text.Length()) {
		SQL += " AND pv.cod_representante = " + QuotedStr(cod_representante->Text);
	}
	if (cod_produto_ini->Text.Length()) {
		SQL += " AND pvi.cod_produto >= " + QuotedStr(cod_produto_ini->Text);
	}
	if (cod_produto_fim->Text.Length()) {
		SQL += " AND pvi.cod_produto <= " + QuotedStr(cod_produto_fim->Text);
	}
	if (forma_pagto->Text.Length()) {
		SQL += " AND pv.cod_forma_pagto >= " + QuotedStr(forma_pagto->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		SQL += " AND pv.data_cadastro >= :data_ini";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		SQL += " AND pv.data_cadastro <= :data_fim";
	} __finally {}
	}
	SQL += " \
GROUP BY pagto.cod_forma_pagto, pagto.den_forma_pagto,\
       pvi.cod_produto, prd.den_produto\
 ORDER BY pagto.cod_forma_pagto, pvi.cod_produto";
   ConsultaPorProduto(SQL,dt_data_ini, dt_data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3011::ConsultaPorProduto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3012 *Vdp3012;
	Vdp3012 = new TVdp3012(Application);
	Vdp3012->QyPrdPedidoVenda->Close();
	Vdp3012->QyPrdPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3012->QyPrdPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3012->QyPrdPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3012->QyPrdPedidoVenda->Active = true;
   if(Vdp3012->RpRelatBase->PrepareReport(true))
      Vdp3012->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------

