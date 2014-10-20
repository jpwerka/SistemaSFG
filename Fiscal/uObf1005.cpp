/*
Módulo: Fiscal
Função: Impostos dos Itens da Nota Fiscal
Autor.: Jackson Patrick Werka
Data..: 13/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "ZDataset.hpp"
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uObf1006.h"
#pragma hdrstop
#include "uObf1005.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TObf1005::TObf1005(TComponent* Owner, String sCodEmpresa,
      int iCodNotaFiscal, int iTipoNotaFiscal, int iSeqProduto, bool bEditable)
   : TForm(Owner)
{
   pgImpostos->ActivePageIndex = 0;
   this->CodEmpresa = sCodEmpresa;
   this->CodNotaFiscal = iCodNotaFiscal;
   this->TipoNotaFiscal = iTipoNotaFiscal;
   this->SeqProduto = iSeqProduto;
   this->Editable = bEditable;
   GetRegimeTributario();
   //Carregando as opções de CSTs
   regime_tributarioChange(regime_tributario);
   if (this->TipoNotaFiscal == NOTA_FISCAL_ENTRADA) {
      ObfCST::LoadCSTIPI(cod_cst_ipi,CST_IPI_ENTRADA);
   } else {
      ObfCST::LoadCSTIPI(cod_cst_ipi,CST_IPI_SAIDA);
   }
   ObfCST::LoadCSTPIS(cod_cst_pis);
   ObfCST::LoadCSTCOFINS(cod_cst_cofins);
   //Carregando as opções de Base Cálculo (BC)
   ObfModBC::LoadModBCICMS(mod_bc_icmsst,BASE_CALC_ICMS_ST);
   ObfModBC::LoadModBCIPI(mod_bc_ipi);
   ObfModBC::LoadModBCPIS(tipo_calc_pis);
   ObfModBC::LoadModBCPIS(tipo_calc_pisst);
   ObfModBC::LoadModBCCOFINS(tipo_calc_cofins);
   ObfModBC::LoadModBCCOFINS(tipo_calc_cofinsst);
   HabilitarCampos(this->Editable);

   CarregarImpostos();

}
//---------------------------------------------------------------------------
void __fastcall TObf1005::CampoMoedaEnter(TObject *Sender)
{
   TEdit* pEdit = (TEdit*)Sender;
   if (pEdit->Text.Length() > 0) {
      pEdit->Text = pEdit->Text.SubString(4,pEdit->Text.Length()-3);
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::CampoMoedaExit(TObject *Sender)
{
   TEdit* pEdit = (TEdit*)Sender;
   if (pEdit->Text.Length() > 0) {
      pEdit->Text = FloatToStrF(StrToFloat(pEdit->Text),ffCurrency,15,2);
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::ValorPercentualExit(TObject *Sender)
{
   TEdit* pEdit = (TEdit*)Sender;
   if (pEdit->Text.Length() > 0) {
      pEdit->Text = FloatToStrF(StrToFloat(pEdit->Text),ffFixed,5,2);
   }
}
//---------------------------------------------------------------------------
class THackEdit : public TCustomEdit
{
	typedef TCustomEdit inherited;
public:
	__property Color  = {default=-2147483643};
	__property ReadOnly  = {default=0};
};
class THackComboBox : public TCustomComboBox
{
	typedef TCustomComboBox inherited;
public:
	__property Color  = {default=-2147483643};
   __property Enabled  = {default=1};
};
//---------------------------------------------------------------------------
void __fastcall TObf1005::HabilitarCampos(bool Habilita)
{
   TComponent *pCmp;
   TColor Color = (Habilita) ? AppConfig->Colors->Enabled : AppConfig->Colors->Disabled;

   for (int i = 0; i < this->ComponentCount; i++) {
      pCmp = this->Components[i];
      if (pCmp->InheritsFrom(__classid(TCustomEdit))) {
         ((THackEdit*)pCmp)->ReadOnly = !Habilita;
         ((THackEdit*)pCmp)->Color = Color;
      }
      if (pCmp->InheritsFrom(__classid(TCustomComboBox))) {
         ((THackComboBox*)pCmp)->Color = Color;
         ((THackComboBox*)pCmp)->Enabled = Habilita;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::FormClose(TObject *Sender, TCloseAction &Action)
{
   ObfCST::UnloadCST(cod_cst_icms);
   ObfCST::UnloadCST(cod_cst_ipi);
   ObfCST::UnloadCST(cod_cst_pis);
   ObfCST::UnloadCST(cod_cst_cofins);
   ObfModBC::UnloadModBC(mod_bc_icmsst);
   ObfModBC::UnloadModBC(mod_bc_ipi);
   ObfModBC::UnloadModBC(tipo_calc_pis);
   ObfModBC::UnloadModBC(tipo_calc_pisst);
   ObfModBC::UnloadModBC(tipo_calc_cofins);
   ObfModBC::UnloadModBC(tipo_calc_cofinsst);
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::GetRegimeTributario()
{
   TZQuery *QyEmpresa = new TZQuery(this);
   QyEmpresa->Connection = AppConnection;
   QyEmpresa->SQL->Text = "SELECT regime_tributario FROM tbl_empresa WHERE cod_empresa = " + QuotedStr(CodEmpresa);
   QyEmpresa->Active = true;
   if (QyEmpresa->RecordCount > 0) {
      if (QyEmpresa->FieldByName("regime_tributario")->AsInteger == 1 /*Simples*/) {
         regime_tributario->ItemIndex = REGIME_SIMPLES;
      } else {
         regime_tributario->ItemIndex = REGIME_NORMAL;
      }
   } else {
      regime_tributario->ItemIndex = -1;
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::regime_tributarioChange(TObject *Sender)
{
   if (regime_tributario->ItemIndex == REGIME_SIMPLES) {
      ObfCST::LoadCSTICMS(cod_cst_icms,CST_ICMS_SIMPLES);
   } else {
      ObfCST::LoadCSTICMS(cod_cst_icms,CST_ICMS_NORMAL);
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::CarregarImpostos()
{
   String sMsgErro;
   TZQuery *QyImposto = new TZQuery(this);
   QyImposto->Connection = AppConnection;

//********************************************//
//             Carga do ICMS                  //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT cod_cst, mod_def_base_calc, perc_tributo, base_calculo, valor_tributo, \
       perc_red_base_calc, perc_marg_valor_add, valor_unit_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'ICMS'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(cod_cst_icms,QyImposto->FieldByName("cod_cst")->AsString);
      //SetIndexCombo(mod_bc_icms,QyImposto->FieldByName("mod_def_base_calc")->AsString);
      //perc_red_bc_icms->Text = FloatToStrF(QyImposto->FieldByName("perc_red_base_calc")->AsFloat,ffFixed,5,2);
      //perc_marg_add_icms->Text = FloatToStrF(QyImposto->FieldByName("perc_marg_valor_add")->AsFloat,ffFixed,5,2);
      //valor_bc_icms->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      aliquota_icms->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      valor_icms->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
      if (regime_tributario->ItemIndex == REGIME_SIMPLES) {

      }
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do ICMS:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//           Carga do ICMS ST                 //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT cod_cst, mod_def_base_calc, perc_tributo, base_calculo, valor_tributo, \
       perc_red_base_calc, perc_marg_valor_add, valor_unit_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'ICMSST'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(mod_bc_icmsst,QyImposto->FieldByName("mod_def_base_calc")->AsString);
      if (!QyImposto->FieldByName("perc_red_base_calc")->Value.IsNull())
         perc_red_bc_icmsst->Text = FloatToStrF(QyImposto->FieldByName("perc_red_base_calc")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("perc_marg_valor_add")->Value.IsNull())
         perc_marg_add_icmsst->Text = FloatToStrF(QyImposto->FieldByName("perc_marg_valor_add")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_icmsst->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_icmsst->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      valor_icmsst->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do ICMS ST:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//               Carga do IPI                 //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT cod_cst, mod_def_base_calc, perc_tributo, base_calculo, valor_tributo, \
       perc_red_base_calc, perc_marg_valor_add, valor_unit_tributo, qtd_total_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'IPI'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(cod_cst_ipi,QyImposto->FieldByName("cod_cst")->AsString);
      SetIndexCombo(mod_bc_ipi,QyImposto->FieldByName("mod_def_base_calc")->AsString);

      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_ipi->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_ipi->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("qtd_total_tributo")->Value.IsNull())
         qtd_unid_ipi->Text = FloatToStrF(QyImposto->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3);
      if (!QyImposto->FieldByName("valor_unit_tributo")->Value.IsNull())
         valor_unid_ipi->Text = FloatToStrF(QyImposto->FieldByName("valor_unit_tributo")->AsFloat,ffCurrency,15,2);
      valor_ipi->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do IPI:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//              Carga do PIS                  //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT cod_cst, mod_def_base_calc, perc_tributo, base_calculo, \
       valor_tributo, valor_unit_tributo, qtd_total_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'PIS'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(cod_cst_pis,QyImposto->FieldByName("cod_cst")->AsString);
      SetIndexCombo(tipo_calc_pis,QyImposto->FieldByName("mod_def_base_calc")->AsString);

      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_pis->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_pis_perc->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("valor_unit_tributo")->Value.IsNull())
         aliquota_pis_reais->Text = FloatToStrF(QyImposto->FieldByName("valor_unit_tributo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("qtd_total_tributo")->Value.IsNull())
         qtd_vendida_pis->Text = FloatToStrF(QyImposto->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3);
      valor_pis->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do PIS:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//             Carga do PIS ST                //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT mod_def_base_calc, perc_tributo, base_calculo, \
       valor_tributo, valor_unit_tributo, qtd_total_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'PISST'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(tipo_calc_pisst,QyImposto->FieldByName("mod_def_base_calc")->AsString);

      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_pisst->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_pisst_perc->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("valor_unit_tributo")->Value.IsNull())
         aliquota_pisst_reais->Text = FloatToStrF(QyImposto->FieldByName("valor_unit_tributo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("qtd_total_tributo")->Value.IsNull())
         qtd_vendida_pisst->Text = FloatToStrF(QyImposto->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3);
      valor_pisst->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do PIS ST:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//             Carga do COFINS                //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT cod_cst, mod_def_base_calc, perc_tributo, base_calculo, \
       valor_tributo, valor_unit_tributo, qtd_total_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'COFINS'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(cod_cst_cofins,QyImposto->FieldByName("cod_cst")->AsString);
      SetIndexCombo(tipo_calc_cofins,QyImposto->FieldByName("mod_def_base_calc")->AsString);

      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_cofins->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_cofins_perc->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("valor_unit_tributo")->Value.IsNull())
         aliquota_cofins_reais->Text = FloatToStrF(QyImposto->FieldByName("valor_unit_tributo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("qtd_total_tributo")->Value.IsNull())
         qtd_vendida_cofins->Text = FloatToStrF(QyImposto->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3);
      valor_cofins->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do cofins:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

//********************************************//
//            Carga do COFINS ST              //
//********************************************//
   QyImposto->Active = false;
   QyImposto->SQL->Text = "\
SELECT mod_def_base_calc, perc_tributo, base_calculo, \
       valor_tributo, valor_unit_tributo, qtd_total_tributo \
  FROM tbl_nota_fiscal_item_tributo \
 WHERE cod_empresa = " + QuotedStr(CodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(CodNotaFiscal) + "\
   AND seq_produto = " + IntToStr(SeqProduto) + "\
   AND cod_tributo = 'COFINSST'";
try {
   QyImposto->Active = true;
   if (QyImposto->RecordCount > 0) {
      SetIndexCombo(tipo_calc_cofinsst,QyImposto->FieldByName("mod_def_base_calc")->AsString);

      if (!QyImposto->FieldByName("base_calculo")->Value.IsNull())
         valor_bc_cofinsst->Text = FloatToStrF(QyImposto->FieldByName("base_calculo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("perc_tributo")->Value.IsNull())
         aliquota_cofinsst_perc->Text = FloatToStrF(QyImposto->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2);
      if (!QyImposto->FieldByName("valor_unit_tributo")->Value.IsNull())
         aliquota_cofinsst_reais->Text = FloatToStrF(QyImposto->FieldByName("valor_unit_tributo")->AsFloat,ffCurrency,15,2);
      if (!QyImposto->FieldByName("qtd_total_tributo")->Value.IsNull())
         qtd_vendida_cofinsst->Text = FloatToStrF(QyImposto->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3);
      valor_cofinsst->Text = FloatToStrF(QyImposto->FieldByName("valor_tributo")->AsFloat,ffCurrency,15,2);
   }
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do COFINS ST:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
}

   delete QyImposto;
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::SetIndexCombo(TComboBox *pComboBox, String sValue)
{
   TComboBoxObject *pValue = NULL;
   int iCount = pComboBox->Items->Count;

   pComboBox->ItemIndex = -1;
   for (int iIndex = 0; iIndex < iCount; iIndex++) {
      pValue = (TComboBoxObject*)pComboBox->Items->Objects[iIndex];
      if (pValue->GetValue() == sValue) {
         pComboBox->ItemIndex = iIndex;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::btOKClick(TObject *Sender)
{
   if (Editable) {
      btOK->SetFocus(); //Para forçar voltar a máscara numérica no campo
      if (!ValidarDados())
         return;
      if (!SalvarImpostos())
         return;
   }
   this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
bool __fastcall TObf1005::ValidarDados()
{
   if (cod_cst_ipi->ItemIndex < 0) {
      MessageBox(Handle,"Informe a situação tributária do ICMS.",Caption.c_str(),APP_ATENTION);
      return false;
   }
   if (cod_cst_ipi->ItemIndex < 0) {
      MessageBox(Handle,"Informe a situação tributária do IPI.",Caption.c_str(),APP_ATENTION);
      return false;
   }
   if (cod_cst_pis->ItemIndex < 0) {
      MessageBox(Handle,"Informe a situação tributária do PIS.",Caption.c_str(),APP_ATENTION);
      return false;
   }
   if (cod_cst_cofins->ItemIndex < 0) {
      MessageBox(Handle,"Informe a situação tributária do COFINS.",Caption.c_str(),APP_ATENTION);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TObf1005::SalvarImpostos()
{
   String sMsgErro;
   String sSQL;
   String sLastCST, sLastModBC;
   TZQuery *QyImposto = new TZQuery(this);
   QyImposto->Connection = AppConnection;

//********************************************//
//       Salvar Informações do ICMS           //
//********************************************//
try {
   sLastCST = ((TComboBoxObject*)cod_cst_icms->Items->Objects[cod_cst_icms->ItemIndex])->GetValue();
   sSQL = "call atualiza_imposto_item("\
          + QuotedStr(CodEmpresa) + ","\
          + IntToStr(CodNotaFiscal) + ","\
          + IntToStr(SeqProduto) + ",'ICMS',"\
          + QuotedStr(sLastCST);
   if (aliquota_icms->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_icms->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",0.0";
   }
   if (valor_icms->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_icms->Text.SubString(4,valor_icms->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",0.0";
   }
   if (regime_tributario->ItemIndex == REGIME_SIMPLES) {
      sSQL += ",NULL,NULL,NULL,NULL,NULL,NULL)";
   } else {
      //Não definido ainda
   }
   QyImposto->SQL->Text = sSQL;
   QyImposto->ExecSQL();
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao salvar as informações do ICMS:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
   return false;
}
//********************************************//
//       Salvar Informações do ICMS ST        //
//********************************************//
try {
   //Somente os CST do ICMS que permitem Substituição Tributária
   if ((sLastCST == "10") || (sLastCST == "30") || (sLastCST == "60") ||
      (sLastCST == "70") || (sLastCST == "90") || (sLastCST == "201") ||  
      (sLastCST == "202") || (sLastCST == "203")) {
      sSQL = "call atualiza_imposto_item("\
             + QuotedStr(CodEmpresa) + ","\
             + IntToStr(CodNotaFiscal) + ","\
             + IntToStr(SeqProduto) + ",'ICMSST',NULL"; // ICMS ST não tem CST
      if (aliquota_icmsst->Text.Length() > 0) {
         sSQL = sSQL + "," + StringReplace(aliquota_icmsst->Text,",",".",TReplaceFlags() << rfReplaceAll);
      } else {
         sSQL = sSQL + ",0.0";
      }
      if (valor_icmsst->Text.Length() > 0) {
         sSQL = sSQL + "," + StringReplace(valor_icmsst->Text.SubString(4,valor_icmsst->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
      } else {
         sSQL = sSQL + ",0.0";
      }
      sLastModBC = "";
      if (mod_bc_icmsst->ItemIndex >= 0)
         sLastModBC = ((TComboBoxObject*)mod_bc_icmsst->Items->Objects[mod_bc_icmsst->ItemIndex])->GetValue();
      if (sLastModBC.Length() > 0) {
         sSQL = sSQL + "," + sLastModBC;
      } else {
         sSQL = sSQL + ",NULL";
      }
      if (valor_bc_icmsst->Text.Length() > 0) {
         sSQL = sSQL + "," + StringReplace(valor_bc_icmsst->Text.SubString(4,valor_bc_icmsst->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
      } else {
         sSQL = sSQL + ",0.0";
      }
      if (perc_red_bc_icmsst->Text.Length() > 0) {
         sSQL = sSQL + "," + StringReplace(perc_red_bc_icmsst->Text,",",".",TReplaceFlags() << rfReplaceAll);
      } else {
         sSQL = sSQL + ",0.0";
      }
      if (perc_marg_add_icmsst->Text.Length() > 0) {
         sSQL = sSQL + "," + StringReplace(perc_marg_add_icmsst->Text,",",".",TReplaceFlags() << rfReplaceAll);
      } else {
         sSQL = sSQL + ",0.0";
      }
      sSQL = sSQL + ",NULL,NULL)"; //valor_unit_tributo, qtd_total_tributo
   } else { //Não existe ICMS ST - exclui
      sSQL = "call exclui_imposto_item("\
            + QuotedStr(CodEmpresa) + ","\
            + IntToStr(CodNotaFiscal) + ","\
            + IntToStr(SeqProduto) + ",'ICMSST')";
   }
   QyImposto->SQL->Text = sSQL;
   QyImposto->ExecSQL();
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao salvar as informações do ICMS ST:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
   return false;
}
//********************************************//
//         Salvar Informações do IPI          //
//********************************************//
try {
   sLastCST = ((TComboBoxObject*)cod_cst_ipi->Items->Objects[cod_cst_ipi->ItemIndex])->GetValue();
   sSQL = "call atualiza_imposto_item("\
          + QuotedStr(CodEmpresa) + ","\
          + IntToStr(CodNotaFiscal) + ","\
          + IntToStr(SeqProduto) + ",'IPI',"\
          + QuotedStr(sLastCST);
   if (aliquota_ipi->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_ipi->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_ipi->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_ipi->Text.SubString(4,valor_ipi->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",0.0";
   }
   sLastModBC = "";
   if (mod_bc_ipi->ItemIndex >= 0)
      sLastModBC = ((TComboBoxObject*)mod_bc_ipi->Items->Objects[mod_bc_ipi->ItemIndex])->GetValue();
   if (sLastModBC.Length() > 0) {
      sSQL = sSQL + "," + sLastModBC;
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_bc_ipi->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_bc_ipi->Text.SubString(4,valor_bc_ipi->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ",NULL,NULL"; //perc_red_base_calc, perc_marg_valor_add
   if (qtd_unid_ipi->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(qtd_unid_ipi->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_unid_ipi->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_unid_ipi->Text.SubString(4,valor_unid_ipi->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ")";
   QyImposto->SQL->Text = sSQL;
   QyImposto->ExecSQL();
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao salvar as informações do IPI:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
   return false;
}
//********************************************//
//         Salvar Informações do PIS          //
//********************************************//
try {
   sLastCST = ((TComboBoxObject*)cod_cst_pis->Items->Objects[cod_cst_pis->ItemIndex])->GetValue();
   sSQL = "call atualiza_imposto_item("\
          + QuotedStr(CodEmpresa) + ","\
          + IntToStr(CodNotaFiscal) + ","\
          + IntToStr(SeqProduto) + ",'PIS',"\
          + QuotedStr(sLastCST);
   if (aliquota_pis_perc->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_pis_perc->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_pis->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_pis->Text.SubString(4,valor_pis->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",0.0";
   }
   sLastModBC = "";
   if (tipo_calc_pis->ItemIndex >= 0)
      sLastModBC = ((TComboBoxObject*)tipo_calc_pis->Items->Objects[tipo_calc_pis->ItemIndex])->GetValue();
   if (sLastModBC.Length() > 0) {
      sSQL = sSQL + "," + sLastModBC;
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_bc_pis->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_bc_pis->Text.SubString(4,valor_bc_pis->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ",NULL,NULL"; //perc_red_base_calc, perc_marg_valor_add
   if (qtd_vendida_pis->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(qtd_vendida_pis->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (aliquota_pis_reais->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_pis_reais->Text.SubString(4,aliquota_pis_reais->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ")";
   QyImposto->SQL->Text = sSQL;
   QyImposto->ExecSQL();
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao salvar as informações do PIS:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
   return false;
}
//********************************************//
//         Salvar Informações do PIS          //
//********************************************//
try {
   sLastCST = ((TComboBoxObject*)cod_cst_cofins->Items->Objects[cod_cst_cofins->ItemIndex])->GetValue();
   sSQL = "call atualiza_imposto_item("\
          + QuotedStr(CodEmpresa) + ","\
          + IntToStr(CodNotaFiscal) + ","\
          + IntToStr(SeqProduto) + ",'COFINS',"\
          + QuotedStr(sLastCST);
   if (aliquota_cofins_perc->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_cofins_perc->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_cofins->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_cofins->Text.SubString(4,valor_cofins->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",0.0";
   }
   sLastModBC = "";
   if (tipo_calc_cofins->ItemIndex >= 0)
      sLastModBC = ((TComboBoxObject*)tipo_calc_cofins->Items->Objects[tipo_calc_cofins->ItemIndex])->GetValue();
   if (sLastModBC.Length() > 0) {
      sSQL = sSQL + "," + sLastModBC;
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (valor_bc_cofins->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(valor_bc_cofins->Text.SubString(4,valor_bc_cofins->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ",NULL,NULL"; //perc_red_base_calc, perc_marg_valor_add
   if (qtd_vendida_cofins->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(qtd_vendida_cofins->Text,",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   if (aliquota_cofins_reais->Text.Length() > 0) {
      sSQL = sSQL + "," + StringReplace(aliquota_cofins_reais->Text.SubString(4,aliquota_cofins_reais->Text.Length()-3),",",".",TReplaceFlags() << rfReplaceAll);
   } else {
      sSQL = sSQL + ",NULL";
   }
   sSQL = sSQL + ")";
   QyImposto->SQL->Text = sSQL;
   QyImposto->ExecSQL();
} catch (Exception &e) {
   sMsgErro = "Ocorreu o seguinte erro ao salvar as informações do PIS:\n" + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_ERROR);
   return false;
}
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1005::EditKeyPress(TObject *Sender, char &Key)
{
   Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------

