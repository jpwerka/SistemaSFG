/*
Módulo: Financeiro
Função: Relatório Contas à Receber por Situação
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3009H
#define uFin3009H
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
class TFin3009 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QySitContaReceber;
	TfrxDBDataset *frxQySitContaReceber;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3009(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
