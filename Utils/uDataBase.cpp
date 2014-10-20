//---------------------------------------------------------------------------
#include "uDataModule.h"
#pragma hdrstop
#include "uDataBase.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//-------------------------------------------------------------------
bool ExistDatabase(String DatabaseName) {
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
	QyCt->SQL->Text = "SHOW DATABASES LIKE " + QuotedStr(DatabaseName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTable(String TableName) {
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW TABLES FROM " + AppConnection->Database + " LIKE " + QuotedStr(TableName);
   QyCt->SQL->Text = "\
SELECT table_name\
  FROM information_schema.tables\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(TableName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTableColumn(String TableName, String ColumnName) {
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW COLUMNS FROM " + TableName + " WHERE `Field` = " + QuotedStr(ColumnName);
   QyCt->SQL->Text = "\
SELECT table_name\
  FROM information_schema.columns\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(TableName) + "\
   AND column_name = " + QuotedStr(ColumnName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTablePrimaryKey(String TableName)
{
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW INDEXES FROM " + TableName + " WHERE key_name = 'PRIMARY'";
   QyCt->SQL->Text = "\
SELECT constraint_name\
  FROM information_schema.table_constraints\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(TableName) + "\
   AND constraint_type = 'PRIMARY KEY'";
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTableForeignKey(String TableName, String ForeignKeyName)
{
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
   QyCt->SQL->Text = "\
SELECT constraint_name\
  FROM information_schema.table_constraints\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(TableName) + "\
   AND constraint_schema = " + QuotedStr(AppConnection->Database) + "\
   AND constraint_name = " + QuotedStr(ForeignKeyName) + "\
   AND constraint_type = 'FOREIGN KEY'";
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTableIndex(String TableName, String IndexName)
{
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW INDEXES FROM " + TableName + " WHERE key_name = " + QuotedStr(IndexName);
   QyCt->SQL->Text = "\
SELECT index_name\
  FROM information_schema.statistics\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(TableName) + "\
   AND index_schema = " + QuotedStr(AppConnection->Database) + "\
   AND index_name = " + QuotedStr(IndexName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistTableTrigger(String TableName, String TriggerName)
{
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "\
// SHOW TRIGGERS FROM " + AppConnection->Database + 
//WHERE `Table` = " + QuotedStr(TableName) + "\
//  AND `Trigger` = " + QuotedStr(TriggerName);
   QyCt->SQL->Text = "\
SELECT trigger_name\
  FROM information_schema.triggers\
 WHERE event_object_schema = " + QuotedStr(AppConnection->Database) + "\
   AND event_object_table = " + QuotedStr(TableName) + "\
   AND trigger_schema = " + QuotedStr(AppConnection->Database) + "\
   AND trigger_name = " + QuotedStr(TriggerName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistProcedure(String ProcedureName) {
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW PROCEDURE STATUS WHERE db = " + QuotedStr(AppConnection->Database) + " AND name = " + QuotedStr(ProcedureName);
   QyCt->SQL->Text = "\
SELECT specific_name\
  FROM information_schema.routines\
 WHERE routine_schema = " + QuotedStr(AppConnection->Database) + "\
   AND routine_name = " + QuotedStr(ProcedureName) + "\
   AND routine_type = 'PROCEDURE'";
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------
bool ExistView(String ViewName)
{
	bool bRet = false;
	TZQuery *QyCt = new TZQuery(Application);
try {
//   QyCt->SQL->Text = "SHOW CREATE VIEW + QuotedStr(ViewName);
   QyCt->SQL->Text = "\
SELECT table_name\
  FROM information_schema.views\
 WHERE table_schema = " + QuotedStr(AppConnection->Database) + "\
   AND table_name = " + QuotedStr(ViewName);
	QyCt->Connection = AppConnection;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		bRet = true;
	}
} catch (...) {
	delete(QyCt);
}
   return bRet;
}
//-------------------------------------------------------------------


