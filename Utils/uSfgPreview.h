//---------------------------------------------------------------------------
#ifndef uSfgPreviewH
#define uSfgPreviewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <BandActn.hpp>
#include <Dialogs.hpp>
#include "frxClass.hpp"
#include "frxPreview.hpp"
#include "frxExportMail.hpp"
#include "frxExportPDF.hpp"
#include "frxExportXLS.hpp"
#include "frxExportHTML.hpp"
#include "frxExportXML.hpp"
#include "frxExportText.hpp"
#include <ExtCtrls.hpp>
class SfgToolTips;
//---------------------------------------------------------------------------
class PACKAGE TSfgPreview : public TForm
{
__published:	// IDE-managed Components
        TToolBar *BarraBotoes;
        TToolButton *ToolButton1;
        TImageList *Habilitadas;
   TPopupMenu *PrewPopup;
        TToolButton *ToolButton2;
        TToolButton *ToolButton3;
        TToolButton *ToolButton4;
        TToolButton *ToolButton5;
        TActionList *ActionList1;
        TAction *Imprimir;
        TMenuItem *Imprimir1;
        TAction *ZoomMais;
        TAction *ZoomMenos;
        TToolButton *ToolButton6;
        TToolButton *ToolButton7;
        TMenuItem *ZoomMais1;
        TMenuItem *ZoomMenos1;
        TComboBox *CbZoom;
        TAction *NextPage;
        TMenuItem *PrximaPgina1;
        TAction *PrewPage;
        TMenuItem *PginaAnterior1;
        TToolButton *ToolButton8;
        TToolButton *ToolButton9;
        TToolButton *ToolButton10;
        TAction *Ajustar;
        TMenuItem *AjustaraPgina1;
        TAction *LastPage;
        TAction *FirstPage;
        TAction *SetupPrinter;
        TToolButton *ToolButton11;
        TToolButton *ToolButton12;
        TToolButton *ToolButton13;
        TToolButton *ToolButton14;
        TAction *Ajustarlarg;
        TAction *AjustarReal;
        TMenuItem *AjustaraLargura1;
        TMenuItem *AjustarReal1;
        TMenuItem *PrimeiraPgina1;
        TMenuItem *UltimaPgina1;
        TAction *Salvar;
        TAction *Abrir;
	TToolButton *ToolButton15;
	TAction *Exit;
   TfrxPreview *PrewRelat;
   TToolButton *ExportMenu;
   TToolButton *ToolButton17;
   TToolButton *ToolButton18;
   TToolButton *ThumbB;
   TfrxXLSExport *SendToExcel;
   TfrxPDFExport *SendToPDF;
   TfrxHTMLExport *SendToHTML;
   TAction *FindText;
   TPopupMenu *ExportPopup;
   TMenuItem *LocalizarTexto1;
   TToolButton *ToolButton19;
   TToolButton *ToolButton20;
   TMenuItem *ExportToPDF;
   TMenuItem *ExportToHtml;
   TfrxXMLExport *SendToXML;
   TMenuItem *ExportToXML;
   TMenuItem *ExportToExcel;
   TfrxSimpleTextExport *SendToTXT;
   TMenuItem *ExportToTXT;
   TfrxMailExport *SendByMail;
   TStatusBar *BarraStatus;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall ImprimirExecute(TObject *Sender);
        void __fastcall ZoomMaisExecute(TObject *Sender);
        void __fastcall ZoomMenosExecute(TObject *Sender);
        void __fastcall NextPageExecute(TObject *Sender);
        void __fastcall PrewPageExecute(TObject *Sender);
        void __fastcall AjustarExecute(TObject *Sender);
        void __fastcall SetupPrinterExecute(TObject *Sender);
        void __fastcall FirstPageExecute(TObject *Sender);
        void __fastcall LastPageExecute(TObject *Sender);
        void __fastcall AjustarlargExecute(TObject *Sender);
        void __fastcall AjustarRealExecute(TObject *Sender);
        void __fastcall CbZoomClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall CbZoomKeyPress(TObject *Sender, char &Key);
        void __fastcall SalvarExecute(TObject *Sender);
        void __fastcall AbrirExecute(TObject *Sender);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
	void __fastcall ExitExecute(TObject *Sender);
   void __fastcall PrewRelatPageChanged(TfrxPreview *Sender, int PageNo);
   void __fastcall ToolButton17Click(TObject *Sender);
   void __fastcall ThumbBClick(TObject *Sender);
   void __fastcall FindTextExecute(TObject *Sender);
   void __fastcall ExportToPDFClick(TObject *Sender);
   void __fastcall ExportToHtmlClick(TObject *Sender);
   void __fastcall ExportToXMLClick(TObject *Sender);
   void __fastcall ExportToExcelClick(TObject *Sender);
   void __fastcall ExportToTXTClick(TObject *Sender);
private:
        void __fastcall PaginaInfo();
		  SfgToolTips* Tolltips;
public:		// User declarations
        __fastcall TSfgPreview(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
