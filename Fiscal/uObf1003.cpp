/*
Módulo: Vendas
Função: Importação de Pedidos de Venda para Notas Fiscais Saída
Autor.: Jackson Patrick Werka
Data..: 22/12/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#include "uSfgBrowseObf.h"
#pragma hdrstop
#include "uObf1003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TObf1003::TObf1003(TComponent* Owner)
	: TForm(Owner)
{
	num_pedido_venda = 0;
	AfterImport = NULL;
	QyPedidoVenda->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "importado") {
		bool bChecked = QyPedidoVenda->FieldByName("importado")->AsString == "S";
		DrawCheckBoxGrid(ListItens,-1,-1,Rect,State,bChecked);
	} else if (Column->Field->FieldName == "natureza_operacao") {
		DrawSearchGrid(ListItens,-1,-1,Rect,State,false);
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensCellClick(TColumn *Column)
{
	if(Column->Field->FieldName == "importado") {
		QyPedidoVenda->Edit();
		if (importado->AsString == "S") {
			importado->AsString = "N";
			num_pedido_venda--;
		} else {
			importado->AsString = "S";
			num_pedido_venda++;
		}
		QyPedidoVenda->Post();
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::btCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::btOKClick(TObject *Sender)
{
	TZQuery *QyImport;
   String sDateTime;
	if (num_pedido_venda == 0) {
		MessageBox(Handle,"Selecione ao menos um pedido para importação!",Caption.c_str(),APP_INFORM);
		return;
	}
	QyPedidoVenda->DisableControls();
	QyPedidoVenda->First();
   //Deve validar se foi informado a natureza de operação para importação
   while (!QyPedidoVenda->Eof) {
		if (QyPedidoVenda->FieldByName("importado")->AsString == "S") {
         if (QyPedidoVenda->FieldByName("natureza_operacao")->AsInteger == 0) {
		      MessageBox(Handle,"Não foi informado a natureza de operação!",Caption.c_str(),APP_INFORM);
            ListItens->SelectedField = QyPedidoVenda->FieldByName("natureza_operacao");
		      QyPedidoVenda->EnableControls();
            return;
         }
      }
      QyPedidoVenda->Next();
   }
	QyImport = new TZQuery(Application);
	QyImport->Connection = AppConnection;
	pnProgress->Show();
	ProgressImport->Max = num_pedido_venda;
	Application->ProcessMessages();
	QyPedidoVenda->First();
	while (!QyPedidoVenda->Eof) {
		if (QyPedidoVenda->FieldByName("importado")->AsString == "S") {
         if (!SfgDataCenter->StartTrans()) {
            MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
            break;
         }
			try {
            DateTimeToString(sDateTime, "yyyy-mm-dd hh:nn:ss", Now());
				QyImport->SQL->Text = "CALL fatura_pedido_venda(" \
                                   + QyPedidoVenda->FieldByName("cod_pedido_venda")->AsString + "," \
                                   + QuotedStr(AppUser->CodEmpresa) + "," \
                                   + QyPedidoVenda->FieldByName("natureza_operacao")->AsString + "," \
                                   + QuotedStr(AppUser->Usuario) + "," \
                                   + QuotedStr(sDateTime) + ");";
				QyImport->ExecSQL();
            SfgDataCenter->CommitTrans();
			} catch(Exception &e){
            SfgDataCenter->RollbackTrans();
				String Msg = "Ocorreu o seguinte erro ao importar o pedido de venda " + QyPedidoVenda->FieldByName("cod_pedido_venda")->AsString + ":\n";
				Msg = Msg + e.Message;
				MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
			}
			ProgressImport->StepIt();
			Application->ProcessMessages();
		}
		QyPedidoVenda->Next();
	}
	if (AfterImport != NULL)
		AfterImport();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::NaturezaOperacaoValidate(TField *Sender)
{
	if(!Sender->AsString.Length())
		return;
	String sSQL;
	sSQL = "SELECT cod_natureza_operacao FROM tbl_natureza_operacao" \
			" WHERE cod_natureza_operacao = " + Sender->AsString;
	if(!ValidacoesDB::ExistePrimaryKey(AppConnection,sSQL)) {
		throw Exception("Natureza de operação não cadastrada!");
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensEditButtonClick(TObject *Sender)
{
	if (ListItens->SelectedField->FieldName == "natureza_operacao") {
		SfgBrowse::EscolheNaturezaOperacao(this,&SearchNaturezaOperacao);
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::SearchNaturezaOperacao(Variant Value)
{
   QyPedidoVenda->Edit();
	natureza_operacao->Value = Value;
   QyPedidoVenda->Post();
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensColEnter(TObject *Sender)
{
	TDBGridOptions Options;
	if (ListItens->SelectedField->FieldName == "importado") {
		Options = ListItens->Options;
		Options >> dgEditing;
		ListItens->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensColExit(TObject *Sender)
{
	TDBGridOptions Options;
	if (ListItens->SelectedField->FieldName == "importado") {
		Options = ListItens->Options;
		Options << dgEditing;
		ListItens->Options = Options;
	}
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::QyPedidoVendaBeforeInsert(TDataSet *DataSet)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TObf1003::ListItensKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------

