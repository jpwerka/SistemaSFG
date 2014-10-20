/*
Módulo: Vendas
Função: Consulta Produtos Pedidos de Venda (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3011H
#define uVdp3011H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <DBCtrls.hpp>
#include "CustomButtons.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TVdp3011 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *SfgToolbar;
	TResBitBtn *btRelatorio;
	TResBitBtn *btExit;
	TBevel *Bevel2;
	TGroupBox *gbFiltros;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *cod_cliente;
	TResBitBtn *btPesqCliente;
	TEdit *den_cliente;
	TMaskEdit *data_ini;
	TCustomImgButton *btCalendar01;
	TMaskEdit *data_fim;
	TCustomImgButton *btCalendar02;
	TLabel *Label12;
	TLabel *Label4;
   TEdit *forma_pagto;
   TResBitBtn *btPesqFormaPagto;
	TLabel *Label5;
   TEdit *cod_produto_ini;
   TResBitBtn *btPesqProdutoIni;
   TEdit *den_forma_pagto;
	TLabel *Label3;
   TEdit *cod_produto_fim;
   TResBitBtn *btPesqProdutoFim;
   TLabel *Label7;
   TEdit *cod_representante;
   TResBitBtn *btPesqRepresentante;
   TEdit *den_representante;
   TLabel *Label6;
	void __fastcall cod_clienteExit(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall btPesqFormaPagtoClick(TObject *Sender);
	void __fastcall btPesqProdutoIniClick(TObject *Sender);
	void __fastcall btPesqProdutoFimClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
   void __fastcall btPesqRepresentanteClick(TObject *Sender);
   void __fastcall cod_representanteExit(TObject *Sender);
   void __fastcall forma_pagtoExit(TObject *Sender);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall ConsultaPorProduto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
public:		// User declarations
	__fastcall TVdp3011(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
