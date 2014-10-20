/*
Módulo: Fiscal
Função: Impostos dos Itens da Nota Fiscal
Autor.: Jackson Patrick Werka
Data..: 13/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uObf1005H
#define uObf1005H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
#define NOTA_FISCAL_ENTRADA 0
#define NOTA_FISCAL_SAIDA   1
#define REGIME_SIMPLES      0
#define REGIME_NORMAL       1
//---------------------------------------------------------------------------
class TObf1005 : public TForm
{
__published:	// IDE-managed Components
   TPageControl *pgImpostos;
   TTabSheet *pgICMS;
   TTabSheet *pgIPI;
   TTabSheet *pgPIS;
   TTabSheet *pgCOFINS;
   TTabSheet *pgISSQN;
   TPanel *Panel1;
   TLabel *Label1;
   TComboBox *regime_tributario;
   TLabel *Label2;
   TComboBox *cod_cst_icms;
   TPanel *Panel2;
   TGroupBox *gbICMS;
   TGroupBox *gbICMSST;
   TLabel *Label3;
   TLabel *Label4;
   TAlignEdit *aliquota_icms;
   TAlignEdit *valor_icms;
   TLabel *Label5;
   TLabel *Label20;
   TLabel *Label7;
   TLabel *Label8;
   TLabel *Label9;
   TAlignEdit *perc_marg_add_icmsst;
   TAlignEdit *perc_red_bc_icmsst;
   TAlignEdit *valor_bc_icmsst;
   TAlignEdit *aliquota_icmsst;
   TAlignEdit *valor_icmsst;
   TLabel *Label10;
   TComboBox *mod_bc_icmsst;
   TLabel *Label11;
   TComboBox *cod_cst_ipi;
   TLabel *Label12;
   TComboBox *mod_bc_ipi;
   TLabel *Label13;
   TAlignEdit *valor_bc_ipi;
   TLabel *Label14;
   TAlignEdit *aliquota_ipi;
   TLabel *Label15;
   TAlignEdit *qtd_unid_ipi;
   TLabel *Label16;
   TAlignEdit *valor_unid_ipi;
   TLabel *Label17;
   TAlignEdit *valor_ipi;
   TPanel *Panel3;
   TLabel *Label6;
   TComboBox *cod_cst_pis;
   TPanel *Panel4;
   TGroupBox *gbPIS;
   TLabel *Label18;
   TComboBox *tipo_calc_pis;
   TLabel *Label19;
   TAlignEdit *valor_bc_pis;
   TLabel *Label21;
   TAlignEdit *aliquota_pis_perc;
   TLabel *Label22;
   TAlignEdit *aliquota_pis_reais;
   TLabel *Label23;
   TAlignEdit *qtd_vendida_pis;
   TLabel *Label24;
   TAlignEdit *valor_pis;
   TGroupBox *gbPISST;
   TLabel *Label25;
   TLabel *Label26;
   TLabel *Label27;
   TLabel *Label28;
   TLabel *Label29;
   TLabel *Label30;
   TComboBox *tipo_calc_pisst;
   TAlignEdit *valor_bc_pisst;
   TAlignEdit *aliquota_pisst_perc;
   TAlignEdit *aliquota_pisst_reais;
   TAlignEdit *qtd_vendida_pisst;
   TAlignEdit *valor_pisst;
   TPanel *Panel6;
   TGroupBox *gbCOFINS;
   TLabel *Label31;
   TLabel *Label32;
   TLabel *Label33;
   TLabel *Label34;
   TLabel *Label35;
   TLabel *Label36;
   TComboBox *tipo_calc_cofins;
   TAlignEdit *valor_bc_cofins;
   TAlignEdit *aliquota_cofins_perc;
   TAlignEdit *aliquota_cofins_reais;
   TAlignEdit *qtd_vendida_cofins;
   TAlignEdit *valor_cofins;
   TGroupBox *gbCOFINSST;
   TLabel *Label37;
   TLabel *Label38;
   TLabel *Label39;
   TLabel *Label40;
   TLabel *Label41;
   TLabel *Label42;
   TComboBox *tipo_calc_cofinsst;
   TAlignEdit *valor_bc_cofinsst;
   TAlignEdit *aliquota_cofinsst_perc;
   TAlignEdit *aliquota_cofinsst_reais;
   TAlignEdit *qtd_vendida_cofinsst;
   TAlignEdit *valor_cofinsst;
   TPanel *Panel5;
   TLabel *Label43;
   TComboBox *cod_cst_cofins;
   TButton *btOK;
   TButton *btCancel;
   void __fastcall CampoMoedaEnter(TObject *Sender);
   void __fastcall CampoMoedaExit(TObject *Sender);
   void __fastcall ValorPercentualExit(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btOKClick(TObject *Sender);
   void __fastcall regime_tributarioChange(TObject *Sender);
   void __fastcall EditKeyPress(TObject *Sender, char &Key);
private:	// User declarations
   void __fastcall HabilitarCampos(bool Habilita);
   void __fastcall CarregarImpostos();
   void __fastcall SetIndexCombo(TComboBox *pComboBox, String sValue);
   bool __fastcall SalvarImpostos();
   bool __fastcall ValidarDados();
   void __fastcall GetRegimeTributario();
public:		// User declarations
   __fastcall TObf1005(TComponent* Owner, String sCodEmpresa,
      int iCodNotaFiscal, int iTipoNotaFiscal, int iSeqProduto, bool bEditable);
public:
   String CodEmpresa;
   int CodNotaFiscal;
   int TipoNotaFiscal;
   int SeqProduto;
   bool Editable;
};
//---------------------------------------------------------------------------
#endif
