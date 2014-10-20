//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "uSfgMsgOption.h"
#pragma package(smart_init)
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
   GetTextExtentPoint(Canvas->Handle, buffer, strlen(buffer)+1, &pSize);
   Point->y = pSize.cy;
   Point->x = pSize.cx / 52;
   delete[] buffer;
   return Point;
}

//---------------------------------------------------------------------------
int SfgMsgOption(String strMsg, TMsgDlgType DlgType, TStrings *DlgButtons,
    const String strCaption,
    const int DefaultButton,
    const int CancelButton)
{
   const mcHorzMargin = 8;
   const mcVertMargin = 8;
   const mcHorzSpacing = 10;
   const mcVertSpacing = 10;
   const mcButtonWidth = 50;
   const mcButtonHeight = 14;
   const mcButtonSpacing = 4;

   TPoint *DialogUnits;
   int i, HorzMargin, VertMargin, HorzSpacing, VertSpacing, ButtonWidth,
   ButtonHeight, ButtonSpacing, ButtonCount, ButtonGroupWidth,
   ButtonResult, IconTextWidth, IconTextHeight, X, ALeft;
   PChar IconID;
   TRect TextRect;
   TForm *form;
   TImage *Image = NULL;
   TLabel *Message = NULL;
   TButton *Button = NULL;
   int ret;

   form = new TForm(Application);
   form->Tag = 0;
   form->BiDiMode = Application->BiDiMode;
   form->BorderStyle = bsDialog;
   form->Canvas->Font = form->Font;
   DialogUnits = SfgCharSize(form->Canvas);
   HorzMargin = MulDiv(mcHorzMargin, DialogUnits->x, 4);
   VertMargin = MulDiv(mcVertMargin, DialogUnits->y, 8);
   HorzSpacing = MulDiv(mcHorzSpacing, DialogUnits->x, 4);
   VertSpacing = MulDiv(mcVertSpacing, DialogUnits->y, 8);
   ButtonWidth = MulDiv(mcButtonWidth, DialogUnits->x, 4);
   for (i=0; i<DlgButtons->Count; i++) {
      String strText = DlgButtons->Names[i];
      if(strText.Length() == 0)
         strText = DlgButtons->Strings[i];
      TextRect = Rect(0,0,0,0);
      DrawText(form->Canvas->Handle,strText.c_str(), -1,
            &TextRect, DT_CALCRECT | DT_LEFT | DT_SINGLELINE |
            form->DrawTextBiDiModeFlagsReadingOnly());
      if (ButtonWidth < ((TextRect.Width()+8)))
          ButtonWidth = TextRect.Width()+8;
   }
   ButtonHeight = MulDiv(mcButtonHeight, DialogUnits->y, 8);
   ButtonSpacing = MulDiv(mcButtonSpacing, DialogUnits->x, 4);
   SetRect(&TextRect, 0, 0, Screen->Width / 2, 0);
   DrawText(form->Canvas->Handle, strMsg.c_str(), strMsg.Length()+1, &TextRect,
      DT_EXPANDTABS | DT_CALCRECT | DT_WORDBREAK |
      form->DrawTextBiDiModeFlagsReadingOnly());
   IconTextWidth = TextRect.Right;
   IconTextHeight = TextRect.Bottom;
   if (DlgType != mtCustom) {
      IconTextWidth += (32 + HorzSpacing);
      if (IconTextHeight < 32)
         IconTextHeight = 32;
   }
   ButtonGroupWidth = 0;
   if (DlgButtons->Count != 0)
      ButtonGroupWidth = (ButtonWidth * DlgButtons->Count) + (ButtonSpacing * (DlgButtons->Count - 1));
   form->ClientWidth = ((IconTextWidth > ButtonGroupWidth) ? IconTextWidth : ButtonGroupWidth)+ HorzMargin * 2;
   form->ClientHeight = IconTextHeight + ButtonHeight + VertSpacing + VertMargin * 2;
   form->Left = (Screen->Width / 2) - (form->Width / 2);
   form->Top = (Screen->Height / 2) - (form->Height / 2);
   if (strCaption == NULL || strCaption.Length() == 0) {
      form->Caption = Application->Title;
   } else {
      form->Caption = strCaption;
   }
   if (DlgType != mtCustom) {
      switch(DlgType) {
         case mtInformation:
            IconID = IDI_ASTERISK;
            break;
         case mtWarning:
            IconID = IDI_EXCLAMATION;
            break;
         case mtError:
            IconID = IDI_HAND;
            break;
         case mtConfirmation:
            IconID = IDI_QUESTION;
            break;
         }
      Image = new TImage(form);
      Image->Name = "Image";
      Image->Parent = form;
      Image->Picture->Icon->Handle = LoadIcon(0, IconID);
      Image->SetBounds(HorzMargin, VertMargin, 32, 32);
   }
   Message = new TLabel(form);
   Message->Name = "Message";
   Message->Parent = form;
   Message->WordWrap = true;
   Message->Caption = strMsg;
   Message->BoundsRect = TextRect;
   Message->BiDiMode = form->BiDiMode;
   ALeft = IconTextWidth - TextRect.Right + HorzMargin;
   if (form->UseRightToLeftAlignment())
        ALeft = form->ClientWidth - ALeft - form->Width;
   Message->SetBounds(ALeft, VertMargin, TextRect.Right, TextRect.Bottom);

   X = (form->ClientWidth - ButtonGroupWidth) / 2;
   for (i=0; i<DlgButtons->Count; i++) {
      String strText = DlgButtons->Names[i];
      String strValue;
      if(strText.Length() == 0)
         strText = DlgButtons->Strings[i];
      strValue = DlgButtons->Values[strText];
      if(strValue.Length() == 0)
         ButtonResult = i;
      else
         ButtonResult = StrToInt(strValue);
      Button = new TButton(form);
      Button->Name = "Button" + IntToStr(i+1);
      Button->Parent = form;
      Button->Caption = strText;
      Button->ModalResult = ButtonResult;
      if (DefaultButton != -1 && DefaultButton == ButtonResult)
         Button->Default = true;
      if (CancelButton != -1 && CancelButton == ButtonResult)
         Button->Cancel = true;
      Button->SetBounds(X, IconTextHeight + VertMargin + VertSpacing,
            ButtonWidth, ButtonHeight);
      X += (ButtonWidth + ButtonSpacing);
   }

   ret = form->ShowModal();
   delete DialogUnits;
   delete form;
   return ret;
}
