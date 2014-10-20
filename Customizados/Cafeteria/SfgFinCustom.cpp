//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uCFin1003.h"
#pragma hdrstop
//---------------------------------------------------------------------------
extern "C" void __declspec(dllexport) WINAPI SfgFinCustomInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgFinCustomFinish();
extern "C" bool __declspec(dllexport) WINAPI SfgFin1003AfterCreate(TForm *pForm);
extern "C" bool __declspec(dllexport) WINAPI SfgFin1003AfterValidInsert(TForm *pForm, TDataSet *pDataSet);
extern "C" bool __declspec(dllexport) WINAPI SfgFin1003AfterValidUpdate(TForm *pForm, TDataSet *pDataSet);

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgFinCustomInit(LPARAM lParam)
{
   //Não faz nada
}
//---------------------------------------------------------------------------
void WINAPI SfgFinCustomFinish()
{
   //Não faz nada
}
//---------------------------------------------------------------------------
bool WINAPI SfgFin1003AfterCreate(TForm *pForm)
{
   uCFin1003::Determina5DiaUtil(0);
   return uCFin1003::ValidFormPgtoSenha(pForm);
}
//---------------------------------------------------------------------------
bool WINAPI SfgFin1003AfterValidInsert(TForm *pForm, TDataSet *pDataSet)
{
   return uCFin1003::AfterValidInsert(pForm, pDataSet);
}
//---------------------------------------------------------------------------
bool WINAPI SfgFin1003AfterValidUpdate(TForm *pForm, TDataSet *pDataSet)
{
   return true; //SfgFin1003AfterValidInsert(pForm, pDataSet);
}
//---------------------------------------------------------------------------



