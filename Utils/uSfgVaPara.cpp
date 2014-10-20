//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgToolTip.h"
#include "uSfgBrowse.h"
#pragma hdrstop
#include "uSfgVaPara.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSfgVaPara *SfgVaPara;
//---------------------------------------------------------------------------
__fastcall TSfgVaPara::TSfgVaPara(TComponent* Owner)
        : TForm(Owner)
{
	Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
	Tolltips->CreateToolTips();
	VaPara->Color = AppConfig->Colors->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSfgVaPara::SetDataSet(TDataSet *DataSet)
{
   int i = 0;
   TField *Field;
   this->FDataSet = DataSet;
   for(i=0; i < DataSet->FieldCount; i++) {
      Field = DataSet->Fields->Fields[i];
      if (Field->ProviderFlags.Contains(pfInKey)) {
         FPkField = Field;
         break;
      }
   }
}
//---------------------------------------------------------------------------
void __fastcall TSfgVaPara::btOKClick(TObject *Sender)
{
   bool bRet;
   if(VaPara->Text.Length()){
      bRet = FDataSet->Locate(FPkField->FieldName, Variant(this->VaPara->Text), TLocateOptions());
   if(!bRet){
      MessageBox(Handle,"Registro não encontrado!","Vá Para",APP_INFORM);
      VaPara->SetFocus();
   }
   else{
      if(AfterGoToFind != NULL) {
         AfterGoToFind();
      }
      Close();
   }
 }
 else{
   MessageBox(Handle,"Entre com um código para efetuar a procura!","Vá Para",APP_ATENTION);
   VaPara->SetFocus();
 } 
}
//---------------------------------------------------------------------------
void __fastcall TSfgVaPara::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	delete Tolltips;
	Action = caFree;
	SfgVaPara = NULL;
}
//---------------------------------------------------------------------------

