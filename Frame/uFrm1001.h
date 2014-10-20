/*
Módulo: Framework SoftGreen
Função: Configurações Sistema
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1001H
#define uFrm1001H
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
//---------------------------------------------------------------------------
class TFrm1001 : public TfrmBase01
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label3;
	TOpenPictureDialog *OpenPicture;
	TResBitBtn *btConfirmar;
	TResBitBtn *btCancelar;
	TGroupBox *gbRodRelatorio;
	TEdit *edtCidade;
	TAlignEdit *Edit1;
	TAlignEdit *Edit2;
	TAlignEdit *edtRodLivre01;
	TAlignEdit *edtRodLivre02;
	TGroupBox *gbImagens;
	TGroupBox *gbServerMail;
	TButton *btMarcaDagua;
	TButton *btLogotipo;
	TButton *btDelLogotipo;
	TButton *btDelMarcaDagua;
	TEdit *LogotipoPath;
	TEdit *MarcaDaguaPath;
	TLabel *Label5;
	TLabel *Label4;
	TImage *MarcaDagua;
	TLabel *Label2;
	TEdit *ServerEmail;
	TLabel *Label6;
	TEdit *PortaServerEmail;
	TCheckBox *RequerAutenticacao;
	TCheckBox *ConexaoSegura;
	TBevel *Bevel2;
	TGroupBox *gbCabRelatorio;
	TEdit *edtCabLivre01;
	TEdit *edtCabLivre02;
	TImage *RelatLogotipo;
	TEdit *edtCabLivre03;
	TLabel *Label7;
	void __fastcall btLogotipoClick(TObject *Sender);
	void __fastcall btMarcaDaguaClick(TObject *Sender);
	void __fastcall btDelLogotipoClick(TObject *Sender);
	void __fastcall btDelMarcaDaguaClick(TObject *Sender);
	void __fastcall btConfirmarClick(TObject *Sender);
	void __fastcall btCancelarClick(TObject *Sender);
	void __fastcall edtRodLivre01Enter(TObject *Sender);
	void __fastcall edtRodLivre01Exit(TObject *Sender);
	void __fastcall edtRodLivre02Enter(TObject *Sender);
	void __fastcall edtRodLivre02Exit(TObject *Sender);
	void __fastcall edtCidadeEnter(TObject *Sender);
	void __fastcall edtCidadeExit(TObject *Sender);
	void __fastcall edtCabLivre01Enter(TObject *Sender);
	void __fastcall edtCabLivre01Exit(TObject *Sender);
	void __fastcall edtCabLivre02Enter(TObject *Sender);
	void __fastcall edtCabLivre02Exit(TObject *Sender);
	void __fastcall edtCabLivre03Enter(TObject *Sender);
	void __fastcall edtCabLivre03Exit(TObject *Sender);
   void __fastcall LogotipoPathExit(TObject *Sender);
   void __fastcall MarcaDaguaPathExit(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrm1001(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
