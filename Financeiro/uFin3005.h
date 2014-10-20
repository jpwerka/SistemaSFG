/*
Módulo: Financeiro
Função: Relatório Conta à Pagar por Conta Contábil
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin3005H
#define uFin3005H
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
class TFin3005 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCntContaPagar;
	TZReadOnlyQuery *QyContaContabil;
	TDataSource *DsCctPedidoCompra;
	TfrxDBDataset *frxQyCntContaPagar;
   TfrxDBDataset *frxQyContaContabil;
private:	// User declarations
public:		// User declarations
	__fastcall TFin3005(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
