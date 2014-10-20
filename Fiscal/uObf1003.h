/*
Módulo: Vendas
Função: Importação de Pedidos de Venda para Notas Fiscais Saída
Autor.: Jackson Patrick Werka
Data..: 22/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uObf1003H
#define uObf1003H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TObf1003 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btCancel;
	TButton *btOK;
	TZQuery *QyPedidoVenda;
   TDataSource *DsPedidoVenda;
	TDBGrid *ListItens;
	TStringField *importado;
	TIntegerField *QyPedidoVendacod_pedido_venda;
	TStringField *QyPedidoVendacod_cliente;
	TStringField *QyPedidoVendaden_cliente;
	TDateTimeField *QyPedidoVendadata_cadastro;
	TFloatField *QyPedidoVendavalor_total;
	TPanel *pnProgress;
	TLabel *lbInfoMail;
	TProgressBar *ProgressImport;
   TLargeintField *natureza_operacao;
	void __fastcall ListItensDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall ListItensCellClick(TColumn *Column);
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btOKClick(TObject *Sender);
   void __fastcall NaturezaOperacaoValidate(TField *Sender);
   void __fastcall ListItensEditButtonClick(TObject *Sender);
   void __fastcall ListItensColEnter(TObject *Sender);
   void __fastcall ListItensColExit(TObject *Sender);
   void __fastcall QyPedidoVendaBeforeInsert(TDataSet *DataSet);
   void __fastcall ListItensKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	int num_pedido_venda;
   void __fastcall SearchNaturezaOperacao(Variant Value);
public:		// User declarations
	__fastcall TObf1003(TComponent* Owner);
	void __fastcall(__closure *AfterImport) ();
};
//---------------------------------------------------------------------------
#endif
