/*
Módulo: Financeiro
Função: Pagamentos Contas à Pagar
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgWorkEdition.h"
#include "uSfgCalendar.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFin1004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1004(void) {
   AddAppForm("Fin1004","Pagamento de Contas",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1004",__classid(TFin1004));
}
#pragma startup RegisterFin1004
//---------------------------------------------------------------------------
__fastcall TFin1004::TFin1004(TComponent* Owner)
	: TfrmBase02(Owner)
{
   TSfgMetaTable *MetaTable = AddMetaTable("cns_conta_pagar");
   MetaTable->FieldByName("cod_conta_pagar")->IsPkKey = true;
   CarregarSitContaPagar();
	SfgToolbar->DataSource = DsContaPagar;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
	ies_situacao->ReadOnly = true;
	ies_situacao->Color = AppConfig->Colors->Disabled;
	pWorkEdtPagto = new SfgWorkEdition(DsContaPagarPagto,this);
	pWorkEdtPagto->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

	btPagarPagto->Visible = false;
	btEstornaPagto->Visible = false;
	btSavePagto->Visible = false;
	btCancelPagto->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::FilterCodConta(int CodConta)
{
   SfgToolbar->WhereFilter = "cod_conta_pagar = " + IntToStr(CodConta);
   SfgToolbar->OrderByFilter = "";
   SfgToolbar->RefreshQuery();
	SfgToolbar->btExit->Left = 6;
	for (int i=0; i < SfgToolbar->ActionList1->ActionCount; i++) {
		TAction *pAction = (TAction*)SfgToolbar->ActionList1->Actions[i];
		pAction->Visible = false;
		pAction->Enabled = false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFin1004::ValidaCampos()
{
	if (RoundTo(QyCadPagto->FieldByName("valor_pago")->AsFloat,-3) !=
		 RoundTo((QyCadPagto->FieldByName("valor_parcela")->AsFloat -
					 QyCadPagto->FieldByName("valor_desconto")->AsFloat +
					 QyCadPagto->FieldByName("valor_multa")->AsFloat +
					 QyCadPagto->FieldByName("valor_acrescimo")->AsFloat) ,-3)) {
		MessageBox(Handle, "Valor pago menos descontos, mais multas e acrescimos diferente do valor da parcela!",Caption.c_str(),APP_ATENTION);
		valor_pago->SetFocus();
		return false;
	}
	if (!data_pagamento->Text.Length()) {
		MessageBox(Handle, "Informe a data de pagamento!",Caption.c_str(),APP_ATENTION);
		data_pagamento->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::CarregarSitContaPagar()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Pendente","P");
	ies_situacao->AddItem("Andamento","A");
	ies_situacao->AddItem("Liquidado","L");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "ies_situacao") {
      ComboBox->Clear();
      ComboBox->Items->Assign(ies_situacao->Items);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::HabilitarItens(bool Habilita)
{
	grdPagtos->Enabled = Habilita;
	if(Habilita) {
		QyCadPagtoAfterScroll(QyCadPagto);
	} else {
		btPagarPagto->Enabled = Habilita;
		btEstornaPagto->Enabled = Habilita;
	}
	btSavePagto->Enabled = !Habilita;
	btCancelPagto->Enabled = !Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::btPagarPagtoClick(TObject *Sender)
{
	QyCadPagto->Edit();
	QyCadPagto->FieldByName("valor_pago")->Value = QyCadPagto->FieldByName("valor_parcela")->Value;
	QyCadPagto->FieldByName("data_pagamento")->AsDateTime = Date();
	HabilitarItens(false);
	pWorkEdtPagto->SetWorkEdition(true,false,AppConfig->Colors->Enabled);
	valor_desconto->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::btEstornaPagtoClick(TObject *Sender)
{
	if (MessageBox(Handle, "Confirma o estorno do pagamento da parcela?", Caption.c_str(), APP_QUESTION) == IDNO) {
		return;
	}
	QyCadPagto->Edit();
	QyCadPagto->FieldByName("valor_desconto")->AsFloat = 0;
	QyCadPagto->FieldByName("valor_multa")->AsFloat = 0;
	QyCadPagto->FieldByName("valor_acrescimo")->AsFloat = 0;
	QyCadPagto->FieldByName("valor_pago")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("data_pagamento")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_pago")->AsString = "N";
	QyCadPagto->Post();
	QyCadPagtoAfterScroll(QyCadPagto);
	QySitContaPagar->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::btSavePagtoClick(TObject *Sender)
{
	if (!ValidaCampos()) {
		return;
	}
	QyCadPagto->FieldByName("ies_pago")->AsString = "S";
	QyCadPagto->Post();
	pWorkEdtPagto->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(true);
	QySitContaPagar->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::btCancelPagtoClick(TObject *Sender)
{
	QyCadPagto->Cancel();
	pWorkEdtPagto->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::QyCadPagtoAfterScroll(TDataSet *DataSet)
{
	if(DataSet->FieldByName("ies_pago")->AsString == "S") {
		btPagarPagto->Enabled = false;
		btEstornaPagto->Enabled = true;
	} else {
		btPagarPagto->Enabled = true;
		btEstornaPagto->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::CnsContaPagarAfterScroll(TDataSet *DataSet)
{
	QyCadPagtoAfterScroll(QyCadPagto);
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::grdPagtosDrawColumnCell(
		TObject *Sender, const TRect &Rect, int DataCol, TColumn *Column,
		TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_pago") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdPagtos,-1,-1,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::bt_data_pagamentoClick(TObject *Sender)
{
	ExecCalendar(data_pagamento);
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::CnsContaPagarAfterOpen(TDataSet *DataSet)
{
   QySitContaPagar->Active = true;
   QyCadPagto->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1004::CnsContaPagarBeforeClose(TDataSet *DataSet)
{
   QySitContaPagar->Active = false;
   QyCadPagto->Active = false;
}
//---------------------------------------------------------------------------



