//---------------------------------------------------------------------------
#include "uFrmCriptoTxt.h"
#include "StdControls.h"
//---------------------------------------------------------------------------
FrmCriptoTxt *frmCriptoTxt = NULL;
//---------------------------------------------------------------------------
char *EncryptText(char *Source)
{
  char *Dest;
  int I,L;
  unsigned char A;
  L = strlen(Source);
  Dest = new char[L+1];

  for(I = 0; I < L; I++) {
		A = (int)Source[L - I - 1];
	  Dest[I] = (char)((270 + I) - (int)A);
  }

  Dest[L] = '\0';
  return Dest;
}
//---------------------------------------------------------------------------
FrmCriptoTxt::FrmCriptoTxt(): GradientForm()
{
	this->OnCreate = MakeDelegate(this, &FrmCriptoTxt::FormOnCreate);
	this->OnClose = MakeDelegate(this, &FrmCriptoTxt::FormOnClose);
	this->setIsGradient(true);
	this->setGrOrientation(GRADIENT_FILL_RECT_H);
	this->setFromColor(0x80ffff);
	this->setToColor(0x80ff80);
}
//---------------------------------------------------------------------------
FrmCriptoTxt::~FrmCriptoTxt(){}
//---------------------------------------------------------------------------
void FrmCriptoTxt::FormOnCreate(WindowBase *wB)
{
	TxtNormal  = new TextBox();
	TxtCriptoN = new TextBox();
	TxtMascara = new TextBox();
	TxtCriptoM = new TextBox();
	BtCriptoTxt = new Button();
	BtCancelar = new Button();
	TxtNormal->AppendControl(this, 1000, TJ_EDT);
	TxtCriptoN->AppendControl(this,1001,TJ_EDT);
	TxtMascara->AppendControl(this,1002,TJ_EDT);
	TxtCriptoM->AppendControl(this, 1003, TJ_EDT);
	BtCriptoTxt->AppendControl(this,IDOK,TJ_BTN);
	BtCancelar->AppendControl(this,IDCANCEL,TJ_BTN);

	TxtNormal->setLimitText(MAX_INFO);
	TxtMascara->setLimitText(MAX_INFO);

	BtCriptoTxt->OnClick = MakeDelegate(this, &FrmCriptoTxt::BtCriptoTxtClick);
	BtCancelar->OnClick = MakeDelegate(this, &FrmCriptoTxt::BtCancelarClick);
}
//---------------------------------------------------------------------------
void FrmCriptoTxt::FormOnClose(WindowBase *wB, bool *Cancel)
{
	PostQuitMessage(0);
}
//---------------------------------------------------------------------------
void FrmCriptoTxt::BtCancelarClick(WindowBase *wB)
{
	this->Close();
}
//---------------------------------------------------------------------------
void FrmCriptoTxt::BtCriptoTxtClick(WindowBase *wB)
{
	char *txt = NULL;
	txt = TxtNormal->getText();
	if (txt != NULL) {
		txt = EncryptText(txt);
		TxtCriptoN->setText(txt);
	}
	txt = TxtMascara->getText();
	if (txt != NULL) {
		txt = EncryptText(txt);
		TxtCriptoM->setText(txt);
	}
}
//---------------------------------------------------------------------------

