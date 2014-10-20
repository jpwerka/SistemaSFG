//---------------------------------------------------------------------------
#ifndef uSfgToolsH
#define uSfgToolsH
//---------------------------------------------------------------------------
#include <system.hpp>
#include <ExtCtrls.hpp>
#include "ZConnection.hpp"
#include "ZDataset.hpp"
//---------------------------------------------------------------------------
extern PACKAGE char *EncryptText(char *Source);
extern PACKAGE char *DecryptText(char *Source);
extern PACKAGE void AddAppForm(String FormClass, String FormTitle, const int FormModule = 0);
extern PACKAGE void AddAppFormClass(String FormClass, System::TMetaClass* AClass);
extern PACKAGE System::TMetaClass* GetAppFormClass(String FormClass);
extern PACKAGE void AssignImage(TImage *Origem, TImage *Destino);

//Validacoes
namespace Validacoes {
   extern PACKAGE bool BackSpace(char &C);
   extern PACKAGE void CharIsInteger(char &C);
   extern PACKAGE void CharIsFloat(char &C);
   extern PACKAGE bool IsInteger(String StrInteger);
   extern PACKAGE bool IsFloat(String StrFloat);
   extern PACKAGE bool IsDate(String StrDate);
   extern PACKAGE bool IsTime(String StrTime);
   extern PACKAGE void ValidarFloat(String Valor, char &C);
   extern PACKAGE bool ValidarCPFCNPJ(String Valor);
   extern PACKAGE bool ValidarCPF(String Valor);
   extern PACKAGE bool ValidarCNPJ(String Valor);
};
namespace ValidacoesDB {
	extern PACKAGE bool ExistePrimaryKey(TZConnection *pConexao, String sSQL);
	extern PACKAGE bool ExisteForeingKey(TZConnection *pConexao, String sSQL);
	extern PACKAGE String GetDenominacaoByKey(TZConnection *pConexao, String sSQL);
   extern PACKAGE Variant GetParamValue(TZConnection *pConexao, String sSQL);
   extern PACKAGE bool SetParamValue(TZConnection *pConexao, String sSQL);
   extern PACKAGE bool GetProxCod(TZConnection *pConexao, String Param, String &RetCod);
};
#endif
