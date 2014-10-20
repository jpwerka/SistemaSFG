/*
Módulo: Vendas
Função: Análise Comissão Representantes (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uVdp2002.h"
#pragma hdrstop
#include "uVdp2022.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp2022(void) {
   AddAppForm("Vdp2022","Comissão Representantes",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp2022",__classid(TVdp2022));
}
#pragma startup RegisterVdp2022
//---------------------------------------------------------------------------
__fastcall TVdp2022::TVdp2022(TComponent* Owner)
	: TfrmBase01(Owner)
{
	HabilitaCampos(false);
   den_cliente->Color = AppConfig->Colors->Disabled;
   den_representante->Color = AppConfig->Colors->Disabled;
   CnsComissao->Active = true;
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdRepresentantes)->OnEditSetFocus = &EditItemSetFocus;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   //Escondendo as opções de menu do SfgToolbar
	execInformar->Visible = false;
	execProcessar->Visible = false;
   //Desabilitando as teclas de atalho também
	execInformar->Enabled = false;
	execProcessar->Enabled = false;
   btSair->Left = 6;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	} else if(pEditRet->Name == "cod_representante") {
		cod_representanteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::data_iniExit(TObject *Sender)
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
void __fastcall TVdp2022::data_fimExit(TObject *Sender)
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
void __fastcall TVdp2022::cod_clienteExit(TObject *Sender)
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
void __fastcall TVdp2022::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::btPesqRepresentanteClick(TObject *Sender)
{
	pEditRet = cod_representante;
	SfgBrowse::EscolheRepresentante(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::cod_representanteExit(TObject *Sender)
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
void __fastcall TVdp2022::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::HabilitaCampos(bool Habilita) {
	TColor Color = (Habilita) ? AppConfig->Colors->Enabled : AppConfig->Colors->Disabled;
	data_ini->ReadOnly = !Habilita;
	data_fim->ReadOnly = !Habilita;
	cod_cliente->ReadOnly = !Habilita;
	cod_representante->ReadOnly = !Habilita;
	btPesqCliente->Enabled = Habilita;
	btPesqRepresentante->Enabled = Habilita;
	execAtualizar->Enabled = Habilita;
	execInformar->Enabled = !Habilita;
	execProcessar->Enabled = !Habilita;
	btSair->Enabled = !Habilita;
	execConfirmar->Enabled = Habilita;
	execCancelar->Enabled = Habilita;
	btConfirmar->Visible = Habilita;
	btCancelar->Visible = Habilita;
	cod_cliente->Color = Color;
	cod_representante->Color = Color;
	data_ini->Color = Color;
	data_fim->Color = Color;
	valor_base_calculo->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::RestauraGrid()
{
   CnsComissao->CancelUpdates();
   CnsComissao->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::execInformarExecute(TObject *Sender)
{
	HabilitaCampos(true);
	RestauraGrid();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::execConfirmarExecute(TObject *Sender)
{
   if (!CnsComissao->RecordCount) {
      MessageBox(NULL,"Não foram informados os dados para o processamento!",Caption.c_str(),APP_INFORM);
      return;
   }
	HabilitaCampos(false);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::execCancelarExecute(TObject *Sender)
{
	HabilitaCampos(false);
	RestauraGrid();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::execAtualizarExecute(TObject *Sender)
{
	String sSQL = "";
	System::TDateTime dt_data_ini, dt_data_fim, data_comissao;
	String str_data_ini, str_data_fim;
	dt_data_ini = dt_data_fim = 0;
   TZQuery *LoadComissao;
   bool bExisteComissao = false;

   if (valor_base_calculo->ItemIndex == 0) {
      sSQL += "\
SELECT tbl_pedido_venda.cod_representante,\
       tbl_representante.den_representante,\
       tbl_pedido_venda.cod_pedido_venda,\
       tbl_pedido_venda_pagto.seq_parcela,\
       tbl_pedido_venda_pagto.valor_parcela valor_calculo,\
       tbl_representante.perc_comissao,\
       tbl_pedido_venda.data_fechamento data_comissao\
  FROM tbl_pedido_venda\
 INNER JOIN tbl_pedido_venda_pagto\
    ON tbl_pedido_venda_pagto.cod_pedido_venda = tbl_pedido_venda.cod_pedido_venda\
 INNER JOIN tbl_representante\
    ON tbl_representante.cod_representante = tbl_pedido_venda.cod_representante\
 WHERE tbl_pedido_venda.ies_situacao IN ('F','T')\
   AND NOT EXISTS (SELECT 1\
                     FROM tbl_comissao_representante cr\
                    WHERE cr.cod_representante = tbl_pedido_venda.cod_representante\
                      AND cr.cod_pedido_venda = tbl_pedido_venda.cod_pedido_venda\
                      AND cr.seq_parcela = tbl_pedido_venda_pagto.seq_parcela)";
   } else {
      sSQL += "\
SELECT tbl_pedido_venda.cod_representante,\
       tbl_representante.den_representante,\
       tbl_pedido_venda.cod_pedido_venda,\
       tbl_conta_receber_pagto.seq_parcela,\
       tbl_conta_receber_pagto.valor_recebido valor_calculo,\
       tbl_representante.perc_comissao,\
       tbl_pedido_venda.data_fechamento data_comissao\
  FROM tbl_conta_receber_pagto\
 INNER JOIN tbl_conta_receber\
    ON tbl_conta_receber.cod_conta_receber = tbl_conta_receber_pagto.cod_conta_receber\
 INNER JOIN tbl_pedido_venda\
    ON tbl_pedido_venda.cod_pedido_venda = tbl_conta_receber.num_documento\
 INNER JOIN tbl_representante\
    ON tbl_representante.cod_representante = tbl_pedido_venda.cod_representante\
 WHERE tbl_conta_receber.tipo_registro = 'PV'\
   AND tbl_conta_receber_pagto.ies_recebido = 'S'\
   AND NOT EXISTS (SELECT 1\
                     FROM tbl_comissao_representante cr\
                    WHERE cr.cod_representante = tbl_pedido_venda.cod_representante\
                      AND cr.cod_pedido_venda = tbl_pedido_venda.cod_pedido_venda\
                      AND cr.seq_parcela = tbl_conta_receber_pagto.seq_parcela)";
   }

	if (cod_cliente->Text.Length()) {
		sSQL += " AND tbl_pedido_venda.cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if (cod_representante->Text.Length()) {
		sSQL += " AND tbl_pedido_venda.cod_representante = " + QuotedStr(cod_representante->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		DateTimeToString(str_data_ini,"yyyy-mm-dd hh:nn:ss",dt_data_ini);
		if (valor_base_calculo->ItemIndex == 0)
         sSQL += " AND (tbl_pedido_venda.data_fechamento >= {ts '"+str_data_ini+"'})";
      else
         sSQL += " AND (tbl_conta_receber_pagto.data_recebimento >= {ts '"+str_data_ini+"'})";
	} __finally {}
	}
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		DateTimeToString(str_data_fim,"yyyy-mm-dd hh:nn:ss",dt_data_fim);
		if (valor_base_calculo->ItemIndex == 0)
         sSQL += " AND (tbl_pedido_venda.data_fechamento <= {ts '"+str_data_fim+"'})";
      else
         sSQL += " AND (tbl_conta_receber_pagto.data_recebimento <= {ts '"+str_data_fim+"'})";
	} __finally {}
	}
   sSQL += " ORDER BY 1,3,4";
	//Limpando os objetos anteriores
	RestauraGrid();

   LoadComissao = new TZQuery(this);
   //Desabilita o evento que previne e inclusão no GID
   CnsComissao->BeforeInsert = NULL;
try {
	LoadComissao->SQL->Text = sSQL;
	LoadComissao->Connection = AppConnection;
	LoadComissao->Active = true;
   LoadComissao->First();
   CnsComissao->CachedUpdates = true;
   while (!LoadComissao->Eof) {
      CnsComissao->Insert();
      CnsComissao->FieldByName("cod_representante")->AsString =  LoadComissao->FieldByName("cod_representante")->AsString;
      CnsComissao->FieldByName("den_representante")->AsString =  LoadComissao->FieldByName("den_representante")->AsString;
      CnsComissao->FieldByName("cod_pedido_venda")->AsInteger =  LoadComissao->FieldByName("cod_pedido_venda")->AsInteger;
      CnsComissao->FieldByName("seq_parcela")->AsInteger =  LoadComissao->FieldByName("seq_parcela")->AsInteger;
      CnsComissao->FieldByName("valor_calculo")->AsFloat =  LoadComissao->FieldByName("valor_calculo")->AsFloat;
      CnsComissao->FieldByName("perc_comissao")->AsFloat =  LoadComissao->FieldByName("perc_comissao")->AsFloat;
      CnsComissao->FieldByName("valor_comissao")->AsFloat = CnsComissao->FieldByName("valor_calculo")->AsFloat *
                                                           (CnsComissao->FieldByName("perc_comissao")->AsFloat/100);
      CnsComissao->FieldByName("valor_base_calculo")->AsInteger =  valor_base_calculo->ItemIndex + 1;
      data_comissao = LoadComissao->FieldByName("data_comissao")->AsDateTime;
      CnsComissao->FieldByName("mes_comissao")->AsInteger = MonthOf(data_comissao);
      CnsComissao->FieldByName("ano_comissao")->AsInteger = YearOf(data_comissao);
      CnsComissao->FieldByName("data_calculo")->AsDateTime = Now();
      CnsComissao->Post();
      LoadComissao->Next();
      bExisteComissao = true;
   }
}__finally {
	delete(LoadComissao);
}
   //Habilita novam,ente o evento que previne a inclusão manual no GID
   CnsComissao->BeforeInsert = &CnsComissaoBeforeInsert;
   if (!bExisteComissao)
      MessageBox(NULL,"Não existem dados para serem processados!",Caption.c_str(),APP_INFORM);
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::execProcessarExecute(TObject *Sender)
{
   //Deve processar a geração dos dados inserindo na tabela de comissões
	String sMsg;
   bool bSucesso = true;
   if (!CnsComissao->RecordCount) {
      MessageBox(NULL,"Não foram informados os dados para o processamento!",Caption.c_str(),APP_INFORM);
      return;
   }

   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	try {
		CnsComissao->ApplyUpdates();
	}
	catch(Exception &e){
		sMsg = "Ocorreu um erro ao gravar as comissões dos representantes:\n";
		sMsg = sMsg + e.Message;
		bSucesso = false;
	}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
		MessageBox(Handle,"Comissão dos representantes calculada com sucesso!", Caption.c_str(), APP_INFORM);
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::grdRepresentantesKeyDown(TObject *Sender,
      WORD &Key, TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::CnsComissaoBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::EditItemSetFocus(TObject *Sender)
{
	if (grdRepresentantes->SelectedField->FieldName == "valor_comissao") {
		((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
	} else {
		((TEdit*)Sender)->OnKeyPress = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp2022::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------

