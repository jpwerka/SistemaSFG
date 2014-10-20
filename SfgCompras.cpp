//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgSupCustom.h"
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
USEFORM("Compras\uSup1001.cpp", Sup1001);
USEFORM("Compras\uSup1002.cpp", Sup1002);
USEFORM("Compras\uSup1003.cpp", Sup1003);
USEFORM("Compras\uSup1004.cpp", Sup1004);
USEFORM("Fornecedor\uSup1010.cpp", Sup1010);
USEFORM("Fornecedor\uSup1011.cpp", Sup1011);
USEFORM("Compras\uSup2001.cpp", Sup2001);
USEFORM("Fornecedor\uSup2020.cpp", Sup2020);
USEFORM("Compras\uSup3001.cpp", Sup3001);
USEFORM("Compras\uSup3002.cpp", Sup3002);
USEFORM("Compras\uSup3003.cpp", Sup3003);
USEFORM("Compras\uSup3004.cpp", Sup3004);
USEFORM("Compras\uSup3005.cpp", Sup3005);
USEFORM("Compras\uSup3006.cpp", Sup3006);
USEFORM("Fornecedor\uSup3010.cpp", Sup3010);
USEFORM("Fornecedor\uSup3020.cpp", Sup3020);
USEFORM("Vendas\uVdp1010.cpp", Vdp1010);
USEFORM("Cliente\uVdp1021.cpp", Vdp1021);
USEFORM("Cliente\uVdp1022.cpp", Vdp1022);
//---------------------------------------------------------------------------
HINSTANCE hSfgVdpCustom = NULL;
PSfgVdpCustomInit SfgVdpCustomInit = NULL;
PSfgVdpCustomFinish SfgVdpCustomFinish = NULL;
PSfgVdp1010AfterCreate SfgVdp1010AfterCreate = NULL;
//---------------------------------------------------------------------------

extern "C" void __declspec(dllexport) WINAPI SfgComprasInit(LPARAM lParam);
extern "C" void __declspec(dllexport) WINAPI SfgComprasFinish();

#pragma argsused
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
   return 1;
}
//---------------------------------------------------------------------------
void WINAPI SfgComprasInit(LPARAM lParam)
{
   SfgForm *AppForm;

   //Esta parte é para alterar o registro do formulário
   //do módulo de Vendas que é usado pelo módulo de Compras
   if (AppForms != NULL) {
      for (int i=0; i<AppForms->Count; i++) {
         AppForm = (SfgForm*)AppForms->Items[i];
         if ((AppForm->FormClass == "Vdp1010") ||
             (AppForm->FormClass == "Vdp1021") ||
             (AppForm->FormClass == "Vdp1022")) {
              AppForm->FormModule =APP_MODULO_COMPRAS;
         }
      }
   }

   //Carregando as customizações do módulo de vendas
   hSfgVdpCustom = LoadLibrary("SfgVdpCustom.dll");
   if(hSfgVdpCustom) {
      SfgVdpCustomInit = (PSfgVdpCustomInit)GetProcAddress(hSfgVdpCustom,"SfgVdpCustomInit");
      SfgVdpCustomFinish = (PSfgVdpCustomFinish)GetProcAddress(hSfgVdpCustom,"SfgVdpCustomFinish");
      if (SfgVdpCustomInit)
         SfgVdpCustomInit(lParam);
   }

}
//---------------------------------------------------------------------------
void WINAPI SfgComprasFinish()
{
   if (SfgVdpCustomFinish)
      SfgVdpCustomFinish();
   if (hSfgVdpCustom)
      FreeLibrary(hSfgVdpCustom);
}
//---------------------------------------------------------------------------



