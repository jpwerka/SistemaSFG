/*
Módulo: Produtos
Função: Cadastro Unidades de Medida
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd1003H
#define uPrd1003H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
class TPrd1003 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_unid_medida;
	TDBEdit *den_unid_medida;
	TZQuery *QyCadUnidMedida;
	TDataSource *DsCadUnidMedida;
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TPrd1003(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
