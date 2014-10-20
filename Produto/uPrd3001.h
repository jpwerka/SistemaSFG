/*
Módulo: Produtos
Função: Relatório Lista de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd3001H
#define uPrd3001H
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
#include "frxChBox.hpp"
//---------------------------------------------------------------------------
class TPrd3001 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *TbCnsProduto;
   TfrxDBDataset *frxTbCnsProduto;
private:	// User declarations
public:		// User declarations
        __fastcall TPrd3001(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
