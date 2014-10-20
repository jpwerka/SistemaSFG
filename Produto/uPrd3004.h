/*
Módulo: Produtos
Função: Relatório Estoque de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd3004H
#define uPrd3004H
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
class TPrd3004 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *QyEstoque;
   TfrxDBDataset *frxQyEstoque;
private:	// User declarations
public:		// User declarations
        __fastcall TPrd3004(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
