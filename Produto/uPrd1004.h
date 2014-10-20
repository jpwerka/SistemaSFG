/*
Módulo: Produtos
Função: Atualização de Preços de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd1004H
#define uPrd1004H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include "SfgAlignGrid.hpp"
#include <Grids.hpp>
#include "SfgResButtons.hpp"
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ImgList.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "uSfgToolbar.h"
#include <Buttons.hpp>
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
class TPrd1004 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TActionList *ActionList1;
	TAction *execPesquisa;
	TResBitBtn *btInformar;
	TResBitBtn *btProcessar;
	TResBitBtn *btSair;
	TResBitBtn *btConfirmar;
	TResBitBtn *btCancelar;
	TZQuery *QyAtuProdutos;
	TStringField *QyAtuProdutosden_familia;
	TStringField *QyAtuProdutoscod_produto;
	TStringField *QyAtuProdutosden_produto;
	TFloatField *QyAtuProdutospreco_custo;
	TAction *execInformar;
	TAction *execProcessar;
	TAction *execConfirmar;
	TAction *execCancelar;
	TPopupMenu *PopupMenu1;
	TMenuItem *Informar1;
	TMenuItem *Processar1;
	TMenuItem *Pesquisar1;
	TMenuItem *Confirmar1;
	TMenuItem *Cancelar1;
	TZQuery *QyAtuPrecoProduto;
	TAction *execAtualizar;
	TMenuItem *Atualizar1;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label1;
	TEdit *den_familia;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label6;
	TEdit *den_fornecedor;
	TEdit *cod_familia;
	TResBitBtn *btSearchFamilia;
	TEdit *cod_produto_ini;
	TResBitBtn *btSearchProdutoIni;
	TEdit *cod_produto_fim;
	TResBitBtn *btSearchProdutoFim;
	TEdit *cod_fornecedor;
	TResBitBtn *btSearchFornecedor;
	TAlignEdit *percentual;
	TResBitBtn *btAtualiza;
	TUpDown *UpDownPercent;
   TStringAlignGrid *grdProdutos;
	TLabel *Label5;
	TBevel *Bevel2;
	void __fastcall execPesquisaExecute(TObject *Sender);
	void __fastcall cod_fornecedorExit(TObject *Sender);
	void __fastcall cod_familiaExit(TObject *Sender);
	void __fastcall btSearchFornecedorClick(TObject *Sender);
	void __fastcall btSearchFamiliaClick(TObject *Sender);
	void __fastcall btSearchProdutoIniClick(TObject *Sender);
	void __fastcall btSearchProdutoFimClick(TObject *Sender);
	void __fastcall btAtualizaClick(TObject *Sender);
	void __fastcall grdProdutosDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
	void __fastcall percentualKeyPress(TObject *Sender, char &Key);
	void __fastcall execInformarExecute(TObject *Sender);
	void __fastcall execConfirmarExecute(TObject *Sender);
	void __fastcall execCancelarExecute(TObject *Sender);
	void __fastcall btSairClick(TObject *Sender);
	void __fastcall execProcessarExecute(TObject *Sender);
	void __fastcall grdProdutosMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
private:	// User declarations
	TEdit *pEditRet;
	bool FInformado;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall ClearObjectsCheck();
	void __fastcall HabilitaCampos(bool Habilita);
	void __fastcall RestauraGrid();
public:		// User declarations
	__fastcall TPrd1004(TComponent* Owner);
	void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
