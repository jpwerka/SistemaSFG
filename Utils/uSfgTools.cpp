//---------------------------------------------------------------------------
#include <ctype.h>
#include <vcl.h>
#include "uSfgGlobals.h"
#pragma hdrstop
#include "uSfgTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
//Encripta a senha digitada
char *EncryptText(char *Source)
{
  char *Dest;
  int I,L;
  unsigned char A;
  L = strlen(Source);
  Dest = new char[L+1];

  for(I = 0; I < L; I++) {
		A = (int)Source[L - I - 1];
	  Dest[I] = (char)((270 + I) - (int)A);
  }

  Dest[L] = '\0';
  return Dest;
}
//---------------------------------------------------------------------------
//Encripta a senha digitada
char *DecryptText(char *Source)
{
	char *Dest;
	int I,L;
	unsigned char A;
	L = strlen(Source);
	Dest = new char[L+1];

	for(I = 0; I < L; I++) {
		A = (char)Source[I];
		Dest[L - I - 1] = (char)((270 + I) - (int)A);
	}

	Dest[L] = '\0';
	return Dest;
}
//---------------------------------------------------------------------------
void AddAppForm(String FormClass, String FormTitle, int FormModule)
{
      SfgForm *AppForm = new SfgForm();
      AppForm->FormClass = FormClass;
      AppForm->FormTitle = FormTitle;
      AppForm->FormModule = FormModule;
      if (AppForms == NULL)
         AppForms = new SfgForms();
      AppForms->Add((void*)AppForm);
}
//---------------------------------------------------------------------------
void AddAppFormClass(String FormClass, System::TMetaClass* AClass)
{
   if (AppFormsClass == NULL) {
      AppFormsClass = new SfgFormsClass();
      AppFormsClass->Duplicates = dupError;
      AppFormsClass->CaseSensitive = true;
   }
   AppFormsClass->AddObject(FormClass, (System::TObject*)AClass);
}
//---------------------------------------------------------------------------
System::TMetaClass* GetAppFormClass(String FormClass)
{
   int iIndex;
   if (AppFormsClass == NULL)
      return NULL;      
   iIndex = AppFormsClass->IndexOf(FormClass);
   if (iIndex >= 0) {
      return (System::TMetaClass*)AppFormsClass->Objects[iIndex];
   }
   return NULL;
}
//---------------------------------------------------------------------------
void AssignImage(TImage *Origem, TImage *Destino)
{
try {
   if (Origem != NULL) {
      if (Origem->Picture != NULL) {
         if (Origem->Picture->Graphic != NULL) {
            Destino->Picture->Assign(Origem->Picture);
         } else if (Origem->Picture->Bitmap != NULL) {
            Destino->Picture->Assign(Origem->Picture);
         }
      }
   }
} __finally {}
}
//---------------------------------------------------------------------------
namespace Validacoes
{

bool BackSpace(char &C){
  if(int(C) == 8)
     return true;
  else
     return false;
}

void CharIsInteger(char &C){
  if(BackSpace(C))
    return;
  if(!isdigit(C))
    C =0;
}

void CharIsFloat(char &C){
  if(C == ',')
    return;
  if(!isdigit(C))
    C =0;
}

bool IsInteger(String StrInteger){
try {
  StrToInt(StrInteger);
  return true;
}
catch(...){
  Application->MessageBox("O valor informado não é um número inteiro válido!",
                         "Mensagem de Erro",MB_OK|MB_ICONSTOP);
  return false;
}
}

bool IsFloat(String StrFloat){
try {
  StrToFloat(StrFloat);
  return true;
}
catch(...){
  Application->MessageBox("O valor informado não é número decimal válido!",
                         "Mensagem de Erro",MB_OK|MB_ICONSTOP);
  return false;
}
}

bool IsDate(String StrDate){
try {
  StrToDateTime(StrDate);
  return true;
}
catch(...){
  Application->MessageBox("O valor informado não é uma data válida!",
                         "Mensagem de Erro",MB_OK|MB_ICONSTOP);
  return false;
}
}

bool IsTime(String StrTime){
try {
  StrToDateTime(StrTime);
  return true;
}
catch(...){
  Application->MessageBox("O valor informado não é uma hora válida!",
                         "Mensagem de Erro",MB_OK|MB_ICONSTOP);
  return false;
}
}
//---------------------------------------------------------------------------
void ValidarFloat(String Valor, char &C){
  int I;
  int Achou = 0;
  if(BackSpace(C)) return;
  for(I = 0;I <= Valor.Length();I++){
    if(Valor.SubString(I,1) == ",")
      Achou++;
  }
  if(Achou > 0 && C == ','){
    C = 0;
    MessageBeep(0xFFFFFFFF);
  }
  else
    CharIsFloat(C);
}
//---------------------------------------------------------------------------
bool ValidarCPFCNPJ(String Valor) {
  //Valida argumento
   if (Valor.Length() != 15)
      return false;
   if (Valor.SubString(10,4) == "0000") {
      Valor = Valor.SubString(1,9) + Valor.SubString(14,Valor.Length());
      return ValidarCPF(Valor);
   } else {
      Valor = Valor.SubString(2,Valor.Length());
      return ValidarCNPJ(Valor);
   }
}
//---------------------------------------------------------------------------
bool ValidarCPF(String Valor){
  int soma;
  int Resto;
  int i;

  //Valida argumento
  if (Valor.Length() != 11)
     return false;
  soma = 0;
  for(i = 1;i <= 9; i++)
    soma = soma + Valor.SubString(i,1).ToInt() * (11 - i);
  Resto = 11 - (soma - (int(soma / 11) * 11));
  if (Resto == 10 || Resto == 11) Resto = 0;
  if (Resto != Valor.SubString(10,1).ToInt())
     return false;
  soma = 0;
  for(i = 1;i <= 10; i++)
    soma = soma + Valor.SubString(i,1).ToInt() * (12 - i);
  Resto = 11 - (soma - (int(soma / 11) * 11));
  if (Resto == 10 || Resto == 11) Resto = 0;
  if (Resto != Valor.SubString(11,1).ToInt())
     return false;
  return true;
}
//---------------------------------------------------------------------------
bool ValidarCNPJ(String Valor){
  int soma = 0;
  int Resto;
  int i;
  int c[13] = {6,5,4,3,2,9,8,7,6,5,4,3,2};
  for (i=1; i <= 12; i++)
    soma += Valor.SubString(i,1).ToInt() * c[i];
  Resto = soma % 11;
  if(Resto < 2) Resto = 0; else Resto = 11 - Resto;
  if (Resto != Valor.SubString(13,1).ToInt())
     return false;
  soma = 0;
  for (i=1; i <= 13; i++)
    soma += Valor.SubString(i,1).ToInt() * c[i-1];
  Resto = soma % 11;
  if(Resto < 2) Resto = 0; else Resto = 11 - Resto;
  if (Resto != Valor.SubString(14,1).ToInt())
     return false;
  return true;
}
//---------------------------------------------------------------------------
}; //End namespace Validacoes

