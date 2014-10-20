/*
Módulo: Produtos
Função: Consulta Lista de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd2001H
#define uPrd2001H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <DBTables.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "SfgResButtons.hpp"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
class TPrd2001 : public TForm
{
__published:    // IDE-managed Components
        TPanel *FooterPanel;
        TButton *A;
        TButton *B;
        TButton *C;
        TButton *D;
        TButton *E;
        TButton *F;
        TButton *G;
        TButton *H;
        TButton *I;
        TButton *J;
        TButton *K;
        TButton *L;
        TButton *M;
        TButton *N;
        TButton *O;
        TButton *P;
        TButton *Q;
        TButton *R;
        TButton *T;
        TButton *S;
        TButton *U;
        TButton *V;
        TButton *W;
        TButton *X;
        TButton *Y;
        TButton *Z;
        TButton *TODOS;
        TResBitBtn *BtRelat;
	TZQuery *TbCnsProduto;
        TDataSource *DsCnsProduto;
   TDBGrid *grdCnsProduto;
	TStringField *TbCnsProdutocod_produto;
	TStringField *TbCnsProdutoden_produto;
	TFloatField *TbCnsProdutopreco_custo;
	TFloatField *TbCnsProdutoqtd_estoque;
	TStringField *TbCnsProdutoies_ativo;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall AClick(TObject *Sender);
        void __fastcall BClick(TObject *Sender);
        void __fastcall CClick(TObject *Sender);
        void __fastcall DClick(TObject *Sender);
        void __fastcall EClick(TObject *Sender);
        void __fastcall FClick(TObject *Sender);
        void __fastcall GClick(TObject *Sender);
        void __fastcall HClick(TObject *Sender);
        void __fastcall IClick(TObject *Sender);
        void __fastcall JClick(TObject *Sender);
        void __fastcall KClick(TObject *Sender);
        void __fastcall LClick(TObject *Sender);
        void __fastcall MClick(TObject *Sender);
        void __fastcall NClick(TObject *Sender);
        void __fastcall OClick(TObject *Sender);
        void __fastcall PClick(TObject *Sender);
        void __fastcall QClick(TObject *Sender);
        void __fastcall RClick(TObject *Sender);
        void __fastcall SClick(TObject *Sender);
        void __fastcall TClick(TObject *Sender);
        void __fastcall UClick(TObject *Sender);
        void __fastcall VClick(TObject *Sender);
        void __fastcall WClick(TObject *Sender);
        void __fastcall XClick(TObject *Sender);
        void __fastcall YClick(TObject *Sender);
        void __fastcall ZClick(TObject *Sender);
        void __fastcall TODOSClick(TObject *Sender);
        void __fastcall BtRelatClick(TObject *Sender);
   void __fastcall grdCnsProdutoDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
private:       // Private declarations
public:		// User declarations
        __fastcall TPrd2001(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
