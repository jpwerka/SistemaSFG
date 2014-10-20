//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uSup1004.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
struct SelProdutos {
	String cod_produto;
	String den_produto;
	float  val_produto;
	float  qtd_produto;
};
//---------------------------------------------------------------------------
__fastcall TSup1004::TSup1004(TComponent* Owner)
	: TForm(Owner)
{
	TZReadOnlyQuery *QyFamilia = new TZReadOnlyQuery(this);
	QyFamilia->Connection = AppConnection;
	QyFamilia->SQL->Text = "SELECT cod_familia, den_familia FROM tbl_familia ORDER BY cod_familia";
	QyFamilia->Active = true;
	QyFamilia->First();
	while(!QyFamilia->Eof) {
		cbFamilia->AddItem(QyFamilia->FieldByName("den_familia")->AsString,
								 (TObject*)new int(QyFamilia->FieldByName("cod_familia")->AsInteger));
		QyFamilia->Next();
	}
	QyFamilia->Active = false;
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::FormClose(TObject *Sender, TCloseAction &Action)
{
	int i;
	int *iCodFamilia;

	LimpaItemObjects(ItensAll);
	LimpaItemObjects(ItensAdd);
	for(i=0;i<cbFamilia->Items->Count;i++) {
		iCodFamilia = (int*)cbFamilia->Items->Objects[i];
		delete iCodFamilia;
	}
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::LimpaItemObjects(TListBox *Lista)
{
	int i;
	SelProdutos *pListProdutos;
	if(Lista->Items->Count <= 0) {
		return;
	}
	for(i=0;i<Lista->Items->Count;i++) {
		pListProdutos = (SelProdutos*)Lista->Items->Objects[i];
		delete pListProdutos;
	}
	Lista->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::cbFamiliaChange(TObject *Sender)
{
	int *iCodFamilia;
	SelProdutos *pListProdutos;
	String sText;
	if (cbFamilia->ItemIndex < 0)
		return;
	iCodFamilia = (int*)cbFamilia->Items->Objects[cbFamilia->ItemIndex];
	QyCnsProduto->Params->ParamByName("cod_familia")->Value = iCodFamilia;
	QyCnsProduto->Open();
	LimpaItemObjects(ItensAll);
	while(!QyCnsProduto->Eof) {
		pListProdutos = new SelProdutos();
		pListProdutos->cod_produto = QyCnsProduto->FieldByName("cod_produto")->AsString;
		pListProdutos->den_produto = QyCnsProduto->FieldByName("den_produto")->AsString;
		pListProdutos->val_produto = QyCnsProduto->FieldByName("val_produto")->AsFloat;
		pListProdutos->qtd_produto = 1;
		sText = pListProdutos->cod_produto + " - " + pListProdutos->den_produto;
		ItensAll->AddItem(sText,(TObject*)pListProdutos);
		QyCnsProduto->Next();
	}
	QyCnsProduto->Close();
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::btAddClick(TObject *Sender)
{
	int i;
	float fQtdProduto = 0;
	SelProdutos *pListProdutos, *pSelProdutos;
	if(ItensAll->Items->Count <= 0) {
		return;
	}
	try {
		fQtdProduto = StrToFloat(edtQtd->Text);
	}
	__finally {}
	if (fQtdProduto <= 0 ) {
		MessageBox(Handle,"Informe a quantidade dos produtos maior que zero!",Caption.c_str(),APP_INFORM);
		return;
	}
	for(i=0;i<ItensAll->Items->Count;i++) {
		if (ItensAll->Selected[i]) {
			pListProdutos = (SelProdutos*)ItensAll->Items->Objects[i];
			pSelProdutos = new SelProdutos();
			pSelProdutos->cod_produto = pListProdutos->cod_produto;
			pSelProdutos->den_produto = pListProdutos->den_produto;
			pSelProdutos->val_produto = pListProdutos->val_produto;
			pSelProdutos->qtd_produto = fQtdProduto;
			ItensAdd->AddItem(ItensAll->Items->Strings[i],(TObject*)pSelProdutos);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::edtQtdKeyPress(TObject *Sender, char &Key)
{
	Validacoes::ValidarFloat(edtQtd->Text, Key);
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::btRemoveClick(TObject *Sender)
{
	int i;
	SelProdutos *pSelProdutos;
	for(i=0;i<ItensAdd->Items->Count;i++) {
		if (ItensAdd->Selected[i]) {
			pSelProdutos = (SelProdutos*)ItensAdd->Items->Objects[i];
			delete pSelProdutos;
			ItensAdd->Items->Delete(i);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1004::btOKClick(TObject *Sender)
{
	int i;
	if(ItensAdd->Items->Count> 0) {
		TList *pListAdd = new TList();
		for(i=0;i<ItensAdd->Items->Count;i++) {
			pListAdd->Add(ItensAdd->Items->Objects[i]);
		}
		this->OnConfirmList(pListAdd);
		delete pListAdd;
	}
	Close();
}
//---------------------------------------------------------------------------

