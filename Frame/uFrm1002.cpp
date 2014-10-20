/*
Módulo: Framework SoftGreen
Função: Cadastro Usuários
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgBrowseFrm.h"
#include "uSfgSearch.h"
#pragma hdrstop
#include "uFrm1002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1002(void) {
   AddAppForm("Frm1002","Usuários");
   AddAppFormClass("TFrm1002",__classid(TFrm1002));
}
#pragma startup RegisterFrm1002
//---------------------------------------------------------------------------
__fastcall TFrm1002::TFrm1002(TComponent* Owner)
	: TfrmBase02(Owner)
{
   SfgToolbar->DataSource = DsCadUsuario;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
   HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::ValidInsert(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
	if (!ValidaCampos()) {
      bValid = false;
      return;
   }
   PostStatus = true;
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
	}
   PostStatus = true;
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::ValidDelete(bool &bValid)
{
	if (usuario->Field->AsString == "administrador") {
		MessageBox(Handle, "Não é possível excluir o usuário Administrador!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1002::VerificaCampos()
{
	String SenhaCripto;

	if(usuario->Text.Length() < 4) {
		MessageBox(Handle, "Digite o código de usuário com pelo menos 4 caracteres!",Caption.c_str(),APP_ATENTION);
		usuario->SetFocus();
		return false;
	}
	if(!nome->Text.Length()) {
		MessageBox(Handle, "Digite o nome do usuário!",Caption.c_str(),APP_ATENTION);
		nome->SetFocus();
		return false;
	}
	if(senha->Text.Length() < 4) {
		MessageBox(Handle, "Digite a senha do usuário com pelo menos 4 caracteres!",Caption.c_str(),APP_ATENTION);
		senha->SetFocus();
		return false;
	}
	if(!confirmacao->Text.Length()) {
		MessageBox(Handle, "Digite a confirmação da senha do usuário!",Caption.c_str(),APP_ATENTION);
		confirmacao->SetFocus();
		return false;
	}

	if (confirmacao->Text != senha->Text) {
		MessageBox(Handle, "A confirmação da senha não confere!",Caption.c_str(),APP_ATENTION);
		confirmacao->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1002::ValidaCampos()
{
	String SQL;
	SQL = "SELECT usuario FROM tbl_usuario" \
			" WHERE usuario = " + QuotedStr(usuario->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "usuário já cadastrado!",Caption.c_str(),APP_ATENTION);
		usuario->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::senhaExit(TObject *Sender)
{
  if((DsCadUsuario->State == dsInsert || DsCadUsuario->State == dsEdit) &&
	 senha->Text.Length())
	 senha->Field->Value = EncryptText(senha->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::confirmacaoExit(TObject *Sender)
{
  if(confirmacao->Text.Length())
	 confirmacao->Text = EncryptText(confirmacao->Text.c_str());
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioAfterScroll(TDataSet *DataSet)
{
	confirmacao->Text = senha->Text;
   CarregarGrupos();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::CarregarGrupos()
{
	ListGrupos->Clear();
   QyUsuarioGrupo->First();
   while (!QyUsuarioGrupo->Eof) {
      ListGrupos->AddItem(QyUsuarioGrupo->FieldByName("cod_grupo")->AsString, NULL);
      QyUsuarioGrupo->Next();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::btSearchGrupoClick(TObject *Sender)
{
   if(QyCadUsuario->State == dsInsert) {
      if (usuario->Text.Length() == 0) {
         MessageBox(Handle,"Informe primeiro o usuário para depois relacionar os grupos!",Caption.c_str(),APP_ATENTION);
         return;
      }
   }
   SfgBrowse::EscolheGrupo(this,&SearchGrupo);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::SearchGrupo(Variant Value) {
   bool achou = false;
   String cod_grupo = VarToStr(Value);
   for(int i=0; i < ListGrupos->Count; i++) {
      if (ListGrupos->Items->operator [](i) == cod_grupo) {
         achou = true;
         break;
      }
   }
   if (achou) {
      MessageBox(Handle,"O usuário atual já faz parte do grupo escolhido!", Caption.c_str(),APP_INFORM);
   } else {
      ListGrupos->AddItem(cod_grupo,NULL);
      QyUsuarioGrupo->Insert();
      QyUsuarioGrupo->FieldByName("usuario")->AsString = usuario->Text;
      QyUsuarioGrupo->FieldByName("cod_grupo")->AsString = cod_grupo;
      QyUsuarioGrupo->Post();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::NavegbtEditClick(TObject *Sender)
{
	SfgToolbar->btEditClick(Sender);
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::NavegbtSaveClick(TObject *Sender)
{
	PostStatus = false;
	SfgToolbar->btSaveClick(Sender);
   if(PostStatus) {
      HabilitarItens(false);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::NavegbtCancelClick(TObject *Sender)
{
	QyUsuarioGrupo->CancelUpdates();
   SfgToolbar->btCancelClick(Sender);
	HabilitarItens(false);
   CarregarGrupos();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::NavegbtNewClick(TObject *Sender)
{
	SfgToolbar->btNewClick(Sender);
	HabilitarItens(true);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioBeforeDelete(TDataSet *DataSet)
{
   QyUsuarioGrupo->First();
   while(!QyUsuarioGrupo->Eof) {
      QyUsuarioGrupo->First();
      QyUsuarioGrupo->Delete();
   }
   QyUsuarioGrupo->ApplyUpdates();
   ListGrupos->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::HabilitarItens(bool Habilita)
{
   confirmacao->ReadOnly = !Habilita;
   confirmacao->Color = (Habilita) ? AppConfig->Colors->Enabled : AppConfig->Colors->Disabled;
   ListGrupos->Color = (Habilita) ? AppConfig->Colors->Enabled : AppConfig->Colors->Disabled;
   btSearchGrupo->Enabled = Habilita;
   btDeleteGrupo->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::btDeleteGrupoClick(TObject *Sender)
{
   int Index = ListGrupos->ItemIndex;
   if (Index < 0)
      return;
   String cod_grupo = ListGrupos->Items->operator [](Index);
   if(QyUsuarioGrupo->Locate("cod_grupo",Variant(cod_grupo),TLocateOptions())) {
      QyUsuarioGrupo->Delete();
      ListGrupos->DeleteSelected();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioAfterPost(TDataSet *DataSet)
{
try {
try {
	//Verificação para atualizar o campo usuário do mestre nos grupos
	QyUsuarioGrupo->First();
	while (!QyUsuarioGrupo->Eof) {
		QyUsuarioGrupo->Edit();
      QyUsuarioGrupo->FieldByName("usuario")->AsString = usuario->Text;
      QyUsuarioGrupo->Post();
		QyUsuarioGrupo->Next();
	}
	QyUsuarioGrupo->ApplyUpdates();
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	PostStatus = false;
}
}
//Sempre vai passar por aqui, mesmo dando erro
__finally {
	QyUsuarioGrupo->DataSource = DsCadUsuario;
	QyCadUsuario->AfterScroll = &QyCadUsuarioAfterScroll;
}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioBeforePost(TDataSet *DataSet)
{
	QyCadUsuario->AfterScroll = NULL;
	QyUsuarioGrupo->DataSource = NULL;
}
//-------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioAfterOpen(TDataSet *DataSet)
{
   QyUsuarioGrupo->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1002::QyCadUsuarioBeforeClose(TDataSet *DataSet)
{
   QyUsuarioGrupo->Active = false;
}
//---------------------------------------------------------------------------

