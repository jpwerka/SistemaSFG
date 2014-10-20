/*
Módulo: Compras
Função: Registro Recebimento Pedidos de Compra
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uSup1003.h"
//--------------------------------------------------------------------- 
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------
__fastcall TSup1003::TSup1003(TComponent* AOwner)
	: TForm(AOwner)
{
	cod_pedido_compra->Color = AppConfig->Colors->Disabled;
	data_recebimento->Color = AppConfig->Colors->Disabled;
	data_recebimento->Text = FormatDateTime("dd/mm/yyyy", Date());
	OnRecebeSucess = NULL;
}
//---------------------------------------------------------------------
void __fastcall TSup1003::QyCadProdutoBeforeInsert(TDataSet *DataSet)
{
	Abort();
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::grdItensKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
	if (Shift.Contains(ssCtrl) && Key == 46) {
		Key =0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::grdEditCtrlKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::QyCadProdutoBeforeEdit(TDataSet *DataSet)
{
class TGrdItensGrid : public TDBGrid
{
public:
	__property InplaceEditor;
};
	TEdit *pEdtCtr = NULL;
	if (grdItens->SelectedField->FieldName == "qtd_recebida") {
		pEdtCtr = (TEdit*)((TGrdItensGrid*)grdItens)->InplaceEditor;
		if(pEdtCtr != NULL) {
			pEdtCtr->OnKeyPress = &grdEditCtrlKeyPress;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::btOKClick(TObject *Sender)
{
try {
   if (!SfgDataCenter->StartTrans()) {
      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
      return;
   }
	QyCadProduto->ApplyUpdates();
	if (OnRecebeSucess != NULL)
		OnRecebeSucess();
	SfgDataCenter->CommitTrans();
	Close();
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	SfgDataCenter->RollbackTrans();
}
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::btCancelClick(TObject *Sender)
{
	QyCadProduto->CancelUpdates();
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSup1003::grdItensTitleClick(TColumn *Column)
{
	QyCadProduto->SortedFields = Column->FieldName;
}
//---------------------------------------------------------------------------

