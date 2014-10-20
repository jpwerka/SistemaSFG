/*
Módulo: Financeiro
Função: Cadastro Contas à Pagar
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef Fin1002H
#define Fin1002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include "ZSqlUpdate.hpp"
#include <Menus.hpp>
#include "CustomButtons.h"
#include <Buttons.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
struct TBDFin1002Object : public TBDDataObject {
  bool ies_parcelado;
};
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TFin1002 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *gpCadastro;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label12;
	TLabel *Label6;
	TDBEdit *cod_conta_pagar;
	TDBEdit *data_cadastro;
	TDBEdit *num_documento;
	TDBDataComboBox *ies_situacao;
	TCustomImgButton *bt_data_cadastro;
	TGroupBox *gpCredor;
	TLabel *Label3;
	TEdit *den_fornecedor;
	TDBEdit *cod_fornecedor;
	TResBitBtn *btPesqFornecedor;
   TZQuery *QyContaPagar;
	TZQuery *QyCadPagto;
	TDataSource *DsContaPagar;
	TDataSource *DsContaPagarPagto;
	TIntegerField *QyCadPagtocod_conta_pagar;
	TIntegerField *QyCadPagtoseq_parcela;
	TFloatField *QyCadPagtovalor_parcela;
	TDateTimeField *QyCadPagtodata_vencimento;
	TStringField *QyCadPagtoobservacao;
	TPageControl *pgDetalhes;
	TTabSheet *tbItens;
	TTabSheet *tbObs;
	TDBMemo *observacao;
	TZUpdateSQL *AddPagto;
	TStringField *QyCadPagtoies_pago;
	TLabel *Label4;
	TDBEdit *cod_plano_conta;
	TResBitBtn *btPesqPlanoConta;
	TLabel *Label5;
	TDBEdit *cod_centro_custo;
	TResBitBtn *btPesqCentroCusto;
	TResBitBtn *btRecContaPagar;
	TZReadOnlyQuery *QySitContaPagar;
	TDataSource *DsSitContaPagar;
	TLabel *Label7;
	TDBDataComboBox *tipo_registro;
	TPanel *pnTotal;
	TLabel *Label8;
	TDBEdit *valor_total;
	TDBGrid *grdPagtos;
	TPanel *pnParcela;
	TLabel *Label9;
	TLabel *Label10;
	TDBDataComboBox *cod_forma_pagto;
	TEdit *num_parcelas;
	TUpDown *UpDwNumParcelas;
   TActionList *ActionList1;
   TAction *execVisualizaPagto;
   TAction *execRelatorio;
   TAction *delLine;
   TMenuItem *execVisualizaPagto1;
   TMenuItem *execRelatorio1;
   TResBitBtn *btRelatorio;
	void __fastcall FormContaPagarClose(TObject *Sender, TCloseAction &Action);
	void __fastcall CodFornecedorValidate(TField *Sender);
	void __fastcall NavegexecBtEditClickExecute(TObject *Sender);
	void __fastcall NavegexecBtNewClickExecute(TObject *Sender);
	void __fastcall cod_fornecedorExit(TObject *Sender);
	void __fastcall btPesqFornecedorClick(TObject *Sender);
	void __fastcall btPesqPlanoContaClick(TObject *Sender);
	void __fastcall btPesqCentroCustoClick(TObject *Sender);
	void __fastcall bt_data_cadastroClick(TObject *Sender);
	void __fastcall QyContaPagarAfterPost(TDataSet *DataSet);
	void __fastcall QyContaPagarAfterScroll(TDataSet *DataSet);
	void __fastcall NavegexecBtSaveClickExecute(TObject *Sender);
	void __fastcall QyContaPagarBeforePost(TDataSet *DataSet);
	void __fastcall NavegexecBtCancelClickExecute(TObject *Sender);
	void __fastcall CodCentroCustoValidate(TField *Sender);
	void __fastcall CodPlanoContaValidate(TField *Sender);
	void __fastcall btRecContaPagarClick(TObject *Sender);
	void __fastcall QyContaPagarBeforeDelete(TDataSet *DataSet);
	void __fastcall NavegbtDeleteClick(TObject *Sender);
	void __fastcall cod_forma_pagtoChange(TObject *Sender);
	void __fastcall UpDwNumParcelasClick(TObject *Sender, TUDBtnType Button);
	void __fastcall QyCadPagtoBeforeInsert(TDataSet *DataSet);
	void __fastcall grdPagtosKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
	void __fastcall QyCadPagtovalor_parcelaSetText(TField *Sender,
          const AnsiString Text);
	void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
	void __fastcall grdPagtosDrawColumnCell(TObject *Sender,
			 const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall grdPagtosColEnter(TObject *Sender);
	void __fastcall grdPagtosColExit(TObject *Sender);
	void __fastcall grdPagtosEditButtonClick(TObject *Sender);
	void __fastcall EditPagtoSetFocus(TObject *Sender);
   void __fastcall QyContaPagarPostError(TDataSet *DataSet,
          EDatabaseError *E, TDataAction &Action);
   void __fastcall QyContaPagarAfterOpen(TDataSet *DataSet);
   void __fastcall QyContaPagarBeforeClose(TDataSet *DataSet);
   void __fastcall execRelatorioExecute(TObject *Sender);
private:	// User declarations
   int NivelPerm;
   void __fastcall AfterCreateFields(TDataSet *DataSet);
	void __fastcall ValidInsert(bool &bValid);
	void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
	void __fastcall CarregarSitContaPagar();
	void __fastcall CarregarTipoRegistro();
	void __fastcall CarregarFormaPagto();
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	void __fastcall SearchFornecedor(Variant Value);
	void __fastcall SearchPlanoConta(Variant Value);
	void __fastcall SearchCentroCusto(Variant Value);
	void __fastcall HabilitarItens(bool Habilita);
public:		// User declarations
	bool PostStatus;
	__fastcall TFin1002(TComponent* Owner);
   void __fastcall FilterCodConta(int CodConta);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
