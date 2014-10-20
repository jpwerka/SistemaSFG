/*
Módulo: Vendas
Função: Relatório Orçamento
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3010H
#define uVdp3010H
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
class TVdp3010 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZReadOnlyQuery *CnsOrcamento;
	TZReadOnlyQuery *CnsPagtos;
	TZReadOnlyQuery *CnsProdutos;
	TDataSource *DsOrcamento;
   TfrxDBDataset *frxCnsOrcamento;
   TfrxDBDataset *frxCnsPagtos;
   TfrxDBDataset *frxCnsProdutos;
	void __fastcall CnsOrcamentoAfterOpen(TDataSet *DataSet);
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3010(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
