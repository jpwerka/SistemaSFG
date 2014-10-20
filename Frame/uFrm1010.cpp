//---------------------------------------------------------------------------
#include <vcl.h>
#include <XMLDoc.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgWorkEdition.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFrm1010.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1010(void) {
   AddAppForm("Frm1010","Menu");
   AddAppFormClass("TFrm1010",__classid(TFrm1010));
}
#pragma startup RegisterFrm1010
//---------------------------------------------------------------------------
__fastcall TFrm1010::TFrm1010(TComponent* Owner)
   : TfrmBase01(Owner)
{
   CarregarModulos();
	CadMenu->Active = true;
	TreeMenu->Items->Clear();
	CarregaMenu(NULL);
	CadMenu->Filtered = false;
	pWorkEdition = new SfgWorkEdition(DsMenu,this);
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
	ico_index->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::FormClose(TObject *Sender, TCloseAction &Action)
{
	FreeTreeNodes(TreeMenu->Items->GetFirstNode(), -1);
	TfrmBase01::FormClose(Sender,Action);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::CarregarModulos()
{
	modulo->Clear();
	modulo->AddItem("Padrão",Variant(APP_MODULO_GERAL));
	modulo->AddItem("Estoque",Variant(APP_MODULO_ESTOQUE));
	modulo->AddItem("Compras",Variant(APP_MODULO_COMPRAS));
	modulo->AddItem("Vendas",Variant(APP_MODULO_VENDAS));
	modulo->AddItem("Finanças",Variant(APP_MODULO_FINANCAS));
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::CarregaMenu(TTreeNode *pParentItem)
{
	String TextNode;
	SfgMenuInfo *MenuInfo;
	TTreeNode *pChildItem = NULL;
	TTreeNode *pFirstItem = NULL;
	CadMenu->Filtered = false;
	if (pParentItem == NULL) {
		CadMenu->Filter = "cod_rotina_pai IS NULL";
	} else {
		MenuInfo = (SfgMenuInfo*)pParentItem->Data;
		CadMenu->Filter =  "cod_rotina_pai  = " + QuotedStr(MenuInfo->cod_rotina);
	}
	CadMenu->Filtered = true;
	CadMenu->First();
	while (!CadMenu->Eof) {
      MenuInfo = new SfgMenuInfo();
		MenuInfo->cod_rotina = CadMenu->FieldByName("cod_rotina")->AsString;
      if (CadMenu->FieldByName("programa")->AsString.Length() > 0) {
		   TextNode = CadMenu->FieldByName("programa")->AsString.UpperCase() + " - " + CadMenu->FieldByName("den_rotina")->AsString;
      } else {
		   TextNode = CadMenu->FieldByName("den_rotina")->AsString;
      }
		if (pParentItem == NULL) {
			pChildItem = TreeMenu->Items->AddObject(pParentItem, TextNode, (void*)MenuInfo);
		} else {
			pChildItem = TreeMenu->Items->AddChildObject(pParentItem, TextNode, (void*)MenuInfo);
		}
      pChildItem->ImageIndex = CadMenu->FieldByName("ico_index")->AsInteger;
      pChildItem->SelectedIndex = pChildItem->ImageIndex;
		if (pFirstItem == NULL) {
			pFirstItem = pChildItem;
		}
		CadMenu->Next();
	}
	while(pFirstItem != NULL) {
		CarregaMenu(pFirstItem);
		pFirstItem = pFirstItem->getNextSibling();
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::FreeTreeNodes(TTreeNode *Parent, int Level)
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
void __fastcall TFrm1010::HabilitarItens(bool Habilita)
{
	//TreeMenu->Enabled = !Habilita;
	execBtAddItem->Enabled = !Habilita;
	execBtAddChild->Enabled = !Habilita;
	execBtEdit->Enabled = !Habilita;
	execBtSave->Enabled = Habilita;
	execBtCancel->Enabled = Habilita;
	execBtDelete->Enabled = !Habilita;
	btExit->Enabled = !Habilita;
   ico_index->Enabled = Habilita;
   btSearchForm->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::TreeMenuChange(TObject *Sender, TTreeNode *Node)
{
	SfgMenuInfo *MenuInfo;
	if (Node != NULL) {
      if (Node->Data != NULL) {
		   MenuInfo = (SfgMenuInfo*)Node->Data;
		   CadMenu->Locate("cod_rotina",Variant(MenuInfo->cod_rotina),TLocateOptions());
         ico_index->ItemIndex = CadMenu->FieldByName("ico_index")->AsInteger + 1;
      }
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::TreeMenuChanging(TObject *Sender,
      TTreeNode *Node, bool &AllowChange)
{
	if (CadMenu->State == dsInsert || CadMenu->State == dsEdit) {
		AllowChange = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtAddItemExecute(TObject *Sender)
{
	Variant Parent = CadMenu->FieldByName("cod_rotina_pai")->Value;
	TTreeNode *Node = TreeMenu->Selected;
	Node = TreeMenu->Items->Add(Node, "Novo item.");
   Node->Data = NULL;
   TreeMenu->Selected = Node;
	CadMenu->Insert();
	CadMenu->FieldByName("cod_rotina_pai")->Value = Parent;
   CadMenu->FieldByName("ord_rotina")->Value = (Node->Index + 1);
	pWorkEdition->SetWorkEdition(true,true,AppConfig->Colors->Enabled);
	cod_rotina_pai->ReadOnly = true;
	cod_rotina_pai->Color = AppConfig->Colors->Disabled;
   ico_index->ItemIndex = 0;
	HabilitarItens(true);
	ico_index->Color = AppConfig->Colors->Enabled;
	cod_rotina->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtAddChildExecute(TObject *Sender)
{
	TTreeNode *Node = TreeMenu->Selected;
	Node = TreeMenu->Items->AddChild(Node, "Novo filho.");
   Node->Data = NULL;
	TreeMenu->Selected = Node;
	Variant Parent = CadMenu->FieldByName("cod_rotina")->Value;
	CadMenu->Insert();
	CadMenu->FieldByName("cod_rotina_pai")->Value = Parent;
   CadMenu->FieldByName("ord_rotina")->Value = (Node->Index + 1);
	pWorkEdition->SetWorkEdition(true,true,AppConfig->Colors->Enabled);
	cod_rotina_pai->ReadOnly = true;
	cod_rotina_pai->Color = AppConfig->Colors->Disabled;
   ico_index->ItemIndex = 0;
	HabilitarItens(true);
	ico_index->Color = AppConfig->Colors->Enabled;
	cod_rotina->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtEditExecute(TObject *Sender)
{
	HabilitarItens(true);
	pWorkEdition->SetWorkEdition(true,false,AppConfig->Colors->Enabled);
	CadMenu->Edit();
	ico_index->Color = AppConfig->Colors->Enabled;
	den_rotina->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtSaveExecute(TObject *Sender)
{
	bool inclui = false;
	if (!VerificaCampos())
		return;
	if (CadMenu->State == dsInsert) {
		if (!ValidaCampos())
			return;
		inclui = true;
	}
	String TextNode;
	TTreeNode *Node = TreeMenu->Selected;
   CadMenu->FieldByName("ico_index")->AsInteger = ico_index->ItemsEx->Items[ico_index->ItemIndex]->ImageIndex;
	CadMenu->Post();
   if (CadMenu->FieldByName("programa")->AsString.Length() > 0) {
      TextNode = CadMenu->FieldByName("programa")->AsString.UpperCase() + " - " + CadMenu->FieldByName("den_rotina")->AsString;
   } else {
      TextNode = CadMenu->FieldByName("den_rotina")->AsString;
   }
	Node->Text = TextNode;
	if (inclui) {
		SfgMenuInfo *MenuInfo = new SfgMenuInfo();
      MenuInfo->cod_rotina = CadMenu->FieldByName("cod_rotina")->AsString;
		Node->Data = (void*)MenuInfo;
	}
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
	ico_index->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtCancelExecute(TObject *Sender)
{
	TTreeNode *Node;
	TTreeNode *Prew = NULL;
	if (CadMenu->State == dsInsert) {
		Node = TreeMenu->Selected;
		Prew = Node->getPrevSibling();
		if(Prew == NULL) {
			Prew = Node->GetPrev();
		}
		if (Node) {
			TreeMenu->Items->Delete(Node);
		}
	}
	CadMenu->Cancel();
	pWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
	HabilitarItens(false);
	ico_index->Color = AppConfig->Colors->Disabled;
	if (Prew != NULL) {
		TreeMenu->Selected = Prew;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtDeleteExecute(TObject *Sender)
{
	TTreeNode *Node = TreeMenu->Selected;
   SfgMenuInfo *MenuInfo;
   if (Node->HasChildren) {
		MessageBox(Handle, "Somente é possível excluir uma rotina que não tenha nenhum nível abaixo dela. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		return;
	}
	if (MessageBox(Handle,"Deseja excluir a rotina do menu?\n"
      "Após a exclusão não será possível recuperar cadastro!",
		"Excluir",APP_QUESTION | MB_DEFBUTTON2) == IDNO) {
		return;
	}
   CadMenu->Delete();
   MenuInfo = (SfgMenuInfo*)Node->Data;
   delete MenuInfo;
   TreeMenu->Items->Delete(Node);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::btExitClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1010::VerificaCampos()
{
	if(!cod_rotina->Text.Length()) {
		MessageBox(Handle, "Digite o código da rotina do menu!",Caption.c_str(),APP_ATENTION);
		cod_rotina->SetFocus();
		return false;
	}
	if(!den_rotina->Text.Length()) {
		MessageBox(Handle, "Digite a denominação da rotina do menu!",Caption.c_str(),APP_ATENTION);
		den_rotina->SetFocus();
		return false;
	}
/*	if(!tipo_rotina->Field->AsString.Length()) {
		MessageBox(Handle, "Informe a natureza da conta contábil!",Caption.c_str(),APP_ATENTION);
		tipo_rotina->SetFocus();
		return false;
	}*/
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1010::ValidaCampos()
{
	String SQL;
	SQL = "SELECT cod_rotina FROM tbl_menu_sistema" \
			" WHERE cod_rotina = " + QuotedStr(cod_rotina->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Rotina de menu já cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_rotina->SetFocus();
		return false;
	}
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::ico_indexChange(TObject *Sender)
{
	TTreeNode *Node;
	Node = TreeMenu->Selected;
   if (Node != NULL) { 
      Node->ImageIndex = ico_index->ItemsEx->Items[ico_index->ItemIndex]->ImageIndex;
      Node->SelectedIndex = Node->ImageIndex;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::btSearchFormClick(TObject *Sender)
{
   ShowAppForms();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::ShowAppForms()
{
   SfgForm *AppForm;
   TForm *form = new TForm(Application);
   TStringAlignGrid *grdAppForms = new TStringAlignGrid(form);
   form->ClientHeight = 154;
   form->ClientWidth = 402;
   form->BorderStyle = bsDialog;
   form->BorderIcons = TBorderIcons() << biSystemMenu;
   form->Caption = "Escolher Programa";
   form->Position = poDesktopCenter;
   grdAppForms->Parent = form;
   grdAppForms->ColCount = 4;
   grdAppForms->DefaultRowHeight = 18;
   grdAppForms->AlignCol[1] = alCenter;
   grdAppForms->AlignCell[1][0] = alCenter;
   grdAppForms->AlignCell[2][0] = alCenter;
   grdAppForms->Cells[1][0] = "Programa";
   grdAppForms->Cells[2][0] = "Título";
   grdAppForms->Cells[3][0] = "Módulo";
   grdAppForms->ColWidths[0] = 14;
   grdAppForms->ColWidths[1] = 74;
   grdAppForms->ColWidths[2] = 190;
   grdAppForms->ColWidths[3] = 100;
   grdAppForms->Align = alClient;
   grdAppForms->OnDblClick = &grdAppFormsDblClick;
   grdAppForms->Options = grdAppForms->Options << goColSizing << goRowSelect;
   grdAppForms->RowCount = 2;

   for (int i=0; i<AppForms->Count;i++) {
      AppForm = (SfgForm*)AppForms->Items[i];
      if (i > 0)
        grdAppForms->RowCount++;
      grdAppForms->Cells[1][i+1] = AppForm->FormClass;
      grdAppForms->Cells[2][i+1] = AppForm->FormTitle;
      switch(AppForm->FormModule) {
         case APP_MODULO_ESTOQUE:
            grdAppForms->Cells[3][i+1] = "Estoque";
            break;
         case APP_MODULO_COMPRAS:
            grdAppForms->Cells[3][i+1] = "Compras";
            break;
         case APP_MODULO_VENDAS:
            grdAppForms->Cells[3][i+1] = "Vendas";
            break;
         case APP_MODULO_FINANCAS:
            grdAppForms->Cells[3][i+1] = "Finanças";
            break;
         default:
            grdAppForms->Cells[3][i+1] = "Padrão";
      }
   }
   grdAppForms->SortColumn(1,true);
   grdAppForms->Row = 1;
   form->ShowModal();
   delete form;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::grdAppFormsDblClick(TObject *Sender)
{
   TStringAlignGrid *grdAppForms = (TStringAlignGrid*)Sender;
   programa->Field->AsString = grdAppForms->Cells[1][grdAppForms->Row];
   modulo->Field->Value = modulo->GetValueByText(grdAppForms->Cells[3][grdAppForms->Row]);
   if(cod_rotina->Field->AsString.Length() <= 0) {
      cod_rotina->Field->AsString = grdAppForms->Cells[1][grdAppForms->Row];
   }
   if(den_rotina->Field->AsString.Length() <= 0) {
      den_rotina->Field->AsString = grdAppForms->Cells[2][grdAppForms->Row];
   }
   ((TForm*)grdAppForms->Parent)->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execBtPadraoExecute(TObject *Sender)
{
   TStringStream *StrStream;
	HRSRC HrSql;
	HGLOBAL SqlData;
	DWORD szbf;
   String sCodRotina, sSQL;

   if (MessageBox(Handle,"Confirma a carga do menu padrão do sistema?",Caption.c_str(),APP_QUESTION|MB_DEFBUTTON2) == IDNO)
      return;

   StrStream = new TStringStream("");
	HrSql = FindResource(HInstance, "MENUPADRAO", RT_RCDATA);
	SqlData = LoadResource(HInstance, HrSql);
   szbf = SizeofResource(HInstance, HrSql);
   StrStream->Write(SqlData,szbf);
   StrStream->Seek(0, soFromBeginning);

   XMLLoadMenu->LoadFromStream(StrStream); 

	TZQuery *QyMenuItem = new TZQuery(Application);
	QyMenuItem->Connection = AppConnection;

   IXMLNodeList *NodeList = XMLLoadMenu->ChildNodes;
   NodeList = NodeList->FindNode("MenuSFG")->ChildNodes;
   IXMLNode *InstNode = NULL;
   IXMLNodeList *AtrsNode = NULL;
   IXMLNode *AtrNode = NULL;

   int iNumInsts = NodeList->GetCount();
   for (int i=0; i < iNumInsts; i++) {
      InstNode = NodeList->Nodes[i];
      if (InstNode != NULL) {
         AtrsNode = InstNode->GetAttributeNodes();
         if (AtrsNode != NULL) {
            AtrNode = AtrsNode->FindNode("cod_rotina");
            if (AtrNode != NULL) {
               sCodRotina = String(AtrNode->Text).Trim();
               sSQL = "SELECT 1 FROM tbl_menu_sistema WHERE cod_rotina = " + QuotedStr(sCodRotina);
               if (!ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL)) {
                  sSQL = InstNode->Text;
                  QyMenuItem->SQL->Text = sSQL;
                  try {
                     QyMenuItem->ExecSQL();
	               }
                  catch (Exception &e) {
                     String Msg = "Ocorreu o seguinte erro:\n" + e.Message +\
                      "\nAo executar o comando de ordem " + IntToStr(i+1) + \
                      " da carga do menu padrão.";
                     MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",APP_ERROR);
                  }
               }
            }
         }
      }
   }

   delete QyMenuItem;
   delete StrStream;

   //Recarrega o menu
   FreeTreeNodes(TreeMenu->Items->GetFirstNode(), -1);
   CadMenu->Refresh();
   CarregaMenu(NULL);
   CadMenu->Filtered = false;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::execSaveMenuExecute(TObject *Sender)
{
   SaveMenuToXml();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1010::SaveMenuToXml()
{
   TXMLDocument *XMLSaveMenu = new TXMLDocument("");
   XMLSaveMenu->Active = true;
   XMLSaveMenu->Version = "1.0";
   XMLSaveMenu->Encoding = "utf-8";
   _di_IXMLNode pXmlNode = XMLSaveMenu->AddChild("MenuSFG");
   _di_IXMLNode pXmlItem = NULL;

   String sCmdSQL;
   TBookmark SavePlace = CadMenu->GetBookmark();
   CadMenu->DisableControls(); //Para desativar a atualização da tela
   CadMenu->First();
   while (!CadMenu->Eof) {
      pXmlItem = pXmlNode->AddChild("MenuItem");
      pXmlItem->SetAttribute("cod_rotina",OleVariant(CadMenu->FieldByName("cod_rotina")->AsString));
      sCmdSQL = "INSERT INTO tbl_menu_sistema (cod_rotina, ord_rotina, cod_rotina_pai, den_rotina, programa, ico_index, modulo) VALUES (";

      sCmdSQL += QuotedStr(CadMenu->FieldByName("cod_rotina")->AsString);
      sCmdSQL = sCmdSQL + "," + CadMenu->FieldByName("ord_rotina")->AsInteger;
      if (CadMenu->FieldByName("cod_rotina_pai")->AsString.Length() > 0)
         sCmdSQL = sCmdSQL + "," + QuotedStr(CadMenu->FieldByName("cod_rotina_pai")->AsString);
      else
         sCmdSQL += ",NULL";
      sCmdSQL = sCmdSQL + "," + QuotedStr(CadMenu->FieldByName("den_rotina")->AsString);
      if (CadMenu->FieldByName("programa")->AsString.Length() > 0)
         sCmdSQL = sCmdSQL + "," + QuotedStr(CadMenu->FieldByName("programa")->AsString);
      else
         sCmdSQL += ",NULL";
      sCmdSQL = sCmdSQL + "," + CadMenu->FieldByName("ico_index")->AsInteger;
      if (CadMenu->FieldByName("modulo")->AsInteger > 0)
         sCmdSQL = sCmdSQL + "," + CadMenu->FieldByName("modulo")->AsInteger;
      else
         sCmdSQL += ",NULL";
      sCmdSQL += ");";
      
      pXmlItem->SetText(WideString(sCmdSQL));
      
      CadMenu->Next();
   }
   CadMenu->GotoBookmark(SavePlace);
   CadMenu->FreeBookmark(SavePlace);
   CadMenu->EnableControls(); //Para ativar a atualização da tela

   XMLSaveMenu->SaveToFile("MenuPadrao.xml");

   delete XMLSaveMenu;
}
//---------------------------------------------------------------------------


