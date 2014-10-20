/*
Módulo: Compras - Fornecedores
Função: Relatório Lista de Telefone dos Fornecedores
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3020H
#define uSup3020H
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
class TSup3020 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
   TZQuery *QyFoneFornec;
   TfrxDBDataset *frxQyFoneFornec;
private:	// User declarations
public:		// User declarations
	__fastcall TSup3020(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
