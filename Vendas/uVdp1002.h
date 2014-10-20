/*
Módulo: Vendas
Função: Cadastro Pedidos de Venda
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1002H
#define uVdp1002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"
#include "CustomButtons.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
struct TBDVdp1002Object : public TBDDataObject {
  bool ies_parcelado;
};
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TVdp1002 : public TfrmBase02
{
__published:	// IDE-managed Components
	TZQuery *QyOrcamento;
	TDataSource *DsOrcamento;
	TZQuery *QyCadProduto;
	TZQuery *QyCadPagto;
	TLabel *Label3;
   TLabel *Label20;
   TLabel *Rtulo98;
   TLabel *Label1;
	TDBEdit *cod_orcamento;
	TGroupBox *gbCadastro;
   TLabel *Label2;
	TGroupBox *gbCliente;
	TDBEdit *den_cliente;
   TDBEdit *cpf_cnpj;
   TDBEdit *rg_ie;
	TDBEdit *cod_cliente;
	TResBitBtn *btPesqCliente;
	TDBEdit *data_cadastro;
	TDBEdit *data_validade;
	TLabel *Label12;
   TZQuery *QyCliente;
	TDataSource *DsClientes;
	TLabel *Label4;
	TDBDataComboBox *tipo_pessoa;
	TPageControl *pgDetalhes;
	TTabSheet *tbObs;
	TDBMemo *observacao;
	TTabSheet *tbPgto;
	TDBDataComboBox *ies_situacao;
	TLabel *Label6;
	TCustomImgButton *btCalendar01;
	TCustomImgButton *btCalendar02;
	TMenuItem *PesquisaProdutoCliente2;
	TResBitBtn *btEndereco;
	TFloatField *QyCadPagtovalor_parcela;
	TDateTimeField *QyCadPagtodata_vencimento;
	TStringField *QyCadPagtoobservacao;
	TZUpdateSQL *AddItemVenda;
	TZUpdateSQL *AddPagto;
	TIntegerField *QyCadPagtocod_orcamento;
	TIntegerField *QyCadPagtoseq_parcela;
	TIntegerField *QyCadProdutocod_orcamento;
	TIntegerField *QyCadProdutoseq_produto;
	TStringField *QyCadProdutocod_produto;
	TStringField *QyCadProdutoden_produto;
	TFloatField *QyCadProdutoqtd_produto;
	TFloatField *QyCadProdutopreco_venda;
	TFloatField *QyCadProdutopreco_custo;
	TResBitBtn *btFechamento;
	TResBitBtn *btRelatorio;
	TTabSheet *tbItens;
	TActionList *ActionList1;
	TAction *execRelatorio;
	TAction *execFechamento;
	TMenuItem *Fechar1;
	TFloatField *QyCadProdutoval_desconto;
	TLabel *Label5;
	TDBEdit *cod_plano_conta;
	TResBitBtn *btPesqPlanoConta;
	TLabel *Label7;
	TDBEdit *cod_centro_custo;
	TResBitBtn *btPesqCentroCusto;
	TGroupBox *grpEndereco;
	TLabel *Label9;
	TLabel *Label8;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TDBEdit *logradouro;
	TDBEdit *numero;
	TDBComboBox *cod_uf;
	TDBEdit *cep;
	TDBEdit *bairro;
	TDBEdit *complemento;
	TDBDataComboBox *cod_cidade;
	TZQuery *QySitPedidoVenda;
	TDataSource *DsSitPedidoVenda;
	TDataSource *DsCadProduto;
	TDataSource *DsCompraPagto;
	TPanel *Panel6;
	TLabel *Label19;
	TResBitBtn *btAddLinha;
	TResBitBtn *btDelLinha;
	TResBitBtn *btAddItens;
	TDBEdit *valor_total;
	TDBGrid *grdItens;
	TPopupMenu *PopupMenu1;
	TMenuItem *AdicionarLinha1;
	TMenuItem *RemoverLinha1;
	TMenuItem *AdicionarItens1;
	TAction *addLine;
	TAction *delLine;
	TAction *addItens;
	TPanel *pnTotal;
	TLabel *Label16;
	TLabel *MsgDifTotalPagto;
	TDBEdit *pagto_total;
	TDBGrid *grdPagtos;
	TPanel *pnParcela;
	TLabel *Label17;
	TLabel *Label18;
	TDBDataComboBox *cod_forma_pagto;
	TEdit *num_parcelas;
	TUpDown *UpDwNumParcelas;
	TZQuery *QyCnsProduto;
	TFloatField *QyCadProdutovalor_total;
	TZQuery *QyCidade;
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
	void __fastcall NavegexecBtEditClickExecute(TObject *Sender);
	void __fastcall NavegexecBtSaveClickExecute(TObject *Sender);
	void __fastcall NavegexecBtCancelClickExecute(TObject *Sender);
	void __fastcall NavegexecBtNewClickExecute(TObject *Sender);
	void __fastcall NavegexecBtDeleteClickExecute(TObject *Sender);
	void __fastcall addLineExecute(TObject *Sender);
	void __fastcall delLineExecute(TObject *Sender);
	void __fastcall addItensExecute(TObject *Sender);
	void __fastcall CodClienteValidate(TField *Sender);
	void __fastcall QyOrcamentoAfterScroll(TDataSet *DataSet);
	void __fastcall QyOrcamentoAfterPost(TDataSet *DataSet);
	void __fastcall QyOrcamentoBeforePost(TDataSet *DataSet);
	void __fastcall data_validadeExit(TObject *Sender);
	void __fastcall QyOrcamentoBeforeDelete(TDataSet *DataSet);
	void __fastcall btFechamentoClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall cod_ufChange(TObject *Sender);
	void __fastcall btEnderecoClick(TObject *Sender);
	void __fastcall btPesqPlanoContaClick(TObject *Sender);
	void __fastcall btPesqCentroCustoClick(TObject *Sender);
	void __fastcall grpEnderecoExit(TObject *Sender);
	void __fastcall cod_forma_pagtoChange(TObject *Sender);
	void __fastcall UpDwNumParcelasClick(TObject *Sender, TUDBtnType Button);
	void __fastcall QyDetalheBeforeInsert(TDataSet *DataSet);
	void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
	void __fastcall grdPagtosEditButtonClick(TObject *Sender);
	void __fastcall DbGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall grdPagtosDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall ValorParcelaSetText(TField *Sender,
          const AnsiString Text);
	void __fastcall QyCadProdutoCalcFields(TDataSet *DataSet);
	void __fastcall grdItensDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall CodProdutoValidate(TField *Sender);
	void __fastcall QtdProdutoSetText(TField *Sender, const AnsiString Text);
	void __fastcall PrecoVendaSetText(TField *Sender, const AnsiString Text);
	void __fastcall ValDescontoSetText(TField *Sender, const AnsiString Text);
	void __fastcall EditItemSetFocus(TObject *Sender);
	void __fastcall EditPagtoSetFocus(TObject *Sender);
	void __fastcall QyOrcamentoCalcFields(TDataSet *DataSet);
	void __fastcall grdItensEditButtonClick(TObject *Sender);
	void __fastcall CodCentroCustoValidate(TField *Sender);
	void __fastcall CodPlanoContaValidate(TField *Sender);
   void __fastcall TipoPessoaChange(TField *Sender);
   void __fastcall QyOrcamentoAfterOpen(TDataSet *DataSet);
   void __fastcall QyOrcamentoBeforeClose(TDataSet *DataSet);
private:	// User declarations
	bool PostStatus;
	void __fastcall AfterCreateFields(TDataSet *DataSet);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
   void __fastcall ValidInsert(bool &bValid);
	void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
	void __fastcall CarregarSitOrcamento();
	void __fastcall CarregarTipoPessoa();
	void __fastcall CarregarEstado();
	void __fastcall CarregarFormaPagto();
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	bool __fastcall VerificaCamposCliente();
	void __fastcall SearchCliente(Variant Value);
	void __fastcall SearchPlanoConta(Variant Value);
	void __fastcall SearchCentroCusto(Variant Value);
	void __fastcall HabilitaCadCliente();
	void __fastcall DesabilitaCadCliente();
	void __fastcall HabilitarItens(bool Habilita);
	void __fastcall addItensConfirm(TList *pListAdd);
	void __fastcall AlteraSituacao(String Situacao);
	void __fastcall SearchProduto(Variant Value);
	void __fastcall RecalculaParcelas();
	void __fastcall CalculaDifTotalPagto();
public:		// User declarations
	SfgWorkEdition *pWorkEdtCliente; //Trabalha a lista de campos habilitando-os quando necessário
	__fastcall TVdp1002(TComponent* Owner);
	void __fastcall FilterCodOrcamento(int CodOrcamento);
	void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
