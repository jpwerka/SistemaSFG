//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgFinCustom.h"
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
USEFORM("Financeiro\uFin1001.cpp", Fin1001);
USEFORM("Financeiro\uFin1002.cpp", Fin1002);
USEFORM("Financeiro\uFin1003.cpp", Fin1003);
USEFORM("Financeiro\uFin1004.cpp", Fin1004);
USEFORM("Financeiro\uFin1005.cpp", Fin1005);
USEFORM("Financeiro\uFin1006.cpp", Fin1006);
USEFORM("Financeiro\uFin1007.cpp", Fin1007);
USEFORM("Financeiro\uFin2001.cpp", Fin2001);
USEFORM("Financeiro\uFin2002.cpp", Fin2002);
USEFORM("Financeiro\uFin2004.cpp", Fin2004);
USEFORM("Financeiro\uFin3002.cpp", Fin3002);
USEFORM("Financeiro\uFin3003.cpp", Fin3003);
USEFORM("Financeiro\uFin3004.cpp", Fin3004);
USEFORM("Financeiro\uFin3005.cpp", Fin3005);
USEFORM("Financeiro\uFin3006.cpp", Fin3006);
USEFORM("Financeiro\uFin3007.cpp", Fin3007);
USEFORM("Financeiro\uFin3008.cpp", Fin3008);
USEFORM("Financeiro\uFin3009.cpp", Fin3009);
USEFORM("Financeiro\uFin3010.cpp", Fin3010);
USEFORM("Financeiro\uFin3011.cpp", Fin3011);
USEFORM("Financeiro\uFin3012.cpp", Fin3012);
USEFORM("Financeiro\uFin3013.cpp", Fin3013);
USEFORM("Financeiro\uFin3014.cpp", Fin3014);
USEFORM("Financeiro\uFin3015.cpp", Fin3015);
USEFORM("Financeiro\uFin3016.cpp", Fin3016);
USEFORM("Financeiro\uFin3017.cpp", Fin3017);
//---------------------------------------------------------------------------
#pragma link "Utils/uSfgBrowseSup.obj"
#pragma link "Utils/uSfgBrowseVdp.obj"
//---------------------------------------------------------------------------
HINSTANCE hSfgFinCustom = NULL;
PSfgFinCustomInit SfgFinCustomInit = NULL;
PSfgFinCustomFinish SfgFinCustomFinish = NULL;
PSfgFin1003AfterCreate SfgFin1003AfterCreate = NULL;
PSfgFin1003AfterValidInsert SfgFin1003AfterValidInsert = NULL;
PSfgFin1003AfterValidUpdate SfgFin1003AfterValidUpdate = NULL;
//---------------------------------------------------------------------------

extern "C" void __declspec(dllexport) WINAPI SfgFinancasInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgFinancasFinish();
extern "C" long __declspec(dllexport) WINAPI SfgFinancasCreateForm(ShortString sFormName, int iNivelPermissao);

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgFinancasInit(LPARAM lParam)
{
   hSfgFinCustom = LoadLibrary("SfgFinCustom.dll");
   if(hSfgFinCustom) {
      SfgFinCustomInit = (PSfgFinCustomInit)GetProcAddress(hSfgFinCustom,"SfgFinCustomInit");
      SfgFinCustomFinish = (PSfgFinCustomFinish)GetProcAddress(hSfgFinCustom,"SfgFinCustomFinish");
      if (SfgFinCustomInit)
         SfgFinCustomInit(lParam);
   }
}
//---------------------------------------------------------------------------
void WINAPI SfgFinancasFinish()
{
   if (SfgFinCustomFinish)
      SfgFinCustomFinish();
   if (hSfgFinCustom)
      FreeLibrary(hSfgFinCustom);
}
//---------------------------------------------------------------------------

