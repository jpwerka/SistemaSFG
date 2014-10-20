//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgCriptoLic.h"
#include "uSfgClientLicence.h"
#pragma hdrstop
#include "uSobre.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
Versao::Versao(char *File)
{
	this->m_pData = NULL;
	this->m_dwDataSize = NULL;
	this->m_File = NULL;
	this->m_strLangId = NULL;
	this->m_FixedInfo = NULL;
	if(File != NULL && strlen(File))
	{
		if(m_File) delete[] m_File;
		this->m_File = new char[strlen(File)+1];
		strcpy(this->m_File,File);
	}
}
//---------------------------------------------------------------------------
Versao::~Versao()
{
	if(m_File) delete[] m_File;
	if(m_strLangId) delete[] m_strLangId;
	if(m_pData) delete[] m_pData;
}
//---------------------------------------------------------------------------
bool Versao::Init()
{
	DWORD dwHandle;
	DWORD dwSize;
	BOOL rc;

	dwSize = ::GetFileVersionInfoSize((LPTSTR)m_File, &dwHandle);
	if (dwSize == 0)
		return false;
	m_pData = new BYTE[dwSize + 1];//(BYTE*) LocalAlloc(GMEM_ZEROINIT|GMEM_FIXED,dwSize + 1);
	ZeroMemory(m_pData, dwSize+1);
	m_dwDataSize = dwSize;
	rc = ::GetFileVersionInfo((LPTSTR)m_File, dwHandle, dwSize, m_pData);
	if (!rc)
		return false;
	return GetFixedInfo();
}
//---------------------------------------------------------------------------
bool Versao::GetFixedInfo()
{
	BOOL rc;
	UINT nLength;

	if (!m_pData)
		return false;

	rc = ::VerQueryValue(m_pData, "\\", (void**)&m_FixedInfo, &nLength);
	return (bool)rc;
}
//---------------------------------------------------------------------------
void Versao::setLangId(char *Value)
{
	if(Value != NULL && strlen(Value))
	{
		if(m_strLangId) delete[] m_strLangId;
		this->m_strLangId = new char[strlen(Value)+1];
		strcpy(this->m_strLangId,Value);
	}
}
//---------------------------------------------------------------------------
char* Versao::MontaValor(char* Inicio, int Tam)
{
	int i;
	char* monta = NULL;
	if(Tam)
	{
		monta = new char(Tam+1);
		for(i = 0; i <= Tam; i++)
			monta[i] = Inicio[i];
		monta[Tam] = '\0';
	}
	return monta;
}
//---------------------------------------------------------------------------
char* Versao::GetFileVersion()
{
	char *bf = new char[10];
	wsprintf(bf,"%u.%u.%u.%u",
		HIWORD(m_FixedInfo->dwFileVersionMS),
		LOWORD(m_FixedInfo->dwFileVersionMS),
		HIWORD(m_FixedInfo->dwFileVersionLS),
		LOWORD(m_FixedInfo->dwFileVersionLS));
	return bf;
}
//---------------------------------------------------------------------------
char* Versao::GetCompanyName()
{
	return GetStringInfo("CompanyName");
}
//---------------------------------------------------------------------------
char* Versao::GetFileDescription()
{
	return GetStringInfo("FileDescription");
}
//---------------------------------------------------------------------------
char* Versao::GetLegalCopyright()
{
	return GetStringInfo("LegalCopyright");
}
//---------------------------------------------------------------------------
char* Versao::GetProductName()
{
	return GetStringInfo("ProductName");
}
//---------------------------------------------------------------------------
char* Versao::GetLanguageName(DWORD LangId)
{
	char *ret = new char[100];
	VerLanguageName(LangId, ret, 100);
	return ret;
}
//---------------------------------------------------------------------------
char* Versao::GetStringInfo(LPCTSTR lpszKey)
{
	UINT nLength;
	LPTSTR lpszValue = NULL;
	char *ret = NULL;
	if (m_pData == NULL)
		return NULL;

	char* Key = new char[strlen(lpszKey) + 100];
	wsprintf(Key,"\\StringFileInfo\\%s\\%s", m_strLangId, lpszKey);

	BOOL rc = ::VerQueryValue(m_pData, Key, (void**) &lpszValue, &nLength);

	if (rc)
	{
		if (lpszValue)
			ret = lpszValue;//MontaValor(lpszValue, nLength);
	}
	if (Key)
		delete [] Key;

	return ret;
}
//---------------------------------------------------------------------------
static TCHAR * pszKeys[] = {"Comments",
					"CompanyName",
					"InternalName",
					"LegalTrademarks",
					"OriginalFilename",
					"ProductName",
					"ProductVersion",
					"Idioma",
					"FileVersion",
					NULL };
static int IdKeys[] = {8752,8753,8755,8756,8757,8759,8760,8763,8765};
static TCHAR * pszKeysPt[] = {"Comentários",
               "Empresa",
               "Nome interno",
               "Marcas registradas",
               "Nome original do arquivo",
               "Nome do produto",
               "Versão do produto",
               "Idioma",
               "Versão do arquivo",
               NULL };
