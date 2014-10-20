//---------------------------------------------------------------------------
#include "uDataModule.h"
#include "uDataBase.h"
#pragma hdrstop
#include "uAtualizaDB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//-------------------------------------------------------------------
bool AtualizaBD00001() {
   int pos, cmd;
   TStringStream *CmdStream;
   TStringStream *StrStream = new TStringStream("");
	HRSRC HrSql = FindResource(HInstance, "ATUDB00001", RT_RCDATA);
	HGLOBAL SqlData = LoadResource(HInstance, HrSql);
	DWORD szbf = SizeofResource(HInstance, HrSql);
   String StrScript;
   bool ret = true;

   StrStream->Write(SqlData,szbf);
   StrStream->Seek(0, soFromBeginning);
   StrScript = StrStream->DataString;
   delete StrStream;

	TZQuery *QyCt = new TZQuery(Application);
	QyCt->Connection = SfgDataCenter->AppConnection;
try {
/*
Os comandos do arquivo estão dispostos na seguinte ordem
O separador de cada comando é um pipe |
01 - CREATE TABLE tbl_grupo
02 - CREATE TABLE tbl_usuario_grupo
     ADD CONSTRAINT fk1_usuario_grupo
     ADD CONSTRAINT fk2_usuario_grupo
03 - CREATE TABLE tbl_menu_sistema
04 - CREATE TABLE tbl_permissao_usuario_grupo
     ADD CONSTRAINT fk1_perm_user_grupo
05 - CREATE PROCEDURE carrega_permissao_menu
06 - CREATE PROCEDURE modifica_permissao_menu
07 - ALTER TABLE tbl_usuario
08 - UPDATE tbl_usuario
*/
   //Deve separar cada comando e executar cada um deles
   pos = StrScript.Pos("|");
   cmd = 0;
   while (pos > 0) {
      CmdStream = new TStringStream("");
      CmdStream->Write(StrScript.data(), pos-1);
      CmdStream->Seek(0, soFromBeginning);
	   QyCt->SQL->LoadFromStream(CmdStream);
      delete CmdStream;
      cmd++;
      try {
         switch(cmd) {
            case 1:
               if(!ExistTable("tbl_grupo"))
	               QyCt->ExecSQL();
               break;
            case 2:
               if(!ExistTable("tbl_usuario_grupo"))
	               QyCt->ExecSQL();
               break;
            case 3:
               if(!ExistTable("tbl_menu_sistema"))
	               QyCt->ExecSQL();
               break;
            case 4:
               if(!ExistTable("tbl_permissao_usuario_grupo"))
	               QyCt->ExecSQL();
               break;
            case 5:
               if(!ExistProcedure("carrega_permissao_menu"))
	               QyCt->ExecSQL();
               break;
            case 6:
               if(!ExistProcedure("modifica_permissao_menu"))
	               QyCt->ExecSQL();
               break;
            default:
               QyCt->ExecSQL();
         }
		}
		catch (Exception &e) {
         String Msg = "Ocorreu o seguinte erro:\n" +\
                       e.Message +\
                       "\nAo executar o comando de ordem " + IntToStr(cmd) + \
                       " da atualização 00001";
			MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",MB_OK | MB_ICONSTOP);
         ret = false;
		}
      if (!ret) break;
      //Procura pelo próximo comando, desconsiderando o | + '\r\n'
      StrScript = StrScript.SubString(pos+3,StrScript.Length()-pos-2);
      pos = StrScript.Pos("|");
   }
}__finally {
	delete(QyCt);
}
   return ret;
}
//-------------------------------------------------------------------
bool ValidaEstruturaDB()
{
   String Msg;
   if (!ExistTableColumn("tbl_usuario","ies_administrador")) {
      Msg = "A versão do seu banco de dados precisa ser atualizada!\n\n"
            "Entre em contato com a pessoa responsável pelo sistema para\n"
            "a mesma efetuar esta atualização ou confirme para atualizar.\n\n"
            "Antes de atualizar o seu banco de dados não será possível\n"
            "utilizar esta versão do sistema.\n\n"
            "Confirma a atualização do seu banco de dados?";
      if (MessageBox(NULL,Msg.c_str(),"Atualizar Sistema - Versão 00001",
         MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO) {
         return false;
      } else {
         if (!AtualizaBD00001()) return false;
      }
   }
   return true;
}

