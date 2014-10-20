/*
Módulo: Vendas
Função: Relatório Pedidos de Venda por Conta Contábil
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3005H
#define uVdp3005H
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
class TVdp3005 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *QyCntPedidoVenda;
	TDataSource *DsCctPedidoVenda;
	TZReadOnlyQuery *QyContaContabil;
   TfrxDBDataset *frxQyCntPedidoVenda;
   TfrxDBDataset *frxQyContaContabil;
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3005(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
