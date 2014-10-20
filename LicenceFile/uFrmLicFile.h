//---------------------------------------------------------------------------
#ifndef uFrmLicFileH
#define uFrmLicFileH
//---------------------------------------------------------------------------
#include "FormControls.h"

#define MAX_INFO_CLIENTE 15
#define MAX_DEN_CLIENTE 50
#define MAX_INFO_SERIAL 16
#define MAX_NUM_LICENCE  1000
class TFrmLicFile: public GradientForm
{
private://Variables
	TextBox 	*TxtCliente;
	TextBox 	*TxtDenCli;
	TextBox 	*TxtSerial;
   SpinBox  *SpnNumLic;
   MaskTextBox *TxtValid;
	Button 	*BtGerar;
	Button 	*BtCancelar;
private://Methods
	void 		FormOnCreate(WindowBase *wB);
	void 		FormOnClose(WindowBase *wB, bool &Cancel);
	void 		BtGerarClick(WindowBase* wB);
	void 		BtCancelarClick(WindowBase* wB);
	void 		CreateControls();
	void 		Initialize();
public:
	TFrmLicFile();
	~TFrmLicFile();
};
extern TFrmLicFile *FrmLicFile;
#endif
