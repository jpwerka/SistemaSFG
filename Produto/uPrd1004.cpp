/*
Módulo: Produtos
Função: Atualização de Preços de Produtos
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#include "uSfgBrowsePrd.h"
#include "uSfgBrowseSup.h"
#pragma hdrstop
#include "uPrd1004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterPrd1004(void) {
   AddAppForm("Prd1004","Atualizar Preços dos Produtos",APP_MODULO_ESTOQUE);
   AddAppFormClass("TPrd1004",__classid(TPrd1004));
}
#pragma startup RegisterPrd1004
//---------------------------------------------------------------------------
__fastcall TPrd1004::TPrd1004(TComponent* Owner)
	: TfrmBase01(Owner)
{
	grdProdutos->Objects[0][1] = (TObject*)new bool(false);
	HabilitaCampos(false);
	FInformado = false;
	den_fornecedor->Color = AppConfig->Colors->Disabled;
	den_familia->Color = AppConfig->Colors->Disabled;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::SetPermissao(int Nivel)
{
   if (Nivel == APP_PERM_TOTAL)
      return;

   //Escondendo as opções de menu do SfgToolbar
	execInformar->Visible = false;
	execProcessar->Visible = false;
   //Desabilitando as teclas de atalho também
	execInformar->Enabled = false;
	execProcessar->Enabled = false;
   btSair->Left = 6;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::execPesquisaExecute(TObject *Sender)
{
	if (Screen->ActiveControl == NULL)
     return;
	if(Screen->ActiveControl->InheritsFrom(__classid(TEdit))) {
		pEditRet = (TEdit*)Screen->ActiveControl;
		if(pEditRet->Name == "cod_fornecedor") {
			SfgBrowse::EscolheFornecedor(this,&SearchReturn);
		} else if(pEditRet->Name == "cod_familia") {
			SfgBrowse::EscolheFamilia(this,&SearchReturn);
		} else if(pEditRet->Name == "cod_produto_ini") {
			SfgBrowse::EscolheProduto(this,&SearchReturn);
		} else if(pEditRet->Name == "cod_produto_fim") {
			SfgBrowse::EscolheProduto(this,&SearchReturn);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::SearchReturn(Variant Value) {
	pEditRet->Text = VarToStr(Value);
	if(pEditRet->Name == "cod_fornecedor") {
		cod_fornecedorExit(pEditRet);
	} else if(pEditRet->Name == "cod_familia") {
		cod_familiaExit(pEditRet);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::cod_fornecedorExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_fornecedor->Text.Length() <= 0) {
		den_fornecedor->Text = "";
		return;
	}
	SQL = "SELECT den_fornecedor FROM tbl_fornecedor" \
			" WHERE cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Fornecedor não cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_fornecedor->SetFocus();
	} else {
		den_fornecedor->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::cod_familiaExit(TObject *Sender)
{
	String SQL;
	String sRet;
	if(cod_familia->Text.Length() <= 0) {
		den_familia->Text = "";
		return;
	}
	SQL = "SELECT den_familia FROM tbl_familia" \
			" WHERE cod_familia = " + QuotedStr(cod_familia->Text);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,SQL);
	if(sRet.Length() <= 0) {
		MessageBox(Handle, "Família não cadastrada!",Caption.c_str(),APP_ATENTION);
		cod_familia->SetFocus();
	} else {
		den_familia->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btSearchFornecedorClick(TObject *Sender)
{
	pEditRet = cod_fornecedor;
	SfgBrowse::EscolheFornecedor(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btSearchFamiliaClick(TObject *Sender)
{
	pEditRet = cod_familia;
	SfgBrowse::EscolheFamilia(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btSearchProdutoIniClick(TObject *Sender)
{
	pEditRet = cod_produto_ini;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btSearchProdutoFimClick(TObject *Sender)
{
	pEditRet = cod_produto_fim;
	SfgBrowse::EscolheProduto(this,&SearchReturn);
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::ClearObjectsCheck()
{
	bool *check;
	System::Currency *curr;
	for( int i=1; i < grdProdutos->RowCount; i++) {
		check = (bool*)grdProdutos->Objects[0][i];
		delete check;
		curr = (System::Currency*)grdProdutos->Objects[5][i];
		delete curr;
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btAtualizaClick(TObject *Sender)
{
	String SQL;
	int row = 0;
	float val_percent = 0;
	System::Currency preco_final;

	val_percent = StrToFloat(percentual->Text);
	if (val_percent <= 0) {
		MessageBox(Handle,"Informe um percentual maior que zero!", Caption.c_str(), APP_INFORM);
		return;
	}

	SQL = "SELECT f.den_familia,"\
					" p.cod_produto, p.den_produto,"\
					" p.preco_venda"\
			 " FROM tbl_produto p, tbl_familia f";
	if (cod_fornecedor->Text.Length()) {
		SQL += " ,tbl_fornecedor_produto o";
	}
	SQL += " WHERE p.cod_familia = f.cod_familia";
	if (cod_fornecedor->Text.Length()) {
		SQL += " AND o.cod_produto = p.cod_produto"\
				 " AND o.cod_fornecedor = " + QuotedStr(cod_fornecedor->Text);
	}
	if(cod_familia->Text.Length()) {
		SQL += " AND p.cod_familia = " + cod_familia->Text;
	}
	if(cod_produto_ini->Text.Length()) {
		SQL += " AND p.cod_produto >= " + QuotedStr(cod_produto_ini->Text);
	}
	if(cod_produto_fim->Text.Length()) {
		SQL += " AND p.cod_produto <= " + QuotedStr(cod_produto_fim->Text);
	}
	SQL += " ORDER BY f.den_familia,p.cod_produto";

	//Limpando os objetos anteriores
	RestauraGrid();
	//Carrega o GRID de produtos
	QyAtuProdutos->Active = false;
	QyAtuProdutos->SQL->Text = SQL;
	QyAtuProdutos->Active = true;
	if (QyAtuProdutos->RecordCount > 0) {
		grdProdutos->RowCount = QyAtuProdutos->RecordCount + 1;
		grdProdutos->OnMouseUp = &grdProdutosMouseUp;
	}
	QyAtuProdutos->First();
	while(!QyAtuProdutos->Eof) {
		row++;
		grdProdutos->Objects[0][row] = (TObject*)new bool(true);
		grdProdutos->Cells[2][row] = QyAtuProdutos->FieldByName("den_familia")->AsString;
		grdProdutos->Cells[3][row] = QyAtuProdutos->FieldByName("cod_produto")->AsString;
		grdProdutos->Cells[4][row] = QyAtuProdutos->FieldByName("den_produto")->AsString;
		preco_final = QyAtuProdutos->FieldByName("preco_venda")->AsCurrency;
		grdProdutos->Cells[5][row] = CurrToStrF(preco_final,ffCurrency,2);
		preco_final += (preco_final * (val_percent / 100));
		grdProdutos->Cells[6][row] = CurrToStrF(preco_final,ffCurrency,2);
		grdProdutos->Objects[6][row] = (TObject*)new System::Currency(preco_final);
		QyAtuProdutos->Next();
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::grdProdutosDrawCell(TObject *Sender,
		int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
	if (grdProdutos->Cells[ACol][0] == "X") {
		bool bChecked = (bool*)grdProdutos->Objects[0][ARow];
		DrawCheckBoxGrid(grdProdutos,ACol,ARow,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::percentualKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(percentual->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::HabilitaCampos(bool Habilita) {
	TColor Color = AppConfig->Colors->Enabled;
	cod_fornecedor->ReadOnly = !Habilita;
	cod_familia->ReadOnly = !Habilita;
	cod_produto_ini->ReadOnly = !Habilita;
	cod_produto_fim->ReadOnly = !Habilita;
	percentual->ReadOnly = !Habilita;
	btSearchFornecedor->Enabled = Habilita;
	btSearchFamilia->Enabled = Habilita;
	btSearchProdutoIni->Enabled = Habilita;
	btSearchProdutoFim->Enabled = Habilita;
	execAtualizar->Enabled = Habilita;
	execPesquisa->Enabled = Habilita;
	execInformar->Enabled = !Habilita;
	execProcessar->Enabled = !Habilita;
	btSair->Enabled = !Habilita;
	execConfirmar->Enabled = Habilita;
	execCancelar->Enabled = Habilita;
	btConfirmar->Visible = Habilita;
	btCancelar->Visible = Habilita;
	if (!Habilita) {
		Color = AppConfig->Colors->Disabled;
	}
	cod_fornecedor->Color = Color;
	cod_familia->Color = Color;
	cod_produto_ini->Color = Color;
	cod_produto_fim->Color = Color;
	percentual->Color = Color;
	UpDownPercent->Enabled = Habilita;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::RestauraGrid() {
	bool *obj = new bool(false);
	ClearObjectsCheck();
	grdProdutos->OnMouseUp = NULL;
	grdProdutos->RowCount = 2;
	grdProdutos->Rows[1]->Clear();
	grdProdutos->Rows[1]->Add("");
	grdProdutos->Rows[1]->Add("");
	grdProdutos->Rows[1]->Add("");
	grdProdutos->Rows[1]->Add("");
	grdProdutos->Rows[1]->Add("");
	grdProdutos->Rows[1]->Add("R$ 0,00");
	grdProdutos->Rows[1]->Add("R$ 0,00");
	grdProdutos->Objects[0][1] = (TObject*)obj;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::execInformarExecute(TObject *Sender)
{
	HabilitaCampos(true);
	RestauraGrid();
	FInformado = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::execConfirmarExecute(TObject *Sender)
{
	bool *check;
	for( int i=1; i < grdProdutos->RowCount; i++) {
		check = (bool*)grdProdutos->Objects[0][i];
		if (*check)
			break;
	}
	if (!(*check)) {
		MessageBox(Handle,"Informe pelo menos um produto para atualizar!", Caption.c_str(), APP_INFORM);
		return;
	}

	HabilitaCampos(false);
	//Desabiltando para o usuário não poder clicar no GRID
	grdProdutos->OnMouseUp = NULL;
	FInformado = true;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::execCancelarExecute(TObject *Sender)
{
	HabilitaCampos(false);
	RestauraGrid();
	FInformado = false;
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::btSairClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::execProcessarExecute(TObject *Sender)
{
	bool *check;
	System::Currency *curr;
	bool sucesso = true;
	String Msg;
	if (!FInformado) {
		MessageBox(Handle,"Informe os dados primeiro!", Caption.c_str(), APP_INFORM);
		return;
	}

   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }

	try {
		for( int i=1; i < grdProdutos->RowCount; i++) {
			check = (bool*)grdProdutos->Objects[0][i];
			if (*check) {
				curr = (System::Currency*)grdProdutos->Objects[6][i];
				QyAtuPrecoProduto->Params->ParamByName("preco_final")->Value = curr;
				QyAtuPrecoProduto->Params->ParamByName("cod_produto")->Value = grdProdutos->Cells[3][i];
				QyAtuPrecoProduto->ExecSQL();
			}
		}
	}
	catch(Exception &e){
		Msg = "Ocorreu um erro ao atualizar os preços dos produtos:\n";
		Msg = Msg + e.Message;
		sucesso = false;
	}
	if (sucesso) {
		SfgDataCenter->CommitTrans();
		MessageBox(Handle,"Atualização de preços efetuada com sucesso!", Caption.c_str(), APP_INFORM);
	}
	else {
		SfgDataCenter->RollbackTrans();
		MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TPrd1004::grdProdutosMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TGridCoord lCell;
	bool *check;
	lCell = grdProdutos->MouseCoord(X, Y);
	if (lCell.X == 1 && lCell.Y > 0) {
		check = (bool*)grdProdutos->Objects[0][lCell.Y];
		*check = !(*check);
		//Esta linha é só pra forcar ele redesenhar a célula
		grdProdutos->Cells[1][lCell.Y] = "";
	}
}
//---------------------------------------------------------------------------

