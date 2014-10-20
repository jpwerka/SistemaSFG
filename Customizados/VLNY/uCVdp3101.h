/*
Módulo: Vendas
Função: Consulta Amostragem por Representante (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uCVdp3101H
#define uCVdp3101H
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
class TCVdp3101 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *SfgToolbar;
	TResBitBtn *btRelatorio;
	TResBitBtn *btExit;
	TBevel *Bevel2;
	TGroupBox *gbFiltros;
	TLabel *Label2;
	TMaskEdit *data_ini;
	TCustomImgButton *btCalendar01;
	TMaskEdit *data_fim;
	TCustomImgButton *btCalendar02;
	TLabel *Label12;
	TGroupBox *gbSituacao;
	TCheckBox *ckAberto;
	TCheckBox *ckFechado;
	TCheckBox *ckCancelado;
   TLabel *Label7;
   TEdit *cod_representante;
   TResBitBtn *btPesqRepresentante;
   TEdit *den_representante;
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
   void __fastcall btPesqRepresentanteClick(TObject *Sender);
   void __fastcall cod_representanteExit(TObject *Sender);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall ConsultaPorRepresentante(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
public:		// User declarations
	__fastcall TCVdp3101(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
