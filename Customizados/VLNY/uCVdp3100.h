/*
Módulo: Vendas
Função: Relatório Pedido de Venda
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uCVdp3100H
#define uCVdp3100H
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
class TCVdp3100 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *CnsPedidoVenda;
	TZReadOnlyQuery *CnsProdutos;
	TDataSource *DsPedidoVenda;
   TfrxDBDataset *frxCnsPedidoVenda;
   TfrxDBDataset *frxCnsProdutos;
private:	// User declarations
public:		// User declarations
	__fastcall TCVdp3100(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
