//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uCVdp1001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace uCVdp1001
{
//---------------------------------------------------------------------------
int forma_pagto_senha;
bool ValidFormPgtoSenha(TForm *pForm)
{
   forma_pagto_senha = StrToInt(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_numero('forma_pagto_senha');")));
   if (forma_pagto_senha == 0)
      MessageBox(NULL,"Não foi parametrizada a forma de pagamento para solicitação de senha!", "Parametrização", APP_INFORM);
   return true;
}
//---------------------------------------------------------------------------
bool AfterValidInsert(TForm *pForm, TDataSet *pDataSet)
{
   int iModalResult;
   bool bRetorno = true;
   //Se a condição de pagamento for a parametrizada na conta a receber
   //Chama a tela de solicitação de senha do cliente esperando o retorno
   if (pDataSet->FieldByName("cod_forma_pagto")->AsInteger == forma_pagto_senha) {
      TCVdp1001A *pFormPdw = new TCVdp1001A(Application);
      pFormPdw->cod_cliente = pDataSet->FieldByName("cod_cliente")->AsString;
      iModalResult = pFormPdw->ShowModal();
      bRetorno = (iModalResult == mrOk) ? true : false;
      delete pFormPdw;
   }
   return bRetorno;
}
//---------------------------------------------------------------------------
__fastcall TCVdp1001A::TCVdp1001A(TComponent* Owner)
	: TForm(Owner, 1)
{
   this->BorderStyle = bsDialog;
   this->BorderIcons = TBorderIcons() << biSystemMenu;
   this->Caption = "Senha";
   this->Position = poDesktopCenter;
   this->ClientHeight = 68;
   this->ClientWidth = 185;
   pLabel = new TLabel(this);
   pLabel->Parent = this;
   pLabel->Caption = "&Senha:";
   pLabel->SetBounds(10,12,36,13);
   pEdtPdw = new TEdit(this);
   pEdtPdw->Parent = this;
   pEdtPdw->PasswordChar = '*';
   pEdtPdw->SetBounds(48,8,120,21);
   pLabel->FocusControl = pEdtPdw;
   pBtOK = new TButton(this);
   pBtOK->Parent = this;
   pBtOK->Caption = "&OK";
   pBtOK->Default = true;
   //pBtOK->ModalResult = mrOk;
   pBtOK->OnClick = &BtOKClick;
   pBtOK->SetBounds(13,38,75,22);
   pBtCancel = new TButton(this);
   pBtCancel->Parent = this;
   pBtCancel->Caption = "&Cancelar";
   pBtCancel->Cancel = true;
   pBtCancel->ModalResult = mrCancel;
   pBtCancel->SetBounds(97,38,75,22);
}
//---------------------------------------------------------------------------
void __fastcall TCVdp1001A::BtOKClick(TObject *Sender)
{
   TZQuery *QyConsulta;
   String SenhaCripto;

   if (pEdtPdw->Text.Length() == 0) {
      MessageBox(NULL,"Informe a senha do cliente para confirmar a operação.","Senha",APP_ATENTION);
      return;
   }
   SenhaCripto = EncryptText(pEdtPdw->Text.c_str());
try {
   QyConsulta = new TZQuery(Application);
   QyConsulta->Connection = AppConnection;
   QyConsulta->SQL->Add("SELECT senha_cliente FROM tbl_cliente_ctm");
   QyConsulta->SQL->Add("WHERE cod_cliente = '" + cod_cliente + "';");
   QyConsulta->Open();
   if (QyConsulta->RecordCount <= 0) {
      MessageBox(NULL,"O cliente não possui senha cadastrada.","Senha",APP_ATENTION);
      return;
   }
   if (QyConsulta->FieldByName("senha_cliente")->AsString == SenhaCripto) {
      this->ModalResult = mrOk;
   } else {
      MessageBox(NULL,"A senha do cliente não confere!","Senha",APP_ATENTION);
      pEdtPdw->SetFocus();
   }
}
__finally { delete(QyConsulta); }
}
//---------------------------------------------------------------------------
} //end namespace uCVdp1001
//---------------------------------------------------------------------------



