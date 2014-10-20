//---------------------------------------------------------------------------

#ifndef uFrm1010H
#define uFrm1010H
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
#include "CustomDbControls.h"
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
#include <Grids.hpp>
#include "SfgAlignGrid.hpp"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
//---------------------------------------------------------------------------
struct SfgMenuInfo {
	String cod_rotina;
};

class SfgWorkEdition;
class TFrm1010 : public TfrmBase01
{
__published:	// IDE-managed Components
   TPanel *Panel1;
   TSplitter *Splitter1;
   TTreeView *TreeMenu;
   TPanel *Panel2;
   TPanel *Panel4;
   TLabel *Label1;
   TLabel *Label2;
   TLabel *Label3;
   TLabel *Label4;
   TPanel *Panel3;
   TBevel *Bevel2;
   TResBitBtn *btEdit;
   TResBitBtn *btSave;
   TResBitBtn *btCancel;
   TResBitBtn *btAddChild;
   TResBitBtn *btAddItem;
   TResBitBtn *btDelete;
   TResBitBtn *btExit;
   TComboBoxEx *ico_index;
   TLabel *Label5;
   TPopupMenu *PopupMenu1;
   TMenuItem *Adicionarfilho1;
   TMenuItem *Adicionarfilho2;
   TMenuItem *Editar1;
   TMenuItem *Salvar1;
   TMenuItem *Cancelar1;
   TMenuItem *Excluir1;
   TActionList *ActionList1;
   TAction *execBtAddItem;
   TAction *execBtAddChild;
   TAction *execBtEdit;
   TAction *execBtSave;
   TAction *execBtCancel;
   TAction *execBtDelete;
   TDataSource *DsMenu;
   TZTable *CadMenu;
   TStringField *CadMenucod_rotina;
   TStringField *CadMenuden_rotina;
   TStringField *CadMenuprograma;
   TStringField *CadMenucod_rotina_pai;
   TSmallintField *CadMenuord_rotina;
   TSmallintField *CadMenuico_index;
   TDBEdit *cod_rotina;
   TDBEdit *den_rotina;
   TDBEdit *cod_rotina_pai;
   TDBEdit *programa;
   TImageList *ImageList1;
   TResBitBtn *btSearchForm;
   TDBEdit *ord_rotina;
   TLabel *Label6;
   TResBitBtn *btMenuPadrao;
   TAction *execBtPadrao;
   TMenuItem *CarregarMenuPadro1;
   TSmallintField *CadMenumodulo;
   TLabel *Label7;
   TDBDataComboBox *modulo;
   TAction *execSaveMenu;
   TXMLDocument *XMLLoadMenu;
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall TreeMenuChange(TObject *Sender, TTreeNode *Node);
   void __fastcall TreeMenuChanging(TObject *Sender, TTreeNode *Node,
          bool &AllowChange);
   void __fastcall execBtAddItemExecute(TObject *Sender);
   void __fastcall execBtAddChildExecute(TObject *Sender);
   void __fastcall execBtEditExecute(TObject *Sender);
   void __fastcall execBtSaveExecute(TObject *Sender);
   void __fastcall execBtCancelExecute(TObject *Sender);
   void __fastcall execBtDeleteExecute(TObject *Sender);
   void __fastcall btExitClick(TObject *Sender);
   void __fastcall ico_indexChange(TObject *Sender);
   void __fastcall grdAppFormsDblClick(TObject *Sender);
   void __fastcall btSearchFormClick(TObject *Sender);
   void __fastcall execBtPadraoExecute(TObject *Sender);
   void __fastcall execSaveMenuExecute(TObject *Sender);
private:	// User declarations
   void __fastcall CarregaMenu(TTreeNode *pParentItem);
	void __fastcall HabilitarItens(bool Habilita);
	SfgWorkEdition *pWorkEdition; //Trabalha a lista de campos habilitando-os quando necessário
   bool __fastcall VerificaCampos();
	bool __fastcall ValidaCampos();
	void __fastcall FreeTreeNodes(TTreeNode *Parent, int Level);
   void __fastcall ShowAppForms();
   void __fastcall CarregarModulos();
   void __fastcall SaveMenuToXml();
public:		// User declarations
   __fastcall TFrm1010(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
