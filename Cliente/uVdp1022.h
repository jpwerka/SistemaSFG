/*
Módulo: Vendas - Clientes
Função: Cadastro Cidades
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1022H
#define uVdp1022H
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
class TVdp1022 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_cidade;
	TDBEdit *den_cidade;
	TZQuery *QyCadCidade;
	TDataSource *DsCadCidade;
	TLabel *Label5;
	TDBComboBox *cod_uf;
   TLabel *Label4;
   TDBEdit *cod_ibge;
private:	// User declarations
   bool UseCodAuto;
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
	void __fastcall ValidDelete(bool &bValid);
	void __fastcall CarregarEstado();
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
	__fastcall TVdp1022(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
