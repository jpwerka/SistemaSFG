/*
Módulo: Financeiro
Função: Cadastro Contas à Receber
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
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uFin1005.h"
#include "uFin3012.h"
#include "uSfgFinCustom.h"
#pragma hdrstop
#include "uFin1003.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1003(void) {
   AddAppForm("Fin1003","Contas à Receber",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1003",__classid(TFin1003));
}
#pragma startup RegisterFin1003
//---------------------------------------------------------------------------
__fastcall TFin1003::TFin1003(TComponent* Owner)
	: TfrmBase02(Owner)
{
	CarregarTipoRegistro();
	CarregarSitContaReceber();
	CarregarFormaPagto();
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsContaReceber;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   //Adicionando os eventos customizados dos campos
   QyContaReceber->FieldByName("cod_cliente")->OnValidate = &CodClienteValidate;
   QyContaReceber->FieldByName("cod_plano_conta")->OnValidate = &CodPlanoContaValidate;
   QyContaReceber->FieldByName("cod_centro_custo")->OnValidate = &CodCentroCustoValidate;
	den_cliente->Color = AppConfig->Colors->Disabled;
	ies_situacao->Color = AppConfig->Colors->Disabled;
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdPagtos)->OnEditSetFocus = &EditPagtoSetFocus;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRecContaReceber->Parent = SfgToolbar;
	btRecContaReceber->Top = 6;
	btRecContaReceber->TabOrder = btRelatorio->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btRecContaReceber);
	this->Tolltips->AddToolTip(btRelatorio);
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   if(hSfgFinCustom) {
      SfgFin1003AfterCreate = (PSfgFin1003AfterCreate)GetProcAddress(hSfgFinCustom,"SfgFin1003AfterCreate");
      SfgFin1003AfterValidInsert = (PSfgFin1003AfterValidInsert)GetProcAddress(hSfgFinCustom,"SfgFin1003AfterValidInsert");
      SfgFin1003AfterValidUpdate = (PSfgFin1003AfterValidUpdate)GetProcAddress(hSfgFinCustom,"SfgFin1003AfterValidUpdate");
      if (SfgFin1003AfterCreate)
         SfgFin1003AfterCreate(this);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::AfterCreateFields(TDataSet *DataSet)
{
   //Marcando campo como auto incremento
   QyContaReceber->FieldByName("cod_conta_receber")->AutoGenerateValue = arAutoInc;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::SetPermissao(int Nivel)
{
   NivelPerm = Nivel;
   if (Nivel == APP_PERM_TOTAL)
      return;

   TfrmBase02::SetPermissao(Nivel);
   btRecContaReceber->Left = SfgToolbar->btExit->Left;
   SfgToolbar->btExit->Left += 38;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::FilterCodConta(int CodConta)
{
   SfgToolbar->WhereFilter = "cod_conta_receber = " + IntToStr(CodConta);
   SfgToolbar->OrderByFilter = "";
   SfgToolbar->RefreshQuery();
	btRecContaReceber->Left = 6;
	SfgToolbar->btExit->Left = 44;
	for (int i=0; i < SfgToolbar->ActionList1->ActionCount; i++) {
		TAction *pAction = (TAction*)SfgToolbar->ActionList1->Actions[i];
		pAction->Visible = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::ValidInsert(bool &bValid)
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
   if (SfgFin1003AfterValidInsert != NULL) {
      if (!SfgFin1003AfterValidInsert(this,QyContaReceber)) {
		   bValid = false;
		   PostStatus = false;
		   return;
      }
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   if (SfgFin1003AfterValidUpdate != NULL) {
      if (!SfgFin1003AfterValidUpdate(this,QyContaReceber)) {
		   bValid = false;
		   PostStatus = false;
		   return;
      }
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::ValidDelete(bool &bValid)
{
	String Situacao;
	String TipoDocum;

	TipoDocum = QyContaReceber->FieldByName("tipo_registro")->AsString;
	if (TipoDocum == "PV") { //Pedido de Venda
		MessageBox(Handle,"Conta a receber integrada a partir de um pedido de venda. Exclusão não permitida!",Caption.c_str(),APP_INFORM);
		bValid = false;
      return;
	}
	QySitContaReceber->Refresh();
	Situacao = QySitContaReceber->FieldByName("ies_situacao")->AsString;
	if(Situacao != "P") {
		MessageBox(Handle,"Conta a receber não está mais pendente. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::CarregarSitContaReceber()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Pendente","P");
	ies_situacao->AddItem("Andamento","A");
	ies_situacao->AddItem("Liquidado","L");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::CarregarTipoRegistro()
{
	tipo_registro->Clear();
	tipo_registro->AddItem("Manual","CR");
	tipo_registro->AddItem("Pedido Venda","PV");
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::CarregarFormaPagto()
{
  TBDFin1003Object *Obj;
  TZQuery *QyPagto = new TZQuery(this);
try
{
	QyPagto->SQL->Text = "SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado FROM tbl_forma_pagto WHERE ies_financeiro = 'S'";
	QyPagto->Connection = AppConnection;
	QyPagto->Active = true;
	cod_forma_pagto->Clear();
	while(!QyPagto->Eof) {
		Obj = new TBDFin1003Object();
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
void __fastcall TFin1003::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
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
bool __fastcall TFin1003::VerificaCampos()
{
	bool bPagto = false;
	if(!num_documento->Text.Length()) {
		MessageBox(Handle, "Digite o número do documento referente a conta a receber!",Caption.c_str(),APP_ATENTION);
		num_documento->SetFocus();
		return false;
	}
	if(!cod_cliente->Text.Length()) {
		MessageBox(Handle, "Digite o código do cliente que representa o devedor da conta a receber!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
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
bool __fastcall TFin1003::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::CodClienteValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		throw Exception("Cliente não cadastrado!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::NavegexecBtEditClickExecute(TObject *Sender)
{
	String Situacao;
	String TipoDocum;

	TipoDocum = QyContaReceber->FieldByName("tipo_registro")->AsString;
	if (TipoDocum == "PV") { //Pedido de Venda
		MessageBox(Handle,"Conta a receber integrada a partir de um pedido de venda. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	QySitContaReceber->Refresh();
	Situacao = QySitContaReceber->FieldByName("ies_situacao")->AsString;
	if(Situacao != "P") {
		MessageBox(Handle,"Conta a receber não está mais pendente. Modificação não permitida!",Caption.c_str(),APP_ATENTION);
		return;
	}
	SfgToolbar->btEditClick(Sender);
	HabilitarItens(true);
	QyContaReceber->FieldByName("ies_situacao")->AsString = Situacao;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::NavegexecBtNewClickExecute(TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	data_cadastro->Field->Value = Now();
	QyContaReceber->FieldByName("ies_situacao")->AsString = "P";
	QyContaReceber->FieldByName("tipo_registro")->AsString = "CR";
	cod_forma_pagto->ItemIndex = 0;
	cod_forma_pagto->Field->Value = cod_forma_pagto->Value;
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyCadPagtoBeforeInsert;
	QyCadPagto->FieldByName("cod_conta_receber")->AsInteger = 0;
	QyCadPagto->FieldByName("seq_parcela")->AsInteger = 1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_recebido")->AsString = "N";
	QyCadPagto->Post();
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::cod_clienteExit(TObject *Sender)
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
void __fastcall TFin1003::btPesqClienteClick(TObject *Sender)
{
	SfgBrowse::EscolheCliente(this,&SearchCliente);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::SearchCliente(Variant Value) {
	cod_cliente->Field->Value = Value;
	cod_clienteExit(cod_cliente);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::btPesqPlanoContaClick(TObject *Sender)
{
	SfgBrowse::EscolhePlanoConta(this,&SearchPlanoConta);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::SearchPlanoConta(Variant Value) {
	cod_plano_conta->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::btPesqCentroCustoClick(TObject *Sender)
{
	SfgBrowse::EscolheCentroCusto(this,&SearchCentroCusto);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::SearchCentroCusto(Variant Value) {
	cod_centro_custo->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::bt_data_cadastroClick(TObject *Sender)
{
	ExecCalendar(data_cadastro);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberBeforePost(TDataSet *DataSet)
{
	QyCadPagto->DataSource = NULL;
	QyContaReceber->AfterScroll = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberAfterPost(TDataSet *DataSet)
{
try {
try {
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (!QyCadPagto->Eof) {
		if (QyCadPagto->FieldByName("cod_conta_receber")->AsInteger == 0) {
			QyCadPagto->Edit();
			QyCadPagto->FieldByName("cod_conta_receber")->AsInteger = QyContaReceber->FieldByName("cod_conta_receber")->AsInteger;
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
	QyCadPagto->DataSource = DsContaReceber;
	QyContaReceber->AfterScroll = &QyContaReceberAfterScroll;
}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberAfterScroll(TDataSet *DataSet)
{
	cod_clienteExit(cod_cliente);
	UpDwNumParcelas->Position = DataSet->FieldByName("num_parcelas")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::HabilitarItens(bool Habilita)
{
	btPesqPlanoConta->Enabled = Habilita;
	btPesqCentroCusto->Enabled = Habilita;
	btPesqCliente->Enabled = Habilita;
	DsContaReceberPagto->AutoEdit = Habilita;
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
void __fastcall TFin1003::NavegexecBtSaveClickExecute(
		TObject *Sender)
{
	QyContaReceber->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
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
void __fastcall TFin1003::NavegexecBtCancelClickExecute(
      TObject *Sender)
{
	bool edit = (QyContaReceber->State == dsEdit);
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyContaReceberAfterScroll(QyContaReceber);
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::CodCentroCustoValidate(TField *Sender)
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
void __fastcall TFin1003::CodPlanoContaValidate(TField *Sender)
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
void __fastcall TFin1003::btRecContaReceberClick(TObject *Sender)
{
	TFin1005 *Fin1005 = new TFin1005(Application);
   Fin1005->SetPermissao(NivelPerm);
   Fin1005->FilterCodConta(QyContaReceber->FieldByName("cod_conta_receber")->AsInteger);
   AppDummyMethod = NULL; //Anula o método para não ser chamado indevidamente
	Fin1005->OnClose = &FormContaReceberClose; 
	Fin1005->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::FormContaReceberClose(TObject *Sender, TCloseAction &Action)
{
	((TFin1005*)Sender)->FormClose(Sender, Action);
	QySitContaReceber->Refresh();
	QyCadPagto->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberBeforeDelete(TDataSet *DataSet)
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
void __fastcall TFin1003::NavegbtDeleteClick(TObject *Sender)
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
void __fastcall TFin1003::cod_forma_pagtoChange(TObject *Sender)
{
	TBDFin1003Object *Obj = (TBDFin1003Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = QyContaReceber->FieldByName("valor_total")->AsFloat;
		QyCadPagto->Post();
		QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	}
	UpDwNumParcelas->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::UpDwNumParcelasClick(TObject *Sender,
      TUDBtnType Button)
{
	if (Button == btNext) {
		//Adiciona uma linha no GRID de parcelas
		QyCadPagto->Last();
		QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual 
		QyCadPagto->Insert();
		QyCadPagto->BeforeInsert = &QyCadPagtoBeforeInsert;
		if (QyContaReceber->State == dsEdit)
			QyCadPagto->FieldByName("cod_conta_receber")->AsInteger = cod_conta_receber->Field->AsInteger;
		else
			QyCadPagto->FieldByName("cod_conta_receber")->AsInteger = 0;
		QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
		QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
		QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("ies_recebido")->AsString = "N";
		QyCadPagto->Post();
	} else {
		//Elimina uma linha no GRID de parcelas
		QyCadPagto->Last();
		QyContaReceber->FieldByName("valor_total")->AsFloat -= QyCadPagto->FieldByName("valor_parcela")->AsFloat;
		QyCadPagto->Delete();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyCadPagtoBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdPagtosKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyCadPagtovalor_parcelaSetText(TField *Sender,
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
		QyContaReceber->FieldByName("valor_total")->AsFloat += (v - Sender->AsFloat);
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::EditPagtoSetFocus(TObject *Sender)
{
	if(QyContaReceber->State == dsInsert || QyContaReceber->State == dsEdit) {
		if (grdPagtos->SelectedField->FieldName == "valor_parcela") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdPagtosDrawColumnCell(TObject *Sender,
		const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_recebido") {
		bool bChecked = QyCadPagto->FieldByName("ies_recebido")->AsString == "S";
		DrawCheckBoxGrid(grdPagtos,-1,-1,Rect,State,bChecked);
	} else if (Column->Field->FieldName == "data_vencimento") {
		DrawCalendarGrid(grdPagtos,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdPagtosColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_recebido") {
		Options = grdPagtos->Options;
		Options >> dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdPagtosColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_recebido") {
		Options = grdPagtos->Options;
		Options << dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::grdPagtosEditButtonClick(TObject *Sender)
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
			if(QyContaReceber->State == dsEdit || QyContaReceber->State == dsInsert) {
				if (!(QyCadPagto->State == dsEdit))
					QyCadPagto->Edit();
				grdPagtos->SelectedField->AsString = sDate;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberPostError(TDataSet *DataSet,
      EDatabaseError *E, TDataAction &Action)
{
   PostStatus = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberAfterOpen(TDataSet *DataSet)
{
	QyCadPagto->Active = true;
	QySitContaReceber->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::QyContaReceberBeforeClose(TDataSet *DataSet)
{
	QyCadPagto->Active = false;
	QySitContaReceber->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFin1003::execRelatorioExecute(TObject *Sender)
{
	TFin3012 *Fin3012 = new TFin3012(Owner);
	Fin3012->CnsContaReceber->Active = false;
   Fin3012->CnsContaReceber->ParamByName("cod_conta_receber")->Value = QyContaReceber->FieldByName("cod_conta_receber")->Value;
	Fin3012->CnsContaReceber->Active = true;
   if(Fin3012->RpRelatBase->PrepareReport(true))
      Fin3012->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------


