/*
Módulo: Vendas
Função: Cadastro Formas de Pagamento
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1010H
#define uVdp1010H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TVdp1010 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_forma_pagto;
	TDBEdit *den_forma_pagto;
	TZQuery *QyCadFormaPagto;
	TDataSource *DsCadFormaPagto;
	TDBCheckBox *ies_parcelado;
   TDBCheckBox *ies_financeiro;
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
	bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TVdp1010(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
