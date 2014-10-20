//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "ZDataset.hpp"
#pragma hdrstop
#include "uCFin1003.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace uCFin1003
{
double VerificaClientAtraso(String CodCliente);
bool ValidaClienteInadimplente(String CodCliente);
bool ValidaClienteAtraso(String CodCliente);
//---------------------------------------------------------------------------
TDateTime QuintoDiaUtil;
void Determina5DiaUtil(Word wMonth)
{
   if (wMonth == 0) wMonth = MonthOf(Date());
   TDateTime PriDiaMes = EncodeDate(YearOf(Date()),wMonth,1);
   Word DayWeek = DayOfWeek(PriDiaMes);

   if (DayWeek == 1) {  //Domingo
      QuintoDiaUtil = PriDiaMes + 5;
   } else if (DayWeek == 2) {  //Segunda
      QuintoDiaUtil = PriDiaMes + 4;
   } else { //Restante
      QuintoDiaUtil = PriDiaMes + 6;
   }
}
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

   if (!ValidaClienteInadimplente(pDataSet->FieldByName("cod_cliente")->AsString))
      return false;

   if (!ValidaClienteAtraso(pDataSet->FieldByName("cod_cliente")->AsString))
      return false;
   //Se a condição de pagamento for a parametrizada na conta a receber
   //Chama a tela de solicitação de senha do cliente esperando o retorno
   if (pDataSet->FieldByName("cod_forma_pagto")->AsInteger == forma_pagto_senha) {
      TCFin1003A *pFormPdw = new TCFin1003A(Application);
      pFormPdw->cod_cliente = pDataSet->FieldByName("cod_cliente")->AsString;
      iModalResult = pFormPdw->ShowModal();
      bRetorno = (iModalResult == mrOk) ? true : false;
      delete pFormPdw;
   }
   return bRetorno;
}
//---------------------------------------------------------------------------
__fastcall TCFin1003A::TCFin1003A(TComponent* Owner)
	: TForm(Owner,1)
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
void __fastcall TCFin1003A::BtOKClick(TObject *Sender)
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
bool ValidaClienteInadimplente(String CodCliente) {
   bool bReturn = true;
	TZQuery *QyCt = new TZQuery(Application);
   String SQL = "\
SELECT ies_inadimplente\
  FROM tbl_cliente\
 WHERE cod_cliente = " + QuotedStr(CodCliente) + "\
   AND ies_inadimplente = 'S'";

try {
	QyCt->Connection = AppConnection;
	QyCt->SQL->Text = SQL;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
      bReturn = false;
      String sMsg = "O cliente " + CodCliente + " possui restrição de crédito.";
      TCFin1003C *pFin1003C = new TCFin1003C(Application,sMsg);
      pFin1003C->ShowModal();
      delete pFin1003C;
	}
} catch (...) {
}
	delete(QyCt);
   return bReturn;
}
//---------------------------------------------------------------------------
bool ValidaClienteAtraso(String CodCliente) {
   double nAtraso = 0;
   if (Date() >= (QuintoDiaUtil + 1)) {
      nAtraso = VerificaClientAtraso(CodCliente);
      if (nAtraso > 0) {
         String sMsg = "O cliente " + CodCliente + " possui o valor de " +\
                       FloatToStrF(nAtraso, ffCurrency, 15, 2) + " em atraso.";
         TCFin1003B *pFin1003B = new TCFin1003B(Application,sMsg);
         int ModalResul = pFin1003B->ShowModal();
         delete pFin1003B;
         return (ModalResul == mrOk);
      }
   } else
      return true;
}
//---------------------------------------------------------------------------
double VerificaClientAtraso(String CodCliente)
{
   double nReturn = 0;
	TZQuery *QyCt = new TZQuery(Application);
   String SQL = \
   "SELECT sum(pagto.valor_parcela) valor_atraso\
  FROM tbl_conta_receber_pagto pagto\
 INNER JOIN tbl_conta_receber conta\
    ON conta.cod_conta_receber = pagto.cod_conta_receber\
 WHERE conta.cod_cliente = " + QuotedStr(CodCliente) + "\
   AND pagto.ies_recebido = 'N'\
   AND pagto.data_vencimento < :quinto_dia_util";

try {
	QyCt->Connection = AppConnection;
	QyCt->SQL->Text = SQL;
	QyCt->ParamByName("quinto_dia_util")->AsDateTime = QuintoDiaUtil;
	QyCt->Active = true;
	if (QyCt->RecordCount > 0) {
		nReturn = QyCt->FieldByName("valor_atraso")->AsFloat;
	}
} catch (...) {
}
	delete(QyCt);
   return nReturn;
}
//---------------------------------------------------------------------------
__fastcall TCFin1003B::TCFin1003B(TComponent* Owner, String sMsg)
	: TForm(Owner,1)
{
   this->BorderStyle = bsDialog;
   this->BorderIcons = TBorderIcons() << biSystemMenu;
   this->Caption = "Cliente em Atraso";
   this->Position = poDesktopCenter;

   Image = new TImage(this);
   Image->Name = "Image";
   Image->Parent = this;
   Image->Picture->Icon->Handle = LoadIcon(0, IDI_EXCLAMATION);
   Image->SetBounds(6, 6, 32, 32);
   ClienteMsg = new TLabel(this);
   ClienteMsg->Name = "ClienteMsg";
   ClienteMsg->Parent = this;
   ClienteMsg->WordWrap = false;
   ClienteMsg->AutoSize = true;
   ClienteMsg->SetBounds(44, 6, 100, 16);
   ClienteMsg->Font->Color = clRed;
   ClienteMsg->Font->Style = TFontStyles() << fsBold;
   ClienteMsg->Caption = sMsg;
   LiberaMsg = new TLabel(this);
   LiberaMsg->Name = "LiberaMsg";
   LiberaMsg->Parent = this;
   LiberaMsg->WordWrap = false;
   LiberaMsg->AutoSize = true;
   LiberaMsg->SetBounds(44, ClienteMsg->Top + ClienteMsg->Height + 6, 100, 16);
   LiberaMsg->Font->Color = clBlue;
   LiberaMsg->Font->Style = TFontStyles() << fsBold;
   LiberaMsg->Caption = "Novas vendas para o mesmo estão sujeitas a aprovação.";

   pBtLibera = new TButton(this);
   pBtLibera->Parent = this;
   pBtLibera->Caption = "&Liberar";
   pBtLibera->Default = true;
   pBtLibera->ModalResult = mrOk;

   pBtCancel = new TButton(this);
   pBtCancel->Parent = this;
   pBtCancel->Caption = "&Cancelar";
   pBtCancel->Cancel = true;
   pBtCancel->ModalResult = mrCancel;
   pBtCancel->SetBounds(44+((ClienteMsg->Width > LiberaMsg->Width)? ClienteMsg->Width - 96: LiberaMsg->Width - 96),45,100,23);
   pBtLibera->SetBounds(pBtCancel->Left-104,45,100,23);

   this->ClientWidth = pBtCancel->Left + pBtCancel->Width + 6;
   this->ClientHeight = pBtCancel->Top + pBtCancel->Height + 6;
   MessageBeep(MB_ICONSTOP);
}
//---------------------------------------------------------------------------
__fastcall TCFin1003C::TCFin1003C(TComponent* Owner, String sMsg)
	: TForm(Owner,1)
{
   this->BorderStyle = bsDialog;
   this->BorderIcons = TBorderIcons() << biSystemMenu;
   this->Caption = "Cliente Bloqueado";
   this->Position = poDesktopCenter;

   Image = new TImage(this);
   Image->Name = "Image";
   Image->Parent = this;
   Image->Picture->Icon->Handle = LoadIcon(0, IDI_ERROR);
   Image->SetBounds(6, 6, 32, 32);
   ClienteMsg = new TLabel(this);
   ClienteMsg->Name = "ClienteMsg";
   ClienteMsg->Parent = this;
   ClienteMsg->WordWrap = false;
   ClienteMsg->AutoSize = true;
   ClienteMsg->SetBounds(44, 6, 100, 16);
   ClienteMsg->Font->Color = clRed;
   ClienteMsg->Font->Style = TFontStyles() << fsBold;
   ClienteMsg->Caption = sMsg;
   LiberaMsg = new TLabel(this);
   LiberaMsg->Name = "LiberaMsg";
   LiberaMsg->Parent = this;
   LiberaMsg->WordWrap = false;
   LiberaMsg->AutoSize = true;
   LiberaMsg->SetBounds(44, ClienteMsg->Top + ClienteMsg->Height + 6, 100, 16);
   LiberaMsg->Font->Color = clBlue;
   LiberaMsg->Font->Style = TFontStyles() << fsBold;
   LiberaMsg->Caption = "Novas vendas para o mesmo somente com aprovação da gerência.";

   pBtOK = new TButton(this);
   pBtOK->Parent = this;
   pBtOK->Caption = "&OK";
   pBtOK->Default = true;
   pBtOK->ModalResult = mrOk;

   pBtOK->SetBounds(44+((ClienteMsg->Width > LiberaMsg->Width)? ClienteMsg->Width - 70: LiberaMsg->Width - 70),45,75,23);

   this->ClientWidth = pBtOK->Left + pBtOK->Width + 6;
   this->ClientHeight = pBtOK->Top + pBtOK->Height + 6;
   MessageBeep(MB_ICONSTOP);
}
//---------------------------------------------------------------------------
} //end namespace uFin1003
//---------------------------------------------------------------------------
