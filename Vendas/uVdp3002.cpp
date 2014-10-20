/*
Módulo: Vendas
Função: Consulta Pedidos de Venda (Filtros)
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
#include "uSfgBrowseFin.h"
#include "uVdp3003.h"
#include "uVdp3004.h"
#include "uVdp3006.h"
#include "uVdp3005.h"
#include "uVdp3007.h"
#pragma hdrstop
#include "uVdp3002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp3002(void) {
   AddAppForm("Vdp3002","Consulta Pedidos de Venda",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp3002",__classid(TVdp3002));
}
#pragma startup RegisterVdp3002
//---------------------------------------------------------------------------
__fastcall TVdp3002::TVdp3002(TComponent* Owner)
	: TfrmBase01(Owner)
{
   den_cliente->Color = AppConfig->Colors->Disabled;
   den_representante->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	} else if(pEditRet->Name == "cod_representante") {
		cod_representanteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::data_iniExit(TObject *Sender)
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
void __fastcall TVdp3002::data_fimExit(TObject *Sender)
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
void __fastcall TVdp3002::cod_clienteExit(TObject *Sender)
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
void __fastcall TVdp3002::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btPesqPlanoContaIniClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_ini;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btPesqPlanoContaFimClick(TObject *Sender)
{
	pEditRet = cod_plano_conta_fim;
	SfgBrowse::EscolhePlanoConta(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btPesqCentroCustoIniClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_ini;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btPesqCentroCustoFimClick(TObject *Sender)
{
	pEditRet = cod_centro_custo_fim;
	SfgBrowse::EscolheCentroCusto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btPesqRepresentanteClick(TObject *Sender)
{
	pEditRet = cod_representante;
	SfgBrowse::EscolheRepresentante(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::cod_representanteExit(TObject *Sender)
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
void __fastcall TVdp3002::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btRelatorioClick(TObject *Sender)
{
	String SQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	String str_situacao;
	dt_data_ini = dt_data_fim = 0;

	SQL = "SELECT * FROM cns_pedido_venda WHERE 1=1";
	if (cod_cliente->Text.Length()) {
		SQL += " AND cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if (cod_representante->Text.Length()) {
		SQL += " AND cod_representante = " + QuotedStr(cod_representante->Text);
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
			ckFechado->Checked &&
			ckCancelado->Checked)) {
		str_situacao = "";
		//Faz uma junção de cada situação.
		if (ckAberto->Checked)
			str_situacao += (str_situacao.Length())? ",'A'":"'A'";
		if (ckFechado->Checked)
			str_situacao += (str_situacao.Length())? ",'F'":"'F'";
		if (ckCancelado->Checked)
			str_situacao += (str_situacao.Length())? ",'C'":"'C'";
		SQL += " AND ies_situacao IN (" + str_situacao + ")";
	}
	switch (rbAgrupamento->ItemIndex) {
		case 0:
			SQL += " ORDER BY cod_cliente, cod_pedido_venda";
			ConsultaPorCliente(SQL,dt_data_ini, dt_data_fim);
			break;
		case 1:
			SQL += " ORDER BY cod_representante, cod_pedido_venda";
			ConsultaPorRepresentante(SQL,dt_data_ini, dt_data_fim);
			break;
		case 2:
			SQL += " ORDER BY ord_situacao, cod_pedido_venda";
			ConsultaPorSitacao(SQL,dt_data_ini, dt_data_fim);
			break;
		case 3:
			SQL += " ORDER BY cod_plano_conta, cod_pedido_venda";
			ConsultaPorContaContabil(SQL,dt_data_ini, dt_data_fim);
			break;
		case 4:
			SQL += " ORDER BY cod_centro_custo, cod_pedido_venda";
			ConsultaPorCentroCusto(SQL,dt_data_ini, dt_data_fim);
			break;
		default:
			SQL += " ORDER BY cod_cliente, cod_pedido_venda";
			ConsultaPorCliente(SQL,dt_data_ini, dt_data_fim);
	}
	//Close();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::ConsultaPorCliente(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3003 *Vdp3003;
	Vdp3003 = new TVdp3003(Application);
	Vdp3003->QyForPedidoVenda->Close();
	Vdp3003->QyForPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3003->QyForPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3003->QyForPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3003->QyForPedidoVenda->Active = true;
   if(Vdp3003->RpRelatBase->PrepareReport(true))
      Vdp3003->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::ConsultaPorRepresentante(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3007 *Vdp3007;
	Vdp3007 = new TVdp3007(Application);
	Vdp3007->QyForPedidoVenda->Close();
	Vdp3007->QyForPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3007->QyForPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3007->QyForPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3007->QyForPedidoVenda->Active = true;
   if(Vdp3007->RpRelatBase->PrepareReport(true))
      Vdp3007->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::ConsultaPorSitacao(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3004 *Vdp3004;
	Vdp3004 = new TVdp3004(Application);
	Vdp3004->QySitPedidoVenda->Close();
	Vdp3004->QySitPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3004->QySitPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3004->QySitPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3004->QySitPedidoVenda->Active = true;
   if(Vdp3004->RpRelatBase->PrepareReport(true))
      Vdp3004->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::ConsultaPorContaContabil(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3005 *Vdp3005;
	Vdp3005 = new TVdp3005(Application);
	Vdp3005->QyCntPedidoVenda->Close();
	Vdp3005->QyCntPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3005->QyCntPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3005->QyCntPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3005->QyCntPedidoVenda->Active = true;
   if(Vdp3005->RpRelatBase->PrepareReport(true))
      Vdp3005->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp3002::ConsultaPorCentroCusto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim)
{
	TVdp3006 *Vdp3006;
	Vdp3006 = new TVdp3006(Application);
	Vdp3006->QyCctPedidoVenda->Close();
	Vdp3006->QyCctPedidoVenda->SQL->Text = SQL;
	if ((int)dt_data_ini != 0) {
		Vdp3006->QyCctPedidoVenda->ParamByName("data_ini")->AsDateTime = dt_data_ini;
	}
	if ((int)dt_data_fim != 0) {
		Vdp3006->QyCctPedidoVenda->ParamByName("data_fim")->AsDateTime = dt_data_fim;
	}
	Vdp3006->QyCctPedidoVenda->Active = true;
   if(Vdp3006->RpRelatBase->PrepareReport(true))
      Vdp3006->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------



