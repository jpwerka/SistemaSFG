/*
Módulo: Vendas - Representantes
Função: Cadastro Representantes x Comissão
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#include "uDataModule.h"
#include "uVdp3008.h"
#pragma hdrstop
#include "uVdp1024.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1024(void) {
   AddAppForm("Vdp1024","Representantes x Comissão",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1024",__classid(TVdp1024));
}
#pragma startup RegisterVdp1024
//---------------------------------------------------------------------------
__fastcall TVdp1024::TVdp1024(TComponent* Owner)
   : TfrmBase02(Owner)
{
	CarregarTipoPessoa();
	SfgToolbar->DataSource = DsRepresentantes;
   UpDownAno->Position = YearOf(Date());
   mes_comissao->ItemIndex = MonthOf(Date()) - 2; //Para pegar o mês anterior
   UpDownMes->Position = mes_comissao->ItemIndex;
   //Força os botões a pertencerem a SfgToolbar
	btFechamento->Parent = SfgToolbar;
	btFechamento->Top = 6;
	btFechamento->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = btFechamento->TabOrder + 1;
	btParFormaPagto->Parent = SfgToolbar;
	btParFormaPagto->Top = 6;
	btParFormaPagto->TabOrder = btRelatorio->TabOrder + 1;
	valor_total->ReadOnly = true;
	valor_total->Color = AppConfig->Colors->Disabled;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btFechamento);
	this->Tolltips->AddToolTip(btRelatorio);
	this->Tolltips->AddToolTip(btParFormaPagto);
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdReprComissao)->OnEditSetFocus = &EditItemSetFocus;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   SfgToolbar->execBtEditClick->Visible = false;
   SfgToolbar->execBtEditClick->Enabled = false;
   SfgToolbar->execBtSaveClick->Visible = false;
   SfgToolbar->execBtSaveClick->Enabled = false;
   SfgToolbar->execBtCancelClick->Visible = false;
   SfgToolbar->execBtCancelClick->Enabled = false;
   SfgToolbar->execBtDeleteClick->Visible = false;
   SfgToolbar->execBtDeleteClick->Enabled = false;
   execFechamento->Visible = false;
   execFechamento->Enabled = false;
   execParFormaPagto->Visible = false;
   execParFormaPagto->Enabled = false;
   SfgToolbar->btExit->Left = SfgToolbar->btEdit->Left;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::CarregarTipoPessoa()
{
   tipo_pessoa->Clear();
   tipo_pessoa->AddItem("Pessoa Física","F");
   tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::HabilitarItens(bool Habilita)
{
   TDBGridOptions DbOptions = grdReprComissao->Options;
   if (Habilita && (QyReprComissao->FieldByName("cod_conta_pagar")->AsFloat == 0))
      DbOptions << dgEditing;
   else
      DbOptions >> dgEditing;
   //Deve habilitar o GRID para fazer edição
   DsReprComissao->AutoEdit = Habilita;
   grdReprComissao->Options = DbOptions;
   SfgToolbar->EnableToolbarButtons(!Habilita);
   execParFormaPagto->Enabled = !Habilita;
   delLine->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::QyRepresentantesAfterScroll(TDataSet *DataSet)
{
   //Aqui deve carregar os valores das comissões do cliente
   QyReprComissao->Active = false;
   QyReprComissao->ParamByName("cod_representante")->Value = QyRepresentantes->FieldByName("cod_representante")->Value;
   QyReprComissao->ParamByName("mes_comissao")->Value = mes_comissao->ItemIndex + 1;
   QyReprComissao->ParamByName("ano_comissao")->Value = ano_comissao->Text;
   QyReprComissao->Active = true;
   QySumComissao->Active = false;
   QySumComissao->ParamByName("cod_representante")->Value = QyRepresentantes->FieldByName("cod_representante")->Value;
   QySumComissao->ParamByName("mes_comissao")->Value = mes_comissao->ItemIndex + 1;
   QySumComissao->ParamByName("ano_comissao")->Value = ano_comissao->Text;
   QySumComissao->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::mes_comissaoChange(TObject *Sender)
{
   UpDownMes->Position = mes_comissao->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::ano_comissaoChange(TObject *Sender)
{
   if(QyRepresentantes->Active)
      QyRepresentantesAfterScroll(QyRepresentantes);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::grdReprComissaoKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::QyReprComissaoBeforeInsert(TDataSet *DataSet)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::SfgToolbarexecBtEditClickExecute(TObject *Sender)
{
   HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::SfgToolbarexecBtSaveClickExecute(TObject *Sender)
{
   String sMsg;
   bool bSucesso = true;
   //Deve salvar as alterações no GRID
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	try {
		QyReprComissao->ApplyUpdates();
	}
	catch(Exception &e){
		sMsg = "Ocorreu um erro ao salvar as alterações nas comissões do representante:\n";
		sMsg = sMsg + e.Message;
		bSucesso = false;
	}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
   HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::SfgToolbarexecBtCancelClickExecute(TObject *Sender)
{
   HabilitarItens(false);
   QyReprComissao->CancelUpdates();
   QySumComissao->CancelUpdates();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::SfgToolbarexecBtDeleteClickExecute(TObject *Sender)
{
   //Deve perguntar se deseja excluir todos os registros do mês
	String sSQL, sMsg;
   TZQuery *DelComissao;
   bool bSucesso = true;

   if (MessageBox(Handle,"Confirma a exclusão de todos os lançamentos de comissão?",Caption.c_str(),APP_QUESTION) == IDNO)
      return;

   //Deve verificar se por acaso já não feito o lançamento no contas a pagar das comissões
   sSQL = "SELECT DISTINCT 1 FROM tbl_comissao_representante";
   sSQL += " WHERE cod_representante = " + QuotedStr(cod_representante->Text);
   sSQL += " AND mes_comissao = " + IntToStr(mes_comissao->ItemIndex+1);
   sSQL += " AND ano_comissao = " + ano_comissao->Text;
   sSQL += " AND cod_conta_pagar IS NOT NULL";
   if (ValidacoesDB::ExisteForeingKey(AppConnection, sSQL)) {
      MessageBox(Handle,"Existem comissões já lançadas no contas a pagar!",Caption.c_str(),APP_INFORM);
      return;
   }

   sSQL = "DELETE FROM tbl_comissao_representante";
   sSQL += " WHERE cod_representante = " + QuotedStr(cod_representante->Text);
   sSQL += " AND mes_comissao = " + IntToStr(mes_comissao->ItemIndex+1);
   sSQL += " AND ano_comissao = " + ano_comissao->Text;

   DelComissao = new TZQuery(this);
	DelComissao->SQL->Text = sSQL;
	DelComissao->Connection = AppConnection;

   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	try {
		DelComissao->ExecSQL();
	}
	catch(Exception &e){
		sMsg = "Ocorreu um erro ao excluir as comissões do representante:\n";
		sMsg = sMsg + e.Message;
		bSucesso = false;
	}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
      QyReprComissao->Refresh();
      QySumComissao->Refresh();
		MessageBox(Handle,"Comissão do representante excluída com sucesso!", Caption.c_str(), APP_INFORM);
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::execFechamentoExecute(TObject *Sender)
{
   String sSQL, sMsg;
   bool bSucesso = true;
   //Deve integrar com o contas a pagar gerando um lançamento
   //Para isto deve verificar se o representante está cadastrado como um fornecedor
	sSQL = "SELECT cod_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_representante->Text);
	if (!ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		MessageBox(Handle, "Representante não cadastrado como fornecedor!",Caption.c_str(),APP_ATENTION);
		return;
	}

   sSQL = "CALL fecha_comissao_representante("+ QuotedStr(cod_representante->Text);
   sSQL += "," + IntToStr(mes_comissao->ItemIndex+1) + "," + ano_comissao->Text;
   sSQL += "," + QuotedStr(AppUser->Usuario) + ")";

   TZQuery *IntegraComissao = new TZQuery(this);
	IntegraComissao->SQL->Text = sSQL;
	IntegraComissao->Connection = AppConnection;

   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	try {
		IntegraComissao->ExecSQL();
	}
	catch(Exception &e){
		sMsg = "Ocorreu um erro ao integrar as comissões do representante:\n";
		sMsg = sMsg + e.Message;
		bSucesso = false;
	}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
      QyReprComissao->Refresh();
		MessageBox(Handle,"Comissões do representante integradas com o contas a pagar com sucesso!", Caption.c_str(), APP_INFORM);
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::delLineExecute(TObject *Sender)
{
   String sSQL;

   if (MessageBox(Handle,"Confirma a exclusão deste lançamento de comissão?",Caption.c_str(),APP_QUESTION) == IDNO)
      return;

   if (QyReprComissao->RecordCount > 0) {
      //Deve verificar se por acaso já não feito o lançamento no contas a pagar da comissão
      sSQL = "SELECT DISTINCT 1 FROM tbl_comissao_representante";
      sSQL += " WHERE cod_representante = " + QuotedStr(cod_representante->Text);
      sSQL += " AND cod_pedido_venda = " + QyReprComissao->FieldByName("cod_pedido_venda")->AsString;
      sSQL += " AND seq_parcela = " + QyReprComissao->FieldByName("seq_parcela")->AsString;
      sSQL += " AND cod_conta_pagar IS NOT NULL";
      if (ValidacoesDB::ExisteForeingKey(AppConnection, sSQL)) {
         MessageBox(Handle,"Comissão já lançada no contas a pagar!",Caption.c_str(),APP_INFORM);
         return;
      }
      QyReprComissao->Delete();
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::UpDownMesChangingEx(TObject *Sender,
      bool &AllowChange, short NewValue, TUpDownDirection Direction)
{
	short ValueMes = NewValue;
   //Desabilita o evento de change do ano
   ano_comissao->OnChange = NULL;
	if(ValueMes == 12) {
		NewValue = 0;
		UpDownAno->Position++;
      UpDownMes->Position = 0;
      AllowChange = false;
	}
	if(ValueMes == -1) {
		NewValue = 11;
		UpDownAno->Position--;
      UpDownMes->Position = 11;
      AllowChange = false;
	}
	mes_comissao->ItemIndex = NewValue;
   if (AllowChange)
      QyRepresentantesAfterScroll(QyRepresentantes);
   ano_comissao->OnChange = &ano_comissaoChange;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::EditItemSetFocus(TObject *Sender)
{
	if (grdReprComissao->SelectedField->FieldName == "valor_comissao") {
		((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
	} else {
		((TEdit*)Sender)->OnKeyPress = NULL;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::execParFormaPagtoExecute(TObject *Sender)
{
   pFormPgto = new TForm(Application);
   pFormPgto->BorderStyle = bsDialog;
   pFormPgto->BorderIcons = TBorderIcons() << biSystemMenu;
   pFormPgto->Caption = "Forma pagamento";
   pFormPgto->Position = poDesktopCenter;
   pFormPgto->ClientHeight = 68;
   pFormPgto->ClientWidth = 185;
   TLabel *pLabel = new TLabel(pFormPgto);
   pLabel->Parent = pFormPgto;
   pLabel->Caption = "&Forma pagamento:";
   pLabel->SetBounds(10,12,88,13);
   pEdtPgto = new TAlignEdit(pFormPgto);
   pEdtPgto->Parent = pFormPgto;
   pEdtPgto->Alignment = taRightJustify;
   pEdtPgto->SetBounds(105,8,70,21);
	SetWindowLong(pEdtPgto->Handle, GWL_STYLE, GetWindowLong(pEdtPgto->Handle, GWL_STYLE) | ES_NUMBER);
   pLabel->FocusControl = pEdtPgto;
   TButton *pBtOK = new TButton(pFormPgto);
   pBtOK->Parent = pFormPgto;
   pBtOK->Caption = "&OK";
   pBtOK->Default = true;
   //pBtOK->ModalResult = mrOk;
   pBtOK->OnClick = &BtOKClick;
   pBtOK->SetBounds(13,38,75,22);
   TButton *pBtCancel = new TButton(pFormPgto);
   pBtCancel->Parent = pFormPgto;
   pBtCancel->Caption = "&Cancelar";
   pBtCancel->Cancel = true;
   pBtCancel->ModalResult = mrCancel;
   pBtCancel->SetBounds(97,38,75,22);
   pEdtPgto->Text = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_numero('forma_pagto_comissao');"));
   pFormPgto->ShowModal();
   delete pFormPgto;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::BtOKClick(TObject *Sender)
{
   String sSQL;

   if (pEdtPgto->Text.Length() == 0) {
      MessageBox(NULL,"Informe o código da forma de pagamento para integração das comissões.","Forma pagamento",APP_ATENTION);
      return;
   }
   sSQL = "CALL set_parametro_numero('forma_pagto_comissao'," + pEdtPgto->Text + ",'" + AppUser->Usuario + "');";
   if (ValidacoesDB::SetParamValue(AppConnection,sSQL)) {
      pFormPgto->ModalResult = mrOk;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::QyReprComissaoAfterScroll(TDataSet *DataSet)
{
   TDBGridOptions DbOptions = grdReprComissao->Options;
   if (QyReprComissao->FieldByName("cod_conta_pagar")->AsFloat > 0)
      DbOptions >> dgEditing;
   else
      DbOptions << dgEditing;
   grdReprComissao->Options = DbOptions;

}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::ValorComissaoSetText(TField *Sender,
      const AnsiString Text)
{
	//Deve recalcular o valor total do item e do pedido
	float fValor = 0;
	try {
		fValor = (Text.Length()) ? StrToFloat(Text) : 0;
	}
	__finally {}
	if (fValor == NULL) {
		fValor = 0;
   }
	if(fValor < 0) {
		MessageBox(Handle,"Informe um valor numérico maior ou igual a zero!",Caption.c_str(),APP_ATENTION);
		return;
   } else {
      QySumComissao->Edit();
      QySumComissao->FieldByName("valor_comissao")->AsFloat +=
		(fValor - QyReprComissao->FieldByName("valor_comissao")->AsFloat);
      QySumComissao->Post();
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1024::execRelatorioExecute(TObject *Sender)
{
	TVdp3008 *Vdp3008 = new TVdp3008(Owner);
	Vdp3008->CnsReprComissao->Active = false;
   Vdp3008->CnsReprComissao->ParamByName("cod_representante")->Value = QyRepresentantes->FieldByName("cod_representante")->Value;
   Vdp3008->CnsReprComissao->ParamByName("mes_comissao")->Value = mes_comissao->ItemIndex + 1;
   Vdp3008->CnsReprComissao->ParamByName("ano_comissao")->Value = ano_comissao->Text;
	Vdp3008->CnsReprComissao->Active = true;
   if(Vdp3008->RpRelatBase->PrepareReport(true))
      Vdp3008->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------


