/*
Módulo: Financeiro
Função: Relatório Contas à Receber por Centro de Custo
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3011H
#define uFin3011H
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
class TFin3011 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCctContaReceber;
	TZReadOnlyQuery *QyCentroCusto;
	TDataSource *DsCctContaReceber;
	TfrxDBDataset *frxQyCentroCusto;
   TfrxDBDataset *frxQyCctContaReceber;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3011(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
