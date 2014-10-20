/*
Módulo: Vendas
Função: Cadastro Notas Fiscais Saída
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//--------------------------------------------------------------------------
#include <vcl.h>
#include <math.hpp>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#include "uSfgWorkEdition.h"
#include "uSfgCalendar.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uSfgBrowseVdp.h"
#include "uSfgBrowseObf.h"
#include "uObf1003.h"
#include "uObf1004.h"
#include "uObf1005.h"
#include "uObf1007.h"
#include "uSfgXmlNFe.h"
#pragma hdrstop
#include "uObf1001.h"
#include "ThemedDBGrid.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterObf1001(void) {
   AddAppForm("Obf1001","Notas Fiscais Saída",APP_MODULO_FISCAL);
   AddAppFormClass("TObf1001",__classid(TObf1001));
} 
#pragma startup RegisterObf1001
//---------------------------------------------------------------------------
__fastcall TObf1001::TObf1001(TComponent* Owner)
	: TfrmBase02(Owner)
{
   pgDetalhes->ActivePageIndex = 0;
   CarregarSitNotaFiscal();
   CarregarFormaPagto();
   CarregarTipoFrete();
	CarregarEstado();
   QyNotaFiscal->ParamByName("cod_empresa")->AsString = AppUser->CodEmpresa;
   SfgToolbar->SelectColumns = "\
cod_empresa;cod_nota_fiscal;tipo_nota_fiscal;num_nota_fiscal;serie_nota_fiscal;\
modelo_nota_fiscal;ies_situacao;cod_natureza_operacao;cod_forma_pagto;cod_cliente;\
cod_transportador;tipo_frete;placa_veiculo;estado_placa_veiculo;placa_reboque;\
estado_placa_reboque;qtd_volume;especie_volume;marca_volume;numeracao_volume;\
peso_liquido;peso_bruto;volume_cubico;valor_mercadoria;valor_desconto;valor_duplicata;\
valor_frete;valor_seguro;outras_despesas;valor_nota_fiscal;usuario_inclusao;\
data_hora_emissao;data_hora_saida;data_hora_cancelamento;motivo_cancelamento;\
usuario_cancelamento;info_complementar; info_adicional_fisco;";
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
	SfgToolbar->DataSource = DsNotaFiscal;
	SfgToolbar->ValidInsert = &ValidInsert;
	SfgToolbar->ValidUpdate = &ValidUpdate;
	SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->BeforeShowCombo = &BeforeShowCombo;
   //Adicionando os eventos customizados aos campos
   QyNotaFiscal->FieldByName("cod_cliente")->OnValidate = &CodClienteValidate;
   QyNotaFiscal->FieldByName("cod_natureza_operacao")->OnValidate = &NaturezaOperacaoValidate;
   QyNotaFiscal->FieldByName("cod_transportador")->OnValidate = &CodTransportadorValidate;
	HabilitarItens(false);
	ies_situacao->Color = AppConfig->Colors->Disabled;
	//Hack* - Evento customizado do componente Edit do Grid
	((TThemeDBGrid*)grdItens)->OnEditSetFocus = &EditItemSetFocus;
   //Adicionando os campos do DataSet Cliente
   String ClienteColumns = SfgToolbar->ParserSelectColumns(QyCliente->SQL->Text);
   TSfgMetaTable *MetaTable = AddMetaTable("tbl_cliente");
   CreateFieldDefs(MetaTable, ClienteColumns, QyCliente);
   CreateFields(QyCliente);
   QyCliente->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;
	//TStrings *pStrings = SfgToolbar->WorkEdition->GetListControls();
	//pStrings->Delete(pStrings->IndexOf("data_hora_emissao"));
	//data_hora_emissao->ReadOnly = true;
	//data_hora_emissao->Color = AppConfig->Colors->Disabled;
   DesabilitaCampos();
   //this->WindowProc = &SubClassWndProc;
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
	btNumNF->Parent = SfgToolbar;
	btNumNF->Top = 6;
	btNumNF->TabOrder = btImportar->TabOrder + 1;
	//Como redefiniu o Parent deve redefinir a ToolTip
	this->Tolltips->AddToolTip(btFechamento);
	this->Tolltips->AddToolTip(btRelatorio);
	this->Tolltips->AddToolTip(btImportar);
	this->Tolltips->AddToolTip(btNumNF);
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   //if(hSfgObfCustom) {}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::AfterCreateFields(TDataSet *DataSet)
{
   //Adicionando o campo virtual na tabela
// FieldKind,FieldName,DataType,Size,DisplayLabel,IsPkKey,Visible,DisplayWidth,Precision,EditMask,DisplayFormat
	DynamicArray<String> FieldDefs;
	FieldDefs.Length = 9;
	FieldDefs[0] = "fkInternalCalc|base_calc_icms|ftFloat|0|BC ICMS|0|1|16|2";
	FieldDefs[1] = "fkInternalCalc|valor_icms|ftFloat|0|Valor ICMS|0|1|16|2";
	FieldDefs[2] = "fkInternalCalc|base_calc_icms_st|ftFloat|0|BC ICMS ST|0|1|16|2";
	FieldDefs[3] = "fkInternalCalc|valor_icms_st|ftFloat|0|Valor ICMS ST|0|1|16|2";
	FieldDefs[4] = "fkInternalCalc|base_calc_ipi|ftFloat|0|BC IPI|0|1|16|2";
	FieldDefs[5] = "fkInternalCalc|valor_ipi|ftFloat|0|Valor IPI|0|1|16|2";
	FieldDefs[6] = "fkInternalCalc|data_saida|ftDate|0|Data Saída|0|1|10|0|!90/90/0099;1;_|dd/mm/yyyy|";
	FieldDefs[7] = "fkInternalCalc|hora_saida|ftString|8|Hora Saída|0|1|8|0|!90:00:00;1;_";
	FieldDefs[8] = "fkCalculated|vazio_calc|ftString|1|Vazio|0|0|1";
   AddVirtualFields(FieldDefs,QyNotaFiscal,true);
   ((TFloatField*)QyNotaFiscal->FieldByName("base_calc_icms"))->currency = true;
   ((TFloatField*)QyNotaFiscal->FieldByName("valor_icms"))->currency = true;
   ((TFloatField*)QyNotaFiscal->FieldByName("base_calc_icms_st"))->currency = true;
   ((TFloatField*)QyNotaFiscal->FieldByName("valor_icms_st"))->currency = true;
   ((TFloatField*)QyNotaFiscal->FieldByName("base_calc_ipi"))->currency = true;
   ((TFloatField*)QyNotaFiscal->FieldByName("valor_ipi"))->currency = true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::SetPermissao(int Nivel)
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
void __fastcall TObf1001::DesabilitaCampos()
{
	den_cliente->Color = AppConfig->Colors->Disabled;
	cpf_cnpj->Color = AppConfig->Colors->Disabled;
	rg_ie->Color = AppConfig->Colors->Disabled;
	telefone->Color = AppConfig->Colors->Disabled;
	logradouro->Color = AppConfig->Colors->Disabled;
	numero->Color = AppConfig->Colors->Disabled;
	cod_uf_cliente->Color = AppConfig->Colors->Disabled;
	cod_cidade_cliente->Color = AppConfig->Colors->Disabled;
	cep->Color = AppConfig->Colors->Disabled;
	bairro->Color = AppConfig->Colors->Disabled;
	complemento->Color = AppConfig->Colors->Disabled;
	den_natureza_operacao->Color = AppConfig->Colors->Disabled;
	den_transportador->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::FilterNotaFiscal(int NotaFiscal)
{
	QyNotaFiscal->Filter = "cod_nota_fiscal = " + IntToStr(NotaFiscal);
	QyNotaFiscal->Filtered = true;
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
void __fastcall TObf1001::SubClassWndProc(Messages::TMessage &Message)
{
   if (Message.Msg == WM_SFGEXECPARAM) {
      //Trata as possibilidades de executar este programa por parâmetros
      if (Message.WParam == 1) {//Opção de execução da função de filtro
         this->FilterNotaFiscal(Message.LParam);
      } else if (Message.WParam == 2) { //Opção de execução de inclusão de novo registro
         this->SfgToolbar->btNew->Click();
      }
      Message.Result = 1;
   } else {
      this->WndProc(Message);
   }

}
//---------------------------------------------------------------------------
void __fastcall TObf1001::ValidInsert(bool &bValid)
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
void __fastcall TObf1001::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
		bValid = false;
		PostStatus = false;
      return;
	}
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::ValidDelete(bool &bValid)
{
	String SQL;
	String Situacao;
	QySitNotaFiscal->Refresh();
	Situacao = QySitNotaFiscal->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		MessageBox(Handle, "Nota fiscal faturada. Não pode ser excluída!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		PostStatus = false;
		return;
	}
	if(Situacao == "C") {
		MessageBox(Handle, "Nota fiscal cancelada. Não pode ser excluída!",Caption.c_str(),APP_ATENTION);
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
void __fastcall TObf1001::CarregarSitNotaFiscal()
{
	ies_situacao->Clear();
	ies_situacao->AddItem("Aberto","A");
	ies_situacao->AddItem("Fechado","F");
	ies_situacao->AddItem("Cancelado","C");
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CarregarFormaPagto()
{
	cod_forma_pagto->Clear();
	cod_forma_pagto->AddItem("Pagamento à vista",Variant(0));
	cod_forma_pagto->AddItem("Pagamento à prazo",Variant(1));
	cod_forma_pagto->AddItem("Outros",Variant(2));
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CarregarTipoFrete()
{
	tipo_frete->Clear();
	tipo_frete->AddItem("Por conta do emitente",Variant(0));
	tipo_frete->AddItem("Por conta do destinatário/remetente",Variant(1));
	tipo_frete->AddItem("Por conta de terceiros",Variant(2));
	tipo_frete->AddItem("Sem frete",Variant(9));
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CarregarEstado()
{
  TZQuery *QyUF = new TZQuery(this);
  cod_uf_cliente->Clear();
  cod_uf_placa_veiculo->Clear();
try
{
  QyUF->SQL->Text = "SELECT cod_uf FROM tbl_uf ORDER BY cod_uf";
  QyUF->Connection = AppConnection;
  QyUF->Active = true;
  while(!QyUF->Eof) {
	 cod_uf_cliente->AddItem(QyUF->FieldByName("cod_uf")->AsString,NULL);
    QyUF->Next();
  }
}__finally{delete(QyUF);}
   cod_uf_placa_veiculo->Items->AddStrings(cod_uf_cliente->Items);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   if (Filter->Field->FieldName == "ies_situacao") {
      ComboBox->Clear();
      ComboBox->Items->Assign(ies_situacao->Items);
   } else
   if (Filter->Field->FieldName == "cod_forma_pagto") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_forma_pagto->Items);
   } else
   if (Filter->Field->FieldName == "tipo_frete") {
      ComboBox->Clear();
      ComboBox->Items->Assign(tipo_frete->Items);
   } else
   if (Filter->Field->FieldName == "cod_uf_placa_veiculo") {
      ComboBox->Clear();
      ComboBox->Items->Assign(cod_uf_placa_veiculo->Items);
   }
}
//---------------------------------------------------------------------------
bool __fastcall TObf1001::VerificaCampos()
{
	bool bItem = false;
	if(!cod_cliente->Text.Length()) {
		MessageBox(Handle, "Digite o código do cliente da nota fiscal!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
		return false;
	}
	/*if (RoundTo(valor_total->Field->AsFloat,-3) != RoundTo(pagto_total->Field->AsFloat,-3)) {
		MessageBox(Handle, "Valor total dos itens difere do valor de pagamento total do pedido de venda!",Caption.c_str(),APP_ATENTION);
		return false;
	}*/
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
		if (VarIsNull(QyCadProduto->FieldByName("cod_cfop")->Value)) {
			MessageBox(Handle, "Informe o código do CFOP do item!",Caption.c_str(),APP_ATENTION);
			pgDetalhes->ActivePageIndex = 0;
			grdItens->SetFocus();
			grdItens->SelectedField = QyCadProduto->FieldByName("cod_cfop");
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
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TObf1001::ValidaCampos()
{
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::SearchCliente(Variant Value) {
	cod_cliente->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CodClienteValidate(TField *Sender)
{
	String SQL;
	if(!Sender->AsString.Length())
		return;
	SQL = "SELECT cod_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(Sender->AsString);
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
      throw Exception("Cliente não cadastrado!");
	} else {
		QyCliente->Params->ParamByName("cod_cliente")->Value = Sender->AsString;
		QyCliente->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_hora_emissao);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btCalendar02Click(TObject *Sender)
{
	ExecCalendar(data_saida);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::NavegexecBtEditClickExecute(
		TObject *Sender)
{
	String Situacao;
	bool bAltera = false;
	QySitNotaFiscal->Refresh();
	Situacao = QySitNotaFiscal->FieldByName("ies_situacao")->AsString;
	if (Situacao == "F") {
		if (MessageBox(Handle, "Nota fiscal faturada. Deseja realmente alterar a mesma?\nEsta ação irá alterar a situação da mesma para aberta.",Caption.c_str(),APP_QUESTION)==ID_YES) {
			bAltera = true;
		} else {
			return;
		}
	} else if(Situacao == "C") {
		MessageBox(Handle,"Nota fiscal cancelada. Modificação não permitida!",Caption.c_str(),APP_INFORM);
		return;
	}

	if (bAltera && Situacao == "F") { //Deve estornar o fechamento da nota fiscal de venda
		TZReadOnlyQuery *QyReabreNota = new TZReadOnlyQuery(Application);
		QyReabreNota->Connection = AppConnection;
	try {
		if (!SfgDataCenter->StartTrans()) {
		   MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
         return;
      }
		//Reabre a nota fiscal de venda
		//Excluindo o registro da NFe
		QyReabreNota->SQL->Text = "CALL reabre_nota_fiscal_venda(" \
                                 + QuotedStr(AppUser->CodEmpresa) + "," \
                                 + QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsString + ");";
		QyReabreNota->ExecSQL(); //Neste caso não retorna nada
		SfgDataCenter->CommitTrans();
		delete QyReabreNota;
	} catch(Exception &e){
		SfgDataCenter->RollbackTrans();
		String sMsgErro = "Ocorreu o seguinte erro ao reabrir a nota fiscal de venda:\n";
		sMsgErro = sMsgErro + e.Message;
		MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
		delete QyReabreNota;
		return;
	}
	}
	QySitNotaFiscal->Refresh();
	SfgToolbar->btEditClick(Sender);
	if (bAltera)
		QyNotaFiscal->FieldByName("ies_situacao")->AsString = "A";
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::NavegexecBtSaveClickExecute(TObject *Sender)
{
   if (!VarIsNull(QyNotaFiscal->FieldByName("data_saida")->Value)) {
      TDateTime dtTime = StrToTime("00:00:00");
      TDateTime dtDate = DateOf(QyNotaFiscal->FieldByName("data_saida")->AsDateTime);
      if (!VarIsNull(QyNotaFiscal->FieldByName("hora_saida")->Value)) {
         dtTime = StrToTime(QyNotaFiscal->FieldByName("hora_saida")->AsString);
      }
      dtDate = dtDate + dtTime;
      QyNotaFiscal->FieldByName("data_hora_saida")->AsDateTime = dtDate;
   }
   //QyNotaFiscal->FieldByName("num_parcelas")->Value = UpDwNumParcelas->Position;
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
void __fastcall TObf1001::NavegexecBtCancelClickExecute(TObject *Sender)
{
	bool edit = (QyNotaFiscal->State == dsEdit);
	SfgToolbar->btCancelClick(Sender);
	if(edit)
		QyNotaFiscalAfterScroll(QyNotaFiscal);
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::NavegexecBtNewClickExecute(TObject *Sender)
{
	MessageBox(Handle,"Função ainda não liberada.", Caption.c_str(), APP_INFORM);
   return;

	SfgToolbar->btNewClick(Sender);
	/*QyNotaFiscal->FieldByName("data_cadastro")->Value = Now();
	QyNotaFiscal->FieldByName("ies_situacao")->Value = "A";
	//Adiciona uma linha no GRID de itens
	addLineExecute(Sender);
	//Adiciona uma linha no GRID de parcelas
	QyCadPagto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyCadPagto->Insert();
	QyCadPagto->BeforeInsert = &QyDetalheBeforeInsert;
	QyCadPagto->FieldByName("cod_nota_fiscal")->AsInteger = 0;
	QyCadPagto->FieldByName("seq_parcela")->AsInteger = QyCadPagto->RecordCount+1;
	QyCadPagto->FieldByName("valor_parcela")->AsFloat =  0;
	QyCadPagto->FieldByName("data_vencimento")->Value =  VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("observacao")->Value = VarAsType(Variant::Empty(), varNull);
	QyCadPagto->FieldByName("ies_recebido")->AsString = "N";
	QyCadPagto->Post();
	HabilitarItens(true);
	num_nota_fiscal->SetFocus();*/
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::NavegexecBtDeleteClickExecute(TObject *Sender)
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
void __fastcall TObf1001::HabilitarItens(bool Habilita)
{
	btPesqCliente->Enabled = Habilita;
	btPesqNatOp->Enabled = Habilita;
	btPesqTransportador->Enabled = Habilita; 
	//Habilitando os itens do GRID de itens
	DsCadProduto->AutoEdit = Habilita;
	//addLine->Enabled = Habilita;
	//delLine->Enabled = Habilita;
	//addItens->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::addLineExecute(TObject *Sender)
{
	/*
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
	if(QyNotaFiscal->State == dsEdit)
		QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger = QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsInteger;
	else
		QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger = 0;
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
   */
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::delLineExecute(TObject *Sender)
{
	/*if(QyCadProduto->RecordCount > 0) {
		QyNotaFiscal->FieldByName("valor_total")->AsFloat -= QyCadProduto->FieldByName("valor_total")->AsFloat;
		QyCadProduto->Delete();
	}*/
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::addItensExecute(TObject *Sender)
{
   /*TObf1004 *Obf1004 = new TObf1004(Application);
	Obf1004->OnConfirmList = &addItensConfirm;
	Obf1004->ShowModal();
   delete Obf1004;*/
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::addItensConfirm(TList *pListAdd)
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
		if(QyNotaFiscal->State == dsEdit)
			QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger = QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsInteger;
		else
			QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger = 0;
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
	QyNotaFiscal->FieldByName("valor_total")->AsFloat += fValorTotal;
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
void __fastcall TObf1001::QyNotaFiscalAfterScroll(TDataSet *DataSet)
{
	QyCliente->Params->ParamByName("cod_cliente")->Value = DataSet->FieldByName("cod_cliente")->Value;
	QyCliente->Refresh();
   TipoPessoaChange(QyCliente->FieldByName("tipo_pessoa"));
try {
   CodTransportadorValidate(cod_transportador->Field);
} catch ( ... ) {}
try {
   NaturezaOperacaoValidate(natureza_operacao->Field);
} catch ( ... ) {}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyNotaFiscalCalcFields(TDataSet *DataSet)
{
   if (!VarIsNull(QyNotaFiscal->FieldByName("data_hora_saida")->Value)) {
      TDateTime dtTime = TimeOf(QyNotaFiscal->FieldByName("data_hora_saida")->AsDateTime);
      TDateTime dtDate = DateOf(QyNotaFiscal->FieldByName("data_hora_saida")->AsDateTime);
      QyNotaFiscal->FieldByName("data_saida")->AsDateTime = dtDate;
      QyNotaFiscal->FieldByName("hora_saida")->AsString = TimeToStr(dtTime);
   } else {
      QyNotaFiscal->FieldByName("data_saida")->Value = Null();
      QyNotaFiscal->FieldByName("hora_saida")->Value = Null();
   }
	//QyNotaFiscal->FieldByName("pagto_total")->AsFloat = QyNotaFiscal->FieldByName("valor_total")->AsFloat;
}
//---------------------------------------------------------------------------
//No evento de BeforPost ele desassocia os datasets das querys filhas para não recarregar
void __fastcall TObf1001::QyNotaFiscalBeforePost(TDataSet *DataSet)
{
	QyCadProduto->DataSource = NULL;
	QyNotaFiscal->AfterScroll = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyNotaFiscalAfterPost(TDataSet *DataSet)
{
try {
try {
	int iSeq = 1;  //Utilizado para refazer a ordenação dos produtos 
	//Verificação para atualizar o campo código do mestre nos itens
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	QyCadProduto->First();
	while (!QyCadProduto->Eof) {
		if (QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger == 0) {
			QyCadProduto->Edit();
			QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger = QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsInteger;
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
	QyCadProduto->DataSource = DsNotaFiscal;
	QyNotaFiscal->AfterScroll = &QyNotaFiscalAfterScroll;
}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyNotaFiscalBeforeDelete(TDataSet *DataSet)
{
   String sSQL = "\
UPDATE tbl_pedido_venda SET ies_situacao = 'F'\
 WHERE cod_pedido_venda IN (\
 SELECT DISTINCT cod_pedido\
   FROM tbl_nota_fiscal_item\
  WHERE cod_empresa = " + QuotedStr(AppUser->CodEmpresa) + "\
    AND cod_nota_fiscal = " + QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsString + ")";
   TZQuery *QyAtuPedido = new TZQuery(this);
   QyAtuPedido->Connection = AppConnection;
try {
   //Desmarcando pedido de faturado, voltando para fechado
   QyAtuPedido->SQL->Text = sSQL;
   QyAtuPedido->ExecSQL();
	//Excluindo os itens do pedido - os impostos também são excluídos pelo banco
	QyCadProduto->DisableControls();  //Para desativar a atualização da tela
	while (QyCadProduto->RecordCount > 0) {
		QyCadProduto->Last();
		QyCadProduto->Delete();
	}
	QyCadProduto->ApplyUpdates();
	QyCadProduto->EnableControls(); //Para ativar a atualização da tela
}
catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao excluir as informações do registro:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(Handle,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
	PostStatus = false;
}
   delete QyAtuPedido;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btRelatorioClick(TObject *Sender)
{
   MessageBox(Handle, "Visualização da DANFE ainda não disponível.",Caption.c_str(),APP_INFORM);
	/*TObf3001 *Obf3001 = new TObf3001(Owner);
	Obf3001->CnsNotaFiscal->Active = false;
	Obf3001->CnsNotaFiscal->Params->ParamByName("cod_nota_fiscal")->Value = QyNotaFiscal->FieldByName("cod_nota_fiscal")->Value;
	Obf3001->CnsNotaFiscal->Active = true;
   if(Obf3001->RpRelatBase->PrepareReport(true))
      Obf3001->RpRelatBase->ShowPreparedReport();*/
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btPesqClienteClick(TObject *Sender)
{
	SfgBrowse::EscolheCliente(this,&SearchCliente);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btEnderecoClick(TObject *Sender)
{
	grpEndereco->Top = 235;
	grpEndereco->Left = 8;
	grpEndereco->Show();
	logradouro->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grpEnderecoExit(TObject *Sender)
{
	grpEndereco->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btFechamentoClick(TObject *Sender)
{
	String Situacao;
	QySitNotaFiscal->Refresh();
	Situacao = QySitNotaFiscal->FieldByName("ies_situacao")->AsString;
	if(Situacao == "F") {
		MessageBox(Handle, "Nota fiscal já fechada, será apenas regerado um novo arquivo de exportação.",Caption.c_str(),APP_INFORM);
	} else if(Situacao == "C") {
		MessageBox(Handle, "Nota fiscal cancelada.",Caption.c_str(),APP_INFORM);
		return;
	} else if(MessageBox(Handle, "Confirma o fechamento da nota fiscal e a geração do arquivo de exportação da mesma?",Caption.c_str(),APP_QUESTION)==ID_NO) {
		return;
	}
   //Efetuando a geração do xml da nota fiscal
   TSfgXmlNFe *SfgXmlNFe = new TSfgXmlNFe();
   SfgXmlNFe->CodEmpresa = AppUser->CodEmpresa;
   SfgXmlNFe->CodNotaFiscal = QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsInteger;
   //if (SfgXmlNFe->CreateXmlFile()) {
      //if (SfgXmlNFe->LoadNfe()) {
      //   SfgXmlNFe->SaveXmlFile();
      //}
   if (SfgXmlNFe->LoadNfeToTxt()) {
      bool bSucesso = true;
   	if (Situacao == "A") { //Deve estornar o fechamento da nota fiscal de venda
   		TZReadOnlyQuery *QyFechaNota = new TZReadOnlyQuery(Application);
   		QyFechaNota->Connection = AppConnection;
   	try {
   		if (!SfgDataCenter->StartTrans()) {
   		   MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
            delete SfgXmlNFe;
            return;
         }
   		//Reabre a nota fiscal de venda
   		//Excluindo o registro da NFe
   		QyFechaNota->SQL->Text = "CALL fecha_nota_fiscal_venda(" \
                                    + QuotedStr(AppUser->CodEmpresa) + "," \
                                    + QyNotaFiscal->FieldByName("cod_nota_fiscal")->AsString + "," \
                                    + QuotedStr(SfgXmlNFe->ChaveNFe) + ");";
   		QyFechaNota->ExecSQL(); //Neste caso não retorna nada
   		SfgDataCenter->CommitTrans();
   		QySitNotaFiscal->Refresh();
   		delete QyFechaNota;
   	} catch(Exception &e){
   		bSucesso = false;
         SfgDataCenter->RollbackTrans();
   		String sMsgErro = "Ocorreu o seguinte erro ao fechar a nota fiscal de venda:\n";
   		sMsgErro = sMsgErro + e.Message;
   		MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
   		delete QyFechaNota;
   	}
   	}
      if (bSucesso)
         MessageBox(Handle,"Geração do arquivo de exportação da NFe efetuada com sucesso!", Caption.c_str(), APP_INFORM);
   }
   delete SfgXmlNFe;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::execImportarExecute(TObject *Sender)
{
	TObf1003 *Obf1003 = new TObf1003(Application);
	Obf1003->AfterImport = &AfterImport;
	Obf1003->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::AfterImport()
{
   if (QyNotaFiscal->Active) {
      QyNotaFiscal->Refresh();
      SfgToolbar->btLast->Click();
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyDetalheBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::DbGridKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::EditItemSetFocus(TObject *Sender)
{
	if(QyNotaFiscal->State == dsInsert || QyNotaFiscal->State == dsEdit) {
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
void __fastcall TObf1001::grdItensDrawColumnCell(TObject *Sender,
		const TRect &Rect, int DataCol, TColumn *Column, TGridDrawState State)
{
	if (Column->Field->FieldName == "cod_produto") {
		DrawSearchGrid(grdItens,-1,-1,Rect,State,false);
	} else if (Column->Field->FieldName == "impostos") {
      //Força o RECT a desenhar no meio
      TRect newRect;
      SetRect(&newRect, Rect.left,Rect.top,Rect.right,Rect.bottom);
      newRect.right = newRect.left + (((newRect.right - newRect.left) / 2) + 10);
		DrawSearchGrid(grdItens,-1,-1,newRect,State,false);
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CodProdutoValidate(TField *Sender)
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
		QyNotaFiscal->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
	} else {
		QyCadProduto->FieldByName("den_produto")->AsString = "";
		throw Exception("Produto não cadastrado ou está inativo!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QtdProdutoSetText(TField *Sender, const AnsiString Text)
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
		QyNotaFiscal->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::PrecoVendaSetText(TField *Sender, const AnsiString Text)
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
		QyNotaFiscal->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::ValDescontoSetText(TField *Sender, const AnsiString Text)
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
		QyNotaFiscal->FieldByName("valor_total")->AsFloat += (fNewTotal - fOldTotal);
		Sender->AsString = Text;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grdItensEditButtonClick(TObject *Sender)
{
	MessageBox(Handle,"Função ainda não liberada.", Caption.c_str(), APP_INFORM);
   return;
   
	if (!(QyNotaFiscal->State == dsInsert || QyNotaFiscal->State == dsEdit))
		return;
	if (grdItens->SelectedField->FieldName == "cod_produto") {
		SfgBrowse::EscolheProduto(this,&SearchProduto);
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::SearchProduto(Variant Value) {
	if (QyCadProduto->State != dsEdit)
		QyCadProduto->Edit();
	QyCadProduto->FieldByName("cod_produto")->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btPesqTransportadorClick(TObject *Sender)
{
	SfgBrowse::EscolheCliente(this,&SearchTransportador);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::SearchTransportador(Variant Value)
{
	cod_transportador->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::CodTransportadorValidate(TField *Sender)
{
	String sSQL, sRet;
	if(!Sender->AsString.Length())
		return;
	sSQL = "SELECT den_cliente FROM tbl_cliente" \
			 " WHERE cod_cliente = " + QuotedStr(Sender->AsString);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,sSQL);
	if(sRet.Length() <= 0) {
		throw Exception("Transportador não cadastrado como cliente!");
	} else {
		den_transportador->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::btPesqNatOpClick(TObject *Sender)
{
	SfgBrowse::EscolheNaturezaOperacao(this,&SearchNaturezaOperacao);
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::SearchNaturezaOperacao(Variant Value)
{
	natureza_operacao->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::NaturezaOperacaoValidate(TField *Sender)
{
	String sSQL, sRet;
	if(!Sender->AsString.Length())
		return;
	sSQL = "SELECT den_natureza_operacao FROM tbl_natureza_operacao" \
			 " WHERE cod_natureza_operacao = " + Sender->AsString;
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,sSQL);
	if(sRet.Length() <= 0) {
		throw Exception("Natureza de operação não cadastrada!");
	} else {
		den_natureza_operacao->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::FormShow(TObject *Sender)
{
   if (AppUser->CodEmpresa.Length() == 0) {
		MessageBox(Handle,"Não foi selecionada a empresa para geração de nota fiscal!",Caption.c_str(),APP_INFORM);
      lbEmpresaClick(Sender);
   }
   if (AppUser->CodEmpresa.Length() > 0)
      lbEmpresa->Caption = "Empresa: " + AppUser->CodEmpresa;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::lbEmpresaClick(TObject *Sender)
{
   TObf1004 *Obf1004 = new TObf1004(Application);
   Obf1004->ShowModal();
   delete Obf1004;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grdItensColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdItens->SelectedField->FieldName == "impostos") {
		Options = grdItens->Options;
		Options >> dgEditing;
		grdItens->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grdItensColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdItens->SelectedField->FieldName == "impostos") {
		Options = grdItens->Options;
		Options << dgEditing;
		grdItens->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::grdItensCellClick(TColumn *Column)
{
	if(Column->Field->FieldName == "impostos") {
      TObf1005 *Obf1005 = new TObf1005(Application, AppUser->CodEmpresa,
         QyCadProduto->FieldByName("cod_nota_fiscal")->AsInteger,
         NOTA_FISCAL_SAIDA,
         QyCadProduto->FieldByName("seq_produto")->AsInteger,
         (QyNotaFiscal->State == dsEdit));
      Obf1005->ShowModal();
      delete Obf1005;
      if (QyNotaFiscal->State == dsEdit)
         QyTotCredICMS->Refresh();
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCliente->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyNotaFiscalAfterOpen(TDataSet *DataSet)
{
	QyCliente->Active = true;
	QyCadProduto->Active = true;
	QySitNotaFiscal->Active = true;
   QyTotCredICMS->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::QyNotaFiscalBeforeClose(TDataSet *DataSet)
{
	QyCliente->Active = false;
	QyCadProduto->Active = false;
	QySitNotaFiscal->Active = false;
   QyTotCredICMS->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TObf1001::execNumeracaoNFExecute(TObject *Sender)
{
   TObf1007 *Obf1007 = new TObf1007(Application);
   Obf1007->ShowModal();
   delete Obf1007;
}
//---------------------------------------------------------------------------