#define MAX_KEYS 8
//---------------------------------------------------------------------------
__fastcall TfrmSobre::TfrmSobre(TComponent* Owner)
   : TForm(Owner)
{
	int i;
   float mem;
	char* bfName = (char*)malloc(sizeof(char)*MAX_PATH);
	ZeroMemory( bfName, MAX_PATH);
	GetModuleFileName(NULL,bfName,MAX_PATH);

	m_Versao = new Versao(bfName);
	m_Versao->setLangId("041604E4");
	if(m_Versao->Init())
	{
		char *versao = m_Versao->GetFileVersion();
		FileVersao->Text = versao;
      if(versao) delete[] versao;
		Descricao->Text = m_Versao->GetFileDescription();
		CopyRight->Text = m_Versao->GetLegalCopyright();
	}
	for(i = 0; i < MAX_KEYS; i++)
	{
		char* valor;
		if(strcmpi(pszKeys[i],"Idioma") == 0)
			valor = m_Versao->GetLanguageName(0x0416);
		else
			valor = m_Versao->GetStringInfo(pszKeys[i]);
		ListaInfo->AddItem(pszKeysPt[i], (TObject*)&valor[0]);
	}
	ListaInfo->ItemIndex = 0;
   ListaInfoClick(ListaInfo);
	free(bfName);

   Icone->Picture->Icon->Handle = LoadIcon(HInstance, "MAINICON");

	MEMORYSTATUS pMen;
	ZeroMemory(&pMen, sizeof(MEMORYSTATUS));
	pMen.dwLength = sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&pMen);
   mem = (pMen.dwTotalPhys/(1024*1024));
   if (mem > 1000)
	   Memory->Caption = FloatToStrF((mem/1024),ffNumber,15,2) + " GB";
   else
	   Memory->Caption = FloatToStrF(mem,ffNumber,15,0) + " MB";

   btLoadLicence->Enabled = false;
   //Informações sobre a licença de uso do sistema
   this->CodCliente->Text = AppLicence->CodCliente;
   this->DenCliente->Text = AppLicence->DenCliente;
   this->NumLicence->Text = IntToStr(AppLicence->NumLicence);
   this->UseServer->Checked = AppLicence->UseServer;
   if ((int)AppLicence->Validade != 0) {
      this->IdLicence->Text = AppLicence->IdLicence;
      this->Validade->Text = FormatDateTime("dd/mm/yyyy",AppLicence->Validade);
   } else {
      char MsgErro[255];
      char *FirstSerial = TSfgClientLicence::GetFirstSerial(MsgErro);
      this->IdLicence->Text = FirstSerial;
      this->Validade->Text = "";
      HeapFree(GetProcessHeap(),0,FirstSerial);
      btLoadLicence->Enabled = !AppLicence->UseServer;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::FormClose(TObject *Sender, TCloseAction &Action)
{
   delete m_Versao;
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::ListaInfoClick(TObject *Sender)
{
   char *valor = (char*)ListaInfo->Items->Objects[ListaInfo->ItemIndex];
   InfoKey->Text = valor;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::HiperLinkClick(TObject *Sender)
{
	ShellExecute(NULL, "open", HiperLink->Caption.c_str(), NULL, NULL, SW_MAXIMIZE);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::UseServerMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
   Abort();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::UseServerKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   Key = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSobre::btLoadLicenceClick(TObject *Sender)
{
   TfrmLoadLicence *pForm = new TfrmLoadLicence(Application);
   if (pForm->ShowModal() == mrOk) {
      //Informações sobre a licença de uso do sistema
      this->CodCliente->Text = AppLicence->CodCliente;
      this->DenCliente->Text = AppLicence->DenCliente;
      this->NumLicence->Text = IntToStr(AppLicence->NumLicence);
      this->UseServer->Checked = AppLicence->UseServer;
      this->IdLicence->Text = AppLicence->IdLicence;
      this->Validade->Text = FormatDateTime("dd/mm/yyyy",AppLicence->Validade);
      btLoadLicence->Enabled = false;
   }
   delete pForm;
}
//---------------------------------------------------------------------------
__fastcall TfrmLoadLicence::TfrmLoadLicence(TComponent* Owner)
   : TForm(Owner,0)
{
   this->BorderStyle = bsDialog;
   this->BorderIcons = TBorderIcons() << biSystemMenu;
   this->Caption = "Licença";
   this->Position = poDesktopCenter;
   this->ClientHeight = 302;
   this->ClientWidth = 512;
   TLabel *pLabel = new TLabel(this);
   pLabel->Parent = this;
   pLabel->Caption = "Cole o texto da licença nesta caixa e confirme para licenciar o sistema.";
   pLabel->SetBounds(6,8,400,16);
   InfoLicence = new TMemo(this);
   InfoLicence->Parent = this;
   InfoLicence->SetBounds(6,26,500,240);
   btOK = new TButton(this);
   btOK->Parent = this;
   btOK->Caption = "&OK";
   btOK->Default = true;
   btOK->OnClick = &btOKClick;
   btOK->SetBounds(348,274,75,22);
   btCancel = new TButton(this);
   btCancel->Parent = this;
   btCancel->Caption = "&Cancelar";
   btCancel->Cancel = true;
   btCancel->ModalResult = mrCancel;
   btCancel->SetBounds(430,274,75,22);
}
//---------------------------------------------------------------------------
void __fastcall TfrmLoadLicence::btOKClick(TObject *Sender)
{
   if (InfoLicence->Text.Length() != 1024) {
      MessageBox(Handle,"As informações da licença não são válidas de acordo com o formato esperado!",Caption.c_str(),APP_ATENTION);
      return;
   }
   InfoLicence->Lines->SaveToFile("SfgLicence.lic");
   if (!TSfgClientLicence::LicenceValidFile()) {
      return;
   }
   this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------


