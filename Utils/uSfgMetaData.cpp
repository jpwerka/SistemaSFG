//---------------------------------------------------------------------------
#include <vcl.h>
#include <ZDataset.hpp>
#include <ZDBCMySqlUtils.hpp>
#include <ZDatasetUtils.hpp>
#include "uDataModule.h"
#include "uSfgDinForms.hpp"
#pragma hdrstop
#include "uSfgMetaData.h"
#pragma package(smart_init)
const String SFieldNotFound = "Campo '%s' não encontrado.";
const String SMetaFieldNotFound = "Campo '%s' não encontrado no metadados da tabela '%s'.";
//---------------------------------------------------------------------------
typedef TStringList TSfgMetaTables;
TSfgMetaTables *AppMetaTables = NULL;
//---------------------------------------------------------------------------
__fastcall TSfgMetaTable::TSfgMetaTable(TComponent* AOwner)
        : TComponent(AOwner)
{
   FTableName = "";
}
//---------------------------------------------------------------------------
TSfgMetaField* __fastcall TSfgMetaTable::GetMetaField(int AIndex)
{
   return (TSfgMetaField*)this->Components[AIndex];
}
//---------------------------------------------------------------------------
TSfgMetaField* __fastcall TSfgMetaTable::FieldByName(const String Name)
{
   TSfgMetaField *Result = Find(Name);
   if (Result == NULL)
      DatabaseErrorFmt(SFieldNotFound, ARRAYOFCONST((Name)), this);
   return Result;
}
//---------------------------------------------------------------------------
TSfgMetaField* __fastcall TSfgMetaTable::Find(const String Name)
{
   return (TSfgMetaField*)this->FindComponent(Name);
}
//---------------------------------------------------------------------------
void __fastcall TSfgMetaTable::SetTableName(String Value)
{
   if (FTableName == Value)
      return;
   FTableName = Value;
   //Deve excluir dos componentes todos os campos já existentes
   for (int i = (this->ComponentCount - 1); i >= 0 ; i--)
      delete this->Components[i];
   //Deve carregar do metadados todos os campos da tabela
   TSfgMetaField *MetaField;
   int FieldProp;
try {
   TZQuery *QyMetaData = new TZQuery(Application);
   QyMetaData->Connection = AppConnection;
   QyMetaData->SQL->Text = "\
SELECT column_order, column_name, column_datatype, column_typename, column_size, \
       column_precision, column_label, column_editmask, column_properties, \
       column_checkvalues, column_editcmp, column_format, fk_table_name, fk_column_name\
  FROM tbl_meta_fiedls\
 WHERE table_name = '" + FTableName + "'\
 ORDER BY column_order";
   QyMetaData->Active = true;
   QyMetaData->First();
   while (!QyMetaData->Eof) {
      MetaField = new TSfgMetaField(this);
      MetaField->Name = QyMetaData->FieldByName("column_name")->AsString;
      MetaField->FieldName = QyMetaData->FieldByName("column_name")->AsString;
      MetaField->DisplayLabel = QyMetaData->FieldByName("column_label")->AsString;
      MetaField->DisplayFormat = QyMetaData->FieldByName("column_format")->AsString;
      MetaField->EditMask = QyMetaData->FieldByName("column_editmask")->AsString;
      MetaField->CheckValues = QyMetaData->FieldByName("column_checkvalues")->AsString;
      MetaField->DataType = ConvertDbcToDatasetType(
                            ConvertMySQLTypeToSQLType(
                            QyMetaData->FieldByName("column_datatype")->AsString,
                            QyMetaData->FieldByName("column_typename")->AsString));
      if (MetaField->DataType == ftString ||
         MetaField->DataType == ftMemo ||
         MetaField->DataType == ftFmtMemo ||
         MetaField->DataType == ftVarBytes ||
         MetaField->DataType == ftBytes ||
         MetaField->DataType == ftBlob ||
         MetaField->DataType == ftGraphic) {
         MetaField->Size = QyMetaData->FieldByName("column_size")->AsInteger;
         MetaField->Precision = 0;
      } else
      if (MetaField->DataType == ftBCD ||
         MetaField->DataType == ftFMTBcd) {
         MetaField->Size = QyMetaData->FieldByName("column_precision")->AsInteger;
         MetaField->Precision = QyMetaData->FieldByName("column_size")->AsInteger;
      } else {
         MetaField->Size = 0;
         MetaField->Precision = 15;
      }
      FieldProp = QyMetaData->FieldByName("column_properties")->AsInteger;
      MetaField->IsPkKey = (FieldProp & FD_PKKEY);
      MetaField->IsFkKey = (FieldProp & FD_FKKEY);
      MetaField->IsBrowse = (FieldProp & FD_BROWSE);
      MetaField->IsSearch = (FieldProp & FD_SEARCH);
      MetaField->Order.InBrowse = (FieldProp & FD_ORDERB);
      MetaField->Order.InSearch = (FieldProp & FD_ORDERS);
      MetaField->IsIndex = (FieldProp & FD_INDEX);
      MetaField->IsNotNull = (FieldProp & FD_NOTNULL);
      MetaField->IsMoney = (FieldProp & FD_MONEY);
      MetaField->IsFkList = (FieldProp & FD_FKLIST);
      MetaField->EditCmp = (SfgMfEdit)QyMetaData->FieldByName("column_editcmp")->AsInteger;
      MetaField->FkTableName = QyMetaData->FieldByName("fk_table_name")->AsString;
      MetaField->FkColumnName = QyMetaData->FieldByName("fk_column_name")->AsString;
      QyMetaData->Next();
   }
} catch (Exception &e) {
   String MsgErro = "Erro ao carregar as informações de metadados da tabela: " + FTableName + "\n" + e.Message;
   throw Exception(MsgErro);
}
}
//---------------------------------------------------------------------------
__fastcall TSfgMetaField::TSfgMetaField(TComponent* Owner)
        : TComponent(Owner)
{
   FIsPkKey = false;
   FIsFkKey = false;
   FIsBrowse = false;
   FIsSearch = false;
   FIsMoney = false;
   FIsFkList = false;
   FOrder.InBrowse = false;
   FOrder.InSearch = false;
   FIsIndex = false;
   FIsNotNull = false;
   FEditCmp = smeMaskEdit;
   FEditMask = "";
   FFieldName = "";
   FDisplayLabel = "";
   FDisplayFormat = "";
   FDataType = ftUnknown;
   FFkTableName = "";
   FFkColumnName = "";
}
//---------------------------------------------------------------------------
void __fastcall TSfgMetaField::SetOrder(SfgMfOrder Value) {
      FOrder.InBrowse = Value.InBrowse;
      FOrder.InSearch = Value.InSearch;
};
//---------------------------------------------------------------------------
__fastcall TSfgFieldDef::TSfgFieldDef(TFieldDefs* Owner, const AnsiString Name, TFieldType DataType, int Size, int FieldNo)
        : TFieldDef(Owner,Name,DataType,Size,false,FieldNo)
{
   FIsPkKey = false;
   FIsMoney = false;
   FVisible = true;
   FEditMask = "";
   FDisplayLabel = "";
   FDisplayWidth = 0;
   FDisplayFormat = "";
   FMetaField = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgFieldDef::SetMetaField(TSfgMetaField *Value)
{
   FMetaField = Value;
   if (FMetaField == NULL)
      return;

   this->IsPkKey = FMetaField->IsPkKey;
   this->EditMask = FMetaField->EditMask;
   this->Name = FMetaField->FieldName;
   this->DisplayName = FMetaField->FieldName;
   this->DisplayLabel = FMetaField->DisplayLabel;
   this->DisplayFormat = FMetaField->DisplayFormat;
   this->DisplayWidth = FMetaField->Size;
   this->Size = FMetaField->Size;
   this->IsMoney = FMetaField->IsMoney;
}
//---------------------------------------------------------------------------
TSfgFieldDef* CreateFieldDef(TSfgMetaField *MetaField, TDataSet *DataSet)
{
   TSfgFieldDef *FieldDef = new TSfgFieldDef(DataSet->FieldDefs,MetaField->FieldName,MetaField->DataType,MetaField->Size, DataSet->FieldDefs->Count+1);
   FieldDef->MetaField = MetaField;
   return FieldDef;
}
//---------------------------------------------------------------------------
TSfgFieldDef* CopyFieldDef(TField *Field, TDataSet *DataSet)
{
   TSfgFieldDef *FieldDef = new TSfgFieldDef(DataSet->FieldDefs,Field->FieldName,Field->DataType,Field->Size, DataSet->FieldDefs->Count+1);
   if (Field->Tag > 0) {
      FieldDef->MetaField = (TSfgMetaField*)Field->Tag;
   } else {
      FieldDef->MetaField = NULL;
      FieldDef->IsPkKey = Field->ProviderFlags.Contains(pfInKey);
      FieldDef->EditMask = Field->EditMask;
      FieldDef->Name = (Field->Origin.Length() > 0) ? Field->Origin : Field->FieldName;
      FieldDef->DisplayName = Field->FieldName;
      FieldDef->DisplayLabel = Field->DisplayLabel;
      FieldDef->DisplayWidth = Field->DisplayWidth;
      if (Field->InheritsFrom(__classid(TNumericField)))
         FieldDef->DisplayFormat = ((TNumericField*)Field)->DisplayFormat;
      if (Field->InheritsFrom(__classid(TDateTimeField)))
         FieldDef->DisplayFormat = ((TDateTimeField*)Field)->DisplayFormat;
      if (Field->InheritsFrom(__classid(TFloatField)))
         FieldDef->Precision = ((TFloatField*)Field)->Precision;
      else
         FieldDef->Precision = 0;
   }
   FieldDef->Visible = Field->Visible;
   return FieldDef;
}
//---------------------------------------------------------------------------
#include "EnumTypeInfo.h"
DECLARE_ENUM_TYPEINFO(TFieldType);
// Pode Receber um ARRAY de Strings concatenado por |
// Estas podem estar nomeadas indicando as proprieades, ou então
// Devem estar ordenadas seguindo a orderm:
// FieldName,DataType,Size,DisplayLabel,IsPkKey,Visible,DisplayWidth,Precision,EditMask,DisplayFormat
TFieldDefs* CreateFieldDefs(DynamicArray<String> AFieldDefs, TDataSet *DataSet)
{
   int i, j;
   String StrFieldDef;
   TSfgFieldDef *FieldDef = NULL;
   TStrings *AFieldDef = new TStringList();
   PTypeInfo pTypeInfo = GET_ENUM_TYPEINFO(TFieldType);

   for(i = 0; i < AFieldDefs.Length; i++) {
      AFieldDef->Clear();
      StrFieldDef = StringReplace(AFieldDefs[i], "|", "\r\n", TReplaceFlags()<<rfReplaceAll);
      AFieldDef->Text = StrFieldDef;
      //Valida para verificar se recebeu as strings nomeadas
      FieldDef = new TSfgFieldDef(DataSet->FieldDefs, "", ftUnknown, 0, DataSet->FieldDefs->Count+1);
      FieldDef->MetaField = NULL;
      if (AFieldDef->Count > 0 && AFieldDef->Names[0].Length() > 0) {
         for(j = 0; j < AFieldDef->Count; j++) {
            if (AFieldDef->Names[j] == "FieldName") {
               FieldDef->Name = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "DataType") {
               FieldDef->DataType = (TFieldType)GetEnumValue(pTypeInfo,AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Size") {
               FieldDef->Size = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "DisplayLabel") {
               FieldDef->DisplayLabel = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "IsPkKey") {
               FieldDef->IsPkKey = StrToBool(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Visible") {
               FieldDef->Visible = StrToBool(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "DisplayWidth") {
               FieldDef->DisplayWidth = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Precision") {
               FieldDef->Precision = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "EditMask") {
               FieldDef->EditMask = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "DisplayFormat") {
               FieldDef->DisplayFormat = AFieldDef->Values[j];
            }
         }
      } else {
         for(j = 0; j < AFieldDef->Count; j++) {
            switch(j) {
               case 0:
                  FieldDef->Name = AFieldDef->Strings[j];
                  break;
               case 1:
                  FieldDef->DataType = (TFieldType)GetEnumValue(pTypeInfo,AFieldDef->Strings[j]);
                  break;
               case 2:
                  FieldDef->Size = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 3:
                  FieldDef->DisplayLabel = AFieldDef->Strings[j];
                  break;
               case 4:
                  FieldDef->IsPkKey = StrToBool(AFieldDef->Strings[j]);
                  break;
               case 5:
                  FieldDef->Visible = StrToBool(AFieldDef->Strings[j]);
                  break;
               case 6:
                  FieldDef->DisplayWidth = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 7:
                  FieldDef->Precision = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 8:
                  FieldDef->EditMask = AFieldDef->Strings[j];
                  break;
               case 9:
                  FieldDef->DisplayFormat = AFieldDef->Strings[j];
                  break;
               default:
                  break;
            }
         }
      }
      if (FieldDef->DisplayWidth == 0)
         FieldDef->DisplayWidth = FieldDef->Size;
   }

   return DataSet->FieldDefs;
}
//---------------------------------------------------------------------------
// Pode receber uma listagem de campos concatenado por ; em FieldNames
TFieldDefs* CreateFieldDefs(TSfgMetaTable *MetaTable, String FieldNames, TDataSet *DataSet)
{
   TSfgFieldDef *FieldDef = NULL;
   TSfgMetaField *MetaField = NULL;
   String FieldName;
   int iPos = 1;

   while (iPos <= FieldNames.Length()) {
      FieldName = ExtractFieldName(FieldNames,iPos);
      MetaField = (TSfgMetaField*)MetaTable->FindComponent(FieldName);
      if (MetaField != NULL) {
         FieldDef = new TSfgFieldDef(DataSet->FieldDefs, MetaField->FieldName, MetaField->DataType, MetaField->Size, DataSet->FieldDefs->Count+1);
         FieldDef->MetaField = MetaField;
      } else {
         DatabaseErrorFmt(SMetaFieldNotFound, ARRAYOFCONST((FieldName,MetaTable->TableName)), DataSet);
      }
   }
   return DataSet->FieldDefs;
}
//---------------------------------------------------------------------------
TFieldDefs* CreateFieldDefs(String TableName, String FieldNames, TDataSet *DataSet)
{
   TSfgMetaTable* MetaTable = GetMetaTable(TableName);
   if (MetaTable != NULL)
      CreateFieldDefs(MetaTable, FieldNames, DataSet);
   return DataSet->FieldDefs;
}
//---------------------------------------------------------------------------
TFields* CreateFields(TDataSet *DataSet)
{
   for (int i = 0; i < DataSet->FieldDefs->Count; i++) {
      CreateField((TSfgFieldDef*)DataSet->FieldDefs->Items[i]);
   }
   return DataSet->Fields;
}
//---------------------------------------------------------------------------
TField* CreateField(TSfgFieldDef *FieldDef)
{
   TDataSet *DataSet = ((TFieldDefs*)FieldDef->Collection)->DataSet;
   TField *Field = FieldDef->CreateField(DataSet);
   Field->FieldName = FieldDef->Name;
   Field->DisplayLabel = FieldDef->DisplayLabel;
   Field->Size = FieldDef->Size;
   Field->EditMask = FieldDef->EditMask;
   Field->DisplayWidth = FieldDef->DisplayWidth;
   Field->Visible = FieldDef->Visible;
   if (FieldDef->IsPkKey)
      Field->ProviderFlags = TProviderFlags() << pfInKey << pfInWhere;
   else
      Field->ProviderFlags = TProviderFlags() << pfInUpdate;
   if (Field->InheritsFrom(__classid(TNumericField))) {
      ((TNumericField*)Field)->DisplayFormat = FieldDef->DisplayFormat;
   }
   if (Field->InheritsFrom(__classid(TDateTimeField))) {
      ((TDateTimeField*)Field)->DisplayFormat = FieldDef->DisplayFormat;
   }
   if (Field->InheritsFrom(__classid(TFloatField))) {
      //((TFloatField*)Field)->Precision = FieldDef->Precision;
      ((TFloatField*)Field)->currency = FieldDef->IsMoney;
   }
   if (FieldDef->MetaField != NULL)
      Field->Tag = (long)FieldDef->MetaField;
   Field->DataSet = DataSet;
   return Field;
}
//---------------------------------------------------------------------------
DECLARE_ENUM_TYPEINFO(TFieldKind);
// Pode Receber um ARRAY de Strings concatenado por |
// Estas podem estar nomeadas indicando as proprieades, ou então
// Devem estar ordenadas seguindo a orderm:
// FieldKind,FieldName,DataType,Size,DisplayLabel,IsPkKey,Visible,DisplayWidth,Precision,EditMask,DisplayFormat
TFields* AddVirtualFields(DynamicArray<String> AFieldDefs, TDataSet *DataSet, bool CreateFields)
{
   int i, j;
   String StrFieldDef;
   TSfgFieldDef *FieldDef = NULL;
   TStrings *AFieldDef = new TStringList();
   TFieldKind FieldKind;
   PTypeInfo pTypeInfo = GET_ENUM_TYPEINFO(TFieldType);
   PTypeInfo pKindInfo = GET_ENUM_TYPEINFO(TFieldKind);

   for(i = 0; i < AFieldDefs.Length; i++) {
      AFieldDef->Clear();
      StrFieldDef = StringReplace(AFieldDefs[i], "|", "\r\n", TReplaceFlags()<<rfReplaceAll);
      AFieldDef->Text = StrFieldDef;
      //Valida para verificar se recebeu as strings nomeadas
      FieldDef = new TSfgFieldDef(DataSet->FieldDefs, "", ftUnknown, 0, DataSet->FieldDefs->Count+1);
      FieldDef->MetaField = NULL;
      FieldKind = fkCalculated;
      if (AFieldDef->Count > 0 && AFieldDef->Names[0].Length() > 0) {
         for(j = 0; j < AFieldDef->Count; j++) {
            if (AFieldDef->Names[j] == "FieldKind") {
               FieldKind = (TFieldKind)GetEnumValue(pKindInfo,AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "FieldName") {
               FieldDef->Name = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "DataType") {
               FieldDef->DataType = (TFieldType)GetEnumValue(pTypeInfo,AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Size") {
               FieldDef->Size = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "DisplayLabel") {
               FieldDef->DisplayLabel = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "IsPkKey") {
               FieldDef->IsPkKey = StrToBool(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Visible") {
               FieldDef->Visible = StrToBool(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "DisplayWidth") {
               FieldDef->DisplayWidth = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "Precision") {
               FieldDef->Precision = StrToInt(AFieldDef->Values[j]);
            } else
            if (AFieldDef->Names[j] == "EditMask") {
               FieldDef->EditMask = AFieldDef->Values[j];
            } else
            if (AFieldDef->Names[j] == "DisplayFormat") {
               FieldDef->DisplayFormat = AFieldDef->Values[j];
            }
         }
      } else {
         for(j = 0; j < AFieldDef->Count; j++) {
            switch(j) {
               case 0:
                  FieldKind = (TFieldKind)GetEnumValue(pKindInfo,AFieldDef->Strings[j]);
                  break;
               case 1:
                  FieldDef->Name = AFieldDef->Strings[j];
                  break;
               case 2:
                  FieldDef->DataType = (TFieldType)GetEnumValue(pTypeInfo,AFieldDef->Strings[j]);
                  break;
               case 3:
                  FieldDef->Size = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 4:
                  FieldDef->DisplayLabel = AFieldDef->Strings[j];
                  break;
               case 5:
                  FieldDef->IsPkKey = StrToBool(AFieldDef->Strings[j]);
                  break;
               case 6:
                  FieldDef->Visible = StrToBool(AFieldDef->Strings[j]);
                  break;
               case 7:
                  FieldDef->DisplayWidth = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 8:
                  FieldDef->Precision = StrToInt(AFieldDef->Strings[j]);
                  break;
               case 9:
                  FieldDef->EditMask = AFieldDef->Strings[j];
                  break;
               case 10:
                  FieldDef->DisplayFormat = AFieldDef->Strings[j];
                  break;
               default:
                  break;
            }
         }
      }
      if (FieldDef->DisplayWidth == 0)
         FieldDef->DisplayWidth = FieldDef->Size;
      if (CreateFields)
         CreateField(FieldDef)->FieldKind = FieldKind;
   }

   return DataSet->Fields;
}
//---------------------------------------------------------------------------
TSfgMetaTable* AddMetaTable(String TableName)
{
   if (AppMetaTables == NULL) {
      AppMetaTables = new TSfgMetaTables();
      AppMetaTables->Duplicates = dupError;
      AppMetaTables->Sorted = false;
   }
   int Index = AppMetaTables->IndexOf(TableName);
   TSfgMetaTable* ReturnTable = NULL;
   if (Index >= 0) {
      ReturnTable = (TSfgMetaTable*)AppMetaTables->Objects[Index];
   } else {
      ReturnTable = new TSfgMetaTable(Application);
      ReturnTable->TableName = TableName;
      AppMetaTables->AddObject(TableName, ReturnTable);
   }
   return ReturnTable;
}
//---------------------------------------------------------------------------
TSfgMetaTable* AddMetaTable(TSfgMetaTable *MetaTable)
{
   if (AppMetaTables == NULL) {
      AppMetaTables = new TSfgMetaTables();
      AppMetaTables->Duplicates = dupError;
      AppMetaTables->Sorted = false;
   }
   int Index = AppMetaTables->IndexOf(MetaTable->TableName);
   TSfgMetaTable* ReturnTable = NULL;
   if (Index >= 0) {
      String MsgErro = "Tabela '" + MetaTable->TableName + "' já adicionada ao dicionário de dados.";
      throw Exception(MsgErro);
   } else {
      ReturnTable = MetaTable;
      AppMetaTables->AddObject(MetaTable->TableName, ReturnTable);
   }
   return ReturnTable;
}
//---------------------------------------------------------------------------
TSfgMetaTable* GetMetaTable(String TableName)
{
   if (AppMetaTables == NULL)
      return NULL;

   int Index = AppMetaTables->IndexOf(TableName);
   if (Index >= 0)
      return (TSfgMetaTable*)AppMetaTables->Objects[Index];
   else
      return NULL;
}
//---------------------------------------------------------------------------

