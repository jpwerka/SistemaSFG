/*
Módulo: Compras
Função: Cadastro Pedidos de Compra
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup1001H
#define uSup1001H
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
#include <Grids.hpp>
#include <DBGrids.hpp>
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
struct TBDSup1001Object : public TBDDataObject {
  bool ies_parcelado;
  bool ies_financeiro;
};
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TSup1001 : public TfrmBase02
{
__published:	// IDE-managed Components
   TDataSource *DsCadCompra;
	TPageControl *pgDetalhes;
	TTabSheet *tbItens;
	TTabSheet *tbObs;
	TDBMemo *observacao;
	TTabSheet *tbPgto;
	TMenuItem *PesquisaProdutoCliente2;
	TZQuery *QyCadProduto;
	TFloatField *QyCadPagtovalor_parcela;
	TDateTimeField *QyCadPagtodata_vencimento;
	TStringField *QyCadPagtoQyCadPagtoobservacao;
	TZUpdateSQL *AddItemVenda;
	TZUpdateSQL *AddPagto;
	TZQuery *QyCadCompra;
	TIntegerField *CodPedidoCompraPagto;
	TIntegerField *QyCadPagtoseq_parcela;
	TIntegerField *CodPedidoCompraItem;
	TIntegerField *QyCadProdutoseq_produto;
	TStringField *QyCadProdutocod_produto;
	TStringField *QyCadProdutoden_produto;
	TFloatField *QyCadProdutoqtd_produto;
	TMenuItem *PercentualReajuste1;
	TResBitBtn *btEnviarPedido;
	TResBitBtn *btRelatorio;
	TFloatField *QyCadProdutopreco_compra;
	TActionList *ActionList1;
	TAction *execRecebimento;
	TAction *execRelatorio;
	TAction *execEnviaPedido;
	TAction *execFechamento;
	TFloatField *QyCadProdutoval_desconto;
	TStringField *QyCadPagtoies_pago;
	TGroupBox *gbCadastro;
	TLabel *Label1;
	TDBEdit *cod_pedido_compra;
	TLabel *Label2;
	TDBEdit *data_cadastro;
	TCustomImgButton *btCalendar01;
	TLabel *Label12;
	TDBEdit *data_recebimento;
	TCustomImgButton *btCalendar02;
	TLabel *Label6;
	TDBDataComboBox *ies_situacao;
	TLabel *Label4;
	TDBEdit *cod_plano_conta;
	TResBitBtn *btPesqPlanoConta;
	TLabel *Label5;
	TDBEdit *cod_centro_custo;
	TResBitBtn *btPesqCentroCusto;
	TGroupBox *gbFornecedor;
	TLabel *Label3;
	TDBEdit *cod_fornecedor;
	TResBitBtn *btPesqFornecedor;
	TEdit *den_fornecedor;
	TResBitBtn *btRecebePedido;
	TMenuItem *VisualizarImpresso1;
	TResBitBtn *btFechamento;
	TZQuery *QySitPedidoCompra;
	TDataSource *DsSitPedidoCompra;
	TMenuItem *FechamentoPedido1;
	TFloatField *QyCadProdutovalor_total;
	TFloatField *QyCadProdutopreco_custo;
	TPanel *pnParcela;
	TLabel *Label9;
	TLabel *Label10;
	TDBDataComboBox *cod_forma_pagto;
	TEdit *num_parcelas;
	TUpDown *UpDwNumParcelas;
	TDBGrid *grdPagtos;
	TPanel *pnTotal;
	TLabel *Label8;
	TDBEdit *pagto_total;
	TLabel *MsgDifTotalPagto;
	TDataSource *DsCompraPagto;
	TZQuery *QyCadPagto;
	TPanel *Panel6;
	TLabel *Label7;
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
	TDataSource *DsCadProduto;
	TZQuery *QyCnsProduto;
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
	void __fastcall NavegexecBtEditClickExecute(TObject *Sender);
	void __fastcall NavegexecBtSaveClickExecute(TObject *Sender);
	void __fastcall NavegexecBtCancelClickExecute(TObject *Sender);
	void __fastcall NavegexecBtNewClickExecute(TObject *Sender);
	void __fastcall NavegexecBtDeleteClickExecute(TObject *Sender);
	void __fastcall CodFornecedorValidate(TField *Sender);
	void __fastcall QyCadCompraAfterScroll(TDataSet *DataSet);
	void __fastcall QyCadCompraAfterPost(TDataSet *DataSet);
	void __fastcall QyCadCompraBeforePost(TDataSet *DataSet);
	void __fastcall QyCadCompraBeforeDelete(TDataSet *DataSet);
	void __fastcall btEnviarPedidoClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall delLineExecute(TObject *Sender);
	void __fastcall addItensExecute(TObject *Sender);
	void __fastcall btPesqFornecedorClick(TObject *Sender);
	void __fastcall CodFornecedorSetText(TField *Sender,
          const AnsiString Text);
	void __fastcall btPesqPlanoContaClick(TObject *Sender);
	void __fastcall btPesqCentroCustoClick(TObject *Sender);
	void __fastcall execRecebimentoExecute(TObject *Sender);
	void __fastcall execFechamentoExecute(TObject *Sender);
	void __fastcall cod_forma_pagtoChange(TObject *Sender);
	void __fastcall UpDwNumParcelasClick(TObject *Sender, TUDBtnType Button);
	void __fastcall QyDetalheBeforeInsert(TDataSet *DataSet);
	void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
	void __fastcall grdPagtosColEnter(TObject *Sender);
	void __fastcall grdPagtosColExit(TObject *Sender);
	void __fastcall grdPagtosEditButtonClick(TObject *Sender);
	void __fastcall DbGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall grdPagtosDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall ValorParcelaSetText(TField *Sender,
          const AnsiString Text);
	void __fastcall QyCadProdutoCalcFields(TDataSet *DataSet);
	void __fastcall addLineExecute(TObject *Sender);
	void __fastcall grdItensDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall CodProdutoValidate(TField *Sender);
	void __fastcall QtdProdutoSetText(TField *Sender, const AnsiString Text);
	void __fastcall PrecoCompraSetText(TField *Sender, const AnsiString Text);
	void __fastcall ValDescontoSetText(TField *Sender, const AnsiString Text);
	void __fastcall EditItemSetFocus(TObject *Sender);
	void __fastcall EditPagtoSetFocus(TObject *Sender);
	void __fastcall QyCadCompraCalcFields(TDataSet *DataSet);
	void __fastcall grdItensEditButtonClick(TObject *Sender);
	void __fastcall CodCentroCustoValidate(TField *Sender);
	void __fastcall CodPlanoContaValidate(TField *Sender);
   void __fastcall SubClassWndProc(Messages::TMessage &Message);
   void __fastcall QyCadCompraPostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
   void __fastcall QyCadCompraAfterOpen(TDataSet *DataSet);
   void __fastcall QyCadCompraBeforeClose(TDataSet *DataSet);
private:	// User declarations
	bool PostStatus;
   void __fastcall AfterCreateFields(TDataSet *DataSet);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
	void __fastcall ValidInsert(bool &bValid);
	void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
	void __fastcall CarregarSitPedidoCompra();
	void __fastcall CarregarFormaPagto();
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	void __fastcall SearchFornecedor(Variant Value);
	void __fastcall SearchPlanoConta(Variant Value);
	void __fastcall SearchCentroCusto(Variant Value);
	void __fastcall HabilitarItens(bool Habilita);
	void __fastcall addItensConfirm(TList *pListAdd);
	void __fastcall SearchProduto(Variant Value);
	void __fastcall RecalculaParcelas();
	void __fastcall CalculaDifTotalPagto();
	void __fastcall Sup1002SendMailSucess();
	void __fastcall Sup1003RecebeSucess();
	void __fastcall AlteraSitCompra(String Situacao);
public:		// User declarations
	__fastcall TSup1001(TComponent* Owner);
	void __fastcall FilterCodCompra(int CodCompra);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
