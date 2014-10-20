//---------------------------------------------------------------------------
#ifndef uSfgFinCustomH
#define uSfgFinCustomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef void(__stdcall *PSfgVdpCustomInit)(LPARAM lParam);
typedef void(__stdcall *PSfgVdpCustomFinish)();
typedef long(__stdcall *PSfgVdp1010AfterCreate)(TForm *pForm);

extern HINSTANCE hSfgVdpCustom;
extern PSfgVdpCustomInit SfgVdpCustomInit;
extern PSfgVdpCustomFinish SfgVdpCustomFinish;
extern PSfgVdp1010AfterCreate SfgVdp1010AfterCreate;
#endif

