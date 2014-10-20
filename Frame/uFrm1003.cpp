/*
Módulo: Framework SoftGreen
Função: Alteração Senha Usuário
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFrm1003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1003(void) {
   AddAppForm("Frm1003","Alterar Senha");
   AddAppFormClass("TFrm1003",__classid(TFrm1003));
}
#pragma startup RegisterFrm1003
//---------------------------------------------------------------------------
__fastcall TFrm1003::TFrm1003(TComponent* Owner)
        : TfrmBase01(Owner)
{
	Senha->Color = AppConfig->Colors->Enabled;
	NvSenha->Color = AppConfig->Colors->Enabled;
	CfSenha->Color = AppConfig->Colors->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1003::btConfirmarClick(TObject *Sender)
{
  TZQuery *QyConsulta;
  if(!Senha->Text.Length()){
     MessageBox(Handle,"Entre com a senha do usuário!",
					 Caption.c_str(),APP_ATENTION);
     Senha->SetFocus();
    return;
  }
  if(!NvSenha->Text.Length()){
     MessageBox(Handle,"Entre com a nova senha!",
					 Caption.c_str(),APP_ATENTION);
     NvSenha->SetFocus();
    return;
  }
  if(!CfSenha->Text.Length()){
     MessageBox(Handle,"Entre com a confimação da senha!",
					 Caption.c_str(),APP_ATENTION);
     CfSenha->SetFocus();
    return;
  }
  if(!SenhaValida()) return;
  if(CfSenha->Text != NvSenha->Text){
     MessageBox(Handle,"A confirmação da senha não confere!",
					 Caption.c_str(),APP_ATENTION);
	  CfSenha->SetFocus();
	  return;
  }
  else{
    String SenhaCripto = EncryptText(NvSenha->Text.c_str());
    QyConsulta = new TZQuery(Application);
	 QyConsulta->Connection = AppConnection;
	 QyConsulta->SQL->Add("UPDATE tbl_usuario SET senha = '" + SenhaCripto + "'");
	 QyConsulta->SQL->Add("WHERE usuario = '" + AppUser->Usuario + "';");
    //ShowMessage(QyConsulta->SQL->Text);
    QyConsulta->ExecSQL();
	 MessageBox(Handle,"Senha alterada com sucesso!",Caption.c_str(),APP_INFORM);
    delete QyConsulta;
  }
  Close();
}
//---------------------------------------------------------------------------
bool __fastcall TFrm1003::SenhaValida()
{
  TZQuery *QyConsulta;
  String SenhaCripto = EncryptText(Senha->Text.c_str());
try{
  QyConsulta = new TZQuery(Application);
  QyConsulta->Connection = AppConnection;
  QyConsulta->SQL->Add("SELECT senha FROM tbl_usuario");
  QyConsulta->SQL->Add("WHERE usuario = '" + AppUser->Usuario + "';");
  QyConsulta->Open();
  if(QyConsulta->FieldByName("senha")->AsString == SenhaCripto){
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
void __fastcall TFrm1003::btCancelarClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------

