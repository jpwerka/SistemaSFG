////---------------------------------------------------------------------------
//#include <vcl.h>
//#include "uSfgGlobals.h"
//#include "uSfgTools.h"
//#include "uDataModule.h"
//#include "uFormBase02.h"
//#include "uSfgToolTip.h"
//#pragma hdrstop
//#include "uCVdp1010.h"
////---------------------------------------------------------------------------
//#pragma package(smart_init)
////---------------------------------------------------------------------------
//namespace uCVdp1010
//{
////---------------------------------------------------------------------------
//class THackVdp1010 : public TfrmBase02 {
//public:
//   void __fastcall BtParametroClick(TObject *Sender);
//};
////---------------------------------------------------------------------------
//void __fastcall THackVdp1010::BtParametroClick(TObject *Sender)
//{
//   TCVdp1010A *pFormPgto = new TCVdp1010A(Application);
//   pFormPgto->ShowModal();
//   delete pFormPgto;
//}
////---------------------------------------------------------------------------
//void CreateButtonParametro(TForm *pForm)
//{
//   THackVdp1010 *pForm02 = (THackVdp1010*)pForm;
//   TResBitBtn *btExit = pForm02->SfgToolbar->btExit;
//   TResBitBtn *btParametro = new TResBitBtn(pForm02);
//   btParametro->GlyphLoadType = glByResName;
//   btParametro->GlyphResName = "ANOTAR";
//   btParametro->Parent = pForm02->SfgToolbar;
//   btParametro->SetBounds(btExit->Left,btExit->Top,btExit->Width,btExit->Height);
//   btParametro->Hint = "Indicar a forma de pagamento para ser utilizada|na venda sem lançamento da conta no financeiro.";
//   btParametro->OnClick = &pForm02->BtParametroClick;
//   btParametro->TabOrder = btExit->TabOrder;
//   btExit->Left += 38;
//   pForm02->Tolltips->AddToolTip(btParametro);
//}
////---------------------------------------------------------------------------
//__fastcall TCVdp1010A::TCVdp1010A(TComponent* Owner)
//	: TForm(Owner,1)
//{
//   this->BorderStyle = bsDialog;
//   this->BorderIcons = TBorderIcons() << biSystemMenu;
//   this->Caption = "Forma pagamento";
//   this->Position = poDesktopCenter;
//   this->ClientHeight = 68;
//   this->ClientWidth = 185;
//   pLabel = new TLabel(this);
//   pLabel->Parent = this;
//   pLabel->Caption = "&Forma pagamento:";
//   pLabel->SetBounds(10,12,88,13);
//   pEdtPgto = new TAlignEdit(this);
//   pEdtPgto->Parent = this;
//   pEdtPgto->Alignment = taRightJustify;
//   pEdtPgto->SetBounds(105,8,70,21);
//	SetWindowLong(pEdtPgto->Handle, GWL_STYLE, GetWindowLong(pEdtPgto->Handle, GWL_STYLE) | ES_NUMBER);
//   pLabel->FocusControl = pEdtPgto;
//   pBtOK = new TButton(this);
//   pBtOK->Parent = this;
//   pBtOK->Caption = "&OK";
//   pBtOK->Default = true;
//   //pBtOK->ModalResult = mrOk;
//   pBtOK->OnClick = &BtOKClick;
//   pBtOK->SetBounds(13,38,75,22);
//   pBtCancel = new TButton(this);
//   pBtCancel->Parent = this;
//   pBtCancel->Caption = "&Cancelar";
//   pBtCancel->Cancel = true;
//   pBtCancel->ModalResult = mrCancel;
//   pBtCancel->SetBounds(97,38,75,22);
//   pEdtPgto->Text = VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_numero('forma_pagto_sem_finc');"));
//}
////---------------------------------------------------------------------------
//void __fastcall TCVdp1010A::BtOKClick(TObject *Sender)
//{
//   String sSQL;
//
//   if (pEdtPgto->Text.Length() == 0) {
//      MessageBox(NULL,"Informe o código da forma de pagamento sem integração com o financeiro.","Forma pagamento",APP_ATENTION);
//      return;
//   }
//   sSQL = "CALL set_parametro_numero('forma_pagto_sem_finc'," + pEdtPgto->Text + ",'" + AppUser->Usuario + "');";
//   if (ValidacoesDB::SetParamValue(AppConnection,sSQL)) {
//      this->ModalResult = mrOk;
//   }
//}
////---------------------------------------------------------------------------
//} // end namespace uCVdp1010
////---------------------------------------------------------------------------
