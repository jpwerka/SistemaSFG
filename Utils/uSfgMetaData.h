//---------------------------------------------------------------------------
#ifndef uSfgMetaDataH
#define uSfgMetaDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <DB.hpp>

enum SFG_FIELD_DEF {
   FD_NONE    = 0x00000000,
   FD_PKKEY   = 0x00000001,
   FD_BROWSE  = 0x00000002,
   FD_SEARCH  = 0x00000004,
   FD_ORDERB  = 0x00000008,
   FD_ORDERS  = 0x00000010,
   FD_INDEX   = 0x00000020,
   FD_NOTNULL = 0x00000040,
   FD_FKKEY   = 0x00000080,
   FD_MONEY   = 0x00000100,
   FD_FKLIST  = 0x00000200
};

struct SfgMfOrder {
   bool InBrowse;
   bool InSearch;
};

enum SfgMfEdit { smeMaskEdit, smeComboBox, smeCheckBox };

class TSfgMetaField;
class PACKAGE TSfgMetaTable : public TComponent
{
private:
   String FTableName;
private:
   void __fastcall SetTableName(String Value);
   TSfgMetaField* __fastcall GetMetaField(int AIndex);
public:
   __fastcall TSfgMetaTable(TComponent* AOwner);
   __property String TableName = {read=FTableName, write=SetTableName};
   __property TSfgMetaField* MetaFields[int Index] = {read=GetMetaField};
   __property int FieldCount = {read=ComponentCount};
	TSfgMetaField* __fastcall FieldByName(const String Name);
	TSfgMetaField* __fastcall Find(const String Name);
};
 
class PACKAGE TSfgMetaField : public TComponent
{
private:
   bool FIsPkKey;
   bool FIsFkKey;
   bool FIsBrowse;
   bool FIsSearch;
   SfgMfOrder FOrder;
   bool FIsIndex;
   bool FIsNotNull;
   bool FIsMoney;
   bool FIsFkList;
   SfgMfEdit FEditCmp;
   String FEditMask;
   String FFieldName;
   String FDisplayLabel;
   String FDisplayFormat;
   String FCheckValues;
   int FSize;
   int FPrecision;
   TFieldType FDataType;
   String FFkTableName;
   String FFkColumnName;
protected:
   void __fastcall SetOrder(SfgMfOrder Value);
public:
   __fastcall TSfgMetaField(TComponent* AOwner);
	__property bool IsPkKey = {read=FIsPkKey, write=FIsPkKey};
	__property bool IsFkKey = {read=FIsFkKey, write=FIsFkKey};
	__property bool IsBrowse = {read=FIsBrowse, write=FIsBrowse};
	__property bool IsSearch = {read=FIsSearch, write=FIsSearch};
	__property bool IsIndex = {read=FIsIndex, write=FIsIndex};
	__property bool IsNotNull = {read=FIsNotNull, write=FIsNotNull};
	__property bool IsMoney = {read=FIsMoney, write=FIsMoney};
	__property bool IsFkList = {read=FIsFkList, write=FIsFkList};
	__property SfgMfOrder Order = {read=FOrder, write=SetOrder};
	__property SfgMfEdit EditCmp = {read=FEditCmp, write=FEditCmp};
   __property String EditMask = {read=FEditMask, write=FEditMask};
   __property String FieldName = {read=FFieldName, write=FFieldName};
   __property String DisplayLabel = {read=FDisplayLabel, write=FDisplayLabel};
	__property String DisplayFormat = {read=FDisplayFormat, write=FDisplayFormat};
   __property String CheckValues = {read=FCheckValues, write=FCheckValues};
   __property String FkTableName = {read=FFkTableName, write=FFkTableName};
   __property String FkColumnName = {read=FFkColumnName, write=FFkColumnName};
	__property int Precision = {read=FPrecision, write=FPrecision, default=0};
	__property int Size = {read=FSize, write=FSize, default=0};
	__property TFieldType DataType = {read=FDataType, write=FDataType, default=0};
};

class PACKAGE TSfgFieldDef : public TFieldDef
{
private:
   bool FIsPkKey;
   bool FIsMoney;
   bool FVisible;
   String FEditMask;
   String FDisplayLabel;
   String FDisplayFormat;
   int FDisplayWidth;
   TSfgMetaField *FMetaField;
private:
   void __fastcall SetMetaField(TSfgMetaField *Value);
public:
	__fastcall TSfgFieldDef(TFieldDefs* Owner, const String Name, TFieldType DataType, int Size, int FieldNo);
   __property bool IsPkKey = {read=FIsPkKey, write=FIsPkKey};
	__property bool IsMoney = {read=FIsMoney, write=FIsMoney};
   __property bool Visible = {read=FVisible, write=FVisible};
   __property String EditMask = {read=FEditMask, write=FEditMask};
   __property String DisplayLabel = {read=FDisplayLabel, write=FDisplayLabel};
	__property String DisplayFormat = {read=FDisplayFormat, write=FDisplayFormat};
   __property int DisplayWidth = {read=FDisplayWidth, write=FDisplayWidth};
   __property TSfgMetaField* MetaField = {read=FMetaField, write=SetMetaField};
};

//---------------------------------------------------------------------------
extern PACKAGE TSfgMetaTable* AddMetaTable(String TableName);
extern PACKAGE TSfgMetaTable* AddMetaTable(TSfgMetaTable *MetaTable);
extern PACKAGE TSfgMetaTable* GetMetaTable(String TableName);
extern PACKAGE TSfgFieldDef* CreateFieldDef(TSfgMetaField *MetaField, TDataSet *DataSet);
extern PACKAGE TSfgFieldDef* CopyFieldDef(TField *Field, TDataSet *DataSet);
extern PACKAGE TFieldDefs* CreateFieldDefs(DynamicArray<String> AFieldDefs, TDataSet *DataSet);
extern PACKAGE TFieldDefs* CreateFieldDefs(String TableName, String FieldNames, TDataSet *DataSet);
extern PACKAGE TFieldDefs* CreateFieldDefs(TSfgMetaTable *MetaTable, String FieldNames, TDataSet *DataSet);
extern PACKAGE TFields* CreateFields(TDataSet *DataSet);
extern PACKAGE TFields* AddVirtualFields(DynamicArray<String> AFieldDefs, TDataSet *DataSet, bool CreateFields);
extern PACKAGE TField* CreateField(TSfgFieldDef *FieldDef);
//---------------------------------------------------------------------------
#endif
 