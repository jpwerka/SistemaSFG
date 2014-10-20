//---------------------------------------------------------------------------
#pragma hdrstop
#include "ConverterQR2FR.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void __fastcall TConverterQr2Fr::AddObjects(TQRCustomBand* ABand, TfrxBand* Band)
{
  int i;
  TfrxMemoView *Memo;
  TfrxRichView *Rich;
  TfrxShapeView *Shape;
  TfrxLineView *Line;
  TfrxPictureView *Image;

  TControl *pCt;
  TQRCustomLabel *Lbl;
  TQRRichText *Rt;
  TQRShape *Sh;
  TQRImage *Img;

  for (i= 0; i < ABand->ControlCount; i++) {
    pCt = ABand->Controls[i];
    if(pCt == NULL)
         continue;
    if (pCt->InheritsFrom(__classid(TQRCustomLabel))) {
      Lbl = (TQRCustomLabel*)pCt;
      Memo = new TfrxMemoView(Band);
      Memo->CreateUniqueName();
      if (Lbl->ClassNameIs("TQRDBText" )) {
         Memo->DataField = ((TQRDBText*)Lbl)->DataField;
         Memo->DataSetName  = ((TQRDBText*)Lbl)->DataSet->Name;
         Memo->Memo->Text = "[" + Memo->DataSetName + ".\"" + Memo->DataField + "\"]";
      } else if (Lbl->ClassNameIs("TQRSysData" )) {
         switch (((TQRSysData*)Lbl)->Data) {
            case qrsTime:
               Memo->Memo->Text = "[TIME]";
            break;
            case qrsDate:
               Memo->Memo->Text = "[DATE]";
            break;
            case qrsDateTime:
               Memo->Memo->Text = "[DATE] [TIME]";
            break;
            case qrsPageNumber:
               Memo->Memo->Text = "[PAGE#]";
            break;
            case qrsReportTitle:
               Memo->Memo->Text = Source->ReportTitle;
            break;
            case qrsDetailCount:
               Memo->Memo->Text = "[COUNT()]";
            break;
            case qrsDetailNo:
               Memo->Memo->Text = "[LINE#]";
            break;
         }
      } else {
         if (Lbl->Caption == "")
            Memo->Memo->Text = Lbl->Lines->Text;
         else
            Memo->Memo->Text = Lbl->Caption;
         if (ABand->BandType == rbDetail && Lbl->Caption == "COUNT")
            Memo->Memo->Text = "[LINE]";
      }
      if (!((TQRLabel*)Lbl)->ParentFont) {
         Memo->Font->Assign(Lbl->Font);
      }
      if (((TQRLabel*)Lbl)->AlignToBand) {
         if (Lbl->Alignment == taCenter) {
            Memo->Align = baCenter;
            Memo->HAlign = haCenter;
         }
         else if (Lbl->Alignment == taRightJustify) {
            Memo->Align = baRight;
            Memo->HAlign = haRight;
         }
         else
            Memo->Align = baLeft;
      } else {
         if (Lbl->Alignment == taCenter)
            Memo->HAlign = haCenter;
         else if (Lbl->Alignment == taRightJustify)
            Memo->HAlign = haRight;
      }
      if (Lbl->AutoSize || Lbl->AutoStretch) {
         Memo->Clipped = false;
         Memo->WordWrap = false;
      } else {
         Memo->WordWrap = Lbl->WordWrap;
      }
      Memo->SetBounds(Lbl->Left, Lbl->Top, Lbl->Width, Lbl->Height);
    }
    else if (pCt->InheritsFrom(__classid(TQRRichText))) {
      Rt = (TQRRichText*)pCt;
      Rich = new TfrxRichView(Band);
      Rich->CreateUniqueName();
      Rich->RichEdit->Lines->Assign(Rt->Lines);
      Rich->RichEdit->Font->Assign(Rt->Font);
      Rich->Color = Rt->Color;
      Rich->SetBounds(Rt->Left, Rt->Top, Rt->Width, Rt->Height);
    }
    else if (pCt->InheritsFrom(__classid(TQRShape))) {
      Sh = (TQRShape*)pCt;
      if (Sh->Shape == qrsRectangle || Sh->Shape == qrsCircle) {
         Shape = new TfrxShapeView(Band);
         Shape->CreateUniqueName();
         Shape->Shape = (Sh->Shape == qrsRectangle) ? skRectangle : skEllipse;
         Shape->SetBounds(Sh->Left, Sh->Top, Sh->Width, Sh->Height);
      } else {
         Line = new TfrxLineView(Band);
         Line->CreateUniqueName();
         Line->Frame->Color = Sh->Pen->Color;
         Line->SetBounds(Sh->Left, Sh->Top, Sh->Width, Sh->Height);
      }
    }
    else if (pCt->InheritsFrom(__classid(TQRImage))) {
      Img = (TQRImage*)pCt;
      Image = new TfrxPictureView(Band);
      Image->CreateUniqueName();
      Image->Picture->Assign(Img->Picture);
      Image->SetBounds(Img->Left, Img->Top, Img->Width, Img->Height);
    }
  }
  if (ABand->Frame->DrawBottom && ABand->Frame->DrawTop &&
      ABand->Frame->DrawLeft && ABand->Frame->DrawRight) {
      Shape = new TfrxShapeView(Band);
      Shape->CreateUniqueName();
      Shape->Shape = skRectangle;
      Shape->Align = baWidth;
      Shape->Frame->Color = ABand->Frame->Color;
      Shape->Frame->Width = ABand->Frame->Width;
  } else {
      if (ABand->Frame->DrawBottom) {
         Line = new TfrxLineView(Band);
         Line->CreateUniqueName();
         Line->Align = baBottom;
         Line->Frame->Color = ABand->Frame->Color;
         Line->Frame->Width = ABand->Frame->Width;
         Line->SetBounds(0, ABand->Height, ABand->Width, 0);
      }
      if (ABand->Frame->DrawTop) {
         Line = new TfrxLineView(Band);
         Line->CreateUniqueName();
         Line->Align = baWidth;
         Line->Frame->Color = ABand->Frame->Color;
         Line->Frame->Width = ABand->Frame->Width;
         Line->SetBounds(0, 0, ABand->Width, 0);
      }
      if (ABand->Frame->DrawLeft) {
         Line = new TfrxLineView(Band);
         Line->CreateUniqueName();
         Line->Align = baLeft;
         Line->Frame->Color = ABand->Frame->Color;
         Line->Frame->Width = ABand->Frame->Width;
         Line->SetBounds(0, 0, 0, ABand->Height);
      }
      if (ABand->Frame->DrawRight) {
         Line = new TfrxLineView(Band);
         Line->CreateUniqueName();
         Line->Align = baRight;
         Line->Frame->Color = ABand->Frame->Color;
         Line->Frame->Width = ABand->Frame->Width;
         Line->SetBounds(ABand->Width, 0, 0, ABand->Height);
      }
  }
}

