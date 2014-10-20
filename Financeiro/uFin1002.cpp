/*
Módulo: Financeiro
Função: Cadastro Contas à Pagar
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#include "uSfgCalendar.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#include "uSfgBrowseSup.h"
#include "uSfgBrowseFin.h"
#include "uFin1004.h"
#include "uFin3013.h"
#pragma hdrstop
#include "uFin1002.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1002(void) {
   AddAppForm("Fin1002","Contas à Pagar",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1002",__classid(TFin1002));
}
#pragma startup RegisterFin1002
//---------------------------------------------------------------------------
__fastcall TFin1002::TFin1002(TComponent* Owner)
	: TfrmBase02(Owner)
{
   CarregarTipoRegistro();
	CarregarSitContaPagar();
	CarregarFormaPagto();
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsContaPagar;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   QyContaPagar->FieldByName("cod_fornecedor")->OnValidate = &CodFornecedorValidate;
   QyContaPagar->FieldByName("cod_plano_conta")->OnValidate = &CodPlanoContaValidate;
   QyContaPagar->FieldByName("cod_centro_custo")->OnValidate = &CodCentroCustoValidate;
	den_fornecedor->Color = AppConfig->Colors->Disabled;
	ies_situacao->Color = AppConfig->Colors->Disabled;
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdPagtos)->OnEditSetFocus = &EditPagtoSetFocus;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRecContaPagar->Parent = SfgToolbar;
	btRecContaPagar->Top = 6;
	btRecContaPagar->TabOrder = btRelatorio->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btRelatorio);
	this->Tolltips->AddToolTip(btRecContaPagar);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::AfterCreateFields(TDataSet *DataSet)
{
   //Marcando campo como auto incremento
   QyContaPagar->FieldByName("cod_conta_pagar")->AutoGenerateValue = arAutoInc;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::SetPermissao(int Nivel)
{
   NivelPerm = Nivel;
   if (Nivel == APP_PERM_TOTAL)
      return;

   TfrmBase02::SetPermissao(Nivel);
   btRecContaPagar->Left = SfgToolbar->btExit->Left;
   SfgToolbar->btExit->Left += 38;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::FilterCodConta(int CodConta)
{
   SfgToolbar->WhereFilter = "cod_conta_pagar = " + IntToStr(CodConta);
   SfgToolbar->OrderByFilter = "";
   SfgToolbar->RefreshQuery();
	btRecContaPagar->Left = 6;
	SfgToolbar->btExit->Left = 44;
	for (int i=0; i < SfgToolbar->ActionList1->ActionCount; i++) {
		TAction *pAction = (TAction*)SfgToolbar->ActionList1->Actions[i];
		pAction->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::ValidInsert(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
   }
	if (!ValidaCampos()) {
		bValid = false;
		PostStatus = false;
		return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::ValidDelete(bool &bValid)
{
	String Situacao;
	String TipoDocum;

	TipoDocum = QyContaPagar->FieldByName("tipo_registro")->AsString;
	if (TipoDocum == "PC") { //Pedido de Compra
		MessageBox(Handle,"Conta a pagar integrada a partir de um pedido de compra. Exclusão não permitida!",Caption.c_str(),APP_INFORM);
		bValid = false;
		return;
	}
	QySitContaPagar->Refresh();
	Situacao = QySitContaPagar->FieldByName("ies_situacao")->AsString;
	if(Situacao != "P") {
		MessageBox(Handle,"Conta a pagar não está mais pendente. Exclusão não permitida!",Caption.c_str(),APP_INFORM);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CarregarSitContaPagar()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Pendente","P");
	ies_situacao->AddItem("Andamento","A");
	ies_situacao->AddItem("Liquidado","L");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CarregarTipoRegistro()
{
	tipo_registro->Clear();
	tipo_registro->AddItem("Manual","CP");
	tipo_registro->AddItem("Pedido Compra","PC");
	tipo_registro->AddItem("Comissão","CR");
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CarregarFormaPagto()
{
  TBDFin1002Object *Obj;
  TZQuery *QyPagto = new TZQuery(this);
try
{
	QyPagto->SQL->Text = "SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado FROM tbl_forma_pagto WHERE ies_financeiro = 'S'";
	QyPagto->Connection = AppConnection;
	QyPagto->Active = true;
	cod_forma_pagto->Clear();
	while(!QyPagto->Eof) {
		Obj = new TBDFin1002Object();
		Obj->SetValue(QyPagto->FieldByName("cod_forma_pagto")->Value);
		if (QyPagto->FieldByName("ies_parcelado")->AsString == "S") {
			Obj->ies_parcelado = true;
		} else {
			Obj->ies_parcelado = false;
		}
		cod_forma_pagto->AddItem(QyPagto->FieldByName("den_forma_pagto")->AsString, (TObject*)Obj);
		QyPagto->Next();
  }
}__finally{delete(QyPagto);}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "ies_situacao") {
      ComboBox->Clear();
      ComboBox->Items->Assign(ies_situacao->Items);
   } else
   if (Filter->Field->FieldName == "tipo_registro") {
      ComboBox->Clear();
      ComboBox->Items->Assign(tipo_registro->Items);
   } else
   if (Filter->Field->FieldName == "cod_forma_pagto") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_forma_pagto->Items);
   }
}
//---------------------------------------------------------------------------
bool __fastcall TFin1002::VerificaCampos()
{
	bool bPagto = false;
	if(!num_documento->Text.Length()) {
		MessageBox(Handle, "Digite o número do documento referente a conta a pagar!",Caption.c_str(),APP_ATENTION);
		num_documento->SetFocus();
		return false;
	}
	if(!cod_fornecedor->Text.Length()) {
		MessageBox(Handle, "Digite o código do fornecedor que representa o credor da conta a pagar!",Caption.c_str(),APP_ATENTION);
		cod_fornecedor->SetFocus();
		return false;
	}
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (!QyCadPagto->Eof) {
		if (QyCadPagto->FieldByName("valor_parcela")->AsFloat <= 0) {
			MessageBox(Handle, "Informe um valor da parcela maior que zero!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 0;
			grdPagtos->SetFocus();
			grdPagtos->SelectedField = QyCadPagto->FieldByName("valor_parcela");
			QyCadPagto->EnableControls(); //Para ativar a atualização da tela
			return false;
		}
		if (VarIsNull(QyCadPagto->FieldByName("data_vencimento")->Value)) {
			MessageBox(Handle, "Informe a data de vencimento da parcela!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 0;
			grdPagtos->SetFocus();
			grdPagtos->SelectedField = QyCadPagto->FieldByName("data_vencimento");
			QyCadPagto->EnableControls(); //Para ativar a atualização da tela
			return false;
		}
		QyCadPagto->Next();
		bPagto = true;
	}
	QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	if (!bPagto) {
		MessageBox(Handle, "Informe pelo menos uma parcela para recebimento!",Caption.c_str(),APP_ATENTION);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFin1002::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CodFornecedorValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		throw Exception("Fornecedor não cadastrado!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::NavegexecBtEditClickExecute(TObject *Sender)
{
	String Situacao;
	String TipoDocum;

	TipoDocum = QyContaPagar->FieldByName("tipo_registro")->AsString;
	if (TipoDocum == "PC") { //Pedido de Compra
		MessageBox(Handle,"Conta a pagar integrada a partir de um pedido de compra. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	QySitContaPagar->Refresh();
	Situacao = QySitContaPagar->FieldByName("ies_situacao")->AsString;
	if(Situacao != "P") {
		MessageBox(Handle,"Conta a pagar não está mais pendente. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	SfgToolbar->btEditClick(Sender);
	HabilitarItens(true);
	QyContaPagar->FieldByName("ies_situacao")->AsString = Situacao;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::NavegexecBtNewClickExecute(TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	data_cadastro->Field->Value = Now();
	QyContaPagar->FieldByName("ies_situacao")->AsString = "P";
	QyContaPagar->FieldByName("tipo_registro")->AsString = "CP";
	cod_forma_pagto->ItemIndex = 0;
	cod_forma_pagto->Field->Value = cod_forma_pagto->Value;
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyCadPagtoBeforeInsert;
	QyCadPagto->FieldByName("cod_conta_pagar")->AsInteger = 0;
   QyCadPagto->FieldByName("seq_parcela")->AsInteger = 1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_pago")->AsString = "N";
	QyCadPagto->Post();
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::cod_fornecedorExit(TObject *Sender)
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
void __fastcall TFin1002::btPesqFornecedorClick(TObject *Sender)
{
	SfgBrowse::EscolheFornecedor(this,&SearchFornecedor);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::SearchFornecedor(Variant Value) {
	cod_fornecedor->Field->Value = Value;
	cod_fornecedorExit(cod_fornecedor);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::btPesqPlanoContaClick(TObject *Sender)
{
	SfgBrowse::EscolhePlanoConta(this,&SearchPlanoConta);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::SearchPlanoConta(Variant Value) {
	cod_plano_conta->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::btPesqCentroCustoClick(TObject *Sender)
{
	SfgBrowse::EscolheCentroCusto(this,&SearchCentroCusto);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::SearchCentroCusto(Variant Value) {
	cod_centro_custo->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::bt_data_cadastroClick(TObject *Sender)
{
	ExecCalendar(data_cadastro);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarBeforePost(TDataSet *DataSet)
{
	QyCadPagto->DataSource = NULL;
	QyContaPagar->AfterScroll = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarAfterPost(TDataSet *DataSet)
{
try {
try {
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (!QyCadPagto->Eof) {
		if (QyCadPagto->FieldByName("cod_conta_pagar")->AsInteger == 0) {
			QyCadPagto->Edit();
			QyCadPagto->FieldByName("cod_conta_pagar")->AsInteger = QyContaPagar->FieldByName("cod_conta_pagar")->AsInteger;
			QyCadPagto->Post();
		}
		QyCadPagto->Next();
	}
	QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	//Inserindo os novos registros de pagamentos
	QyCadPagto->ApplyUpdates();
	QyCadPagto->First();
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	PostStatus = false;
}
}
//Sempre vai passar por aqui, mesmo dando erro
__finally {
	QyCadPagto->DataSource = DsContaPagar;
	QyContaPagar->AfterScroll = &QyContaPagarAfterScroll;
}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarAfterScroll(TDataSet *DataSet)
{
	cod_fornecedorExit(cod_fornecedor);
	UpDwNumParcelas->Position = DataSet->FieldByName("num_parcelas")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::HabilitarItens(bool Habilita)
{
	btPesqPlanoConta->Enabled = Habilita;
	btPesqCentroCusto->Enabled = Habilita;
	btPesqFornecedor->Enabled = Habilita;
	DsContaPagarPagto->AutoEdit = Habilita;
	valor_total->ReadOnly = true;
	valor_total->Color = AppConfig->Colors->Disabled;
	if (Habilita) {
		cod_forma_pagtoChange(cod_forma_pagto);
	} else {
		num_parcelas->Enabled = false;
		num_parcelas->Color = AppConfig->Colors->Disabled;
		UpDwNumParcelas->Invalidate();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::NavegexecBtSaveClickExecute(
		TObject *Sender)
{
	QyContaPagar->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
	PostStatus = true;
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	SfgToolbar->btSaveClick(Sender);
	if (PostStatus) {
		SfgDataCenter->CommitTrans();
		HabilitarItens(false);
	} else {
		SfgDataCenter->RollbackTrans();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::NavegexecBtCancelClickExecute(
      TObject *Sender)
{
	bool edit = (QyContaPagar->State == dsEdit);
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyContaPagarAfterScroll(QyContaPagar);
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CodCentroCustoValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_centro_custo FROM tbl_centro_custo"\
			" WHERE cod_centro_custo = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		throw Exception("Centro de custo não cadastrado!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::CodPlanoContaValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_plano_conta FROM tbl_plano_conta"\
			" WHERE cod_plano_conta = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		throw Exception("Conta contábil não cadastrada no plano de contas!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::btRecContaPagarClick(TObject *Sender)
{
	TFin1004 *Fin1004 = new TFin1004(Application);
   Fin1004->SetPermissao(NivelPerm);
   Fin1004->FilterCodConta(QyContaPagar->FieldByName("cod_conta_pagar")->AsInteger);
   AppDummyMethod = NULL; //Anula o método para não ser chamado indevidamente
	Fin1004->OnClose = &FormContaPagarClose;
	Fin1004->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::FormContaPagarClose(TObject *Sender, TCloseAction &Action)
{
	((TFin1004*)Sender)->FormClose(Sender, Action);
	QySitContaPagar->Refresh();
	QyCadPagto->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarBeforeDelete(TDataSet *DataSet)
{
try {
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	while (QyCadPagto->RecordCount > 0) {
		QyCadPagto->Last();
		QyCadPagto->Delete();
	}
	QyCadPagto->ApplyUpdates();
	QyCadPagto->EnableControls(); //Para ativar a atualização da tela
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao excluir as informações do registro:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	PostStatus = false;
}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::NavegbtDeleteClick(TObject *Sender)
{
	PostStatus = true;
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	SfgToolbar->btDeleteClick(Sender);
	if (PostStatus) {
		SfgDataCenter->CommitTrans();
	} else {
		SfgDataCenter->RollbackTrans();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::cod_forma_pagtoChange(TObject *Sender)
{
	TBDFin1002Object *Obj = (TBDFin1002Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
	if (Obj->ies_parcelado) {
		num_parcelas->Enabled = true;
		num_parcelas->Color = AppConfig->Colors->Enabled;
	} else {
		num_parcelas->Enabled = false;
		num_parcelas->Color = AppConfig->Colors->Disabled;
		UpDwNumParcelas->Position = 1;
		QyCadPagto->DisableControls();  //Para desativar a atualização da tela
		while (QyCadPagto->RecordCount > 1) {
			QyCadPagto->Last();
			QyCadPagto->Delete();
		}
		QyCadPagto->First();
		QyCadPagto->Edit();
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = QyContaPagar->FieldByName("valor_total")->AsFloat;
		QyCadPagto->Post();
		QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	}
	UpDwNumParcelas->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::UpDwNumParcelasClick(TObject *Sender,
      TUDBtnType Button)
{
	if (Button == btNext) {
		//Adiciona uma linha no GRID de parcelas
		QyCadPagto->Last();
		QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual 
		QyCadPagto->Insert();
		QyCadPagto->BeforeInsert = &QyCadPagtoBeforeInsert;
		if (QyContaPagar->State == dsEdit)
			QyCadPagto->FieldByName("cod_conta_pagar")->AsInteger = cod_conta_pagar->Field->AsInteger;
		else
			QyCadPagto->FieldByName("cod_conta_pagar")->AsInteger = 0;
		QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
		QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
		QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("ies_pago")->AsString = "N";
		QyCadPagto->Post();
	} else {
		//Elimina uma linha no GRID de parcelas
		QyCadPagto->Last();
		QyContaPagar->FieldByName("valor_total")->AsFloat -= QyCadPagto->FieldByName("valor_parcela")->AsFloat;
		QyCadPagto->Delete();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyCadPagtoBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdPagtosKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyCadPagtovalor_parcelaSetText(TField *Sender,
		const AnsiString Text)
{
	float v = 0;
	try {
		v = (Text.Length()) ? StrToFloat(Text) : 0;
	}
	__finally {}
	if (v == NULL || v <= 0) {
		MessageBox(Handle,"Informe um valor numérico maior que zero!",Caption.c_str(),APP_INFORM);
	} else {
		QyContaPagar->FieldByName("valor_total")->AsFloat += (v - Sender->AsFloat);
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::EditPagtoSetFocus(TObject *Sender)
{
	if(QyContaPagar->State == dsInsert || QyContaPagar->State == dsEdit) {
		if (grdPagtos->SelectedField->FieldName == "valor_parcela") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdPagtosDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_pago") {
		bool bChecked = QyCadPagto->FieldByName("ies_pago")->AsString == "S";
		DrawCheckBoxGrid(grdPagtos,-1,-1,Rect,State,bChecked);
	} else if (Column->Field->FieldName == "data_vencimento") {
		DrawCalendarGrid(grdPagtos,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdPagtosColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_pago") {
		Options = grdPagtos->Options;
		Options >> dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdPagtosColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_pago") {
		Options = grdPagtos->Options;
		Options << dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::grdPagtosEditButtonClick(TObject *Sender)
{
	TPoint ptGrid;
	TRect rtCell;
	String sDate;
	if (grdPagtos->SelectedField->FieldName == "data_vencimento") {
		ptGrid.x = 0; ptGrid.y = 0;
		ptGrid = grdPagtos->ClientToParent(ptGrid,this);
		THackCustomGrid *pHackGrid = (THackCustomGrid*)grdPagtos;
		rtCell = pHackGrid->CellRect(pHackGrid->Col, pHackGrid->Row);
		rtCell.Left += ptGrid.x;
		rtCell.Top += ptGrid.y + 4;
		rtCell.Right += ptGrid.x;
		rtCell.Bottom += ptGrid.y + 4;
		sDate = ExecCalendarRect(rtCell,grdPagtos->SelectedField->AsString);
		if(sDate.Length() > 0) {
			if(QyContaPagar->State == dsEdit || QyContaPagar->State == dsInsert) {
				if (!(QyCadPagto->State == dsEdit))
					QyCadPagto->Edit();
				grdPagtos->SelectedField->AsString = sDate;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarPostError(TDataSet *DataSet,
      EDatabaseError *E, TDataAction &Action)
{
   PostStatus = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarAfterOpen(TDataSet *DataSet)
{
	QyCadPagto->Active = true;
	QySitContaPagar->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::QyContaPagarBeforeClose(TDataSet *DataSet)
{
	QyCadPagto->Active = false;
	QySitContaPagar->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin1002::execRelatorioExecute(TObject *Sender)
{
	TFin3013 *Fin3013 = new TFin3013(Owner);
	Fin3013->CnsContaPagar->Active = false;
   Fin3013->CnsContaPagar->ParamByName("cod_conta_pagar")->Value = QyContaPagar->FieldByName("cod_conta_pagar")->Value;
	Fin3013->CnsContaPagar->Active = true;
   if(Fin3013->RpRelatBase->PrepareReport(true))
      Fin3013->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------

