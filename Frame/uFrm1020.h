/*
Módulo: Frame - Empresas
Função: Cadastro Empresas
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1020H
#define uFrm1020H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
class TFrm1020 : public TfrmBase02
{
__published:	// IDE-managed Components
   TZQuery *QyCadEmpresa;
   TDataSource *DsCadEmpresa;
   TLabel *Label3;
   TLabel *Label20;
   TLabel *Rtulo98;
   TLabel *Label1;
   TDBEdit *cod_empresa;
   TGroupBox *GroupBox1;
   TDBEdit *razao_social;
   TDBEdit *cnpj;
   TDBEdit *inscricao_estadual;
   TGroupBox *GroupBox3;
   TDBEdit *numero;
   TDBEdit *logradouro;
   TDBComboBox *cod_uf;
   TDBEdit *complemento;
   TDBDataComboBox *cod_cidade;
   TDBEdit *bairro;
   TLabel *Label9;
   TLabel *Label8;
   TLabel *Label7;
   TLabel *Label6;
   TLabel *Label5;
   TLabel *Label4;
   TLabel *Label10;
   TDBEdit *cep;
   TGroupBox *GroupBox4;
   TDBEdit *telefone;
   TLabel *Label13;
   TLabel *Label11;
   TDBEdit *fax;
	TZQuery *QyCidade;
   TLabel *Label2;
   TDBEdit *nome_fantasia;
   TGroupBox *GroupBox2;
   TLabel *Label12;
   TLabel *Label14;
   TDBEdit *inscricao_municipal;
   TDBDataComboBox *regime_tributario;
   void __fastcall cod_ufChange(TObject *Sender);
	void __fastcall QyCadEmpresaAfterScroll(TDataSet *DataSet);
private:	// User declarations
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   void __fastcall BeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
   void __fastcall CarregarRegimeTributario();
   void __fastcall CarregarEstado();
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
   __fastcall TFrm1020(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
