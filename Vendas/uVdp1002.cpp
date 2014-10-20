/*
Módulo: Vendas
Função: Cadastro Orçamentos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//--------------------------------------------------------------------------
#include <vcl.h>
#include <math.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#include "uSfgWorkEdition.h"
#include "uSfgCalendar.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseFin.h"
#include "uVdp1004.h"
#include "uVdp3010.h"
#pragma hdrstop
#include "uVdp1002.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1002(void) {
   AddAppForm("Vdp1002","Orçamentos",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1002",__classid(TVdp1002));
}
#pragma startup RegisterVdp1002
//---------------------------------------------------------------------------
__fastcall TVdp1002::TVdp1002(TComponent* Owner)
	: TfrmBase02(Owner)
{
   CarregarSitOrcamento();
	CarregarTipoPessoa();
	CarregarEstado();
	CarregarFormaPagto();
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsOrcamento;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   //Adicionando os eventos customizados dos campos
   QyOrcamento->FieldByName("cod_cliente")->OnValidate = &CodClienteValidate;
   QyOrcamento->FieldByName("cod_plano_conta")->OnValidate = &CodPlanoContaValidate;
   QyOrcamento->FieldByName("cod_centro_custo")->OnValidate = &CodCentroCustoValidate;
   //Adicionando os campos do DataSet Cliente
   String ClienteColumns = SfgToolbar->ParserSelectColumns(QyCliente->SQL->Text);
   TSfgMetaTable *MetaTable = AddMetaTable("tbl_cliente");
   CreateFieldDefs(MetaTable, ClienteColumns, QyCliente);
   CreateFields(QyCliente);
   QyCliente->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;

	pWorkEdtCliente = new SfgWorkEdition(DsClientes,this);
	pWorkEdtCliente->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
	ies_situacao->Color = AppConfig->Colors->Disabled;
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
   //Força o botão percentual pertencer ao SfgToolbar
	btFechamento->Parent = SfgToolbar;
	btFechamento->Top = 6;
	btFechamento->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = btFechamento->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btFechamento);
	this->Tolltips->AddToolTip(btRelatorio);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::AfterCreateFields(TDataSet *DataSet)
{
   //Adicionando o campo virtual na tabela
	DynamicArray<String> FieldDefs;
	FieldDefs.Length = 1;
	FieldDefs[0] = "fkCalculated|pagto_total|ftFloat|0|Pagto Total";
   AddVirtualFields(FieldDefs,QyOrcamento,true);
   ((TFloatField*)QyOrcamento->FieldByName("pagto_total"))->currency = true;
   //Marcando campo como auto incremento
   QyOrcamento->FieldByName("cod_orcamento")->AutoGenerateValue = arAutoInc;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   TfrmBase02::SetPermissao(Nivel);
   //Escondendo as opções de menu do SfgToolbar
	execFechamento->Visible = false;
   //Desabilitando as teclas de atalho também
	execFechamento->Enabled = false;
   btRelatorio->Left = SfgToolbar->btExit->Left;
   SfgToolbar->btExit->Left += 38;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::FilterCodOrcamento(int CodOrcamento)
{
	QyOrcamento->Filter = "cod_orcamento = " + IntToStr(CodOrcamento);
	QyOrcamento->Filtered = true;
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
void __fastcall TVdp1002::ValidInsert(bool &bValid)
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
void __fastcall TVdp1002::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::ValidDelete(bool &bValid)
{
	String SQL;
	String Situacao;
	QySitPedidoVenda->Refresh();
	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		MessageBox(Handle, "Orçamento fechado. Não pode ser excluído!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		PostStatus = false;
		return;
	}
	/*SQL = "SELECT DISTINCT 1 FROM tbl_orcamento_produto" \
			" WHERE cod_orcamento = " + QuotedStr(cod_orcamento->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Orçamento possui produtos já relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}*/
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CarregarSitOrcamento()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Aberto","A");
	ies_situacao->AddItem("Fechado","F");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CarregarTipoPessoa()
{
	tipo_pessoa->Clear();
	tipo_pessoa->AddItem("Pessoa Física","F");
	tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CarregarEstado()
{
  TZQuery *QyUF = new TZQuery(this);
try
{
  QyUF->SQL->Text = "SELECT cod_uf FROM tbl_uf ORDER BY cod_uf";
  QyUF->Connection = AppConnection;
  QyUF->Active = true;
  while(!QyUF->Eof) {
	 cod_uf->AddItem(QyUF->FieldByName("cod_uf")->AsString,NULL);
    QyUF->Next();
  }
}__finally{delete(QyUF);}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::cod_ufChange(TObject *Sender)
{
   if(cod_uf->ReadOnly)
      return;
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
	cod_cidade->SetTableItems(true);
	cod_cidade->Field->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CarregarFormaPagto()
{
  TBDVdp1002Object *Obj;
  TZQuery *QyPagto = new TZQuery(this);
try
{
	QyPagto->SQL->Text = "SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado FROM tbl_forma_pagto";
	QyPagto->Connection = AppConnection;
	QyPagto->Active = true;
	cod_forma_pagto->Clear();
	while(!QyPagto->Eof) {
		Obj = new TBDVdp1002Object();
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
void __fastcall TVdp1002::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
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
bool __fastcall TVdp1002::VerificaCampos()
{
	bool bItem = false;
	bool bPagto = false;
	if(!cod_cliente->Text.Length()) {
		MessageBox(Handle, "Digite o código do cliente do orçamento!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
		return false;
	}
	if(!data_validade->Text.Length()) {
		MessageBox(Handle, "Digite a data de validade do orçamento!",Caption.c_str(),APP_ATENTION);
		data_validade->SetFocus();
		return false;
	}
	if (RoundTo(valor_total->Field->AsFloat,-3) != RoundTo(pagto_total->Field->AsFloat,-3)) {
		MessageBox(Handle, "Valor total dos itens difere do valor de pagamento total do pedido de venda!",Caption.c_str(),APP_ATENTION);
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
			grdItens->SelectedField = QyCadProduto->FieldByName("cod_produto");
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
bool __fastcall TVdp1002::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::SearchCliente(Variant Value) {
	cod_cliente->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CodClienteValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		if(MessageBox(Handle, "Cliente não encontrado no cadastro.\nDeseja incluir um novo cliente com os dados informados?",Caption.c_str(),APP_QUESTION) == ID_NO) {
			if (QyCliente->State == dsInsert) {
				DesabilitaCadCliente();
			}
			throw Exception("Cliente não cadastrado!");
		} else {
			HabilitaCadCliente();
		}
	} else {
		if (QyCliente->State == dsInsert) {
			DesabilitaCadCliente();
		}
		QyCliente->Params->ParamByName("cod_cliente")->Value = Sender->AsString;
		QyCliente->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::HabilitaCadCliente()
{
	if (QyCliente->State == dsInsert)
		return;
	QyCliente->Insert();
	QyCliente->FieldByName("cod_cliente")->Value = cod_cliente->Field->AsString;
	pWorkEdtCliente->SetWorkEdition(true, true, AppConfig->Colors->Enabled);
	den_cliente->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::DesabilitaCadCliente()
{
	QyCliente->Cancel();
	pWorkEdtCliente->SetWorkEdition(false, true, AppConfig->Colors->Disabled);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_cadastro);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_validade);
	data_validadeExit(data_validade);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::NavegexecBtEditClickExecute(
		TObject *Sender)
{
	String Situacao;
	bool altera = false;
	QySitPedidoVenda->Refresh();
	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		if (MessageBox(Handle, "Orçamento fechado. Deseja realmente alterar o mesmo?\nEsta ação irá alterar a situação do mesmo para aberto.",Caption.c_str(),APP_QUESTION)==ID_YES) {
			altera = true;
		} else {
			return;
		}
	} else if(Situacao == "C") {
		MessageBox(Handle,"Orçamento cancelado. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	if (altera && Situacao == "F") { //Deve estornar o fechamento do orçamento
		AlteraSituacao("A");
	}
	SfgToolbar->btEditClick(Sender);
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::NavegexecBtSaveClickExecute(TObject *Sender)
{
	QyOrcamento->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
	PostStatus = true;
	if (QyCliente->State == dsInsert) {
		if(!VerificaCamposCliente()) {
			return;
		}
	}
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
try {
	SfgToolbar->btSaveClick(Sender);
} catch (Exception &e) {
   String sMsgErro = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
   sMsgErro = sMsgErro + e.Message;
   MessageBox(Handle,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
   PostStatus = false;
}
	if (PostStatus) {
		SfgDataCenter->CommitTrans();
		HabilitarItens(false);
	} else {
		SfgDataCenter->RollbackTrans();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::NavegexecBtCancelClickExecute(
      TObject *Sender)
{
	bool edit = (QyOrcamento->State == dsEdit);
	if (QyCliente->State == dsInsert) {
		DesabilitaCadCliente();
	}
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyOrcamentoAfterScroll(QyOrcamento);
	HabilitarItens(false);
   MsgDifTotalPagto->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::NavegexecBtNewClickExecute(
		TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	QyOrcamento->FieldByName("data_cadastro")->Value = Now();
	QyOrcamento->FieldByName("ies_situacao")->Value = "A";
	cod_forma_pagto->ItemIndex = 0;
	cod_forma_pagto->Field->Value = cod_forma_pagto->Value;
	//Adiciona uma linha no GRID de itens
	addLineExecute(Sender);
	//Adiciona uma linha no GRID de parcelas
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
	QyCadPagto->FieldByName("cod_orcamento")->AsInteger = 0;
	QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->Post();
	HabilitarItens(true);
	data_cadastro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::NavegexecBtDeleteClickExecute(TObject *Sender)
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
void __fastcall TVdp1002::HabilitarItens(bool Habilita)
{
	btPesqPlanoConta->Enabled = Habilita;
	btPesqCentroCusto->Enabled = Habilita;
	btPesqCliente->Enabled = Habilita;
	//Habilitando os itens do GRID de itens
	DsCadProduto->AutoEdit = Habilita;
	addLine->Enabled = Habilita;
	delLine->Enabled = Habilita;
	addItens->Enabled = Habilita;
	//Habilitando os itens do GRID pagamentos
	DsCompraPagto->AutoEdit = Habilita;
	if (Habilita) {
		TBDVdp1002Object *Obj = (TBDVdp1002Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
void __fastcall TVdp1002::addLineExecute(TObject *Sender)
{
	int iSeq;
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
	if(QyOrcamento->State == dsEdit)
		QyCadProduto->FieldByName("cod_orcamento")->AsInteger = QyOrcamento->FieldByName("cod_orcamento")->AsInteger;
	else
		QyCadProduto->FieldByName("cod_orcamento")->AsInteger = 0;
	QyCadProduto->FieldByName("seq_produto")->AsInteger = iSeq;
	QyCadProduto->FieldByName("cod_produto")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadProduto->FieldByName("den_produto")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadProduto->FieldByName("qtd_produto")->AsFloat =  0;
	QyCadProduto->FieldByName("preco_venda")->AsFloat =  0;
	QyCadProduto->FieldByName("val_desconto")->AsFloat = 0;
	QyCadProduto->Post();
	pgDetalhes->ActivePageIndex = 0;
	grdItens->SetFocus();
	grdItens->SelectedField = QyCadProduto->FieldByName("cod_produto");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::delLineExecute(TObject *Sender)
{
	if(QyCadProduto->RecordCount > 0) {
		QyOrcamento->FieldByName("valor_total")->AsFloat -= QyCadProduto->FieldByName("valor_total")->AsFloat;
		QyCadProduto->Delete();
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::addItensExecute(TObject *Sender)
{
   TVdp1004 *Vdp1004 = new TVdp1004(Application);
	Vdp1004->OnConfirmList = &addItensConfirm;
	Vdp1004->ShowModal();
   delete Vdp1004;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::addItensConfirm(TList *pListAdd)
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
	QyCadProduto->FieldByName("preco_venda")->OnSetText = NULL;
	QyCadProduto->FieldByName("val_desconto")->OnSetText = NULL;
try {
	for (int i=0; i<pListAdd->Count; i++) {
		pSelProdutos = (SelProdutos*)pListAdd->Items[i];
		QyCadProduto->Insert();
		if(QyOrcamento->State == dsEdit)
			QyCadProduto->FieldByName("cod_orcamento")->AsInteger = QyOrcamento->FieldByName("cod_orcamento")->AsInteger;
		else
			QyCadProduto->FieldByName("cod_orcamento")->AsInteger = 0;
		QyCadProduto->FieldByName("seq_produto")->AsInteger = iSeq;
		QyCadProduto->FieldByName("cod_produto")->AsString = pSelProdutos->cod_produto;
		QyCadProduto->FieldByName("den_produto")->AsString = pSelProdutos->den_produto;
		QyCadProduto->FieldByName("qtd_produto")->AsFloat = pSelProdutos->qtd_produto;
		QyCadProduto->FieldByName("preco_venda")->AsFloat = pSelProdutos->val_produto;
		QyCadProduto->FieldByName("val_desconto")->AsFloat = 0;
		QyCadProduto->FieldByName("valor_total")->AsFloat = pSelProdutos->qtd_produto * pSelProdutos->val_produto;
		QyCadProduto->Post();
		fValorTotal += pSelProdutos->qtd_produto * pSelProdutos->val_produto;
		iSeq++;
	}
	QyOrcamento->FieldByName("valor_total")->AsFloat += fValorTotal;
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
	QyCadProduto->FieldByName("preco_venda")->OnSetText = &PrecoVendaSetText;
	QyCadProduto->FieldByName("val_desconto")->OnSetText = &ValDescontoSetText;
}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::RecalculaParcelas()
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
void __fastcall TVdp1002::CalculaDifTotalPagto()
{
	String Msg;
	if (RoundTo(QyOrcamento->FieldByName("pagto_total")->AsFloat,-2) == RoundTo(QyOrcamento->FieldByName("valor_total")->AsFloat,-2)) {
		MsgDifTotalPagto->Caption = "";
	} else {
		if (QyOrcamento->FieldByName("pagto_total")->AsFloat < QyOrcamento->FieldByName("valor_total")->AsFloat
		) {
			Msg = "O valor total informado para pagamento é menor que o valor total da venda.";
			Msg += "\nDiferença entre o valor total e o pagamento: " + \
			CurrToStrF((QyOrcamento->FieldByName("valor_total")->AsFloat - QyOrcamento->FieldByName("pagto_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clRed;
			MsgDifTotalPagto->Caption = Msg;
		} else {
			Msg = "O valor total informado para pagamento é maior que o valor total da venda.";
			Msg += "\nDiferença entre o pagamento e o valor total: " + \
			CurrToStrF((QyOrcamento->FieldByName("pagto_total")->AsFloat - QyOrcamento->FieldByName("valor_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clBlue;
			MsgDifTotalPagto->Caption = Msg;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoAfterScroll(TDataSet *DataSet)
{
	QyCliente->Params->ParamByName("cod_cliente")->Value = DataSet->FieldByName("cod_cliente")->Value;
	QyCliente->Refresh();
	UpDwNumParcelas->Position = DataSet->FieldByName("num_parcelas")->AsInteger;
   TipoPessoaChange(tipo_pessoa->Field);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoCalcFields(TDataSet *DataSet)
{
	QyOrcamento->FieldByName("pagto_total")->AsFloat = QyOrcamento->FieldByName("valor_total")->AsFloat;
}
//---------------------------------------------------------------------------
//No evento de BeforPost ele desassocia os datasets das querys filhas para não recarregar
void __fastcall TVdp1002::QyOrcamentoBeforePost(TDataSet *DataSet)
{
	QyCadProduto->DataSource = NULL;
	QyCadPagto->DataSource = NULL;
	QyOrcamento->AfterScroll = NULL;
	//Se está inserindo um cliente deve postar o mesmo primeiro
	if (QyCliente->State == dsInsert) {
		QyCliente->Post();
		pWorkEdtCliente->SetWorkEdition(false, true, AppConfig->Colors->Disabled);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoAfterPost(TDataSet *DataSet)
{
try {
try {
	int iSeq = 1;  //Utilizado para refazer a ordenação dos produtos 
	//Verificação para atualizar o campo código do mestre nos itens
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	QyCadProduto->First();
	while (!QyCadProduto->Eof) {
		if (QyCadProduto->FieldByName("cod_orcamento")->AsInteger == 0) {
			QyCadProduto->Edit();
			QyCadProduto->FieldByName("cod_orcamento")->AsInteger = QyOrcamento->FieldByName("cod_orcamento")->AsInteger;
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
		if (QyCadPagto->FieldByName("cod_orcamento")->AsInteger == 0) {
			QyCadPagto->Edit();
			QyCadPagto->FieldByName("cod_orcamento")->AsInteger = QyOrcamento->FieldByName("cod_orcamento")->AsInteger;
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
	QyCadProduto->DataSource = DsOrcamento;
	QyCadPagto->DataSource = DsOrcamento;
	QyOrcamento->AfterScroll = &QyOrcamentoAfterScroll;
}
}
//--------------------------------------------------------------------
void __fastcall TVdp1002::data_validadeExit(TObject *Sender)
{
	TBDVdp1002Object *Obj = (TBDVdp1002Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
	if (!Obj->ies_parcelado) {
		//Como não é parcelado assume automaticamente a data de vencimento como sendo a do Orçamento
		if (QyCadPagto->State != dsEdit)
			QyCadPagto->Edit();
		QyCadPagto->FieldByName("data_vencimento")->Value = data_validade->Field->Value;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1002::VerificaCamposCliente()
{
	if(!cod_cliente->Text.Length()) {
		MessageBox(Handle, "Digite o código do cliente!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
		return false;
	}
	if(!den_cliente->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do cliente!",Caption.c_str(),APP_ATENTION);
		den_cliente->SetFocus();
		return false;
	}
	if(cpf_cnpj->Text.Trim().Length()) {
      if (QyCliente->FieldByName("tipo_pessoa")->AsString == "F") {
		   if(!Validacoes::ValidarCPF(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CPF válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      } else {
		   if(!Validacoes::ValidarCNPJ(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CNPJ válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      }
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoBeforeDelete(
      TDataSet *DataSet)
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
void __fastcall TVdp1002::btRelatorioClick(TObject *Sender)
{
	TVdp3010 *Vdp3010 = new TVdp3010(Owner);
	Vdp3010->CnsOrcamento->Active = false;
	Vdp3010->CnsOrcamento->Params->ParamByName("cod_orcamento")->Value = QyOrcamento->FieldByName("cod_orcamento")->Value;
	Vdp3010->CnsOrcamento->Active = true;
   if(Vdp3010->RpRelatBase->PrepareReport(true))
      Vdp3010->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btPesqClienteClick(TObject *Sender)
{
	SfgBrowse::EscolheCliente(this,&SearchCliente);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btEnderecoClick(TObject *Sender)
{
	grpEndereco->Top = 235;
	grpEndereco->Left = 8;
	grpEndereco->Show();
	logradouro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grpEnderecoExit(TObject *Sender)
{
	grpEndereco->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btPesqPlanoContaClick(TObject *Sender)
{
	SfgBrowse::EscolhePlanoConta(this,&SearchPlanoConta);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::SearchPlanoConta(Variant Value) {
	cod_plano_conta->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btPesqCentroCustoClick(TObject *Sender)
{
	SfgBrowse::EscolheCentroCusto(this,&SearchCentroCusto);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::SearchCentroCusto(Variant Value) {
	cod_centro_custo->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::btFechamentoClick(TObject *Sender)
{
	if (MessageBox(Handle, "Confirma o fechamento do orçamento?",Caption.c_str(),APP_QUESTION)==ID_NO) {
		return;
	}
	AlteraSituacao("F");
	MessageBox(Handle,"Orçamento fechado com sucesso!",Caption.c_str(), APP_INFORM);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::AlteraSituacao(String Situacao)
{
	QyOrcamento->Edit();
	QyOrcamento->FieldByName("ies_situacao")->AsString = Situacao;
	//Deve retirar os eventos para não reenviar os itens, pois os mesmos não alteram
	QyOrcamento->BeforePost = NULL;
	QyOrcamento->AfterPost = NULL;
	QyOrcamento->Post();
	//Atribuindo novamente os eventos
	QyOrcamento->BeforePost = &QyOrcamentoAfterPost;
	QyOrcamento->AfterPost = &QyOrcamentoBeforePost;
	QySitPedidoVenda->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::cod_forma_pagtoChange(TObject *Sender)
{
	TBDVdp1002Object *Obj = (TBDVdp1002Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = QyOrcamento->FieldByName("valor_total")->AsFloat;
		QyCadPagto->Post();
		QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	}
	UpDwNumParcelas->Invalidate();
	if (!Obj->ies_parcelado) {
		RecalculaParcelas();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::UpDwNumParcelasClick(TObject *Sender,
		TUDBtnType Button)
{
	if (Button == btNext) {
		QyCadPagto->Last();
		//Adiciona uma linha no GRID de parcelas
		QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
		QyCadPagto->Insert();
		QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
		if (QyOrcamento->State == dsEdit)
			QyCadPagto->FieldByName("cod_orcamento")->AsInteger = cod_orcamento->Field->AsInteger;
		else
			QyCadPagto->FieldByName("cod_orcamento")->AsInteger = 0;
		QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
		QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
		QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
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
void __fastcall TVdp1002::QyDetalheBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::EditPagtoSetFocus(TObject *Sender)
{
	if(QyOrcamento->State == dsInsert || QyOrcamento->State == dsEdit) {
		if (grdPagtos->SelectedField->FieldName == "valor_parcela") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::DbGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grdPagtosDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "data_vencimento") {
		DrawCalendarGrid(grdPagtos,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grdPagtosEditButtonClick(TObject *Sender)
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
			if(QyOrcamento->State == dsEdit || QyOrcamento->State == dsInsert) {
				if (!(QyCadPagto->State == dsEdit))
					QyCadPagto->Edit();
				grdPagtos->SelectedField->AsString = sDate;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::ValorParcelaSetText(TField *Sender,
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
		QyOrcamento->FieldByName("pagto_total")->AsFloat += (v - Sender->AsFloat);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::EditItemSetFocus(TObject *Sender)
{
	if(QyOrcamento->State == dsInsert || QyOrcamento->State == dsEdit) {
		if (grdItens->SelectedField->FieldName == "qtd_produto" ||
			 grdItens->SelectedField->FieldName == "preco_venda" ||
			 grdItens->SelectedField->FieldName == "val_desconto") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyCadProdutoCalcFields(TDataSet *DataSet)
{
	QyCadProduto->FieldByName("valor_total")->AsFloat =
	QyCadProduto->FieldByName("qtd_produto")->AsFloat *
	(QyCadProduto->FieldByName("preco_venda")->AsFloat -
	QyCadProduto->FieldByName("val_desconto")->AsFloat);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grdItensDrawColumnCell(TObject *Sender,
		const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->FieldName == "cod_produto") {
		DrawSearchGrid(grdItens,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CodProdutoValidate(TField *Sender)
{
	if(Sender->AsString.Length() == 0) {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		return;
	}
	//Deve validar o código do item
	QyCnsProduto->Active = false;
	QyCnsProduto->Params->ParamByName("cod_produto")->Value = Sender->Value;
	QyCnsProduto->Active = true;
	if(QyCnsProduto->RecordCount > 0) {
		float fOldTotal, fNewTotal;
		QyCadProduto->FieldByName("den_produto")->AsString = QyCnsProduto->FieldByName("den_produto")->AsString;
		fOldTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("preco_venda")->AsFloat = QyCnsProduto->FieldByName("preco_venda")->AsFloat;
		fNewTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyOrcamento->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		CalculaDifTotalPagto();
	} else {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		throw Exception("Produto não cadastrado ou está inativo!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QtdProdutoSetText(TField *Sender, const AnsiString Text)
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
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		fNewTotal = fValor *
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat -
						QyCadProduto->FieldByName("val_desconto")->AsFloat);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyOrcamento->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::PrecoVendaSetText(TField *Sender, const AnsiString Text)
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
		QyOrcamento->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::ValDescontoSetText(TField *Sender, const AnsiString Text)
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
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat - Sender->AsFloat);
		fNewTotal = QyCadProduto->FieldByName("qtd_produto")->AsFloat *
					  (QyCadProduto->FieldByName("preco_venda")->AsFloat - fValor);
		QyCadProduto->FieldByName("valor_total")->AsFloat = fNewTotal;
		QyOrcamento->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::grdItensEditButtonClick(TObject *Sender)
{
	if (!(QyOrcamento->State == dsInsert || QyOrcamento->State == dsEdit))
		return;
	if (grdItens->SelectedField->FieldName == "cod_produto") {
		SfgBrowse::EscolheProduto(this,&SearchProduto);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::SearchProduto(Variant Value) {
	if (QyCadProduto->State != dsEdit)
		QyCadProduto->Edit();
	QyCadProduto->FieldByName("cod_produto")->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::CodCentroCustoValidate(TField *Sender)
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
void __fastcall TVdp1002::CodPlanoContaValidate(TField *Sender)
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
void __fastcall TVdp1002::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoAfterOpen(TDataSet *DataSet)
{
	QyCliente->Active = true;
	QyCadProduto->Active = true;
	QyCadPagto->Active = true;
	QySitPedidoVenda->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1002::QyOrcamentoBeforeClose(TDataSet *DataSet)
{
	QyCliente->Active = false;
	QyCadProduto->Active = false;
	QyCadPagto->Active = false;
	QySitPedidoVenda->Active = false;
}
//---------------------------------------------------------------------------

