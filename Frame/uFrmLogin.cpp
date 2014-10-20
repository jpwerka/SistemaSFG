//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uFrmMain.h"
#include "uSfgClientLicence.h"
#pragma hdrstop
#include "uFrmLogin.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TFrmLogin::TFrmLogin(TComponent* Owner)
		  : TForm(Owner)
{
}
//---------------------------------------------------------------------------
__fastcall TFrmLogin::~TFrmLogin()
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmLogin::btOKClick(TObject *Sender)
{
  if(!Login->Text.Length()){
     MessageBox(Handle,"Entre com o nome do usuário!",
                Caption.c_str(),APP_ATENTION);
     Login->SetFocus();
    return;
  }
  if(!Senha->Text.Length()){
     MessageBox(Handle,"Entre com a senha do usuário!",
                Caption.c_str(),APP_ATENTION);
     Senha->SetFocus();
    return;
  }
   if(!UserValido()) return;
	if(!SenhaValida()) return;
	CarregaInfoUser();
	this->Close();
   delete FrmMain->FrmLogin;
   FrmMain->FrmLogin = NULL;

   //Efetuado o login deve solicitar a licença ao servidor de licenças
   if (AppLicence->UseServer) {
      //Criando o objeto responsável por controlar a comunicação com o servidor
      AppClientLicence = new TSfgClientLicence();
      //Solicitando uma licença ao servidor
      if (!AppClientLicence->LicenceAddClient()) {
         FrmMain->Close();
         return;
      }
      SfgDataCenter->IsLicenceOK = true;
   }

   FrmMain->LoadSfgModulos();
	FrmMain->CriarMenu();
	FrmMain->OnPaint = &FrmMain->FormPaint;
}
//---------------------------------------------------------------------------
void __fastcall TFrmLogin::btCancelarClick(TObject *Sender)
{
	this->Close();
	Application->Terminate();
}
//---------------------------------------------------------------------------
bool __fastcall TFrmLogin::UserValido()
{
  TZQuery *QyConsulta;
try{
  QyConsulta = new TZQuery(Application);
  QyConsulta->Connection = AppConnection;
  QyConsulta->SQL->Add("SELECT usuario FROM tbl_usuario");
  QyConsulta->SQL->Add("WHERE usuario = '" + Login->Text + "';");
  QyConsulta->Open();
  if(QyConsulta->RecordCount){
    return true;
  }
   else {
      //Se está tentando entrar com o usuário administrador e o mesmo não existe
      //cadastra o usuário banco de dados com as informações padrões
      if (Login->Text.LowerCase() == "administrador") {
         if (CadastraUserAdm()) {
            return true;
         }
      } else {
         MessageBox(Handle,"Usuário não cadastrado!",Caption.c_str(),APP_ATENTION);
         Login->SetFocus();
         return false;
      }
   }
}
 __finally{delete(QyConsulta);}
  return false;
}
//---------------------------------------------------------------------------
bool __fastcall TFrmLogin::SenhaValida()
{
  TZQuery *QyConsulta;
  String SenhaCripto = EncryptText(Senha->Text.c_str());
try{
  QyConsulta = new TZQuery(Application);
  QyConsulta->Connection = AppConnection;
  QyConsulta->SQL->Add("SELECT senha FROM tbl_usuario");
  QyConsulta->SQL->Add("WHERE usuario = '" + Login->Text + "';");
  QyConsulta->Open();
  if(QyConsulta->FieldByName("senha")->AsString == SenhaCripto){
	 AppUser->Usuario = Login->Text;
	 return true;
  }
  else{
     MessageBox(Handle,"A senha do usuário não confere!",
                Caption.c_str(),APP_ATENTION);
     Senha->SetFocus();
    return false;
  }
}
 __finally{delete(QyConsulta);}
  return false;
}
//---------------------------------------------------------------------------
void __fastcall TFrmLogin::CarregaInfoUser()
{
	TZQuery *QyConsulta;
	String SenhaEmail;
	Variant Value;
try {
	QyConsulta = new TZQuery(Application);
	QyConsulta->Connection = AppConnection;
	QyConsulta->SQL->Add("SELECT nome, email, ies_administrador FROM tbl_usuario");
	QyConsulta->SQL->Add("WHERE usuario = '" + AppUser->Usuario + "';");
	QyConsulta->Open();
	AppParEmail->SMTPNomeExibicao = QyConsulta->FieldByName("nome")->AsString;
	AppParEmail->SMTPUsername = QyConsulta->FieldByName("email")->AsString;
	AppParEmail->SMTPConta = AppParEmail->SMTPUsername;
	Value = ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('epw_"+AppUser->Usuario+"');");
	SenhaEmail = VarToStr(Value);
	if (SenhaEmail.Length() > 0) {
		SenhaEmail = DecryptText(SenhaEmail.c_str());
		AppParEmail->SMTPPassword = SenhaEmail;
	} else {
		AppParEmail->SMTPPassword = "";
	}
   if (AppUser->Usuario == "administrador") {
      AppUser->IsAdm = true;
   } else {
      AppUser->IsAdm = (QyConsulta->FieldByName("ies_administrador")->AsString == "S");
   }
}
 __finally{delete(QyConsulta);}
}
//---------------------------------------------------------------------------
void __fastcall TFrmLogin::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
bool __fastcall TFrmLogin::CadastraUserAdm()
{
   bool bRet = false;
	TZQuery *QyCadAdm = new TZQuery(Application);
try {
   char *cSenha = EncryptText("administrador");
   String sSenha = cSenha;
   delete[] cSenha;
   QyCadAdm->Connection = AppConnection;
   QyCadAdm->SQL->Add("INSERT INTO tbl_usuario (usuario,nome,senha,ies_administrador)");
   QyCadAdm->SQL->Add(" VALUES ('administrador','Administrador','"+ sSenha +"','S')");
   QyCadAdm->ExecSQL();
   bRet = true;
} catch(Exception &e) {
   String Msg = "Ocorreu o seguinte erro ao tentar cadastro o administrador para primeiro acesso:\n" + e.Message;
   MessageBox(NULL,Msg.c_str(),"Mensagem de Erro",MB_OK | MB_ICONSTOP);
}
   delete QyCadAdm;
   return bRet;
}
//---------------------------------------------------------------------------







