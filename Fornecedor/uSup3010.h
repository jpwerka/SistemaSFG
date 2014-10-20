/*
Módulo: Compras - Fornecedor
Função: Relatório Fornecedores x Endereço
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3010H
#define uSup3010H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "uRelatBase01.h"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
//---------------------------------------------------------------------------
class TSup3010 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *QyFornecEnd;
   TfrxDBDataset *frxQyFornecEnd;
private:	// User declarations
public:		// User declarations
        __fastcall TSup3010(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
