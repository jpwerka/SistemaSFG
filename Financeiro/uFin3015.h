/*
Módulo: Financeiro
Função: Relatório Recebimento por Cliente
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3015H
#define uFin3015H
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
class TFin3015 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyRecebtoCliente;
	TfrxDBDataset *frxQyRecebtoCliente;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3015(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
