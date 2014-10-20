//---------------------------------------------------------------------------
#ifndef uSfgFinCustomH
#define uSfgFinCustomH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
typedef void(__stdcall *PSfgFinCustomInit)(LPARAM lParam);
typedef void(__stdcall *PSfgFinCustomFinish)();
typedef long(__stdcall *PSfgFin1003AfterCreate)(TForm *pForm);
typedef long(__stdcall *PSfgFin1003AfterValidInsert)(TForm *pForm, TDataSet *pDataSet);
typedef long(__stdcall *PSfgFin1003AfterValidUpdate)(TForm *pForm, TDataSet *pDataSet);

extern HINSTANCE hSfgFinCustom;
extern PSfgFinCustomInit SfgFinCustomInit;
extern PSfgFinCustomFinish SfgFinCustomFinish;
extern PSfgFin1003AfterCreate SfgFin1003AfterCreate;
extern PSfgFin1003AfterValidInsert SfgFin1003AfterValidInsert;
extern PSfgFin1003AfterValidUpdate SfgFin1003AfterValidUpdate;
#endif

