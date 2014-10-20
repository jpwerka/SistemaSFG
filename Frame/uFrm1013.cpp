/*
Módulo: Framework SoftGreen
Função: Processa Atualização Metadados dos Sistema
Autor.: Jackson Patrick Werka
Data..: 18/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uDataBase.h"
#include "uSfgDrawCmp.h"
#include "uSfgMetaData.h"
#pragma hdrstop
#include "uFrm1013.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*void RegisterFrm1013(void) {
   AddAppForm("Frm1013","Atualização Metadados");
   AddAppFormClass("TFrm1013",__classid(TFrm1013));
}
#pragma startup RegisterFrm1012*/
//---------------------------------------------------------------------------
__fastcall TFrm1013::TFrm1013(TComponent* Owner)
   : TfrmBase02(Owner)
{
   //Deve criar a tabela do metadados não mão (virtual)
   TSfgMetaTable *MetaTable = GetMetaTable("information_schema.tables");
   if (MetaTable == NULL) {
      TSfgMetaField *MetaField;
      MetaTable = new TSfgMetaTable(Application);
      MetaTable->TableName = "information_schema.tables";
      MetaField = new TSfgMetaField(MetaTable);
      MetaField->Name = "table_name";
      MetaField->FieldName = "table_name";
      MetaField->DisplayLabel = "Tabela";
      MetaField->IsPkKey = true;
      MetaField->DataType = ftString;
      MetaField->Size = 45;
      MetaField->IsBrowse = true;
      MetaField->IsSearch = true;
      MetaField->Order.InBrowse = true;
      MetaField->Order.InSearch = true;
      MetaField->EditCmp = smeMaskEdit;
      MetaField = new TSfgMetaField(MetaTable);
      MetaField->Name = "table_type";
      MetaField->FieldName = "table_type";
      MetaField->DisplayLabel = "Tipo";
      MetaField->IsPkKey = false;
      MetaField->IsIndex = true;
      MetaField->DataType = ftString;
      MetaField->Size = 30;
      MetaField->IsBrowse = true;
      MetaField->IsSearch = true;
      MetaField->Order.InBrowse = true;
      MetaField->Order.InSearch = true;
      MetaField->EditCmp = smeMaskEdit;
      AddMetaTable(MetaTable);
   }
   CreateFieldDefs(MetaTable,"table_name;table_type;",QyTables);
   CreateFields(QyTables);
   CarregarMetadados();
   SfgToolbar->DataSource = DsTables;
   SfgToolbar->BeforeBrowse = &BeforeBrowse;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1013::CarregarMetadados()
{
   bool bRet = true;
   TZQuery *QyEcexAtuDB = new TZQuery(Application);
   QyEcexAtuDB->Connection = AppConnection;
try {
   try {
      //Deve fazer assim para não fazer o PARSER do ZEOS
      QyEcexAtuDB->ParamCheck = false;
      QyEcexAtuDB->SQL->Text = "call carrega_metadados()";
      QyEcexAtuDB->ExecSQL();
   }
   catch (Exception &e) {
      String Msg = "Ocorreu o seguinte erro a efetuar a carga do metadados do sistema:\n" +\
                    e.Message;
      MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",MB_OK | MB_ICONSTOP);
      bRet = false;
   }
}__finally {
   delete(QyEcexAtuDB);
}
   return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::BeforeBrowse(TStrings *FromTables, String &TableBrowse)
{
   FromTables->Strings[0] = "information_schema.tables";
   TableBrowse = "information_schema.tables WHERE table_schema = DATABASE()";
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::QyTablesAfterOpen(TDataSet *DataSet)
{
   QyMetaFields->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::QyMetaFieldsCalcFields(TDataSet *DataSet)
{
   //Aqui deve atualizar os campos da tela que são baseados nas propriedades
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::grdFieldsKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::QyMetaFieldsBeforeInsert(TDataSet *DataSet)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::HabilitarItens(bool Habilita)
{
   TDBGridOptions DbOptions = grdFields->Options;
   if (Habilita)
      DbOptions << dgEditing;
   else
      DbOptions >> dgEditing;
   //Deve habilitar o GRID para fazer edição
   DsMetaFields->AutoEdit = Habilita;
   grdFields->Options = DbOptions;
   SfgToolbar->EnableToolbarButtons(!Habilita);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::BtEditClickExecute(TObject *Sender)
{
   HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::BtSaveClickExecute(TObject *Sender)
{
   String sMsg;
   bool bSucesso = true;
   //Deve salvar as alterações no GRID
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	try {
		if (SalvaMetaFields())
         QyMetaFields->ApplyUpdates();
	}
	catch(Exception &e){
		sMsg = "Ocorreu um erro ao salvar as alterações nas comissões do representante:\n";
		sMsg = sMsg + e.Message;
		bSucesso = false;
	}
	if (bSucesso) {
		SfgDataCenter->CommitTrans();
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,sMsg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
   HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::BtCancelClickExecute(TObject *Sender)
{
   HabilitarItens(false);
   QyMetaFields->CancelUpdates();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1013::SalvaMetaFields()
{
   int ColumnProp, ColumnEditCmp;
   String StrEditCmp;
   TZQuery *QyDelFields = new TZQuery(Application);
   QyDelFields->Connection = AppConnection;
   QyDelFields->SQL->Text = "DELETE FROM tbl_meta_fiedls WHERE table_name = " + QuotedStr(table_name->Text);
   QyDelFields->ExecSQL();
   delete QyDelFields;

	QyMetaFields->DisableControls();  //Para desativar a atualização da tela
	QyMetaFields->First();
	while (!QyMetaFields->Eof) {
      StrEditCmp = QyMetaFields->FieldByName("column_editcmp")->AsString;
      if (StrEditCmp == "ComboBox") {
         ColumnEditCmp = (int)smeComboBox;
      } else
      if (StrEditCmp == "CheckBox") {
         ColumnEditCmp = (int)smeCheckBox;
      } else {
         ColumnEditCmp = (int)smeMaskEdit;
      }
      ColumnProp = 0;
      if (QyMetaFields->FieldByName("column_ispkkey")->AsString == "S")
         ColumnProp |= FD_PKKEY;
      if (QyMetaFields->FieldByName("column_isnull")->AsString == "N")
         ColumnProp |= FD_NOTNULL;
      if (QyMetaFields->FieldByName("column_isindex")->AsString == "S")
         ColumnProp |= FD_INDEX;
      if (QyMetaFields->FieldByName("column_isfkkey")->AsString == "S")
         ColumnProp |= FD_FKKEY;
      if (QyMetaFields->FieldByName("column_isbrowse")->AsString == "S")
         ColumnProp |= FD_BROWSE;
      if (QyMetaFields->FieldByName("column_issearch")->AsString == "S")
         ColumnProp |= FD_SEARCH;
      if (QyMetaFields->FieldByName("column_orderb")->AsString == "S")
         ColumnProp |= FD_ORDERB;
      if (QyMetaFields->FieldByName("column_orders")->AsString == "S")
         ColumnProp |= FD_ORDERS;
      if (QyMetaFields->FieldByName("column_fklist")->AsString == "S")
         ColumnProp |= FD_FKLIST;
      if (QyMetaFields->FieldByName("column_ismoney")->AsString == "S")
         ColumnProp |= FD_MONEY;
      QyAddFields->ParamByName("table_name")->AsString = QyMetaFields->FieldByName("table_name")->AsString;
      QyAddFields->ParamByName("column_order")->AsInteger = QyMetaFields->FieldByName("column_order")->AsInteger;
      QyAddFields->ParamByName("column_name")->AsString = QyMetaFields->FieldByName("column_name")->AsString;
      QyAddFields->ParamByName("column_label")->AsString = QyMetaFields->FieldByName("column_label")->AsString;
      QyAddFields->ParamByName("column_datatype")->AsString = QyMetaFields->FieldByName("column_datatype")->AsString;
      QyAddFields->ParamByName("column_typename")->AsString = QyMetaFields->FieldByName("column_typename")->AsString;
      QyAddFields->ParamByName("column_size")->AsInteger = QyMetaFields->FieldByName("column_size")->AsInteger;
      QyAddFields->ParamByName("column_precision")->AsInteger = QyMetaFields->FieldByName("column_precision")->AsInteger;
      QyAddFields->ParamByName("column_properties")->AsInteger = ColumnProp;
      QyAddFields->ParamByName("fk_table_name")->Value = QyMetaFields->FieldByName("fk_table_name")->Value;
      QyAddFields->ParamByName("fk_column_name")->Value = QyMetaFields->FieldByName("fk_column_name")->Value;
      QyAddFields->ParamByName("column_editcmp")->AsInteger = ColumnEditCmp;
      QyAddFields->ParamByName("column_editmask")->Value = QyMetaFields->FieldByName("column_editmask")->Value;
      QyAddFields->ParamByName("column_format")->Value = QyMetaFields->FieldByName("column_format")->Value;
      QyAddFields->ParamByName("column_checkvalues")->Value = QyMetaFields->FieldByName("column_checkvalues")->Value;
      QyAddFields->ExecSQL();

      QyMetaFields->Next();
   }
   QyMetaFields->First();
   QyMetaFields->EnableControls(); //Para ativar a atualização da tela
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::grdFieldsCellClick(TColumn *Column)
{
   if (!DsMetaFields->AutoEdit)
      return;
	if ((Column->Field->FieldName == "column_isbrowse") ||
       (Column->Field->FieldName == "column_orderb") ||
       (Column->Field->FieldName == "column_issearch") ||
       (Column->Field->FieldName == "column_orders") ||
       (Column->Field->FieldName == "column_fklist") ||
       (Column->Field->FieldName == "column_ismoney")) {
		QyMetaFields->Edit();
		if (Column->Field->AsString == "S") {
			Column->Field->AsString = "N";
		} else {
			Column->Field->AsString = "S";
		}
		QyMetaFields->Post();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::grdFieldsColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdFields->SelectedField->DataType == ftString && grdFields->SelectedField->Size == 1) {
		Options = grdFields->Options;
		Options >> dgEditing;
		grdFields->Options = Options;
	} else
   if (grdFields->SelectedField->FieldName == "fk_table_name") {
      grdFields->Columns->Items[grdFields->SelectedIndex]->PickList->Clear();
      if (QyMetaFields->FieldByName("more_fkkey")->AsString == "S")
         CarregarFkTables(grdFields->Columns->Items[grdFields->SelectedIndex]->PickList);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::grdFieldsColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (grdFields->SelectedField->DataType == ftString && grdFields->SelectedField->Size == 1) {
		Options = grdFields->Options;
		Options << dgEditing;
		grdFields->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::grdFieldsDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->DataType == ftString && Column->Field->Size == 1) {
		bool bChecked = Column->Field->AsString == "S";
		DrawCheckBoxGrid(grdFields,-1,-1,Rect,State,bChecked);
	} else
   if ((Column->Field->FieldName == "fk_table_name") &&
       (QyMetaFields->FieldByName("more_fkkey")->AsString == "S")) {
      grdFields->Canvas->Brush->Color = clRed;
      grdFields->Canvas->FillRect(Rect);
      grdFields->Canvas->TextOut(Rect.left + 2, Rect.top + 2,Column->Field->AsString);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1013::CarregarFkTables(TStrings *FKList)
{
   TZQuery *QyFkTables = new TZQuery(Application);
   QyFkTables->Connection = AppConnection;
   QyFkTables->SQL->Text = "\
SELECT referenced_table_name\
  FROM information_schema.key_column_usage fk\
 WHERE fk.table_schema = DATABASE()\
   AND fk.constraint_name != 'PRIMARY'\
   and fk.table_name = " + QuotedStr(QyMetaFields->FieldByName("table_name")->AsString) + "\
   AND fk.column_name = " + QuotedStr(QyMetaFields->FieldByName("column_name")->AsString) + "\
 ORDER BY fk.referenced_table_name";
   QyFkTables->Active = true;
   QyFkTables->First();
   while (!QyFkTables->Eof) {
      FKList->Add(QyFkTables->FieldByName("referenced_table_name")->AsString);
      QyFkTables->Next();
   }
 }
//---------------------------------------------------------------------------
void __fastcall TFrm1013::QyMetaFieldsAfterScroll(TDataSet *DataSet)
{
   if (grdFields->SelectedField->FieldName == "fk_table_name") {
      grdFields->Columns->Items[grdFields->SelectedIndex]->PickList->Clear();
      if (QyMetaFields->FieldByName("more_fkkey")->AsString == "S")
         CarregarFkTables(grdFields->Columns->Items[grdFields->SelectedIndex]->PickList);
   }
}
//---------------------------------------------------------------------------



