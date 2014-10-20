/*
Módulo: Compras
Função: Relatório Pedido de Compra por Situação
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3004H
#define uSup3004H
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
class TSup3004 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QySitPedidoCompra;
	TfrxDBDataset *frxQySitPedidoCompra;
private:	// User declarations
public:		// User declarations
	__fastcall TSup3004(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
