/*
Módulo: Framework SoftGreen
Função: Configurações Sistema
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1005H
#define uFrm1005H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <ExtDlgs.hpp>
#include <Buttons.hpp>
#include "SfgAlignEdit.hpp"
#include "SfgResButtons.hpp"
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrm1005 : public TfrmBase01
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TResBitBtn *btConfirmar;
	TResBitBtn *btCancelar;
   TGroupBox *gbCodigos;
   TEdit *PreCli;
   TEdit *PreFor;
	TLabel *Label5;
	TLabel *Label4;
	TBevel *Bevel2;
   TEdit *ZeroCli;
   TLabel *Label2;
   TLabel *Label3;
   TAlignEdit *ProxCli;
   TAlignEdit *ProxFor;
   TEdit *PreRep;
   TAlignEdit *ProxRep;
   TLabel *Label6;
   TLabel *CheckBox1;
   TLabel *Label7;
   TLabel *ExeCodCli;
   TLabel *ExeCodFor;
   TLabel *ExeCodRep;
   TBevel *Bevel3;
   TEdit *ZeroFor;
   TEdit *ZeroRep;
   TUpDown *UpDownCli;
   TUpDown *UpDownFor;
   TUpDown *UpDownRep;
   TLabel *Label8;
   TCheckBox *CodAutoFor;
   TCheckBox *CodAutoRep;
   TLabel *Label9;
   TCheckBox *CodAutoCid;
   TCheckBox *CodAutoCli;
   TEdit *PreCid;
   TAlignEdit *ProxCid;
   TEdit *ZeroCid;
   TUpDown *UpDownCid;
   TLabel *ExeCodCid;
   void __fastcall btConfirmarClick(TObject *Sender);
   void __fastcall btCancelarClick(TObject *Sender);
   void __fastcall ClienteExit(TObject *Sender);
   void __fastcall FornecedorExit(TObject *Sender);
   void __fastcall RepresentaExit(TObject *Sender);
   void __fastcall CidadeExit(TObject *Sender);
   void __fastcall CodAutoCliClick(TObject *Sender);
   void __fastcall CodAutoForClick(TObject *Sender);
   void __fastcall CodAutoRepClick(TObject *Sender);
   void __fastcall CodAutoCidClick(TObject *Sender);
   void __fastcall UpDownCliClick(TObject *Sender, TUDBtnType Button);
   void __fastcall UpDownForClick(TObject *Sender, TUDBtnType Button);
   void __fastcall UpDownRepClick(TObject *Sender, TUDBtnType Button);
   void __fastcall UpDownCidClick(TObject *Sender, TUDBtnType Button);
private:	// User declarations
   void __fastcall CarregaParam();
   void __fastcall EnableFields(bool bEnable, int iGrupo);
public:		// User declarations
	__fastcall TFrm1005(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
