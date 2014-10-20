//---------------------------------------------------------------------------
#ifndef uSfgGlobalsH
#define uSfgGlobalsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Graphics.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
#define APP_INFORM     MB_OK | MB_ICONINFORMATION
#define APP_ATENTION   MB_OK | MB_ICONEXCLAMATION
#define APP_ERROR      MB_OK | MB_ICONSTOP
#define APP_QUESTION   MB_YESNO | MB_ICONQUESTION
#define APP_CANCEL     MB_OKCANCEL | MB_ICONQUESTION

#define APP_PERM_TOTAL   2
#define APP_PERM_LEITURA 1

#define APP_MODULO_GERAL    0
#define APP_MODULO_ESTOQUE  1
#define APP_MODULO_COMPRAS  2
#define APP_MODULO_VENDAS   3
#define APP_MODULO_FINANCAS 4
#define APP_MODULO_FISCAL   5

//---------------------------------------------------------------------------
const int crMais = 1;
const int VK_MAIS = 0x06B;

const String MesesAno[13] = {"Indefinido","Janeiro","Fevereiro","Março","Abril","Maio","Junho",
                            "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

const String CPFMask = "!000.000.000-00;0;_";
const String CNPJMask  = "!00.000.000/0000-00;0;_";
static const UINT WM_SFGEXECPROGRAM = WM_USER + 2000;
static const UINT WM_SFGEXECPARAM   = WM_USER + 2001;

enum SMTP_CFG {
	CFG_NONE = 0,
	CFG_AUT = 1,
	CFG_SSL = 2
};
//---------------------------------------------------------------------------
typedef struct {
   TColor Enabled;
   TColor Disabled;
   TColor Backgrd;
   TColor GrLfTop;
   TColor GrLfBtt;
   TColor GrRgTop;
   TColor GrRgBtt;
   TColor TTFontColor;
   TColor TTBackColor;
   TColor TextColor;
} SfgColors;

typedef struct {
   String MarcaDaguaPath;
   Extctrls::TImage *MarcaDagua;
   String LogotipoPath;
   Extctrls::TImage *Logotipo;
} SfgImages;

typedef struct {
   String CabLivre01;
   String CabLivre02;
   String CabLivre03;
   String RodCidade;
   String RodLivre01;
   String RodLivre02;
} SfgReports;

typedef struct {
   SfgColors  *Colors;
   SfgImages  *Images;
   SfgReports *Reports;
   int        Icon;
} SfgConfig;

typedef struct {
   String  Host;
   int     Port;
   String  Database;
   String  User;
   String  Password;
   void   *Connection; //Pointer to object Connection.
} SfgDB;

typedef struct {
   bool      UseServer;  //Utiliza servidor de licenças externo
   String    IdLicence;  //Identificador da licença
   String    CodCliente; //Código do cliente para o qual a licença é válida
   String    DenCliente; //Denominação do cliente para o qual a licença é válida
   int       NumLicence; //Número de licenças liberadas para o cliente
   TDateTime Validade;   //Validade da licença em uso pelo SFG
} SfgLicence;

typedef struct {
   String  Address;
   int     Port;
   int     LastMsg;
   char   *MsgBuffer;
   void   *ClientSocket; //Pointer to object Socket.
   TNotifyEvent OnReceiveMessage;
} SfgLicenceSvr;

typedef struct {
   String Database;
   String Usuario;
   String Password;
   bool Splash;
} SfgArgs;

typedef struct {
   String FormClass;
   String FormTitle;
   int FormModule;
} SfgForm;

typedef struct {  //para guardar os parâmetros de conexão
   String SMTPHost, SMTPUsername, SMTPPassword;
   String SMTPConta, SMTPNomeExibicao, SMTPDestinatarios;
   bool SMTPAutenticacao, SMTPSSL;
   int SMTPPorta;
} SfgParEmail;

typedef struct {  //para guardar os parâmetros de conexão
   String Usuario;
   bool IsAdm;
   String CodEmpresa;
   int MaxProgram;
} SfgUser;

typedef struct {
   String ProgramName; //Indicador de qual rotina deve ser chamada
   int ProgramModulo;  //Indicador de qual módulo a rotina pertence
   int NivelPermissao; //Nìvel de permissão para a execussão da rotina - Normalmente herda da rotina que chamou
   WORD ProgramRotina; //Indicador numérico de qual rotina deve ser chamada - Rotina destino deve tratar esta informação
   WORD CallBeforeShow; //Indicador se a rotina deve ser chamada, antes ou depois do Form->Show. 0 - false  1 - true
   LPARAM ProgramParams; //Ponteiro para os parâmetros que devem ser passados - Rotina destino deve tratar esta informação
} SfgExecProgram;

typedef TList SfgForms;
typedef TStringList SfgFormsClass;
typedef TForm* (*SfgCreatePreview)();
typedef void __fastcall (__closure *SfgDummyMethod)(void *pVoid);
//---------------------------------------------------------------------------
extern PACKAGE SfgArgs *AppArgs;
extern PACKAGE SfgConfig *AppConfig;
extern PACKAGE SfgUser *AppUser;
extern PACKAGE SfgParEmail *AppParEmail;
extern PACKAGE SfgDB *AppDB;
extern PACKAGE SfgLicence *AppLicence;
extern PACKAGE SfgLicenceSvr *AppLicenceSvr;
extern PACKAGE TMetaClass *FormBaseClass;
extern PACKAGE TMetaClass *PreviewReportClass;
extern PACKAGE SfgCreatePreview AppCreatePreview;
extern PACKAGE SfgDummyMethod AppDummyMethod;
extern PACKAGE SfgForms *AppForms;
extern PACKAGE SfgFormsClass *AppFormsClass;
#endif
