/*
Módulo: Vendas
Função: Relatório Pedidos de Venda por Representante
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3007H
#define uVdp3007H
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
class TVdp3007 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyForPedidoVenda;
   TfrxDBDataset *frxQyForPedidoVenda;
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3007(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
