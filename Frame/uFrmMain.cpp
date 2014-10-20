//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include <DBCtrls.hpp>
#include <Grids.hpp>
#include <DBConsts.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgDinForms.hpp"
#include "uDataModule.h"
#include "uDataBase.h"
//#include "uAtualizaDB.h"
#include "uFrmLogin.h"
#include "uSobre.h"
#include "uFrm1001.h"
#include "uFrm1012.h"
#include "uSfgClientLicence.h"
#pragma hdrstop
#include "uFrmMain.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmMain *FrmMain;
//---------------------------------------------------------------------------
struct SfgMenuExec {
	String cod_rotina;
	String programa;
   int nivel_permissao;
   int modulo;
   TMenuItem *next;
};
//---------------------------------------------------------------------------
TList *HackForms = NULL;
TList *HackFormsOnClose = NULL;
struct SfgHackOnClose {
   TCloseEvent OnClose;
};
//---------------------------------------------------------------------------
typedef void(__stdcall *PSfgModuloInit)(LPARAM lParam);
typedef void(__stdcall *PSfgModuloFinish)();
typedef struct {
   HINSTANCE hSfgModulo;
   PSfgModuloInit SfgModuloInit;
   PSfgModuloFinish SfgModuloFinish;
} SfgModulo;
TStringList *AppModulos = NULL;
//---------------------------------------------------------------------------
void LoadSfgModulo(String sName) {
   SfgModulo *AppModulo;
   String sAux;

   sAux = "Sfg" + sName + ".dll";
   HINSTANCE hSfgModulo = LoadLibrary(sAux.c_str());
   if(hSfgModulo) {
      //Se ainda não criou a lista de móludos deve criar agora
      if (AppModulos == NULL)
         AppModulos = new TStringList();
      //Cria o objeto que vai conter os ponteiros do módulo
      AppModulo = new SfgModulo();
      AppModulo->hSfgModulo = hSfgModulo;
      AppModulos->AddObject(sName, (TObject*)AppModulo);
      sAux = "Sfg" + sName + "Init";
      AppModulo->SfgModuloInit = (PSfgModuloInit)GetProcAddress(hSfgModulo,sAux.c_str());
      sAux = "Sfg" + sName + "Finish";
      AppModulo->SfgModuloFinish = (PSfgModuloFinish)GetProcAddress(hSfgModulo,sAux.c_str());
      if(AppModulo->SfgModuloInit != NULL) {
         AppModulo->SfgModuloInit((LPARAM)0);
      }
   }
}
//---------------------------------------------------------------------------
TForm* SfgAppCreatePreview() {
   TForm *pForm = NULL;
   SfgCreateForm(Application, PreviewReportClass, &pForm);
   return pForm;
}
//---------------------------------------------------------------------------
void FreeAppForms(void) {
   SfgForm *pAppForm;
   for (int i=0; i<AppForms->Count; i++) {
      pAppForm = (SfgForm*)AppForms->Items[i];
      delete pAppForm;
   }
   delete AppForms;
}
#pragma exit FreeAppForms 64
//---------------------------------------------------------------------------
__fastcall TFrmMain::TFrmMain(TComponent* Owner)
	: TForm(Owner)
{
   FrmLogin = NULL;
   bCreateAtuDB = false;
   ThemeManagerDB = new TThemeManagerDB(this);
   SetClassLong((HWND)CreateWindow("BUTTON","Mão",WS_CHILD,8,150,50,25,Handle,(HMENU)5000,HInstance,NULL),GCL_HCURSOR,(LONG)LoadCursor(NULL,IDC_HAND));
   Screen->Cursors[crHandPoint] = LoadCursor(NULL,IDC_HAND);
   //Antes de fazer qualquer outro comando deve validar as licenças
   //Porém somente deve validar se caso utilizar o servidor de licenças
   //Se cheou até aqui e não tem licença é porque está parametrizado para utilizar local
   if (!AppLicence->UseServer && !SfgDataCenter->IsLicenceOK) {
      String sMsg = "O sistema está parametrizado para utilizar arquivo de licença local.\n" \
                    "Porém não foi possível validar a licença local de uso do sistema.\n" \
                    "Altere as configurações do sistema para utilizar um servidor de licenças\n" \
                    "ou então solicite um arquivo de licenças para o suporte SoftGreen.\n" \
                    "As informações necessárias para geração da licença devem ser\n" \
                    "consultadas na tela de 'Sobre' do sistema na aba 'Licença de Uso'.";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);
      FrmMain->CriarMenu();
      return;
   }
   //Deve validar se conseguiu se conectar ao banco de dados
   if (!AppConnection->Connected) {
      MessageBox(Handle,"Não foi possível conectar ao banco de dados!",Caption.c_str(),APP_ERROR);
      Application->Terminate();
      //this->Close();
      return;
   }
   //Se não existe o banco de dados e criou o mesmo deve abrir o formulário
   //para efetuar a importação do xml que cria a estrutura do banco de dados
   if (!ValidSchemaDB()) {
      String sMsg = "A base de dados não está consistente, por isso será aberta a tela para importação do esquema da base dados\n" \
                    "para o sistema SFG. Será necessário solicitar os arquivos 'xml' para efetuar esta importação de dados.\n\n" \
                    "É recomendável entrar em contato com o suporte SoftGreen para efetuar este procedimento.\n";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);
      bCreateAtuDB = true;
      FrmMain->CriarMenu();
   }

   this->WindowProc = &SubClassWndProc;
   Application->OnMessage = &AppEventsMessage;
   AppUser = new SfgUser();
   AppUser->CodEmpresa = "";
	AppConfig = new SfgConfig();
	AppConfig->Colors = new SfgColors();
	AppConfig->Images = new SfgImages();
	AppConfig->Reports = new SfgReports();
   AppConfig->Images->MarcaDaguaPath = "";
	AppConfig->Images->MarcaDagua = new TImage(this);
   AppConfig->Images->LogotipoPath = "";
	AppConfig->Images->Logotipo = new TImage(this);
	AppParEmail = new SfgParEmail();
