/*
Módulo: Vendas
Função: Relatório Comissão x Representante
Autor.: Jackson Patrick Werka
Data..: 22/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3008H
#define uVdp3008H
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
class TVdp3008 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
   TfrxDBDataset *frxCnsReprComissao;
   TZQuery *CnsReprComissao;
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3008(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
