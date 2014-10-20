/*
Módulo: Compras
Função: Registro Recebimento Pedidos de Compra
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//----------------------------------------------------------------------------
#ifndef uSup1003H
#define uSup1003H
//----------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <StdCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "SfgResButtons.hpp"
#include "ZSqlUpdate.hpp"
#include "ThemeMgr.hpp"
//----------------------------------------------------------------------------
class TSup1003 : public TForm
{
__published:
	TGroupBox *gbItens;
	TPanel *Panel1;
	TButton *btCancel;
	TButton *btOK;
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label12;
	TDBEdit *cod_pedido_compra;
	TEdit *data_recebimento;
	TDBGrid *grdItens;
	TZQuery *QyCadProduto;
	TIntegerField *QyCadProdutoseq_produto;
	TStringField *QyCadProdutocod_produto;
	TStringField *QyCadProdutoden_produto;
	TFloatField *QyCadProdutoqtd_produto;
	TFloatField *QyCadProdutoqtd_recebida;
	TDataSource *DataSource1;
	TZUpdateSQL *AddItemVenda;
	TIntegerField *CodPedidoCompra;
	void __fastcall QyCadProdutoBeforeInsert(TDataSet *DataSet);
	void __fastcall grdItensKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
	void __fastcall QyCadProdutoBeforeEdit(TDataSet *DataSet);
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall grdItensTitleClick(TColumn *Column);
public:
	virtual __fastcall TSup1003(TComponent* AOwner);
	void __fastcall(__closure *OnRecebeSucess)();
};
//----------------------------------------------------------------------------
#endif    
