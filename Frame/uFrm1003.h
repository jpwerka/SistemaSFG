/*
Módulo: Framework SoftGreen
Função: Alteração Senha Usuário
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1003H
#define uFrm1003H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
//---------------------------------------------------------------------------
class TFrm1003 : public TfrmBase01
{
__published:	// IDE-managed Components
	TBevel *Bevel2;
   TLabel *Label1;
   TEdit *Senha;
   TLabel *Label2;
   TEdit *CfSenha;
   TLabel *Label3;
   TEdit *NvSenha;
   TPanel *SfgToolbar;
   TResBitBtn *btConfirmar;
   TResBitBtn *btCancelar;
   void __fastcall btConfirmarClick(TObject *Sender);
   void __fastcall btCancelarClick(TObject *Sender);
private:	// User declarations
   SfgToolTips *Tolltips;
   bool __fastcall SenhaValida();
public:		// User declarations
   __fastcall TFrm1003(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
 