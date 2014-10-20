/*
Módulo: Vendas
Função: Cadastro Pedidos de Venda
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
#include "uVdp3001.h"
#include "uVdp1003.h"
#include "uSfgVdpCustom.h"
#pragma hdrstop
#include "uVdp1001.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1001(void) {
   AddAppForm("Vdp1001","Pedidos de Venda",APP_MODULO_VENDAS);
   AddAppFormClass("TVdp1001",__classid(TVdp1001));
}
#pragma startup RegisterVdp1001
//---------------------------------------------------------------------------
__fastcall TVdp1001::TVdp1001(TComponent* Owner)
	: TfrmBase02(Owner)
{
   CarregarSitOrcamento();
	CarregarTipoPessoa();
	CarregarEstado();
	CarregarFormaPagto();
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsCadVenda;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   SfgToolbar->WorkEdition->AfterWorkEdition = &AfterWorkEdition;
   //Adicionando os eventos customizados dos campos
   QyCadVenda->FieldByName("cod_cliente")->OnValidate = &CodClienteValidate;
   QyCadVenda->FieldByName("cod_representante")->OnValidate = &CodRepresentanteValidate;
   QyCadVenda->FieldByName("cod_plano_conta")->OnValidate = &CodPlanoContaValidate;
   QyCadVenda->FieldByName("cod_centro_custo")->OnValidate = &CodCentroCustoValidate;
   //Adicionando os campos do DataSet Cliente
   String ClienteColumns = SfgToolbar->ParserSelectColumns(QyCliente->SQL->Text);
   TSfgMetaTable *MetaTable = AddMetaTable("tbl_cliente");
   CreateFieldDefs(MetaTable, ClienteColumns, QyCliente);
   CreateFields(QyCliente);
   QyCliente->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;

	pWorkEdtCliente = new SfgWorkEdition(DsClientes,this);
	pWorkEdtCliente->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	AfterWorkEdition(false,AppConfig->Colors->Disabled);
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
   this->WindowProc = &SubClassWndProc;
   //Força o botão percentual pertencer ao SfgToolbar
	btFechamento->Parent = SfgToolbar;
	btFechamento->Top = 6;
	btFechamento->TabOrder = SfgToolbar->btDelete->TabOrder + 1;
	btRelatorio->Parent = SfgToolbar;
	btRelatorio->Top = 6;
	btRelatorio->TabOrder = btFechamento->TabOrder + 1;
	btImportar->Parent = SfgToolbar;
	btImportar->Top = 6;
	btImportar->TabOrder = btRelatorio->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btFechamento);
	this->Tolltips->AddToolTip(btRelatorio);
	this->Tolltips->AddToolTip(btImportar);
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   if(hSfgVdpCustom) {
      SfgVdp1001AfterCreate = (PSfgVdp1001AfterCreate)GetProcAddress(hSfgVdpCustom,"SfgVdp1001AfterCreate");
      SfgVdp1001AfterValidInsert = (PSfgVdp1001AfterValidInsert)GetProcAddress(hSfgVdpCustom,"SfgVdp1001AfterValidInsert");
      SfgVdp1001AfterValidUpdate = (PSfgVdp1001AfterValidUpdate)GetProcAddress(hSfgVdpCustom,"SfgVdp1001AfterValidUpdate");
      if (SfgVdp1001AfterCreate)
         SfgVdp1001AfterCreate(this);
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::AfterCreateFields(TDataSet *DataSet)
{
   //Adicionando o campo virtual na tabela
	DynamicArray<String> FieldDefs;
	FieldDefs.Length = 1;
	FieldDefs[0] = "fkCalculated|pagto_total|ftFloat|0|Pagto Total";
   AddVirtualFields(FieldDefs,QyCadVenda,true);
   ((TFloatField*)QyCadVenda->FieldByName("pagto_total"))->currency = true;
   //Marcando campo como auto incremento
   QyCadVenda->FieldByName("cod_pedido_venda")->AutoGenerateValue = arAutoInc;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   TfrmBase02::SetPermissao(Nivel);
   //Escondendo as opções de menu do SfgToolbar
	execFechamento->Visible = false;
	execImportar->Visible = false;
   //Desabilitando as teclas de atalho também
	execFechamento->Enabled = false;
	execImportar->Enabled = false;
   btRelatorio->Left = SfgToolbar->btExit->Left;
   SfgToolbar->btExit->Left += 38;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::FilterCodVenda(int CodVenda)
{
   SfgToolbar->WhereFilter = "cod_pedido_venda = " + IntToStr(CodVenda);
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
void __fastcall TVdp1001::SubClassWndProc(Messages::TMessage &Message)
{
   if (Message.Msg == WM_SFGEXECPARAM) {
      //Trata as possibilidades de executar este programa por parâmetros
      if (Message.WParam == 1) {//Opção de execução da função de filtro
         this->FilterCodVenda(Message.LParam);
      } else if (Message.WParam == 2) { //Opção de execução de inclusão de novo registro
         this->SfgToolbar->btNew->Click();
      }
      Message.Result = 1;
   } else {
      this->WndProc(Message);
   }

}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::ValidInsert(bool &bValid)
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
   if (SfgVdp1001AfterValidInsert != NULL) {
      if (!SfgVdp1001AfterValidInsert(this,QyCadVenda)) {
		   bValid = false;
		   PostStatus = false;
		   return;
      }
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   if (SfgVdp1001AfterValidUpdate != NULL) {
      if (!SfgVdp1001AfterValidUpdate(this,QyCadVenda)) {
		   bValid = false;
		   PostStatus = false;
		   return;
      }
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::ValidDelete(bool &bValid)
{
	String SQL;
	String Situacao;
	QySitPedidoVenda->Refresh();
	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
	if(Situacao != "A") {
		MessageBox(Handle, "Situação do pedido de venda diferente de aberto. Não pode ser excluído!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		PostStatus = false;
		return;
	}
	/*SQL = "SELECT DISTINCT 1 FROM tbl_orcamento_produto" \
			" WHERE cod_orcamento = " + QuotedStr(cod_orcamento->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Orcamento possui produtos já relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}*/
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CarregarSitOrcamento()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Aberto","A");
	ies_situacao->AddItem("Fechado","F");
	ies_situacao->AddItem("Faturado","T");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CarregarTipoPessoa()
{
	tipo_pessoa->Clear();
	tipo_pessoa->AddItem("Pessoa Física","F");
	tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CarregarEstado()
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
void __fastcall TVdp1001::cod_ufChange(TObject *Sender)
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
void __fastcall TVdp1001::CarregarFormaPagto()
{
  TBDVdp1001Object *Obj;
  TZQuery *QyPagto = new TZQuery(this);
try
{
	QyPagto->SQL->Text = "SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado, ies_financeiro FROM tbl_forma_pagto";
	QyPagto->Connection = AppConnection;
	QyPagto->Active = true;
	cod_forma_pagto->Clear();
	while(!QyPagto->Eof) {
		Obj = new TBDVdp1001Object();
		Obj->SetValue(QyPagto->FieldByName("cod_forma_pagto")->Value);
      Obj->ies_parcelado = (bool)(QyPagto->FieldByName("ies_parcelado")->AsString == "S");
      Obj->ies_financeiro = (bool)(QyPagto->FieldByName("ies_financeiro")->AsString == "S");
		cod_forma_pagto->AddItem(QyPagto->FieldByName("den_forma_pagto")->AsString, (TObject*)Obj);
		QyPagto->Next();
  }
}__finally{delete(QyPagto);}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
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
bool __fastcall TVdp1001::VerificaCampos()
{
	bool bItem = false;
	bool bPagto = false;
	if(!cod_cliente->Text.Length()) {
		MessageBox(Handle, "Digite o código do cliente do pedido de venda!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
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
bool __fastcall TVdp1001::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SearchCliente(Variant Value) {
	cod_cliente->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CodClienteValidate(TField *Sender)
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
void __fastcall TVdp1001::HabilitaCadCliente()
{
	if (QyCliente->State == dsInsert)
		return;
	QyCliente->Insert();
	QyCliente->FieldByName("cod_cliente")->Value = cod_cliente->Field->AsString;
	pWorkEdtCliente->SetWorkEdition(true, true, AppConfig->Colors->Enabled);
	den_cliente->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::DesabilitaCadCliente()
{
	QyCliente->Cancel();
	pWorkEdtCliente->SetWorkEdition(false, true, AppConfig->Colors->Disabled);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_cadastro);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::NavegexecBtEditClickExecute(
		TObject *Sender)
{
	String Situacao;
	bool bAltera = false;
	QySitPedidoVenda->Refresh();
	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
	if (Situacao == "F") {
		if (MessageBox(Handle, "Pedido de venda fechado. Deseja realmente alterar o mesmo?\nEsta ação irá alterar a situação do mesmo para aberto.",Caption.c_str(),APP_QUESTION)==ID_YES) {
			bAltera = true;
		} else {
			return;
		}
	} else if (Situacao == "T") {
		MessageBox(Handle,"Pedido de venda faturado. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	} else if (Situacao == "C") {
		MessageBox(Handle,"Pedido de venda cancelado. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}
	if (bAltera && Situacao == "F") { //Deve estornar o fechamento do pedido
		TZReadOnlyQuery *QyFechaPedido = new TZReadOnlyQuery(Application);
		QyFechaPedido->Connection = AppConnection;
	try {
		if (!SfgDataCenter->StartTrans()) {
		   MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
         return;
      }
		//Reabre o pedido de venda
		//Estornando os itens no estoque
		//Excluindo o registro da conta a receber
		QyFechaPedido->SQL->Text = "CALL reabre_pedido_venda("+ cod_pedido_venda->Text +");";
		QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
		SfgDataCenter->CommitTrans();
		delete QyFechaPedido;
	} catch(Exception &e){
		SfgDataCenter->RollbackTrans();
		String Msg = "Ocorreu o seguinte erro ao reabrir o pedido de venda:\n";
		Msg = Msg + e.Message;
		MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
		delete QyFechaPedido;
		return;
	}
	}
	QySitPedidoVenda->Refresh(); 
	SfgToolbar->btEditClick(Sender);
	if (bAltera)
		QyCadVenda->FieldByName("ies_situacao")->AsString = "A";
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::NavegexecBtSaveClickExecute(TObject *Sender)
{
	QyCadVenda->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
	if (QyCadVenda->FieldByName("cod_representante")->AsString.Length() == 0)
       QyCadVenda->FieldByName("cod_representante")->Value = Null();
	if (QyCadVenda->FieldByName("cod_centro_custo")->AsString.Length() == 0)
       QyCadVenda->FieldByName("cod_centro_custo")->Value = Null();
	if (QyCadVenda->FieldByName("cod_plano_conta")->AsString.Length() == 0)
       QyCadVenda->FieldByName("cod_plano_conta")->Value = Null();
	PostStatus = true;
	if (QyCliente->State == dsInsert) {
		if(!VerificaCamposCliente()) {
			return;
		}
	}
   //Deve verificar se o cliente possui pedidos em atraso
   if(!VerificaClientAtraso(QyCadVenda->FieldByName("cod_cliente")->AsString)) {
      return;
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
	} else {
		SfgDataCenter->RollbackTrans();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::NavegexecBtCancelClickExecute(TObject *Sender)
{
	bool edit = (QyCadVenda->State == dsEdit);
	if (QyCliente->State == dsInsert) {
		DesabilitaCadCliente();
	}
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyCadVendaAfterScroll(QyCadVenda);
   MsgDifTotalPagto->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::NavegexecBtNewClickExecute(TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	//Adiciona uma linha no GRID de itens
	addLineExecute(Sender);
	//Adiciona uma linha no GRID de parcelas
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
	QyCadPagto->FieldByName("cod_pedido_venda")->AsInteger = 0;
	QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_recebido")->AsString = "N";
	QyCadPagto->Post();
	data_cadastro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::NavegexecBtDeleteClickExecute(TObject *Sender)
{
	PostStatus = true;
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
try {
	SfgToolbar->btDeleteClick(Sender);
} catch(Exception &e) {
   String sMsgErro = "Ocorreu o seguinte erro ao excluir o registro:\n";
   sMsgErro = sMsgErro + e.Message;
   MessageBox(Handle,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
	PostStatus = false;
}
	if (PostStatus) {
		SfgDataCenter->CommitTrans();
	} else {
		SfgDataCenter->RollbackTrans();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::AfterWorkEdition(bool Enable, TColor Color)
{
	btPesqPlanoConta->Enabled = Enable;
	btPesqCentroCusto->Enabled = Enable;
	btPesqRepresentante->Enabled = Enable;
	btPesqCliente->Enabled = Enable;
   execImportar->Enabled = !Enable;
	//Habilitando os itens do GRID de itens
	DsCadProduto->AutoEdit = Enable;
	addLine->Enabled = Enable;
	delLine->Enabled = Enable;
	addItens->Enabled = Enable;
	//Habilitando os itens do GRID pagamentos
	DsCompraPagto->AutoEdit = Enable;
	if (Enable) {
		TBDVdp1001Object *Obj = (TBDVdp1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
void __fastcall TVdp1001::addLineExecute(TObject *Sender)
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
	if(QyCadVenda->State == dsEdit)
		QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger = QyCadVenda->FieldByName("cod_pedido_venda")->AsInteger;
	else
		QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger = 0;
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
void __fastcall TVdp1001::delLineExecute(TObject *Sender)
{
	if(QyCadProduto->RecordCount > 0) {
		QyCadVenda->FieldByName("valor_total")->AsFloat -= QyCadProduto->FieldByName("valor_total")->AsFloat;
		QyCadProduto->Delete();
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::addItensExecute(TObject *Sender)
{
   TVdp1004 *Vdp1004 = new TVdp1004(Application);
	Vdp1004->OnConfirmList = &addItensConfirm;
	Vdp1004->ShowModal();
   delete Vdp1004;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::addItensConfirm(TList *pListAdd)
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
		if(QyCadVenda->State == dsEdit)
			QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger = QyCadVenda->FieldByName("cod_pedido_venda")->AsInteger;
		else
			QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger = 0;
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
	QyCadVenda->FieldByName("valor_total")->AsFloat += fValorTotal;
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
void __fastcall TVdp1001::RecalculaParcelas()
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
void __fastcall TVdp1001::CalculaDifTotalPagto()
{
	String Msg;
	if (RoundTo(QyCadVenda->FieldByName("pagto_total")->AsFloat,-2) == RoundTo(QyCadVenda->FieldByName("valor_total")->AsFloat,-2)) {
		MsgDifTotalPagto->Caption = "";
	} else {
		if (QyCadVenda->FieldByName("pagto_total")->AsFloat < QyCadVenda->FieldByName("valor_total")->AsFloat
		) {
			Msg = "O valor total informado para pagamento é menor que o valor total da venda.";
			Msg += "\nDiferença entre o valor total e o pagamento: " + \
			CurrToStrF((QyCadVenda->FieldByName("valor_total")->AsFloat - QyCadVenda->FieldByName("pagto_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clRed;
			MsgDifTotalPagto->Caption = Msg;
		} else {
			Msg = "O valor total informado para pagamento é maior que o valor total da venda.";
			Msg += "\nDiferença entre o pagamento e o valor total: " + \
			CurrToStrF((QyCadVenda->FieldByName("pagto_total")->AsFloat - QyCadVenda->FieldByName("valor_total")->AsFloat),ffCurrency,2);
			MsgDifTotalPagto->Font->Color = clBlue;
			MsgDifTotalPagto->Caption = Msg;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaAfterScroll(TDataSet *DataSet)
{
	QyCliente->Params->ParamByName("cod_cliente")->Value = DataSet->FieldByName("cod_cliente")->Value;
	QyCliente->Refresh();
	UpDwNumParcelas->Position = DataSet->FieldByName("num_parcelas")->AsInteger;
   TipoPessoaChange(tipo_pessoa->Field);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaCalcFields(TDataSet *DataSet)
{
	QyCadVenda->FieldByName("pagto_total")->AsFloat = QyCadVenda->FieldByName("valor_total")->AsFloat;
}
//---------------------------------------------------------------------------
//No evento de BeforPost ele desassocia os datasets das querys filhas para não recarregar
void __fastcall TVdp1001::QyCadVendaBeforePost(TDataSet *DataSet)
{
	QyCadProduto->DataSource = NULL;
	QyCadPagto->DataSource = NULL;
	QyCadVenda->AfterScroll = NULL;
	//Se está inserindo um cliente deve postar o mesmo primeiro
	if (QyCliente->State == dsInsert) {
		QyCliente->Post();
		pWorkEdtCliente->SetWorkEdition(false, true, AppConfig->Colors->Disabled);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaAfterPost(TDataSet *DataSet)
{
try {
try {
	int iSeq = 1;  //Utilizado para refazer a ordenação dos produtos 
	//Verificação para atualizar o campo código do mestre nos itens
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	QyCadProduto->First();
	while (!QyCadProduto->Eof) {
		if (QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger == 0) {
			QyCadProduto->Edit();
			QyCadProduto->FieldByName("cod_pedido_venda")->AsInteger = QyCadVenda->FieldByName("cod_pedido_venda")->AsInteger;
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
		if (QyCadPagto->FieldByName("cod_pedido_venda")->AsInteger == 0) {
			QyCadPagto->Edit();
			QyCadPagto->FieldByName("cod_pedido_venda")->AsInteger = QyCadVenda->FieldByName("cod_pedido_venda")->AsInteger;
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
	QyCadProduto->DataSource = DsCadVenda;
	QyCadPagto->DataSource = DsCadVenda;
	QyCadVenda->AfterScroll = &QyCadVendaAfterScroll;
}
}
//--------------------------------------------------------------------
bool __fastcall TVdp1001::VerificaCamposCliente()
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
void __fastcall TVdp1001::QyCadVendaBeforeDelete(TDataSet *DataSet)
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
void __fastcall TVdp1001::btRelatorioClick(TObject *Sender)
{
	TVdp3001 *Vdp3001 = new TVdp3001(Owner);
	Vdp3001->CnsPedidoVenda->Active = false;
	Vdp3001->CnsPedidoVenda->Params->ParamByName("cod_pedido_venda")->Value = QyCadVenda->FieldByName("cod_pedido_venda")->Value;
	Vdp3001->CnsPedidoVenda->Active = true;
   if(Vdp3001->RpRelatBase->PrepareReport(true))
      Vdp3001->RpRelatBase->ShowPreparedReport();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btPesqClienteClick(TObject *Sender)
{
	SfgBrowse::EscolheCliente(this,&SearchCliente);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btEnderecoClick(TObject *Sender)
{
	grpEndereco->Top = 235;
	grpEndereco->Left = 8;
	grpEndereco->Show();
	logradouro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grpEnderecoExit(TObject *Sender)
{
	grpEndereco->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btPesqPlanoContaClick(TObject *Sender)
{
	SfgBrowse::EscolhePlanoConta(this,&SearchPlanoConta);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SearchPlanoConta(Variant Value) {
	cod_plano_conta->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btPesqCentroCustoClick(TObject *Sender)
{
	SfgBrowse::EscolheCentroCusto(this,&SearchCentroCusto);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SearchCentroCusto(Variant Value) {
	cod_centro_custo->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::btFechamentoClick(TObject *Sender)
{
   bool bFechado = false;
	String Situacao;
	QySitPedidoVenda->Refresh();
	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		MessageBox(Handle, "Pedido de venda já fechado.",Caption.c_str(),APP_INFORM);
		return;
	} else if(Situacao == "C") {
		MessageBox(Handle, "Pedido de venda cancelado.",Caption.c_str(),APP_INFORM);
		return;
	} else if(MessageBox(Handle, "Confirma o fechamento do pedido de venda?",Caption.c_str(),APP_QUESTION)==ID_NO) {
		return;
	}
	//Verifica se o pagamento é parcelado, caso não seja, pergunta ao usuário seo mesmo deseja baixar já a conta a pagar
	bool liquidado = false;
	TBDVdp1001Object *Obj = (TBDVdp1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
	if (Obj->ies_financeiro && !Obj->ies_parcelado) {
		if (MessageBox(Handle, "Pagamento do pedido de venda não é parcelado.\nDeseja lançar a conta a receber como liquidada?",Caption.c_str(),APP_QUESTION)==ID_YES) {
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
	   //Fecha o pedido de venda
	   //Baixando os itens no estoque
	   //Incluindo o registro da conta a receber
	   //Liquidando o pagamento, este processo também já efetua o lançamento no caixa
	   SQL = "CALL fecha_pedido_venda("+ cod_pedido_venda->Text +"," + ((liquidado) ? "1" : "0") + ");";
	   QyFechaPedido->SQL->Text = SQL;
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
   } else {
	   //Fecha o pedido de venda
	   //Baixando os itens no estoque
	   QyFechaPedido->SQL->Text = "CALL baixa_pedido_venda_estoque("+ cod_pedido_venda->Text +");";
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
	   SQL = "UPDATE tbl_pedido_venda SET ies_situacao = 'F', data_fechamento = now()";
      SQL += " WHERE cod_pedido_venda = " + cod_pedido_venda->Text;
	   QyFechaPedido->SQL->Text = SQL;
	   QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
   }
	SfgDataCenter->CommitTrans();
   bFechado = true;
} catch(Exception &e){
	SfgDataCenter->RollbackTrans();
	String Msg = "Ocorreu o seguinte erro ao efetuar o fechamento do pedido de venda:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
	delete QyFechaPedido;
	QySitPedidoVenda->Refresh();
	if (liquidado) {
		QyCadPagto->Refresh();
	}
   if (bFechado)
	   MessageBox(Handle,"Pedido de venda fechado com sucesso!",Caption.c_str(), APP_INFORM);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::execImportarExecute(TObject *Sender)
{
	TVdp1003 *Vdp1003 = new TVdp1003(Application);
	Vdp1003->AfterImport = &AfterImport;
	Vdp1003->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::AfterImport()
{
	QyCadVenda->Refresh();
	SfgToolbar->btLast->Click();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::cod_forma_pagtoChange(TObject *Sender)
{
	TBDVdp1001Object *Obj = (TBDVdp1001Object*)cod_forma_pagto->Items->Objects[cod_forma_pagto->ItemIndex];
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
		QyCadPagto->FieldByName("valor_parcela")->AsFloat = QyCadVenda->FieldByName("valor_total")->AsFloat;
		QyCadPagto->Post();
		QyCadPagto->EnableControls(); //Para ativar a atualização da tela
	}
	UpDwNumParcelas->Invalidate();
	if (!Obj->ies_parcelado) {
		RecalculaParcelas();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::UpDwNumParcelasClick(TObject *Sender,
		TUDBtnType Button)
{
	if (Button == btNext) {
		QyCadPagto->Last();
		//Adiciona uma linha no GRID de parcelas
		QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
		QyCadPagto->Insert();
		QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
		if (QyCadVenda->State == dsEdit)
			QyCadPagto->FieldByName("cod_pedido_venda")->AsInteger = cod_pedido_venda->Field->AsInteger;
		else
			QyCadPagto->FieldByName("cod_pedido_venda")->AsInteger = 0;
		QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
		QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
		QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
		QyCadPagto->FieldByName("ies_recebido")->AsString = "N";
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
void __fastcall TVdp1001::QyDetalheBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::EditPagtoSetFocus(TObject *Sender)
{
	if(QyCadVenda->State == dsInsert || QyCadVenda->State == dsEdit) {
		if (grdPagtos->SelectedField->FieldName == "valor_parcela") {
			((TEdit*)Sender)->OnKeyPress = &grdEditCtrlKeyPress;
		} else {
			((TEdit*)Sender)->OnKeyPress = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdPagtosColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_recebido") {
		Options = grdPagtos->Options;
		Options >> dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdPagtosColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdPagtos->SelectedField->FieldName == "ies_recebido") {
		Options = grdPagtos->Options;
		Options << dgEditing;
		grdPagtos->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::DbGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdPagtosDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "ies_recebido") {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdPagtos,-1,-1,Rect,State,bChecked);
	} else if (Column->Field->FieldName == "data_vencimento") {
		DrawCalendarGrid(grdPagtos,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdPagtosEditButtonClick(TObject *Sender)
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
			if(QyCadVenda->State == dsEdit || QyCadVenda->State == dsInsert) {
				if (!(QyCadPagto->State == dsEdit))
					QyCadPagto->Edit();
				grdPagtos->SelectedField->AsString = sDate;
			}
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::ValorParcelaSetText(TField *Sender,
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
		QyCadVenda->FieldByName("pagto_total")->AsFloat += (v - Sender->AsFloat);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::EditItemSetFocus(TObject *Sender)
{
	if(QyCadVenda->State == dsInsert || QyCadVenda->State == dsEdit) {
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
void __fastcall TVdp1001::QyCadProdutoCalcFields(TDataSet *DataSet)
{
	QyCadProduto->FieldByName("valor_total")->AsFloat =
	QyCadProduto->FieldByName("qtd_produto")->AsFloat *
	(QyCadProduto->FieldByName("preco_venda")->AsFloat -
	QyCadProduto->FieldByName("val_desconto")->AsFloat);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdItensDrawColumnCell(TObject *Sender,
		const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->FieldName == "cod_produto") {
		DrawSearchGrid(grdItens,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CodProdutoValidate(TField *Sender)
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
		QyCadVenda->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		CalculaDifTotalPagto();
	} else {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		throw Exception("Produto não cadastrado ou está inativo!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QtdProdutoSetText(TField *Sender, const AnsiString Text)
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
		QyCadVenda->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::PrecoVendaSetText(TField *Sender, const AnsiString Text)
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
		QyCadVenda->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::ValDescontoSetText(TField *Sender, const AnsiString Text)
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
		QyCadVenda->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
		CalculaDifTotalPagto();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::grdItensEditButtonClick(TObject *Sender)
{
	if (!(QyCadVenda->State == dsInsert || QyCadVenda->State == dsEdit))
		return;
	if (grdItens->SelectedField->FieldName == "cod_produto") {
		SfgBrowse::EscolheProduto(this,&SearchProduto);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SearchProduto(Variant Value) {
	if (QyCadProduto->State != dsEdit)
		QyCadProduto->Edit();
	QyCadProduto->FieldByName("cod_produto")->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CodCentroCustoValidate(TField *Sender)
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
void __fastcall TVdp1001::CodPlanoContaValidate(TField *Sender)
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
void __fastcall TVdp1001::btPesqRepresentanteClick(TObject *Sender)
{
	SfgBrowse::EscolheRepresentante(this,&SearchRepresentante);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::SearchRepresentante(Variant Value)
{
	cod_representante->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::CodRepresentanteValidate(TField *Sender)
{
	String sSQL;
	if(!Sender->AsString.Length())
		return;
	sSQL = "SELECT cod_representante FROM tbl_representante" \
			" WHERE cod_representante = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		throw Exception("Representante não cadastrado!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaPostError(TDataSet *DataSet,
      EDatabaseError *E, TDataAction &Action)
{
   PostStatus = false;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaAfterOpen(TDataSet *DataSet)
{
	QyCliente->Active = true;
	QyCadProduto->Active = true;
	QyCadPagto->Active = true;
	QySitPedidoVenda->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaBeforeClose(TDataSet *DataSet)
{
	QyCliente->Active = false;
	QyCadProduto->Active = false;
	QyCadPagto->Active = false;
	QySitPedidoVenda->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1001::QyCadVendaAfterInsert(TDataSet *DataSet)
{
	QyCadVenda->FieldByName("data_cadastro")->Value = Now();
	QyCadVenda->FieldByName("ies_situacao")->Value = "A";
	cod_forma_pagto->ItemIndex = 0;
	cod_forma_pagto->Field->Value = cod_forma_pagto->Value;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1001::VerificaClientAtraso(String CodCliente)
{
   String SQL = \
   "SELECT DISTINCT 1\
  FROM tbl_conta_receber_pagto pagto\
 INNER JOIN tbl_conta_receber conta\
    ON conta.cod_conta_receber = pagto.cod_conta_receber\
 WHERE conta.cod_cliente = " + QuotedStr(CodCliente) + "\
   AND pagto.ies_recebido = 'N'\
   AND pagto.data_vencimento < DATE(now())";

   if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
      String Pergunta = "O cliente possui parcelas em atraso.\nConfirma a inclusão de novo pedido para o mesmo?";
      if (MessageBox(Handle, Pergunta.c_str(),Caption.c_str(),APP_QUESTION) == ID_NO)
         return false;
   }
   return true;
}
//---------------------------------------------------------------------------



