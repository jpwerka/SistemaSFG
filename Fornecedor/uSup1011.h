/*
Módulo: Compras - Fornecedor
Função: Cadastro Fornecedor x Produto
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup1011H
#define uSup1011H
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
#include <Menus.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"
#include "CustomButtons.h"
#include <Buttons.hpp>
class SfgWorkEdition;
//---------------------------------------------------------------------------
class TSup1011 : public TfrmBase02
{
__published:	// IDE-managed Components
	TZQuery *QyCnsFornecedor;
	TDataSource *DsCnsFornecedor;
   TLabel *Label1;
   TDBEdit *cod_fornecedor;
   TGroupBox *GroupBox1;
   TDBCheckBox *ies_ativo;
   TDBDataComboBox *tipo_pessoa;
   TLabel *Label2;
	TLabel *Label3;
	TDBEdit *den_fornecedor;
	TPanel *pnAddProduto;
	TDBGrid *grdAddProduto;
   TZQuery *QyFornecProduto;
   TDataSource *DsFornecProduto;
   TStringField *QyFornecProdutocod_produto;
   TStringField *QyFornecProdutoden_produto;
   TFloatField *QyFornecProdutopreco_compra;
   TDateTimeField *QyFornecProdutodata_atualizacao;
   TStringField *QyFornecProdutocod_fornecedor;
	TActionList *ActionList1;
   TAction *addLine;
   TAction *delLine;
	TLabel *Label7;
	TZUpdateSQL *AtuSup1011;
   TResBitBtn *btAddLinha;
   TResBitBtn *btDelLinha;
   TResBitBtn *btAddItens;
   TAction *addItens;
   TPopupMenu *PopupMenu1;
   TMenuItem *AdicionarLinha1;
   TMenuItem *RemoverLinha1;
   TMenuItem *MenuItem1;
	void __fastcall addLineExecute(TObject *Sender);
	void __fastcall btEditClickExecute(TObject *Sender);
	void __fastcall delLineExecute(TObject *Sender);
	void __fastcall btSaveClickExecute(TObject *Sender);
	void __fastcall btCancelClickExecute(TObject *Sender);
	void __fastcall CodProdutoValidate(TField *Sender);
   void __fastcall grdAddProdutoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall QyFornecProdutoBeforeInsert(TDataSet *DataSet);
   void __fastcall grdAddProdutoEditButtonClick(TObject *Sender);
   void __fastcall grdAddProdutoDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
   void __fastcall addItensExecute(TObject *Sender);
   void __fastcall QyCnsFornecedorAfterOpen(TDataSet *DataSet);
   void __fastcall QyCnsFornecedorBeforeClose(TDataSet *DataSet);
private:	// User declarations
	void __fastcall CarregarTipoPessoa();
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	void __fastcall HabilitarItens(bool Habilita);
	void __fastcall SearchProduto(Variant Value);
   void __fastcall addItensConfirm(TList *pListAdd);
public:		// User declarations
   __fastcall TSup1011(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
