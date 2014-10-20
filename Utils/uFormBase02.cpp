//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#pragma hdrstop
#include "uFormBase02.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TfrmBase02::TfrmBase02(TComponent* Owner)
	: TfrmBase01(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmBase02::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   //Escondendo as opções de menu do SfgToolbar
	SfgToolbar->execBtEditClick->Visible = false;
	SfgToolbar->execBtSaveClick->Visible = false;
	SfgToolbar->execBtUndoClick->Visible = false;
	SfgToolbar->execBtCancelClick->Visible = false;
	SfgToolbar->execBtNewClick->Visible = false;
	SfgToolbar->execBtDeleteClick->Visible = false;
	SfgToolbar->execBtCopyClick->Visible = false;
   //Desabilitando as teclas de atalho também
	SfgToolbar->execBtEditClick->Enabled = false;
	SfgToolbar->execBtSaveClick->Enabled = false;
	SfgToolbar->execBtUndoClick->Enabled = false;
	SfgToolbar->execBtCancelClick->Enabled = false;
	SfgToolbar->execBtNewClick->Enabled = false;
	SfgToolbar->execBtDeleteClick->Enabled = false;
	SfgToolbar->execBtCopyClick->Enabled = false;
   SfgToolbar->btExit->Left = 272;
}
//---------------------------------------------------------------------------


