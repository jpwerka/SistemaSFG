//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
//#include "uCVdp1001.h"
//#include "uCVdp1010.h"
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("uCVdp3100.cpp", CVdp3100);
USEFORM("uCVdp3101.cpp", CVdp3101);
//---------------------------------------------------------------------------
extern "C" void __declspec(dllexport) WINAPI SfgVdpCustomInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgVdpCustomFinish();
//extern "C" bool __declspec(dllexport) WINAPI SfgVdp1001AfterCreate(TForm *pForm);
//extern "C" bool __declspec(dllexport) WINAPI SfgVdp1010AfterCreate(TForm *pForm);

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
//bool WINAPI SfgVdp1001AfterCreate(TForm *pForm)
//{
//   AlterButtonFechamento(pForm);
//   return true;
//}
////---------------------------------------------------------------------------
//bool WINAPI SfgVdp1010AfterCreate(TForm *pForm)
//{
//   uCVdp1010::CreateButtonParametro(pForm);
//   return true;
//}
//---------------------------------------------------------------------------

