//---------------------------------------------------------------------------
#ifndef uSfgToExcelH
#define uSfgToExcelH
//---------------------------------------------------------------------------
#include <DB.hpp>
#include "ZConnection.hpp"
#include "ZDataset.hpp"
#include <OleCtnrs.hpp>
#include "Excel_2K_SRVR.h"
//---------------------------------------------------------------------------
class PACKAGE TSfgAnaToExcel : public System::TObject
{
private:
   HANDLE hFileXml;
	String sFileName;
	String sDadosSheet;
	String sPivotSheet;
	String sPivotTable;
   bool CreateFileXml(String &sMsgErro);
   bool WriteFileXml(String sTagXml);
   bool LoadWorkbookHeader(String &sMsgErro);
   bool LoadPivotSheet(String &sMsgErro);
   bool LoadPivotTable(int iCols, int iRows, String &sMsgErro);
protected:
	TExcelApplication		*pExcel;
	TExcelWorkbook			*pWorkbook;
	TExcelWorksheet		*pDadosSheet;
	TExcelWorksheet		*pPivotSheet;
	PivotTablePtr			pPivotTable;
	RangePtr					pRange;
   OleVariant oExcel;
   OleVariant oWorkbooks;
	TZReadOnlyQuery *QySfgToExcel;
public:
	__fastcall TSfgAnaToExcel();
	__fastcall ~TSfgAnaToExcel();
	bool SetContainer(TOleContainer *OleContainer);
	bool QueryToExcel(TZConnection *AppConnection, String SQL);
	bool QueryToExcelEx(TZConnection *AppConnection, String SQL);
   __property String FileName = {read=sFileName, write=sFileName};
   __property String DadosSheet = {read=sDadosSheet, write=sDadosSheet};
   __property String PivotSheet = {read=sPivotSheet, write=sPivotSheet};
   __property String PivotTable = {read=sPivotTable, write=sPivotTable};
};
#endif
