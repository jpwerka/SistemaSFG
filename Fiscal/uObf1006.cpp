/*
Módulo: Fiscal
Função: Opções para CSTs e Base Cálculo de Impostos
Autor.: Jackson Patrick Werka
Data..: 13/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "CustomDbControls.h"
#pragma hdrstop
#include "uObf1006.h"
//--------------------------------------------------------------------------
#pragma package(smart_init)
//--------------------------------------------------------------------------
void LoadComboValue(TCustomComboBox *pComboBox, String sText, String sValue, bool bIsDB)
{
   if (bIsDB) {
      TBDDataObject *pValue = new TBDDataObject();
      pValue->SetValue(sValue);
      pComboBox->AddItem(sText,(TObject*)pValue);
   } else {
      TComboBoxObject *pValue = new TComboBoxObject();
      pValue->SetValue(sValue);
      pComboBox->AddItem(sText,(TObject*)pValue);
   }
}
//--------------------------------------------------------------------------
void UnloadComboValue(TCustomComboBox *pComboBox, bool bIsDB)
{
   int iCount = pComboBox->Items->Count;
   TBDDataObject *pDbObj = NULL;
   TComboBoxObject *pCbObj = NULL;

   for (int i = 0; i < iCount; i++) {
      if (bIsDB) {
         pDbObj = (TBDDataObject*)pComboBox->Items->Objects[i];
         if (pDbObj != NULL) delete pDbObj;
      } else {
         pCbObj = (TComboBoxObject*)pComboBox->Items->Objects[i];
         if (pCbObj != NULL) delete pCbObj;
      }
   }
   pComboBox->Clear();
}
//--------------------------------------------------------------------------
namespace ObfCST
{
//--------------------------------------------------------------------------
void LoadCSTICMS(TCustomComboBox *pComboBox, int iLoadOption)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   if (iLoadOption == CST_ICMS_AMBOS || iLoadOption == CST_ICMS_NORMAL) {
      LoadComboValue(pComboBox,"00 - Tributada integralmente"                                 ,"00",bIsDB);
      LoadComboValue(pComboBox,"10 - Tributada e com cobrança do ICMS por ST"                 ,"10",bIsDB);
      LoadComboValue(pComboBox,"20 - Com redução de base de cálculo"                          ,"20",bIsDB);
      LoadComboValue(pComboBox,"30 - Isenta ou não tributada e com cobrança do ICMS por ST"   ,"30",bIsDB);
      LoadComboValue(pComboBox,"40 - Isenta"                                                  ,"40",bIsDB);
      LoadComboValue(pComboBox,"41 - Não tributada"                                           ,"41",bIsDB);
      LoadComboValue(pComboBox,"50 - Suspensão"                                               ,"50",bIsDB);
      LoadComboValue(pComboBox,"51 - Diferimento"                                             ,"51",bIsDB);
      LoadComboValue(pComboBox,"60 - ICMS cobrado anteriormente por ST"                       ,"60",bIsDB);
      LoadComboValue(pComboBox,"70 - Com redução de base de cálculo e cobrança do ICMS por ST","70",bIsDB);
      LoadComboValue(pComboBox,"90 - Outros"                                                  ,"90",bIsDB);
   }
   if (iLoadOption == CST_ICMS_AMBOS || iLoadOption == CST_ICMS_SIMPLES) {
      LoadComboValue(pComboBox,"101 - Tributada pelo Simples Nacional com permissão de crédito"                                     ,"101",bIsDB);
      LoadComboValue(pComboBox,"102 - Tributada pelo Simples Nacional sem permissão de crédito"                                     ,"102",bIsDB);
      LoadComboValue(pComboBox,"103 - Isenção do ICMS no Simples Nacional para faixa de receita bruta"                              ,"103",bIsDB);
      LoadComboValue(pComboBox,"201 - Tributada pelo Simples Nacional com permissão de crédito e com cobrança do ICMS por ST"       ,"201",bIsDB);
      LoadComboValue(pComboBox,"202 - Tributada pelo Simples Nacional sem permissão de crédito e com cobrança do ICMS por ST"       ,"202",bIsDB);
      LoadComboValue(pComboBox,"203 - Isenção do ICMS no Simples Nacional para faixa de receita bruta e com cobrança do ICMS por ST","203",bIsDB);
      LoadComboValue(pComboBox,"300 - Imune"                                                                                        ,"300",bIsDB);
      LoadComboValue(pComboBox,"400 - Não tributada pelo Simples Nacional"                                                          ,"400",bIsDB);
      LoadComboValue(pComboBox,"500 - ICMS cobrado anteriormente por ST ou por antecipação"                                         ,"500",bIsDB);
      LoadComboValue(pComboBox,"900 - Outros"                                                                                       ,"900",bIsDB);
   }   
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTIPI(TCustomComboBox *pComboBox, int iLoadOption)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   if (iLoadOption == CST_IPI_ENTRADA || iLoadOption == CST_IPI_AMBOS) {
      LoadComboValue(pComboBox,"00 - Entrada com Recuperação de Crédito"  ,"00",bIsDB);
      LoadComboValue(pComboBox,"01 - Entrada Tributável com Alíquota Zero","01",bIsDB);
      LoadComboValue(pComboBox,"02 - Entrada Isenta"                      ,"02",bIsDB);
      LoadComboValue(pComboBox,"03 - Entrada Não-Tributada"               ,"03",bIsDB);
      LoadComboValue(pComboBox,"04 - Entrada Imune"                       ,"04",bIsDB);
      LoadComboValue(pComboBox,"05 - Entrada com Suspensão"               ,"05",bIsDB);
      LoadComboValue(pComboBox,"49 - Outras Entradas"                     ,"49",bIsDB);
   }
   if (iLoadOption == CST_IPI_SAIDA || iLoadOption == CST_IPI_AMBOS) {
      LoadComboValue(pComboBox,"50 - Saída Tributada"                     ,"50",bIsDB);
      LoadComboValue(pComboBox,"51 - Saída Tributável com Alíquota Zero"  ,"51",bIsDB);
      LoadComboValue(pComboBox,"52 - Saida Isenta"                        ,"52",bIsDB);
      LoadComboValue(pComboBox,"53 - Saída Não-Tributada"                 ,"53",bIsDB);
      LoadComboValue(pComboBox,"54 - Saída Imune"                         ,"54",bIsDB);
      LoadComboValue(pComboBox,"55 - Saída com Suspensão"                 ,"55",bIsDB);
      LoadComboValue(pComboBox,"99 - Outras Saídas"                       ,"99",bIsDB);
   }
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTPIS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   LoadComboValue(pComboBox,"01 - Operação Tributável com Alíquota Básica"                                                                                       ,"01",bIsDB);
   LoadComboValue(pComboBox,"02 - Operação Tributável com Alíquota Diferenciada"                                                                                 ,"02",bIsDB);
   LoadComboValue(pComboBox,"03 - Operação Tributável com Alíquota por Unidade de Medida de Produto"                                                             ,"03",bIsDB);
   LoadComboValue(pComboBox,"04 - Operação Tributável Monofásica - Revenda a Alíquota Zero"                                                                      ,"04",bIsDB);
   LoadComboValue(pComboBox,"05 - Operação Tributável por Substituição Tributária"                                                                               ,"05",bIsDB);
   LoadComboValue(pComboBox,"06 - Operação Tributável a Alíquota Zero"                                                                                           ,"06",bIsDB);
   LoadComboValue(pComboBox,"07 - Operação Isenta da Contribuição"                                                                                               ,"07",bIsDB);
   LoadComboValue(pComboBox,"08 - Operação sem Incidência da Contribuição"                                                                                       ,"08",bIsDB);
   LoadComboValue(pComboBox,"09 - Operação com Suspensão da Contribuição"                                                                                        ,"09",bIsDB);
   LoadComboValue(pComboBox,"49 - Outras Operações de Saída"                                                                                                     ,"49",bIsDB);
   LoadComboValue(pComboBox,"50 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                              ,"50",bIsDB);
   LoadComboValue(pComboBox,"51 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita Não Tributada no Mercado Interno"                          ,"51",bIsDB);
   LoadComboValue(pComboBox,"52 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita de Exportação"                                             ,"52",bIsDB);
   LoadComboValue(pComboBox,"53 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno"                          ,"53",bIsDB);
   LoadComboValue(pComboBox,"54 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas no Mercado Interno e de Exportação"                           ,"54",bIsDB);
   LoadComboValue(pComboBox,"55 - Operação com Direito a Crédito - Vinculada a Receitas Não-Tributadas no Mercado Interno e de Exportação"                       ,"55",bIsDB);
   LoadComboValue(pComboBox,"56 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno, e de Exportação"         ,"56",bIsDB);
   LoadComboValue(pComboBox,"60 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                     ,"60",bIsDB);
   LoadComboValue(pComboBox,"61 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita Não-Tributada no Mercado Interno"                 ,"61",bIsDB);
   LoadComboValue(pComboBox,"62 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita de Exportação"                                    ,"62",bIsDB);
   LoadComboValue(pComboBox,"63 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno"                 ,"63",bIsDB);
   LoadComboValue(pComboBox,"64 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas no Mercado Interno e de Exportação"                  ,"64",bIsDB);
   LoadComboValue(pComboBox,"65 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Não-Tributadas no Mercado Interno e de Exportação"              ,"65",bIsDB);
   LoadComboValue(pComboBox,"66 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno, e de Exportação","66",bIsDB);
   LoadComboValue(pComboBox,"67 - Crédito Presumido - Outras Operações"                                                                                          ,"67",bIsDB);
   LoadComboValue(pComboBox,"70 - Operação de Aquisição sem Direito a Crédito"                                                                                   ,"70",bIsDB);
   LoadComboValue(pComboBox,"71 - Operação de Aquisição com Isenção"                                                                                             ,"71",bIsDB);
   LoadComboValue(pComboBox,"72 - Operação de Aquisição com Suspensão"                                                                                           ,"72",bIsDB);
   LoadComboValue(pComboBox,"73 - Operação de Aquisição a Alíquota Zero"                                                                                         ,"73",bIsDB);
   LoadComboValue(pComboBox,"74 - Operação de Aquisição sem Incidência da Contribuição"                                                                          ,"74",bIsDB);
   LoadComboValue(pComboBox,"75 - Operação de Aquisição por Substituição Tributária"                                                                             ,"75",bIsDB);
   LoadComboValue(pComboBox,"98 - Outras Operações de Entrada"                                                                                                   ,"98",bIsDB);
   LoadComboValue(pComboBox,"99 - Outras Operações"                                                                                                              ,"99",bIsDB);
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTCOFINS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   LoadComboValue(pComboBox,"01 - Operação Tributável com Alíquota Básica"                                                                                       ,"01",bIsDB);
   LoadComboValue(pComboBox,"02 - Operação Tributável com Alíquota Diferenciada"                                                                                 ,"02",bIsDB);
   LoadComboValue(pComboBox,"03 - Operação Tributável com Alíquota por Unidade de Medida de Produto"                                                             ,"03",bIsDB);
   LoadComboValue(pComboBox,"04 - Operação Tributável Monofásica - Revenda a Alíquota Zero"                                                                      ,"04",bIsDB);
   LoadComboValue(pComboBox,"05 - Operação Tributável por Substituição Tributária"                                                                               ,"05",bIsDB);
   LoadComboValue(pComboBox,"06 - Operação Tributável a Alíquota Zero"                                                                                           ,"06",bIsDB);
   LoadComboValue(pComboBox,"07 - Operação Isenta da Contribuição"                                                                                               ,"07",bIsDB);
   LoadComboValue(pComboBox,"08 - Operação sem Incidência da Contribuição"                                                                                       ,"08",bIsDB);
   LoadComboValue(pComboBox,"09 - Operação com Suspensão da Contribuição"                                                                                        ,"09",bIsDB);
   LoadComboValue(pComboBox,"49 - Outras Operações de Saída"                                                                                                     ,"49",bIsDB);
   LoadComboValue(pComboBox,"50 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                              ,"50",bIsDB);
   LoadComboValue(pComboBox,"51 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita Não Tributada no Mercado Interno"                          ,"51",bIsDB);
   LoadComboValue(pComboBox,"52 - Operação com Direito a Crédito - Vinculada Exclusivamente a Receita de Exportação"                                             ,"52",bIsDB);
   LoadComboValue(pComboBox,"53 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno"                          ,"53",bIsDB);
   LoadComboValue(pComboBox,"54 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas no Mercado Interno e de Exportação"                           ,"54",bIsDB);
   LoadComboValue(pComboBox,"55 - Operação com Direito a Crédito - Vinculada a Receitas Não-Tributadas no Mercado Interno e de Exportação"                       ,"55",bIsDB);
   LoadComboValue(pComboBox,"56 - Operação com Direito a Crédito - Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno, e de Exportação"         ,"56",bIsDB);
   LoadComboValue(pComboBox,"60 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                     ,"60",bIsDB);
   LoadComboValue(pComboBox,"61 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita Não-Tributada no Mercado Interno"                 ,"61",bIsDB);
   LoadComboValue(pComboBox,"62 - Crédito Presumido - Operação de Aquisição Vinculada Exclusivamente a Receita de Exportação"                                    ,"62",bIsDB);
   LoadComboValue(pComboBox,"63 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno"                 ,"63",bIsDB);
   LoadComboValue(pComboBox,"64 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas no Mercado Interno e de Exportação"                  ,"64",bIsDB);
   LoadComboValue(pComboBox,"65 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Não-Tributadas no Mercado Interno e de Exportação"              ,"65",bIsDB);
   LoadComboValue(pComboBox,"66 - Crédito Presumido - Operação de Aquisição Vinculada a Receitas Tributadas e Não-Tributadas no Mercado Interno, e de Exportação","66",bIsDB);
   LoadComboValue(pComboBox,"67 - Crédito Presumido - Outras Operações"                                                                                          ,"67",bIsDB);
   LoadComboValue(pComboBox,"70 - Operação de Aquisição sem Direito a Crédito"                                                                                   ,"70",bIsDB);
   LoadComboValue(pComboBox,"71 - Operação de Aquisição com Isenção"                                                                                             ,"71",bIsDB);
   LoadComboValue(pComboBox,"72 - Operação de Aquisição com Suspensão"                                                                                           ,"72",bIsDB);
   LoadComboValue(pComboBox,"73 - Operação de Aquisição a Alíquota Zero"                                                                                         ,"73",bIsDB);
   LoadComboValue(pComboBox,"74 - Operação de Aquisição sem Incidência da Contribuição"                                                                          ,"74",bIsDB);
   LoadComboValue(pComboBox,"75 - Operação de Aquisição por Substituição Tributária"                                                                             ,"75",bIsDB);
   LoadComboValue(pComboBox,"98 - Outras Operações de Entrada"                                                                                                   ,"98",bIsDB);
   LoadComboValue(pComboBox,"99 - Outras Operações"                                                                                                              ,"99",bIsDB);
}
//--------------------------------------------------------------------------
void UnloadCST(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   UnloadComboValue(pComboBox,bIsDB);
}
//--------------------------------------------------------------------------
} //end namespace ObfCST
namespace ObfModBC
{
//--------------------------------------------------------------------------
void LoadModBCICMS(TCustomComboBox *pComboBox, int iLoadOption)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");

   UnloadModBC(pComboBox);
   if (iLoadOption == BASE_CALC_ICMS) {
      LoadComboValue(pComboBox,"0 - Margem Valor Agregado (%)"     ,"0",bIsDB);
      LoadComboValue(pComboBox,"1 - Pauta (valor)"                 ,"1",bIsDB);
      LoadComboValue(pComboBox,"2 - Preço Tabelado Máximo (valor)" ,"2",bIsDB);
      LoadComboValue(pComboBox,"3 - Valor da Operação"             ,"3",bIsDB);
   }
   if (iLoadOption == BASE_CALC_ICMS_ST) {
      LoadComboValue(pComboBox,"0 - Preço Tabelado ou Máximo Sugerido","0",bIsDB);
      LoadComboValue(pComboBox,"1 - Lista Negativa (valor)"           ,"1",bIsDB);
      LoadComboValue(pComboBox,"2 - Lista Positiva (valor)"           ,"2",bIsDB);
      LoadComboValue(pComboBox,"3 - Lista Neutra (valor)"             ,"3",bIsDB);
      LoadComboValue(pComboBox,"4 - Margem Valor Agregado (%)"        ,"4",bIsDB);
      LoadComboValue(pComboBox,"5 - Pauta (valor)"                    ,"5",bIsDB);
   }
}
//--------------------------------------------------------------------------
void LoadModBCIPI(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");

   UnloadModBC(pComboBox);
   LoadComboValue(pComboBox,"Percentual","0",bIsDB);
   LoadComboValue(pComboBox,"Em Valor"  ,"1",bIsDB);
}
//--------------------------------------------------------------------------
void LoadModBCPIS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");

   UnloadModBC(pComboBox);
   LoadComboValue(pComboBox,"Percentual","0",bIsDB);
   LoadComboValue(pComboBox,"Em Valor"  ,"1",bIsDB);
}
//--------------------------------------------------------------------------
void LoadModBCCOFINS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");

   UnloadModBC(pComboBox);
   LoadComboValue(pComboBox,"Percentual","0",bIsDB);
   LoadComboValue(pComboBox,"Em Valor"  ,"1",bIsDB);
}
//--------------------------------------------------------------------------
void UnloadModBC(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   UnloadComboValue(pComboBox,bIsDB);
}
//--------------------------------------------------------------------------
} //end namespace ObfModBC
