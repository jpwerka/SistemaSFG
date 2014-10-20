/*
Módulo: Compras
Função: Análise Pedidos de Compra (Integração Excel)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup2002H
#define uSup2002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <OleCtnrs.hpp>
//---------------------------------------------------------------------------
class TSup2002 : public TfrmBase01
{
__published:	// IDE-managed Components
	TOleContainer *OleAnalise;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   void __fastcall DataSetAfterOpen(TDataSet* DataSet);
public:		// User declarations
	__fastcall TSup2002(TComponent* Owner, String SQL);
};
//---------------------------------------------------------------------------
#endif
