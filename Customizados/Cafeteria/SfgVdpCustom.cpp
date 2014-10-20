//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uCVdp1001.h"
#include "uCVdp1010.h"
#include "uCVdp1020.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("uCVdp1020.cpp", CVdp1020A);
//---------------------------------------------------------------------------
extern "C" void __declspec(dllexport) WINAPI SfgVdpCustomInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgVdpCustomFinish();
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1001AfterCreate(TForm *pForm);
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1001AfterValidInsert(TForm *pForm, TDataSet *pDataSet);
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1001AfterValidUpdate(TForm *pForm, TDataSet *pDataSet);
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1010AfterCreate(TForm *pForm);
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1020BeforeCreate(TForm *pForm);
extern "C" bool __declspec(dllexport) WINAPI SfgVdp1020AfterCreate(TForm *pForm);

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgVdpCustomInit(LPARAM lParam)
{
   //Não faz nada
}
//---------------------------------------------------------------------------
void WINAPI SfgVdpCustomFinish()
{
   //Não faz nada
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1001AfterCreate(TForm *pForm)
{
   return uCVdp1001::ValidFormPgtoSenha(pForm);
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1001AfterValidInsert(TForm *pForm, TDataSet *pDataSet)
{
   return uCVdp1001::AfterValidInsert(pForm, pDataSet);
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1001AfterValidUpdate(TForm *pForm, TDataSet *pDataSet)
{
   return true; //SfgVdp1001AfterValidInsert(pForm, pDataSet);
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1010AfterCreate(TForm *pForm)
{
   uCVdp1010::CreateButtonParametro(pForm);
   return true;
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1020BeforeCreate(TForm *pForm)
{
   uCVdp1020::CreateFieldInadimplente(pForm);
   return true;
}
//---------------------------------------------------------------------------
bool WINAPI SfgVdp1020AfterCreate(TForm *pForm)
{
   uCVdp1020::CreateButtonSenha(pForm);
   return true;
}
//---------------------------------------------------------------------------

