/*
M�dulo: Fiscal
Fun��o: Op��es para CSTs e Base C�lculo de Impostos
Autor.: Jackson Patrick Werka
Data..: 13/12/2012
� Copyright 2012-2012 SoftGreen - All Rights Reserved
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
      LoadComboValue(pComboBox,"10 - Tributada e com cobran�a do ICMS por ST"                 ,"10",bIsDB);
      LoadComboValue(pComboBox,"20 - Com redu��o de base de c�lculo"                          ,"20",bIsDB);
      LoadComboValue(pComboBox,"30 - Isenta ou n�o tributada e com cobran�a do ICMS por ST"   ,"30",bIsDB);
      LoadComboValue(pComboBox,"40 - Isenta"                                                  ,"40",bIsDB);
      LoadComboValue(pComboBox,"41 - N�o tributada"                                           ,"41",bIsDB);
      LoadComboValue(pComboBox,"50 - Suspens�o"                                               ,"50",bIsDB);
      LoadComboValue(pComboBox,"51 - Diferimento"                                             ,"51",bIsDB);
      LoadComboValue(pComboBox,"60 - ICMS cobrado anteriormente por ST"                       ,"60",bIsDB);
      LoadComboValue(pComboBox,"70 - Com redu��o de base de c�lculo e cobran�a do ICMS por ST","70",bIsDB);
      LoadComboValue(pComboBox,"90 - Outros"                                                  ,"90",bIsDB);
   }
   if (iLoadOption == CST_ICMS_AMBOS || iLoadOption == CST_ICMS_SIMPLES) {
      LoadComboValue(pComboBox,"101 - Tributada pelo Simples Nacional com permiss�o de cr�dito"                                     ,"101",bIsDB);
      LoadComboValue(pComboBox,"102 - Tributada pelo Simples Nacional sem permiss�o de cr�dito"                                     ,"102",bIsDB);
      LoadComboValue(pComboBox,"103 - Isen��o do ICMS no Simples Nacional para faixa de receita bruta"                              ,"103",bIsDB);
      LoadComboValue(pComboBox,"201 - Tributada pelo Simples Nacional com permiss�o de cr�dito e com cobran�a do ICMS por ST"       ,"201",bIsDB);
      LoadComboValue(pComboBox,"202 - Tributada pelo Simples Nacional sem permiss�o de cr�dito e com cobran�a do ICMS por ST"       ,"202",bIsDB);
      LoadComboValue(pComboBox,"203 - Isen��o do ICMS no Simples Nacional para faixa de receita bruta e com cobran�a do ICMS por ST","203",bIsDB);
      LoadComboValue(pComboBox,"300 - Imune"                                                                                        ,"300",bIsDB);
      LoadComboValue(pComboBox,"400 - N�o tributada pelo Simples Nacional"                                                          ,"400",bIsDB);
      LoadComboValue(pComboBox,"500 - ICMS cobrado anteriormente por ST ou por antecipa��o"                                         ,"500",bIsDB);
      LoadComboValue(pComboBox,"900 - Outros"                                                                                       ,"900",bIsDB);
   }   
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTIPI(TCustomComboBox *pComboBox, int iLoadOption)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   if (iLoadOption == CST_IPI_ENTRADA || iLoadOption == CST_IPI_AMBOS) {
      LoadComboValue(pComboBox,"00 - Entrada com Recupera��o de Cr�dito"  ,"00",bIsDB);
      LoadComboValue(pComboBox,"01 - Entrada Tribut�vel com Al�quota Zero","01",bIsDB);
      LoadComboValue(pComboBox,"02 - Entrada Isenta"                      ,"02",bIsDB);
      LoadComboValue(pComboBox,"03 - Entrada N�o-Tributada"               ,"03",bIsDB);
      LoadComboValue(pComboBox,"04 - Entrada Imune"                       ,"04",bIsDB);
      LoadComboValue(pComboBox,"05 - Entrada com Suspens�o"               ,"05",bIsDB);
      LoadComboValue(pComboBox,"49 - Outras Entradas"                     ,"49",bIsDB);
   }
   if (iLoadOption == CST_IPI_SAIDA || iLoadOption == CST_IPI_AMBOS) {
      LoadComboValue(pComboBox,"50 - Sa�da Tributada"                     ,"50",bIsDB);
      LoadComboValue(pComboBox,"51 - Sa�da Tribut�vel com Al�quota Zero"  ,"51",bIsDB);
      LoadComboValue(pComboBox,"52 - Saida Isenta"                        ,"52",bIsDB);
      LoadComboValue(pComboBox,"53 - Sa�da N�o-Tributada"                 ,"53",bIsDB);
      LoadComboValue(pComboBox,"54 - Sa�da Imune"                         ,"54",bIsDB);
      LoadComboValue(pComboBox,"55 - Sa�da com Suspens�o"                 ,"55",bIsDB);
      LoadComboValue(pComboBox,"99 - Outras Sa�das"                       ,"99",bIsDB);
   }
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTPIS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   LoadComboValue(pComboBox,"01 - Opera��o Tribut�vel com Al�quota B�sica"                                                                                       ,"01",bIsDB);
   LoadComboValue(pComboBox,"02 - Opera��o Tribut�vel com Al�quota Diferenciada"                                                                                 ,"02",bIsDB);
   LoadComboValue(pComboBox,"03 - Opera��o Tribut�vel com Al�quota por Unidade de Medida de Produto"                                                             ,"03",bIsDB);
   LoadComboValue(pComboBox,"04 - Opera��o Tribut�vel Monof�sica - Revenda a Al�quota Zero"                                                                      ,"04",bIsDB);
   LoadComboValue(pComboBox,"05 - Opera��o Tribut�vel por Substitui��o Tribut�ria"                                                                               ,"05",bIsDB);
   LoadComboValue(pComboBox,"06 - Opera��o Tribut�vel a Al�quota Zero"                                                                                           ,"06",bIsDB);
   LoadComboValue(pComboBox,"07 - Opera��o Isenta da Contribui��o"                                                                                               ,"07",bIsDB);
   LoadComboValue(pComboBox,"08 - Opera��o sem Incid�ncia da Contribui��o"                                                                                       ,"08",bIsDB);
   LoadComboValue(pComboBox,"09 - Opera��o com Suspens�o da Contribui��o"                                                                                        ,"09",bIsDB);
   LoadComboValue(pComboBox,"49 - Outras Opera��es de Sa�da"                                                                                                     ,"49",bIsDB);
   LoadComboValue(pComboBox,"50 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                              ,"50",bIsDB);
   LoadComboValue(pComboBox,"51 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita N�o Tributada no Mercado Interno"                          ,"51",bIsDB);
   LoadComboValue(pComboBox,"52 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita de Exporta��o"                                             ,"52",bIsDB);
   LoadComboValue(pComboBox,"53 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno"                          ,"53",bIsDB);
   LoadComboValue(pComboBox,"54 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas no Mercado Interno e de Exporta��o"                           ,"54",bIsDB);
   LoadComboValue(pComboBox,"55 - Opera��o com Direito a Cr�dito - Vinculada a Receitas N�o-Tributadas no Mercado Interno e de Exporta��o"                       ,"55",bIsDB);
   LoadComboValue(pComboBox,"56 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno, e de Exporta��o"         ,"56",bIsDB);
   LoadComboValue(pComboBox,"60 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                     ,"60",bIsDB);
   LoadComboValue(pComboBox,"61 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita N�o-Tributada no Mercado Interno"                 ,"61",bIsDB);
   LoadComboValue(pComboBox,"62 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita de Exporta��o"                                    ,"62",bIsDB);
   LoadComboValue(pComboBox,"63 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno"                 ,"63",bIsDB);
   LoadComboValue(pComboBox,"64 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas no Mercado Interno e de Exporta��o"                  ,"64",bIsDB);
   LoadComboValue(pComboBox,"65 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas N�o-Tributadas no Mercado Interno e de Exporta��o"              ,"65",bIsDB);
   LoadComboValue(pComboBox,"66 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno, e de Exporta��o","66",bIsDB);
   LoadComboValue(pComboBox,"67 - Cr�dito Presumido - Outras Opera��es"                                                                                          ,"67",bIsDB);
   LoadComboValue(pComboBox,"70 - Opera��o de Aquisi��o sem Direito a Cr�dito"                                                                                   ,"70",bIsDB);
   LoadComboValue(pComboBox,"71 - Opera��o de Aquisi��o com Isen��o"                                                                                             ,"71",bIsDB);
   LoadComboValue(pComboBox,"72 - Opera��o de Aquisi��o com Suspens�o"                                                                                           ,"72",bIsDB);
   LoadComboValue(pComboBox,"73 - Opera��o de Aquisi��o a Al�quota Zero"                                                                                         ,"73",bIsDB);
   LoadComboValue(pComboBox,"74 - Opera��o de Aquisi��o sem Incid�ncia da Contribui��o"                                                                          ,"74",bIsDB);
   LoadComboValue(pComboBox,"75 - Opera��o de Aquisi��o por Substitui��o Tribut�ria"                                                                             ,"75",bIsDB);
   LoadComboValue(pComboBox,"98 - Outras Opera��es de Entrada"                                                                                                   ,"98",bIsDB);
   LoadComboValue(pComboBox,"99 - Outras Opera��es"                                                                                                              ,"99",bIsDB);
}
//--------------------------------------------------------------------------
extern PACKAGE void LoadCSTCOFINS(TCustomComboBox *pComboBox)
{
   bool bIsDB = pComboBox->ClassNameIs("TDBDataComboBox");
   
   UnloadCST(pComboBox);
   LoadComboValue(pComboBox,"01 - Opera��o Tribut�vel com Al�quota B�sica"                                                                                       ,"01",bIsDB);
   LoadComboValue(pComboBox,"02 - Opera��o Tribut�vel com Al�quota Diferenciada"                                                                                 ,"02",bIsDB);
   LoadComboValue(pComboBox,"03 - Opera��o Tribut�vel com Al�quota por Unidade de Medida de Produto"                                                             ,"03",bIsDB);
   LoadComboValue(pComboBox,"04 - Opera��o Tribut�vel Monof�sica - Revenda a Al�quota Zero"                                                                      ,"04",bIsDB);
   LoadComboValue(pComboBox,"05 - Opera��o Tribut�vel por Substitui��o Tribut�ria"                                                                               ,"05",bIsDB);
   LoadComboValue(pComboBox,"06 - Opera��o Tribut�vel a Al�quota Zero"                                                                                           ,"06",bIsDB);
   LoadComboValue(pComboBox,"07 - Opera��o Isenta da Contribui��o"                                                                                               ,"07",bIsDB);
   LoadComboValue(pComboBox,"08 - Opera��o sem Incid�ncia da Contribui��o"                                                                                       ,"08",bIsDB);
   LoadComboValue(pComboBox,"09 - Opera��o com Suspens�o da Contribui��o"                                                                                        ,"09",bIsDB);
   LoadComboValue(pComboBox,"49 - Outras Opera��es de Sa�da"                                                                                                     ,"49",bIsDB);
   LoadComboValue(pComboBox,"50 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                              ,"50",bIsDB);
   LoadComboValue(pComboBox,"51 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita N�o Tributada no Mercado Interno"                          ,"51",bIsDB);
   LoadComboValue(pComboBox,"52 - Opera��o com Direito a Cr�dito - Vinculada Exclusivamente a Receita de Exporta��o"                                             ,"52",bIsDB);
   LoadComboValue(pComboBox,"53 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno"                          ,"53",bIsDB);
   LoadComboValue(pComboBox,"54 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas no Mercado Interno e de Exporta��o"                           ,"54",bIsDB);
   LoadComboValue(pComboBox,"55 - Opera��o com Direito a Cr�dito - Vinculada a Receitas N�o-Tributadas no Mercado Interno e de Exporta��o"                       ,"55",bIsDB);
   LoadComboValue(pComboBox,"56 - Opera��o com Direito a Cr�dito - Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno, e de Exporta��o"         ,"56",bIsDB);
   LoadComboValue(pComboBox,"60 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita Tributada no Mercado Interno"                     ,"60",bIsDB);
   LoadComboValue(pComboBox,"61 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita N�o-Tributada no Mercado Interno"                 ,"61",bIsDB);
   LoadComboValue(pComboBox,"62 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada Exclusivamente a Receita de Exporta��o"                                    ,"62",bIsDB);
   LoadComboValue(pComboBox,"63 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno"                 ,"63",bIsDB);
   LoadComboValue(pComboBox,"64 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas no Mercado Interno e de Exporta��o"                  ,"64",bIsDB);
   LoadComboValue(pComboBox,"65 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas N�o-Tributadas no Mercado Interno e de Exporta��o"              ,"65",bIsDB);
   LoadComboValue(pComboBox,"66 - Cr�dito Presumido - Opera��o de Aquisi��o Vinculada a Receitas Tributadas e N�o-Tributadas no Mercado Interno, e de Exporta��o","66",bIsDB);
   LoadComboValue(pComboBox,"67 - Cr�dito Presumido - Outras Opera��es"                                                                                          ,"67",bIsDB);
   LoadComboValue(pComboBox,"70 - Opera��o de Aquisi��o sem Direito a Cr�dito"                                                                                   ,"70",bIsDB);
   LoadComboValue(pComboBox,"71 - Opera��o de Aquisi��o com Isen��o"                                                                                             ,"71",bIsDB);
   LoadComboValue(pComboBox,"72 - Opera��o de Aquisi��o com Suspens�o"                                                                                           ,"72",bIsDB);
   LoadComboValue(pComboBox,"73 - Opera��o de Aquisi��o a Al�quota Zero"                                                                                         ,"73",bIsDB);
   LoadComboValue(pComboBox,"74 - Opera��o de Aquisi��o sem Incid�ncia da Contribui��o"                                                                          ,"74",bIsDB);
   LoadComboValue(pComboBox,"75 - Opera��o de Aquisi��o por Substitui��o Tribut�ria"                                                                             ,"75",bIsDB);
   LoadComboValue(pComboBox,"98 - Outras Opera��es de Entrada"                                                                                                   ,"98",bIsDB);
   LoadComboValue(pComboBox,"99 - Outras Opera��es"                                                                                                              ,"99",bIsDB);
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
      LoadComboValue(pComboBox,"2 - Pre�o Tabelado M�ximo (valor)" ,"2",bIsDB);
      LoadComboValue(pComboBox,"3 - Valor da Opera��o"             ,"3",bIsDB);
   }
   if (iLoadOption == BASE_CALC_ICMS_ST) {
      LoadComboValue(pComboBox,"0 - Pre�o Tabelado ou M�ximo Sugerido","0",bIsDB);
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