void __fastcall TConverterQr2Fr::Convert()
{
   if (Source == NULL)
    throw new Exception("Source not assigned");
   if (Target == NULL)
    throw new Exception("Target not assigned");

  Target->Clear();
  CreateMainBands();
}

void __fastcall TConverterQr2Fr::CreateCustomBand(TQRCustomBand *ABand)
{
  TfrxBand *Band;
  if (ABand->BandType == rbPageHeader)
    Band = new TfrxPageHeader(Target->Pages[0]);
  else
  if (ABand->BandType == rbPageFooter)
    Band = new TfrxPageFooter(Target->Pages[0]);
  else
  if (ABand->BandType == rbTitle)
    Band = new TfrxHeader(Target->Pages[0]);
  else
  if (ABand->BandType == rbChild)
    Band = new TfrxChild(Target->Pages[0]);
  else
  if (ABand->BandType == rbColumnHeader)
    Band = new TfrxColumnHeader(Target->Pages[0]);
  else
  if (ABand->BandType == rbGroupHeader) {
    Band = new TfrxGroupHeader(Target->Pages[0]);
    if (ABand->ClassNameIs("TQRGroup"))
      ((TfrxGroupHeader*)Band)->Condition = ((TQRGroup*)ABand)->Expression;
  }
  else
  if (ABand->BandType == rbGroupFooter)
    Band = new TfrxGroupFooter(Target->Pages[0]);
  else
  if (ABand->BandType == rbDetail)
    Band = new TfrxMasterData(Target->Pages[0]);
  else
  if (ABand->ClassNameIs("TQRSubDetail"))
    Band = new TfrxDetailData(Target->Pages[0]);
  else
    return;

  if (!ABand->ParentFont)
    Band->Font->Assign(ABand->Font);
  Band->CreateUniqueName();

  Band->Top = ABand->Top;
  Band->Height = ABand->Height;

  AddObjects(ABand, Band);
}

void __fastcall TConverterQr2Fr::CreateMainBands()
{
   TfrxReportPage *Page;
   int i;

   Page = new TfrxReportPage(Target);
   Page->CreateUniqueName();
   Page->SetDefaults();

   for (i = 0; i < Source->BandList->Count; i++) {
      CreateCustomBand((TQRCustomBand*)Source->BandList->Items[i]);
   }
}
