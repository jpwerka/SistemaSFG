/*
Módulo: Financeiro
Função: Movimentações Caixa (Entradas x Saídas)
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
#include "uFin1003.h"
#include "uFin1002.h"
#pragma hdrstop
#include "uFin2001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin2001(void) {
   AddAppForm("Fin2001","Movimentações Caixa",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin2001",__classid(TFin2001));
}
#pragma startup RegisterFin2001
//---------------------------------------------------------------------------
__fastcall TFin2001::TFin2001(TComponent* Owner)
	: TfrmBase01(Owner)
{
	cbPeriodoChange(cbPeriodo);
	edtTotalEntrada->Color = AppConfig->Colors->Disabled;
	edtTotalSaida->Color = AppConfig->Colors->Disabled;
	edtDiferenca->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::SetPermissao(int Nivel)
{
   NivelPerm = Nivel;
   if (Nivel == APP_PERM_TOTAL)
      return;

   PopupMenu1->Items->Items[2]->Visible = false;
   PopupMenu1->Items->Items[3]->Visible = false;
   PopupMenu1->Items->Items[4]->Visible = false;
   PopupMenu2->Items->Items[2]->Visible = false;
   PopupMenu2->Items->Items[3]->Visible = false;
   PopupMenu2->Items->Items[4]->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::SplitterBodyMoved(TObject *Sender)
{
	if (gbEntrada->Height <= 1) {
		btAbaixo->Left = int((gbSaida->Width / 2) - 18);
		btAbaixo->Visible = true;
		btAcima->Visible = false;
	} else if (gbSaida->Height <= 1) {
		btAcima->Left = int((gbEntrada->Width / 2) - 18);
		btAcima->Top = gbEntrada->Height - 7;
		btAcima->Visible = true;
		btAbaixo->Visible = false;
	} else {
		btAcima->Visible = false;
		btAbaixo->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::btAcimaClick(TObject *Sender)
{
	GridPanelResize(BodyPanel);
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::btAbaixoClick(TObject *Sender)
{
	GridPanelResize(BodyPanel);
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::GridPanelResize(TObject *Sender)
{
	gbSaida->Height = GridPanel->Height/2;
	btAcima->Visible = false;
	btAbaixo->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::cbPeriodoChange(TObject *Sender)
{
	data_ini->ReadOnly = true;
	data_ini->Color = AppConfig->Colors->Disabled;
	data_ini->ReadOnly = true;
	data_fim->Color = AppConfig->Colors->Disabled;
	if (cbPeriodo->ItemIndex == 0) { //Pode ser por dia atual
		data_ini->Text = FormatDateTime("dd/mm/yyyy", Date());
		data_fim->Text = FormatDateTime("dd/mm/yyyy", Date());
		RefazConsulta();
	} else if (cbPeriodo->ItemIndex == 1) { //Pode ser por semana atual
		data_ini->Text = FormatDateTime("dd/mm/yyyy", StartOfTheWeek(Date()));
		data_fim->Text = FormatDateTime("dd/mm/yyyy", EndOfTheWeek(Date()));
		RefazConsulta();
	} else if (cbPeriodo->ItemIndex == 2) { //Pode ser por mês atual
		data_ini->Text = FormatDateTime("dd/mm/yyyy", StartOfTheMonth(Date()));
		data_fim->Text = FormatDateTime("dd/mm/yyyy", EndOfTheMonth(Date()));
		RefazConsulta();
	} else { //Ou um período informado pelo usuário
		data_ini->ReadOnly = false;
		data_ini->Color = AppConfig->Colors->Enabled;
		data_ini->ReadOnly = false;
		data_fim->Color = AppConfig->Colors->Enabled;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::RefazConsulta()
{
	Word Year, Month, Day;
	System::TDateTime DateTimeIni, DateTimeFim;
	float TotalEntrada, TotalSaida;

	DecodeDate(StrToDate(data_ini->Text), Year, Month, Day);
	DateTimeIni = EncodeDateTime(Year, Month, Day, 00, 00, 00, 0);
	DecodeDate(StrToDate(data_fim->Text), Year, Month, Day);
	DateTimeFim = EncodeDateTime(Year, Month, Day, 23, 59, 59, 0);

	QyEntrada->Active = false;
	QySaida->Active = false;

	QyEntrada->ParamByName("data_ini")->AsDateTime = DateTimeIni;
	QyEntrada->ParamByName("data_fim")->AsDateTime = DateTimeFim;
	QySaida->ParamByName("data_ini")->AsDateTime = DateTimeIni;
	QySaida->ParamByName("data_fim")->AsDateTime = DateTimeFim;

	QyEntrada->Active = true;
	QySaida->Active = true;

	TotalEntrada = TotalSaida = 0;
	QyEntrada->First();
	QyEntrada->DisableControls();
	while (!QyEntrada->Eof) {
		TotalEntrada += QyEntrada->FieldByName("valor_lancamento")->AsFloat;
		QyEntrada->Next();
	}
	QyEntrada->First();
	QyEntrada->EnableControls();

	QySaida->First();
	QySaida->DisableControls();
	while (!QySaida->Eof) {
		TotalSaida += QySaida->FieldByName("valor_lancamento")->AsFloat;
		QySaida->Next();
	}
	QySaida->First();
	QySaida->EnableControls();

	edtTotalEntrada->Text = CurrToStrF(TotalEntrada,ffCurrency,2);
	edtTotalSaida->Text = CurrToStrF(TotalSaida,ffCurrency,2);
   edtDiferenca->Text = CurrToStrF((TotalEntrada-TotalSaida),ffCurrency,2);
}
//DecodeDate(const System::TDateTime DateTime, Word &Year, Word &Month, Word &Day);
//EncodeDateTime(const Word AYear, const Word AMonth, const Word ADay, const Word AHour, const Word AMinute, const Word ASecond, const Word AMilliSecond);
//EndOfTheMonth(const System::TDateTime AValue);
//StartOfTheWeek(const System::TDateTime AValue);
//EndOfTheWeek(const System::TDateTime AValue);
//---------------------------------------------------------------------------
void __fastcall TFin2001::btAtualizaClick(TObject *Sender)
{
	RefazConsulta();
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_ini);
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_fim);
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::PopupMenu1Popup(TObject *Sender)
{
	if (QyEntrada->RecordCount > 0) {
		PopupMenu1->Items->Items[0]->Enabled = true;
		if (QyEntrada->FieldByName("tipo_registro")->AsString == "PV") {
			PopupMenu1->Items->Items[1]->Enabled = true;
		} else {
			PopupMenu1->Items->Items[1]->Enabled = false;
		}
	} else {
		PopupMenu1->Items->Items[0]->Enabled = false;
		PopupMenu1->Items->Items[1]->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::IrParaContaReceber1Click(TObject *Sender)
{
	TFin1003 *form;
	if (QyEntrada->RecordCount > 0) {
		form = new TFin1003(Application);
      form->SetPermissao(NivelPerm);
		form->FilterCodConta(QyEntrada->FieldByName("cod_documento")->AsInteger);
		form->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::VisualizarPedidoVenda1Click(TObject *Sender)
{
   SfgExecProgram *pSfgExecProgram = new SfgExecProgram();
   pSfgExecProgram->ProgramName = "Vdp1001";
   pSfgExecProgram->ProgramModulo = APP_MODULO_VENDAS;
   pSfgExecProgram->NivelPermissao = NivelPerm;
   pSfgExecProgram->ProgramRotina = 1;
   pSfgExecProgram->CallBeforeShow = TRUE;
   pSfgExecProgram->ProgramParams = QyEntrada->FieldByName("num_documento")->AsInteger;
   Application->MainForm->Perform(WM_SFGEXECPROGRAM, 0, (LPARAM)pSfgExecProgram);
   delete pSfgExecProgram;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::IncluirContaReceber1Click(TObject *Sender)
{
	TFin1003 *form = new TFin1003(Application);
	form->Show();
	form->SfgToolbar->btNew->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::IncluirPedidoVenda1Click(TObject *Sender)
{
   SfgExecProgram *pSfgExecProgram = new SfgExecProgram();
   pSfgExecProgram->ProgramName = "Vdp1001";
   pSfgExecProgram->ProgramModulo = APP_MODULO_VENDAS;
   pSfgExecProgram->NivelPermissao = NivelPerm;
   pSfgExecProgram->ProgramRotina = 2;
   pSfgExecProgram->CallBeforeShow = FALSE;
   pSfgExecProgram->ProgramParams = 0;
   Application->MainForm->Perform(WM_SFGEXECPROGRAM, 0, (LPARAM)pSfgExecProgram);
   delete pSfgExecProgram;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::PopupMenu2Popup(TObject *Sender)
{
	if (QySaida->RecordCount > 0) {
		PopupMenu2->Items->Items[0]->Enabled = true;
		if (QySaida->FieldByName("tipo_registro")->AsString == "PC") {
			PopupMenu2->Items->Items[1]->Enabled = true;
		} else {
			PopupMenu2->Items->Items[1]->Enabled = false;
		}
	} else {
		PopupMenu2->Items->Items[0]->Enabled = false;
		PopupMenu2->Items->Items[1]->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::N11Click(TObject *Sender)
{
	TFin1002 *form;
	if (QyEntrada->RecordCount > 0) {
		form = new TFin1002(Application);
      form->SetPermissao(NivelPerm);
		form->FilterCodConta(QySaida->FieldByName("cod_documento")->AsInteger);
		form->Show();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::N21Click(TObject *Sender)
{
   SfgExecProgram *pSfgExecProgram = new SfgExecProgram();
   pSfgExecProgram->ProgramName = "Sup1001";
   pSfgExecProgram->ProgramModulo = APP_MODULO_COMPRAS;
   pSfgExecProgram->NivelPermissao = NivelPerm;
   pSfgExecProgram->ProgramRotina = 1;
   pSfgExecProgram->CallBeforeShow = TRUE;
   pSfgExecProgram->ProgramParams = QySaida->FieldByName("num_documento")->AsInteger;
   Application->MainForm->Perform(WM_SFGEXECPROGRAM, 0, (LPARAM)pSfgExecProgram);
   delete pSfgExecProgram;
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::N31Click(TObject *Sender)
{
	TFin1002 *form = new TFin1002(Application);
	form->Show();
	form->SfgToolbar->btNew->Click();
}
//---------------------------------------------------------------------------
void __fastcall TFin2001::N41Click(TObject *Sender)
{
   SfgExecProgram *pSfgExecProgram = new SfgExecProgram();
   pSfgExecProgram->ProgramName = "Sup1001";
   pSfgExecProgram->ProgramModulo = APP_MODULO_COMPRAS;
   pSfgExecProgram->NivelPermissao = NivelPerm;
   pSfgExecProgram->ProgramRotina = 2;
   pSfgExecProgram->CallBeforeShow = FALSE;
   pSfgExecProgram->ProgramParams = 0;
   Application->MainForm->Perform(WM_SFGEXECPROGRAM, 0, (LPARAM)pSfgExecProgram);
   delete pSfgExecProgram;
}
//---------------------------------------------------------------------------

