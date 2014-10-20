/*
Módulo: Financeiro
Função: Pagamentos Contas à Pagar
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin1004H
#define uFin1004H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "ZAbstractDataset.hpp"
#include "ZSqlUpdate.hpp"
#include <Menus.hpp>
#include "CustomButtons.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TFin1004 : public TfrmBase02
{
__published:	// IDE-managed Components
	TZQuery *CnsContaPagar;
	TDataSource *DsContaPagar;
	TGroupBox *gpCadastro;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label12;
	TLabel *Label6;
	TLabel *Label4;
	TLabel *Label5;
	TDBEdit *cod_conta_pagar;
	TDBEdit *data_cadastro;
	TDBEdit *num_documento;
   TDBDataComboBox *ies_situacao;
	TDBEdit *cod_plano_conta;
	TDBEdit *cod_centro_custo;
	TLabel *Label3;
	TDBEdit *den_fornecedor;
	TDBEdit *cod_fornecedor;
	TLabel *Label7;
	TDBEdit *cod_forma_pagto;
	TGroupBox *gbPagtos;
	TDBEdit *valor_parcela;
	TDBEdit *valor_pago;
	TDBEdit *data_pagamento;
	TDBEdit *valor_desconto;
	TDBEdit *valor_multa;
	TDBEdit *valor_acrescimo;
	TLabel *Label8;
	TLabel *Label9;
	TLabel *Label10;
	TLabel *Label11;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label15;
	TDBGrid *grdPagtos;
	TZQuery *QyCadPagto;
	TIntegerField *QyCadPagtocod_conta_pagar;
	TIntegerField *QyCadPagtoseq_parcela;
	TFloatField *QyCadPagtovalor_parcela;
	TDateTimeField *QyCadPagtodata_vencimento;
	TStringField *QyCadPagtoies_pago;
	TDataSource *DsContaPagarPagto;
	TZUpdateSQL *AtuPagto;
	TFloatField *QyCadPagtovalor_desconto;
	TFloatField *QyCadPagtovalor_acrescimo;
	TFloatField *QyCadPagtovalor_multa;
	TDateTimeField *QyCadPagtodata_pagamento;
	TFloatField *QyCadPagtovalor_pago;
	TResBitBtn *btPagarPagto;
	TResBitBtn *btSavePagto;
	TResBitBtn *btCancelPagto;
	TResBitBtn *btEstornaPagto;
	TCustomImgButton *bt_data_pagamento;
	TZReadOnlyQuery *QySitContaPagar;
	TDataSource *DsSitContaPagar;
	void __fastcall btPagarPagtoClick(TObject *Sender);
	void __fastcall btSavePagtoClick(TObject *Sender);
	void __fastcall btCancelPagtoClick(TObject *Sender);
	void __fastcall QyCadPagtoAfterScroll(TDataSet *DataSet);
	void __fastcall btEstornaPagtoClick(TObject *Sender);
	void __fastcall CnsContaPagarAfterScroll(TDataSet *DataSet);
	void __fastcall grdPagtosDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall bt_data_pagamentoClick(TObject *Sender);
   void __fastcall CnsContaPagarAfterOpen(TDataSet *DataSet);
   void __fastcall CnsContaPagarBeforeClose(TDataSet *DataSet);
private:	// User declarations
   void __fastcall CarregarSitContaPagar();
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
	void __fastcall HabilitarItens(bool Habilita);
	bool __fastcall ValidaCampos();
	SfgWorkEdition *pWorkEdtPagto; //Trabalha a lista de campos habilitando-os quando necessário
public:		// User declarations
	__fastcall TFin1004(TComponent* Owner);
   void __fastcall FilterCodConta(int CodConta);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
