//---------------------------------------------------------------------------
#ifndef uSfgBrowseH
#define uSfgBrowseH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <Grids.hpp>
#include <DBGrids.hpp>
#include <ExtCtrls.hpp>
#include <DBCtrls.hpp>
#include "ZDataset.hpp"
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include <Mask.hpp>

typedef void __fastcall (__closure *SfgBrowseReturn)(Variant Value);
//---------------------------------------------------------------------------
class SfgToolTips;
class PACKAGE TfrmBrowse : public TForm
{
__published:    // IDE-managed Components
	TLabel *LabelCodigo;
   TLabel *LabelOpcoesFiltro;
   TDBGrid *GrdRegistros;
   TZQuery *QyRegistros;
   TDataSource *DsRegistros;
   TButton *BtOk;
   TButton *BtCancel;
   TComboBox *CbOpcFiltro;
   TMaskEdit *edtValor;
   TBevel *Cabecalho;
   TBevel *BottomLine;
   TResBitBtn *btFiltrar;
   TComboBox *cbCondicao;
   void __fastcall CbOpcFiltroChange(TObject *Sender);
   void __fastcall edtValorKeyPress(TObject *Sender, char &Key);
   void __fastcall BtCancelClick(TObject *Sender);
   void __fastcall BtOkClick(TObject *Sender);
   void __fastcall GrdRegistrosDblClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall btFiltrarClick(TObject *Sender);
   void __fastcall GrdRegistrosDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
private:
	SfgToolTips *Tolltips;
   String FSQL;
   TFields *FFieldsKey;
   bool bFloat;
   inline TDataSet* GetDataSet() { return QyRegistros; };
   void __fastcall SetSQL(String Value);
public:		// User declarations
	__fastcall TfrmBrowse(TComponent* Owner);
	__property String SQL = {read=FSQL, write=SetSQL};
	__property TDataSet *DataSet = { read=GetDataSet };
	__property TFields *FieldsKey = {read=FFieldsKey};
	SfgBrowseReturn OnBrowseReturn;
};
//---------------------------------------------------------------------------
extern PACKAGE String GetBrowseSQL(String TableName, TDataSet *Source);
//---------------------------------------------------------------------------
#endif
