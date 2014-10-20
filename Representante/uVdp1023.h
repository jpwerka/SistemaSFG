/*
Módulo: Vendas - Representantes
Função: Cadastro Representantes
Autor.: Jackson Patrick Werka
Data..: 31/10/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1023H
#define uVdp1023H
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
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "CustomButtons.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TVdp1023 : public TfrmBase02
{
__published:	// IDE-managed Components
   TDataSource *DsCadRepresentante;
   TLabel *Label3;
   TLabel *Label20;
   TLabel *Rtulo98;
   TLabel *Label55;
   TLabel *Label1;
   TDBEdit *cod_representante;
   TGroupBox *GroupBox1;
   TDBCheckBox *ies_ativo;
   TDBDataComboBox *tipo_pessoa;
   TLabel *Label2;
   TGroupBox *grpInfo;
   TDBEdit *den_representante;
   TDBEdit *cpf_cnpj;
	TDBEdit *data_nasc_fund;
   TDBEdit *rg_ie;
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
   TDBEdit *UrlForn;
   TDBEdit *TelefoneForn;
   TLabel *Rtulo108;
   TLabel *Label16;
   TLabel *Label14;
   TLabel *Label13;
   TLabel *Label12;
   TLabel *Label11;
   TDBEdit *FaxForn;
   TDBEdit *EmailForn;
   TDBEdit *Contato;
   TDBEdit *CelForn;
	TCustomImgButton *btCalendar01;
	TZQuery *QyCidade;
   TLabel *Label15;
   TDBEdit *nome_fantasia;
   TDBEdit *perc_comissao;
   TResBitBtn *btObs;
   TGroupBox *grpObs;
   TDBMemo *observacao;
   TLabel *Label17;
   TZQuery *QyCadRepresentante;
   void __fastcall cod_ufChange(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall QyCadRepresentanteAfterScroll(TDataSet *DataSet);
   void __fastcall perc_comissaoKeyPress(TObject *Sender, char &Key);
   void __fastcall TipoPessoaChange(TField *Sender);
   void __fastcall grpObsExit(TObject *Sender);
   void __fastcall btObsClick(TObject *Sender);
private:	// User declarations
   bool UseCodAuto;
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   void __fastcall CarregarTipoPessoa();
   void __fastcall CarregarEstado();
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
public:		// User declarations
   __fastcall TVdp1023(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
