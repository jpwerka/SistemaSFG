/*
Módulo: Vendas
Função: Importação de Orçamentos para Pedidos de Venda
Autor.: Jackson Patrick Werka
Data..: 07/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1003H
#define uVdp1003H
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
class TVdp1003 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TButton *btCancel;
	TButton *btOK;
	TZQuery *QyOrcamento;
	TDataSource *DsOrcamento;
	TDBGrid *ListItens;
	TStringField *importado;
	TIntegerField *QyOrcamentocod_orcamento;
	TStringField *QyOrcamentocod_cliente;
	TStringField *QyOrcamentoden_cliente;
	TDateTimeField *QyOrcamentodata_cadastro;
	TFloatField *QyOrcamentovalor_total;
	TPanel *pnProgress;
	TLabel *lbInfoMail;
	TProgressBar *ProgressImport;
	void __fastcall ListItensDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
	void __fastcall ListItensCellClick(TColumn *Column);
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall btOKClick(TObject *Sender);
private:	// User declarations
	int num_orcamento;
public:		// User declarations
	__fastcall TVdp1003(TComponent* Owner);
	void __fastcall(__closure *AfterImport) ();
};
//---------------------------------------------------------------------------
#endif
