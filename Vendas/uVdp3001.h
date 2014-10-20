/*
Módulo: Vendas
Função: Relatório Pedido de Venda
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3001H
#define uVdp3001H
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
class TVdp3001 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *CnsPedidoVenda;
	TZReadOnlyQuery *CnsPagtos;
	TZReadOnlyQuery *CnsProdutos;
	TDataSource *DsPedidoVenda;
   TfrxDBDataset *frxCnsPedidoVenda;
   TfrxDBDataset *frxCnsPagtos;
   TfrxDBDataset *frxCnsProdutos;
   TZQuery *CnsRepresentante;
   TfrxDBDataset *frxCnsRepresentante;
	void __fastcall CnsPedidoVendaAfterOpen(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3001(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
