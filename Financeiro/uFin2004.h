/*
Módulo: Financeiro
Função: Análise de Contas à Receber (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin2004H
#define uFin2004H
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
class TFin2004 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *SfgToolbar;
	TResBitBtn *btProcessar;
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
	TEdit *cod_plano_conta_ini;
	TResBitBtn *btPesqPlanoContaIni;
	TLabel *Label5;
	TEdit *cod_centro_custo_ini;
	TResBitBtn *btPesqCentroCustoIni;
	TGroupBox *gbSituacao;
	TCheckBox *ckPendente;
	TCheckBox *ckAndamento;
	TCheckBox *ckLiquidado;
	TCheckBox *ckCancelado;
	TResBitBtn *btPesqPlanoContaFim;
	TEdit *cod_plano_conta_fim;
	TLabel *Label3;
	TLabel *Label6;
	TEdit *cod_centro_custo_fim;
	TResBitBtn *btPesqCentroCustoFim;
	void __fastcall cod_clienteExit(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall btPesqPlanoContaIniClick(TObject *Sender);
	void __fastcall btPesqPlanoContaFimClick(TObject *Sender);
	void __fastcall btPesqCentroCustoIniClick(TObject *Sender);
	void __fastcall btPesqCentroCustoFimClick(TObject *Sender);
	void __fastcall btProcessarClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
   void __fastcall ExportToExcel(String Where);
   void __fastcall DataSetAfterOpen(TDataSet* DataSet);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
public:		// User declarations
	__fastcall TFin2004(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
