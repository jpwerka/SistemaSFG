//---------------------------------------------------------------------------

#include <basepch.h>
#pragma hdrstop
USEFORM("Utils\uSfgToolbar.cpp", SfgToolbar); /* TFrame: File Type */
USEFORM("Utils\uSfgBrowse.cpp", frmBrowse);
USEFORM("Utils\uSfgSearch.cpp", frmSearch);
USEFORM("Utils\uSfgVaPara.cpp", SfgVaPara);
USEFORM("Utils\uSfgPreview.cpp", SfgPreview);
USEFORM("Utils\uRelatBase01.cpp", frmRelatBase01);
USEFORM("Utils\uFormBase02.cpp", frmBase02);
USEFORM("Utils\uFormBase01.cpp", frmBase01);
USEFORM("Utils\uDataModule.cpp", SfgDataCenter); /* TDataModule: File Type */
//---------------------------------------------------------------------------
#pragma link "ThemeMgr.obj"
#pragma link "ThemeMgrDB.obj"
#pragma link "ZSqlMonitor.obj"
#pragma link "CustomDbControls"
#pragma link "CustomButtons"
#pragma link "SfgResButtons"
#pragma link "SfgAlignEdit.obj"
#pragma link "SfgAlignGrid.obj"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Package source.
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void*)
{
   return 1;
}
//---------------------------------------------------------------------------
