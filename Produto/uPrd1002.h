/*
Módulo: Produtos
Função: Cadastro Famílias
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uPrd1002H
#define uPrd1002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include "SfgResButtons.hpp"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
class TPrd1002 : public TfrmBase02
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TLabel *Label2;
   TDBEdit *cod_familia;
   TDBEdit *den_familia;
   TZQuery *QyCadFamilia;
   TDataSource *DsCadFamilia;
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TPrd1002(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
