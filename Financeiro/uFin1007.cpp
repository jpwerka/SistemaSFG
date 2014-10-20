/*
Módulo: Financeiro
Função: Baixa em Lote Contas à Receber
Autor.: Jackson Patrick Werka
Data..: 25/11/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uSfgDrawCmp.h"
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uFin2005.h"
#pragma hdrstop
#include "uFin1007.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1007(void) {
   AddAppForm("Fin1007","Baixa em Lote Contas à Receber",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1007",__classid(TFin1007));
}
#pragma startup RegisterFin1007
//---------------------------------------------------------------------------
__fastcall TFin1007::TFin1007(TComponent* Owner)
	: TfrmBase01(Owner)
{
	den_cliente->Color = AppConfig->Colors->Disabled;
   grdParcelas->OnMouseUp = NULL;
   HabilitaCampos(false);
   //Hack* - Evento customizado do componente Edit do Grid
   ((TThemeDBGrid*)grdParcelas)->OnEditSetFocus = &EditItemSetFocus;
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::SetPermissao(int Nivel)
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
void __fastcall TFin1007::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_cliente") {
		cod_clienteExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::data_iniExit(TObject *Sender)
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
void __fastcall TFin1007::data_fimExit(TObject *Sender)
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
void __fastcall TFin1007::cod_clienteExit(TObject *Sender)
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
void __fastcall TFin1007::btPesqClienteClick(TObject *Sender)
{
	pEditRet = cod_cliente;
	SfgBrowse::EscolheCliente(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::HabilitaCampos(bool Habilita) {
	TColor Color = AppConfig->Colors->Enabled;
	cod_cliente->ReadOnly = !Habilita;
	data_ini->ReadOnly = !Habilita;
	data_fim->ReadOnly = !Habilita;
	btPesqCliente->Enabled = Habilita;
	execAtualizar->Enabled = Habilita;
	execInformar->Enabled = !Habilita;
	execProcessar->Enabled = !Habilita;
	btSair->Enabled = !Habilita;
	execConfirmar->Enabled = Habilita;
	execCancelar->Enabled = Habilita;
	btConfirmar->Visible = Habilita;
	btCancelar->Visible = Habilita;
	if (!Habilita) {
		Color = AppConfig->Colors->Disabled;
	}
	cod_cliente->Color = Color;
	data_ini->Color = Color;
	data_fim->Color = Color;
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btInformarClick(TObject *Sender)
{
	HabilitaCampos(true);
   QyCnsCtaRec->Active = false;
   DsAtuCtaRec->AutoEdit = false;
   valor_recebto->Text = CurrToStrF(0,ffCurrency,2);
   valor_total->Text = CurrToStrF(0,ffCurrency,2);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btAtualizaClick(TObject *Sender)
{
	String sSQL;
	System::TDateTime dt_data_ini, dt_data_fim;
	String str_data_ini, str_data_fim;
	dt_data_ini = dt_data_fim = 0;

   sSQL = "\
SELECT 'S' ies_recebido, cr.cod_cliente, cl.den_cliente,\
       crp.cod_conta_receber, crp.seq_parcela,\
       crp.data_vencimento, crp.valor_parcela, crp.valor_parcela valor_recebido\
  FROM tbl_conta_receber cr\
 INNER JOIN tbl_conta_receber_pagto crp\
    ON cr.cod_conta_receber = crp.cod_conta_receber\
 INNER JOIN tbl_cliente cl\
    ON cl.cod_cliente = cr.cod_cliente\
 WHERE crp.ies_recebido = 'N'";

	if (cod_cliente->Text.Length()) {
		sSQL += " AND cr.cod_cliente = " + QuotedStr(cod_cliente->Text);
	}
	if(data_ini->Text.Length()) {
	try {
		str_data_ini = data_ini->EditText + " 00:00:00";
		dt_data_ini = StrToDateTime(str_data_ini);
		//DateTimeToString(str_data_ini,"yyyy-mm-dd hh:nn:ss",dt_data_ini);
		sSQL += " AND crp.data_vencimento >= :data_ini";
	} catch (...) {}
   }
	if(data_fim->Text.Length()) {
	try {
		str_data_fim = data_fim->EditText + " 23:59:59";
		dt_data_fim = StrToDateTime(str_data_fim);
		//DateTimeToString(str_data_fim,"yyyy-mm-dd hh:nn:ss",dt_data_fim);
		sSQL += " AND crp.data_vencimento <= :data_fim";
	} catch (...) {}
	}
	sSQL += " ORDER BY cr.cod_cliente, crp.cod_conta_receber, crp.seq_parcela";

	//Carrega o GRID de parcelas de contas a receber
   DsAtuCtaRec->AutoEdit = false;
	QyCnsCtaRec->Active = false;
	QyCnsCtaRec->SQL->Text = sSQL;
   if ((int)dt_data_ini != 0) {
      QyCnsCtaRec->ParamByName("data_ini")->AsDateTime = dt_data_ini;
   }
   if ((int)dt_data_fim != 0) {
      QyCnsCtaRec->ParamByName("data_fim")->AsDateTime = dt_data_fim;
   }
	QyCnsCtaRec->Active = true;
   QyCnsCtaRec->DisableControls(); //Para ativar a atualização da tela
	QyCnsCtaRec->First();
	if (QyCnsCtaRec->RecordCount > 0) {
		grdParcelas->OnMouseUp = &grdParcelasMouseUp;
      DsAtuCtaRec->AutoEdit = true;
	} else {
		MessageBox(Handle,"Não foram encontrados registros pendentes para efetuar a baixa!", Caption.c_str(), APP_INFORM);
   }
   FValorRecebto = 0;
	while(!QyCnsCtaRec->Eof) {
      FValorRecebto += QyCnsCtaRec->FieldByName("valor_parcela")->AsFloat;
		QyCnsCtaRec->Next();
	}
   QyCnsCtaRec->First();
   QyCnsCtaRec->EnableControls(); //Para ativar a atualização da tela
   grdParcelas->SelectedField = QyCnsCtaRec->FieldByName("cod_cliente");
   FValorTotal = FValorRecebto;
   valor_recebto->Text = CurrToStrF(FValorRecebto,ffCurrency,2);
   valor_total->Text = CurrToStrF(FValorTotal,ffCurrency,2);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btConfirmarClick(TObject *Sender)
{
	bool check;
   if (!QyCnsCtaRec->Active) {
		MessageBox(Handle,"Informe os dados primeiro para efetuar a baixa!", Caption.c_str(), APP_INFORM);
		return;
   }
   QyCnsCtaRec->DisableControls(); //Para ativar a atualização da tela
	QyCnsCtaRec->First();
	while (!QyCnsCtaRec->Eof) {
		check = QyCnsCtaRec->FieldByName("ies_recebido")->AsString == "S";
		if (check)
			break;
      QyCnsCtaRec->Next();
	}
   QyCnsCtaRec->First();
   QyCnsCtaRec->EnableControls(); //Para ativar a atualização da tela
	if (!check) {
		MessageBox(Handle,"Informe pelo menos uma conta a receber para efetuar a baixa!", Caption.c_str(), APP_INFORM);
		return;
	}

	HabilitaCampos(false);
	//Desabiltando para o usuário não poder clicar no GRID
   DsAtuCtaRec->AutoEdit = false;
	grdParcelas->OnMouseUp = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btCancelarClick(TObject *Sender)
{
	HabilitaCampos(false);
   QyCnsCtaRec->Active = false;
   DsAtuCtaRec->AutoEdit = false;
   valor_recebto->Text = CurrToStrF(0,ffCurrency,2);
   valor_total->Text = CurrToStrF(0,ffCurrency,2);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btProcessarClick(TObject *Sender)
{
	String sSQL;
   bool bSucesso = true;
   String sMsgErro;

   if (!QyCnsCtaRec->Active) {
		MessageBox(Handle,"Informe os dados primeiro para efetuar a baixa!", Caption.c_str(), APP_INFORM);
		return;
   }

   sSQL = "\
UPDATE tbl_conta_receber_pagto\
   SET valor_recebido = :valor_recebido\
      ,valor_desconto = :valor_desconto\
      ,valor_acrescimo = :valor_acrescimo\
      ,data_recebimento = :data_recebimento\
      ,ies_recebido = 'S'\
 WHERE cod_conta_receber = :cod_conta_receber\
   AND seq_parcela = :seq_parcela";

   TZQuery *QyAtuCtaRec = new TZQuery(this);
   QyAtuCtaRec->Connection = AppConnection;
   QyCnsCtaRec->DisableControls(); //Para ativar a atualização da tela
try {
   QyAtuCtaRec->SQL->Text = sSQL;
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	QyCnsCtaRec->First();
	while(!QyCnsCtaRec->Eof) {
      //Se não está marcado para atualizar continua
      if (QyCnsCtaRec->FieldByName("ies_recebido")->AsString == "S") {
         //Copiando os valores da tela para a consulta de atualização
         QyAtuCtaRec->ParamByName("cod_conta_receber")->Value = QyCnsCtaRec->FieldByName("cod_conta_receber")->Value;
         QyAtuCtaRec->ParamByName("seq_parcela")->Value = QyCnsCtaRec->FieldByName("seq_parcela")->Value;
         QyAtuCtaRec->ParamByName("valor_recebido")->Value = QyCnsCtaRec->FieldByName("valor_recebido")->Value;
         if (QyCnsCtaRec->FieldByName("valor_parcela")->AsCurrency == QyCnsCtaRec->FieldByName("valor_recebido")->AsCurrency) {
            QyAtuCtaRec->ParamByName("valor_desconto")->AsInteger = 0;
            QyAtuCtaRec->ParamByName("valor_acrescimo")->AsInteger = 0;
         } else if (QyCnsCtaRec->FieldByName("valor_parcela")->AsCurrency < QyCnsCtaRec->FieldByName("valor_recebido")->AsCurrency) {
            QyAtuCtaRec->ParamByName("valor_desconto")->AsInteger = 0;
            QyAtuCtaRec->ParamByName("valor_acrescimo")->AsCurrency = QyCnsCtaRec->FieldByName("valor_recebido")->AsCurrency -
                                                                      QyCnsCtaRec->FieldByName("valor_parcela")->AsCurrency;
         } else {
            QyAtuCtaRec->ParamByName("valor_desconto")->AsCurrency = QyCnsCtaRec->FieldByName("valor_parcela")->AsCurrency -
                                                                     QyCnsCtaRec->FieldByName("valor_recebido")->AsCurrency;
            QyAtuCtaRec->ParamByName("valor_acrescimo")->AsInteger = 0;
         }
         QyAtuCtaRec->ParamByName("data_recebimento")->AsDateTime = Now();
         QyAtuCtaRec->ExecSQL();
      }
		QyCnsCtaRec->Next();
	}
} catch (Exception &e) {
   sMsgErro = "Ocorreu um erro ao atualizar o recebimento das contas:\n";
   sMsgErro = sMsgErro + e.Message;
   bSucesso = false;
}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
		MessageBox(Handle,"Atualização do recebimento das contas efetuada com sucesso!", Caption.c_str(), APP_INFORM);
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
	}
   QyCnsCtaRec->First();
   QyCnsCtaRec->EnableControls(); //Para ativar a atualização da tela
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdParcelasMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   if (grdParcelas->SelectedField->FieldName == "ies_recebido") {
      if (QyCnsCtaRec->State != dsEdit)
         QyCnsCtaRec->Edit();
      if (grdParcelas->SelectedField->AsString == "S") {
         grdParcelas->SelectedField->AsString = "N";
         FValorRecebto -= QyCnsCtaRec->FieldByName("valor_parcela")->AsFloat;
         FValorTotal -= QyCnsCtaRec->FieldByName("valor_recebido")->AsFloat;
      }
      else {
         grdParcelas->SelectedField->AsString = "S";
         FValorRecebto += QyCnsCtaRec->FieldByName("valor_parcela")->AsFloat;
         FValorTotal += QyCnsCtaRec->FieldByName("valor_recebido")->AsFloat;
      }
      valor_recebto->Text = CurrToStrF(FValorRecebto,ffCurrency,2);
      valor_total->Text = CurrToStrF(FValorTotal,ffCurrency,2);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::EditItemSetFocus(TObject *Sender)
{
   if (DsAtuCtaRec->AutoEdit) {
		if (grdParcelas->SelectedField->FieldName == "valor_recebido") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
   }
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdParcelasDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_recebido") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdParcelas,-1,-1,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdParcelasColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdParcelas->SelectedField->FieldName == "ies_recebido") {
		Options = grdParcelas->Options;
		Options >> dgEditing;
		grdParcelas->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdParcelasColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdParcelas->SelectedField->FieldName == "ies_recebido") {
		Options = grdParcelas->Options;
		Options << dgEditing;
		grdParcelas->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::QyCnsCtaRecBeforeInsert(TDataSet *DataSet)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::grdParcelasKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1007::ValorRecebidoSetText(TField *Sender,
      const AnsiString Text)
{
	//Deve recalcular o valor total do item e do pedido
	float fValor = 0;
	try {
		fValor = (Text.Length()) ? StrToFloat(Text) : 0;
	}
	__finally {}
	if (fValor == NULL || fValor <= 0) {
		MessageBox(Handle,"Informe um valor numérico maior que zero!",Caption.c_str(),APP_ATENTION);
		return;
	} else {
      FValorTotal = (FValorTotal - Sender->AsFloat) + fValor;
		Sender->AsString = Text;
      valor_total->Text = CurrToStrF(FValorTotal,ffCurrency,2);
	}
}
//---------------------------------------------------------------------------



