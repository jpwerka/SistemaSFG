//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
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
USEFORM("Produto\uPrd1001.cpp", Prd1001);
USEFORM("Produto\uPrd1002.cpp", Prd1002);
USEFORM("Produto\uPrd1003.cpp", Prd1003);
USEFORM("Produto\uPrd1004.cpp", Prd1004);
USEFORM("Produto\uPrd2001.cpp", Prd2001);
USEFORM("Produto\uPrd2002.cpp", Prd2002);
USEFORM("Produto\uPrd3001.cpp", Prd3001);
USEFORM("Produto\uPrd3002.cpp", Prd3002);
USEFORM("Produto\uPrd3003.cpp", Prd3003);
USEFORM("Produto\uPrd3004.cpp", Prd3004);
//---------------------------------------------------------------------------
#pragma link "Utils/uSfgBrowseSup.obj"
//---------------------------------------------------------------------------

extern "C" void __declspec(dllexport) WINAPI SfgEstoqueInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgEstoqueFinish();

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgEstoqueInit(LPARAM lParam)
{
   //Não faz nada
}
//---------------------------------------------------------------------------
void WINAPI SfgEstoqueFinish()
{
   //Não faz nada
}
//---------------------------------------------------------------------------




