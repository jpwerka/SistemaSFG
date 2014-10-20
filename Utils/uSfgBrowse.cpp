//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgToolTip.h"
#include "uDataModule.h"
#include "uSfgDrawCmp.h"
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uSfgBrowse.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TfrmBrowse::TfrmBrowse(TComponent* Owner)
        : TForm(Owner)
{
   this->FSQL = "";
   this->FFieldsKey = NULL;
   this->OnBrowseReturn = NULL;
   Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
   Tolltips->CreateToolTips();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::FormClose(TObject *Sender,
      TCloseAction &Action)
{
   delete Tolltips;
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::SetSQL(String Value)
{
   TField *Field = NULL;
   TSfgMetaField *MetaField = NULL;
   FSQL = Value;
   QyRegistros->SQL->Text = FSQL;
   QyRegistros->Active = true;
   CbOpcFiltro->Clear();
   CbOpcFiltro->AddItem("Sem filtro...",NULL);
   CbOpcFiltro->ItemIndex = 0;

   if (FFieldsKey != NULL)
      delete FFieldsKey;
   FFieldsKey = new TFields(QyRegistros);

   for(int i = 0; i < QyRegistros->Fields->Count; i++) {
      Field = QyRegistros->Fields->Fields[i];
      CbOpcFiltro->AddItem(Field->DisplayLabel,(TObject*)Field);
      if (Field->ProviderFlags.Contains(pfInKey))
         FFieldsKey->Add(Field);
      if (Field->Tag > 0) {
         MetaField = (TSfgMetaField*)Field->Tag;
         if (MetaField->EditCmp == smeCheckBox) {
            GrdRegistros->Columns->Items[Field->Index]->Alignment = taCenter;
            GrdRegistros->Columns->Items[Field->Index]->Title->Alignment = taCenter;
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::edtValorKeyPress(TObject *Sender, char &Key)
{
   if (bFloat) {
      Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
   } else {
      Validacoes::CharIsInteger(Key);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::CbOpcFiltroChange(TObject *Sender)
{
   int Index = CbOpcFiltro->ItemIndex;
   if (Index < 1) {
      edtValor->Enabled = false;
      edtValor->Color = AppConfig->Colors->Disabled;
      edtValor->Text = "";
      return;
   }
   edtValor->Enabled = true;
   edtValor->Color = AppConfig->Colors->Enabled;
   edtValor->Text = "";
   TField *Field = (TField*)CbOpcFiltro->Items->Objects[Index];
   if ((Field->DataType == ftString) ||
       (Field->DataType == ftWideString) ||
       (Field->DataType == ftFixedChar)) {
       edtValor->MaxLength = Field->Size;
   } else {
       edtValor->MaxLength = 0;
   }
   bFloat = false;
   edtValor->OnKeyPress = NULL;
   edtValor->EditMask = Field->EditMask;
   if ((Field->DataType == ftSmallint) ||
       (Field->DataType == ftWord) ||
       (Field->DataType == ftInteger) ||
       (Field->DataType == ftAutoInc) ||
       (Field->DataType == ftLargeint) ||
       (Field->DataType == ftBoolean )) {
      edtValor->OnKeyPress = &edtValorKeyPress;
   } else
   if ((Field->DataType == ftFloat) ||
       (Field->DataType == ftCurrency) ||
       (Field->DataType == ftBCD)) {
      bFloat = true;
      edtValor->OnKeyPress = &edtValorKeyPress;
   }
   cbCondicao->ItemIndex = 0;
   edtValor->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::BtCancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::BtOkClick(TObject *Sender)
{
   int i = 0;
   String sFindKey;
   Variant vFindKey;
   int Bounds[2] = {0,0};

   if (FFieldsKey->Count <= 0)
      return;
   //Deve fazer esta tratativa, pois se for somente um valor dá erro no ARRAY de variantes
   if (FFieldsKey->Count > 1) {
      Bounds[1] = FFieldsKey->Count - 1;
      vFindKey = VarArrayCreate(Bounds,1,varVariant);
      for (i = 0; i < FFieldsKey->Count; i++) {
         vFindKey.PutElement(FFieldsKey->Fields[i]->Value,i);
      }
   } else {
      vFindKey = FFieldsKey->Fields[0]->Value;
   }
   
   if (OnBrowseReturn != NULL) {
      OnBrowseReturn(vFindKey);
   }
   this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::GrdRegistrosDblClick(TObject *Sender)
{
   BtOkClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::btFiltrarClick(TObject *Sender)
{
   String Filter;
   String SQLFilter;
   String OrderBy;
   int iPosOrder;
   TField *Field;
   int i = CbOpcFiltro->ItemIndex;
   if (i < 0)
      return;
   if (i == 0) {
      QyRegistros->Active = false;
      QyRegistros->SQL->Text = this->SQL;
      QyRegistros->Active = true;
      return;
   }
   if  (edtValor->Text.Length() <= 0)
      return;

   Field = (TField*)CbOpcFiltro->Items->Objects[i];
   Filter = edtValor->Text;
   //Verifica se foi informado um filtro por '*' LIKE
   if (Filter.AnsiPos('*') > 0) {
      Filter = StringReplace(Filter,'*','%',TReplaceFlags() << rfReplaceAll);
      Filter = Field->FieldName + " LIKE " + QuotedStr(Filter);
   } else {
      Filter = Field->FieldName + cbCondicao->Text + QuotedStr(Filter);
   }
   //Esta opção seria um filtro cumulativo de valores
   //SQLFilter = QyRegistros->SQL->Text;
   SQLFilter = this->SQL;
   if (SQLFilter.Pos("WHERE") > 0) {
      Filter = " AND " + Filter;
   } else {
      Filter = " WHERE " + Filter;
   }
   iPosOrder = SQLFilter.Pos("ORDER BY");
   if (iPosOrder > 0) {
      OrderBy = SQLFilter.SubString(iPosOrder,SQLFilter.Length());
      SQLFilter = SQLFilter.SubString(0,iPosOrder-1);
   }
   SQLFilter = SQLFilter + '\r' + '\n' + Filter;
   if (iPosOrder > 0) {
      SQLFilter = SQLFilter + '\r' + '\n' + OrderBy;
   }
   QyRegistros->Active = false;
   QyRegistros->SQL->Text = SQLFilter;
   QyRegistros->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBrowse::GrdRegistrosDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
   //Deve verificar se a coluna é do tipo checkbox
   if (Column->Field->Tag > 0) {
      TSfgMetaField *MetaField = (TSfgMetaField*)Column->Field->Tag;
      if (MetaField->EditCmp == smeCheckBox) {
         bool bChecked = (bool)(VarToStr(Column->Field->Value) == MetaField->CheckValues.SubString(1,1));
         DrawCheckBoxGrid(GrdRegistros,-1,-1,Rect,State,bChecked);
      }
   }
}
//---------------------------------------------------------------------------
String GetBrowseSQL(String TableName, TDataSet *Source)
{
   String sSelect, sOrder;
   TSfgMetaTable *MetaTable = AddMetaTable(TableName);
   TSfgMetaField *MetaField = NULL;
   TSfgFieldDef *FieldDef = NULL;

   //Montando o SELECT a ser utilizado no BROWSE
   for(int i = 0; i < MetaTable->FieldCount; i++) {
      MetaField = MetaTable->MetaFields[i];

      if ((MetaField->IsPkKey) || (MetaField->IsBrowse)) {
         FieldDef = CreateFieldDef(MetaField,Source);
         if (!(MetaField->IsBrowse))
            FieldDef->Visible = false;
         if (sSelect.Length() > 0) {
            sSelect += "," + MetaField->FieldName;
         } else {
            sSelect = "SELECT " + MetaField->FieldName;
         }
         if (MetaField->Order.InBrowse) {
            if (sOrder.Length() > 0) {
               sOrder += "," + MetaField->FieldName;
            } else {
               sOrder = "ORDER BY " + MetaField->FieldName;
            }
         }
      }
   }
   return sSelect + " FROM " + TableName + " " + sOrder;
}
//---------------------------------------------------------------------------


