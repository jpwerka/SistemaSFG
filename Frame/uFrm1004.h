/*
Módulo: FrameWork
Função: Cadastro Grupos
Autor.: Jackson Patrick Werka
Data..: 25/08/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1004H
#define uFrm1004H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
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
class TFrm1004 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_grupo;
	TDBEdit *den_grupo;
   TZQuery *QyCadGrupo;
   TDataSource *DsCadGrupo;
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TFrm1004(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
