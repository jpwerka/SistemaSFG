/*
Módulo: Vendas
Função: Cadastro Notas Fiscais Saída
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uObf1001H
#define uObf1001H
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
struct TBDObf1001Object : public TBDDataObject {
  bool ies_parcelado;
};
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TObf1001 : public TfrmBase02
{
__published:	// IDE-managed Components
	TZQuery *QyNotaFiscal;
   TDataSource *DsNotaFiscal;
	TZQuery *QyCadProduto;
   TLabel *Label3;
   TLabel *Label20;
   TLabel *Rtulo98;
   TGroupBox *gbNotaFiscal;
   TLabel *Label2;
   TGroupBox *gbDestinatario;
	TDBEdit *den_cliente;
   TDBEdit *cpf_cnpj;
   TDBEdit *rg_ie;
	TDBEdit *cod_cliente;
	TResBitBtn *btPesqCliente;
   TDBEdit *data_hora_emissao;
   TZQuery *QyCliente;
	TDataSource *DsClientes;
	TPageControl *pgDetalhes;
   TTabSheet *tbTotais;
	TDBDataComboBox *ies_situacao;
	TLabel *Label6;
	TCustomImgButton *btCalendar01;
	TMenuItem *PesquisaProdutoCliente2;
	TResBitBtn *btEndereco;
   TZUpdateSQL *AddItemNota;
	TIntegerField *QyCadProdutocod_nota_fiscal;
	TIntegerField *QyCadProdutoseq_produto;
	TStringField *QyCadProdutocod_produto;
	TStringField *QyCadProdutoden_produto;
	TFloatField *QyCadProdutoqtd_produto;
   TFloatField *QyCadProdutovalor_unitario;
	TResBitBtn *btFechamento;
	TResBitBtn *btRelatorio;
	TTabSheet *tbItens;
	TActionList *ActionList1;
	TAction *execRelatorio;
	TAction *execFechamento;
	TAction *execImportar;
	TMenuItem *Fechar1;
	TLabel *Label5;
   TDBEdit *num_nota_fiscal;
	TLabel *Label7;
   TDBEdit *serie_nota_fiscal;
	TZQuery *QySitNotaFiscal;
	TDataSource *DsSitNotaFiscal;
	TResBitBtn *btImportar;
	TMenuItem *ImportarOramento1;
	TDataSource *DsCadProduto;
	TPanel *Panel6;
	TResBitBtn *btAddLinha;
	TResBitBtn *btDelLinha;
	TResBitBtn *btAddItens;
	TDBGrid *grdItens;
	TPopupMenu *PopupMenu1;
	TMenuItem *AdicionarLinha1;
	TMenuItem *RemoverLinha1;
	TMenuItem *AdicionarItens1;
	TAction *addLine;
	TAction *delLine;
	TAction *addItens;
	TZQuery *QyCnsProduto;
	TFloatField *QyCadProdutovalor_total;
	TZQuery *QyCidade;
   TDBEdit *telefone;
   TLabel *Label4;
   TLabel *Label12;
   TDBEdit *data_saida;
   TCustomImgButton *btCalendar02;
   TStringField *QyCadProdutocod_empresa;
   TStringField *QyCadProdutocod_ncm;
   TStringField *CodEXTIPI;
   TStringField *QyCadProdutocod_unid_medida;
   TFloatField *QyCadProdutovalor_desconto;
   TIntegerField *QyCadProdutocod_pedido;
   TSmallintField *QyCadProdutoseq_pedido;
   TSmallintField *QyCadProdutocod_cfop;
   TLabel *Label1;
   TDBEdit *natureza_operacao;
   TResBitBtn *btPesqNatOp;
   TEdit *den_natureza_operacao;
   TTabSheet *tbTransportador;
   TGroupBox *gbTransportador;
   TLabel *Label22;
   TEdit *den_transportador;
   TDBEdit *cod_transportador;
   TResBitBtn *btPesqTransportador;
   TDBDataComboBox *tipo_frete;
   TLabel *Label31;
   TLabel *Label32;
   TDBEdit *placa_veiculo;
   TLabel *Label33;
   TDBComboBox *cod_uf_placa_veiculo;
   TGroupBox *gbVolumes;
   TLabel *Label18;
   TDBEdit *qtd_volume;
   TLabel *Label21;
   TDBEdit *especie_volume;
   TLabel *Label34;
   TDBEdit *marca_volume;
   TLabel *Label35;
   TDBEdit *mumeracao_volume;
   TLabel *Label36;
   TDBEdit *peso_liquido;
   TLabel *Label37;
   TDBEdit *peso_bruto;
   TLabel *Label38;
   TDBEdit *volume_cubico;
   TLabel *Label39;
   TDBEdit *valor_mercadoria;
   TLabel *Label40;
   TDBEdit *valor_nota_fiscal;
   TLabel *Label41;
   TDBEdit *valor_desconto;
   TLabel *Label42;
   TDBEdit *valor_frete;
   TLabel *Label43;
   TDBEdit *valor_seguro;
   TLabel *Label44;
   TLabel *Label45;
   TLabel *Label46;
   TLabel *Label47;
   TDBEdit *base_calc_icms_st;
   TDBEdit *valor_icms;
   TDBEdit *base_calc_icms;
   TDBEdit *base_calc_ipi;
   TLabel *Label48;
   TLabel *Label49;
   TLabel *Label51;
   TDBEdit *valor_icms_st;
   TDBEdit *valor_ipi;
   TDBEdit *outras_despesas;
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
   TDBComboBox *cod_uf_cliente;
   TDBEdit *cep;
   TDBEdit *bairro;
   TDBEdit *complemento;
   TDBDataComboBox *cod_cidade_cliente;
   TLabel *lbEmpresa;
   TStringField *Impostos;
   TFloatField *QyCadProdutovalor_frete;
   TFloatField *QyCadProdutovalor_seguro;
   TStringField *QyCadProdutoclasse_enq_ipi;
   TStringField *QyCadProdutocod_enq_ipi;
   TTabSheet *tbObs;
   TGroupBox *gbInfoFisco;
   TDBMemo *info_adicional_fisco;
   TGroupBox *gbInfoCompl;
   TDBMemo *info_complementar;
   TDBDataComboBox *cod_forma_pagto;
   TLabel *Label16;
   TLabel *lbTotCredICMS;
   TZReadOnlyQuery *QyTotCredICMS;
   TDBText *val_cred_icms;
   TDataSource *DsTotCredICMS;
   TFloatField *QyTotCredICMSval_cred_icms;
   TLabel *Label19;
   TDBEdit *hora_saida;
   TResBitBtn *btNumNF;
   TAction *execNumeracaoNF;
   TMenuItem *NumeraoNotaFiscal1;
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
	void __fastcall QyNotaFiscalAfterScroll(TDataSet *DataSet);
	void __fastcall QyNotaFiscalAfterPost(TDataSet *DataSet);
	void __fastcall QyNotaFiscalBeforePost(TDataSet *DataSet);
	void __fastcall btFechamentoClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall btEnderecoClick(TObject *Sender);
	void __fastcall grpEnderecoExit(TObject *Sender);
	void __fastcall QyDetalheBeforeInsert(TDataSet *DataSet);
	void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
	void __fastcall DbGridKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall execImportarExecute(TObject *Sender);
	void __fastcall grdItensDrawColumnCell(TObject *Sender, const TRect &Rect,
          int DataCol, TColumn *Column, TGridDrawState State);
	void __fastcall CodProdutoValidate(TField *Sender);
	void __fastcall QtdProdutoSetText(TField *Sender, const AnsiString Text);
	void __fastcall PrecoVendaSetText(TField *Sender, const AnsiString Text);
	void __fastcall ValDescontoSetText(TField *Sender, const AnsiString Text);
	void __fastcall EditItemSetFocus(TObject *Sender);
	void __fastcall QyNotaFiscalCalcFields(TDataSet *DataSet);
	void __fastcall grdItensEditButtonClick(TObject *Sender);
   void __fastcall SubClassWndProc(Messages::TMessage &Message);
   void __fastcall btPesqTransportadorClick(TObject *Sender);
   void __fastcall CodTransportadorValidate(TField *Sender);
   void __fastcall NaturezaOperacaoValidate(TField *Sender);
   void __fastcall btPesqNatOpClick(TObject *Sender);
   void __fastcall FormShow(TObject *Sender);
   void __fastcall lbEmpresaClick(TObject *Sender);
   void __fastcall grdItensColEnter(TObject *Sender);
   void __fastcall grdItensColExit(TObject *Sender);
   void __fastcall grdItensCellClick(TColumn *Column);
   void __fastcall TipoPessoaChange(TField *Sender);
   void __fastcall QyNotaFiscalBeforeDelete(TDataSet *DataSet);
   void __fastcall QyNotaFiscalAfterOpen(TDataSet *DataSet);
   void __fastcall QyNotaFiscalBeforeClose(TDataSet *DataSet);
   void __fastcall execNumeracaoNFExecute(TObject *Sender);
private:	// User declarations
	bool PostStatus;
	void __fastcall ValidInsert(bool &bValid);
	void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
   void __fastcall AfterCreateFields(TDataSet *DataSet);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
   void __fastcall CarregarFormaPagto();
	void __fastcall CarregarSitNotaFiscal();
   void __fastcall CarregarTipoFrete();
	void __fastcall CarregarEstado();
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
   void __fastcall DesabilitaCampos();
	void __fastcall SearchCliente(Variant Value);
   void __fastcall SearchNaturezaOperacao(Variant Value);
   void __fastcall SearchTransportador(Variant Value);
	void __fastcall HabilitarItens(bool Habilita);
	void __fastcall addItensConfirm(TList *pListAdd);
	void __fastcall SearchProduto(Variant Value);
	void __fastcall AfterImport();
public:		// User declarations
	SfgWorkEdition *pWorkEdtCliente; //Trabalha a lista de campos habilitando-os quando necessário
	__fastcall TObf1001(TComponent* Owner);
	void __fastcall FilterNotaFiscal(int NotaFiscal);
	void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
