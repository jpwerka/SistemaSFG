/*
Módulo: Produtos
Função: Cadastro Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd1001H
#define uPrd1001H
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
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <ComCtrls.hpp>
#include "uSfgMetaData.h"
//---------------------------------------------------------------------------
class TPrd1001 : public TfrmBase02
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TLabel *Label2;
   TDBEdit *cod_produto;
   TDBCheckBox *ies_ativo;
   TDBDataComboBox *cod_familia;
   TZQuery *QyProduto;
   TDataSource *DsProduto;
   TZQuery *QyCnsUnidMedida;
   TPageControl *pgDetItem;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TTabSheet *TabSheet3;
	TDBMemo *observacoes;
	TTabSheet *TabSheet4;
	TLabel *Label3;
	TDBEdit *den_produto;
	TLabel *Label4;
	TDBEdit *qtd_estoque;
	TLabel *Label5;
	TDBEdit *qtd_estoque_min;
	TLabel *Label6;
	TDBEdit *preco_custo;
	TLabel *Label8;
	TDBEdit *preco_venda;
	TDBRadioGroup *DBRadioGroup1;
	TDBCheckBox *DBCheckBox1;
	TLabel *Label9;
	TDBEdit *preco_compra;
	TDBDataComboBox *cod_unid_medida;
	TLabel *Label7;
   TZQuery *QyFamilia;
   TTabSheet *TabSheet5;
   TLabel *Label10;
   TDBEdit *cod_ncm;
   TLabel *Label11;
   TDBDataComboBox *origem_mercadoria;
   TLabel *Label12;
   TDBEdit *cod_extipi;
   TLabel *Label13;
   TDBEdit *classe_enq_ipi;
   TLabel *Label14;
   TDBEdit *cod_enq_ipi;
private:	// User declarations
   TStrings *TipoProduto;
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
   void __fastcall CarregarOrigemMercadoria();
   void __fastcall CarregarTipoProduto();
   void __fastcall BeforeFilterEdit(SfgFilter *Filter, SfgMfEdit &EditCmp);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
public:		// User declarations
   __fastcall TPrd1001(TComponent* Owner);
   __fastcall ~TPrd1001();
};
//---------------------------------------------------------------------------
#endif
