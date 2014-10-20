/*
Módulo: Vendas - Clientes
Função: Relatório Lista de Telefone dos Clientes
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp3020H
#define uVdp3020H
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
class TVdp3020 : public TfrmRelatBase01
{
__published:	// IDE-managed Components
	TZQuery *QyFoneCliente;
	TfrxDBDataset *frxQyFoneCliente;
private:	// User declarations
public:		// User declarations
	__fastcall TVdp3020(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
