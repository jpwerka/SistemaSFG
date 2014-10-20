/*
Módulo: Compras
Função: Cadastro Pedidos de Compra
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
#include "uSfgWorkEdition.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uSfgBrowseSup.h"
#include "uSfgBrowseFin.h"
#include "uSup1004.h"
#include "uSup3001.h"
#include "uSup1002.h"
#include "uSup1003.h"
#pragma hdrstop
#include "uSup1001.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup1001(void) {
   AddAppForm("Sup1001","Pedidos de Compra",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup1001",__classid(TSup1001));
}
#pragma startup RegisterSup1001
//---------------------------------------------------------------------------
__fastcall TSup1001::TSup1001(TComponent* Owner)
	: TfrmBase02(Owner)
{
	CarregarSitPedidoCompra();
	CarregarFormaPagto();
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsCadCompra;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   //Adicionando os eventos customizados dos campos
   QyCadCompra->FieldByName("cod_fornecedor")->OnValidate = &CodFornecedorValidate;
   QyCadCompra->FieldByName("cod_plano_conta")->OnValidate = &CodPlanoContaValidate;
   QyCadCompra->FieldByName("cod_centro_custo")->OnValidate = &CodCentroCustoValidate;
	HabilitarItens(false);
	ies_situacao->Color = AppConfig->Colors->Disabled;
	den_fornecedor->Color = AppConfig->Colors->Disabled;
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdItens)->OnEditSetFocus = &EditItemSetFocus;
	((TThemeDBGrid*)grdPagtos)->OnEditSetFocus = &EditPagtoSetFocus;
	TStrings *pStrings = SfgToolbar->WorkEdition->ListControls;
	pStrings->Delete(pStrings->IndexOf("valor_total"));
	pStrings->Delete(pStrings->IndexOf("pagto_total"));
	valor_total->ReadOnly = true;
	valor_total->Color = AppConfig->Colors->Disabled;
	pagto_total->ReadOnly = true;
	pagto_total->Color = AppConfig->Colors->Disabled;
   this->WindowProc = &SubClassWndProc;
	//Força os botões pertencerem ao SfgToolbar
	btEnviarPedido->Parent = SfgToolbar;
	btEnviarPedido->Top = 6;
	btEnviarPedido->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRecebePedido->Parent = SfgToolbar;
	btRecebePedido->Top = 6;
	btRecebePedido->TabOrder = btEnviarPedido->TabOrder + 1;
	btFechamento->Parent = SfgToolbar;
	btFechamento->Top = 6;
	btFechamento->TabOrder = btRecebePedido->TabOrder + 1;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = btFechamento->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btEnviarPedido);
	this->Tolltips->AddToolTip(btRecebePedido);
	this->Tolltips->AddToolTip(btFechamento);
	this->Tolltips->AddToolTip(btRelatorio);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::AfterCreateFields(TDataSet *DataSet)
{
   //Adicionando o campo virtual na tabela
	DynamicArray<String> FieldDefs;
	FieldDefs.Length = 1;
	FieldDefs[0] = "fkCalculated|pagto_total|ftFloat|0|Pagto Total";
   AddVirtualFields(FieldDefs,QyCadCompra,true);
   ((TFloatField*)QyCadCompra->FieldByName("pagto_total"))->currency = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   TfrmBase02::SetPermissao(Nivel);
   //Escondendo as opções de menu do SfgToolbar
	execRecebimento->Visible = false;
	execEnviaPedido->Visible = false;
	execFechamento->Visible = false;
   //Desabilitando as teclas de atalho também
	execRecebimento->Enabled = false;
	execEnviaPedido->Enabled = false;
	execFechamento->Enabled = false;
   btRelatorio->Left = SfgToolbar->btExit->Left;
   SfgToolbar->btExit->Left += 38;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::FilterCodCompra(int CodCompra)
{
   SfgToolbar->WhereFilter = "cod_pedido_compra = " + IntToStr(CodCompra);
   SfgToolbar->OrderByFilter = "";
   SfgToolbar->RefreshQuery();
	SfgToolbar->btExit->Left = 6;
	for (int i=0; i < SfgToolbar->ActionList1->ActionCount; i++) {
		TAction *pAction = (TAction*)SfgToolbar->ActionList1->Actions[i];
		pAction->Visible = false;
		pAction->Enabled = false;
	}
	for (int i=0; i < ActionList1->ActionCount; i++) {
		TAction *pAction = (TAction*)ActionList1->Actions[i];
		pAction->Visible = false;
		pAction->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SubClassWndProc(Messages::TMessage &Message)
{
   if (Message.Msg == WM_SFGEXECPARAM) {
      //Trata as possibilidades de executar este programa por parâmetros
      if (Message.WParam == 1) {//Opção de execussão da função de filtro
         this->FilterCodCompra(Message.LParam);
      } else if (Message.WParam == 2) { //Opção de execussão de inclusão de novo registro
         this->SfgToolbar->btNew->Click();
      }
      Message.Result = 1;
   } else {
      this->WndProc(Message);
   }

}
//---------------------------------------------------------------------------
void __fastcall TSup1001::ValidInsert(bool &bValid)
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
void __fastcall TSup1001::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::ValidDelete(bool &bValid)
{
	String SQL;
	String Situacao;
	QySitPedidoCompra->Refresh();
	Situacao = QySitPedidoCompra->FieldByName("ies_situacao")->AsString;
	if(Situacao != "A") {
		MessageBox(Handle, "Pedido de compra diferente de aberto. Não pode ser excluído!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		PostStatus = false;
		return;
	}
	/*SQL = "SELECT DISTINCT 1 FROM tbl_orcamento_produto" \
			" WHERE cod_orcamento = " + QuotedStr(cod_orcamento->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Compra possui produtos já relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}*/
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CarregarSitPedidoCompra()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Aberto","A");
	ies_situacao->AddItem("Enviado","E");
	ies_situacao->AddItem("Recebido","R");
	ies_situacao->AddItem("Fechado","F");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CarregarFormaPagto()
{
  TBDSup1001Object *Obj;
  TZQuery *QyPagto = new TZQuery(this);
try
{
	QyPagto->SQL->Text = "SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado, ies_financeiro FROM tbl_forma_pagto";
	QyPagto->Connection = AppConnection;
	QyPagto->Active = true;
	cod_forma_pagto->Clear();
	while(!QyPagto->Eof) {
		Obj = new TBDSup1001Object();
		Obj->SetValue(QyPagto->FieldByName("cod_forma_pagto")->Value);
		Obj->ies_parcelado = (bool)(QyPagto->FieldByName("ies_parcelado")->AsString == "S");
		Obj->ies_financeiro = (bool)(QyPagto->FieldByName("ies_financeiro")->AsString == "S");
		cod_forma_pagto->AddItem(QyPagto->FieldByName("den_forma_pagto")->AsString, (TObject*)Obj);
		QyPagto->Next();
  }
}__finally{delete(QyPagto);}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "ies_situacao") {
      ComboBox->Clear();
      ComboBox->Items->Assign(ies_situacao->Items);
   } else
   if (Filter->Field->FieldName == "cod_forma_pagto") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_forma_pagto->Items);
   }
}
//---------------------------------------------------------------------------
bool __fastcall TSup1001::VerificaCampos()
{
	bool bItem = false;
	bool bPagto = false;
	if(!cod_fornecedor->Text.Length()) {
		MessageBox(Handle, "Digite o código do fornecedor do pedido de compra!",Caption.c_str(),APP_ATENTION);
		cod_fornecedor->SetFocus();
		return false;
	}
	if(!data_recebimento->Text.Length()) {
		MessageBox(Handle, "Digite a data de recebimento do pedido de compra!",Caption.c_str(),APP_ATENTION);
		data_recebimento->SetFocus();
		return false;
	}
	if (RoundTo(valor_total->Field->AsFloat,-3) != RoundTo(pagto_total->Field->AsFloat,-3)) {
		MessageBox(Handle, "Valor total dos itens difere do valor de pagamento total do pedido de compra!",Caption.c_str(),APP_ATENTION);
		return false;
	}
	//Validando inserção dos novos registros de itens
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	QyCadProduto->First();
	while (!QyCadProduto->Eof) {
		if (VarIsNull(QyCadProduto->FieldByName("cod_produto")->Value)) {
			MessageBox(Handle, "Informe o código do item!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 0;
			grdItens->SetFocus();
			grdItens->SelectedField = QyCadProduto->FieldByName("cod_produtos");
			QyCadProduto->EnableControls(); //Para ativar a atualização da tela
			return false;
		}
		if (QyCadProduto->FieldByName("qtd_produto")->AsFloat <= 0) {
			MessageBox(Handle, "Informe uma quantidade maior que zero!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 0;
			grdItens->SetFocus();
			grdItens->SelectedField = QyCadProduto->FieldByName("qtd_produto");
			QyCadProduto->EnableControls(); //Para ativar a atualização da tela
			return false;
		}
		QyCadProduto->Next();
		bItem = true;
	}
	QyCadProduto->EnableControls(); //Para ativar a atualização da tela
	if (!bItem) {
		MessageBox(Handle, "Informe pelo menos um item para o pedido de compra!",Caption.c_str(),APP_ATENTION);
		return false;
	}
	//Validando a inserção dos novos registros de pagamentos
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (!QyCadPagto->Eof) {
		if (QyCadPagto->FieldByName("valor_parcela")->AsFloat <= 0) {
			MessageBox(Handle, "Informe um valor da parcela maior que zero!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 2;
			grdPagtos->SetFocus();
			grdPagtos->SelectedField = QyCadPagto->FieldByName("valor_parcela");
			QyCadPagto->EnableControls(); //Para ativar a atualização da tela
			return false;
		}
		if (VarIsNull(QyCadPagto->FieldByName("data_vencimento")->Value)) {
			MessageBox(Handle, "Informe a data de vencimento da parcela!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 2;
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
		MessageBox(Handle, "Informe pelo menos uma parcela para pagamento!",Caption.c_str(),APP_ATENTION);
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSup1001::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SearchFornecedor(Variant Value) {
	cod_fornecedor->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CodFornecedorValidate(TField *Sender)
{
	String sSQL;
	String sRet;
	if(!Sender->AsString.Length()) {
		den_fornecedor->Text = "";
		return;
	}
	sSQL = "SELECT den_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(Sender->AsString);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,sSQL);
	if(sRet.Length() <= 0) {
		den_fornecedor->Text = "";
		throw Exception("Fornecedor não cadastrado!");
	} else {
		den_fornecedor->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_cadastro);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_recebimento);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::NavegexecBtEditClickExecute(TObject *Sender)
{
	String Situacao;
	bool altera = false;
	QySitPedidoCompra->Refresh();
	Situacao = QySitPedidoCompra->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F" || Situacao == "R" || Situacao == "E") {
		if (MessageBox(Handle, "Pedido de compra diferente de aberto. Deseja realmente alterar o mesmo?\nEsta ação irá alterar a situação do mesmo para aberto.",Caption.c_str(),APP_QUESTION)==ID_YES) {
			altera = true;
		} else {
			return;
		}
	} else if(Situacao == "C") {
		MessageBox(Handle,"Pedido de compra cancelado. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	if (altera && Situacao == "F") { //Deve estornar o fechamento do pedido
		TZReadOnlyQuery *QyFechaPedido = new TZReadOnlyQuery(Application);
		QyFechaPedido->Connection = AppConnection;
	try {
		if (!SfgDataCenter->StartTrans()) {
		   MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
         return;
      }
		//Reabre o pedido de compra
		//Excluindo os itens no estoque
		//Excluindo o registro da conta a pagar
		QyFechaPedido->SQL->Text = "CALL reabre_pedido_compra("+ cod_pedido_compra->Text +");";
		QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
		SfgDataCenter->CommitTrans();
		delete QyFechaPedido;
	} catch(Exception &e){
		SfgDataCenter->RollbackTrans();
		String Msg = "Ocorreu o seguinte erro ao reabrir o pedido de compra:\n";
		Msg = Msg + e.Message;
		MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
		delete QyFechaPedido;
		return;
	}
	}
	QySitPedidoCompra->Refresh();
	SfgToolbar->btEditClick(Sender);
	if (altera) {
		QyCadCompra->FieldByName("ies_situacao")->AsString = "A";
	}
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::NavegexecBtSaveClickExecute(TObject *Sender)
{
	QyCadCompra->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
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
void __fastcall TSup1001::NavegexecBtCancelClickExecute(TObject *Sender)
{
	bool edit = (QyCadCompra->State == dsEdit);
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyCadCompraAfterScroll(QyCadCompra);
	HabilitarItens(false);
   MsgDifTotalPagto->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::NavegexecBtNewClickExecute(TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	QyCadCompra->FieldByName("data_cadastro")->Value = Now();
	QyCadCompra->FieldByName("ies_situacao")->Value = "A";
	cod_forma_pagto->ItemIndex = 0;
	cod_forma_pagto->Field->Value = cod_forma_pagto->Value;
	//Adiciona uma linha no GRID de itens
	//addLineExecute(Sender);
	//Adiciona uma linha no GRID de parcelas
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
	QyCadPagto->FieldByName("cod_pedido_compra")->AsInteger = 0;
	QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_pago")->AsString = "N";
	QyCadPagto->Post();
	HabilitarItens(true);
	data_cadastro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::NavegexecBtDeleteClickExecute(TObject *Sender)
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
void __fastcall TSup1001::HabilitarItens(bool Habilita)
{
   bool bRegistro = QyCadCompra->Active && QyCadCompra->RecordCount > 0;
	execEnviaPedido->Enabled = !Habilita && bRegistro;
	execRecebimento->Enabled = !Habilita && bRegistro;
	execFechamento->Enabled = !Habilita && bRegistro;
	execRelatorio->Enabled = !Habilita && bRegistro;
	btPesqPlanoConta->Enabled = Habilita;
	btPesqCentroCusto->Enabled = Habilita;
	btPesqFornecedor->Enabled = Habilita;
	//Habilitando os itens do GRID de itens
	DsCadProduto->AutoEdit = Habilita;
	addLine->Enabled = Habilita;
	delLine->Enabled = Habilita;
	addItens->Enabled = Habilita;
	//Habilitando os itens do GRID pagamentos
	DsCompraPagto->AutoEdit = Habilita;
	if (Habilita) {
		TBDSup1001Object *Obj = (TBDSup1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
		if (Obj->ies_parcelado) {
			num_parcelas->Enabled = true;
			num_parcelas->Color = AppConfig->Colors->Enabled;
		} else {
			num_parcelas->Enabled = false;
			num_parcelas->Color = AppConfig->Colors->Disabled;
		}
	} else {
		num_parcelas->Enabled = false;
		num_parcelas->Color = AppConfig->Colors->Disabled;
	}
	UpDwNumParcelas->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::addLineExecute(TObject *Sender)
{
	int iSeq;
	if(!cod_fornecedor->Text.Length()) {
		MessageBox(Handle,"Informe primeiro o fornecedor!",Caption.c_str(),APP_INFORM);
		return;
	}
	if (QyCadProduto->RecordCount > 0) {
		QyCadProduto->Last();
		iSeq = QyCadProduto->FieldByName("seq_produto")->AsInteger + 1;
	} else {
		iSeq = 1;
	}
	//Adiciona uma linha no GRID de itens
	QyCadProduto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadProduto->Insert();
	QyCadProduto->BeforeInsert = &QyDetalheBeforeInsert;
	if(QyCadCompra->State == dsEdit)
		QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger = QyCadCompra->FieldByName("cod_pedido_compra")->AsInteger;
	else
		QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger = 0;
	QyCadProduto->FieldByName("seq_produto")->AsInteger = iSeq;
	QyCadProduto->FieldByName("cod_produto")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadProduto->FieldByName("den_produto")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadProduto->FieldByName("qtd_produto")->AsFloat =  0;
	QyCadProduto->FieldByName("preco_compra")->AsFloat =  0;
	QyCadProduto->FieldByName("val_desconto")->AsFloat = 0;
	QyCadProduto->Post();
	pgDetalhes->ActivePageIndex = 0;
	grdItens->SetFocus();
	grdItens->SelectedField = QyCadProduto->FieldByName("cod_produto");
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::delLineExecute(TObject *Sender)
{
	if(QyCadProduto->RecordCount > 0) {
		QyCadCompra->FieldByName("valor_total")->AsFloat -= QyCadProduto->FieldByName("valor_total")->AsFloat;
		QyCadProduto->Delete();
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::addItensExecute(TObject *Sender)
{
	if(!cod_fornecedor->Text.Length()) {
		MessageBox(Handle,"Informe primeiro o fornecedor!",Caption.c_str(),APP_INFORM);
		return;
	}
	TStrings *SQL = new TStringList();
	SQL->Add("SELECT p.cod_produto, p.den_produto, p.cod_unid_medida, f.preco_compra val_produto");
	SQL->Add("FROM tbl_fornecedor_produto f, tbl_produto p");
	SQL->Add("WHERE f.cod_fornecedor = "+ QuotedStr(cod_fornecedor->Text));
	SQL->Add("AND p.cod_produto = f.cod_produto");
	SQL->Add("AND p.cod_familia = :cod_familia");
	SQL->Add("AND p.ies_ativo = 'S'");
	SQL->Add("ORDER BY p.cod_produto");
	TSup1004 *Sup1004 = new TSup1004(Application);
	Sup1004->OnConfirmList = &addItensConfirm;
	Sup1004->QyCnsProduto->SQL->Assign(SQL);
	Sup1004->ShowModal();
   delete Sup1004;
	delete SQL;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::addItensConfirm(TList *pListAdd)
{
struct SelProdutos {
	String cod_produto;
	String den_produto;
	float  val_produto;
	float  qtd_produto;
};
	int iSeq;
	float fValorTotal = 0;
	SelProdutos *pSelProdutos;

   if (QyCadProduto->FieldByName("cod_produto")->AsString.Length() == 0)
      QyCadProduto->Delete();

	if (QyCadProduto->RecordCount > 0) {
		QyCadProduto->Last();
		iSeq = QyCadProduto->FieldByName("seq_produto")->AsInteger + 1;
	} else {
		iSeq = 1;
	}
try {
	//Adiciona uma linha no GRID de itens
	QyCadProduto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadProduto->FieldByName("cod_produto")->OnValidate = NULL;
	QyCadProduto->FieldByName("qtd_produto")->OnSetText = NULL;
	QyCadProduto->FieldByName("preco_compra")->OnSetText = NULL;
	QyCadProduto->FieldByName("val_desconto")->OnSetText = NULL;
try {
	for (int i=0; i<pListAdd->Count; i++) {
		pSelProdutos = (SelProdutos*)pListAdd->Items[i];
		QyCadProduto->Insert();
		if(QyCadCompra->State == dsEdit)
			QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger = QyCadCompra->FieldByName("cod_pedido_compra")->AsInteger;
		else
			QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger = 0;
		QyCadProduto->FieldByName("seq_produto")->AsInteger = iSeq;
		QyCadProduto->FieldByName("cod_produto")->AsString = pSelProdutos->cod_produto;
		QyCadProduto->FieldByName("den_produto")->AsString = pSelProdutos->den_produto;
		QyCadProduto->FieldByName("qtd_produto")->AsFloat = pSelProdutos->qtd_produto;
		QyCadProduto->FieldByName("preco_compra")->AsFloat = pSelProdutos->val_produto;
		QyCadProduto->FieldByName("val_desconto")->AsFloat = 0;
		QyCadProduto->FieldByName("valor_total")->AsFloat = pSelProdutos->qtd_produto * pSelProdutos->val_produto;
		QyCadProduto->Post();
		fValorTotal += pSelProdutos->qtd_produto * pSelProdutos->val_produto;
		iSeq++;
	}
	QyCadCompra->FieldByName("valor_total")->AsFloat += fValorTotal;
	CalculaDifTotalPagto();
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao incluir vários itens:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//Sempre vai passar por aqui, mesmo dando erro
__finally {
	QyCadProduto->BeforeInsert = &QyDetalheBeforeInsert;
	QyCadProduto->FieldByName("cod_produto")->OnValidate = &CodProdutoValidate;
	QyCadProduto->FieldByName("qtd_produto")->OnSetText = &QtdProdutoSetText;
	QyCadProduto->FieldByName("preco_compra")->OnSetText = &PrecoCompraSetText;
	QyCadProduto->FieldByName("val_desconto")->OnSetText = &ValDescontoSetText;
}

}
//---------------------------------------------------------------------------
void __fastcall TSup1001::RecalculaParcelas()
{
	float fParcela, fDiferenca;
	fDiferenca = 0;
	//Divide em parcelas iguais
	fParcela = RoundTo((pagto_total->Field->AsFloat / UpDwNumParcelas->Position),-2);

	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (QyCadPagto->RecNo < QyCadPagto->RecordCount) {
		fDiferenca += fParcela;
		QyCadPagto->Edit();
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = fParcela;
		QyCadPagto->Post();
		QyCadPagto->Next();
	}
	//Na ultima parecela ele mostra a diferença
	fParcela = RoundTo((pagto_total->Field->AsFloat - fDiferenca),-2);
	QyCadPagto->Edit();
	QyCadPagto->FieldByName("valor_parcela")->AsFloat = fParcela;
	QyCadPagto->Post();
	QyCadPagto->EnableControls(); //Para ativar a atualização da tela
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CalculaDifTotalPagto()
{
	String Msg;
	if (RoundTo(QyCadCompra->FieldByName("pagto_total")->AsFloat,-2) == RoundTo(QyCadCompra->FieldByName("valor_total")->AsFloat,-2)) {
		MsgDifTotalPagto->Caption = "";
	} else {
		if (QyCadCompra->FieldByName("pagto_total")->AsFloat < QyCadCompra->FieldByName("valor_total")->AsFloat
		) {
			Msg = "O valor total informado para pagamento é menor que o valor total da compra.";
			Msg += "\nDiferença entre o valor total e o pagamento: " + \
			CurrToStrF((QyCadCompra->FieldByName("valor_total")->AsFloat - QyCadCompra->FieldByName("pagto_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clRed;
			MsgDifTotalPagto->Caption = Msg;
		} else {
			Msg = "O valor total informado para pagamento é maior que o valor total do orçamento.";
			Msg += "\nDiferença entre o pagamento e o valor total: " + \
			CurrToStrF((QyCadCompra->FieldByName("pagto_total")->AsFloat - QyCadCompra->FieldByName("valor_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clBlue;
			MsgDifTotalPagto->Caption = Msg;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraAfterScroll(TDataSet *DataSet)
{
	String sSQL;
	sSQL = "SELECT den_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	den_fornecedor->Text = ValidacoesDB::GetDenominacaoByKey(AppConnection,sSQL);
	UpDwNumParcelas->Position = QyCadCompra->FieldByName("num_parcelas")->AsInteger;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraCalcFields(TDataSet *DataSet)
{
	QyCadCompra->FieldByName("pagto_total")->AsFloat = QyCadCompra->FieldByName("valor_total")->AsFloat;
}
//---------------------------------------------------------------------------
//No evento de BeforPost ele desassocia os datasets das querys filhas para não recarregar
void __fastcall TSup1001::QyCadCompraBeforePost(TDataSet *DataSet)
{
	QyCadCompra->AfterScroll = NULL;
	QyCadProduto->DataSource = NULL;
	QyCadPagto->DataSource = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraAfterPost(TDataSet *DataSet)
{
try {
try {
	int iSeq = 1;  //Utilizado para refazer a ordenação dos produtos 
	//Verificação para atualizar o campo código do mestre nos itens
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	QyCadProduto->First();
	while (!QyCadProduto->Eof) {
		if (QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger == 0) {
			QyCadProduto->Edit();
			QyCadProduto->FieldByName("cod_pedido_compra")->AsInteger = QyCadCompra->FieldByName("cod_pedido_compra")->AsInteger;
			QyCadProduto->Post();
		}
		//QyCadProduto->FieldByName("seq_produto")->AsInteger = iSeq;
		QyCadProduto->Next();
		iSeq++;
	}
	QyCadProduto->EnableControls(); //Para ativar a atualização da tela
	//Inserindo os novos registros de itens
	QyCadProduto->ApplyUpdates();
	QyCadProduto->First();
	//Verificação para atualizar o campo código do mestre nos pagamentos
	QyCadPagto->DisableControls();  //Para desativar a atualização da tela
	QyCadPagto->First();
	while (!QyCadPagto->Eof) {
		if (QyCadPagto->FieldByName("cod_pedido_compra")->AsInteger == 0) {
			QyCadPagto->Edit();
			QyCadPagto->FieldByName("cod_pedido_compra")->AsInteger = QyCadCompra->FieldByName("cod_pedido_compra")->AsInteger;
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
	QyCadCompra->AfterScroll = &QyCadCompraAfterScroll;
	QyCadProduto->DataSource = DsCadCompra;
	QyCadPagto->DataSource = DsCadCompra;
}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraBeforeDelete(TDataSet *DataSet)
{
try {
	//Excluindo os itens do pedido
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	while (QyCadProduto->RecordCount > 0) {
		QyCadProduto->Last();
		QyCadProduto->Delete();
	}
	QyCadProduto->ApplyUpdates();
	QyCadProduto->EnableControls(); //Para ativar a atualização da tela
	//Excluindo os pagamentos do pedido
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
void __fastcall TSup1001::btEnviarPedidoClick(TObject *Sender)
{
	String Situacao;
	bool bAltera = false;
	QySitPedidoCompra->Refresh();
	Situacao = QySitPedidoCompra->FieldByName("ies_situacao")->AsString;
	if(Situacao == "A") {
		if (MessageBox(Handle, "Confirma o envio do pedido de compra?",Caption.c_str(),APP_QUESTION)==ID_YES) {
			bAltera = true;
		} else {
			return;
		}
	} else if(Situacao == "C") {
		MessageBox(Handle,"Pedido de compra cancelado. Envio não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "F") {
		MessageBox(Handle,"Pedido de compra fechado. Envio não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "R") {
		MessageBox(Handle,"Pedido de compra recebido. Envio não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "E") {
		if (MessageBox(Handle,"Pedido de compra já enviado. Confirma o reenvio do mesmo?",Caption.c_str(),APP_QUESTION)==ID_NO) {
			return;
		}
	}
	TSup1002 *Sup1002 = new TSup1002(Application);
	Sup1002->Destinatario->Text = den_fornecedor->Text + " <" + ValidacoesDB::GetDenominacaoByKey(AppConnection,"SELECT email FROM tbl_fornecedor WHERE cod_fornecedor = '" + cod_fornecedor->Text + "';") + ">";
	Sup1002->Assunto->Text = "Pedido de compra Nº" + cod_pedido_compra->Text;
	Sup1002->QyCadProduto->ParamByName("cod_pedido_compra")->Value = cod_pedido_compra->Field->Value;
	Sup1002->QyCadProduto->Active = true;
	if(bAltera) {
		Sup1002->OnSendMailSucess = &Sup1002SendMailSucess;
	}
	Sup1002->ShowModal();
	delete Sup1002;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::Sup1002SendMailSucess() {
	AlteraSitCompra("E");
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::AlteraSitCompra(String Situacao)
{
	QyCadCompra->Edit();
	QyCadCompra->FieldByName("ies_situacao")->AsString = Situacao;
	if (Situacao == "R") {
		QyCadCompra->FieldByName("data_recebimento")->AsDateTime = Now();
	}
	//Deve retirar os eventos para não reenviar os itens, pois os mesmos não alteram
	QyCadCompra->BeforePost = NULL;
	QyCadCompra->AfterPost = NULL;
	QyCadCompra->Post();
	//Atribuindo novamente os eventos
	QyCadCompra->BeforePost = &QyCadCompraAfterPost;
	QyCadCompra->AfterPost = &QyCadCompraBeforePost;
	QySitPedidoCompra->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btRelatorioClick(TObject *Sender)
{
	TSup3001 *Sup3001 = new TSup3001(Application);
	Sup3001->CnsCompra->Active = false;
	Sup3001->CnsCompra->Params->ParamByName("cod_pedido_compra")->Value = QyCadCompra->FieldByName("cod_pedido_compra")->Value;
	Sup3001->CnsCompra->Active = true;
   if(Sup3001->RpRelatBase->PrepareReport(true))
      Sup3001->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btPesqFornecedorClick(TObject *Sender)
{
	SfgBrowse::EscolheFornecedor(this,&SearchFornecedor);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CodFornecedorSetText(
      TField *Sender, const AnsiString Text)
{
	String OldText = VarToStr(Sender->Value);
	// ShowMessage("NewValue: " + Text + " Value: " + OldText);
	if (OldText != Text) {
		//Se só tem uma linha no GRID e não foi informado o produto pode passar
		if ((QyCadProduto->RecordCount <= 1) && (QyCadProduto->FieldByName("cod_produto")->AsString.Length() == 0)) {
			Sender->AsString = Text;
		} else {
			if (MessageBox(Handle,"Está sendo alterado o fornecedor.\n"
				"Serão excluídos os itens já informados.\n"
				"Confirma esta alteração?",Caption.c_str(),APP_QUESTION | MB_DEFBUTTON2) == IDYES) {
				Sender->AsString = Text;
				while (QyCadProduto->RecordCount > 0) {
					QyCadProduto->Last();
					QyCadProduto->Delete();
				}
				//Se exclui todos os itens deve zerar o valor total do pedido
				QyCadCompra->FieldByName("valor_total")->AsFloat = 0;
			}
		}
	}
	if (QyCadProduto->RecordCount == 0)
		addLineExecute(NULL);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btPesqPlanoContaClick(TObject *Sender)
{
	SfgBrowse::EscolhePlanoConta(this,&SearchPlanoConta);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SearchPlanoConta(Variant Value) {
	cod_plano_conta->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::btPesqCentroCustoClick(TObject *Sender)
{
	SfgBrowse::EscolheCentroCusto(this,&SearchCentroCusto);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SearchCentroCusto(Variant Value) {
	cod_centro_custo->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::execRecebimentoExecute(TObject *Sender)
{
	String Situacao;
	QySitPedidoCompra->Refresh();
	Situacao = QySitPedidoCompra->FieldByName("ies_situacao")->AsString;
	if(Situacao == "A") {
		if (MessageBox(Handle, "Pedido de compra ainda não enviado. \nConfirma o recebimento do pedido de compra?",Caption.c_str(),APP_QUESTION)==ID_NO) {
			return;
		}
	} else if(Situacao == "E") {
		if (MessageBox(Handle, "Confirma o recebimento do pedido de compra?",Caption.c_str(),APP_QUESTION)==ID_NO) {
			return;
		}
	} else if(Situacao == "C") {
		MessageBox(Handle,"Pedido de compra cancelado. Recebimento não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "F") {
		MessageBox(Handle,"Pedido de compra fechado. Recebimento não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "R") {
		if (MessageBox(Handle,"Recebimento do pedido de compra já registrado. Registrar novamente o mesmo?",Caption.c_str(),APP_QUESTION)==ID_NO) {
			return;
		}
	}
	TSup1003 *Sup1003 = new TSup1003(Application);
	Sup1003->QyCadProduto->ParamByName("cod_pedido_compra")->Value = cod_pedido_compra->Field->Value;
	Sup1003->QyCadProduto->Active = true;
	Sup1003->OnRecebeSucess = &Sup1003RecebeSucess;
	Sup1003->ShowModal();
	delete Sup1003;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::Sup1003RecebeSucess() {
	AlteraSitCompra("R");
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::execFechamentoExecute(TObject *Sender)
{
	String Situacao;
	QySitPedidoCompra->Refresh();
	Situacao = QySitPedidoCompra->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		MessageBox(Handle, "Pedido de compra já fechado.",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao != "R") {
		MessageBox(Handle, "Pedido de compra ainda não registrado recebimento.\nFechamento do pedido não permitido!",Caption.c_str(),APP_INFORM);
		return;
	} else if(MessageBox(Handle, "Confirma o fechamento do pedido de compra?",Caption.c_str(),APP_QUESTION)==ID_NO) {
		return;
	}
	//Verifica se o pagamento é parcelado, caso não seja, pergunta ao usuário seo mesmo deseja baixar já a conta a pagar
	bool liquidado = false;
	TBDSup1001Object *Obj = (TBDSup1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
	if (Obj->ies_financeiro && !Obj->ies_parcelado) {
		if (MessageBox(Handle, "Pagamento do pedido de compra não é parcelado.\nDeseja lançar a conta a pagar como liquidada?",Caption.c_str(),APP_QUESTION)==ID_YES) {
			liquidado = true;
		}
	}
	//Usuário confirmou o pedido de compra
	String SQL;
	TZReadOnlyQuery *QyFechaPedido = new TZReadOnlyQuery(Application);
	QyFechaPedido->Connection = AppConnection;
try {
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
   if (Obj->ies_financeiro) {
	   //Fecha o pedido de compra
	   //Incluindo os itens no estoque
	   //Incluindo o registro da conta a pagar
	   //Liquidando o pagamento, este processo também já efetua o lançamento no caixa
	   SQL = "CALL fecha_pedido_compra("+ cod_pedido_compra->Text +"," + ((liquidado) ? "1" : "0") + ");";
	   QyFechaPedido->SQL->Text = SQL;
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
   } else {
	   //Fecha o pedido de compra
	   //Incluindo os itens no estoque
	   SQL = "CALL inclui_pedido_compra_estoque("+ cod_pedido_compra->Text +");";
	   QyFechaPedido->SQL->Text = SQL;
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
	   SQL = "UPDATE tbl_pedido_compra SET ies_situacao = 'F'";
      SQL += " WHERE cod_pedido_compra = " + cod_pedido_compra->Text;
	   QyFechaPedido->SQL->Text = SQL;
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
   }
	SfgDataCenter->CommitTrans();
} catch(Exception &e){
	SfgDataCenter->RollbackTrans();
	String Msg = "Ocorreu o seguinte erro ao efetuar o fechamento do pedido de compra:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
	delete QyFechaPedido;
	QySitPedidoCompra->Refresh();
	if (liquidado) {
		QyCadPagto->Refresh();
	}
	MessageBox(Handle,"Pedido de compra fechado com sucesso!",Caption.c_str(), APP_INFORM);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::cod_forma_pagtoChange(TObject *Sender)
{
	TBDSup1001Object *Obj = (TBDSup1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = QyCadCompra->FieldByName("valor_total")->AsFloat;
		QyCadPagto->Post();
		QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	}
	UpDwNumParcelas->Invalidate();
	if (!Obj->ies_parcelado) {
		RecalculaParcelas();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::UpDwNumParcelasClick(TObject *Sender,
		TUDBtnType Button)
{
	if (Button == btNext) {
		QyCadPagto->Last();
		//Adiciona uma linha no GRID de parcelas
		QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
		QyCadPagto->Insert();
		QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
		if (QyCadCompra->State == dsEdit)
			QyCadPagto->FieldByName("cod_pedido_compra")->AsInteger = cod_pedido_compra->Field->AsInteger;
		else
			QyCadPagto->FieldByName("cod_pedido_compra")->AsInteger = 0;
		QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
		QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
		QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("ies_pago")->AsString = "N";
		QyCadPagto->Post();
	} else {
		//Elimina uma linha no GRID de parcelas
		if(QyCadPagto->RecordCount > 0) {
			QyCadPagto->Last();
			QyCadPagto->Delete();
		}
	}
	RecalculaParcelas();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyDetalheBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::EditPagtoSetFocus(TObject *Sender)
{
	if(QyCadCompra->State == dsInsert || QyCadCompra->State == dsEdit) {
		if (grdPagtos->SelectedField->FieldName == "valor_parcela") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdPagtosColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_pago") {
		Options = grdPagtos->Options;
		Options >> dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdPagtosColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_pago") {
		Options = grdPagtos->Options;
		Options << dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::DbGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdPagtosDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_pago") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdPagtos,-1,-1,Rect,State,bChecked);
	} else if (Column->Field->FieldName == "data_vencimento") {
		DrawCalendarGrid(grdPagtos,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdPagtosEditButtonClick(TObject *Sender)
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
			if(QyCadCompra->State == dsEdit || QyCadCompra->State == dsInsert) {
				if (!(QyCadPagto->State == dsEdit))
					QyCadPagto->Edit();
				grdPagtos->SelectedField->AsString = sDate;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::ValorParcelaSetText(TField *Sender,
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
		QyCadCompra->FieldByName("pagto_total")->AsFloat += (v - Sender->AsFloat);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::EditItemSetFocus(TObject *Sender)
{
	if(QyCadCompra->State == dsInsert || QyCadCompra->State == dsEdit) {
		if (grdItens->SelectedField->FieldName == "qtd_produto" ||
			 grdItens->SelectedField->FieldName == "preco_compra" ||
			 grdItens->SelectedField->FieldName == "val_desconto") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadProdutoCalcFields(TDataSet *DataSet)
{
	QyCadProduto->FieldByName("valor_total")->AsFloat =
	QyCadProduto->FieldByName("qtd_produto")->AsFloat *
	(QyCadProduto->FieldByName("preco_compra")->AsFloat -
	QyCadProduto->FieldByName("val_desconto")->AsFloat);
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdItensDrawColumnCell(TObject *Sender,
		const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->FieldName == "cod_produto") {
		DrawSearchGrid(grdItens,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CodProdutoValidate(TField *Sender)
{
	if(Sender->AsString.Length() == 0) {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		return;
	}
	//Deve validar o código do item
	QyCnsProduto->Active = false;
	QyCnsProduto->Params->ParamByName("cod_fornecedor")->Value = cod_fornecedor->Field->Value;
	QyCnsProduto->Params->ParamByName("cod_produto")->Value = Sender->Value;
	QyCnsProduto->Active = true;
	if(QyCnsProduto->RecordCount > 0) {
		float fOldTotal, fNewTotal;
		QyCadProduto->FieldByName("den_produto")->AsString = QyCnsProduto->FieldByName("den_produto")->AsString;
		fOldTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("preco_compra")->AsFloat = QyCnsProduto->FieldByName("preco_compra")->AsFloat;
		fNewTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyCadCompra->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		CalculaDifTotalPagto();
	} else {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		throw Exception("Produto não cadastrado, inativo ou não relacionado ao fornecedor!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QtdProdutoSetText(TField *Sender, const AnsiString Text)
{
	//Deve recalcular o valor total do item e do pedido
	float fOldTotal, fNewTotal;
	float fValor = 0;
	try {
		fValor = (Text.Length()) ? StrToFloat(Text) : 0;
	}
	__finally {}
	if (fValor == NULL || fValor <= 0) {
		MessageBox(Handle,"Informe um valor numérico maior que zero!",Caption.c_str(),APP_ATENTION);
		return;
	} else {
		fOldTotal = Sender->AsFloat *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		fNewTotal = fValor *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyCadCompra->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::PrecoCompraSetText(TField *Sender, const AnsiString Text)
{
	//Deve recalcular o valor total do item e do pedido
	float fOldTotal, fNewTotal;
	float fValor = 0;
	try {
		fValor = (Text.Length()) ? StrToFloat(Text) : 0;
	}
	__finally {}
	if (fValor == NULL || fValor <= 0) {
		MessageBox(Handle,"Informe um valor numérico maior que zero!",Caption.c_str(),APP_ATENTION);
		return;
	} else {
		fOldTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (Sender->AsFloat - QyCadProduto->FieldByName("val_desconto")->AsFloat);
		fNewTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (fValor - QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyCadCompra->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::ValDescontoSetText(TField *Sender, const AnsiString Text)
{
	//Deve recalcular o valor total do item e do pedido
	float fOldTotal, fNewTotal;
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
		fOldTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat - Sender->AsFloat);
		fNewTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_compra")->AsFloat - fValor);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyCadCompra->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::grdItensEditButtonClick(TObject *Sender)
{
	if (!(QyCadCompra->State == dsInsert || QyCadCompra->State == dsEdit))
		return;
	if (grdItens->SelectedField->FieldName == "cod_produto") {
		SfgBrowse::EscolheProdutoFornecedor(this,cod_fornecedor->Text,&SearchProduto);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::SearchProduto(Variant Value) {
	if (QyCadProduto->State != dsEdit)
		QyCadProduto->Edit();
	QyCadProduto->FieldByName("cod_produto")->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CodCentroCustoValidate(TField *Sender)
{
	String sSQL;
	if(!Sender->AsString.Length())
		return;
	sSQL = "SELECT cod_centro_custo FROM tbl_centro_custo" \
			" WHERE cod_centro_custo = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		throw Exception("Centro de custo não cadastrado!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::CodPlanoContaValidate(TField *Sender)
{
	String sSQL;
	if(!Sender->AsString.Length())
		return;
	sSQL = "SELECT cod_plano_conta FROM tbl_plano_conta" \
			" WHERE cod_plano_conta = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		throw Exception("Conta contábil não cadastrada no plano de contas!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraPostError(TDataSet *DataSet,
      EDatabaseError *E, TDataAction &Action)
{
   PostStatus = false;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraAfterOpen(TDataSet *DataSet)
{
	QyCadProduto->Active = true;
	QyCadPagto->Active = true;
	QySitPedidoCompra->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1001::QyCadCompraBeforeClose(TDataSet *DataSet)
{
	QyCadProduto->Active = false;
	QyCadPagto->Active = false;
	QySitPedidoCompra->Active = false;
}
//---------------------------------------------------------------------------

