/*
Módulo: Financeiro
Função: Relatório Conta à Pagar
Autor.: Jackson Patrick Werka
Data..: 23/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3013H
#define uFin3013H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uRelatBase01.h"
#include <ExtCtrls.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class TFin3013 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
   TZReadOnlyQuery *CnsContaPagar;
   TZReadOnlyQuery *CnsPagtos;
   TDataSource *DsContaPagar;
   TfrxDBDataset *frxCnsContaPagar;
   TfrxDBDataset *frxCnsPagtos;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3013(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
