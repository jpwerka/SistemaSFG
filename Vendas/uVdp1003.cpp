/*
Módulo: Vendas
Função: Importação de Orçamentos para Pedidos de Venda
Autor.: Jackson Patrick Werka
Data..: 07/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgDrawCmp.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uVdp1003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TVdp1003::TVdp1003(TComponent* Owner)
	: TForm(Owner)
{
	num_orcamento = 0;
	AfterImport = NULL;
	QyOrcamento->Active = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1003::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1003::ListItensDrawColumnCell(TObject *Sender,
      const TRect &Rect, int DataCol, TColumn *Column,
      TGridDrawState State)
{
	if (Column->Field->FieldName == "importado") {
		bool bChecked = QyOrcamento->FieldByName("importado")->AsString == "S";
		DrawCheckBoxGrid(ListItens,-1,-1,Rect,State,bChecked);
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1003::ListItensCellClick(TColumn *Column)
{
	if(Column->Field->FieldName == "importado") {
		QyOrcamento->Edit();
		if (importado->AsString == "S") {
			importado->AsString = "N";
			num_orcamento--;
		} else {
			importado->AsString = "S";
			num_orcamento++;
		}
		QyOrcamento->Post();
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1003::btCancelClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1003::btOKClick(TObject *Sender)
{
	TZQuery *QyImport;
	if (num_orcamento == 0) {
		MessageBox(Handle,"Selecione ao menos um orçamento para importação!",Caption.c_str(),APP_INFORM);
		return;
	}
	QyImport = new TZQuery(Application);
	QyImport->Connection = AppConnection;
	pnProgress->Show();
	ProgressImport->Max = num_orcamento;
	Application->ProcessMessages();
	QyOrcamento->DisableControls();
	QyOrcamento->First();
	while (!QyOrcamento->Eof) {
		if (importado->AsString == "S") {
			try {
				QyImport->SQL->Text = "CALL importa_orcamento(" + QyOrcamento->FieldByName("cod_orcamento")->AsString + ");";
				QyImport->ExecSQL();
			} catch(Exception &e){
				String Msg = "Ocorreu o seguinte erro ao importar o orçamento " + QyOrcamento->FieldByName("cod_orcamento")->AsString + ":\n";
				Msg = Msg + e.Message;
				MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
			}
			ProgressImport->StepIt();
			Application->ProcessMessages();
		}
		QyOrcamento->Next();
	}
	if (AfterImport != NULL)
		AfterImport();
	Close();
}
//---------------------------------------------------------------------------

