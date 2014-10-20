/*
Módulo: FrameWork
Função: Cadastro Grupos
Autor.: Jackson Patrick Werka
Data..: 25/08/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFrm1004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1004(void) {
   AddAppForm("Frm1004","Grupos");
   AddAppFormClass("TFrm1004",__classid(TFrm1004));
}
#pragma startup RegisterFrm1004
//---------------------------------------------------------------------------
__fastcall TFrm1004::TFrm1004(TComponent* Owner)
	: TfrmBase02(Owner)
{
   SfgToolbar->DataSource = DsCadGrupo;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1004::ValidInsert(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
	if (!ValidaCampos()) {
      bValid = false;
      return;
   }
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1004::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1004::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_usuario_grupo" \
			" WHERE cod_grupo = " + QuotedStr(cod_grupo->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Existem usuários cadastrados para este grupo. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
	bValid = true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1004::VerificaCampos()
{
	if(!cod_grupo->Text.Length()) {
		MessageBox(Handle, "Digite o código do grupo!",Caption.c_str(),APP_ATENTION);
		cod_grupo->SetFocus();
		return false;
	}
	if(!den_grupo->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do grupo!",Caption.c_str(),APP_ATENTION);
		den_grupo->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1004::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_grupo FROM tbl_grupo" \
			" WHERE cod_grupo = " + QuotedStr(cod_grupo->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Grupo já cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_grupo->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
