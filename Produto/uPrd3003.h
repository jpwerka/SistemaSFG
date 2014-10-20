/*
Módulo: Produtos
Função: Relatório Estoque de Produtos (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd3003H
#define uPrd3003H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SfgResButtons.hpp"
#include <Mask.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TPrd3003 : public TfrmBase01
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox2;
	TGroupBox *GroupBox1;
	TLabel *Label4;
	TLabel *Label1;
	TResBitBtn *btSearchFamilia;
	TEdit *cod_produto_ini;
	TEdit *cod_familia;
	TResBitBtn *btSearchProdutoIni;
	TEdit *den_familia;
	TLabel *Label2;
	TEdit *cod_produto_fim;
	TResBitBtn *btSearchProdutoFim;
	TRadioButton *Independente;
	TRadioButton *Abaixo;
	TActionList *ActionList1;
	TAction *execPesquisa;
	TBevel *Bevel2;
	TPanel *SfgToolbar;
	TResBitBtn *btRelatorio;
	TResBitBtn *btExit;
	void __fastcall BtOKClick(TObject *Sender);
	void __fastcall cod_familiaExit(TObject *Sender);
	void __fastcall btSearchFamiliaClick(TObject *Sender);
	void __fastcall btSearchProdutoIniClick(TObject *Sender);
	void __fastcall btSearchProdutoFimClick(TObject *Sender);
	void __fastcall BtCancelClick(TObject *Sender);
	void __fastcall execPesquisaExecute(TObject *Sender);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
public:		// User declarations
	__fastcall TPrd3003(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
