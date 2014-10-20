/*
Módulo: Produtos
Função: Relatório Lista de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd3002H
#define uPrd3002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "ZDataset.hpp"
#include "frxClass.hpp"
#include "frxDBSet.hpp"
#include "uRelatBase01.h"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
//---------------------------------------------------------------------------
class TPrd3002 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *TbCnsProduto;
   TfrxDBDataset *frxTbCnsProduto;
private:	// User declarations
public:		// User declarations
        __fastcall TPrd3002(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
