/*
Módulo: Fiscal
Função: Opções para CSTs e Base Cálculo de Impostos
Autor.: Jackson Patrick Werka
Data..: 13/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uObf1006H
#define uObf1006H
//---------------------------------------------------------------------------
#define CST_ICMS_AMBOS    0
#define CST_ICMS_SIMPLES  1
#define CST_ICMS_NORMAL   2
#define CST_IPI_AMBOS     0
#define CST_IPI_ENTRADA   1
#define CST_IPI_SAIDA     2
#define BASE_CALC_ICMS    1
#define BASE_CALC_ICMS_ST 2
//---------------------------------------------------------------------------
struct TComboBoxObject {
protected:
	String Value;
public:
	String GetValue() {
		return Value;
	}
	void SetValue(String sValue) {
		Value = sValue;
	}
};
//---------------------------------------------------------------------------
namespace ObfCST
{
extern PACKAGE void LoadCSTICMS(TCustomComboBox *pComboBox, int iLoadOption);
extern PACKAGE void LoadCSTIPI(TCustomComboBox *pComboBox, int iLoadOption);
extern PACKAGE void LoadCSTPIS(TCustomComboBox *pComboBox);
extern PACKAGE void LoadCSTCOFINS(TCustomComboBox *pComboBox);
extern PACKAGE void UnloadCST(TCustomComboBox *pComboBox);
};
namespace ObfModBC
{
extern PACKAGE void LoadModBCICMS(TCustomComboBox *pComboBox, int iLoadOption);
extern PACKAGE void LoadModBCIPI(TCustomComboBox *pComboBox);
extern PACKAGE void LoadModBCPIS(TCustomComboBox *pComboBox);
extern PACKAGE void LoadModBCCOFINS(TCustomComboBox *pComboBox);
extern PACKAGE void UnloadModBC(TCustomComboBox *pComboBox);
};
#endif
