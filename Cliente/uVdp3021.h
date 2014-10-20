/*
Módulo: Vendas - Clientes
Função: Relatório Clientes x Endereço
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3021H
#define uVdp3021H
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
class TVdp3021 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *QyClienteEnd;
   TfrxDBDataset *frxQyClienteEnd;
private:	// User declarations
public:		// User declarations
        __fastcall TVdp3021(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
