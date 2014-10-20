/*
Módulo: Financeiro
Função: Relatório Pagamento x Fornecedor
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3017H
#define uFin3017H
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
class TFin3017 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyPagtoFornecedor;
	TfrxDBDataset *frxQyPagtoFornecedor;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3017(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
