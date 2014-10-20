//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgToolTip.h"
#include "uSfgTools.h"
#pragma hdrstop
#include "uSfgPreview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "frxClass"
#pragma link "frxDBSet"
#pragma link "frxChBox"
#pragma link "frxGradient"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterSfgPreview(void) {
   PreviewReportClass = __classid(TSfgPreview);
}
#pragma startup RegisterSfgPreview
const int ID_DICAS = 5000;
//---------------------------------------------------------------------------
/*void __fastcall ConvertQrToFr(TForm *Form)
{
   TForm *pForm = Form;
   TQuickRep *pQR = NULL;
   TComponent *pCp;

   for (int i=0; i < pForm->ComponentCount; i++) {
      pCp = pForm->Components[i];
      if (pCp->ClassNameIs("TQuickRep")) {
         pQR = (TQuickRep*)pCp;
         break;
      }
   }

   if (pQR != NULL) {
      TfrxReport *pFR = new TfrxReport(pForm);
      TConverterQr2Fr *pCV = new TConverterQr2Fr();
      pCV->Source = pQR;
      pCV->Target = pFR;
      pCV->Convert();
      String StrName = pForm->ClassName();
      StrName += ".fr3";
      pFR->SaveToFile(StrName);
      delete pCV;
      delete pFR;
   }
} */
//---------------------------------------------------------------------------
__fastcall TSfgPreview::TSfgPreview(TComponent* Owner)
        : TForm(Owner)
{
	int i;
	Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
	Tolltips->CreateToolTips();
	for(i = 0;i< BarraBotoes->ButtonCount;i++)
		Tolltips->AddToolTip(BarraBotoes,BarraBotoes->Buttons[i]->BoundsRect,
								ID_DICAS + i,BarraBotoes->Buttons[i]->Hint);
   //ConvertQrToFr((TForm*)Owner);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	delete Tolltips;
	if(PrewRelat->Report->Owner)
		((TForm*)PrewRelat->Report->Owner)->Close();
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::SetupPrinterExecute(TObject *Sender)
{
  //PrewRelat->PageSetupDlgA();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ImprimirExecute(TObject *Sender)
{
  PrewRelat->Print();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ZoomMaisExecute(TObject *Sender)
{
  if(PrewRelat->Zoom <  4)
    PrewRelat->Zoom =  PrewRelat->Zoom * 2;
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ZoomMenosExecute(TObject *Sender)
{
  if(PrewRelat->Zoom >  0.1)
    PrewRelat->Zoom =  PrewRelat->Zoom / 2;
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::FirstPageExecute(TObject *Sender)
{
  PrewRelat->First();
  //PaginaInfo();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::PrewPageExecute(TObject *Sender)
{
  PrewRelat->Prior();
  //PaginaInfo();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::NextPageExecute(TObject *Sender)
{
  PrewRelat->Next();
  //PaginaInfo();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::LastPageExecute(TObject *Sender)
{
  PrewRelat->Last();
  //PaginaInfo();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::PaginaInfo()
{
  String Info = " Página " + IntToStr(PrewRelat->PageNo) + " de " + IntToStr(PrewRelat->PageCount);
  BarraStatus->Panels->Items[0]->Text = Info;
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::AjustarExecute(TObject *Sender)
{
  PrewRelat->ZoomMode = zmWholePage;
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::AjustarlargExecute(TObject *Sender)
{
  PrewRelat->ZoomMode = zmPageWidth;
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::AjustarRealExecute(TObject *Sender)
{
  PrewRelat->Zoom =  1;
  CbZoom->Text = IntToStr(100);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::SalvarExecute(TObject *Sender)
{
   TSaveDialog *SaveDlg;
   SaveDlg = new TSaveDialog(Application);
   try {
      SaveDlg->Options = SaveDlg->Options << ofNoChangeDir;
      SaveDlg->FileName = PrewRelat->Report->ReportOptions->Name;
      SaveDlg->Filter = "Relatório preparado (*.fp3)|*.fp3";
      if (SaveDlg->Execute()) {
         PrewRelat->Workspace->Repaint();
         PrewRelat->SaveToFile(ChangeFileExt(SaveDlg->FileName, ".fp3"));
      }
   }
   __finally { delete SaveDlg; }
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::AbrirExecute(TObject *Sender)
{
   PrewRelat->LoadFromFile();
   if (PrewRelat->Report->ReportOptions->Name != "")
      Caption = PrewRelat->Report->ReportOptions->Name;
   else
      Caption = "Visualização de Relatórios";
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::CbZoomClick(TObject *Sender)
{
  PrewRelat->Zoom =  (CbZoom->Text.ToInt() / 100);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::FormResize(TObject *Sender)
{
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::CbZoomKeyPress(TObject *Sender,
      char &Key)
{
  if(Key == 13){
    if(CbZoom->Text.Length())
     if(CbZoom->Text.ToInt() > 0 && CbZoom->Text.ToInt() <= 400)
       PrewRelat->Zoom =  CbZoom->Text.ToInt() / 100;
  }
  else
    Validacoes::CharIsInteger(Key);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::FormMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
   PrewRelat->MouseWheelScroll(WheelDelta);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExitExecute(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::PrewRelatPageChanged(TfrxPreview *Sender,
      int PageNo)
{
  CbZoom->Text = IntToStr((int)(PrewRelat->Zoom * 100));
  PaginaInfo();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ToolButton17Click(TObject *Sender)
{
   PrewRelat->Export(SendByMail);
}
//---------------------------------------------------------------------------

void __fastcall TSfgPreview::ThumbBClick(TObject *Sender)
{
   PrewRelat->ThumbnailVisible = !PrewRelat->ThumbnailVisible;
}
//---------------------------------------------------------------------------

void __fastcall TSfgPreview::FindTextExecute(TObject *Sender)
{
   PrewRelat->Find();
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExportToPDFClick(TObject *Sender)
{
   SendToPDF->FileName = PrewRelat->Report->ReportOptions->Name;
   PrewRelat->Export(SendToPDF);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExportToHtmlClick(TObject *Sender)
{
   SendToHTML->FileName = PrewRelat->Report->ReportOptions->Name;
   PrewRelat->Export(SendToHTML);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExportToXMLClick(TObject *Sender)
{
   SendToXML->FileName = PrewRelat->Report->ReportOptions->Name;
   PrewRelat->Export(SendToXML);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExportToExcelClick(TObject *Sender)
{
   SendToExcel->FileName = PrewRelat->Report->ReportOptions->Name;
   PrewRelat->Export(SendToExcel);
}
//---------------------------------------------------------------------------
void __fastcall TSfgPreview::ExportToTXTClick(TObject *Sender)
{
   SendToTXT->FileName = PrewRelat->Report->ReportOptions->Name;
   PrewRelat->Export(SendToTXT);
}
//---------------------------------------------------------------------------



