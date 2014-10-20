/*
Módulo: Financeiro
Função: Cadastro Centro de Custo
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin1006H
#define uFin1006H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
//---------------------------------------------------------------------------
class TFin1006 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_centro_custo;
	TDBEdit *den_centro_custo;
	TDataSource *DsCentroCusto;
   TZQuery *CentroCusto;
	TStringField *CentroCustocod_centro_custo;
	TStringField *CentroCustoden_centro_custo;
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
	void __fastcall CarregarEstado();
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TFin1006(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFin1006 *Fin1006;
//---------------------------------------------------------------------------
#endif
