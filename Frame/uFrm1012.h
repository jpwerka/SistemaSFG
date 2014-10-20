/*
Módulo: Framework SoftGreen
Função: Processa Atualização Banco de Dados do Sistema
Autor.: Jackson Patrick Werka
Data..: 11/11/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1012H
#define uFrm1012H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgAlignGrid.hpp"
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "uFormBase01.h"
#include "SfgResButtons.hpp"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <ComCtrls.hpp>
#include <msxmldom.hpp>
#include <ActnList.hpp>
//---------------------------------------------------------------------------
class TFrm1012 : public TfrmBase01
{
__published:	// IDE-managed Components
   TStringAlignGrid *AtuDBInsts;
   TXMLDocument *XMLAtuDB;
   TGroupBox *gbCmdSQL;
   TPanel *Panel2;
   TMemo *CmdSQL;
   TPanel *Panel1;
   TEdit *XMLPath;
   TLabel *Label1;
   TButton *btLoadXML;
   TOpenDialog *OpenXML;
   TResBitBtn *btAtualiza;
   TZQuery *QyRegAtuDB;
   TResBitBtn *btProcessar;
   TPanel *pnProgress;
   TLabel *lbInfoMail;
   TProgressBar *ProgressAtuDB;
   TEdit *edtIdent;
   TEdit *edtData;
   TEdit *edtRequisito;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TActionList *ActionList1;
   TAction *execMetadados;
   void __fastcall AtuDBInstsDblClick(TObject *Sender);
   void __fastcall CmdSQLExit(TObject *Sender);
   void __fastcall gbCmdSQLMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall btLoadXMLClick(TObject *Sender);
   void __fastcall btAtualizaClick(TObject *Sender);
   void __fastcall AtuDBInstsDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
   void __fastcall ProcessAtuDB(TObject *Sender);
   void __fastcall btProcessarClick(TObject *Sender);
   void __fastcall execMetadadosExecute(TObject *Sender);
private:	// User declarations
   String sFileAtuDB;
   String sUsuario;
   void __fastcall LimpaGrid();
   bool __fastcall ValidaFileAtuDB();
   static bool __fastcall ExecSqlCreateDB();
   bool __fastcall ExecSqlInstruction(String sCmdSQL, int iCmdSeq);
   void __fastcall RegisterExecution(String sAtuDBAction, String sAtuDBType,
      String sAtuDBObject, String sAtuDBSubAction, String sAtuDBSubType,
      String sAtuDBSubObject, String sAtuDBInfo);
public:		// User declarations
   __fastcall TFrm1012(TComponent* Owner);
   static bool __fastcall CreateDataBase();
};
//---------------------------------------------------------------------------
#endif
