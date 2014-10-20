/*
Módulo: Financeiro
Função: Relatório Conta à Pagar por Centro de Custo
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3006H
#define uFin3006H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uRelatBase01.h"
#include <ExtCtrls.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class TFin3006 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCctContaPagar;
	TZReadOnlyQuery *QyCentroCusto;
	TDataSource *DsCctContaPagar;
	TfrxDBDataset *frxQyCentroCusto;
   TfrxDBDataset *frxQyCctContaPagar;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3006(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
