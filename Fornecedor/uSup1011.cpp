/*
Módulo: Compras - Fornecedor
Função: Cadastro Fornecedor x Produto
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgWorkEdition.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uSfgDrawCmp.h"
#include "uSup1004.h"
#pragma hdrstop
#include "uSup1011.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSup1011(void) {
   AddAppForm("Sup1011","Fornecedor x Produto",APP_MODULO_COMPRAS);
   AddAppFormClass("TSup1011",__classid(TSup1011));
}
#pragma startup RegisterSup1011
//---------------------------------------------------------------------------
__fastcall TSup1011::TSup1011(TComponent* Owner)
   : TfrmBase02(Owner)
{
	SfgToolbar->DataSource = DsCnsFornecedor;
	CarregarTipoPessoa();
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::CarregarTipoPessoa()
{
   tipo_pessoa->Clear();
   tipo_pessoa->AddItem("Pessoa Física","F");
   tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::btEditClickExecute(TObject *Sender)
{
	HabilitarItens(true);
   grdAddProduto->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::btSaveClickExecute(TObject *Sender)
{
	if (!VerificaCampos())
		return;
	try {
		try {
         if (!SfgDataCenter->StartTrans()) {
            MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
            return;
         }
			QyFornecProduto->ApplyUpdates();
         SfgDataCenter->CommitTrans();
		}
		catch(Exception &e) {
         SfgDataCenter->RollbackTrans();
         String Msg = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
         Msg = Msg + e.Message;
         MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
      }
   }
   __finally{
		btCancelClickExecute(Sender);
		SfgToolbar->btGoTo->SetFocus();
   }
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::btCancelClickExecute(TObject *Sender)
{
	QyFornecProduto->CancelUpdates();
	HabilitarItens(false);
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::addLineExecute(TObject *Sender)
{
	//Adiciona uma linha no GRID de itens
	QyFornecProduto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyFornecProduto->Insert();
	QyFornecProduto->BeforeInsert = &QyFornecProdutoBeforeInsert;
	QyFornecProduto->FieldByName("cod_fornecedor")->AsString = QyCnsFornecedor->FieldByName("cod_fornecedor")->AsString;
	QyFornecProduto->FieldByName("cod_produto")->Value = VarAsType(Variant::Empty(), varNull);
	QyFornecProduto->FieldByName("den_produto")->Value =  VarAsType(Variant::Empty(), varNull);
	QyFornecProduto->FieldByName("preco_compra")->AsFloat =  0;
	QyFornecProduto->FieldByName("data_atualizacao")->AsDateTime = Now();
	QyFornecProduto->Post();
	grdAddProduto->SetFocus();
	grdAddProduto->SelectedField = QyFornecProduto->FieldByName("cod_produto");
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::delLineExecute(TObject *Sender)
{
	if(QyFornecProduto->RecordCount > 0) {
		QyFornecProduto->Delete();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::HabilitarItens(bool Habilita)
{
	//Habilitando os itens do GRID de itens
	DsFornecProduto->AutoEdit = Habilita;
	addLine->Enabled = Habilita;
	delLine->Enabled = Habilita;
	addItens->Enabled = Habilita;
   SfgToolbar->EnableToolbarButtons(!Habilita);
}
//---------------------------------------------------------------------------
bool __fastcall TSup1011::VerificaCampos()
{
   int iCountItens = 1;
   int iQtdItens = QyFornecProduto->RecordCount;
   String sBookmark;
   String sCodProduto;
   bool bPrdIgual = false;

   QyFornecProduto->DisableControls();  //Para desativar a atualização da tela
   //Deve verificar se não ficaram linhas em branco no GRID
   QyFornecProduto->First();
   while (iCountItens < iQtdItens) {
      sBookmark = QyFornecProduto->Bookmark;
      sCodProduto = QyFornecProduto->FieldByName("cod_produto")->AsString;
      QyFornecProduto->First();
      while (!QyFornecProduto->Eof) {
         if (sBookmark != QyFornecProduto->Bookmark) {
            if (sCodProduto == QyFornecProduto->FieldByName("cod_produto")->AsString) {
               bPrdIgual = true;
               break;
            }
         }
         QyFornecProduto->Next();
      }
      if (bPrdIgual)
         break;
      QyFornecProduto->Bookmark = sBookmark;
      QyFornecProduto->Next();
      iCountItens++;
   }
   if (bPrdIgual) {
      QyFornecProduto->EnableControls(); //Para ativar a atualização da tela
      String sMsg = "O código de produto " + sCodProduto + " está sendo repetido no cadastro!";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_ATENTION);
      return false;
   }
   QyFornecProduto->EnableControls(); //Para ativar a atualização da tela

	/*if(!cod_produto->Text.Length()) {
		MessageBox(Handle, "Digite o código do produto!",Caption.c_str(),APP_ATENTION);
		cod_produto->SetFocus();
		return false;
	}
	if(preco_custo->Field->AsFloat <= 0) {
		MessageBox(Handle, "O preço de custo deve ser maior que zero!",Caption.c_str(),APP_ATENTION);
		preco_custo->SetFocus();
      return false;
   }*/
	/*if((preco_custo->Field->OldValue != preco_custo->Field->Value) &&
		data_atualizacao->Field->OldValue == data_atualizacao->Field->Value) {
		data_atualizacao->Field->Value = Now();
   }*/
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSup1011::ValidaCampos()
{
	/*String SQL;
	SQL = "SELECT cod_produto FROM tbl_fornecedor_produto" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text) +
			  " AND cod_produto = " + QuotedStr(cod_produto->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Produto já está relacionado ao fornecedor atual!",Caption.c_str(),APP_ATENTION);
		cod_produto->SetFocus();
		return false;
	}*/
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::CodProdutoValidate(TField *Sender)
{
	String SQL;
	String sRet;
	if(Sender->DisplayText.Length() <= 0) {
		QyFornecProduto->FieldByName("den_produto")->AsString = "";
		return;
	}
	SQL = "SELECT den_produto FROM tbl_produto" \
			" WHERE cod_produto = " + QuotedStr(Sender->DisplayText);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		throw Exception("Produto não cadastrado!");
	} else {
		QyFornecProduto->FieldByName("den_produto")->AsString = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::grdAddProdutoKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::QyFornecProdutoBeforeInsert(TDataSet *DataSet)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::grdAddProdutoEditButtonClick(TObject *Sender)
{
	TPoint ptGrid;
	TRect rtCell;
	String sDate;

   if (!DsFornecProduto->AutoEdit)
      return;

	if (grdAddProduto->SelectedField->FieldName == "cod_produto") {
		SfgBrowse::EscolheProduto(this,&SearchProduto);
	} else if (grdAddProduto->SelectedField->FieldName == "data_atualizacao") {
		ptGrid.x = 0; ptGrid.y = 0;
		ptGrid = grdAddProduto->ClientToParent(ptGrid,this);
		THackCustomGrid *pHackGrid = (THackCustomGrid*)grdAddProduto;
		rtCell = pHackGrid->CellRect(pHackGrid->Col, pHackGrid->Row);
		rtCell.Left += ptGrid.x;
		rtCell.Top += ptGrid.y + 4;
		rtCell.Right += ptGrid.x;
		rtCell.Bottom += ptGrid.y + 4;
		sDate = ExecCalendarRect(rtCell,grdAddProduto->SelectedField->AsString);
		if(sDate.Length() > 0) {
         if (!(QyFornecProduto->State == dsEdit))
            QyFornecProduto->Edit();
         grdAddProduto->SelectedField->AsString = sDate;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::SearchProduto(Variant Value) {
	if (QyFornecProduto->State != dsEdit)
		QyFornecProduto->Edit();
	QyFornecProduto->FieldByName("cod_produto")->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::grdAddProdutoDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "cod_produto") {
		DrawSearchGrid(grdAddProduto,-1,-1,Rect,State,false);
	} else if (Column->Field->FieldName == "data_atualizacao") {
		DrawCalendarGrid(grdAddProduto,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::addItensExecute(TObject *Sender)
{
	TStrings *SQL = new TStringList();
	SQL->Add("SELECT p.cod_produto, p.den_produto, p.cod_unid_medida, 0 val_produto");
	SQL->Add("FROM tbl_produto p");
	SQL->Add("WHERE p.cod_familia = :cod_familia");
	SQL->Add("AND p.ies_ativo = 'S'");
	SQL->Add("ORDER BY p.cod_produto");
	TSup1004 *Sup1004 = new TSup1004(Application);
	Sup1004->OnConfirmList = &addItensConfirm;
	Sup1004->QyCnsProduto->SQL->Assign(SQL);
   Sup1004->edtQtd->Text = '1';
   Sup1004->edtQtd->Visible = false;
   Sup1004->lbQtde->Visible = false;
	Sup1004->ShowModal();
   delete Sup1004;
	delete SQL;
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::addItensConfirm(TList *pListAdd)
{
struct SelProdutos {
	String cod_produto;
	String den_produto;
	float  val_produto;
	float  qtd_produto;
};
	SelProdutos *pSelProdutos;

   QyFornecProduto->Last();
try {
	//Adiciona uma linha no GRID de itens
	QyFornecProduto->BeforeInsert = NULL; //Desativando evento de bloqueio de INSERT manual
	QyFornecProduto->FieldByName("cod_produto")->OnValidate = NULL;
try {
	for (int i=0; i<pListAdd->Count; i++) {
		pSelProdutos = (SelProdutos*)pListAdd->Items[i];
		QyFornecProduto->Insert();
      QyFornecProduto->FieldByName("cod_fornecedor")->AsString = QyCnsFornecedor->FieldByName("cod_fornecedor")->AsString;
		QyFornecProduto->FieldByName("cod_produto")->AsString = pSelProdutos->cod_produto;
		QyFornecProduto->FieldByName("den_produto")->AsString = pSelProdutos->den_produto;
		QyFornecProduto->FieldByName("preco_compra")->AsFloat = pSelProdutos->val_produto;
      QyFornecProduto->FieldByName("data_atualizacao")->AsDateTime = Now();
		QyFornecProduto->Post();
	}
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao incluir vários itens:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//Sempre vai passar por aqui, mesmo dando erro
__finally {
	QyFornecProduto->BeforeInsert = &QyFornecProdutoBeforeInsert;
	QyFornecProduto->FieldByName("cod_produto")->OnValidate = &CodProdutoValidate;
}

}
//---------------------------------------------------------------------------
void __fastcall TSup1011::QyCnsFornecedorAfterOpen(TDataSet *DataSet)
{
	QyFornecProduto->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TSup1011::QyCnsFornecedorBeforeClose(TDataSet *DataSet)
{
	QyFornecProduto->Active = false;
}
//---------------------------------------------------------------------------

