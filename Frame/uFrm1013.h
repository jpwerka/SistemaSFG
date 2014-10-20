/*
Módulo: Framework SoftGreen
Função: Processa Atualização Metadados dos Sistema
Autor.: Jackson Patrick Werka
Data..: 18/01/2013
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1013H
#define uFrm1013H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include <ExtCtrls.hpp>
#include "uFormBase01.h"
#include "uSfgToolbar.h"
#include <DBCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrm1013 : public TfrmBase02
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TLabel *Label1;
   TDBEdit *table_name;
   TDBGrid *grdFields;
   TLabel *Label2;
   TZQuery *QyTables;
   TLabel *Label3;
   TDBEdit *table_type;
   TDataSource *DsTables;
   TZQuery *QyMetaFields;
   TStringField *QyMetaFieldstable_name;
   TStringField *QyMetaFieldscolumn_name;
   TIntegerField *QyMetaFieldscolumn_order;
   TStringField *QyMetaFieldscolumn_typename;
   TIntegerField *QyMetaFieldscolumn_size;
   TIntegerField *QyMetaFieldscolumn_precision;
   TStringField *QyMetaFieldscolumn_ispkkey;
   TStringField *QyMetaFieldscolumn_isnull;
   TStringField *QyMetaFieldscolumn_isindex;
   TStringField *QyMetaFieldscolumn_isfkkey;
   TStringField *QyMetaFieldsfk_table_name;
   TStringField *QyMetaFieldsfk_column_name;
   TStringField *QyMetaFieldscolumn_label;
   TStringField *QyMetaFieldscolumn_editmask;
   TStringField *QyMetaFieldscolumn_checkvalues;
   TStringField *QyMetaFieldsmore_fkkey;
   TDataSource *DsMetaFields;
   TStringField *QyMetaFieldscolumn_datatype2;
   TStringField *QyMetaFieldscolumn_isbrowse;
   TStringField *QyMetaFieldscolumn_isserach;
   TStringField *QyMetaFieldscolumn_orderb;
   TStringField *QyMetaFieldscolumn_orders;
   TStringField *QyMetaFieldscolumn_editcmp;
   TStringField *QyMetaFieldscolumn_isfklist;
   TStringField *QyMetaFieldscolumn_ismoney;
   TZQuery *QyAddFields;
   TStringField *QyMetaFieldscolumn_format;
   void __fastcall QyTablesAfterOpen(TDataSet *DataSet);
   void __fastcall QyMetaFieldsCalcFields(TDataSet *DataSet);
   void __fastcall QyMetaFieldsBeforeInsert(TDataSet *DataSet);
   void __fastcall BtEditClickExecute(TObject *Sender);
   void __fastcall BtSaveClickExecute(TObject *Sender);
   void __fastcall BtCancelClickExecute(TObject *Sender);
   void __fastcall grdFieldsKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall grdFieldsCellClick(TColumn *Column);
   void __fastcall grdFieldsColEnter(TObject *Sender);
   void __fastcall grdFieldsColExit(TObject *Sender);
   void __fastcall grdFieldsDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
   void __fastcall QyMetaFieldsAfterScroll(TDataSet *DataSet);
private:	// User declarations
   bool __fastcall CarregarMetadados();
   void __fastcall HabilitarItens(bool);
   bool __fastcall SalvaMetaFields();
   void __fastcall BeforeBrowse(TStrings *FromTables, String &TableBrowse);
   void __fastcall CarregarFkTables(TStrings *FKList);
public:		// User declarations
   __fastcall TFrm1013(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