//  Cor do fundo do formulário
   AppConfig->Colors->Backgrd = clBtnFace;
//  Cor da fonte do formulário
   AppConfig->Colors->TextColor = clWindowText;
//  Cor do campo habilitado
   AppConfig->Colors->Enabled = clWindow;
//  Cor do campo desabilitado
   AppConfig->Colors->Disabled = clBtnFace;
//  Cor do canto sup esq (gradiente)
   AppConfig->Colors->GrLfTop = clGreen;
//  Cor do canto inf esq (gradiente)
   AppConfig->Colors->GrLfBtt = clYellow;
//  Cor do canto sup dir (gradiente)
   AppConfig->Colors->GrRgTop = clBlue;
//  Cor do canto inf dir (gradiente)
   AppConfig->Colors->GrRgBtt = clRed;
//  Cor da fonte das dicas
   AppConfig->Colors->TTFontColor = clInfoText;
//  Cor do fundo das dicas
   AppConfig->Colors->TTBackColor = clInfoBk;
   AppConfig->Icon = 1; //TTIconInfo;

  //AppUser->Usuario = "administrador";
   if (bCreateAtuDB)
      return;

   FrmLogin = new TFrmLogin(Application);
   FrmLogin->Parent = this;
   FrmLogin->Color = this->Color;
   FrmLogin->Show();

   CarregarImages();
	CarregarReports();
	CarregarServerSMTP();

   HackForms = new TList();
   HackFormsOnClose = new TList();
   AppCreatePreview = &SfgAppCreatePreview;
   //OpenFileLog(OPEN_ALWAYS);
}
//---------------------------------------------------------------------------
__fastcall TFrmMain::~TFrmMain()
{
   SfgModulo *AppModulo;

   if (AppConfig != NULL) {
	   delete AppConfig->Images->MarcaDagua;
	   delete AppConfig->Images->Logotipo;
	   delete AppConfig->Images;
	   delete AppConfig->Reports;
	   delete AppConfig->Colors;
	   delete AppConfig;
   }
	if (AppParEmail != NULL) delete AppParEmail;
	if (AppUser != NULL) delete AppUser;
   if (AppModulos != NULL) {
      for (int i=0; i<AppModulos->Count; i++) {
         AppModulo = (SfgModulo*)AppModulos->Objects[i];
         if (AppModulo->hSfgModulo != NULL) {
            if (AppModulo->SfgModuloFinish != NULL)
               AppModulo->SfgModuloFinish();
            FreeLibrary(AppModulo->hSfgModulo);
         }
         delete AppModulo;
      }
      delete AppModulos;
   }
   if (ThemeManagerDB != NULL) delete ThemeManagerDB;
   if (AppClientLicence != NULL) delete AppClientLicence;
   if (HackForms != NULL) delete HackForms;
   if (HackFormsOnClose != NULL) delete HackFormsOnClose;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FormClose(TObject *Sender, TCloseAction &Action)
{
   if (FrmLogin)
      delete FrmLogin;
	if(!TerminarForms()) {
	 Action = caNone;
	 return;
	}
   if (AppClientLicence != NULL)
      AppClientLicence->LicenceDelClient();
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FormResize(TObject *Sender)
{
	if(FrmLogin != NULL) {
		FrmLogin->Top  = ((this->ClientHeight - FrmLogin->Height)/2);
		FrmLogin->Left = ((this->ClientWidth  - FrmLogin->Width)/2);
	}
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FormShow(TObject *Sender)
{
   if (!AppConnection->Connected)
      return;
#ifndef _DEBUG
	this->WindowState = wsMaximized;
#endif
	if(FrmLogin != NULL) {
   	if(AppArgs->Usuario.Length())
   		FrmLogin->Login->Text = AppArgs->Usuario;
   	if(AppArgs->Password.Length())
   		FrmLogin->Senha->Text = AppArgs->Password;
   	if(AppArgs->Usuario.Length() && AppArgs->Password.Length()) {
   		FrmLogin->btOKClick(FrmLogin->btOK);
   	} else {
   		FrmLogin->Login->SetFocus();
   	}
   }
   if (bCreateAtuDB) {
      TFrm1012 *pFrm1012 = new TFrm1012(Application);
      pFrm1012->Show();
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::LoadSfgModulos()
{
   LoadSfgModulo("Estoque");
   LoadSfgModulo("Compras");
   LoadSfgModulo("Vendas");
   LoadSfgModulo("Financas");
   LoadSfgModulo("Fiscal");
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::CarregarImages()
{
   if (!ExistProcedure("get_parametro_texto"))
      return;

	AppConfig->Images->LogotipoPath = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('logotipo_path');"));
	AppConfig->Images->MarcaDaguaPath = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('marcadagua_path');"));
	if(AppConfig->Images->MarcaDaguaPath.Length() > 0) {
	try {
		AppConfig->Images->MarcaDagua->Transparent = true;
		AppConfig->Images->MarcaDagua->Picture->LoadFromFile(AppConfig->Images->MarcaDaguaPath);
		}
		catch (...) {
			MessageBox(Handle,"Não foi possível carregar a imagem de fundo!","Mensagem de Erro",APP_ERROR);
		}
	} else {
	try {
		AppConfig->Images->MarcaDagua->Transparent = true;
		AppConfig->Images->MarcaDagua->Picture->Bitmap = new Graphics::TBitmap();
      AppConfig->Images->MarcaDagua->Picture->Bitmap->LoadFromResourceName((UINT)HInstance,"MARCADAGUA");
		}
		__finally {}
   }
	if(AppConfig->Images->LogotipoPath.Length() > 0) {
	try {
		AppConfig->Images->Logotipo->Picture->LoadFromFile(AppConfig->Images->LogotipoPath);
		}
		catch (...) {
			MessageBox(Handle,"Não foi possível carregar a imagem de logotipo!","Mensagem de Erro",APP_ERROR);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::CarregarReports()
{
   if (!ExistProcedure("get_parametro_texto"))
      return;

	AppConfig->Reports->CabLivre01 = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_cab_livre01');"));
	AppConfig->Reports->CabLivre02 = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_cab_livre02');"));
	AppConfig->Reports->CabLivre03 = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_cab_livre03');"));
	AppConfig->Reports->RodCidade = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_rod_cidade')"));
	AppConfig->Reports->RodLivre01 = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_rod_livre01');"));
	AppConfig->Reports->RodLivre02 = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('report_rod_livre02');"));
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::CarregarServerSMTP()
{
	TZReadOnlyQuery *QyServerSMTP;
	SMTP_CFG smtp_cfg = CFG_NONE;
try {
	QyServerSMTP = new TZReadOnlyQuery(Application);
	QyServerSMTP->Connection = AppConnection;
	QyServerSMTP->SQL->Text = "SELECT valor_texto, valor_decimal, valor_flag FROM tbl_parametro_sistema WHERE nome_parametro = 'server_smtp';";
	QyServerSMTP->Active = true;
	if(QyServerSMTP->RecordCount) {
		AppParEmail->SMTPHost = QyServerSMTP->FieldByName("valor_texto")->AsString;
		AppParEmail->SMTPPorta = QyServerSMTP->FieldByName("valor_decimal")->AsInteger;
		smtp_cfg = StrToInt(QyServerSMTP->FieldByName("valor_flag")->AsString);
		AppParEmail->SMTPAutenticacao = (smtp_cfg & CFG_AUT); // requer autenticacao
		AppParEmail->SMTPSSL = (smtp_cfg & CFG_SSL); // requer conexao segura
	} else {
		AppParEmail->SMTPHost = "";
		AppParEmail->SMTPPorta = 0;
		AppParEmail->SMTPAutenticacao = false; // requer autenticacao
		AppParEmail->SMTPSSL = false; // requer conexao segura
	}
	QyServerSMTP->Active = false;
	delete QyServerSMTP;
} catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao buscar as informações de parametrização do servidor de email:\n";
   Msg = Msg + e.Message;
   MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::FormPaint(TObject *Sender)
{
	TGraphic *Graphic;
	int X,Y;
  if (AppConfig->Images->MarcaDagua == NULL)
    return;
  if (AppConfig->Images->MarcaDagua->Picture == NULL)
    return;
  if (AppConfig->Images->MarcaDagua->Picture->Graphic == NULL)
    return;
	Graphic = AppConfig->Images->MarcaDagua->Picture->Graphic;
	if(Graphic){
		Canvas->FillRect(this->GetClientRect());
		X = (ClientWidth - Graphic->Width) /2;
		Y = (ClientHeight - Graphic->Height)/2;
		Canvas->Draw(X,Y,Graphic);
	}
}
//---------------------------------------------------------------------------
bool __fastcall TFrmMain::FormIsLoadActive(String sFormName)
{
  bool Achou = false;
	for(int i = 0;i<Screen->FormCount;i++) {
	  if(Screen->Forms[i]->Name == sFormName) {
		 Achou = true;
		 ActiveForm(Screen->Forms[i]);
	  }
	}
	return Achou;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::ActiveForm(TForm* pForm)
{
    if(IsIconic(pForm->Handle))
      ShowWindow(pForm->Handle,SW_SHOWNORMAL);
    else
    if(Screen->ActiveForm == pForm)
		 MessageBeep(0);
    else
       BringWindowToTop(pForm->Handle);
}
//---------------------------------------------------------------------------
bool __fastcall TFrmMain::TerminarForms() {
  if(Screen->FormCount > 1){
	 if(MessageBox(Handle,"Há formularios abertos, é necessário fechá-los.\nDeseja fechá-los?",
						Caption.c_str(),APP_QUESTION) == IDYES) {
		for(int i = Screen->FormCount -1; i >= 0;i--) {
         //ShowMessage(Screen->Forms[i]->ClassName());
			if(Screen->Forms[i]->Name != this->Name)
			  Screen->Forms[i]->Close();
      }
		return true;
	 }
	 else
		return false;
  }
  return true;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::CriarMenu()
{
   TMenuItem *MenuItem = NULL;
   TMainMenu *pMenu = new TMainMenu(this);
   bool bMenu = false;
   String SQL;
   pMenu->Images = ImageMenu;
   this->Menu = pMenu;

   //Somente vai criar o menu se o sistema está licenciado
   //Ou se não é a opção de criar o banco de dados
   if (SfgDataCenter->IsLicenceOK && !bCreateAtuDB) {
      //Se o usuário é administrador vai carregar sempre o menu completo      
      if (AppUser->IsAdm) {
         SQL = "SELECT cod_rotina_pai, ord_rotina, cod_rotina, den_rotina,"
                     " programa, ico_index, 'administrador' usuario_grupo,"
                     " 'U' tip_permissao, 2 nivel_permissao, modulo"
                 " FROM tbl_menu_sistema ORDER BY cod_rotina_pai, ord_rotina";
      } else {
         SQL = "CALL carrega_permissao_menu(" + QuotedStr(AppUser->Usuario) + ", 'U')";
      }
      
      CnsMenu->SQL->Clear();
      CnsMenu->SQL->Text = SQL;
      CnsMenu->Active = true;
      
      CarregaMenu(pMenu,NULL,bMenu);
      
      CnsMenu->Active = false;
      
      //Se for o administrador e não carregar nenhum menu
      //Cria o menu do programa de cadastro do menu para o mesmo.
      if (AppUser->IsAdm && !bMenu) {
         SfgMenuExec *MenuExec = new SfgMenuExec();
         MenuExec->cod_rotina = "cad_menu";
         MenuExec->programa = "Frm1010";
         MenuExec->next = NULL;
         MenuItem = new TMenuItem(pMenu);
         MenuItem->Name = "cad_menu";
         MenuItem->Caption = "Menu";
         MenuItem->ImageIndex = 5;
         MenuItem->Tag = (long)MenuExec;
         MenuItem->OnClick = &execMenuExecute;
         pMenu->Items->Add(MenuItem);
      }

      //Cria o menu de janelas
      MenuItem = new TMenuItem(pMenu);
      MenuItem->Name = "janelas1";
      MenuItem->Caption = "Janelas";
      pMenu->Items->Add(MenuItem);
      this->WindowMenu = MenuItem;
      MenuItem = new TMenuItem(this->WindowMenu);
      MenuItem->Caption = "&Cascata";
      MenuItem->Action = wndCascata;
      MenuItem->ImageIndex = 6;
      this->WindowMenu->Add(MenuItem);
      MenuItem = new TMenuItem(this->WindowMenu);
      MenuItem->Caption = "Dispor &Horizontal";
      MenuItem->Action = wndTileHorz;
      MenuItem->ImageIndex = 7;
      this->WindowMenu->Add(MenuItem);
      MenuItem = new TMenuItem(this->WindowMenu);
      MenuItem->Caption = "Dispor &Vertical";
      MenuItem->Action = wndTileVert;
      MenuItem->ImageIndex = 8;
      this->WindowMenu->Add(MenuItem);
      MenuItem = new TMenuItem(this->WindowMenu);
      MenuItem->Caption = "&Minimizar todas";
      MenuItem->Action = wndMinimize;
      this->WindowMenu->Add(MenuItem);
      MenuItem = new TMenuItem(this->WindowMenu);
      MenuItem->Caption = "&Fechar";
      MenuItem->Action = wndClose;
      this->WindowMenu->Add(MenuItem);
   }

   MenuItem = new TMenuItem(pMenu);
   MenuItem->Name = "ajuda1";
   MenuItem->Caption = "Sobre";
   pMenu->Items->Add(MenuItem);
   MenuItem->OnClick = &execMenuSobre;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::CarregaMenu(TMenu *pMenu, TMenuItem *pParentItem, bool &bMenu)
{
   TMenuItem *MenuItem = NULL;
   TMenuItem *MenuFirst = NULL;
   SfgMenuExec *MenuExec = NULL;
	CnsMenu->Filtered = false;
	if (pParentItem == NULL) {
		CnsMenu->Filter = "cod_rotina_pai IS NULL AND nivel_permissao > 0";
	} else {
		MenuExec = (SfgMenuExec*)pParentItem->Tag;
		CnsMenu->Filter =  "cod_rotina_pai  = " + QuotedStr(MenuExec->cod_rotina) + \
                         " AND nivel_permissao > 0";
	}
	CnsMenu->Filtered = true;
	CnsMenu->First();
   MenuExec = NULL;
	while (!CnsMenu->Eof) {
      MenuItem = new TMenuItem(pMenu);
      //Faz com que o ultimo menu criado aponte para o atual
      if (MenuExec != NULL) {
         MenuExec->next = MenuItem;
      }
      MenuExec = new SfgMenuExec();
		MenuExec->cod_rotina = CnsMenu->FieldByName("cod_rotina")->AsString;
		MenuExec->nivel_permissao = CnsMenu->FieldByName("nivel_permissao")->AsInteger;
      MenuExec->modulo = CnsMenu->FieldByName("modulo")->AsInteger;
      if (CnsMenu->FieldByName("programa")->AsString.Length() > 0) {
		   MenuExec->programa = CnsMenu->FieldByName("programa")->AsString;
      } else {
         MenuExec->programa = "";
      }
      MenuExec->next = NULL;
      MenuItem->Name = MenuExec->cod_rotina;
      MenuItem->Caption = CnsMenu->FieldByName("den_rotina")->AsString;
      MenuItem->ImageIndex = CnsMenu->FieldByName("ico_index")->AsInteger;
      MenuItem->Tag = (long)MenuExec;
      if (MenuExec->programa.Length() > 0)
         MenuItem->OnClick = &execMenuExecute;
      if (pParentItem == NULL) {
         pMenu->Items->Add(MenuItem);
      } else {
         pParentItem->Add(MenuItem);
		}
		if (MenuFirst == NULL) {
			MenuFirst = MenuItem;
		}
      if (MenuExec->cod_rotina == "Frm1010") {
         bMenu = true;
      }
		CnsMenu->Next();
	}
	while(MenuFirst != NULL) {
		CarregaMenu(pMenu,MenuFirst,bMenu);
      MenuExec = (SfgMenuExec*)MenuFirst->Tag;
		MenuFirst = MenuExec->next;
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::execMenuSobre(TObject *Sender)
{
   TfrmSobre *Sobre = new TfrmSobre(Application);
   Sobre->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::SubClassWndProc(Messages::TMessage &Message)
{
   if(Message.Msg == WM_SFGEXECPROGRAM)
   {
      Message.Result = CreateFormEx(Message.LParam);
   } else {
      this->WndProc(Message);
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::AppEventsMessage(tagMSG &Msg, bool &Handled)
{
	if (Screen->ActiveControl == NULL)
     return;

   if (Screen->ActiveControl->InheritsFrom(__classid(TButton)) ||
      Screen->ActiveControl->InheritsFrom(__classid(TCustomMemo)))
      return;
      
   if (Screen->ActiveControl->InheritsFrom(__classid(TCustomGrid)) && Msg.message == WM_MOUSEWHEEL)
   {
     Msg.message = WM_KEYDOWN;
     Msg.lParam = 0;
     Msg.wParam = ((signed long)Msg.wParam > 0 ? VK_UP : VK_DOWN);
     Handled = false;
   }

   if(Msg.message == WM_KEYDOWN && Msg.wParam == VK_RETURN)
   {
      keybd_event(VK_TAB, 0, 0, 0);
      Handled = true;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::execMenuExecute(TObject *Sender)
{
   TMenuItem *MenuItem = (TMenuItem*)Sender;
   SfgMenuExec *MenuExec = (SfgMenuExec*)MenuItem->Tag;

	if(!FormIsLoadActive(MenuExec->programa)) {
      CreateForm(MenuExec,MenuItem->Caption);
	}
}
//---------------------------------------------------------------------------
TForm* __fastcall TFrmMain::CreateForm(SfgMenuExec *MenuExec, String sTitle)
{
   String FormClass = "T" + MenuExec->programa;
   TMetaClass *MetaClass = GetAppFormClass(FormClass);
   TForm *pForm = NULL;

   if ((MetaClass != NULL) && MetaClass->InheritsFrom(__classid(TForm))) {
      SfgCreateForm(Application, MetaClass, &pForm);
      if (pForm != NULL) {
         if (pForm->InheritsFrom(FormBaseClass)) {
            if (AppDummyMethod != NULL) {
               AppDummyMethod((void*)&MenuExec->nivel_permissao);
               AppDummyMethod = NULL;
            }
            pForm->Show();
         }
      }
   } else {
      String sModulo;
      switch (MenuExec->modulo) {
         case APP_MODULO_ESTOQUE:
            sModulo = "Estoque";
            break;
         case APP_MODULO_COMPRAS:
            sModulo = "Compras";
            break;
         case APP_MODULO_VENDAS:
            sModulo = "Vendas";
            break;
         case APP_MODULO_FINANCAS:
            sModulo = "Finanças";
            break;
         case APP_MODULO_FISCAL:
            sModulo = "Fiscal";
            break;
         default:
            sModulo = "Geral";
      }
      String Msg = "Não foi encontrado o programa cadastrado no menu:\n" \
                   "Programa: " + MenuExec->programa + " Módulo: " + sModulo +"\n" \
                    "Verifique se módulo solicitado está instalado.\n" \
                    "Verifique se o cadastro do menu está correto.";
      MessageBox(Handle,Msg.c_str(),"Programa Inexistente",APP_ATENTION);
   }
   //Se criou o formulário adiciona o mesmo ao servidor de licenças
   if (pForm != NULL && AppLicence->UseServer) {
      if (!AppClientLicence->LicenceAddProgram(pForm->Name.c_str(),pForm->Caption.c_str())) {
         pForm->Close();
         delete pForm;
         pForm = NULL;
      } else {
         if (pForm->OnClose != NULL) {
            HackForms->Add(pForm);
            SfgHackOnClose *pHackOnClose = new SfgHackOnClose();
            pHackOnClose->OnClose = pForm->OnClose;
            HackFormsOnClose->Add(pHackOnClose);
            pForm->OnClose = &HackFormClose;
         }
      }
   }
   return pForm;
}
//---------------------------------------------------------------------------
long __fastcall TFrmMain::CreateFormEx(LPARAM lParam)
{
   SfgExecProgram *pSfgExecProgram = (SfgExecProgram*)lParam;
   String FormClass = "T" + pSfgExecProgram->ProgramName;
   TMetaClass *MetaClass = GetAppFormClass(FormClass);
   TForm *pForm = NULL;

   WORD wBeforeShow = pSfgExecProgram->CallBeforeShow; //Indicador se deve postar a mensagem antes do método show
   WORD wCallRotina = pSfgExecProgram->ProgramRotina; //Indicador de qual a rotina deve ser chamada pelo form que receber a mensagem

   if ((MetaClass != NULL) && MetaClass->InheritsFrom(__classid(TForm))) {
      SfgCreateForm(Application, MetaClass, &pForm);
      if (pForm != NULL) {
         if (pForm->InheritsFrom(FormBaseClass)) {
            //Chamado o método desconhecido - Neste caso o SetPermissao, passando um ponteiro para a permissão
            if (AppDummyMethod != NULL) {
               AppDummyMethod((void*)&pSfgExecProgram->NivelPermissao);
               AppDummyMethod = NULL; //Anula o método para não ser chamado indevidamente
            }
            if (wBeforeShow > 0)
               pForm->Perform(WM_SFGEXECPARAM,MAKEWPARAM(wCallRotina,0),pSfgExecProgram->ProgramParams);
            pForm->Show();
            if (wBeforeShow == 0)
               pForm->Perform(WM_SFGEXECPARAM,MAKEWPARAM(wCallRotina,0),pSfgExecProgram->ProgramParams);
         } else { //Se não for o form base, então não tem o Show, mas mesmo assim deve executar o método
            pForm->Perform(WM_SFGEXECPARAM,MAKEWPARAM(wCallRotina,0),pSfgExecProgram->ProgramParams);
         }
      }
   } else {
      String sModulo;
      switch (pSfgExecProgram->ProgramModulo) {
         case APP_MODULO_ESTOQUE:
            sModulo = "Estoque";
            break;
         case APP_MODULO_COMPRAS:
            sModulo = "Compras";
            break;
         case APP_MODULO_VENDAS:
            sModulo = "Vendas";
            break;
         case APP_MODULO_FINANCAS:
            sModulo = "Finanças";
            break;
         case APP_MODULO_FISCAL:
            sModulo = "Fiscal";
            break;
         default:
            sModulo = "Geral";
      }
      String Msg = "Não foi encontrado o programa solicitado pela aplicação:\n" \
                   "Programa: " + pSfgExecProgram->ProgramName + " Módulo: " + sModulo + "\n" \
                   "Verifique se módulo solicitado está instalado ou\n" \
                   "entre em contato com o suporte para verificar este problema.";
      MessageBox(NULL,Msg.c_str(),"Programa Inexistente",APP_ATENTION);
   }
   //Se criou o formulário adiciona o mesmo ao servidor de licenças
   if (pForm != NULL && AppLicence->UseServer) {
      if (!AppClientLicence->LicenceAddProgram(pForm->Name.c_str(),pForm->Caption.c_str())) {
         pForm->Close();
         delete pForm;
         pForm = NULL;
      } else {
         if (pForm->OnClose != NULL) {
            HackForms->Add(pForm);
            SfgHackOnClose *pHackOnClose = new SfgHackOnClose();
            pHackOnClose->OnClose = pForm->OnClose;
            HackFormsOnClose->Add(pHackOnClose);
            pForm->OnClose = &HackFormClose;
         }
      }
   }
   return (long)pForm;
}
//---------------------------------------------------------------------------
void __fastcall TFrmMain::HackFormClose(TObject *Sender, TCloseAction &Action)
{
   int iIndex = HackForms->IndexOf(Sender);
   if (iIndex >= 0) {
      SfgHackOnClose *pHackOnClose = (SfgHackOnClose*)HackFormsOnClose->Items[iIndex];
      pHackOnClose->OnClose(Sender, Action);
      if (Action == caFree) {
         HackFormsOnClose->Delete(iIndex);
         HackForms->Delete(iIndex);
         delete pHackOnClose;
      }
   } else {
      Action = caFree;
   }

   AppClientLicence->LicenceDelProgram(((TForm*)Sender)->Name.c_str());
}
//---------------------------------------------------------------------------
bool __fastcall TFrmMain::ValidSchemaDB()
{
   String sMsg;
   String sSQL;

   if (!SfgDataCenter->ExistDataBase) {
      sMsg = "Será necessário criar a base dados completa para o sistema SFG.\n" \
             "São necessários os arquivos: criaDB0001.xml e criaDB0002.xml";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);
      return false;
   }

   if (!ExistTable("tbl_execucao_atualizacao")) {
      sMsg = "Nunca foi executada a rotina de atualização da base dados do SFG." \
             "Será necessário rodar esta rotina para atualização do banco de dados do sistema SFG.\n" \
             "São necessários os arquivos: criaDB0001.xml, criaDB0002.xml e atualizaDB0001.xml";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);
      return false;
   }
   //Verificar se os arquivos de atualização já foram processados
   bool bCriaDB0001, bCriaDB0002, bAtuDB0001;
   //Arquivo de criação de todas as tabelas do sistema SFG
   sSQL = "SELECT file_atualizacao FROM tbl_execucao_atualizacao" \
          " WHERE atudb_action = 'COMPLETE' AND atudb_type = 'ATUDB' AND file_atualizacao = 'criaDB0001'";
   bCriaDB0001 = !ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL);
   //Arquivo de criação de todas as procedures do sistema SFG
   sSQL = "SELECT file_atualizacao FROM tbl_execucao_atualizacao" \
          " WHERE atudb_action = 'COMPLETE' AND atudb_type = 'ATUDB' AND file_atualizacao = 'criaDB0002'";
   bCriaDB0002 = !ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL);
   sSQL = "SELECT file_atualizacao FROM tbl_execucao_atualizacao" \
          " WHERE atudb_action = 'COMPLETE' AND atudb_type = 'ATUDB' AND file_atualizacao = 'atualizaDB0001'";
   bAtuDB0001 = !ValidacoesDB::ExistePrimaryKey(AppConnection, sSQL);

   if (bCriaDB0001 || bCriaDB0002 || bAtuDB0001) {
      sMsg = "Será necessário atualizar a base dados para o sistema SFG.\n" \
             "Algumas rotinas de atualização não foram completamente executadas.\n" \
             "São necessários os arquivos:";
      if (bCriaDB0001) sMsg += " criaDB0001.xml";
      if (bCriaDB0002) sMsg += " criaDB0002.xml";
      if (bAtuDB0001) sMsg += " atualizaDB0001.xml";
      MessageBox(Handle,sMsg.c_str(),Caption.c_str(),APP_INFORM);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------

