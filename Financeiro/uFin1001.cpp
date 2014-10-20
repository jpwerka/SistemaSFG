/*
Módulo: Financeiro
Função: Cadastro Plano de Contas
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgWorkEdition.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFin1001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFin1001(void) {
   AddAppForm("Fin1001","Plano de Contas",APP_MODULO_FINANCAS);
   AddAppFormClass("TFin1001",__classid(TFin1001));
}
#pragma startup RegisterFin1001
//---------------------------------------------------------------------------
__fastcall TFin1001::TFin1001(TComponent* Owner)
	: TfrmBase01(Owner)
{
	PlanoConta->Active = true;
	TreeContas->Items->Clear();
	CarregaPlanoContas(NULL);
	PlanoConta->Filtered = false;
	pWorkEdition = new SfgWorkEdition(DsPlanoConta,this);
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   //Escondendo as opções de menu do SfgToolbar
	execBtAddItem->Visible = false;
	execBtAddChild->Visible = false;
	execBtEdit->Visible = false;
	execBtSave->Visible = false;
	execBtCancel->Visible = false;
	execBtDelete->Visible = false;
   //Desabilitando as teclas de atalho também
	execBtAddItem->Enabled = false;
	execBtAddChild->Enabled = false;
	execBtEdit->Enabled = false;
	execBtSave->Enabled = false;
	execBtCancel->Enabled = false;
	execBtDelete->Enabled = false;
   btExit->Left = 6;
}
//---------------------------------------------------------------------------
//01 {01-DESPESA},02 {02-RECEITA},03 {03-C.COMPENSACAO},04 {04-ATIVO},05 {05-PASSIVO},07 {07-GERENCIAL},08 {08-C.RESULTADO},09 {09-OS}'
void __fastcall TFin1001::FormClose(TObject *Sender,
		TCloseAction &Action)
{
	FreeTreeNodes(TreeContas->Items->GetFirstNode(), -1);
	TfrmBase01::FormClose(Sender,Action);
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::CarregaPlanoContas(TTreeNode *pParentItem)
{
	char *ContaPai;
	String TextNode;
	String CodConta;
	TTreeNode *pChildItem = NULL;
	TTreeNode *pFirstItem = NULL;
	PlanoConta->Filtered = false;
	if (pParentItem == NULL) {
		PlanoConta->Filter = "cod_plano_conta_pai IS NULL";
	} else {
		ContaPai = (char*)pParentItem->Data;
		CodConta = ContaPai;
		PlanoConta->Filter =  "cod_plano_conta_pai  = " + QuotedStr(CodConta);
	}
	PlanoConta->Filtered = true;
	PlanoConta->First();
	while (!PlanoConta->Eof) {
		CodConta = PlanoConta->FieldByName("cod_plano_conta")->AsString;
		ContaPai = new char[CodConta.Length()+1];
		StrCopy(ContaPai, CodConta.c_str());
		TextNode = CodConta + " - " +  PlanoConta->FieldByName("den_plano_conta")->AsString;
		if (pParentItem == NULL) {
			pChildItem = TreeContas->Items->AddObject(pParentItem, TextNode, (void*)ContaPai);
		} else {
			pChildItem = TreeContas->Items->AddChildObject(pParentItem, TextNode, (void*)ContaPai);
		}
		if (pFirstItem == NULL) {
			pFirstItem = pChildItem;
		}
		PlanoConta->Next();
	}
	while(pFirstItem != NULL) {
		CarregaPlanoContas(pFirstItem);
		pFirstItem = pFirstItem->getNextSibling();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::TreeContasChange(TObject *Sender, TTreeNode *Node)
{
	char *ContaPai;
	if (Node != NULL) {
		ContaPai = (char*)Node->Data;
		PlanoConta->Locate("cod_plano_conta",Variant(ContaPai),TLocateOptions());
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btEditClick(TObject *Sender)
{
	HabilitarItens(true);
	pWorkEdition->SetWorkEdition(true,false,AppConfig->Colors->Enabled);
	PlanoConta->Edit();
	cod_plano_conta_reduz->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::HabilitarItens(bool Habilita)
{
	//TreeContas->Enabled = !Habilita;
	execBtAddItem->Enabled = !Habilita;
	execBtAddChild->Enabled = !Habilita;
	execBtEdit->Enabled = !Habilita;
	execBtSave->Enabled = Habilita;
	execBtCancel->Enabled = Habilita;
	execBtDelete->Enabled = !Habilita;
	btExit->Enabled = !Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btSaveClick(TObject *Sender)
{
	bool inclui = false;
	if (!VerificaCampos())
		return;
	if (PlanoConta->State == dsInsert) {
		if (!ValidaCampos())
			return;
		inclui = true;
	}
	String TextNode;
	TTreeNode *Node = TreeContas->Selected;
	PlanoConta->Post();
	TextNode = PlanoConta->FieldByName("cod_plano_conta")->AsString + " - " +  PlanoConta->FieldByName("den_plano_conta")->AsString;
	Node->Text = TextNode;
	if (inclui) {
		char *ContaPai;
		String CodConta = PlanoConta->FieldByName("cod_plano_conta")->AsString;
		ContaPai = new char[CodConta.Length()+1];
		StrCopy(ContaPai, CodConta.c_str());
		Node->Data = (void*)ContaPai;
	}
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btCancelClick(TObject *Sender)
{
	TTreeNode *Node;
	TTreeNode *Prew = NULL;
	if (PlanoConta->State == dsInsert) {
		Node = TreeContas->Selected;
		Prew = Node->getPrevSibling();
		if(Prew == NULL) {
			Prew = Node->GetPrev();
		}
		if (Node) {
			TreeContas->Items->Delete(Node);
		}
	}
	PlanoConta->Cancel();
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
	if (Prew != NULL) {
		TreeContas->Selected = Prew;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btAddItemClick(TObject *Sender)
{
	TTreeNode *Node = TreeContas->Selected;
	Node = TreeContas->Items->Add(Node, "? - Novo item.");
	TreeContas->Selected = Node;
	Variant Parent = PlanoConta->FieldByName("cod_plano_conta_pai")->Value;
	PlanoConta->Insert();
	PlanoConta->FieldByName("data_cadastro")->AsDateTime = Date();
	PlanoConta->FieldByName("cod_plano_conta_pai")->Value = Parent;
	PlanoConta->FieldByName("ies_ativo")->AsString = "S";
	pWorkEdition->SetWorkEdition(true,true,AppConfig->Colors->Enabled);
	cod_plano_conta_pai->ReadOnly = true;
	cod_plano_conta_pai->Color = AppConfig->Colors->Disabled;
	HabilitarItens(true);
	cod_plano_conta->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btAddChildClick(TObject *Sender)
{
	TTreeNode *Node = TreeContas->Selected;
	Node = TreeContas->Items->AddChild(Node, "? - Novo filho.");
	TreeContas->Selected = Node;
	Variant Parent = PlanoConta->FieldByName("cod_plano_conta")->Value;
	PlanoConta->Insert();
	PlanoConta->FieldByName("data_cadastro")->AsDateTime = Date();
	PlanoConta->FieldByName("cod_plano_conta_pai")->Value = Parent;
	PlanoConta->FieldByName("ies_ativo")->AsString = "S";
	pWorkEdition->SetWorkEdition(true,true,AppConfig->Colors->Enabled);
	cod_plano_conta_pai->ReadOnly = true;
	cod_plano_conta_pai->Color = AppConfig->Colors->Disabled;
	HabilitarItens(true);
	cod_plano_conta->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btDeleteClick(TObject *Sender)
{
	TTreeNode *Node = TreeContas->Selected;
	CanDelete->ParamByName("cod_plano_conta")->Value = PlanoConta->FieldByName("cod_plano_conta")->Value;
	CanDelete->Active = true;
	if (CanDelete->FieldByName("can_delete")->AsInteger == 0) {
		MessageBox(Handle, "Existem contas já cadastradas para esta conta \ncontábil ou uma de suas filhas. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		CanDelete->Active = false;
		return;
	}
	CanDelete->Active = false;
	if (MessageBox(Handle,"Deseja excluir a conta contábil e suas filhas?\n"
      "Após a exclusão não será possível recuperar cadastro!",
		"Excluir",APP_QUESTION | MB_DEFBUTTON2) == IDNO) {
		return;
	}
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
try {
	DelPlanoConta->ParamByName("cod_plano_conta")->Value = PlanoConta->FieldByName("cod_plano_conta")->Value;
	DelPlanoConta->ExecSQL();
	FreeTreeNodes(Node, Node->Level);
	SfgDataCenter->CommitTrans();
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao excluir as informações da conta:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	SfgDataCenter->RollbackTrans();
}
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::TreeContasChanging(TObject *Sender,
		TTreeNode *Node, bool &AllowChange)
{
	if (PlanoConta->State == dsInsert || PlanoConta->State == dsEdit) {
		AllowChange = false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFin1001::VerificaCampos()
{
	if(!cod_plano_conta->Text.Length()) {
		MessageBox(Handle, "Digite o código da conta contábil!",Caption.c_str(),APP_ATENTION);
		cod_plano_conta->SetFocus();
		return false;
	}
	if(!cod_plano_conta_reduz->Text.Length()) {
		MessageBox(Handle, "Digite o código reduzido da conta contábil!",Caption.c_str(),APP_ATENTION);
		cod_plano_conta_reduz->SetFocus();
		return false;
	}
	if(!den_plano_conta->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da conta contábil!",Caption.c_str(),APP_ATENTION);
		den_plano_conta->SetFocus();
		return false;
	}
	if(!tipo_plano_conta->Field->AsString.Length()) {
		MessageBox(Handle, "Informe a natureza da conta contábil!",Caption.c_str(),APP_ATENTION);
		tipo_plano_conta->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFin1001::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_plano_conta FROM tbl_plano_conta" \
			" WHERE cod_plano_conta = " + QuotedStr(cod_plano_conta->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Conta contábil já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_plano_conta->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::FreeTreeNodes(TTreeNode *Parent, int Level)
{
	char *Data;
	TTreeNode *Next;

	Next = Parent->GetNext();
	if (Next != NULL) {
		if(Next->Level > Level) {
			FreeTreeNodes(Next, Level);
		}
	}
	Data = (char*)Parent->Data;
	delete Data;
	TreeContas->Items->Delete(Parent);
}
//---------------------------------------------------------------------------
void __fastcall TFin1001::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------


