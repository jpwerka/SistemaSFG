//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uSfgToolTip.h"
#include "uSfgTools.h"
#include "uSfgMsgOption.h"
#include "uDataModule.h"
#include "uSfgMetaData.h"
#include "uSfgDrawCmp.h"
#include "uSfgBrowse.h"
#pragma hdrstop
#include "uSfgSearch.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
__fastcall TfrmSearch::TfrmSearch(TComponent* Owner)
        : TForm(Owner)
{
   this->FFilters = NULL;
   this->FOrders = NULL;
	this->FDataSet = NULL;
	this->FWhereUser = "";
	this->FWhereSQL = "";
   this->FWhereAdd = "";
	this->FOrderSQL = "";
   this->FUseSql = false;
	this->OnApplayFilter = NULL;
   this->BeforeFilterEdit = NULL;
   this->BeforeShowCombo = NULL;
   this->AfterChangeCombo = NULL;
   this->FFormBrowse = NULL;
   this->ParentForm = NULL;
	Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
	Tolltips->CreateToolTips();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete Tolltips;
   DelAllObjects();
   Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::DelAllObjects()
{
   int iRow = 0;
   for (iRow = 1; iRow < grdBasico->RowCount; iRow++)
      DelObjectsGrid(grdBasico,iRow);
   for (iRow = 1; iRow < grdAvancado->RowCount; iRow++)
      DelObjectsGrid(grdAvancado,iRow);
   for (iRow = 1; iRow < grdOrder->RowCount; iRow++)
      DelObjectsGrid(grdOrder,iRow);
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SetDataSet(TDataSet *Value)
{
   int ACol = 0;
   TField *Field = NULL;
   TSfgMetaField *MetaField = NULL;
   FDataSet = Value;
   DelAllObjects();
	cbCampoBas->Clear();
	cbCampoOrd->Clear();
   grdAvancado->ColCount = 1;
	for(int i = 0; i < FDataSet->FieldCount; i++) {
      Field = FDataSet->Fields->Fields[i];
      //Só adiciona o campo caso ele seja um campo do SQL
      if (!((Field->FieldKind == fkData) || (Field->FieldKind == fkLookup)))
         continue;

      MetaField = (TSfgMetaField*)Field->Tag;
      if (MetaField == NULL)
         continue;
      if (!MetaField->IsPkKey && !MetaField->IsIndex && !MetaField->IsSearch)
         continue;

      //Só adiciona o campo se ele for de um tipo comum que o usuário possa filtar
      // Texto, Número, Data e Hora
      if ((Field->DataType == ftString) ||
          (Field->DataType == ftWideString) ||
          (Field->DataType == ftFixedChar) ||
          (Field->DataType == ftSmallint) ||
          (Field->DataType == ftWord) ||
          (Field->DataType == ftInteger) ||
          (Field->DataType == ftAutoInc) ||
          (Field->DataType == ftLargeint) ||
          (Field->DataType == ftBoolean ) ||
          (Field->DataType == ftFloat) ||
          (Field->DataType == ftCurrency) ||
          (Field->DataType == ftBCD) ||
          (Field->DataType == ftDate) ||
          (Field->DataType == ftTime) ||
          (Field->DataType == ftDateTime) ||
          (Field->DataType == ftTimeStamp)) {
         //Vinculando os campos aos componentes
         cbCampoBas->AddItem(Field->DisplayLabel, (TObject*)Field);
         if (MetaField->IsPkKey || MetaField->IsIndex || MetaField->Order.InSearch)
            cbCampoOrd->AddItem(Field->DisplayLabel, (TObject*)Field);
         ACol++;
         grdAvancado->ColCount++;
         grdAvancado->ColWidths[ACol] = GetColumnWidth(Field);
         grdAvancado->Cells[ACol][0] = Field->DisplayLabel;
         grdAvancado->Objects[ACol][0] = (TObject*)Field;
      }
   }
   //Adicionando a coluna de seleção (E/OU) no GRID avançado
   grdAvancado->FixedCols = 1;
   ACol++;
   grdAvancado->ColCount++;
   grdAvancado->Cells[ACol][0] = "E/OU";
   grdAvancado->AlignCell[ACol][0] = alCenter;
   grdAvancado->AlignCol[ACol] = alCenter;
   grdAvancado->ColWidths[ACol] = 45;
   grdAvancado->EditCol[ACol] = false;
   iGrdAdvCnd = ACol;
   //Adicionando os objetos para as primeiras linhas dos grids
   AddObjectsGrid(grdBasico,1);
   AddObjectsGrid(grdAvancado,1);
   AddObjectsGrid(grdOrder,1);
}
//---------------------------------------------------------------------------
int __fastcall TfrmSearch::GetColumnWidth(TField *Field)
{
   TEXTMETRIC TM;
   int iRetW = 0;
   int iTitleW = 0;
   TCanvas *Canvas = grdAvancado->Canvas;

try {
   Canvas->Font = this->Font;
   GetTextMetrics(Canvas->Handle, &TM);
   iRetW = Field->DisplayWidth * (Canvas->TextWidth("0") - TM.tmOverhang)
          + TM.tmOverhang + 5;
   iTitleW = Canvas->TextWidth(Field->DisplayLabel) + 5;
   iRetW = (iTitleW > iRetW) ? iTitleW : iRetW;
   iRetW = (iRetW > 600) ? 600 : iRetW;
} catch ( ... ) {
   iRetW = grdAvancado->DefaultColWidth;
}
   return iRetW;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SetFilters(SfgFilters *Value)
{
   if (FDataSet == NULL) {
      throw Exception("Somente é possível definir uma lista de filtros após a definição do conjunto de dados. (DataSet)");
   }
   FFilters = Value;
   if (FFilters == NULL)
      return;

   SfgGroupFilter *GroupFilter = NULL;
   SfgFilter *Filter = NULL;
   int ARow = 1;
   int ACol = 1;
   for (int i =0; i < FFilters->Count; i++) {
      GroupFilter = (SfgGroupFilter*)FFilters->Items[i];
      if (GroupFilter->Group == -1) { //Indica o grupo básico
         if (ARow == 1) {
            Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
            if (Filter->Field != NULL) {
               grdBasico->RowCount++;
               ARow = grdBasico->RowCount - 1;
               AddObjectsGrid(grdBasico,ARow);
               Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
            }
         } else {
            grdBasico->RowCount++;
            ARow = grdBasico->RowCount - 1;
            AddObjectsGrid(grdBasico,ARow);
            Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
         }
         Filter->Field = GroupFilter->Filter->Field;
         Filter->Operator = GroupFilter->Filter->Operator;
         Filter->Value = GroupFilter->Filter->Value;
         Filter->Like = GroupFilter->Filter->Like;
         grdBasico->Cells[GRD_BSC_CMP][ARow] = Filter->Field->DisplayLabel;
         grdBasico->Cells[GRD_BSC_CND][ARow] = Filter->Operator;
         grdBasico->Cells[GRD_BSC_VAL][ARow] = VarToStr(Filter->Value);
      } else {
         ARow = GroupFilter->Group;
         while (ARow > (grdAvancado->RowCount - 1)) {
            grdAvancado->RowCount++;
            AddObjectsGrid(grdAvancado,grdAvancado->RowCount-1);
         }
         ACol = GroupFilter->Filter->Field->Index + 1;
         Filter = (SfgFilter*)grdAvancado->Objects[ACol][ARow];
         Filter->Field = GroupFilter->Filter->Field;
         Filter->Operator = GroupFilter->Filter->Operator;
         Filter->Value = GroupFilter->Filter->Value;
         Filter->Like = GroupFilter->Filter->Like;
         if (Filter->Operator == "=") {
            grdAvancado->Cells[ACol][ARow] = VarToStr(Filter->Value);
         } else {
            grdAvancado->Cells[ACol][ARow] = Filter->Operator + " " + VarToStr(Filter->Value);
         }
         grdAvancado->Cells[grdAvancado->ColCount - 1][ARow] = GroupFilter->StrAndOr;
      }
   }
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SetOrders(SfgOrders *Value)
{
   if (FDataSet == NULL) {
      throw Exception("Somente é possível definir uma lista de ordenação após a definição do conjunto de dados. (DataSet)");
   }
   FOrders = Value;
   if (FOrders == NULL)
      return;

   SfgOrder *Order = NULL;
   SfgOrder *OrderAdd = NULL;
   int ARow = 1;
   for (int i =0; i < FOrders->Count; i++) {
      Order = (SfgOrder*)FOrders->Items[i];
      if (ARow == 1) {
         OrderAdd = (SfgOrder*)grdOrder->Objects[GRD_BSC_PTR][ARow];
         if (OrderAdd->Field != NULL) {
            grdOrder->RowCount++;
            ARow = grdOrder->RowCount - 1;
            AddObjectsGrid(grdOrder,ARow);
            OrderAdd = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][ARow];
         }
      } else {
         grdOrder->RowCount++;
         ARow = grdOrder->RowCount - 1;
         AddObjectsGrid(grdOrder,ARow);
         OrderAdd = (SfgOrder*)grdOrder->Objects[GRD_BSC_PTR][ARow];
      }
      OrderAdd->Field = Order->Field;
      OrderAdd->Order = Order->Order;
      grdOrder->Cells[GRD_ORD_CMP][ARow] = OrderAdd->Field->DisplayLabel;
      grdOrder->Cells[GRD_ORD_ORD][ARow] = ((OrderAdd->Order == SFG_ORDER_ASC) ? "Ascendente" : "Descendente");
   }
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::LimpaFiltros()
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
void __fastcall TfrmSearch::LimpaOrdenacao()
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
void __fastcall TfrmSearch::BtCancelClick(TObject *Sender)
{
   Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::BtOkClick(TObject *Sender)
{
   int ARow, ACol;
   SfgGroupFilter *GroupFilter = NULL;
   SfgFilter *Filter = NULL;
   SfgOrder *Order = NULL;
   SfgOrder *OrderAdd = NULL;

   LimpaFiltros();

   //Montando primeiro todos os filtros básicos
   for (ARow = 1; ARow < grdBasico->RowCount; ARow++) {
      Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
      if (Filter == NULL)
         continue;
      if (Filter->Field != NULL && !Filter->Value.IsNull()) {
         if (FFilters == NULL)
            FFilters = new SfgFilters();
         GroupFilter = new SfgGroupFilter();
         GroupFilter->Group = -1;
         GroupFilter->Filter = new SfgFilter();
         GroupFilter->Filter->Field = Filter->Field;
         GroupFilter->Filter->Operator = Filter->Operator;
         GroupFilter->Filter->Value = Filter->Value;
         GroupFilter->Filter->Like = Filter->Like;
         FFilters->Add(GroupFilter);
      } //Fim campo não é nulo
   } //Fim do for de linhas

   //Montando primeiro todos os filtros básicos
   for (ARow = 1; ARow < grdAvancado->RowCount; ARow++) {
      for (ACol = 1; ACol < (grdAvancado->ColCount - 1); ACol++) {
         Filter = (SfgFilter*)grdAvancado->Objects[ACol][ARow];
         if (Filter == NULL)
            continue;
         if (Filter->Field != NULL && !Filter->Value.IsNull()) {
            if (FFilters == NULL)
               FFilters = new SfgFilters();
            GroupFilter = new SfgGroupFilter();
            GroupFilter->Group = ARow;
            GroupFilter->Filter = new SfgFilter();
            GroupFilter->Filter->Field = Filter->Field;
            GroupFilter->Filter->Operator = Filter->Operator;
            GroupFilter->Filter->Value = Filter->Value;
            GroupFilter->Filter->Like = Filter->Like;
            GroupFilter->StrAndOr = grdAvancado->Cells[grdAvancado->ColCount - 1][ARow];
            FFilters->Add(GroupFilter);
         } //Fim campo não é nulo
      } //Fim do for de colunas
   } //Fim do for de linhas

   //Refazendo a lista de ordenação customizzada
   LimpaOrdenacao();

   for (ARow = 1; ARow < grdOrder->RowCount; ARow++) {
      Order = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][ARow];
      if (Order == NULL)
         continue;
      if (Order->Field != NULL) {
         if (FOrders == NULL)
            FOrders = new SfgOrders();
         OrderAdd = new SfgOrder();
         OrderAdd->Field = Order->Field;
         OrderAdd->Order = Order->Order;
         FOrders->Add(OrderAdd);
      } //Fim campo não é nulo
   } //Fim do for de linhas

   bool bSucess = true;
   if (OnApplayFilter != NULL)
      this->OnApplayFilter(this,bSucess);

   if (bSucess)
      this->ModalResult = mrOk;

}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::edtValorKeyPress(TObject *Sender, char &Key)
{
   if (bFloat) {
      Validacoes::ValidarFloat(((TEdit*)Sender)->Text, Key);
   } else {
      Validacoes::CharIsInteger(Key);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbCampoBasChange(TObject *Sender)
{
   if (cbCampoBas->ItemIndex < 0)
      return;
   if (!cbCampoBas->Visible)
      return;
   //Pega a referência dos filtros do campo
   TField *Field = (TField*)cbCampoBas->Items->Objects[cbCampoBas->ItemIndex];
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   if ((Field->DataType == ftString) ||
       (Field->DataType == ftWideString) ||
       (Field->DataType == ftFixedChar)) {
       edtValorBas->MaxLength = Field->Size;
   } else {
       edtValorBas->MaxLength = 0;
   }
   bFloat = false;
   edtValorBas->OnKeyPress = NULL;
   edtValorBas->EditMask = Field->EditMask;
   if ((Field->DataType == ftSmallint) ||
       (Field->DataType == ftWord) ||
       (Field->DataType == ftInteger) ||
       (Field->DataType == ftAutoInc) ||
       (Field->DataType == ftLargeint) ||
       (Field->DataType == ftBoolean )) {
      edtValorBas->OnKeyPress = &edtValorKeyPress;
   } else
   if ((Field->DataType == ftFloat) ||
       (Field->DataType == ftCurrency) ||
       (Field->DataType == ftBCD)) {
      bFloat = true;
      edtValorBas->OnKeyPress = &edtValorKeyPress;
   }
   //Como mudou o campo deve limpar o valor
   Filter->Field = Field;
   Filter->Value = Null();
   grdBasico->Cells[GRD_BSC_CMP][grdBasico->Row] = Filter->Field->DisplayLabel;
   grdBasico->Cells[GRD_BSC_VAL][grdBasico->Row] = "";
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbCondicaoBasChange(TObject *Sender)
{
   if (cbCondicaoBas->ItemIndex < 0)
      return;
   if (!cbCondicaoBas->Visible)
      return;
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   Filter->Operator = cbCondicaoBas->Text;
   grdBasico->Cells[GRD_BSC_CND][grdBasico->Row] = Filter->Operator;
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::edtValorBasChange(TObject *Sender)
{
   if (!edtValorBas->Visible)
      return;
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   String StrErro;
   if (VarToStr(Filter->Value) != edtValorBas->Text) {
      if (edtValorBas->Text.Trim().Length() > 0) {
         if (!ValidValue(Filter,edtValorBas->Text.Trim(),StrErro)) {
            MessageBox(Handle,StrErro.c_str(),Caption.c_str(),APP_ERROR);
            return;
         }
         Filter->Value = edtValorBas->Text.Trim();
      } else {
         Filter->Value = Null();
      }
      grdBasico->Cells[GRD_BSC_VAL][grdBasico->Row] = VarToStr(Filter->Value);
      MontaFiltro();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbValorBasChange(TObject *Sender)
{
   if (cbValorBas->ItemIndex < 0)
      return;
   if (!cbValorBas->Visible)
      return;
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   SfgComboObject *pObject = (SfgComboObject*)cbValorBas->Items->Objects[cbValorBas->ItemIndex];
   if (pObject != NULL) {
      Filter->Value = pObject->GetValue();
   } else {
      Filter->Value = cbValorBas->Text;
   }
   if (AfterChangeCombo != NULL)
      AfterChangeCombo(Filter, cbValorBas);
   grdBasico->Cells[GRD_BSC_VAL][grdBasico->Row] = cbValorBas->Text;
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::ckCampoBasClick(TObject *Sender)
{
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   TSfgMetaField *MetaField = (TSfgMetaField*)Filter->Field->Tag;
   if (ckCampoBas->Checked) {
      if (Filter->Field->InheritsFrom(__classid(TNumericField)))
         Filter->Value = StrToInt(MetaField->CheckValues.SubString(1,1));
      else
         Filter->Value = MetaField->CheckValues.SubString(1,1);
   } else {
      if (MetaField->CheckValues.Length() > 2) {
         if (Filter->Field->InheritsFrom(__classid(TNumericField)))
            Filter->Value = StrToInt(MetaField->CheckValues.SubString(3,1));
         else
            Filter->Value = MetaField->CheckValues.SubString(3,1);
      } else {
         if (Filter->Field->InheritsFrom(__classid(TNumericField)))
            Filter->Value = (int)0;
         else
            Filter->Value = "N";
      }
   }
   grdBasico->Cells[GRD_BSC_VAL][grdBasico->Row] = VarToStr(Filter->Value);
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::grdAvancadoValidateEdit(TObject *Sender,
      int ACol, int ARow, bool &Result)
{
   //Deve validar se o usuário digitou um valor correto
   String sValue = grdAvancado->Cells[ACol][ARow];
   SfgFilter *Filter = (SfgFilter*)grdAvancado->Objects[ACol][ARow];
   String sOperador, sOpAux;

   if (sValue.Trim().Length() == 0) {
      Filter->Operator = "";
      Filter->Value = Null();
      Result = true;
      MontaFiltro();
      return;
   }

   //Deve validar se o usuário informou um operador
   // = , != , <> , >= , <= , > , <
   sOperador = "";
   sValue = sValue.Trim();
   bool bFindOp = true;
   int iPos = 1;
   while(bFindOp && (iPos - 1) < sValue.Length()) {
      sOpAux = sValue.SubString(iPos,1);
      if (sOpAux == "=" || sOpAux == "!" || sOpAux == "<" || sOpAux == ">") {
         sOperador += sOpAux;
         iPos++;
      } else {
         bFindOp = false;
      }
   }
   //Deve validar se o operador é válido
   if (sOperador.Length() > 0) {
      if (sOperador != "=" &&
          sOperador != "!=" &&
          sOperador != "<>" &&
          sOperador != ">=" &&
          sOperador != "<=" &&
          sOperador != ">" &&
          sOperador != "<") {
         MessageBox(Handle,"Operador informado no campo é inválido!",Caption.c_str(),APP_ERROR);
         Result = false;
         return;
      }
      if (sOperador == "<>")
         sOperador = "!=";
   } else {
      sOperador = "=";
   }
   //Deve validar se foi informado o operador e o valor a ser filtrado
   sValue = sValue.SubString(iPos,sValue.Length()-(iPos-1)).Trim();
   if (sValue.Length() == 0) {
      MessageBox(Handle,"Informe o operador e o valor para o campo!",Caption.c_str(),APP_ERROR);
      Result = false;
      return;
   }
   String StrErro = "";
   Filter->Operator = sOperador;
   if (!ValidValue(Filter,sValue,StrErro)) {
      Filter->Operator = "";
      MessageBox(Handle,StrErro.c_str(),Caption.c_str(),APP_ERROR);
      Result = false;
      return;
   }
   MontaFiltro();
}
//---------------------------------------------------------------------------
bool __fastcall TfrmSearch::ValidValue(SfgFilter *Filter, String StrValue, String &StrErro)
{
   TField *Field = Filter->Field;
   //Deve verificar se o usuário informou um asterisco
   //Somente campos do tipo String podem ser filtrado com LIKE
   bool FilterLike = (bool)StrValue.Pos("*");

   if ((Field->DataType == ftString) ||
       (Field->DataType == ftWideString) ||
       (Field->DataType == ftFixedChar)) {
       //Somente pode ser LIKE com igual ou diferente
       if (FilterLike && Filter->Operator != "=" && Filter->Operator != "!=") {
         StrErro = "Pesquisas parciais somente podem ser feitas\npara operadores 'igual' ou 'dieferente'!";
         return false;
       }
       Filter->Value = StrValue;
       Filter->Like = FilterLike;
   } else {
      if (FilterLike) {
         StrErro = "Pesquisas parciais somente podem ser feitas para campos do tipo texto!";
         return false;
      }
      if (Field->DataType == ftBoolean ) {
         if (StrValue.UpperCase() == "S" ||
             StrValue.UpperCase() == "T" ||
             StrValue == "1") {
            StrValue = "1";
         } else
         if (StrValue.UpperCase() == "N" ||
             StrValue.UpperCase() == "F" ||
             StrValue == "0") {
            StrValue = "0";
         } else {
            StrErro = "Valor inválido para campo do tipo boleano.\nValores válidos: ({N,S}{F,T}{0,1})!";
            return false;
         }
         Filter->Value = StrValue;
      } else
      if ((Field->DataType == ftSmallint) ||
          (Field->DataType == ftWord) ||
          (Field->DataType == ftInteger) ||
          (Field->DataType == ftAutoInc) ||
          (Field->DataType == ftLargeint)) {
         int IntValue = 0;
         try {
            IntValue = StrToInt(StrValue);
         }
         catch(...) {
            StrErro = "Valor informado não é um número inteiro válido!";
            return false;
         }
         if (Field->DataType == ftSmallint && IntValue < -32768 && IntValue > 32767) {
            StrErro = "Limites de valores estourados para o campo.\nValores válidos: (Entre -32768 e 32767)!";
            return false;
         }
         if (Field->DataType == ftWord && IntValue < 0 && IntValue > 65535) {
            StrErro = "Limites de valores estourados para o campo.\nValores válidos: (Entre 0 e 65535)!";
            return false;
         }
         Filter->Value = StrValue;
      } else
      if ((Field->DataType == ftFloat) ||
          (Field->DataType == ftCurrency) ||
          (Field->DataType == ftBCD)) {
         try {
            StrToFloat(StrValue);
         }
         catch(...) {
            StrErro = "Valor informado não é um número decimal válido!";
            return false;
         }
         Filter->Value = StrValue;
      } else
      if (Field->DataType == ftDate) {
         TDateTime dDate;
         try {
            dDate = StrToDate(StrValue);
         }
         catch(...) {
            StrErro = "Valor informado não é uma data válida!";
            return false;
         }
         Filter->Value = dDate;
      } else
      if ((Field->DataType == ftDateTime) ||
          (Field->DataType == ftTimeStamp)) {
         TDateTime dDateTime;
         try {
            dDateTime = StrToDateTime(StrValue);
         }
         catch(...) {
            StrErro = "Valor informado não é uma data/hora válida!";
            return false;
         }
         Filter->Value = dDateTime;
      } else
      if (Field->DataType == ftTime) {
         try {
            StrToTime(StrValue);
         }
         catch(...) {
            StrErro = "Valor informado não é uma hora válida!";
            return false;
         }
         Filter->Value = StrValue;
      }
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbCondicaoAdvChange(TObject *Sender)
{
   if (cbCondicaoAdv->ItemIndex < 0)
      return;
   if (!cbCondicaoAdv->Visible)
      return;
   grdAvancado->Cells[grdAvancado->Col][grdAvancado->Row] =
      cbCondicaoAdv->Items->Strings[cbCondicaoAdv->ItemIndex];
   //cbCondicaoAdv->Visible = false;
   grdAvancado->SetFocus();
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbCampoOrdChange(TObject *Sender)
{
   if (cbCampoOrd->ItemIndex < 0)
      return;
   if (!cbCampoOrd->Visible)
      return;
   SfgOrder *Order = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][grdOrder->Row];
   Order->Field = (TField*)cbCampoOrd->Items->Objects[cbCampoOrd->ItemIndex];
   grdOrder->Cells[GRD_ORD_CMP][grdOrder->Row] = Order->Field->DisplayLabel;
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::cbCondicaoOrdChange(TObject *Sender)
{
   if (cbCondicaoOrd->ItemIndex < 0)
      return;
   if (!cbCondicaoOrd->Visible)
      return;
   SfgOrder *Order = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][grdOrder->Row];
   Order->Order = cbCondicaoOrd->ItemIndex;
   grdOrder->Cells[GRD_ORD_ORD][grdOrder->Row] = cbCondicaoOrd->Text;
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::grdSelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
   TRect Rect;
   TStringAlignGrid *pGrid = (TStringAlignGrid*)Sender;
   TSfgMetaField *MetaField = NULL;
   //Deve validar se esta célula em questão possui um componente para ser posicionado
   FLastEditCtr = NULL;
   if (pGrid == grdBasico) {
      SfgFilter *Filter = (SfgFilter*)pGrid->Objects[GRD_BSC_PTR][ARow];
      if (ACol == GRD_BSC_CMP) {
         FLastEditCtr = cbCampoBas;
         if (Filter->Field != NULL) {
            cbCampoBas->ItemIndex = cbCampoBas->Items->IndexOfObject(Filter->Field);
         } else {
            cbCampoBas->ItemIndex = -1;
         }
      } else
      if (ACol == GRD_BSC_CND) {
         FLastEditCtr = cbCondicaoBas;
         if (Filter->Operator.Length() > 0) {
            cbCondicaoBas->ItemIndex = cbCondicaoBas->Items->IndexOf(Filter->Operator);
         } else {
            cbCondicaoBas->ItemIndex = -1;
         }
      } else
      if (ACol == GRD_BSC_VAL) {
         //Deve validar se esta coluna possui um componente combo ou um edit
         if (Filter->Field != NULL) {
            MetaField = (TSfgMetaField*)Filter->Field->Tag;
            if (BeforeFilterEdit != NULL)
               BeforeFilterEdit(Filter, MetaField->EditCmp);
            if (MetaField->EditCmp == smeCheckBox) {
               FLastEditCtr = ckCampoBas;
               ckCampoBas->Caption = Filter->Field->DisplayLabel;
               ckCampoBas->Checked = (bool)(VarToStr(Filter->Value) == MetaField->CheckValues.SubString(1,1));
            } else
            if (MetaField->EditCmp == smeComboBox) {
               FLastEditCtr = cbValorBas;
               if (BeforeShowCombo != NULL)
                  BeforeShowCombo(Filter, cbValorBas);
            } else {
               FLastEditCtr = edtValorBas;
               edtValorBas->Text = VarToStr(Filter->Value);
            }
         }
      }
   } else
   if (pGrid == grdAvancado) {
      if (ACol == iGrdAdvCnd && ARow < (pGrid->RowCount - 1)) {
         FLastEditCtr = cbCondicaoAdv;
         cbCondicaoAdv->ItemIndex = cbCondicaoAdv->Items->IndexOf(pGrid->Cells[ACol][ARow]);
      }
   } else
   if (pGrid == grdOrder) {
      SfgOrder *Order = (SfgOrder*)pGrid->Objects[GRD_ORD_PTR][ARow];
      if (ACol == GRD_ORD_CMP) {
         FLastEditCtr = cbCampoOrd;
         if (Order->Field != NULL) {
            cbCampoOrd->ItemIndex = cbCampoOrd->Items->IndexOfObject(Order->Field);
         } else {
            cbCampoOrd->ItemIndex = -1;
         }
      } else
      if (ACol == GRD_ORD_ORD) {
         if (Order->Field != NULL) {
            FLastEditCtr = cbCondicaoOrd;
            cbCondicaoOrd->ItemIndex = Order->Order; // 1 - ASC, 2 - DESC
         } else {
            cbCondicaoOrd->ItemIndex = SFG_ORDER_NONE;
         }
      }
   }
   //Se definiu um componente para edição, deve posicionar o mesmo
   if (FLastEditCtr != NULL) {
      Rect = pGrid->CellRect(ACol, ARow);
      Rect.Left = Rect.Left + pGrid->Left;
      Rect.Right = Rect.Right + pGrid->Left;
      if (MetaField != NULL) {
         if (MetaField->IsFkList)
            Rect.Right -= 18;
         if (MetaField->EditCmp == smeCheckBox)
            Rect.Left += 2;
      }
      Rect.Top = Rect.Top + pGrid->Top;
      Rect.Bottom = Rect.Bottom + pGrid->Top;
      FLastEditCtr->Left = Rect.Left + 2;
      FLastEditCtr->Top = Rect.Top + 2;
      FLastEditCtr->Width = (Rect.Right - 1) - Rect.Left;
      FLastEditCtr->Height = (Rect.Bottom - 1) - Rect.Top;
   }
   CanSelect = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::LastEditExit(TObject *Sender)
{
   if (Sender == edtValorBas)
      edtValorBasChange(Sender);

   FLastEditCtr->Visible = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::addLineExecute(TObject *Sender)
{
   //Deve adicionar uma linha no GRID ativo
   if (this->ActiveControl->InheritsFrom(__classid(TCustomGrid))) {
      TStringAlignGrid *pGrid = (TStringAlignGrid*)this->ActiveControl;
      pGrid->RowCount++;
      pGrid->Rows[pGrid->RowCount-1]->Clear();
      //Deve incluir os objetos de filtro
      AddObjectsGrid(pGrid,pGrid->RowCount-1);
      pGrid->Row = pGrid->RowCount-1;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::AddObjectsGrid(TStringAlignGrid *pGrid, int ARow)
{
   if (pGrid == grdBasico) {
      SfgFilter *Filter = new SfgFilter();
      Filter->Field = NULL;
      Filter->Value = Null();
      Filter->Like = false;
      Filter->Operator = "=";
      pGrid->Cells[GRD_BSC_CND][ARow] = "=";
      pGrid->Objects[GRD_BSC_PTR][ARow] = (TObject*)Filter;
   } else
   if (pGrid == grdAvancado) {
      SfgFilter *Filter;
      int iCol;
      for (iCol = 1; iCol < (pGrid->ColCount - 1); iCol++) {
         Filter = new SfgFilter();
         Filter->Field = (TField*)pGrid->Objects[iCol][0];
         Filter->Value = Null();
         Filter->Like = false;
         pGrid->Objects[iCol][ARow] = (TObject*)Filter;
      }
      pGrid->Cells[iCol][ARow] = "E";
   } else
   if (pGrid == grdOrder) {
      SfgOrder *Order = new SfgOrder();
      Order->Field = NULL;
      Order->Order = SFG_ORDER_NONE;
      pGrid->Objects[GRD_BSC_PTR][ARow] = (TObject*)Order;
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::delLineExecute(TObject *Sender)
{
   //Deve apagar a linha corrente do GRID ativo
   if (this->ActiveControl->InheritsFrom(__classid(TCustomGrid))) {
      TStringAlignGrid *pGrid = (TStringAlignGrid*)this->ActiveControl;
      //Deve excluir os objetos de filtro, caso existam
      DelObjectsGrid(pGrid,pGrid->Row);
      if (pGrid->RowCount > 2) {
         pGrid->RemoveRow(pGrid->Row);
      } else {
         pGrid->Rows[1]->Clear();
         AddObjectsGrid(pGrid,1);
      }
      MontaFiltro();
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::DelObjectsGrid(TStringAlignGrid *pGrid, int ARow)
{
   if (pGrid == grdBasico) {
      SfgFilter *Filter = (SfgFilter*)pGrid->Objects[GRD_BSC_PTR][ARow];
      if (Filter != NULL) {
         delete Filter;
      }
   } else
   if (pGrid == grdAvancado) {
      SfgFilter *Filter;
      for (int iCol = 1; iCol < (pGrid->ColCount - 1); iCol++) {
         SfgFilter *Filter = (SfgFilter*)pGrid->Objects[iCol][ARow];
         if (Filter != NULL) {
            delete Filter;
         }
      }
   } else
   if (pGrid == grdOrder) {
      SfgOrder *Order = (SfgOrder*)pGrid->Objects[GRD_ORD_PTR][ARow];
      if (Order != NULL) {
         delete Order;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::MontaFiltro()
{
   SfgFilter *Filter;
   SfgOrder *Order;
   TField *Field;
   String sFieldName;
   int ARow, ACol;
   ACol = GRD_BSC_PTR;
   //Zerando o filtro SQL a ser usado
   FWhereUser = "";
   FWhereSQL = "";
   FOrderSQL = "";
   FOrderUser = "";
   //Montando primeiro todos os filtros básicos - sempre com (E)(AND)
   for (ARow = 1; ARow < grdBasico->RowCount; ARow++) {
      Filter = (SfgFilter*)grdBasico->Objects[ACol][ARow];
      if (Filter == NULL)
         continue;
      if (Filter->Field != NULL && !Filter->Value.IsNull()) {
         Field = Filter->Field;
         String sValue = VarToStr(Filter->Value);
         String sSQLValue;
         sFieldName = (Field->Origin.Length() > 0) ? Field->Origin : Field->FieldName;

         // Texto, Número, Data e Hora
         if ((Field->DataType == ftString) ||
            (Field->DataType == ftWideString) ||
            (Field->DataType == ftFixedChar) ||
            (Field->DataType == ftSmallint)) {
            sValue = QuotedStr(sValue);
            sSQLValue = sValue;
         } else
         if ((Field->DataType == ftWord) ||
            (Field->DataType == ftInteger) ||
            (Field->DataType == ftAutoInc) ||
            (Field->DataType == ftLargeint) ||
            (Field->DataType == ftBoolean)) {
            sSQLValue = sValue;
         } else
         if ((Field->DataType == ftFloat) ||
            (Field->DataType == ftCurrency) ||
            (Field->DataType == ftBCD)) {
            sSQLValue = StringReplace(sValue, ",", ".", TReplaceFlags() << rfReplaceAll);
         } else 
         if (Field->DataType == ftDate) {
            TDateTime dDate = Filter->Value;
            sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate));
            sSQLValue = QuotedStr(FormatDateTime("yyyy-mm-dd",dDate));
         } else
         if (Field->DataType == ftTime) {
            sValue = QuotedStr(sValue);
            sSQLValue = sValue;
         }

         if (FWhereUser.Length() > 0) {
            FWhereUser = FWhereUser + " E ";
            FWhereSQL = FWhereSQL + " AND ";
         }
         FWhereUser += Field->DisplayLabel;
         FWhereSQL += sFieldName;
         if (Filter->Like) {
            sSQLValue = StringReplace(sSQLValue, "*", "%", TReplaceFlags() << rfReplaceAll);
            if (Filter->Operator == "=") {
               FWhereUser = FWhereUser + " CONTÉM " + sValue;
               FWhereSQL = FWhereSQL + " LIKE " + sSQLValue;
            } else {
               FWhereUser = FWhereUser + " NÃO CONTÉM " + sValue;
               FWhereSQL = FWhereSQL + " NOT LIKE " + sSQLValue;
            }
         } else {
            if ((Field->DataType == ftDateTime) ||
                (Field->DataType == ftTimeStamp)) {
               //Deve verificar se informou data/hora ou somente data
               TDateTime dDateTime = Filter->Value;
               TDateTime dDate = DateOf(dDateTime);
               bool bTime = (bool)((double)(dDateTime - dDate) > (double)0.0);
               //Se possuir somente data deve verificar os limites do dia
               if (!bTime) {
                  sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate));
                  sSQLValue = FormatDateTime("yyyy-mm-dd",dDate);
                  if (Filter->Operator == "=") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " >= '" + sSQLValue + " 00:00:00'";
                     FWhereSQL = FWhereSQL + " AND " + sFieldName + " <= '" + sSQLValue + " 23:59:59'";
                  } else
                  if (Filter->Operator == "!=") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " < '" + sSQLValue + " 00:00:00'";
                     FWhereSQL = FWhereSQL + " AND " + sFieldName + " > '" + sSQLValue + " 23:59:59'";
                  } else
                  if (Filter->Operator == ">=") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " " + Filter->Operator + " '" + sSQLValue + " 00:00:00'";
                  } else
                  if (Filter->Operator == ">") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " " + Filter->Operator + " '" + sSQLValue + " 23:59:59'";
                  } else
                  if (Filter->Operator == "<=") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " " + Filter->Operator + " '" + sSQLValue + " 23:59:59'";
                  } else
                  if (Filter->Operator == "<") {
                     FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                     FWhereSQL = FWhereSQL + " " + Filter->Operator + " '" + sSQLValue + " 00:00:00'";
                  }
               } else {
                  sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate) + " " + TimeToStr(TimeOf(dDateTime)));
                  sSQLValue = QuotedStr(FormatDateTime("yyyy-mm-dd",dDate) + " " + TimeToStr(TimeOf(dDateTime)));
                  FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
                  FWhereSQL = FWhereSQL + " " + Filter->Operator + " " + sSQLValue;
               }
               //Verificar
            } else {
               FWhereUser = FWhereUser + " " + Filter->Operator + " " + sValue;
               FWhereSQL = FWhereSQL + " " + Filter->Operator + " " + sSQLValue;
            }
         }
      } //Fim campo não é nulo
   } //Fim do for de linhas

   //Montando em segundo lugar todos os filtros avançados - pode ser com (E,OU)(AND,OR)
   String sParSQL = "";
   String sParFilter = "";
   String sFilterLine = "";
   String sWhereLine = "";
   bool bNextOr = false;
   bool bPrewOr = false;
   for (ARow = 1; ARow < grdAvancado->RowCount; ARow++) {
      sFilterLine = "";
      sWhereLine = "";
      //Deve verificar se a linha anterior contém OU ou E
      //Primeira linha sempre será considerado E
      bNextOr = false;
      bPrewOr = false;
      ACol = grdAvancado->ColCount - 1;
      //Deve verificar se a linha anterior possui um OU
      bPrewOr = (bool)(grdAvancado->Cells[ACol][ARow - 1] == "OU");
      //Deve verificar se a próxima linha possui um OU
      if (ARow < (grdAvancado->RowCount - 1)) {
         bNextOr = (bool)(grdAvancado->Cells[ACol][ARow] == "OU");
      }
      sParFilter = (bPrewOr) ? "(" : ( (bNextOr) ? "((" : "(" );
      sParSQL = (bPrewOr) ? "(" : ( (bNextOr) ? "((" : "(" );
      if (FWhereUser.Length() > 0) {
         sParFilter = ((bPrewOr) ? " OU " : " E ") + sParFilter;
         sParSQL = ((bPrewOr) ? " OR " : " AND ") + sParSQL;
      }
      //Definido o parenteses inicial vai executar os filtros
      for (ACol = 1; ACol < (grdAvancado->ColCount - 1); ACol++) {
         Filter = (SfgFilter*)grdAvancado->Objects[ACol][ARow];
         if (Filter == NULL)
            continue;
         if (Filter->Field != NULL && !Filter->Value.IsNull()) {
            Field = Filter->Field;
            String sValue = VarToStr(Filter->Value);
            String sSQLValue;
            sFieldName = (Field->Origin.Length() > 0) ? Field->Origin : Field->FieldName;
   
            // Texto, Número, Data e Hora
            if ((Field->DataType == ftString) ||
               (Field->DataType == ftWideString) ||
               (Field->DataType == ftFixedChar) ||
               (Field->DataType == ftSmallint)) {
               sValue = QuotedStr(sValue);
               sSQLValue = sValue;
            } else
            if ((Field->DataType == ftWord) ||
               (Field->DataType == ftInteger) ||
               (Field->DataType == ftAutoInc) ||
               (Field->DataType == ftLargeint) ||
               (Field->DataType == ftBoolean)) {
               sSQLValue = sValue;
            } else
            if ((Field->DataType == ftFloat) ||
               (Field->DataType == ftCurrency) ||
               (Field->DataType == ftBCD)) {
               sSQLValue = StringReplace(sValue, ",", ".", TReplaceFlags() << rfReplaceAll);
            } else 
            if (Field->DataType == ftDate) {
               TDateTime dDate = Filter->Value;
               sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate));
               sSQLValue = QuotedStr(FormatDateTime("yyyy-mm-dd",dDate));
            } else
            if (Field->DataType == ftTime) {
               sValue = QuotedStr(sValue);
               sSQLValue = sValue;
            }

            if (sFilterLine.Length() > 0) {
               sFilterLine = sFilterLine + " E ";
               sWhereLine = sWhereLine + " AND ";
            }
            sFilterLine += Field->DisplayLabel;
            sWhereLine += sFieldName;
            if (Filter->Like) {
               sSQLValue = StringReplace(sSQLValue, "*", "%", TReplaceFlags() << rfReplaceAll);
               if (Filter->Operator == "=") {
                  sFilterLine = sFilterLine + " CONTÉM " + sValue;
                  sWhereLine = sWhereLine + " LIKE " + sSQLValue;
               } else {
                  sFilterLine = sFilterLine + " NÃO CONTÉM " + sValue;
                  sWhereLine = sWhereLine + " NOT LIKE " + sSQLValue;
               }
            } else {
               if ((Field->DataType == ftDateTime) ||
                   (Field->DataType == ftTimeStamp)) {
                  //Deve verificar se informou data/hora ou somente data
                  TDateTime dDateTime = Filter->Value;
                  TDateTime dDate = DateOf(dDateTime);
                  bool bTime = (bool)((double)(dDateTime - dDate) > (double)0.0);
                  //Se possuir somente data deve verificar os limites do dia
                  if (!bTime) {
                     sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate));
                     sSQLValue = FormatDateTime("yyyy-mm-dd",dDate);
                     if (Filter->Operator == "=") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " >= '" + sSQLValue + " 00:00:00'";
                        sWhereLine = sWhereLine + " AND " + sFieldName + " <= '" + sSQLValue + " 23:59:59'";
                     } else
                     if (Filter->Operator == "!=") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " < '" + sSQLValue + " 00:00:00'";
                        sWhereLine = sWhereLine + " AND " + sFieldName + " > '" + sSQLValue + " 23:59:59'";
                     } else
                     if (Filter->Operator == ">=") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " " + Filter->Operator + " '" + sSQLValue + " 00:00:00'";
                     } else
                     if (Filter->Operator == ">") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " " + Filter->Operator + " '" + sSQLValue + " 23:59:59'";
                     } else
                     if (Filter->Operator == "<=") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " " + Filter->Operator + " '" + sSQLValue + " 23:59:59'";
                     } else
                     if (Filter->Operator == "<") {
                        sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                        sWhereLine = sWhereLine + " " + Filter->Operator + " '" + sSQLValue + " 00:00:00'";
                     }
                  } else {
                     sValue = QuotedStr(FormatDateTime("dd/mm/yyyy",dDate) + " " + TimeToStr(TimeOf(dDateTime)));
                     sSQLValue = QuotedStr(FormatDateTime("yyyy-mm-dd",dDate) + " " + TimeToStr(TimeOf(dDateTime)));
                     sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                     sWhereLine = sWhereLine + " " + Filter->Operator + " " + sSQLValue;
                  }
                  //Verificar
               } else {
                  sFilterLine = sFilterLine + " " + Filter->Operator + " " + sValue;
                  sWhereLine = sWhereLine + " " + Filter->Operator + " " + sSQLValue;
               }
            }
         } //Fim campo não é nulo
      } //Fim do for de colunas
      //Se teve algum filtro nesta linha
      if (sFilterLine.Length() > 0) {
         sFilterLine = sParFilter + sFilterLine;
         sWhereLine = sParSQL + sWhereLine;
         sParSQL = (!bPrewOr) ? ")" : ( (bNextOr) ? ")" : "))" );
         sFilterLine += sParSQL;
         sWhereLine += sParSQL;
         //Adicionando no filtro final
         FWhereUser += sFilterLine;
         FWhereSQL += sWhereLine;
      }
   } //Fim do for de linhas

   for (ARow = 1; ARow < grdOrder->RowCount; ARow++) {
      Order = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][ARow];
      if (Order->Field != NULL && Order->Order != SFG_ORDER_NONE) {
         sFieldName = (Order->Field->Origin.Length() > 0) ? Order->Field->Origin : Order->Field->FieldName;
         if (FOrderSQL.Length() == 0) {
            FOrderSQL = "ORDER BY";
            FOrderUser += "ORDENADO POR";
         } else {
            FOrderSQL += ",";
            FOrderUser += ",";
         }
         FOrderSQL = FOrderSQL + " " + sFieldName + " " + \
                    ((Order->Order == SFG_ORDER_ASC) ? "ASC" : "DESC");
         FOrderUser = FOrderUser + " " + Order->Field->DisplayLabel + " " + \
                    ((Order->Order == SFG_ORDER_ASC) ? "ASC" : "DESC");
      } //Fim campo não é nulo
   } //Fim do for de linhas

   if (FUseSql)
      StrResultFilter->Text = FWhereSQL + " " + FOrderSQL;
   else
      StrResultFilter->Text = FWhereUser + " " + FOrderUser;
}
//---------------------------------------------------------------------------
String __fastcall TfrmSearch::GetWhere()
{
   String Result = FWhereSQL;
   if (FWhereAdd.Length() > 0) {
      if (Result.Length() > 0)
         Result = Result + " " + FWhereAdd;
      else
         Result = FWhereAdd;
   }
   return Result;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::grdKeyPress(TObject *Sender, char &Key)
{
   TStringAlignGrid *pGrid = (TStringAlignGrid*)Sender;
   int ACol, ARow;
   if (pGrid->Row > 0) {
      if (FLastEditCtr != NULL) {
         FLastEditCtr->Visible = true;
         FLastEditCtr->SetFocus();
         FLastEditCtr->Perform(WM_CHAR,Key,0);
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::grdDblClick(TObject *Sender)
{
   TStringAlignGrid *pGrid = (TStringAlignGrid*)Sender;
   int ACol, ARow;
   TPoint Point = Mouse->CursorPos;
   Point = pGrid->ScreenToClient(Point);
   pGrid->MouseToCell(Point.x, Point.y, ACol, ARow);
   if (ARow > 0) {
      if (pGrid == grdBasico && ACol == GRD_BSC_VAL) {
         SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
         if (Filter->Field == NULL)
            return;
         TSfgMetaField *MetaField = (TSfgMetaField*)Filter->Field->Tag;
         if (MetaField->IsFkList) {
            TRect Rect = pGrid->CellRect(ACol, ARow);
            if (Point.x > (Rect.right - 20)) {
               OpenBrowse(Filter);
               return;
            }
         }
      }
      if (FLastEditCtr != NULL) {
         FLastEditCtr->Visible = true;
         FLastEditCtr->SetFocus();
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::btAddWhereClick(TObject *Sender)
{
   //Permite adicionar um comando customizado
   TForm *FormAdd = new TForm(Application);
   FormAdd->BorderStyle = bsDialog;
   FormAdd->BorderIcons = TBorderIcons() << biSystemMenu;
   FormAdd->Caption = "Comando Adicional";
   FormAdd->Position = poMainFormCenter;
   FormAdd->ClientHeight = 160;
   FormAdd->ClientWidth = 360;
   FormAdd->BorderWidth = 6;
   TMemo *MemoAdd = new TMemo(FormAdd);
   MemoAdd->Parent = FormAdd;
   MemoAdd->Align = alClient;
   MemoAdd->ScrollBars = ssVertical;
   MemoAdd->Text = FWhereAdd;
   FormAdd->ShowModal();
   FWhereAdd = MemoAdd->Text;
   delete FormAdd;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::btExibeClick(TObject *Sender)
{
   //Alterna entre a visualização do SQL ou a String do Filtro
   FUseSql = !FUseSql;
   if (FUseSql) {
      StrResultFilter->Text = FWhereSQL + " " + FOrderSQL;
      btExibe->Caption = "&Exibir Comando Usuário";
   } else {
      StrResultFilter->Text = FWhereUser + " " + FOrderUser;
      btExibe->Caption = "&Exibir Comando SQL";
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::grdBasicoDrawCell(TObject *Sender, int ACol,
      int ARow, TRect &Rect, TGridDrawState State)
{
   //Deve verificar se deve desenhar o botão de pesquisa no campo
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
   if (Filter->Field == NULL)
      return;
   TSfgMetaField *MetaField = (TSfgMetaField*)Filter->Field->Tag;
   if (MetaField->IsFkList && ACol == GRD_BSC_VAL) {
      DrawSearchGrid(grdBasico,-1,-1,Rect,State,false);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::OpenBrowse(SfgFilter *Filter)
{
   TField *Field;
   TSfgFieldDef *FieldDef;
   TSfgMetaField *MetaField = NULL;
   FFormBrowse = new TfrmBrowse(Application);
   String sSelect, sFrom, sOrder;
   TSfgMetaField *BrowseField = (TSfgMetaField*)Filter->Field->Tag;
   TSfgMetaTable *MetaTable = AddMetaTable(BrowseField->FkTableName);

   sSelect = "";
   sFrom = "FROM " + BrowseField->FkTableName;
   sOrder = "";
   //Montando o SELECT a ser utilizado no BROWSE
   for(int i = 0; i < MetaTable->FieldCount; i++) {
      MetaField = MetaTable->MetaFields[i];

      if ((MetaField->IsPkKey) || (MetaField->IsBrowse) ||
          (MetaField->FieldName == BrowseField->FkColumnName)) {
         FieldDef = CreateFieldDef(MetaField,FFormBrowse->DataSet);
         if (!(MetaField->IsBrowse))
            FieldDef->Visible = false;
         if (sSelect.Length() > 0) {
            sSelect += "," + MetaField->FieldName;
         } else {
            sSelect = "SELECT " + MetaField->FieldName;
         }
         if (MetaField->Order.InBrowse) {
            if (sOrder.Length() > 0) {
               sOrder += "," + MetaField->FieldName;
            } else {
               sOrder = "ORDER BY " + MetaField->FieldName;
            }
         }
      }
   }
   CreateFields(FFormBrowse->DataSet);
   FFormBrowse->SQL = sSelect + " " + sFrom + " " + sOrder;
   FFormBrowse->OnBrowseReturn = &BrowseReturn;
   FFormBrowse->ShowModal();
   delete FFormBrowse;
   FFormBrowse = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::BrowseReturn(Variant Value)
{
   SfgFilter *Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][grdBasico->Row];
   TSfgMetaField *BrowseField = (TSfgMetaField*)Filter->Field->Tag;
   Filter->Value = FFormBrowse->DataSet->FieldByName(BrowseField->FkColumnName)->Value;
   grdBasico->Cells[GRD_BSC_VAL][grdBasico->Row] = VarToStr(Filter->Value);
   MontaFiltro();
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SaveProfile()
{
   int ARow, ACol, APos;
   SfgFilter *Filter = NULL;
   SfgOrder *Order = NULL;
   String StrKey;
   String StrProfle = "";
   String StrFilter, StrOrder;
   int Line = 0;

   if (this->ParentForm == NULL)
      return;
   StrKey = ParentForm->Name + "_filter_basic";
   DeleteProfile(StrKey);
   StrProfle = "";
   //Montando primeiro todos os filtros básicos
   for (ARow = 1; ARow < grdBasico->RowCount; ARow++) {
      Filter = (SfgFilter*)grdBasico->Objects[GRD_BSC_PTR][ARow];
      if (Filter == NULL)
         continue;
      if (Filter->Field != NULL && !Filter->Value.IsNull()) {
         StrFilter = "{" + Filter->Field->FieldName + ";" + \
                     Filter->Operator + ";" + VarToStr(Filter->Value) + "}";
         if ((StrProfle.Length() + StrFilter.Length()) <= 255) {
            StrProfle += StrFilter;
         } else {
            //Deve salvar a linha corrente e iniciar um novo grupo de filtros
            Line++;
            SaveLineProfile(StrKey, Line, StrProfle);
            StrProfle = StrFilter;
         }
      } //Fim campo não é nulo
   } //Fim do for de linhas
   if (StrProfle.Length() > 0) {
      Line++;
      SaveLineProfile(StrKey, Line, StrProfle);
   }

   Line = 0;
   StrKey = ParentForm->Name + "_filter_advanced";
   DeleteProfile(StrKey);
   StrProfle = "";
   //Montando primeiro todos os filtros básicos
   for (ARow = 1; ARow < grdAvancado->RowCount; ARow++) {
      for (ACol = 1; ACol < (grdAvancado->ColCount - 1); ACol++) {
         Filter = (SfgFilter*)grdAvancado->Objects[ACol][ARow];
         if (Filter == NULL)
            continue;
         if (Filter->Field != NULL && !Filter->Value.IsNull()) {
            StrFilter = "{" + Filter->Field->FieldName + ";" + IntToStr(ARow) + ";" + \
                        Filter->Operator + ";" + VarToStr(Filter->Value) + ";" + \
                        grdAvancado->Cells[grdAvancado->ColCount - 1][ARow] + "}";
            if ((StrProfle.Length() + StrFilter.Length()) <= 255) {
               StrProfle += StrFilter;
            } else {
               //Deve salvar a linha corrente e iniciar um novo grupo de filtros
               Line++;
               SaveLineProfile(StrKey, Line, StrProfle);
               StrProfle = StrFilter;
            }
         } //Fim campo não é nulo
      } //Fim do for de colunas
   } //Fim do for de linhas
   if (StrProfle.Length() > 0) {
      Line++;
      SaveLineProfile(StrKey, Line, StrProfle);
   }

   Line = 0;
   StrKey = ParentForm->Name + "_filter_user";
   DeleteProfile(StrKey);
   StrProfle = "";
   APos = 1;
   while (APos <= FWhereAdd.Length()) {
      StrProfle = FWhereAdd.SubString(APos,APos+254);
      Line++;
      SaveLineProfile(StrKey, Line, StrProfle);
      APos += 255;
   }
   
   Line = 0;
   StrKey = ParentForm->Name + "_orderby";
   DeleteProfile(StrKey);
   StrProfle = "";
   //Refazendo a lista de ordenação customizzada
   for (ARow = 1; ARow < grdOrder->RowCount; ARow++) {
      Order = (SfgOrder*)grdOrder->Objects[GRD_ORD_PTR][ARow];
      if (Order == NULL)
         continue;
      if (Order->Field != NULL) {
         StrOrder = "{" + Order->Field->FieldName + ";" + IntToStr(Order->Order) + "}";
         if ((StrProfle.Length() + StrOrder.Length()) <= 255) {
            StrProfle += StrOrder;
         } else {
            //Deve salvar a linha corrente e iniciar um novo grupo de filtros
            Line++;
            SaveLineProfile(StrKey, Line, StrProfle);
            StrProfle = StrOrder;
         }
      } //Fim campo não é nulo
   } //Fim do for de linhas
   if (StrProfle.Length() > 0) {
      Line++;
      SaveLineProfile(StrKey, Line, StrProfle);
   }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::DeleteProfile(String StrKey)
{
	TZQuery *QyDelProfile;
try {
	QyDelProfile = new TZQuery(Application);
	QyDelProfile->Connection = AppConnection;
   QyDelProfile->ParamCheck = false;
   QyDelProfile->SQL->Text = "\
DELETE FROM tbl_profile_usuario\
 WHERE usuario = " + QuotedStr(AppUser->Usuario) + "\
   AND profile_key = " + QuotedStr(StrKey);
   QyDelProfile->ExecSQL();
	delete QyDelProfile;
} catch(Exception &e) {
	String MsgErro = "Ocorreu o seguinte erro ao excluir as informações do perfil:\n";
   MsgErro = MsgErro + e.Message;
   MessageBox(NULL,MsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::SaveLineProfile(String StrKey, int Line, String StrProfile)
{
	TZQuery *QySaveProfile;
try {
	QySaveProfile = new TZQuery(Application);
	QySaveProfile->Connection = AppConnection;
   QySaveProfile->ParamCheck = false;
   QySaveProfile->SQL->Text = "\
INSERT INTO tbl_profile_usuario\
       (usuario,profile_key,profile_line,profile_value) \
VALUES (" + QuotedStr(AppUser->Usuario) + "," + QuotedStr(StrKey) + "," + \
        IntToStr(Line) + "," + QuotedStr(StrProfile) + ")";
   QySaveProfile->ExecSQL();
	delete QySaveProfile;
} catch(Exception &e) {
	String MsgErro = "Ocorreu o seguinte erro ao salvar as informações do perfil:\n";
   MsgErro = MsgErro + e.Message;
   MessageBox(NULL,MsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TfrmSearch::btProfileClick(TObject *Sender)
{
   int Option = 0;
   TStrings *Buttons = new TStringList();
   Buttons->Add("Salvar=1");
   Buttons->Add("Excluir=2");
   Buttons->Add("Cancelar=3");

   Option = SfgMsgOption("Qual ação deverá ser executada com as configurações?",mtConfirmation,Buttons,"Pergunta",1,3);

   delete Buttons;

   if (Option == 3)
      return;

   if (Option == 1) { //Salvar as configurações
      SaveProfile();
   } else { //Excluir as configurações
      DeleteProfile(ParentForm->Name + "_filter_basic");
      DeleteProfile(ParentForm->Name + "_filter_advanced");
      DeleteProfile(ParentForm->Name + "_filter_user");
      DeleteProfile(ParentForm->Name + "_orderby");
   }
}
//---------------------------------------------------------------------------


