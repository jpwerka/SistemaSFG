//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgMsgOption.h"
#include "uDataModule.h"
#include "uSfgBrowseFrm.h"
#pragma hdrstop
#include "uFrm1011.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1011(void) {
   AddAppForm("Frm1011","Permissão Menu");
   AddAppFormClass("TFrm1011",__classid(TFrm1011));
}
#pragma startup RegisterFrm1011
//---------------------------------------------------------------------------
__fastcall TFrm1011::TFrm1011(TComponent* Owner)
   : TfrmBase01(Owner)
{
	usuario_grupo->Color = AppConfig->Colors->Disabled;
   denominacao->Color = AppConfig->Colors->Disabled;
   execBtDelete->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::FormClose(TObject *Sender, TCloseAction &Action)
{
	FreeTreeNodes(TreeMenu->Items->GetFirstNode(), -1);
	TfrmBase01::FormClose(Sender,Action);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::CarregaMenu(TTreeNode *pParentItem)
{
	String TextNode;
	SfgMenuInfo *MenuInfo;
	TTreeNode *pChildItem = NULL;
	TTreeNode *pFirstItem = NULL;
	PermissaoMenu->Filtered = false;
	if (pParentItem == NULL) {
		PermissaoMenu->Filter = "cod_rotina_pai IS NULL";
	} else {
		MenuInfo = (SfgMenuInfo*)pParentItem->Data;
		PermissaoMenu->Filter =  "cod_rotina_pai  = " + QuotedStr(MenuInfo->cod_rotina);
	}
	PermissaoMenu->Filtered = true;
	PermissaoMenu->First();
	while (!PermissaoMenu->Eof) {
      MenuInfo = new SfgMenuInfo();
		MenuInfo->cod_rotina = PermissaoMenu->FieldByName("cod_rotina")->AsString;
      if (PermissaoMenu->FieldByName("programa")->AsString.Length() > 0) {
		   TextNode = PermissaoMenu->FieldByName("programa")->AsString.UpperCase() + " - " + PermissaoMenu->FieldByName("den_rotina")->AsString;
      } else {
		   TextNode = PermissaoMenu->FieldByName("den_rotina")->AsString;
      }
		if (pParentItem == NULL) {
			pChildItem = TreeMenu->Items->AddObject(pParentItem, TextNode, (void*)MenuInfo);
		} else {
			pChildItem = TreeMenu->Items->AddChildObject(pParentItem, TextNode, (void*)MenuInfo);
		}
      if (permissao_por->ItemIndex == 1) {  //Permissão por grupo
         pChildItem->ImageIndex = PermissaoMenu->FieldByName("nivel_permissao")->AsInteger;
      } else {
         if (PermissaoMenu->FieldByName("tip_permissao")->AsString == "G") { //Permissão herdada por grupo
            pChildItem->ImageIndex = PermissaoMenu->FieldByName("nivel_permissao")->AsInteger + 2;
         } else {
            pChildItem->ImageIndex = PermissaoMenu->FieldByName("nivel_permissao")->AsInteger;
         }
      }
      pChildItem->SelectedIndex = pChildItem->ImageIndex;
		if (pFirstItem == NULL) {
			pFirstItem = pChildItem;
		}
		PermissaoMenu->Next();
	}
	while(pFirstItem != NULL) {
		CarregaMenu(pFirstItem);
		pFirstItem = pFirstItem->getNextSibling();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::FreeTreeNodes(TTreeNode *Parent, int Level)
{
	SfgMenuInfo *MenuInfo;
	TTreeNode *Next;

   if (Parent == NULL)
      return;

	Next = Parent->GetNext();
	if (Next != NULL) {
		if(Next->Level > Level) {
			FreeTreeNodes(Next, Level);
		}
	}
	MenuInfo = (SfgMenuInfo*)Parent->Data;
	delete MenuInfo;
	TreeMenu->Items->Delete(Parent);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::execBtPesquisaExecute(TObject *Sender)
{
   int opt=0;
   String SQL;
   TStrings *Buttons = new TStringList();
   Buttons->Add("Usuário=1");
   Buttons->Add("Grupo=2");
   Buttons->Add("Cancelar=3");

   execBtDelete->Enabled = false;
   permissao_por->ItemIndex = -1;
   usuario_grupo->Clear();
   denominacao->Clear();
   FreeTreeNodes(TreeMenu->Items->GetFirstNode(), -1);

   opt = SfgMsgOption("Qual o tipo de permissão a ser dada?",mtConfirmation,Buttons,"Pergunta",-1,3);

   delete Buttons;

   if (opt == 3)
      return;

   if (opt == 1) { //Pesquisa por usuário
      SfgBrowse::EscolheUsuario(this,&SearchReturn);
   } else { //Pesquisa por grupo
      SfgBrowse::EscolheGrupo(this,&SearchReturn);
   }

   if (usuario_grupo->Text.Length() > 0) {
      PermissaoMenu->ParamByName("usuario_grupo")->Value = usuario_grupo->Text;
      if (opt == 1) { //Pesquisa por usuário
         permissao_por->ItemIndex = 0;
         PermissaoMenu->ParamByName("tip_permissao")->Value = "U";
         SQL = "SELECT nome FROM tbl_usuario WHERE usuario = " + QuotedStr(usuario_grupo->Text);
      } else { //Pesquisa por grupo
         PermissaoMenu->ParamByName("tip_permissao")->Value = "G";
         permissao_por->ItemIndex = 1;
         SQL = "SELECT den_grupo FROM tbl_grupo WHERE cod_grupo = " + QuotedStr(usuario_grupo->Text);
      }
      denominacao->Text = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
      PermissaoMenu->Active = true;
      CarregaMenu(NULL);
      PermissaoMenu->Active = false;
      execBtDelete->Enabled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::SearchReturn(Variant Value)
{
   usuario_grupo->Text = VarToStr(Value);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::execBtDeleteExecute(TObject *Sender)
{
   if (MessageBox(Handle,"Deseja excluir todas as permissões atuais?",
      "Excluir",APP_QUESTION | MB_DEFBUTTON2) == IDNO)
      return;

   DeletePermissao->ParamByName("usuario_grupo")->Value = usuario_grupo->Text;
   if (permissao_por->ItemIndex == 0)
      DeletePermissao->ParamByName("tip_permissao")->Value = "U";
   else
      DeletePermissao->ParamByName("tip_permissao")->Value = "G";
   DeletePermissao->ExecSQL();
   //Recarregando o menu para mostrar as permissões corretas
   FreeTreeNodes(TreeMenu->Items->GetFirstNode(), -1);
   PermissaoMenu->Active = true;
   CarregaMenu(NULL);
   PermissaoMenu->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::TreeMenuMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   TPoint Point;
   THitTests MyHitTest = TreeMenu->GetHitTestInfoAt(X,Y);
   if (MyHitTest.Contains(htOnIcon)) {
      if (permissao_por->ItemIndex == 1) {
         somente_leitura_g->Visible = false;
         permissao_total_g->Visible = false;
      } else {
         somente_leitura_g->Visible = true;
         permissao_total_g->Visible = true;
      }
      Point.x = X;
      Point.y = Y;
      Point = TreeMenu->ClientToScreen(Point);
      menu_tree->Popup(Point.x,Point.y);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::AlterarPermissao(TTreeNode *Parent, int Level,
      int nivel_permissao)
{
	SfgMenuInfo *MenuInfo;
	TTreeNode *Next;

   if (Parent == NULL)
      return;

   if (Level == -1) {
	   Next = Parent->getFirstChild();
      Level = Parent->Level;
   } else {
	   Next = Parent->GetNext();
   }
	if (Next != NULL) {
		if(Next->Level > Level) {
			AlterarPermissao(Next, Level, nivel_permissao);
		}
	}
	MenuInfo = (SfgMenuInfo*)Parent->Data;
   ModificaPermissao->ParamByName("usuario_grupo")->Value = usuario_grupo->Text;
   if (permissao_por->ItemIndex == 0)
      ModificaPermissao->ParamByName("tip_permissao")->Value = "U";
   else
      ModificaPermissao->ParamByName("tip_permissao")->Value = "G";
   ModificaPermissao->ParamByName("cod_rotina")->Value = MenuInfo->cod_rotina;
   ModificaPermissao->ParamByName("nivel_permissao")->Value = nivel_permissao;
   ModificaPermissao->Active = true;
   ModificaPermissao->Active = false;
   Parent->ImageIndex = nivel_permissao;
   Parent->SelectedIndex = nivel_permissao;
   TreeMenu->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::sem_permissaoClick(TObject *Sender)
{
   //Exclui a permissão do usuário/grupo do nó e de todos os itens abaixo
	AlterarPermissao(TreeMenu->Selected, -1, 0);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::somente_leituraClick(TObject *Sender)
{
   //Inclui a permissão de leitura do usuário/grupo para o nó e para todos os itens abaixo
	AlterarPermissao(TreeMenu->Selected, -1, 1);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1011::permissao_totalClick(TObject *Sender)
{
   //Inclui a permissão total do usuário/grupo para o nó e para todos os itens abaixo
	AlterarPermissao(TreeMenu->Selected, -1, 2);
}
//---------------------------------------------------------------------------

