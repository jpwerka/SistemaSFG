//---------------------------------------------------------------------------
#ifndef uFrmCriptoTxtH
#define uFrmCriptoTxtH
//---------------------------------------------------------------------------
#include "FormControls.h"

#define MAX_INFO 30
class FrmCriptoTxt: public GradientForm
{
private://Variables
	TextBox 	*TxtNormal;
	TextBox 	*TxtCriptoN;
	TextBox 	*TxtMascara;
	TextBox 	*TxtCriptoM;
	Button 	*BtCriptoTxt;
	Button 	*BtCancelar;
private://Methods
	void 		FormOnCreate(WindowBase *wB);
	void 		FormOnClose(WindowBase *wB, bool *Cancel);
	void 		BtCriptoTxtClick(WindowBase* wB);
	void 		BtCancelarClick(WindowBase* wB);
	void 		CreateControls();
	void 		Initialize();
public:
	FrmCriptoTxt();
	~FrmCriptoTxt();
};
extern FrmCriptoTxt *frmCriptoTxt;
#endif
