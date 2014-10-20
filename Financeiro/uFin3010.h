/*
Módulo: Financeiro
Função: Relatório Contas à Receber por Conta Contábil
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3010H
#define uFin3010H
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
class TFin3010 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCntContaReceber;
	TZReadOnlyQuery *QyContaContabil;
	TDataSource *DsCctPedidoCompra;
	TfrxDBDataset *frxQyCntContaReceber;
   TfrxDBDataset *frxQyContaContabil;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3010(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