namespace ValidacoesDB {
//---------------------------------------------------------------------------
bool ExistePrimaryKey(TZConnection *pConexao, String sSQL) {
	bool bRet = false;
	TZQuery *QyPk = new TZQuery(Application);
try {
	QyPk->SQL->Text = sSQL;
	QyPk->Connection = pConexao;
	QyPk->Active = true;
	if (QyPk->RecordCount > 0) {
		bRet = true;
	}
}__finally {
	delete(QyPk);
}
  return bRet;
}
//---------------------------------------------------------------------------
bool ExisteForeingKey(TZConnection *pConexao, String sSQL) {
	bool bRet = false;
	TZQuery *QyFk = new TZQuery(Application);
try {
	QyFk->SQL->Text = sSQL;
	QyFk->Connection = pConexao;
	QyFk->Active = true;
	if (QyFk->RecordCount > 0) {
		bRet = true;
	}
}__finally {
	delete(QyFk);
}
  return bRet;
}
//---------------------------------------------------------------------------
String GetDenominacaoByKey(TZConnection *pConexao, String sSQL) {
	String sRet = "";
	TZQuery *QyPk = new TZQuery(Application);
try {
	QyPk->SQL->Text = sSQL;
	QyPk->Connection = pConexao;
	QyPk->Active = true;
	if (QyPk->RecordCount > 0) {
		sRet = QyPk->Fields->Fields[0]->AsString;
	}
}__finally {
	delete(QyPk);
}
  return sRet;
}
//---------------------------------------------------------------------------
Variant GetParamValue(TZConnection *pConexao, String sSQL)
{
	TZReadOnlyQuery *QyGetParamValue;
	Variant Value = NULL;
try {
	QyGetParamValue = new TZReadOnlyQuery(Application);
	QyGetParamValue->Connection = pConexao;
	QyGetParamValue->SQL->Text = sSQL;
	QyGetParamValue->Active = true;
	Value = QyGetParamValue->Fields->Fields[0]->Value;
	QyGetParamValue->Active = false;
	delete QyGetParamValue;
} catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao buscar as informações de parametrização:\n";
   Msg = Msg + e.Message;
   MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
	return Value;
}
//---------------------------------------------------------------------------
bool SetParamValue(TZConnection *pConexao, String sSQL)
{
	TZReadOnlyQuery *QyGetParamValue;
	bool bRet = false;
try {
	QyGetParamValue = new TZReadOnlyQuery(Application);
	QyGetParamValue->Connection = pConexao;
	QyGetParamValue->SQL->Text = sSQL;
	QyGetParamValue->Active = true;
	QyGetParamValue->Active = false;
	delete QyGetParamValue;
	bRet = true;
} catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao atualizar as informações de parametrização:\n";
   Msg = Msg + e.Message;
   MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
	return bRet;
}
//---------------------------------------------------------------------------
bool GetProxCod(TZConnection *pConexao, String Param, String &RetCod)
{
   String PrefCod = "";
   String ProxCod = "1";
   int iZero = 0;
	TZReadOnlyQuery *QyGetParam;
try {
	QyGetParam = new TZReadOnlyQuery(Application);
	QyGetParam->Connection = pConexao;
	QyGetParam->SQL->Text = \
"SELECT nome_parametro, valor_flag, valor_texto, valor_decimal\
  FROM tbl_parametro_sistema\
 WHERE nome_parametro = " + QuotedStr(Param);
	QyGetParam->Active = true;
   QyGetParam->First();
   if (!QyGetParam->Eof) {
      PrefCod = QyGetParam->FieldByName("valor_texto")->AsString;
      ProxCod = QyGetParam->FieldByName("valor_decimal")->AsString;
      iZero = QyGetParam->FieldByName("valor_flag")->AsInteger;
   }
	QyGetParam->Active = false;
	delete QyGetParam;
} catch(Exception &e) {
   return false;
}
   if (iZero > 0) {
      char mask[5] = "%0";
      strcat(mask,IntToStr(iZero).c_str());
      strcat(mask,"i");
      RetCod.sprintf(mask,StrToInt(ProxCod));
   } else {
      RetCod = ProxCod;
   }
   RetCod = PrefCod + RetCod;
   //Atualiza o parametro para o próximo número
   ProxCod = IntToStr((StrToInt(ProxCod) + 1));
   String SQL = QuotedStr(Param) + "," + QuotedStr(IntToStr(iZero));
	if(PrefCod.Length() > 0)
      SQL = SQL + "," + QuotedStr(PrefCod);
   else
      SQL = SQL + ",NULL";
   SQL = SQL + "," + ProxCod;
   SQL = "CALL set_parametro_sistema(" + SQL + ",NULL,'" + AppUser->Usuario + "');";
   return ValidacoesDB::SetParamValue(pConexao,SQL);
}
//---------------------------------------------------------------------------
}; //End namespace ValidacoesDB


