//---------------------------------------------------------------------------
#ifndef uSfgToolbarH
#define uSfgToolbarH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Menus.hpp>
#include <ActnList.hpp>
#include <Buttons.hpp>
#include "SfgResButtons.hpp"
#include "uSfgMetaData.h"
#include "uSfgSearch.h"
#include "uSfgBrowse.h"
//---------------------------------------------------------------------------
class SfgWorkEdition;
class PACKAGE TSfgToolbar : public TFrame
{
__published:	// IDE-managed Components
   TResBitBtn *btFirst;
   TResBitBtn *btPrew;
   TResBitBtn *btNext;
   TResBitBtn *btLast;
   TResBitBtn *btSearch;
   TResBitBtn *btGoTo;
   TResBitBtn *btBrowse;
   TResBitBtn *btEdit;
   TResBitBtn *btUndo;
   TResBitBtn *btSave;
   TResBitBtn *btCancel;
   TResBitBtn *btNew;
   TResBitBtn *btCopy;
   TResBitBtn *btDelete;
   TResBitBtn *btExit;
   TResBitBtn *btajuda;
   TPopupMenu *MenuClicks;
   TMenuItem *Primeiro1;
   TMenuItem *Anterior1;
   TMenuItem *Proximo1;
   TMenuItem *Ultimo1;
   TMenuItem *Historico1;
   TMenuItem *VaPara1;
   TMenuItem *Pesquisa1;
   TMenuItem *Editar1;
   TMenuItem *Desfazer1;
   TMenuItem *Salvar1;
   TMenuItem *Cancelar1;
   TMenuItem *Novo1;
   TMenuItem *Copiar1;
   TMenuItem *Excluir1;
	TActionList *ActionList1;
	TAction *execBtFirstClick;
	TAction *execBtPrewClick;
	TAction *execBtNextClick;
	TAction *execBtLastClick;
   TAction *execBtSearchClick;
	TAction *execBtGoToClick;
   TAction *execBtBrowseClick;
	TAction *execBtEditClick;
	TAction *execBtSaveClick;
	TAction *execBtUndoClick;
	TAction *execBtCancelClick;
	TAction *execBtNewClick;
	TAction *execBtDeleteClick;
	TAction *execBtCopyClick;
   TResBitBtn *btExport;
   TAction *execBtExportClick;
   TMenuItem *Exportar1;
   void __fastcall btFirstClick(TObject *Sender);
   void __fastcall btPrewClick(TObject *Sender);
   void __fastcall btNextClick(TObject *Sender);
   void __fastcall btLastClick(TObject *Sender);
   void __fastcall btSearchClick(TObject *Sender);
   void __fastcall btGoToClick(TObject *Sender);
   void __fastcall btEditClick(TObject *Sender);
   void __fastcall btUndoClick(TObject *Sender);
   void __fastcall btSaveClick(TObject *Sender);
   void __fastcall btCancelClick(TObject *Sender);
   void __fastcall btNewClick(TObject *Sender);
   void __fastcall btCopyClick(TObject *Sender);
   void __fastcall btDeleteClick(TObject *Sender);
   void __fastcall btExitClick(TObject *Sender);
   void __fastcall btajudaClick(TObject *Sender);
	void __fastcall btBrowseClick(TObject *Sender);
   void __fastcall btExportClick(TObject *Sender);
private:
   TCustomForm *FParentForm; //Formulário no qual o menu navegação está inserido;
   TDataSource *FDataSource; //Conjunto de registros usados no formulário para navegação (Somente chave primária)
   TDataSet    *FDataSet; //Conjunto de registros usados no formulário para navegação (Somente chave primária)
   TDataSet    *FDataSetWork; //Conjunto de registros usados no formulário para manipulação
	SfgWorkEdition *FWorkEdition; //Trabalha a lista de campos habilitando-os quando necessário
	void __fastcall BotoesRegistro();
	void __fastcall AfterFind();
   void __fastcall BrowseReturn(Variant Value);
   void __fastcall ParserSQLOrigin();
   void __fastcall ParserFromOrigin();
   String __fastcall MontaSQLConsulta();
   void __fastcall LimpaFiltros();
   void __fastcall LimpaOrdenacao();
   void __fastcall ToolbarApplyFilter(TObject *Sender, bool &Sucess);
   void __fastcall ToolbarBeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox);
   void __fastcall ToolbarToExcelGetValue(TField *Field, OleVariant &Value);
	void __fastcall SetDataSource(TDataSource *Value);
	void __fastcall SetFromOrigin(String Value);
   bool __fastcall ActiveDataSet();
   void __fastcall GetComboBoxes();
   void __fastcall LoadSearchProfile();
   void __fastcall ExportToExcel();
	//String __fastcall FieldValueByType(TField *AField, TParameters *AParameters);
	//void __fastcall ReposicionaRegistro(TList *ListKey);
   SfgFilters *FFilters;
   SfgOrders *FOrders;
   String FWhereAdd;
   String FWhereFilter;
   String FOrderByFilter;
   String FSelectOrigin;
   String FFromOrigin;
   String FWhereOrigin;
   String FOrderByOrigin;
   String FSelectColumns;
   TStrings *FFromTables;
   TStrings *FComboBoxes;
   bool FLoadProfile;
public:
   __fastcall TSfgToolbar(TComponent* Owner);
	__fastcall ~TSfgToolbar(void);
	void __fastcall(__closure *ValidDelete) (bool &bValid);
   void __fastcall(__closure *ValidInsert) (bool &bValid);
   void __fastcall(__closure *ValidUpdate) (bool &bValid);
   void __fastcall(__closure *BeforeBrowse) (TStrings *FromTables, String &TableBrowse);
   void __fastcall(__closure *AfterCreateFieldDefs) (TDataSet *DataSet);
   void __fastcall(__closure *AfterCreateFields) (TDataSet *DataSet);
   void __fastcall(__closure *ExportOnGetValue) (TField *Field, OleVariant &Value);
   void __fastcall EnableToolbarButtons(bool bEnable);
   void __fastcall RefreshQuery();
   void __fastcall(__closure *AfterEnableButtons) (bool bEnable);
   String __fastcall ParserSelectColumns(String SQL);
   TfrmSearch *FormSearch;
   TfrmBrowse *FormBrowse;
   __property SfgWorkEdition *WorkEdition = {read=FWorkEdition};
	__property TDataSet *DataSet = {read=FDataSet};
	__property TDataSource *DataSource = {read=FDataSource, write=SetDataSource};
	__property String SelectColumns = {read=FSelectColumns, write=FSelectColumns};
	__property String SelectOrigin = {read=FSelectOrigin, write=FSelectOrigin};
	__property String FromOrigin = {read=FFromOrigin, write=SetFromOrigin};
	__property String WhereOrigin = {read=FWhereOrigin, write=FWhereOrigin};
	__property String OrderByOrigin = {read=FOrderByOrigin, write=FOrderByOrigin};
	__property String WhereFilter = {read=FWhereFilter, write=FWhereFilter};
	__property String OrderByFilter = {read=FOrderByFilter, write=FOrderByFilter};
	__property SfgFilters *Filters = {read=FFilters};
	__property SfgOrders *Orders = {read=FOrders};
   __property Classes::TStrings *FromTables = {read=FFromTables};
	SfgApplyFilter OnApplayFilter;
   SfgBeforeFilterEdit BeforeFilterEdit;
   SfgComboFilterEvent BeforeShowCombo;
   SfgComboFilterEvent AfterChangeCombo;
};
//---------------------------------------------------------------------------
#endif
