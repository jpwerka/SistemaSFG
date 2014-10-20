//---------------------------------------------------------------------------
#ifndef uSfgVdpCustomH
#define uSfgVdpCustomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef void(__stdcall *PSfgVdpCustomInit)(LPARAM lParam);
typedef void(__stdcall *PSfgVdpCustomFinish)();
typedef long(__stdcall *PSfgVdp1001AfterCreate)(TForm *pForm);
typedef long(__stdcall *PSfgVdp1001AfterValidInsert)(TForm *pForm, TDataSet *pDataSet);
typedef long(__stdcall *PSfgVdp1001AfterValidUpdate)(TForm *pForm, TDataSet *pDataSet);
typedef long(__stdcall *PSfgVdp1010AfterCreate)(TForm *pForm);
typedef long(__stdcall *PSfgVdp1020BeforeCreate)(TForm *pForm);
typedef long(__stdcall *PSfgVdp1020AfterCreate)(TForm *pForm);

extern HINSTANCE hSfgVdpCustom;
extern PSfgVdpCustomInit SfgVdpCustomInit;
extern PSfgVdpCustomFinish SfgVdpCustomFinish;
extern PSfgVdp1001AfterCreate SfgVdp1001AfterCreate;
extern PSfgVdp1001AfterValidInsert SfgVdp1001AfterValidInsert;
extern PSfgVdp1001AfterValidUpdate SfgVdp1001AfterValidUpdate;
extern PSfgVdp1010AfterCreate SfgVdp1010AfterCreate;
extern PSfgVdp1020AfterCreate SfgVdp1020BeforeCreate;
extern PSfgVdp1020AfterCreate SfgVdp1020AfterCreate;
#endif

