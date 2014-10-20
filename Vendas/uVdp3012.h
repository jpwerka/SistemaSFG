/*
Módulo: Vendas
Função: Relatório Pedidos de Venda por Produto
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3012H
#define uVdp3012H
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
class TVdp3012 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
   TZReadOnlyQuery *QyPrdPedidoVenda;
   TfrxDBDataset *frxQyPrdPedidoVenda;
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3012(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
