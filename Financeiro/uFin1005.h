/*
Módulo: Financeiro
Função: Recebimentos Contas à Receber
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin1005H
#define uFin1005H
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
class TFin1005 : public TfrmBase02
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *CnsContaReceber;
	TDataSource *DsContaReceber;
	TGroupBox *gpCadastro;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label12;
	TLabel *Label6;
	TLabel *Label4;
	TLabel *Label5;
	TDBEdit *cod_conta_receber;
	TDBEdit *data_cadastro;
	TDBEdit *num_documento;
   TDBDataComboBox *ies_situacao;
	TDBEdit *cod_plano_conta;
	TDBEdit *cod_centro_custo;
	TLabel *Label3;
	TDBEdit *den_cliente;
	TDBEdit *cod_cliente;
	TLabel *Label7;
	TDBEdit *cod_forma_pagto;
	TGroupBox *gbPagtos;
	TDBEdit *valor_parcela;
	TDBEdit *valor_recebido;
	TDBEdit *data_recebimento;
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
	TIntegerField *QyCadPagtocod_conta_receber;
	TIntegerField *QyCadPagtoseq_parcela;
	TFloatField *QyCadPagtovalor_parcela;
	TDateTimeField *QyCadPagtodata_vencimento;
	TStringField *QyCadPagtoies_recebido;
	TDataSource *DsContaReceberPagto;
	TZUpdateSQL *AtuPagto;
	TFloatField *QyCadPagtovalor_desconto;
	TFloatField *QyCadPagtovalor_acrescimo;
	TFloatField *QyCadPagtovalor_multa;
	TDateTimeField *QyCadPagtodata_recebimento;
	TFloatField *QyCadPagtovalor_recebido;
	TResBitBtn *btPagarPagto;
	TResBitBtn *btSavePagto;
	TResBitBtn *btCancelPagto;
	TResBitBtn *btEstornaPagto;
	TCustomImgButton *bt_data_recebimento;
	TZReadOnlyQuery *QySitContaReceber;
	TDataSource *DsSitContaReceber;
	void __fastcall btPagarPagtoClick(TObject *Sender);
	void __fastcall btSavePagtoClick(TObject *Sender);
	void __fastcall btCancelPagtoClick(TObject *Sender);
	void __fastcall QyCadPagtoAfterScroll(TDataSet *DataSet);
	void __fastcall btEstornaPagtoClick(TObject *Sender);
	void __fastcall CnsContaReceberAfterScroll(TDataSet *DataSet);
	void __fastcall grdPagtosDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall bt_data_recebimentoClick(TObject *Sender);
   void __fastcall CnsContaReceberAfterOpen(TDataSet *DataSet);
   void __fastcall CnsContaReceberBeforeClose(TDataSet *DataSet);
private:	// User declarations
   void __fastcall CarregarSitContaReceber();
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
	void __fastcall HabilitarItens(bool Habilita);
	bool __fastcall ValidaCampos();
	SfgWorkEdition *pWorkEdtPagto; //Trabalha a lista de campos habilitando-os quando necessário
public:		// User declarations
	__fastcall TFin1005(TComponent* Owner);
   void __fastcall FilterCodConta(int CodConta);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
