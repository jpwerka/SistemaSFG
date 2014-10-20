//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgVdpCustom.h"
#include <DBConsts.hpp>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------
USEFORM("Vendas\uVdp1001.cpp", Vdp1001);
USEFORM("Vendas\uVdp1002.cpp", Vdp1002);
USEFORM("Vendas\uVdp1003.cpp", Vdp1003);
USEFORM("Vendas\uVdp1004.cpp", Vdp1004);
USEFORM("Vendas\uVdp1010.cpp", Vdp1010);
USEFORM("Cliente\uVdp1020.cpp", Vdp1020);
USEFORM("Cliente\uVdp1021.cpp", Vdp1021);
USEFORM("Representante\uVdp1023.cpp", Vdp1023);
USEFORM("Cliente\uVdp1022.cpp", Vdp1022);
USEFORM("Representante\uVdp1024.cpp", Vdp1024);
USEFORM("Cliente\uVdp1025.cpp", Vdp1025);
USEFORM("Vendas\uVdp2001.cpp", Vdp2001);
USEFORM("Cliente\uVdp2020.cpp", Vdp2020);
USEFORM("Representante\uVdp2021.cpp", Vdp2021);
USEFORM("Representante\uVdp2022.cpp", Vdp2022);
USEFORM("Vendas\uVdp3001.cpp", Vdp3001);
USEFORM("Vendas\uVdp3002.cpp", Vdp3002);
USEFORM("Vendas\uVdp3003.cpp", Vdp3003);
USEFORM("Vendas\uVdp3004.cpp", Vdp3004);
USEFORM("Vendas\uVdp3005.cpp", Vdp3005);
USEFORM("Vendas\uVdp3006.cpp", Vdp3006);
USEFORM("Vendas\uVdp3007.cpp", Vdp3007);
USEFORM("Vendas\uVdp3010.cpp", Vdp3010);
USEFORM("Cliente\uVdp3020.cpp", Vdp3020);
USEFORM("Cliente\uVdp3021.cpp", Vdp3021);
USEFORM("Representante\uVdp3022.cpp", Vdp3022);
USEFORM("Representante\uVdp3008.cpp", Vdp3008);
USEFORM("Vendas\uVdp3011.cpp", Vdp3011);
USEFORM("Vendas\uVdp3012.cpp", Vdp3012);
//---------------------------------------------------------------------------
HINSTANCE hSfgVdpCustom = NULL;
PSfgVdpCustomInit SfgVdpCustomInit = NULL;
PSfgVdpCustomFinish SfgVdpCustomFinish = NULL;
PSfgVdp1001AfterCreate SfgVdp1001AfterCreate = NULL;
PSfgVdp1001AfterValidInsert SfgVdp1001AfterValidInsert = NULL;
PSfgVdp1001AfterValidUpdate SfgVdp1001AfterValidUpdate = NULL;
PSfgVdp1010AfterCreate SfgVdp1010AfterCreate = NULL;
PSfgVdp1020BeforeCreate SfgVdp1020BeforeCreate = NULL;
PSfgVdp1020AfterCreate SfgVdp1020AfterCreate = NULL;
//---------------------------------------------------------------------------

extern "C" void __declspec(dllexport) WINAPI SfgVendasInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgVendasFinish();
extern "C" long __declspec(dllexport) WINAPI SfgVendasCreateForm(ShortString sFormName, int iNivelPermissao);
extern "C" long __declspec(dllexport) WINAPI SfgVendasCreateFormEx(ShortString sFormName, int iNivelPermissao, WPARAM wParam, LPARAM lParam);

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgVendasInit(LPARAM lParam)
{
   hSfgVdpCustom = LoadLibrary("SfgVdpCustom.dll");
   if(hSfgVdpCustom) {
      SfgVdpCustomInit = (PSfgVdpCustomInit)GetProcAddress(hSfgVdpCustom,"SfgVdpCustomInit");
      SfgVdpCustomFinish = (PSfgVdpCustomFinish)GetProcAddress(hSfgVdpCustom,"SfgVdpCustomFinish");
      if (SfgVdpCustomInit)
         SfgVdpCustomInit(lParam);
   }
}
//---------------------------------------------------------------------------
void WINAPI SfgVendasFinish()
{
   if (SfgVdpCustomFinish)
      SfgVdpCustomFinish();
   if (hSfgVdpCustom)
      FreeLibrary(hSfgVdpCustom);
}
//---------------------------------------------------------------------------



