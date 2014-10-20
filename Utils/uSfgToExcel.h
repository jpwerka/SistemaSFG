//---------------------------------------------------------------------------
#ifndef uSfgToExcelH
#define uSfgToExcelH
//---------------------------------------------------------------------------
#include <DB.hpp>
#include "ZConnection.hpp"
#include "ZDataset.hpp"
#include <frxProgress.hpp>
//---------------------------------------------------------------------------
#include <list>
#if !defined(__USING_STD_NAMES__) && defined(__cplusplus)
using namespace std;
#endif
//---------------------------------------------------------------------------
typedef struct {
   OLECHAR FieldName[30];
   OLECHAR Caption[50];
   TFieldType FieldType;
} SfgPivotFdPage;
typedef list<SfgPivotFdPage*> SfgPivotFdPageList;

typedef struct {
   OLECHAR FieldName[30];
   OLECHAR Caption[50];
   TFieldType FieldType;
} SfgPivotFdRow;
typedef list<SfgPivotFdRow*> SfgPivotFdRowList;

typedef struct {
   OLECHAR FieldName[30];
   OLECHAR Caption[50];
   TFieldType FieldType;
   int FieldFunction;
} SfgPivotFdData;
typedef list<SfgPivotFdData*> SfgPivotFdDataList;
//---------------------------------------------------------------------------
class PACKAGE TSfgToExcel : public System::TObject
{
private:
   bool FShowProgress;
	String FDadosSheet;
   String FFileName;
protected:
   VARIANT vExcelApp;
   VARIANT vWorkBook;
   VARIANT vDadosSheet;
   VARIANT vDataRange;
   TfrxProgress *FProgress;
	TZReadOnlyQuery *QySfgToExcel;
   bool ApplyStyles(TDataSet *DataSet);
public:
	__fastcall TSfgToExcel();
	__fastcall ~TSfgToExcel();
   __property bool ShowProgress = {read=FShowProgress, write=FShowProgress};
   __property String DadosSheet = {read=FDadosSheet, write=FDadosSheet};
   __property String FileName = {read=FFileName, write=FFileName};
   __property TZReadOnlyQuery *DataSet = {read=QySfgToExcel};
   virtual bool StartExcel();
   virtual bool FinishExcel();
   String GetExcelFileName(TCustomForm *Parent);
	bool QueryToExcel(TZConnection *Connection, String SQL);
	bool DataSetToExcel(TDataSet *DataSet);
   void __fastcall(__closure *OnGetTitle) (TField *Field, OleVariant &Value);
   void __fastcall(__closure *OnGetValue) (TField *Field, OleVariant &Value);
};
//---------------------------------------------------------------------------
class PACKAGE TSfgLstToExcel : public TSfgToExcel
{
public:
	inline __fastcall TSfgLstToExcel() : TSfgToExcel() {};
	inline __fastcall ~TSfgLstToExcel() {};
};
//---------------------------------------------------------------------------
class PACKAGE TSfgAnaToExcel : public TSfgToExcel
{
private:
	String FPivotSheet;
	String FPivotTable;
protected:
   VARIANT vPivotSheet;
public:
	__fastcall TSfgAnaToExcel();
	inline __fastcall ~TSfgAnaToExcel() {};
   __property String PivotSheet = {read=FPivotSheet, write=FPivotSheet};
   __property String PivotTable = {read=FPivotTable, write=FPivotTable};
   bool GeneratePivotTable(SfgPivotFdPageList *PageFields, SfgPivotFdRowList *RowFields, SfgPivotFdDataList *DataFields);
   bool FinishExcel();
};
//---------------------------------------------------------------------------
#endif
