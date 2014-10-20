/*
Módulo: Financeiro
Função: Relatório Conta à Receber
Autor.: Jackson Patrick Werka
Data..: 23/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3012H
#define uFin3012H
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
class TFin3012 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
   TZReadOnlyQuery *CnsContaReceber;
   TZReadOnlyQuery *CnsPagtos;
   TDataSource *DsContaReceber;
   TfrxDBDataset *frxCnsContaReceber;
   TfrxDBDataset *frxCnsPagtos;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3012(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
