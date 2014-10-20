/*
Módulo: Compras
Função: Consulta Pedidos de Compra (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3002H
#define uSup3002H
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
class TSup3002 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *SfgToolbar;
	TResBitBtn *btRelatorio;
	TResBitBtn *btExit;
	TBevel *Bevel2;
	TGroupBox *gbFiltros;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *cod_fornecedor;
	TResBitBtn *btPesqFornecedor;
	TEdit *den_fornecedor;
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
	TRadioGroup *rbAgrupamento;
	TGroupBox *gbSituacao;
	TCheckBox *ckAberto;
	TCheckBox *ckEnviado;
	TCheckBox *ckRecebido;
	TCheckBox *ckFechado;
	TCheckBox *ckCancelado;
	TResBitBtn *btPesqPlanoContaFim;
	TEdit *cod_plano_conta_fim;
	TLabel *Label3;
	TLabel *Label6;
	TEdit *cod_centro_custo_fim;
	TResBitBtn *btPesqCentroCustoFim;
	void __fastcall cod_fornecedorExit(TObject *Sender);
	void __fastcall btPesqFornecedorClick(TObject *Sender);
	void __fastcall btPesqPlanoContaIniClick(TObject *Sender);
	void __fastcall btPesqPlanoContaFimClick(TObject *Sender);
	void __fastcall btPesqCentroCustoIniClick(TObject *Sender);
	void __fastcall btPesqCentroCustoFimClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall ConsultaPorFornecedor(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
	void __fastcall ConsultaPorSitacao(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
	void __fastcall ConsultaPorCentroCusto(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
	void __fastcall ConsultaPorContaContabil(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
public:		// User declarations
	__fastcall TSup3002(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
