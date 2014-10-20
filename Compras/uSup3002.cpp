/*
Módulo: Compras
Função: Consulta Pedidos de Compra (Filtros)
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
#include "uSfgBrowseSup.h"
#include "uSfgBrowseFin.h"
#include "uSup3003.h"
#include "uSup3004.h"
#include "uSup3006.h"
#include "uSup3005.h"
#pragma hdrstop
#include "uSup3002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup3002(void) {
   AddAppForm("Sup3002","Consulta Pedidos de Compra",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup3002",__classid(TSup3002));
}
#pragma startup RegisterSup3002
//---------------------------------------------------------------------------
__fastcall TSup3002::TSup3002(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_fornecedor->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_fornecedor") {
		cod_fornecedorExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::data_iniExit(TObject *Sender)
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
void __fastcall TSup3002::data_fimExit(TObject *Sender)
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
void __fastcall TSup3002::cod_fornecedorExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_fornecedor->Text.Length() <= 0) {
		den_fornecedor->Text = "";
		return;
	}
	SQL = "SELECT den_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Fornecedor não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_fornecedor->SetFocus();
	} else {
		den_fornecedor->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btPesqFornecedorClick(TObject *Sender)
{
	pEditRet = cod_fornecedor;
	SfgBrowse::EscolheFornecedor(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btPesqPlanoContaIniClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_ini;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btPesqPlanoContaFimClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_fim;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btPesqCentroCustoIniClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_ini;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btPesqCentroCustoFimClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_fim;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = "SELECT * FROM cns_pedido_compra WHERE 1=1";
	if (cod_fornecedor->Text.Length()) {
		SQL += " AND cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	}
	if (cod_plano_conta_ini->Text.Length()) {
		SQL += " AND cod_plano_conta >= " + QuotedStr(cod_plano_conta_ini->Text);
	}
	if (cod_plano_conta_fim->Text.Length()) {
		SQL += " AND cod_plano_conta <= " + QuotedStr(cod_plano_conta_fim->Text);
	}
	if (cod_centro_custo_ini->Text.Length()) {
		SQL += " AND cod_centro_custo >= " + QuotedStr(cod_centro_custo_ini->Text);
	}
	if (cod_centro_custo_fim->Text.Length()) {
		SQL += " AND cod_centro_custo <= " + QuotedStr(cod_centro_custo_fim->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		SQL += " AND data_cadastro >= :data_ini";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		SQL += " AND data_cadastro <= :data_fim";
	} __finally {}
	}
	//Verifica se foram selecionadas todas as situações
	if (!(ckAberto->Checked &&
			ckEnviado->Checked &&
			ckRecebido->Checked &&
			ckFechado->Checked &&
			ckCancelado->Checked)) {
		str_situacao = "";
		//Faz uma junção de cada situação.
		if (ckAberto->Checked)
			str_situacao += (str_situacao.Length())? ",'A'":"'A'";
		if (ckEnviado->Checked)
			str_situacao += (str_situacao.Length())? ",'E'":"'E'";
		if (ckRecebido->Checked)
			str_situacao += (str_situacao.Length())? ",'R'":"'R'";
		if (ckFechado->Checked)
			str_situacao += (str_situacao.Length())? ",'F'":"'F'";
		if (ckCancelado->Checked)
			str_situacao += (str_situacao.Length())? ",'C'":"'C'";
		SQL += " AND ies_situacao IN (" + str_situacao + ")";
	}
	switch (rbAgrupamento->ItemIndex) {
		case 0:
			SQL += " ORDER BY cod_fornecedor, cod_pedido_compra";
			ConsultaPorFornecedor(SQL,dt_data_ini, dt_data_fim);
			break;
		case 1:
			SQL += " ORDER BY ord_situacao, cod_pedido_compra";
			ConsultaPorSitacao(SQL,dt_data_ini, dt_data_fim);
			break;
		case 2:
			SQL += " ORDER BY cod_plano_conta, cod_pedido_compra";
			ConsultaPorContaContabil(SQL,dt_data_ini, dt_data_fim);
			break;
		case 3:
			SQL += " ORDER BY cod_centro_custo, cod_pedido_compra";
			ConsultaPorCentroCusto(SQL,dt_data_ini, dt_data_fim);
			break;
		default:
			SQL += " ORDER BY cod_fornecedor, cod_pedido_compra";
			ConsultaPorFornecedor(SQL,dt_data_ini, dt_data_fim);
	}
	//Close();
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::ConsultaPorFornecedor(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TSup3003 *Sup3003;
	Sup3003 = new TSup3003(Application);
	Sup3003->QyForPedidoCompra->Close();
	Sup3003->QyForPedidoCompra->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Sup3003->QyForPedidoCompra->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Sup3003->QyForPedidoCompra->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Sup3003->QyForPedidoCompra->Active = true;
   if(Sup3003->RpRelatBase->PrepareReport(true))
      Sup3003->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::ConsultaPorSitacao(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TSup3004 *Sup3004;
	Sup3004 = new TSup3004(Application);
	Sup3004->QySitPedidoCompra->Close();
	Sup3004->QySitPedidoCompra->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Sup3004->QySitPedidoCompra->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Sup3004->QySitPedidoCompra->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Sup3004->QySitPedidoCompra->Active = true;
   if(Sup3004->RpRelatBase->PrepareReport(true))
      Sup3004->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::ConsultaPorCentroCusto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TSup3006 *Sup3006;
	Sup3006 = new TSup3006(Application);
	Sup3006->QyCctPedidoCompra->Close();
	Sup3006->QyCctPedidoCompra->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Sup3006->QyCctPedidoCompra->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Sup3006->QyCctPedidoCompra->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Sup3006->QyCctPedidoCompra->Active = true;
   if(Sup3006->RpRelatBase->PrepareReport(true))
      Sup3006->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TSup3002::ConsultaPorContaContabil(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TSup3005 *Sup3005;
	Sup3005 = new TSup3005(Application);
	Sup3005->QyCntPedidoCompra->Close();
	Sup3005->QyCntPedidoCompra->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Sup3005->QyCntPedidoCompra->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Sup3005->QyCntPedidoCompra->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Sup3005->QyCntPedidoCompra->Active = true;
   if(Sup3005->RpRelatBase->PrepareReport(true))
      Sup3005->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------


