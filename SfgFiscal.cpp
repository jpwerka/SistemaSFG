//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#pragma hdrstop
#pragma comment(lib, "xmlrtl.lib")
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
USEFORM("Fiscal\uObf1001.cpp", Obf1001);
USEFORM("Fiscal\uObf1002.cpp", Obf1002);
USEFORM("Fiscal\uObf1003.cpp", Obf1003);
USEFORM("Fiscal\uObf1004.cpp", Obf1004);
USEFORM("Fiscal\uObf1005.cpp", Obf1005);
USEFORM("Fiscal\uObf1007.cpp", Obf1007);
//---------------------------------------------------------------------------
extern "C" void __declspec(dllexport) WINAPI SfgFiscalInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgFiscalFinish();

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgFiscalInit(LPARAM lParam)
{
}
//---------------------------------------------------------------------------
void WINAPI SfgFiscalFinish()
{
}
//---------------------------------------------------------------------------



