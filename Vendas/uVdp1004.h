//---------------------------------------------------------------------------

#ifndef uVdp1004H
#define uVdp1004H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include <CheckLst.hpp>
#include <DBCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <ValEdit.hpp>
#include <DB.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
class TVdp1004 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TGroupBox *GroupBox2;
	TLabel *Label1;
	TComboBox *cbFamilia;
	TAlignEdit *edtQtd;
	TLabel *Label2;
	TButton *btAdd;
	TButton *btRemove;
	TButton *btCancel;
	TButton *btOK;
	TZQuery *QyCnsProduto;
	TListBox *ItensAll;
	TListBox *ItensAdd;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall cbFamiliaChange(TObject *Sender);
	void __fastcall btAddClick(TObject *Sender);
	void __fastcall edtQtdKeyPress(TObject *Sender, char &Key);
	void __fastcall btRemoveClick(TObject *Sender);
	void __fastcall btOKClick(TObject *Sender);
private:	// User declarations
	void __fastcall LimpaItemObjects(TListBox *Lista);
public:		// User declarations
	__fastcall TVdp1004(TComponent* Owner);
	void __fastcall(__closure *OnConfirmList) (TList *ListAdd);
};
//---------------------------------------------------------------------------
#endif
