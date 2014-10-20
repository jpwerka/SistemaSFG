/*
Módulo: Framework SoftGreen
Função: Cadastro Usuários
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFrm1002H
#define uFrm1002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
//---------------------------------------------------------------------------
class TFrm1002 : public TfrmBase02
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TDBEdit *usuario;
	TDBEdit *nome;
	TZQuery *QyCadUsuario;
	TDataSource *DsCadUsuario;
	TLabel *Label3;
	TDBEdit *senha;
	TLabel *Label4;
	TEdit *confirmacao;
	TGroupBox *GroupBox2;
   TDBCheckBox *ies_administrador;
   TGroupBox *GroupBox3;
   TLabel *Label6;
   TDBEdit *email;
   TListBox *ListGrupos;
   TResBitBtn *btSearchGrupo;
   TResBitBtn *btDeleteGrupo;
   TZQuery *QyUsuarioGrupo;
	void __fastcall senhaExit(TObject *Sender);
	void __fastcall confirmacaoExit(TObject *Sender);
	void __fastcall QyCadUsuarioAfterScroll(TDataSet *DataSet);
   void __fastcall btSearchGrupoClick(TObject *Sender);
   void __fastcall NavegbtEditClick(TObject *Sender);
   void __fastcall NavegbtSaveClick(TObject *Sender);
   void __fastcall NavegbtCancelClick(TObject *Sender);
   void __fastcall NavegbtNewClick(TObject *Sender);
   void __fastcall QyCadUsuarioBeforeDelete(TDataSet *DataSet);
   void __fastcall btDeleteGrupoClick(TObject *Sender);
   void __fastcall QyCadUsuarioAfterPost(TDataSet *DataSet);
   void __fastcall QyCadUsuarioBeforePost(TDataSet *DataSet);
   void __fastcall QyCadUsuarioAfterOpen(TDataSet *DataSet);
   void __fastcall QyCadUsuarioBeforeClose(TDataSet *DataSet);
private:	// User declarations
   bool PostStatus;
   void __fastcall ValidInsert(bool &bValid);
   void __fastcall ValidUpdate(bool &bValid);
   void __fastcall ValidDelete(bool &bValid);
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
   void __fastcall HabilitarItens(bool Habilita);
   void __fastcall CarregarGrupos();
	void __fastcall SearchGrupo(Variant Value);
public:		// User declarations
	__fastcall TFrm1002(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
