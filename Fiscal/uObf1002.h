/*
Módulo: Vendas - Clientes
Função: Cadastro Natureza Operação
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uObf1002H
#define uObf1002H
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
#include "CustomDbControls.h"
//---------------------------------------------------------------------------
class TObf1002 : public TfrmBase02
{
__published:	// IDE-managed Components
   TGroupBox *gbCadastro;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *cod_natureza_operacao;
	TDBEdit *den_natureza_operacao;
	TZQuery *QyNaturezaOperacao;
	TDataSource *DsNaturezaOperacao;
   TGroupBox *gbInformacao;
   TLabel *Label4;
   TDBDataComboBox *cod_cst_icms_padrao;
   TLabel *Label3;
   TLabel *Label5;
   TLabel *Label6;
   TDBDataComboBox *cod_cst_ipi_padrao;
   TDBDataComboBox *cod_cst_pis_padrao;
   TLabel *Label7;
   TDBDataComboBox *cod_cst_cofins_padrao;
   TDBEdit *cod_cfop_padrao;
   TDBEdit *percentual_icms;
   TLabel *Label8;
   TGroupBox *gbInfoCompl;
   TDBMemo *info_complementar;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall percentual_icmsKeyPress(TObject *Sender, char &Key);
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
   void __fastcall CarregarCST();
public:		// User declarations
	__fastcall TObf1002(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
