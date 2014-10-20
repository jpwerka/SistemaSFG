/*
Módulo: Compras
Função: Relatório Pedido de Compra
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup3001H
#define uSup3001H
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
class TSup3001 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *CnsCompra;
	TZReadOnlyQuery *CnsPagtos;
	TZReadOnlyQuery *CnsProdutos;
	TDataSource *DsCompra;
   TfrxDBDataset *frxCnsCompra;
   TfrxDBDataset *frxCnsPagtos;
   TfrxDBDataset *frxCnsProdutos;
	void __fastcall CnsCompraAfterOpen(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TSup3001(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
