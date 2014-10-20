//---------------------------------------------------------------------------
#ifndef uSfgSearchH
#define uSfgSearchH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ExtCtrls.hpp>
#include "ZDataset.hpp"
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
#include <ComCtrls.hpp>
#include <Mask.hpp>
#include "SfgAlignGrid.hpp"
#include <Menus.hpp>
#include <ActnList.hpp>
#include "uSfgMetaData.h"
class SfgToolTips;
class TfrmBrowse;

#define SFG_FILTER_BASIC    1
#define SFG_FILTER_ADVANCED 2
#define SFG_ORDER_NONE -1
#define SFG_ORDER_ASC  0
#define SFG_ORDER_DESC 1

#define GRD_BSC_PTR 0
#define GRD_BSC_CMP 1
#define GRD_BSC_CND 2
#define GRD_BSC_VAL 3
#define GRD_ORD_PTR 0
#define GRD_ORD_CMP 1
#define GRD_ORD_ORD 2
#define GRD_ADV_CND 1

typedef struct {
   TField *Field;
   String Operator;
   Variant Value;
   bool Like;
} SfgFilter;

typedef struct {
   TField *Field;
   int Order;
} SfgOrder;

typedef struct {
   SfgFilter *Filter;
   int Group; // (-1) Basico, (>0) Linha Avançado
   String StrAndOr;
} SfgGroupFilter;

typedef TList SfgFilters;
typedef TList SfgOrders;

struct SfgComboObject {
protected:
	Variant Value;
public:
	Variant GetValue() {
		return Value;
	}
	void SetValue(Variant _value) {
		Value = _value;
	}
   SfgComboObject(Variant _value) {
		Value = _value;
   }
};
 
typedef void __fastcall (__closure *SfgApplyFilter)(TObject *Sender, bool &Sucess);
typedef void __fastcall (__closure *SfgBeforeFilterEdit)(SfgFilter *Filter, SfgMfEdit &EditCmp);
typedef void __fastcall (__closure *SfgComboFilterEvent)(SfgFilter *Filter, TCustomComboBox *ComboBox);
//---------------------------------------------------------------------------
class PACKAGE TfrmSearch : public TForm
{
__published:    // IDE-managed Components
   TButton *BtOk;
   TButton *BtCancel;
   TButton *btProfile;
   TPageControl *pgFilter;
   TTabSheet *pgFtBasico;
   TTabSheet *pgFtAvancado;
   TTabSheet *pgFtOrder;
   TStringAlignGrid *grdAvancado;
   TComboBox *cbCondicaoAdv;
   TLabel *Separador;
   TStringAlignGrid *grdBasico;
   TStringAlignGrid *grdOrder;
   TPopupMenu *PopupMenu1;
   TActionList *ActionList1;
   TAction *delLine;
   TComboBox *cbCampoBas;
   TComboBox *cbCondicaoBas;
   TComboBox *cbCampoOrd;
   TComboBox *cbCondicaoOrd;
   TMenuItem *RemoverLinha1;
   TAction *addLine;
   TMenuItem *AdicionarLinha1;
   TMaskEdit *edtValorBas;
   TComboBox *cbValorBas;
   TMemo *StrResultFilter;
   TButton *btAddWhere;
   TButton *btExibe;
   TCheckBox *ckCampoBas;
   void __fastcall cbCampoBasChange(TObject *Sender);
   void __fastcall BtCancelClick(TObject *Sender);
   void __fastcall BtOkClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall edtValorKeyPress(TObject *Sender, char &Key);
   void __fastcall cbCondicaoAdvChange(TObject *Sender);
   void __fastcall grdSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
   void __fastcall LastEditExit(TObject *Sender);
   void __fastcall delLineExecute(TObject *Sender);
   void __fastcall addLineExecute(TObject *Sender);
   void __fastcall grdKeyPress(TObject *Sender, char &Key);
   void __fastcall grdDblClick(TObject *Sender);
   void __fastcall cbCondicaoBasChange(TObject *Sender);
   void __fastcall cbValorBasChange(TObject *Sender);
   void __fastcall edtValorBasChange(TObject *Sender);
   void __fastcall cbCampoOrdChange(TObject *Sender);
   void __fastcall cbCondicaoOrdChange(TObject *Sender);
   void __fastcall grdAvancadoValidateEdit(TObject *Sender, int ACol,
          int ARow, bool &Result);
   void __fastcall btAddWhereClick(TObject *Sender);
   void __fastcall btExibeClick(TObject *Sender);
   void __fastcall ckCampoBasClick(TObject *Sender);
   void __fastcall grdBasicoDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
   void __fastcall btProfileClick(TObject *Sender);
private:
	SfgToolTips *Tolltips;
   SfgFilters *FFilters;
   SfgOrders *FOrders;
   TDataSet *FDataSet;
   String FWhereUser;
   String FWhereSQL;
   String FWhereAdd;
   String FOrderSQL;
   String FOrderUser;
   bool bFloat;
   bool FUseSql;
   int iGrdAdvCnd;
   TWinControl *FLastEditCtr;
   void __fastcall SetDataSet(TDataSet *Value);
   void __fastcall SetFilters(SfgFilters *Value);
   void __fastcall SetOrders(SfgOrders *Value);
   String __fastcall GetWhere();
   int __fastcall GetColumnWidth(TField *Field);
   void __fastcall DelAllObjects();
   void __fastcall AddObjectsGrid(TStringAlignGrid *pGrid, int ARow);
   void __fastcall DelObjectsGrid(TStringAlignGrid *pGrid, int ARow);
   bool __fastcall ValidValue(SfgFilter *Filter, String StrValue, String &StrErro);
   void __fastcall MontaFiltro();
   void __fastcall LimpaFiltros();
   void __fastcall LimpaOrdenacao();
   TfrmBrowse *FFormBrowse;
   void __fastcall OpenBrowse(SfgFilter *Filter);
   void __fastcall BrowseReturn(Variant Value);
   void __fastcall SaveProfile();
   void __fastcall DeleteProfile(String StrKey);
   void __fastcall SaveLineProfile(String StrKey, int Line, String StrProfile);
public:		// User declarations
   TCustomForm *ParentForm;
	__property TDataSet *DataSet = { read=FDataSet, write=SetDataSet };
	__property String Where = {read=GetWhere};
	__property String OrderBy = {read=FOrderSQL};
	__property SfgFilters *Filters = {read=FFilters, write=SetFilters};
	__property String WhereAdd = {read=FWhereAdd, write=FWhereAdd};
	__property SfgOrders *Orders = {read=FOrders, write=SetOrders};
	__fastcall TfrmSearch(TComponent* Owner);
	SfgApplyFilter OnApplayFilter;
   SfgBeforeFilterEdit BeforeFilterEdit;
   SfgComboFilterEvent BeforeShowCombo;
   SfgComboFilterEvent AfterChangeCombo;
};
//---------------------------------------------------------------------------
#endif
