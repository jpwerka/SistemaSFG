/*
Módulo: Compras
Função: Relatório Pedido de Compra por Centro de Custo
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3006H
#define uSup3006H
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
class TSup3006 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCctPedidoCompra;
	TDataSource *DsCctPedidoCompra;
	TZReadOnlyQuery *QyCentroCusto;
   TfrxDBDataset *frxQyCentroCusto;
   TfrxDBDataset *frxQyCctPedidoCompra;
private:	// User declarations
public:		// User declarations
	__fastcall TSup3006(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
