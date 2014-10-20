//---------------------------------------------------------------------------

#ifndef uFrm1011H
#define uFrm1011H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZAbstractTable.hpp"
#include "ZDataset.hpp"
#include <ActnList.hpp>
#include <DB.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include "SfgAlignGrid.hpp"
#include <Grids.hpp>
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
//---------------------------------------------------------------------------
struct SfgMenuInfo {
	String cod_rotina;
};

class SfgWorkEdition;
class TFrm1011 : public TfrmBase01
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TSplitter *Splitter1;
   TTreeView *TreeMenu;
   TPanel *Panel2;
   TPanel *Panel4;
   TLabel *Label2;
   TPanel *Panel3;
   TBevel *Bevel2;
   TResBitBtn *btPesquisa;
   TResBitBtn *btDelete;
   TResBitBtn *btExit;
   TPopupMenu *PopupMenu1;
   TMenuItem *Adicionarfilho1;
   TActionList *ActionList1;
   TAction *execBtPesquisa;
   TEdit *denominacao;
   TEdit *usuario_grupo;
   TRadioGroup *permissao_por;
   TAction *execBtDelete;
   TMenuItem *Excluirtodasaspermisses1;
   TZQuery *PermissaoMenu;
   TZQuery *DeletePermissao;
   TImageList *ImageList2;
   TPopupMenu *menu_tree;
   TMenuItem *sem_permissao;
   TMenuItem *somente_leitura;
   TMenuItem *permissao_total;
   TMenuItem *somente_leitura_g;
   TMenuItem *permissao_total_g;
   TZQuery *ModificaPermissao;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall execBtPesquisaExecute(TObject *Sender);
   void __fastcall execBtDeleteExecute(TObject *Sender);
   void __fastcall btExitClick(TObject *Sender);
   void __fastcall TreeMenuMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall sem_permissaoClick(TObject *Sender);
   void __fastcall somente_leituraClick(TObject *Sender);
   void __fastcall permissao_totalClick(TObject *Sender);
private:	// User declarations
   void __fastcall CarregaMenu(TTreeNode *pParentItem);
	void __fastcall FreeTreeNodes(TTreeNode *Parent, int Level);
	void __fastcall SearchReturn(Variant Value);
	void __fastcall AlterarPermissao(TTreeNode *Parent, int Level, int nivel_permissao);
public:		// User declarations
   __fastcall TFrm1011(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
