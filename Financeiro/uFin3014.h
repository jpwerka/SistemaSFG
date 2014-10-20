/*
Módulo: Financeiro
Função: Consulta Recebimento x Cliente (Filtros)
Autor.: Jackson Patrick Werka
Data..: 28/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3014H
#define uFin3014H
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
class TFin3014 : public TfrmBase01
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
   TRadioGroup *gbSituacao;
	void __fastcall cod_clienteExit(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall btRelatorioClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall ConsultaPorCliente(String SQL, System::TDateTime dt_data_ini, System::TDateTime dt_data_fim);
public:		// User declarations
	__fastcall TFin3014(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
