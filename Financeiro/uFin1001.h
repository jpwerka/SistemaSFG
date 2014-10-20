/*
Módulo: Financeiro
Função: Cadastro Plano de Contas
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin1001H
#define uFin1001H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "SfgResButtons.hpp"
#include <Menus.hpp>
#include <ActnList.hpp>
#include "ZStoredProcedure.hpp"
#include "CustomButtons.h"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class SfgWorkEdition;
class TFin1001 : public TfrmBase01
{
__published:	// IDE-managed Components
	TTreeView *TreeContas;
	TZTable *PlanoConta;
	TStringField *PlanoContacod_plano_conta;
	TStringField *PlanoContacod_plano_conta_reduz;
	TStringField *PlanoContaden_plano_conta;
	TStringField *PlanoContatipo_plano_conta;
	TStringField *PlanoContacod_plano_conta_pai;
	TStringField *PlanoContaies_ativo;
	TDateTimeField *PlanoContadata_cadastro;
	TDataSource *DsPlanoConta;
	TPanel *Panel2;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label6;
	TDBEdit *cod_plano_conta;
	TDBEdit *cod_plano_conta_reduz;
	TDBEdit *den_plano_conta;
	TDBCheckBox *ies_ativo;
	TDBRadioGroup *tipo_plano_conta;
	TDBEdit *data_cadastro;
	TCustomImgButton *btCalendar02;
	TPanel *Panel4;
	TLabel *Label4;
	TDBEdit *cod_plano_conta_pai;
	TPanel *Panel1;
	TResBitBtn *btEdit;
	TResBitBtn *btSave;
	TResBitBtn *btCancel;
	TBevel *Bevel2;
	TResBitBtn *btAddChild;
	TResBitBtn *btAddItem;
	TResBitBtn *btDelete;
	TResBitBtn *btExit;
	TPopupMenu *PopupMenu1;
	TActionList *ActionList1;
	TAction *execBtAddItem;
	TAction *execBtAddChild;
	TAction *execBtEdit;
	TAction *execBtSave;
	TAction *execBtCancel;
	TAction *execBtDelete;
	TMenuItem *Adicionarfilho1;
	TMenuItem *Adicionarfilho2;
	TMenuItem *Editar1;
	TMenuItem *Salvar1;
	TMenuItem *Cancelar1;
	TMenuItem *Excluir1;
	TZReadOnlyQuery *CanDelete;
	TIntegerField *CanDeletecan_delete;
	TZQuery *DelPlanoConta;
	TSplitter *Splitter1;
   TLabel *Label5;
	void __fastcall TreeContasChange(TObject *Sender, TTreeNode *Node);
	void __fastcall btEditClick(TObject *Sender);
	void __fastcall btSaveClick(TObject *Sender);
	void __fastcall btCancelClick(TObject *Sender);
	void __fastcall btAddItemClick(TObject *Sender);
	void __fastcall btAddChildClick(TObject *Sender);
	void __fastcall btDeleteClick(TObject *Sender);
	void __fastcall TreeContasChanging(TObject *Sender, TTreeNode *Node,
			 bool &AllowChange);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	void __fastcall CarregaPlanoContas(TTreeNode *pParentItem);
	void __fastcall HabilitarItens(bool Habilita);
	SfgWorkEdition *pWorkEdition; //Trabalha a lista de campos habilitando-os quando necessário
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	void __fastcall FreeTreeNodes(TTreeNode *Parent, int Level);
public:		// User declarations
	__fastcall TFin1001(TComponent* Owner);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
