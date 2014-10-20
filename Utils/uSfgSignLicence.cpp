//---------------------------------------------------------------------------
//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TSfgSignLicence::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
#include <vcl.h>
#include <stdio.h>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#include "uSfgClientLicence.h"
#pragma hdrstop
#include "uSfgSignLicence.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
TSfgSignLicence *AppSignLicence = NULL;
//---------------------------------------------------------------------------
const char* SfgSignClientMsg  = {"0x%08X0x%08X"};
TSfgEndApplication *pEndApp = NULL;
TSfgMsgEndApp *pSfgMsgEndApp = NULL;
//---------------------------------------------------------------------------
__fastcall TSfgSignLicence::TSfgSignLicence(bool CreateSuspended)
   : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TSfgSignLicence::Execute()
{
   //String sMsg;
   bool bSigned = false;
   int iResult = 0;
   long lPreviousCount;

   //Montando a string que deverá ser retornada sempre que o server retornar SFG_RET_LIC_OK
   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(FRetMsgOK,21*sizeof(char));
   wsprintf(FRetMsgOK,"0x%08X0x%08X",GetCurrentProcessId(),SFG_RET_LIC_OK);

   //---- Place thread code here ----
   while (!Terminated) {
      //Espera pelo retorno do evento pelo tempo determinado
      iResult = WaitForSingleObject(AppClientLicence->AppEndSignEvent,SFG_SIGNED_TIME);
      if (iResult == WAIT_OBJECT_0) {
         break;
      }

      //Espera pela liberação do semaforo por 5 segundos
      WaitForSingleObject(AppClientLicence->AppSocketSemaphore,5000);
      //Se finalizou a thread não deve comunicar-se com o servidor de licenças
      if (Terminated) {
         //Libera o semaforo deste processo
         ReleaseSemaphore(AppClientLicence->AppSocketSemaphore,1,&lPreviousCount);
         break;
      }
      //Sinaliza ao servidor de licenças que a aplicação está ativa
      bSigned = LicenceSignClient(FErrorMsg);
      //Libera o semaforo deste processo
      ReleaseSemaphore(AppClientLicence->AppSocketSemaphore,1,&lPreviousCount);
      //Se não conseguiu avisar ao servidor de licenças
      //Vai criar uma segunda Thread, só pra derrubar o SFG
      //Pois ao exibir a mensagem se o usuário não der OK fica esperando
      if (!bSigned) {
         pEndApp = new TSfgEndApplication(false);
         Synchronize(this->CreateMsgEndApp);
         this->Terminate();
      }
   }
}
//---------------------------------------------------------------------------
bool __fastcall TSfgSignLicence::LicenceSignClient(String &sMsgError)
{
   //NxNNNNNNNN -> PID do processo client no formato Hexadecimal
   //NxNNNNNNNN -> Identificador da mensagem no formato Hexadecimal

   //Pega o usuário do sistema operacional
   bool bRetMsg = true;
   char cRetBuffer[21];

   //Zerando o buffer, caso tenha alguma mensagem
   ZeroMemory(AppLicenceSvr->MsgBuffer,(SFG_MAX_SIZE_MSG+1)*sizeof(char));
   //Formatando a mensagem para o servidor de licenças
   wsprintf(AppLicenceSvr->MsgBuffer,
            SfgSignClientMsg,
            GetCurrentProcessId(),
            SFG_SIGN_CLIENT);

try {
   AppLicenceSvr->LastMsg = SFG_SIGN_CLIENT;
   SfgDataCenter->ClientSocketSend();
   SfgDataCenter->ClientSocketRead();
} catch (Exception &e) {
   sMsgError = "Ocorreu o seguinte erro ao tentar comunicação com o servidor de licenças:\n";
   sMsgError += e.Message;
   bRetMsg = false;
}
   if (!bRetMsg)
      return false;

   if (AppLicenceSvr->MsgBuffer == NULL) {
      sMsgError = "Não foi possível receber a resposta do servidor de licenças!";
      return false;
   }
   //Se o tamanho da mensagem de retorno é menor do 20 - erro
   if (strlen(AppLicenceSvr->MsgBuffer) < SFG_MIN_MSG_RET) {
      sMsgError = "Resposta do servidor de licenças no formato desconhecido!";
      return false;
   }
   //Deve validar a mensagem de retorno
   for (int i=0; i < 20; i++)
      cRetBuffer[i] = AppLicenceSvr->MsgBuffer[i];
   cRetBuffer[20] = '\0';
   //Deve ter retonado o PID do processo + OK ambos formato HEX
   //Se o retorno foi negativo, deve mostrar a mensagem retornada
   if (strcmp(cRetBuffer,FRetMsgOK) != 0) {
      sMsgError = &AppLicenceSvr->MsgBuffer[23];
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TSfgSignLicence::CreateMsgEndApp(void)
{
   pSfgMsgEndApp = new TSfgMsgEndApp(Application,FErrorMsg);
}
//---------------------------------------------------------------------------
__fastcall TSfgEndApplication::TSfgEndApplication(bool CreateSuspended)
   : TThread(CreateSuspended)
{
}
//---------------------------------------------------------------------------
void __fastcall TSfgEndApplication::Execute()
{
   int iResult = 0;
   while (!Terminated) {
      iResult = WaitForSingleObject(AppClientLicence->AppEndSignEvent,SFG_SIGNED_TIME);
      if (iResult == WAIT_OBJECT_0) {
         break;
      }
      Synchronize(this->AppTerminate);
      this->Terminate();
   }
   pSfgMsgEndApp->Close();
   delete pSfgMsgEndApp;
   delete pEndApp;
}
//---------------------------------------------------------------------------
void __fastcall TSfgEndApplication::AppTerminate(void)
{
   Application->Terminate();
}
//---------------------------------------------------------------------------
TPoint* SfgCharSize(TCanvas *Canvas)
{
   TPoint *Point = new TPoint();
   SIZE pSize;
   int i;
   char *buffer = new char[sizeof(char)*53];
   ZeroMemory(buffer,sizeof(char)*53);
   for (i= 0; i<26; i++)
      buffer[i] = (char)(i + 'A');
   for (i= 0; i<26; i++)
      buffer[i + 26] = (char)(i + 'a');
   GetTextExtentPoint32(Canvas->Handle, buffer, strlen(buffer)+1, &pSize);
   Point->y = pSize.cy;
   Point->x = pSize.cx / 52;
   delete[] buffer;
   return Point;
}
//---------------------------------------------------------------------------
__fastcall TSfgMsgEndApp::TSfgMsgEndApp(TComponent* Owner, String sMsgError)
	: TForm(Owner,1)
{
   const mcHorzMargin = 8;
   const mcVertMargin = 8;
   const mcHorzSpacing = 10;
   const mcVertSpacing = 10;

   TPoint *DialogUnits;
   int HorzMargin, VertMargin, HorzSpacing, VertSpacing;
   TRect TextRect;

   iSeconds = SFG_SIGNED_TIME/1000;
   this->Tag = 0;
   this->BiDiMode = Application->BiDiMode;
   this->BorderStyle = bsDialog;
   this->BorderIcons = TBorderIcons();
   this->FormStyle = fsStayOnTop;
   this->Canvas->Font = this->Font;
   DialogUnits = SfgCharSize(this->Canvas);
   HorzMargin = MulDiv(mcHorzMargin, DialogUnits->x, 4);
   VertMargin = MulDiv(mcVertMargin, DialogUnits->y, 8);
   HorzSpacing = MulDiv(mcHorzSpacing, DialogUnits->x, 4);
   VertSpacing = MulDiv(mcVertSpacing, DialogUnits->y, 8);

   SetRect(&TextRect, 0, 0, Screen->Width / 2, 0);
   DrawText(this->Canvas->Handle, sMsgError.c_str(), sMsgError.Length()+1, &TextRect,
      DT_EXPANDTABS | DT_CALCRECT | DT_WORDBREAK |
      this->DrawTextBiDiModeFlagsReadingOnly());

   this->ClientWidth = TextRect.Right + 32 + HorzSpacing + (HorzMargin * 2);
   this->ClientHeight = ((TextRect.Bottom < 32) ? 32 : TextRect.Bottom) + VertSpacing + DialogUnits->y + (VertMargin * 2);
   this->Left = (Screen->Width / 2) - (this->Width / 2);
   this->Top = (Screen->Height / 2) - (this->Height / 2);
   this->Caption = Application->Title;

   Image = new TImage(this);
   Image->Name = "Image";
   Image->Parent = this;
   Image->Picture->Icon->Handle = LoadIcon(0, IDI_HAND);
   Image->SetBounds(HorzMargin, VertMargin, 32, 32);
   ErrorMsg = new TLabel(this);
   ErrorMsg->Name = "ErrorMsg";
   ErrorMsg->Parent = this;
   ErrorMsg->WordWrap = true;
   ErrorMsg->Caption = sMsgError;
   ErrorMsg->BiDiMode = this->BiDiMode;
   ErrorMsg->SetBounds((32 + (2 * HorzSpacing)), VertMargin, (TextRect.Right + 32 + (2 * HorzSpacing)), (TextRect.Bottom + VertMargin));

   TimeMsg = new TLabel(this);
   TimeMsg->Name = "TimeMsg";
   TimeMsg->Parent = this;
   TimeMsg->WordWrap = false;
   TimeMsg->BiDiMode = this->BiDiMode;
   TimeMsg->Left = HorzMargin;
   TimeMsg->Top = ((TextRect.Bottom) > (VertMargin + 32))?(TextRect.Bottom + (VertMargin*2)):(32 + (VertMargin*2));
   TimeMsg->AutoSize = true;
   TimeMsg->Font->Color = clRed;
   TimeMsg->Font->Style = TFontStyles() << fsBold;
   TimeMsg->Caption = "Sua aplicação será terminada em " + IntToStr(iSeconds) + " segundos.";

   MsgTimer = new TTimer(this);
   MsgTimer->Interval = 1000;
   MsgTimer->OnTimer = &MsgTimerTimer;
   MsgTimer->Enabled = true;
   
   MessageBeep(MB_ICONSTOP);
   this->OnClose = &FormClose;
   this->Show();
   delete DialogUnits;
}
//---------------------------------------------------------------------------
void __fastcall TSfgMsgEndApp::MsgTimerTimer(TObject *Sender)
{
   iSeconds--;
   TimeMsg->Caption = "Sua aplicação será terminada em " + IntToStr(iSeconds) + " segundos.";
}
//---------------------------------------------------------------------------
void __fastcall TSfgMsgEndApp::FormClose(TObject *Sender, TCloseAction &Action)
{
   MsgTimer->Enabled = false;
   Action = caFree;
}
//---------------------------------------------------------------------------


