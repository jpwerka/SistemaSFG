//---------------------------------------------------------------------------
#ifndef uSobreH
#define uSobreH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <jpeg.hpp>
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
class Versao
{
private:
	char* 	m_File;
	char* 	m_strLangId;
	BYTE* 	m_pData;
	DWORD 	m_dwDataSize;
	VS_FIXEDFILEINFO *m_FixedInfo; // pointer to fixed file info structure
private:
	bool 		GetFixedInfo();
	char* 	MontaValor(char* Inicio, int Tam);
public:
	void 		setLangId(char *Value);
public:
	Versao(char *File);
	~Versao();
	bool 		Init();
	char* 	GetFileVersion();
	char* 	GetCompanyName();
	char* 	GetFileDescription();
	char* 	GetLegalCopyright();
	char* 	GetProductName();
	char* 	GetLanguageName(DWORD LangId);
	char* 	GetStringInfo(LPCTSTR lpszKey);
};
//---------------------------------------------------------------------------
class TfrmSobre : public TForm
{
__published:	// IDE-managed Components
   TButton *btOK;
   TPageControl *PageControl1;
   TTabSheet *TabSheet1;
   TTabSheet *TabSheet2;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TEdit *FileVersao;
   TEdit *Descricao;
   TEdit *CopyRight;
   TGroupBox *GroupBox1;
   TLabel *Label4;
   TLabel *Label5;
   TListBox *ListaInfo;
   TMemo *InfoKey;
   TImage *Image1;
   TImage *Icone;
   TLabel *HiperLink;
   TLabel *Label7;
   TMemo *Memo1;
   TLabel *Label8;
   TBevel *Bevel1;
   TLabel *Memory;
   TTabSheet *TabSheet3;
   TLabel *Label6;
   TLabel *Label9;
   TAlignEdit *CodCliente;
   TAlignEdit *DenCliente;
   TAlignEdit *Validade;
   TLabel *Label10;
   TAlignEdit *NumLicence;
   TLabel *Label11;
   TAlignEdit *IdLicence;
   TCheckBox *UseServer;
   TButton *btLoadLicence;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall ListaInfoClick(TObject *Sender);
   void __fastcall HiperLinkClick(TObject *Sender);
   void __fastcall UseServerMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall UseServerKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall btLoadLicenceClick(TObject *Sender);
private:	// User declarations
   Versao 	*m_Versao;
public:		// User declarations
   __fastcall TfrmSobre(TComponent* Owner);
};
//---------------------------------------------------------------------------
class TfrmLoadLicence : public TForm
{
public:
   TButton *btOK;
   TButton *btCancel;
   TMemo *InfoLicence;
   void __fastcall btOKClick(TObject *Sender);
public:		// User declarations
   __fastcall TfrmLoadLicence(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
