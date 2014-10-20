//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uFormBase02.h"
#include "uSfgToolTip.h"
#pragma hdrstop
#include "uCVdp1020.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "uCVdp1020A.dfm"
//---------------------------------------------------------------------------
namespace uCVdp1020
{
//---------------------------------------------------------------------------
String cod_cliente;
class THackfrmBase02 : public TfrmBase02 {
public:
   void __fastcall BtSenhaClick(TObject *Sender);
};
//---------------------------------------------------------------------------
void __fastcall THackfrmBase02::BtSenhaClick(TObject *Sender)
{
   THackfrmBase02 *pForm02;
   TComponent *pComponent;
   TCVdp1020A *pFormPdw = new TCVdp1020A(Application);
   pForm02 = (THackfrmBase02*)((TResBitBtn*)Sender)->Parent->Parent;
   pComponent = pForm02->FindComponent("QyCadCliente");
   if (pComponent)
      cod_cliente = ((TDataSet*)pComponent)->FieldByName("cod_cliente")->AsString;
   pFormPdw->ShowModal();
   delete pFormPdw;
}
//---------------------------------------------------------------------------
void CreateButtonSenha(TForm *pForm)
{
   THackfrmBase02 *pForm02 = (THackfrmBase02*)pForm;
   TResBitBtn *btExit = pForm02->SfgToolbar->btExit;
   TResBitBtn *btSenha = new TResBitBtn(pForm02);
   btSenha->NumGlyphs = 4;
   btSenha->Glyph->LoadFromResourceName((UINT)HInstance,"BTSENHA");
   btSenha->Parent = pForm02->SfgToolbar;
   btSenha->SetBounds(btExit->Left,btExit->Top,btExit->Width,btExit->Height);
   btSenha->Hint = "Indicar a senha do cliente para ser solicitada|na liberação de uma venda ao mesmo.";
   btSenha->OnClick = &pForm02->BtSenhaClick;
   btSenha->TabOrder = btExit->TabOrder;
   btSenha->Enabled = false;
   btExit->Left += 38;
   pForm02->Tolltips->AddToolTip(btSenha);
}
//---------------------------------------------------------------------------
void CreateFieldInadimplente(TForm *pForm)
{
   TDBCheckBox *ies_ativo = (TDBCheckBox*)pForm->FindComponent("ies_ativo");
   TZQuery *QyCadCliente = (TZQuery*)pForm->FindComponent("QyCadCliente");
   if (QyCadCliente) {
      String sSQLOrig = QyCadCliente->SQL->Text;
      String sSQLDest = "";
      int nPosFrom = sSQLOrig.Pos("FROM");
      sSQLDest = sSQLOrig.SubString(0,nPosFrom-1).TrimRight();
      sSQLDest += ",ies_inadimplente " + sSQLOrig.SubString(nPosFrom,sSQLOrig.Length()-nPosFrom);
      QyCadCliente->SQL->Text = sSQLDest;
   }
   if (ies_ativo) {
      TDBCheckBox *ies_inadimplente = new TDBCheckBox(ies_ativo->Owner);
      ies_inadimplente->Parent = ies_ativo->Parent;
      ies_inadimplente->Caption = "&Inadimplente?";
      ies_inadimplente->DataField = "ies_inadimplente";
      ies_inadimplente->DataSource = ies_ativo->DataSource;
      ies_inadimplente->TabOrder = ies_ativo->TabOrder + 1;
      ies_inadimplente->Top = ies_ativo->Top;
      ies_inadimplente->Height = ies_ativo->Height;
      ies_inadimplente->Left = (ies_ativo->Left + ies_ativo->Width + 10);
      ies_inadimplente->Width = 90;
      ies_inadimplente->ValueChecked = 'S';
      ies_inadimplente->ValueUnchecked = 'N';
   }
}
//---------------------------------------------------------------------------
__fastcall TCVdp1020A::TCVdp1020A(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCVdp1020A::btOKClick(TObject *Sender)
{
   if(!edtPdw->Text.Length()){
      MessageBox(Handle,"Entre com o senha do cliente!",Caption.c_str(),APP_ATENTION);
      edtPdw->SetFocus();
      return;
   }
   if(!edtCfm->Text.Length()){
      MessageBox(Handle,"Entre com a confirmação da senha do cliente!",Caption.c_str(),APP_ATENTION);
      edtCfm->SetFocus();
      return;
   }
   if(edtPdw->Text != edtCfm->Text) {
      MessageBox(Handle,"A confirmação da senha não confere!",Caption.c_str(),APP_ATENTION);
      edtCfm->SetFocus();
      return;
   }
   if(!SalvarSenha())
      return;
	this->Close();
}
//---------------------------------------------------------------------------
bool __fastcall TCVdp1020A::SalvarSenha()
{
   TZQuery *QySenha;
   String sSQL;
   String SenhaCripto = EncryptText(edtPdw->Text.c_str());
try {
   QySenha = new TZQuery(Application);
   QySenha->Connection = AppConnection;
   sSQL = "SELECT senha_cliente FROM tbl_cliente_ctm WHERE cod_cliente = " + QuotedStr(cod_cliente);
   QySenha->SQL->Text = sSQL;
   QySenha->Open();
   if (QySenha->RecordCount){
      sSQL = "UPDATE tbl_cliente_ctm SET senha_cliente = " + QuotedStr(SenhaCripto) + \
             " WHERE cod_cliente = " + QuotedStr(cod_cliente);
   } else {
      sSQL = "INSERT INTO tbl_cliente_ctm (cod_cliente,senha_cliente)" \
             " VALUES (" + QuotedStr(cod_cliente) + "," +  QuotedStr(SenhaCripto) + ")";
   }
   QySenha->Close();
   QySenha->SQL->Text = sSQL;
   QySenha->ExecSQL();
} catch(Exception &e){
   String Msg = "Ocorreu o seguinte erro ao salvar a senha do cliente:\n";
   Msg = Msg + e.Message;
   MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
   delete QySenha;
   return false;
}
   delete QySenha;
   return true;
}
//---------------------------------------------------------------------------
} //end namespace uCVdp1020
//---------------------------------------------------------------------------


