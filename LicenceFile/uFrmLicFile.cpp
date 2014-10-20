//---------------------------------------------------------------------------
#include "uFrmLicFile.h"
#include "StdControls.h"
#include "ExtControls.h"
#include "uSfgCriptoLic.h"
//---------------------------------------------------------------------------
TFrmLicFile *FrmLicFile = NULL;
//---------------------------------------------------------------------------
TFrmLicFile::TFrmLicFile(): GradientForm()
{
	this->OnCreate = MakeDelegate(this, &TFrmLicFile::FormOnCreate);
	this->OnClose = MakeDelegate(this, &TFrmLicFile::FormOnClose);
	this->setIsGradient(true);
	this->setGrOrientation(GRADIENT_FILL_RECT_H);
	this->setFromColor(0x80ffff);
	this->setToColor(0x80ff80);
}
//---------------------------------------------------------------------------
TFrmLicFile::~TFrmLicFile(){}
//---------------------------------------------------------------------------
void TFrmLicFile::FormOnCreate(WindowBase *wB)
{
	TxtCliente = new TextBox();
   TxtDenCli = new TextBox();
	TxtSerial = new TextBox();
	SpnNumLic = new SpinBox();
   TxtValid = new MaskTextBox();
	BtGerar = new Button();
	BtCancelar = new Button();
	TxtCliente->AppendControl(this, 1000, TJ_EDT);
	TxtDenCli->AppendControl(this, 1004, TJ_EDT);
	TxtSerial->AppendControl(this, 1001, TJ_EDT);
	SpnNumLic->AppendControl(this, 1003, TJ_SPE);
   TxtValid->AppendControl(this, 1005, TJ_MTB);
	BtGerar->AppendControl(this,IDOK,TJ_BTN);
	BtCancelar->AppendControl(this,IDCANCEL,TJ_BTN);

	TxtCliente->setLimitText(MAX_INFO_CLIENTE);
	TxtDenCli->setLimitText(MAX_DEN_CLIENTE);
   TxtSerial->setLimitText(MAX_INFO_SERIAL);
   SpnNumLic->setMaxValue(MAX_NUM_LICENCE);
   SpnNumLic->setMinValue(0);
   SpnNumLic->setValue(5);
   TxtValid->setMaskType(ALPHANUMERIC);
   TxtValid->setMask("__/__/____");
   TxtValid->setMaskChar('_');

	BtGerar->OnClick = MakeDelegate(this, &TFrmLicFile::BtGerarClick);
	BtCancelar->OnClick = MakeDelegate(this, &TFrmLicFile::BtCancelarClick);

   char MsgError[255];
   char *FirstSerial = GetFirstSerialLic(MsgError);
   TxtSerial->setText(FirstSerial);
   HeapFree(GetProcessHeap(),0,FirstSerial);
}
//---------------------------------------------------------------------------
void TFrmLicFile::FormOnClose(WindowBase *wB, bool &Cancel)
{
	PostQuitMessage(0);
}
//---------------------------------------------------------------------------
void TFrmLicFile::BtCancelarClick(WindowBase *wB)
{
	this->Close();
}
//---------------------------------------------------------------------------
void TFrmLicFile::BtGerarClick(WindowBase *wB)
{
   char cErrorMsg[255];
   char *cCodCliente = NULL;
   char *cDenCliente = NULL;
   char *cSerialLic = NULL;
   char *cValidade = NULL;
   //SYSTEMTIME stValidade;
   //FILETIME ftValidade;
   //struct tm tmValidade;
   //time_t ltValidade;
   int iYear, iMonth, iDay;
   char cNum[5];

      //MessageBox(this->m_hWnd,TxtValid->getText(),this->getCaption(),Informa);
      //MessageBox(this->m_hWnd,TxtValid->getValue(),this->getCaption(),Informa);

	cCodCliente = TxtCliente->getText();
   if (cCodCliente == NULL) {
      MessageBox(this->m_hWnd,"Não foi informado o código do cliente para gerar a licença!",this->getCaption(),Informa);
      TxtCliente->SetFocus();
      return;
   }
   if (strlen(cCodCliente) != MAX_INFO_CLIENTE) {
      MessageBox(this->m_hWnd,"O código do cliente deve conter 15 posições para gerar a licença!",this->getCaption(),Informa);
      TxtCliente->SetFocus();
      return;
   }
   CodCliente = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(MAX_INFO_CLIENTE+1)*sizeof(char));
   strcpy(CodCliente,cCodCliente);
	cDenCliente = TxtDenCli->getText();
   if (strlen(cDenCliente) == 0) {
      MessageBox(this->m_hWnd,"Informe a descrição do cliente para gerar a licença!",this->getCaption(),Informa);
      TxtDenCli->SetFocus();
      return;
   }
   DenCliente = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(strlen(cDenCliente)+1)*sizeof(char));
   strcpy(DenCliente,cDenCliente);
	cSerialLic = TxtSerial->getText();
   if (cSerialLic == NULL) {
      MessageBox(this->m_hWnd,"Não foi informado o identificador do servidor para gerar a licença!",this->getCaption(),Informa);
      TxtSerial->SetFocus();
      return;
   }
   if (strlen(cSerialLic) != MAX_INFO_SERIAL) {
      MessageBox(this->m_hWnd,"O código do identificador do servidor deve conter 16 posições para gerar a licença!",this->getCaption(),Informa);
      TxtSerial->SetFocus();
      return;
   }
   SerialLic = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(MAX_INFO_SERIAL+1)*sizeof(char));
   strcpy(SerialLic,cSerialLic);

   NumberLic = SpnNumLic->getValue();

   cValidade = TxtValid->getValue();
   if (strlen(cValidade) != 8) {
      MessageBox(this->m_hWnd,"Informe a data de validade para gerar a licença no formato 'dd/mm/aaaa'!",this->getCaption(),Informa);
      TxtValid->SetFocus();
      return;
   }
   //Formtando o dia
   cNum[0] = cValidade[0]; cNum[1] = cValidade[1]; cNum[2] = '\0';
   iDay = atoi(cNum);
   //Formtando o mes
   cNum[0] = cValidade[2]; cNum[1] = cValidade[3]; cNum[2] = '\0';
   iMonth = atoi(cNum);
   //Formtando o ano
   cNum[0] = cValidade[4]; cNum[1] = cValidade[5]; cNum[2] = cValidade[6]; cNum[3] = cValidade[7]; cNum[4] = '\0';
   iYear = atoi(cNum);
   ValidadeLic = MAKELONG(MAKEWORD(iDay,iMonth),iYear);

   if (!SfgSaveLicenceFile(cErrorMsg)) {
      MessageBox(this->m_hWnd,cErrorMsg,this->getCaption(),Atencao);
   } else {
      MessageBox(this->m_hWnd,"Arquivo de licença gerado com sucesso!",this->getCaption(),Informa);
   }
   HeapFree(GetProcessHeap(),0,CodCliente);
   HeapFree(GetProcessHeap(),0,DenCliente);
   HeapFree(GetProcessHeap(),0,SerialLic);
}
//---------------------------------------------------------------------------

