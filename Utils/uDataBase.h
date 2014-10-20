/*
Módulo: Utilidades
Função: Centralizar rotinas de consulta do modelo de dados.
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uDataBaseH
#define uDataBaseH
//---------------------------------------------------------------------------
extern PACKAGE bool ExistDatabase(String DatabaseName);
extern PACKAGE bool ExistTable(String TableName);
extern PACKAGE bool ExistTableColumn(String TableName, String ColumnName);
extern PACKAGE bool ExistTablePrimaryKey(String TableName);
extern PACKAGE bool ExistTableForeignKey(String TableName, String ForeignKeyName);
extern PACKAGE bool ExistTableIndex(String TableName, String IndexName);
extern PACKAGE bool ExistTableTrigger(String TableName, String TriggerName);
extern PACKAGE bool ExistProcedure(String ProcedureName);
extern PACKAGE bool ExistView(String ViewName);
#endif
