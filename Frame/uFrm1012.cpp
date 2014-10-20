/*
Módulo: Framework SoftGreen
Função: Processa Atualização Banco de Dados do Sistema
Autor.: Jackson Patrick Werka
Data..: 11/11/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uDataBase.h"
#include "uSfgDrawCmp.h"
#include "uFrm1013.h"
#pragma hdrstop
#include "uFrm1012.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
void RegisterFrm1012(void) {
   AddAppForm("Frm1012","Atualização Banco Dados");
   AddAppFormClass("TFrm1012",__classid(TFrm1012));
}
#pragma startup RegisterFrm1012
#define GRD_ACTION    2
#define GRD_TYPE      3
#define GRD_OBJECT    4
#define GRD_SUBACTION 5
#define GRD_SUBTYPE   6
#define GRD_SUBOBJECT 7
#define GRD_INFO      8
//---------------------------------------------------------------------------
typedef struct {
   String CmdSQL;
} SfgCmdSQLAtuDB;
//---------------------------------------------------------------------------
__fastcall TFrm1012::TFrm1012(TComponent* Owner)
   : TfrmBase01(Owner)
{
   if (!ExistTable("tbl_execucao_atualizacao")) {
      String sSqlCmd = "\
CREATE TABLE tbl_execucao_atualizacao (\
   file_atualizacao   VARCHAR(16),\
   atudb_action       VARCHAR(16),\
   atudb_type         VARCHAR(16),\
   atudb_object       VARCHAR(30),\
   atudb_subaction    VARCHAR(16),\
   atudb_subtype      VARCHAR(16),\
   atudb_subobject    VARCHAR(30),\
   atudb_info         VARCHAR(255),\
   user_atualizacao   VARCHAR(16),\
   data_atualizacao   DATETIME);";
      if (!ExecSqlInstruction(sSqlCmd,0))
         return;
   }
   QyRegAtuDB->Active = true;
   edtIdent->Color = AppConfig->Colors->Disabled;
   edtData->Color = AppConfig->Colors->Disabled;
   edtRequisito->Color = AppConfig->Colors->Disabled;
   if (!AppUser->Usuario.Length())
      sUsuario = "administrador";
   else
      sUsuario = AppUser->Usuario;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::AtuDBInstsDblClick(TObject *Sender)
{
   if (AtuDBInsts->Col == 1 && AtuDBInsts->Cells[GRD_ACTION][AtuDBInsts->Row].Length() > 0) {
      SfgCmdSQLAtuDB *CmdSQLAtuDB = (SfgCmdSQLAtuDB*)AtuDBInsts->Objects[0][AtuDBInsts->Row];
      TStringStream *StrStream = new TStringStream(CmdSQLAtuDB->CmdSQL);
      gbCmdSQL->Top = (this->ClientHeight / 2) - (gbCmdSQL->Height / 2);
      gbCmdSQL->Left = (this->ClientWidth / 2) - (gbCmdSQL->Width / 2);
      gbCmdSQL->Show();
      CmdSQL->Lines->LoadFromStream(StrStream);
      CmdSQL->SetFocus();
      delete StrStream;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::CmdSQLExit(TObject *Sender)
{
   gbCmdSQL->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::gbCmdSQLMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   ::ReleaseCapture();
   ::SetCursor(LoadCursor(NULL,IDC_SIZEALL));
   ::SendMessage(gbCmdSQL->Handle, WM_NCLBUTTONDOWN, HTCAPTION, 0);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::btLoadXMLClick(TObject *Sender)
{
   OpenXML->Title = "Escolher Arquivo Atualização";
   if(OpenXML->Execute()){
      //Limpa o GRID se tiver algo no mesmo
      LimpaGrid();
      XMLPath->Text = OpenXML->FileName;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::LimpaGrid()
{
   SfgCmdSQLAtuDB *CmdSQLAtuDB = NULL;
   //Se tiver na primeira linha preenchida indica que tem algo no GRID
   if (AtuDBInsts->Cells[GRD_ACTION][1].Length() > 0) {
      for (int i=1; i<AtuDBInsts->RowCount; i++) {
         CmdSQLAtuDB = (SfgCmdSQLAtuDB*)AtuDBInsts->Objects[0][i];
         if (CmdSQLAtuDB) delete CmdSQLAtuDB;
      }
   }
   AtuDBInsts->RowCount = 2;
   AtuDBInsts->Rows[1]->Clear();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1012::ValidaFileAtuDB()
{
   if (XMLPath->Text.Length() <= 0) {
      MessageBox(Handle,"Informe o arquivo xml a ser processado!",Caption.c_str(),APP_INFORM);
      return false;
   }
   //Pega apena o nome do arquivo de atualização
   char *cFile, *cDot;
   sFileAtuDB = ExtractFileName(XMLPath->Text);
   cFile = sFileAtuDB.c_str();
   //Encontra o ultimo ponto no nome
   cDot = strrchr(cFile,'.');
   *cDot = '\0';
   //Salva o nome do arquivo
   sFileAtuDB = cFile;
   //Verifica se o arquivo de atualização já foi processado
   String sSQL = "SELECT file_atualizacao FROM tbl_execucao_atualizacao" \
                 " WHERE atudb_action = 'COMPLETE' AND atudb_type = 'ATUDB' AND file_atualizacao = " + QuotedStr(sFileAtuDB);
   if (ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL)) {
      MessageBox(Handle,"O processamento deste arquivo de atualização já foi efetuado com sucesso!",Caption.c_str(),APP_INFORM);
      return false;
   }
   return true;
 }
//---------------------------------------------------------------------------
void __fastcall TFrm1012::btAtualizaClick(TObject *Sender)
{
   //Limpa o GRID se tiver algo no mesmo
   LimpaGrid();

   if (!ValidaFileAtuDB())
      return;

   XMLAtuDB->Active = false;
try {
   XMLAtuDB->LoadFromFile(XMLPath->Text);
} catch ( Exception &e) {
   String sMsgErro = "Não foi possível carregar o arquivo xml a ser processado!\nErro: " + e.Message;
   MessageBox(Handle,sMsgErro.c_str(),Caption.c_str(),APP_INFORM);
   return;
}
   XMLAtuDB->Active = true;
   if (XMLAtuDB->IsEmptyDoc()) {
      MessageBox(Handle,"Informe o arquivo xml a ser processado!",Caption.c_str(),APP_INFORM);
      return;
   }

   IXMLNodeList *NodeList = XMLAtuDB->ChildNodes;
   NodeList = NodeList->FindNode("Atualization")->ChildNodes;

   IXMLNodeList *AtrsNode = NULL;
   IXMLNode *AtrNode = NULL;
   //Deve validar se o arquivo possui pré-requisito e se o memso já foi processado
   IXMLNode *FileNode = NodeList->FindNode("FileInfoAtuDB");
   if (FileNode != NULL) {
      AtrsNode = FileNode->GetAttributeNodes();
      if (AtrsNode != NULL) {
         AtrNode = AtrsNode->FindNode("file_atudbname");
         if (AtrNode != NULL)
            edtIdent->Text = String(AtrNode->Text).UpperCase().Trim();
         AtrNode = AtrsNode->FindNode("file_atudbdate");
         if (AtrNode != NULL)
            edtData->Text = AtrNode->Text;
         AtrNode = AtrsNode->FindNode("file_requisito");
         if (AtrNode != NULL)
            edtRequisito->Text = String(AtrNode->Text).UpperCase().Trim();
      }
   }
   AtrsNode = NULL;
   AtrNode = NULL;
   if (edtRequisito->Text.Length() > 0) {
      String sSQL = "SELECT file_atualizacao FROM tbl_execucao_atualizacao" \
                    " WHERE atudb_action = 'COMPLETE' AND atudb_type = 'ATUDB' AND atudb_object = " + QuotedStr(edtRequisito->Text);
      if (!ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL)) {
         MessageBox(Handle,"Não foi efetuado o processamento do arquivo pré-requisito!",Caption.c_str(),APP_INFORM);
         return;
      }
   }

   IXMLNodeList *InfosNode = NodeList->FindNode("Informations")->ChildNodes;
   IXMLNodeList *InstsNode = NodeList->FindNode("Instructions")->ChildNodes;
   IXMLNode *InfoNode = NULL;
   IXMLNode *InstNode = NULL;

   int iNumInsts = InstsNode->GetCount();
   for (int i=0; i < iNumInsts; i++) {
      InstNode = InstsNode->Nodes[i];
      if (InstNode != NULL) {
         if (i > 0) {
            AtuDBInsts->RowCount++;
         }
         AtuDBInsts->Rows[i+1]->Clear();
         AtuDBInsts->Cells[0][i+1] = IntToStr(i+1);
         //Carrega os atributos dos comandos xml
         AtrsNode = InstNode->GetAttributeNodes();
         if (AtrsNode != NULL) {
            AtrNode = AtrsNode->FindNode("action");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_ACTION][i+1] = String(AtrNode->Text).UpperCase().Trim();
            AtrNode = AtrsNode->FindNode("type");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_TYPE][i+1] = String(AtrNode->Text).UpperCase().Trim();
            AtrNode = AtrsNode->FindNode("object");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_OBJECT][i+1] = String(AtrNode->Text).LowerCase().Trim();
            AtrNode = AtrsNode->FindNode("subaction");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_SUBACTION][i+1] = String(AtrNode->Text).UpperCase().Trim();
            AtrNode = AtrsNode->FindNode("subtype");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_SUBTYPE][i+1] = String(AtrNode->Text).UpperCase().Trim();
            AtrNode = AtrsNode->FindNode("subobject");
            if (AtrNode != NULL)
               AtuDBInsts->Cells[GRD_SUBOBJECT][i+1] = String(AtrNode->Text).LowerCase().Trim();
         }
         //Carrega a informação dos comandos xml
         InfoNode = InfosNode->Nodes[i];
         if (InfoNode != NULL) {
            AtuDBInsts->Cells[GRD_INFO][i+1] = InfoNode->Text;
         }
         //Deve carregar o próprio comando SQL em memória
         SfgCmdSQLAtuDB *CmdSQLAtuDB = new SfgCmdSQLAtuDB();
         CmdSQLAtuDB->CmdSQL = InstNode->Text;
         AtuDBInsts->Objects[0][i+1] = (TObject*)CmdSQLAtuDB;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::AtuDBInstsDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   if (ACol == 1) {
      DrawSearchGrid(AtuDBInsts,ACol,ARow,Rect,State,"");
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::btProcessarClick(TObject *Sender)
{
   if (!ValidaFileAtuDB())
      return;

   if (AtuDBInsts->Cells[GRD_ACTION][1].Length() <= 0) {
      MessageBox(Handle,"Primeiro deve ser carregado para a tela os comandos, depois processados!",Caption.c_str(),APP_INFORM);
      return;
   }

   pnProgress->Top = (this->ClientHeight / 2) - (pnProgress->Height / 2);
   pnProgress->Left = (this->ClientWidth / 2) - (pnProgress->Width / 2);
	pnProgress->Show();
	ProgressAtuDB->Position = 0;
   ProgressAtuDB->Step = 1;
   ProgressAtuDB->Max = AtuDBInsts->RowCount;
   ::EnableWindow(Handle, 0);
   Application->ProcessMessages();

   ProcessAtuDB(Sender);
   
   ::EnableWindow(Handle, 1);
   pnProgress->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::ProcessAtuDB(TObject *Sender)
{

   SfgCmdSQLAtuDB *CmdSQLAtuDB;
   String sAtuDBAction, sAtuDBType, sAtuDBObject;
   String sAtuDBSubAction, sAtuDBSubType, sAtuDBSubObject;
   String sAtuDBInfo;
   bool bHouveErro = false;

   for (int i=1; i < AtuDBInsts->RowCount; i++) {

      sAtuDBAction = AtuDBInsts->Cells[GRD_ACTION][i];
      sAtuDBType   = AtuDBInsts->Cells[GRD_TYPE][i];
      sAtuDBObject = AtuDBInsts->Cells[GRD_OBJECT][i];
      sAtuDBSubAction = AtuDBInsts->Cells[GRD_SUBACTION][i];
      sAtuDBSubType   = AtuDBInsts->Cells[GRD_SUBTYPE][i];
      sAtuDBSubObject = AtuDBInsts->Cells[GRD_SUBOBJECT][i];
      sAtuDBInfo = AtuDBInsts->Cells[GRD_INFO][i];
      CmdSQLAtuDB  = (SfgCmdSQLAtuDB*)AtuDBInsts->Objects[0][i];
      
      //CREATE TABLE
      if ( sAtuDBAction == "CREATE" && sAtuDBType == "TABLE" ) {
         if (!ExistTable(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;   
         }         
      }
      //ALTER TABLE  
      else if ( sAtuDBAction == "ALTER" && sAtuDBType == "TABLE" ) {
         //ADD COLUMN
         if ( sAtuDBSubAction == "ADD" && sAtuDBSubType == "COLUMN" ) {
            if (!ExistTableColumn(sAtuDBObject,sAtuDBSubObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //MODIFY COLUMN
         if ( sAtuDBSubAction == "MODIFY" && sAtuDBSubType == "COLUMN" ) {
            if (ExistTableColumn(sAtuDBObject,sAtuDBSubObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //DROP COLUMN
         else if ( sAtuDBSubAction == "DROP" && sAtuDBSubType == "COLUMN" ) {
            if (ExistTableColumn(sAtuDBObject,sAtuDBSubObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //ADD PRIMARY KEY
         else if ( sAtuDBSubAction == "ADD CONSTRAINT" && sAtuDBSubType == "PRIMARY KEY" ) {
            if (!ExistTablePrimaryKey(sAtuDBObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //DROP PRIMARY KEY
         else if ( sAtuDBSubAction == "DROP" && sAtuDBSubType == "PRIMARY KEY" ) {
            if (ExistTablePrimaryKey(sAtuDBObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //ADD FOREIGN KEY
         else if ( sAtuDBSubAction == "ADD CONSTRAINT" && sAtuDBSubType == "FOREIGN KEY" ) {
            if (!ExistTableForeignKey(sAtuDBObject,sAtuDBSubObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }
         //DROP FOREIGN KEY
         else if ( sAtuDBSubAction == "DROP" && sAtuDBSubType == "FOREIGN KEY" ) {
            if (ExistTableForeignKey(sAtuDBObject,sAtuDBSubObject)) {
               if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
                  RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
            }
         }      
      }
      //DROP TABLE 
      if ( sAtuDBAction == "DROP" && sAtuDBType == "TABLE" ) {
         if (ExistTable(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
               else 
                  bHouveErro = true;   
         }         
      }
      //CREATE PROCEDURE  
      else if ( sAtuDBAction == "CREATE" && sAtuDBType == "PROCEDURE" ) {
         if (!ExistProcedure(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }
      }
      //DROP PROCEDURE  
      else if ( sAtuDBAction == "DROP" && sAtuDBType == "PROCEDURE" ) {
         if (ExistProcedure(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //CREATE VIEW  
      else if ( sAtuDBAction == "CREATE" && sAtuDBType == "VIEW" ) {
         if (!ExistView(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //DROP VIEW  
      else if ( sAtuDBAction == "DROP" && sAtuDBType == "VIEW" ) {
         if (ExistView(sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //CREATE TRIGGER  
      else if ( sAtuDBAction == "CREATE" && sAtuDBType == "TRIGGER" ) {
         if (!ExistTableTrigger(sAtuDBSubObject, sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //DROP TRIGGER  
      else if ( sAtuDBAction == "DROP" && sAtuDBType == "TRIGGER" ) {
         if (ExistTableTrigger(sAtuDBSubObject, sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //CREATE INDEX  
      else if ( sAtuDBAction == "CREATE" && sAtuDBType == "INDEX" ) {
         if (!ExistTableIndex(sAtuDBSubObject, sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }         
      }
      //DROP INDEX  
      else if ( sAtuDBAction == "DROP" && sAtuDBType == "INDEX" ) {
         if (ExistTableIndex(sAtuDBSubObject, sAtuDBObject)) {
            if (ExecSqlInstruction(CmdSQLAtuDB->CmdSQL,i))
               RegisterExecution(sAtuDBAction,sAtuDBType,sAtuDBObject,sAtuDBSubAction,sAtuDBSubType,sAtuDBSubObject,sAtuDBInfo);
            else 
               bHouveErro = true;
         }
      }
      ProgressAtuDB->StepIt();
      Application->ProcessMessages();
   } //Fim for
   //Se não houve erro ao processar o arquivo, grava uma FLAG indicando arquivo processado
   if (!bHouveErro) {
      RegisterExecution("COMPLETE","ATUDB",edtIdent->Text,NULL,NULL,NULL, "Processamento do arquivo de atualização concluído com sucesso!");
   }
   String sMsg = "Arquivo de atualização processado com sucesso!";
   if (bHouveErro) {
      sMsg += "\nPorém houveram erros em alguns comandos, é imprescindível a correção deste erros\n" \
              "antes de dar continuidade ao uso do sistema SFG. Entre em contato com o suporte SoftGreen.";
   }
   MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);

}
//---------------------------------------------------------------------------
bool __fastcall TFrm1012::ExecSqlInstruction(String sCmdSQL, int iCmdSeq)
{
   bool bRet = true;
   TZQuery *QyEcexAtuDB = new TZQuery(Application);
   QyEcexAtuDB->Connection = AppConnection;
try {
   try {
      //Deve fazer assimpara não fazer o PARSER do ZEOS
      QyEcexAtuDB->ParamCheck = false;
      QyEcexAtuDB->SQL->Text = sCmdSQL;
      QyEcexAtuDB->ExecSQL();
   }
   catch (Exception &e) {
      String Msg = "Ocorreu o seguinte erro:\n" +\
                    e.Message +\
                    "\nAo executar o comando de ordem " + IntToStr(iCmdSeq) + \
                    " da atualização " + sFileAtuDB;
      MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",MB_OK | MB_ICONSTOP);
      bRet = false;
   }
}__finally {
   delete(QyEcexAtuDB);
}
   return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::RegisterExecution(String sAtuDBAction, String sAtuDBType, String sAtuDBObject,
      String sAtuDBSubAction, String sAtuDBSubType, String sAtuDBSubObject, String sAtuDBInfo)
{
   QyRegAtuDB->Insert();
   QyRegAtuDB->FieldByName("file_atualizacao")->AsString = sFileAtuDB;
   QyRegAtuDB->FieldByName("atudb_action")->AsString = sAtuDBAction;
   QyRegAtuDB->FieldByName("atudb_type")->AsString = sAtuDBType;
   QyRegAtuDB->FieldByName("atudb_object")->AsString = sAtuDBObject;
   QyRegAtuDB->FieldByName("atudb_subaction")->AsString = sAtuDBSubAction;
   QyRegAtuDB->FieldByName("atudb_subtype")->AsString = sAtuDBSubType;
   QyRegAtuDB->FieldByName("atudb_subobject")->AsString = sAtuDBSubObject;
   QyRegAtuDB->FieldByName("atudb_info")->AsString = sAtuDBInfo;
   QyRegAtuDB->FieldByName("user_atualizacao")->AsString = sUsuario;
   QyRegAtuDB->FieldByName("data_atualizacao")->AsDateTime = Now();
   QyRegAtuDB->Post();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1012::CreateDataBase()
{
   String sDefaultPdw = "C53@7ED8sF6Au70m@t1cO";
   String sInputPdw = "";
   //Deve criar uma tela solicitando uma palavra chave para criação do banco de dados
   if (!InputQuery("Palavra Chave", "Informe a palavra chave para liberação da rotina de criação do banco de dados.", sInputPdw)) {
      return false;
   }
   if (sInputPdw != sDefaultPdw) {
      MessageBox(NULL,"A palavra chave informada não confere com palavra chave definida para liberação da criação do banco de dados.","Mensagem de Erro",MB_OK | MB_ICONSTOP);
      return false;
   }

   if (!ExecSqlCreateDB()) {
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1012::ExecSqlCreateDB()
{
   bool bRet = true;
   String sCmdSQL = "CREATE DATABASE IF NOT EXISTS `" + AppDB->Database + "` DEFAULT CHARACTER SET utf8;";
   TZQuery *QyEcexAtuDB = new TZQuery(Application);
   QyEcexAtuDB->Connection = AppConnection;
try {
   try {
      AppConnection->Connected = false;
      AppConnection->Database = "";
      AppConnection->Catalog = "";
      AppConnection->Connected = true;
      QyEcexAtuDB->SQL->Text = sCmdSQL;
      QyEcexAtuDB->ExecSQL();
      AppConnection->Connected = false;
      AppConnection->Database = AppDB->Database;
      AppConnection->Catalog = AppDB->Database;
      AppConnection->Connected = true;
   }
   catch (Exception &e) {
      String Msg = "Ocorreu o seguinte erro ao tentar criar o banco de dados:\n" + e.Message;
      MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",MB_OK | MB_ICONSTOP);
      bRet = false;
   }
}__finally {
   delete(QyEcexAtuDB);
}
   return bRet;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1012::execMetadadosExecute(TObject *Sender)
{
   TFrm1013 *Frm1013 = new TFrm1013(Application);
   Frm1013->Show();
}
//---------------------------------------------------------------------------
/*

CREATE TABLE tbl_execucao_atualizacao (
   file_atualizacao   VARCHAR(16),
   atudb_action       VARCHAR(16),
   atudb_type         VARCHAR(16),
   atudb_object       VARCHAR(30),
   atudb_subaction    VARCHAR(16),
   atudb_subtype      VARCHAR(16),
   atudb_subobject    VARCHAR(30),
   atudb_info         VARCHAR(255),
   user_atualizacao   VARCHAR(16),
   data_atualizacao   DATETIME
);
*/



