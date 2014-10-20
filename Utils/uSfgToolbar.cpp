//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgWorkEdition.h"
#include "uSfgVaPara.h"
#include "uDataModule.h"
#include <ZDataset.hpp>
#include "parsesql.h"
#include "CustomDbControls.h"
#pragma hdrstop
#include "uSfgToolbar.h"
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSfgToolbar::TSfgToolbar(TComponent* Owner)
        : TFrame(Owner)
{
	FParentForm = (TCustomForm*)Owner;
   FormBrowse = NULL;
   FormSearch = NULL;
   AfterEnableButtons = NULL;
	this->OnApplayFilter = NULL;
   this->BeforeFilterEdit = NULL;
   this->BeforeShowCombo = NULL;
   this->AfterChangeCombo = NULL;
   this->AfterCreateFieldDefs = NULL;
   this->AfterCreateFields = NULL;
   this->ExportOnGetValue = NULL;
   this->FWhereAdd = "";
   this->FFilters = NULL;
   this->FOrders = NULL;
   this->FFromTables = NULL;
   this->FComboBoxes = NULL;
   this->FLoadProfile = false;
}
//---------------------------------------------------------------------------
__fastcall TSfgToolbar::~TSfgToolbar(void)
{
   if (FComboBoxes != NULL) {
      FComboBoxes->Clear();
      delete FComboBoxes;
   }
   delete(FWorkEdition);
   LimpaFiltros();
   LimpaOrdenacao();
   if (FFromTables != NULL) {
      FFromTables->Clear();
      delete FFromTables;
   }
}
//---------------------------------------------------------------------------
/**************************************************
 AQUI COMEÇA OS EVENTOS CLICK DOS BOTÕES DE COMANDO
**************************************************/
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btFirstClick(TObject *Sender)
{
try {
   FDataSet->First();
	execBtFirstClick->Enabled = false;
	execBtPrewClick->Enabled = false;
	execBtNextClick->Enabled = true;
	execBtLastClick->Enabled = true;
}
catch(...) {
   MessageBox(Handle,"Erro ao mover para o primeiro registro!",
             "Mensagem de Erro",APP_ERROR);
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btPrewClick(TObject *Sender)
{
try {
   FDataSet->Prior();
   BotoesRegistro();
}
catch(...){
  MessageBox(Handle,"Erro ao mover para o registro anterior!",
             "Mensagem de Erro",APP_ERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btNextClick(TObject *Sender)
{
try {
   FDataSet->Next();
   BotoesRegistro();
}
catch(...){
  MessageBox(Handle,"Erro ao mover para o próximo registro!",
             "Mensagem de Erro", APP_ERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btLastClick(TObject *Sender)
{
try {
   FDataSet->Last();
	execBtFirstClick->Enabled = true;
	execBtPrewClick->Enabled = true;
	execBtNextClick->Enabled = false;
	execBtLastClick->Enabled = false;
}
catch(...){
  MessageBox(Handle,"Erro ao mover para o último registro!",
             "Mensagem de Erro",APP_ERROR);
  }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btGoToClick(TObject *Sender)
{
   if (!FDataSet->Active) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
   if (FDataSet->RecordCount == 0) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
   SfgVaPara = new TSfgVaPara(this);
   SfgVaPara->DataSet = FDataSetWork;
   SfgVaPara->AfterGoToFind = &AfterFind;
   SfgVaPara->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::AfterFind() {
   BotoesRegistro();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btSearchClick(TObject *Sender)
{
   if (!FLoadProfile) {
      LoadSearchProfile();
      FLoadProfile = true;
   }
   FormSearch = new TfrmSearch(Application);
   FormSearch->DataSet = this->FDataSetWork;
   FormSearch->WhereAdd = this->FWhereAdd;
   FormSearch->Filters = this->FFilters;
   FormSearch->Orders = this->FOrders;
   FormSearch->ParentForm = this->FParentForm;
   FormSearch->OnApplayFilter = &ToolbarApplyFilter;
   FormSearch->BeforeFilterEdit = this->BeforeFilterEdit;
   FormSearch->BeforeShowCombo = &ToolbarBeforeShowCombo;
   FormSearch->AfterChangeCombo = this->AfterChangeCombo;
   FormSearch->ShowModal();
   this->FFilters = FormSearch->Filters;
   this->FOrders = FormSearch->Orders;
   delete FormSearch;
   FormSearch = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btBrowseClick(TObject *Sender)
{
   TField *Field;
   TSfgFieldDef *FieldDef;
   TSfgMetaField *MetaField = NULL;
   FormBrowse = new TfrmBrowse(Application);
   String sSelect, sFrom, sOrder;
   String TableName = "";
   if (FFromTables != NULL && FFromTables->Count > 0)
      TableName = FFromTables->Strings[0];
   if(BeforeBrowse != NULL) {
      BeforeBrowse(FFromTables, TableName);
   }

   sSelect = "";
   sFrom = "FROM " + TableName;
   sOrder = "";
   //Montando o SELECT a ser utilizado no BROWSE
   for(int i = 0; i < FDataSetWork->FieldCount; i++) {
      Field = FDataSetWork->Fields->Fields[i];
      MetaField = NULL;
      if (Field->Tag > 0)
         MetaField = (TSfgMetaField*)Field->Tag;
      if (MetaField == NULL)
         continue;

      if ((MetaField->IsPkKey) || (MetaField->IsBrowse)) {
         FieldDef = CopyFieldDef(Field,FormBrowse->DataSet);
         FieldDef->IsPkKey = MetaField->IsPkKey;
         if (!(MetaField->IsBrowse))
            FieldDef->Visible = false;
         if (sSelect.Length() > 0) {
            sSelect += "," + Field->FieldName;
         } else {
            sSelect = "SELECT " + Field->FieldName;
         }
         if (MetaField->Order.InBrowse) {
            if (sOrder.Length() > 0) {
               sOrder += "," + Field->FieldName;
            } else {
               sOrder = "ORDER BY " + Field->FieldName;
            }
         }
      }
   }
   CreateFields(FormBrowse->DataSet);
   FormBrowse->SQL = sSelect + " " + sFrom + " " + sOrder;
   FormBrowse->OnBrowseReturn = &BrowseReturn;
   FormBrowse->ShowModal();
   delete FormBrowse;
   FormBrowse = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btEditClick(TObject *Sender)
{
   if (!FDataSetWork->Active) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
   if (FDataSetWork->RecordCount == 0) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
try {
   EnableToolbarButtons(false);
   FDataSetWork->Edit();
	FWorkEdition->SetWorkEdition(true,false,AppConfig->Colors->Enabled);
}
catch(Exception &e){
   String Msg = "Ocorreu o seguinte erro ao editar as informações do item:\n";
   Msg = Msg + e.Message;
   MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btUndoClick(TObject *Sender)
{
   FDataSetWork->Cancel();
   FDataSetWork->Edit();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btSaveClick(TObject *Sender)
{
	bool bValid = true;
	if (FDataSetWork->State == dsInsert) {
      if (ValidInsert != NULL)
         ValidInsert(bValid);
   } else if (FDataSetWork->State == dsEdit) {
      if (ValidUpdate != NULL)
         ValidUpdate(bValid);
   } else { //Não está no modo edição nem inserção
      bValid = false;
   }
   if (!bValid)
      return;
   try {
		try {
			FDataSetWork->Post();
		}
		catch(Exception &e) {
			String Msg = "Ocorreu o seguinte erro ao salvar informações do registro:\n";
			Msg = Msg + e.Message;
			MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
		}
	}
	__finally{
		btCancel->Click();
	}
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btCancelClick(TObject *Sender)
{
	EnableToolbarButtons(true);
	FWorkEdition->SetWorkEdition(false, true, AppConfig->Colors->Disabled);
	FDataSetWork->Cancel();
	if(btSearch->Visible)
		btSearch->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btNewClick(TObject *Sender)
{
   //Se não estiver ativo o DataSet deve ativar o mesmo
   if (!FDataSet->Active) {
      FWhereFilter = "1=0";
      FOrderByFilter = "";
      if (!ActiveDataSet()) {
         return;
      }
   }

try {
   EnableToolbarButtons(false);
   FDataSetWork->Insert();
	FWorkEdition->SetWorkEdition(true, true, AppConfig->Colors->Enabled);
	execBtUndoClick->Enabled = false;
	}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao criar novo registro:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btCopyClick(TObject *Sender)
{
   if (!FDataSetWork->Active) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
   if (FDataSetWork->RecordCount == 0) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }

try {
   int i;
   EnableToolbarButtons(false);
   int Bounds[2] = {0,FDataSetWork->FieldCount -1};
   Variant Valores = VarArrayCreate(Bounds,1, varVariant);
   for(i=0; i < FDataSetWork->FieldCount; i++)
      Valores.PutElement(FDataSetWork->Fields->Fields[i]->Value,i);
   FDataSetWork->Insert();
   for(i=0; i < FDataSetWork->FieldCount; i++)
      FDataSetWork->Fields->Fields[i]->Value = Valores.GetElement(i);
   execBtUndoClick->Enabled = false;
	FWorkEdition->SetWorkEdition(true, true, AppConfig->Colors->Enabled);
}
catch(Exception &e) {
   String Msg = "Ocorreu o seguinte erro ao copiar dados do registro:\n";
   Msg = Msg + e.Message;
   MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btDeleteClick(TObject *Sender)
{
   if (!FDataSetWork->Active) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }
   if (FDataSetWork->RecordCount == 0) {
      MessageBox(Handle,"Não existe nenhuma consulta ativa!", FParentForm->Caption.c_str(),APP_INFORM);
      return;
   }

   bool bValid = true;
   if (ValidDelete != NULL)
      ValidDelete(bValid);
   if (!bValid)
      return;
   if (MessageBox(Handle,"Deseja Excluir o Registro Atual?\n"
      "Após a exclusão não será possível recuperar cadastro!",
      "Excluir",APP_QUESTION | MB_DEFBUTTON2) == IDNO)
      return;
   try {
      FDataSetWork->Delete();
   }
   catch(Exception &e) {
      String Msg = "Ocorreu o seguinte erro ao excluir o registro:\n";
      Msg = Msg + e.Message;
      MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btExportClick(TObject *Sender)
{
   ExportToExcel();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btExitClick(TObject *Sender)
{
   FParentForm->Close();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::btajudaClick(TObject *Sender)
{
/*  HANDLE Ret;
  String Msg;
  String Arquivo;
  Arquivo = ExtractFilePath(Application->ExeName) + "ajuda\\" + btajuda->HelpKeyword + ".pdf";
  //ShowMessage(btajuda->HelpKeyword);
//Método para abrir a ajuda
  if(FileExists(Arquivo)){
    Ret = ShellExecute(Handle,"open",Arquivo.c_str(),NULL,NULL,SW_SHOW);
    if(int(Ret) <= 32){
      Msg = "Erro ao mostrar a ajuda!\nVerifique o seguinte arquivo:\n";
      Msg = Msg + Arquivo;
      MessageBox(Handle,Msg.c_str(),"Mensagem de Erro", APP_ERROR);
    }
  }else{
      Msg = "Não foi possível encontrar o arquivo de ajuda!\n";
      Msg = Msg + Arquivo;
      MessageBox(Handle,Msg.c_str(),FParentForm->Caption.c_str(), APP_INFORM);
  }*/
}
//---------------------------------------------------------------------------
/***************************************************
 AQUI TERMINA OS EVENTOS CLICK DOS BOTÕES DE COMANDO
***************************************************/
//---------------------------------------------------------------------------
//Indica qual o DataSource que que faz referência ao menu de navegação
void __fastcall TSfgToolbar::SetDataSource(TDataSource *Value)
{
   FDataSource = Value;
   this->FDataSetWork = FDataSource->DataSet;
   if (this->FDataSetWork->DataSource != NULL) {
      this->FDataSet = this->FDataSetWork->DataSource->DataSet;
      //this->FDataSet->Active = true;
   }
   else {
		this->FDataSet = this->FDataSetWork;
   }
   //this->FDataSetWork->Active = true;
   LimpaFiltros();
   LimpaOrdenacao();
   ParserSQLOrigin();
   //Se encontrou a tabela e a listagem de campos deve criar os campos dos DataSet
   if (FFromTables->Count == 1) {
      TSfgMetaTable *MetaTable = AddMetaTable(FFromTables->Strings[0]);
      if (FSelectColumns.Length() > 0 && FDataSetWork->Fields->Count == 0) {
         CreateFieldDefs(MetaTable, FSelectColumns, FDataSetWork);
         if (AfterCreateFieldDefs != NULL)
            AfterCreateFieldDefs(FDataSetWork);
         CreateFields(FDataSetWork);
         if (AfterCreateFields != NULL)
            AfterCreateFields(FDataSetWork);
      } else {
         //Se já existem os campos previamente criados, tenta associar com a tabela
         TSfgMetaField *MetaField = NULL;
         TField *Field = NULL;
         for (int i = 0; i < FDataSetWork->Fields->Count; i++) {
            Field = FDataSetWork->Fields->Fields[i];
            MetaField = MetaTable->Find(Field->FieldName);
            if (MetaField != NULL)
               Field->Tag = (int)MetaField;
         }
      }
   }
	FWorkEdition = new SfgWorkEdition(FDataSource,FParentForm);
	FWorkEdition->SetWorkEdition(false,true,AppConfig->Colors->Disabled);
   GetComboBoxes();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::BotoesRegistro()
{
  bool HabPrew, HabNext, HabTwo;
  HabPrew = HabNext = HabTwo = false;
  HabPrew = bool(FDataSet->RecNo > 1);
  HabNext = bool(FDataSet->RecNo < FDataSet->RecordCount);
  HabTwo = bool(HabPrew && HabNext);
  if(!HabTwo){
	  execBtFirstClick->Enabled = HabPrew;
	  execBtPrewClick->Enabled = HabPrew;
	  execBtNextClick->Enabled = HabNext;
	  execBtLastClick->Enabled = HabNext;
  }
  else{
	  execBtFirstClick->Enabled = HabTwo;
	  execBtPrewClick->Enabled = HabTwo;
	  execBtNextClick->Enabled = HabTwo;
	  execBtLastClick->Enabled = HabTwo;
  }
}
//---------------------------------------------------------------------------
//procedimento para desabilitar\habilitar navegação
void __fastcall TSfgToolbar::EnableToolbarButtons(bool Enable)
{
   TButton *Button;
   TControl *Control;

   for (int i=0; i<this->ControlCount; i++) {
   try {
      Control = this->Controls[i];
      if(Control == NULL)
         continue;
      if (Control->InheritsFrom(__classid(TButton))) {
         Button = (TButton*)Control;
         if (!Button->Visible)
            continue;
         if (Button == btSave ||
             Button == btCancel ||
             Button == btUndo) {
            Button->Enabled = !Enable;
            if (Button->Action)
               ((TCustomAction*)Button->Action)->Enabled = !Enable;
         } else
         if (Button == btSearch ||
             Button == btBrowse ||
             Button == btNew ||
             Button == btExit) {
            Button->Enabled = Enable;
            if (Button->Action)
               ((TCustomAction*)Button->Action)->Enabled = Enable;
         } else {
            bool EnableRec = (Enable) ? ((bool)(FDataSetWork->RecordCount > 0)) : Enable;
            Button->Enabled = EnableRec;
            if (Button->Action)
               ((TCustomAction*)Button->Action)->Enabled = EnableRec;
         }
      }
   } __finally {}
   }
   if (AfterEnableButtons != NULL)
      AfterEnableButtons(Enable);
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::LimpaFiltros()
{
   if (FFilters == NULL)
      return;

   SfgGroupFilter *GroupFilter = NULL;
   SfgFilter *Filter = NULL;
   for (int i =0; i < FFilters->Count; i++) {
      GroupFilter = (SfgGroupFilter*)FFilters->Items[i];
      Filter = GroupFilter->Filter;
      delete Filter;
      delete GroupFilter;
   }
   FFilters->Clear();
   delete FFilters;
   FFilters = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::LimpaOrdenacao()
{
   if (FOrders == NULL)
      return;

   SfgOrder *Order = NULL;
   for (int i =0; i < FOrders->Count; i++) {
      Order = (SfgOrder*)FOrders->Items[i];
      delete Order;
   }
   FOrders->Clear();
   delete FOrders;
   FOrders = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ToolbarApplyFilter(TObject *Sender, bool &Sucess)
{
   FDataSet->Active = false;
   FWhereAdd = FormSearch->WhereAdd;
   FWhereFilter = FormSearch->Where;
   FOrderByFilter = FormSearch->OrderBy;
   if (!ActiveDataSet()) {
      Sucess = false;
      return;
   }
   if (OnApplayFilter != NULL)
      this->OnApplayFilter(this,Sucess);

   if (Sucess)
      EnableToolbarButtons(true);
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::RefreshQuery()
{
   FDataSet->Active = false;
   ActiveDataSet();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::BrowseReturn(Variant Value)
{
   TField *Field;
   FDataSet->Active = false;
   FWhereFilter = "";
   //Deve montar uma consulta com os valores
   if (VarIsArray(Value) && (VarArrayDimCount(Value) > 0)) {
      for (int i = VarArrayLowBound(Value, 1); i <= VarArrayHighBound(Value, 1); i++) {
         Field = FormBrowse->FieldsKey->Fields[i];
         if (FWhereFilter.Length() > 0) {
            FWhereFilter = FWhereFilter + " AND " + \
                           Field->FieldName + " = " + QuotedStr(VarToStr(Value.GetElement(i)));
         } else {
            FWhereFilter = Field->FieldName + " = " + QuotedStr(VarToStr(Value.GetElement(i)));
         }
      }
   } else {
      Field = FormBrowse->FieldsKey->Fields[0];
      FWhereFilter = Field->FieldName + " = " + QuotedStr(VarToStr(Value));
   }
   FOrderByFilter = "";
   if (!ActiveDataSet()) {
      return;
   }

   bool Sucess = true;
   if (OnApplayFilter != NULL)
      this->OnApplayFilter(this,Sucess);

   if (Sucess)
      EnableToolbarButtons(true);
}
//---------------------------------------------------------------------------
bool __fastcall TSfgToolbar::ActiveDataSet()
{
   try {
      ((TZQuery*)FDataSet)->SQL->Text = MontaSQLConsulta();
      FDataSet->Active = true;
   }
   catch(Exception &e) {
      String Msg = "Ocorreu o seguinte erro ao aplicar o filtro selecionado:\n";
      Msg = Msg + e.Message;
      MessageBox(Handle,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ParserSQLOrigin()
{
   int iPosFrom, iPosWhere, iPosOrder, iPosIni, iPosFim;
   String sSQL, sSQLUpper;

   sSQL = ((TZQuery*)FDataSet)->SQL->Text;
   sSQLUpper = sSQL.UpperCase();
   iPosFrom = sSQLUpper.Pos("FROM");
   iPosWhere = sSQLUpper.Pos("WHERE");
   iPosOrder = sSQLUpper.Pos("ORDER");

   if (iPosFrom == 0)
      throw Exception("Verifique o SQL da sua consulta. Não foi encontrado a clausula FROM.");

   iPosIni = 1;
   iPosFim = iPosFrom;
   FSelectOrigin = sSQL.SubString(iPosIni, (iPosFim - iPosIni));
   iPosIni = iPosFrom;
   iPosFim = (iPosWhere > 0) ? iPosWhere : ((iPosOrder > 0) ? iPosOrder : (sSQL.Length() +1 ));
   SetFromOrigin(sSQL.SubString(iPosIni, (iPosFim - iPosIni)));
   if (iPosWhere > 0) {
      iPosIni = iPosWhere;
      iPosFim = (iPosOrder > 0) ? iPosOrder : (sSQL.Length() +1 );
      FWhereOrigin = sSQL.SubString(iPosIni, (iPosFim - iPosIni));
   } else {
      FWhereOrigin = "";
   }
   if (iPosOrder > 0) {
      iPosIni = iPosOrder;
      iPosFim = (sSQL.Length() +1 );
      FOrderByOrigin = sSQL.SubString(iPosIni, (iPosFim - iPosIni));
   } else {
      FOrderByOrigin = "";
   }
   //Se não recebeu a listagem de colunas para ser usado, tenta fazer o parser no SELECT
   if (FSelectColumns.Length() == 0)
      FSelectColumns = ParserSelectColumns(sSQL);

}
//---------------------------------------------------------------------------
String __fastcall TSfgToolbar::MontaSQLConsulta()
{
   String sSQL;

   sSQL = FSelectOrigin + " " +\
          FFromOrigin + " " + \
          FWhereOrigin;
   if (FWhereOrigin.Length() > 0) {
      if (FWhereFilter.Length() > 0) {
         sSQL = sSQL + " AND " + FWhereFilter;
      }
   } else {
      if (FWhereFilter.Length() > 0) {
         sSQL = sSQL + " WHERE " + FWhereFilter;
      }
   }
   sSQL += ((FOrderByFilter.Length() > 0) ? (" " + FOrderByFilter) : (" " + FOrderByOrigin));

   return sSQL;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::SetFromOrigin(String Value)
{
   FFromOrigin = Value;
   ParserFromOrigin();
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ParserFromOrigin()
{
   if (FFromTables != NULL) {
      FFromTables->Clear();
      delete FFromTables;
   }
   FFromTables = NULL;

   int iPosIni, iPosFim;
   String sTableName;
   bool bSchemaName;
   String sFROMUpper = FFromOrigin.Trim().UpperCase();

   iPosIni = sFROMUpper.Pos("FROM") + 4;
   iPosFim = (sFROMUpper.Length() + 1);
   sFROMUpper = sFROMUpper.SubString(iPosIni, (iPosFim - iPosIni)).Trim();
   //Verifica se é com JOIN ou virgula
   while (sFROMUpper.Length() > 0) {
      iPosFim = sFROMUpper.Pos("JOIN");
      if (iPosFim == 0)
         iPosFim = sFROMUpper.Pos(",");
      if (iPosFim == 0)
         iPosFim = sFROMUpper.Length() + 1;
      sTableName = "";
      bSchemaName = false;
      for (int i = 1; i < iPosFim; i++) {
         if (!bSchemaName && sFROMUpper[i] == '.') {
            bSchemaName= true;
         } else {
            if (!IsCharAlphaNumeric(sFROMUpper[i]) && sFROMUpper[i] != '_')
               break;
         }
         sTableName = sTableName + sFROMUpper[i];
      }
      if (sTableName.Length() > 0) {
         if (FFromTables == NULL)
            FFromTables = new TStringList();
         FFromTables->Add(sTableName.LowerCase());
      }
      if (iPosFim < sFROMUpper.Length()) {
         sFROMUpper = sFROMUpper.SubString(iPosFim, (sFROMUpper.Length() - iPosFim)).Trim();
      } else {
         break;
      }
   }
}
//---------------------------------------------------------------------------
String __fastcall TSfgToolbar::ParserSelectColumns(String SQL)
{
   String SelectColumns = "";
   try
	{
      WideString wSQL = SQL;
		IAZSQL::ParseSQL parse(wSQL.c_bstr());

		IAZSQL::ParseSQL::StringVector columns;
		parse.GetNameColumns(columns);

		std::wstring colname;
      for (int i = 0; i < columns.size(); i++) {
         colname = columns.operator [](i);
         SelectColumns += String(colname.c_str()).LowerCase().Trim() + ";";
      }
	}
	catch (IAZSQL::ParseException& ex)
	{
		throw ex.Message();
	}
   return SelectColumns;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::GetComboBoxes()
{
   TComponent *Component;
   for (int i = 0; i < FParentForm->ComponentCount; i++) {
      Component = FParentForm->Components[i];
      if (Component->ClassNameIs("TDBComboBox") ||
          Component->ClassNameIs("TDBDataComboBox")) {
         if (FComboBoxes == NULL)
            FComboBoxes = new TStringList();
         if (((TDBComboBox*)Component)->DataSource == FDataSource) {
            FComboBoxes->AddObject(((TDBComboBox*)Component)->DataField, Component);
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ToolbarBeforeShowCombo(SfgFilter *Filter, TCustomComboBox *ComboBox)
{
   //Se possui um evento, executa o evento do usuário
   if (this->BeforeShowCombo != NULL) {
      this->BeforeShowCombo(Filter, ComboBox);
   } else { //Caso contrário, tenta pegar o componente da tela e copiar os itens do mesmo
      int Index = FComboBoxes->IndexOf(Filter->Field->FieldName);
      if (Index >= 0) {
         ComboBox->Clear();
         ComboBox->Items->Assign(((TCustomComboBox*)FComboBoxes->Objects[Index])->Items);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ToolbarToExcelGetValue(TField *Field, OleVariant &Value)
{
   if (!Field->Value.IsNull()) {
      int Index = FComboBoxes->IndexOf(Field->FieldName);
      if (Index >= 0) {
         if (((TCustomComboBox*)FComboBoxes->Objects[Index])->ClassNameIs("TDBDataComboBox")) {
            Value = ((TDBDataComboBox*)FComboBoxes->Objects[Index])->GetText(Field->Value);
         }
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::ExportToExcel()
{
   TSfgLstToExcel *SfgLstToExcel = new TSfgLstToExcel();

   //Se possui um evento, executa o evento do usuário
   if (this->ExportOnGetValue != NULL) {
      SfgLstToExcel->OnGetValue = this->ExportOnGetValue;
   } else { //Caso contrário, se possuir comboboxes na tela, vai usar o evento da toolbar
      if (FComboBoxes != NULL) {
         SfgLstToExcel->OnGetValue = &ToolbarToExcelGetValue;
      }
   }
   //Salvando a posição do RECORD atual
   TBookmark SavePlace = FDataSetWork->GetBookmark();
   //Desabilitando interação com tela
   FDataSetWork->DisableControls();
   //Movendo para o primeiro registro
   FDataSetWork->First();
   //Denominando o nome do arquivo - FORM + AAAA + MM +
   SfgLstToExcel->FileName = SfgLstToExcel->GetExcelFileName(FParentForm);
   SfgLstToExcel->ShowProgress = true;
   //Inicia a comunicação com o Excel
   if (SfgLstToExcel->StartExcel()) {
      //Listando os registro para o Excel
      SfgLstToExcel->DataSetToExcel(FDataSetWork);
      SfgLstToExcel->FinishExcel();
   }
   //Restaura a posição do RECORD anterior
   FDataSetWork->GotoBookmark(SavePlace);
   //Habilita novamente interação com tela
   FDataSetWork->EnableControls();
   delete SfgLstToExcel;
}
//---------------------------------------------------------------------------
String ExtractPartialValue(String StrSearch, int &PosIni, char Delimiter)
{
   String Result;
   int i = PosIni;
   int l = StrSearch.Length();
   while ((i <= l) && (StrSearch[i] != Delimiter))
      i++;
   Result = StrSearch.SubString(PosIni, i - PosIni).Trim();
   if ((i <= l) && (StrSearch[i] == Delimiter))
      i++;
   PosIni = i;
   return Result;
}
//---------------------------------------------------------------------------
void SetFilterValue(SfgFilter *Filter, String StrValue)
{
   TField *Field = Filter->Field;
   if ((Field->DataType == ftString) ||
       (Field->DataType == ftWideString) ||
       (Field->DataType == ftFixedChar)) {
      Filter->Value = StrValue;
   } else
   if ((Field->DataType == ftSmallint) ||
       (Field->DataType == ftWord) ||
       (Field->DataType == ftInteger) ||
       (Field->DataType == ftAutoInc) ||
       (Field->DataType == ftLargeint)) {
      Filter->Value = StrToInt(StrValue);
   } else
   if ((Field->DataType == ftFloat) ||
       (Field->DataType == ftCurrency) ||
       (Field->DataType == ftBCD)) {
      Filter->Value = (float)StrToFloat(StrValue);
   } else
   if (Field->DataType == ftDate) {
      Filter->Value = StrToDate(StrValue);
   } else
   if ((Field->DataType == ftDateTime) ||
       (Field->DataType == ftTimeStamp)) {
      Filter->Value = StrToDateTime(StrValue);
   } else
      Filter->Value = StrValue;
}
//---------------------------------------------------------------------------
void __fastcall TSfgToolbar::LoadSearchProfile()
{
   TField *Field = NULL;
   SfgGroupFilter *GroupFilter = NULL;
   SfgOrder *OrderAdd = NULL;
   String StrProfile, FieldName, StrValue, StrFilter, StrOrder;
   int iPosKey, iPosCsv;
	TZQuery *QyLoadProfile;
try {
	QyLoadProfile = new TZQuery(Application);
	QyLoadProfile->Connection = AppConnection;
   QyLoadProfile->SQL->Text = "\
SELECT 1 pro_ord, profile_line, profile_value\
  FROM tbl_profile_usuario\
 WHERE usuario = :usuario \
   AND profile_key = :key_filter_basic \
UNION ALL \n\
SELECT 2 pro_ord, profile_line, profile_value\
  FROM tbl_profile_usuario\
 WHERE usuario = :usuario\
   AND profile_key = :key_filter_adv \
UNION ALL \n\
SELECT 3 pro_ord, profile_line, profile_value\
  FROM tbl_profile_usuario\
 WHERE usuario = :usuario \
   AND profile_key = :key_orderby \
UNION ALL \n\
SELECT 4 pro_ord, profile_line, profile_value\
  FROM tbl_profile_usuario\
 WHERE usuario = :usuario \
   AND profile_key = :key_filter_user \
 ORDER BY pro_ord, profile_line";
   QyLoadProfile->ParamByName("usuario")->AsString = AppUser->Usuario;
   QyLoadProfile->ParamByName("key_filter_basic")->AsString = FParentForm->Name + "_filter_basic";
   QyLoadProfile->ParamByName("key_filter_adv")->AsString = FParentForm->Name + "_filter_advanced";
   QyLoadProfile->ParamByName("key_orderby")->AsString = FParentForm->Name + "_orderby";
   QyLoadProfile->ParamByName("key_filter_user")->AsString = FParentForm->Name + "_filter_user";
   QyLoadProfile->Active = true;
   QyLoadProfile->First();
   while (!QyLoadProfile->Eof) {
      StrProfile = QyLoadProfile->FieldByName("profile_value")->AsString;
      if (QyLoadProfile->FieldByName("pro_ord")->AsInteger == 1) {
         //Deve desmontar as chaves de filtros {campo;operador;valor}
         iPosKey = 1;
         while (iPosKey <= StrProfile.Length()) {
            iPosKey++; //Primeiro caracter é '{'
            StrFilter = ExtractPartialValue(StrProfile,iPosKey,'}');
            iPosCsv = 1;
            FieldName = ExtractPartialValue(StrFilter,iPosCsv,';');
            Field = FDataSetWork->FindField(FieldName);
            if (Field != NULL) {
               if (FFilters == NULL)
                  FFilters = new SfgFilters();
               GroupFilter = new SfgGroupFilter();
               GroupFilter->Group = -1;
               GroupFilter->Filter = new SfgFilter();
               GroupFilter->Filter->Field = Field;
               GroupFilter->Filter->Operator = ExtractPartialValue(StrFilter,iPosCsv,';');
               StrValue = ExtractPartialValue(StrFilter,iPosCsv,';');
               SetFilterValue(GroupFilter->Filter,StrValue);
               GroupFilter->Filter->Like = (bool)StrValue.Pos("*");
               FFilters->Add(GroupFilter);
            }
         }
      }
      else
      if (QyLoadProfile->FieldByName("pro_ord")->AsInteger == 2) {
         //Deve desmontar as chaves de filtros {campo;linha,operador;valor;e/ou}
         iPosKey = 1;
         while (iPosKey <= StrProfile.Length()) {
            iPosKey++; //Primeiro caracter é '{'
            StrFilter = ExtractPartialValue(StrProfile,iPosKey,'}');
            iPosCsv = 1;
            FieldName = ExtractPartialValue(StrFilter,iPosCsv,';');
            Field = FDataSetWork->FindField(FieldName);
            if (Field != NULL) {
               if (FFilters == NULL)
                  FFilters = new SfgFilters();
               GroupFilter = new SfgGroupFilter();
               GroupFilter->Group = StrToInt(ExtractPartialValue(StrFilter,iPosCsv,';'));
               GroupFilter->Filter = new SfgFilter();
               GroupFilter->Filter->Field = Field;
               GroupFilter->Filter->Operator = ExtractPartialValue(StrFilter,iPosCsv,';');
               StrValue = ExtractPartialValue(StrFilter,iPosCsv,';');
               SetFilterValue(GroupFilter->Filter,StrValue);
               GroupFilter->Filter->Like = (bool)StrValue.Pos("*");
               GroupFilter->StrAndOr = ExtractPartialValue(StrFilter,iPosCsv,';');
               FFilters->Add(GroupFilter);
            }
         }
      }
      else
      if (QyLoadProfile->FieldByName("pro_ord")->AsInteger == 3) {
         //Deve desmontar as chaves de ordenação {campo;ordem}
         iPosKey = 1;
         while (iPosKey <= StrProfile.Length()) {
            iPosKey++; //Primeiro caracter é '{'
            StrOrder = ExtractPartialValue(StrProfile,iPosKey,'}');
            iPosCsv = 1;
            FieldName = ExtractPartialValue(StrOrder,iPosCsv,';');
            Field = FDataSetWork->FindField(FieldName);
            if (Field != NULL) {
               if (FOrders == NULL)
                  FOrders = new SfgOrders();
               OrderAdd = new SfgOrder();
               OrderAdd->Field = Field;
               OrderAdd->Order = StrToInt(ExtractPartialValue(StrOrder,iPosCsv,';'));
               FOrders->Add(OrderAdd);
            }
         }
      }
      else
      if (QyLoadProfile->FieldByName("pro_ord")->AsInteger == 4) {
         FWhereAdd += StrProfile;
      }
      QyLoadProfile->Next();
   }
	delete QyLoadProfile;
} catch(Exception &e) {
	String MsgErro = "Ocorreu o seguinte erro ao carregar as informações do perfil:\n";
   MsgErro = MsgErro + e.Message;
   MessageBox(NULL,MsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------

