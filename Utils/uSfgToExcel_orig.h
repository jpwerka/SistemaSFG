//---------------------------------------------------------------------------
#ifndef uSfgToExcelH
#define uSfgToExcelH
//---------------------------------------------------------------------------
#include <DB.hpp>
#include "ZConnection.hpp"
#include "ZDataset.hpp"
#include <frxProgress.hpp>
#include <OleCtnrs.hpp>
#include "Excel_2K_SRVR.h"
//---------------------------------------------------------------------------
typedef ExcelWorksheetPtr WorksheetPtr;
class PACKAGE TSfgAnaToExcel : public System::TObject
{
private:
   bool FShowProgress;
	String FDadosSheet;
	String FPivotSheet;
	String FPivotTable;
	TZReadOnlyQuery *QySfgToExcel;
protected:
   _ApplicationDisp     *pExcel;
	TExcelWorkbook			*pWorkbook;
	TExcelWorksheet		*pDadosSheet;
	TExcelWorksheet		*pPivotSheet;
	PivotTablePtr			pPivotTable;
	RangePtr					pRange;
   TfrxProgress         *FProgress;
   bool ApplyStyles(TDataSet *DataSet);
public:
	__fastcall TSfgAnaToExcel();
	__fastcall ~TSfgAnaToExcel();
   __property bool ShowProgress = {read=FShowProgress, write=FShowProgress};
   __property String DadosSheet = {read=FDadosSheet, write=FDadosSheet};
   __property String PivotSheet = {read=FPivotSheet, write=FPivotSheet};
   __property String PivotTable = {read=FPivotTable, write=FPivotTable};
   __property TZReadOnlyQuery *DataSet = {read=QySfgToExcel};
	bool SetContainer(TOleContainer *OleContainer);
	bool QueryToExcel(TZConnection *Connection, String SQL);
};
//---------------------------------------------------------------------------
/*class PACKAGE TSfgLstToExcel : public System::TObject
{
private:
   bool FShowProgress;
	String FDadosSheet;
   String FFileName;
protected:
   _ApplicationDisp     *pExcel;
	TExcelWorkbook			*pWorkbook;
	TExcelWorksheet		*pDadosSheet;
	RangePtr					pRange;
   TfrxProgress         *FProgress;
	TZReadOnlyQuery *QySfgToExcel;
   bool OpenExcel();
   bool CloseExcel();
   bool ApplyStyles(TDataSet *DataSet);
public:
	__fastcall TSfgLstToExcel();
	__fastcall ~TSfgLstToExcel();
   __property bool ShowProgress = {read=FShowProgress, write=FShowProgress};
   __property String DadosSheet = {read=FDadosSheet, write=FDadosSheet};
   __property String FileName = {read=FFileName, write=FFileName};
	bool QueryToExcel(TZConnection *Connection, String SQL);
	bool DataSetToExcel(TDataSet *DataSet);
   void __fastcall(__closure *OnGetTitle) (TField *Field, OleVariant &Value);
   void __fastcall(__closure *OnGetValue) (TField *Field, OleVariant &Value);
};*/
class PACKAGE TSfgLstToExcel : public System::TObject
{
private:
   bool FShowProgress;
	String FDadosSheet;
   String FFileName;
protected:
   VARIANT vExcelApp;
   VARIANT vWorkBook;
   VARIANT vWorkSheet;
   VARIANT vRange;
   TfrxProgress         *FProgress;
	TZReadOnlyQuery *QySfgToExcel;
   bool OpenExcel();
   bool CloseExcel();
   bool ApplyStyles(TDataSet *DataSet);
public:
	__fastcall TSfgLstToExcel();
	__fastcall ~TSfgLstToExcel();
   __property bool ShowProgress = {read=FShowProgress, write=FShowProgress};
   __property String DadosSheet = {read=FDadosSheet, write=FDadosSheet};
   __property String FileName = {read=FFileName, write=FFileName};
	bool QueryToExcel(TZConnection *Connection, String SQL);
	bool DataSetToExcel(TDataSet *DataSet);
   void __fastcall(__closure *OnGetTitle) (TField *Field, OleVariant &Value);
   void __fastcall(__closure *OnGetValue) (TField *Field, OleVariant &Value);
};
#endif
