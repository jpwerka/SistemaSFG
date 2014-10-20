//---------------------------------------------------------------------------
#include <vcl.h>
#include "CustomDbControls.h"
#pragma hdrstop
#include "uSfgWorkEdition.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//Procedimento para impedir edições indesejadas
__fastcall SfgWorkEdition::SfgWorkEdition(TDataSource* DataSource, TWinControl* ParentWindow)
: System::TObject()
{
   this->AfterWorkEdition = NULL;
   this->FListControls = new TStringList();
   this->SetListControls(DataSource, ParentWindow);

//   ShowMessage(IntToStr(FListControls->Count));
//   for(int i=0; i<FListControls->Count;i++)
//      ShowMessage(FListControls->Strings[i]);
}
//---------------------------------------------------------------------------
__fastcall SfgWorkEdition::~SfgWorkEdition()
{
   delete(FListControls);
}
//---------------------------------------------------------------------------
//Pega todos os campos que usam o DataSource
void __fastcall SfgWorkEdition::SetListControls(TDataSource* DataSource, TWinControl* ParentWindow)
{
   int i,j;
   TControl *Control;
   SfgWorkField *WorkField;
   j = ParentWindow->ControlCount;
   for(i=0; i<j; i++) {
   try {
      Control = ParentWindow->Controls[i];
      if(Control == NULL)
         continue;
      if(Control->InheritsFrom(__classid(TWinControl))) {
      try {
         if(ParentWindow->ContainsControl(Control)) {
            SetListControls(DataSource, (TWinControl*)Control);
         }
      }
      __finally{}
      }
      if (Control->ClassNameIs("TDBEdit")) {
         if(((TDBEdit*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBEdit*)Control)->DataField);
				FListControls->AddObject(Control->Name, (TObject*)WorkField);
         }
      } else if (Control->ClassNameIs("TDBMemo")) {
         if(((TDBMemo*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBMemo*)Control)->DataField);
				FListControls->AddObject(Control->Name, (TObject*)WorkField);
         }
      } else if (Control->ClassNameIs("TDBComboBox")) {
         if(((TDBComboBox*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBComboBox*)Control)->DataField);
				FListControls->AddObject(Control->Name, (TObject*)WorkField);
         }
      } else if (Control->ClassNameIs("TDBLookupComboBox")) {
         if(((TDBLookupComboBox*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBLookupComboBox*)Control)->DataField);
				FListControls->AddObject(Control->Name, (TObject*)WorkField);
         }
      } else if (Control->ClassNameIs("TDBRadioGroup")) {
         if(((TDBRadioGroup*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBRadioGroup*)Control)->DataField);
				FListControls->AddObject(Control->Name, (TObject*)WorkField);
         }
      } else if (Control->ClassNameIs("TDBCheckBox")) {
         if(((TDBCheckBox*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBCheckBox*)Control)->DataField);
            FListControls->AddObject(Control->Name, (TObject*)WorkField);
			}
      } else if (Control->ClassNameIs("TDBDataComboBox")) {
         if(((TDBDataComboBox*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = DataSource->DataSet->FieldByName(((TDBDataComboBox*)Control)->DataField);
            FListControls->AddObject(Control->Name, (TObject*)WorkField);
			}
		}/* else if (Control->ClassNameIs("TEsDbDateEdit")) {
         if(((TEsDbDateEdit*)Control)->DataSource == DataSource) {
            WorkField = new SfgWorkField();
            WorkField->Control = Control;
            WorkField->Field = ((TEsDbDateEdit*)Control)->Field;
            FListControls->AddObject(Control->Name, (TObject*)WorkField);
            if (WorkField->Field->ProviderFlags.Contains(pfInKey)) {
               pListPkControls->AddObject(Control->Name, (TObject*)WorkField);
            }
         }
      }*/
   }
   __finally{}
   }
}
//---------------------------------------------------------------------------
//Procedimento para impedir edições indesejadas
void __fastcall SfgWorkEdition::SetWorkEdition(bool Enable, bool EnablePk, TColor Color)
{
   int i;
   SfgWorkField *WorkField;
   TControl *Control;
   for(i=0; i < FListControls->Count; i++) {
		WorkField = (SfgWorkField*) FListControls->Objects[i];
		if(WorkField == NULL)
			continue;
		if (!EnablePk && WorkField->Field->ProviderFlags.Contains(pfInKey))
			continue;
		if (Enable && WorkField->Field->AutoGenerateValue == arAutoInc)
			continue;
		if (Enable && !(WorkField->Field->ProviderFlags.Contains(pfInUpdate)||(WorkField->Field->ProviderFlags.Contains(pfInKey))))
			continue;
		Control = WorkField->Control;
      if (Control->ClassNameIs("TDBEdit")) {
         ((TDBEdit*)Control)->ReadOnly = !Enable;
			((TDBEdit*)Control)->Color = Color;
      } else if (Control->ClassNameIs("TDBMemo")) {
         ((TDBMemo*)Control)->ReadOnly = !Enable;
         ((TDBMemo*)Control)->Color = Color;
      } else if (Control->ClassNameIs("TDBComboBox")) {
         ((TDBComboBox*)Control)->ReadOnly = !Enable;
         ((TDBComboBox*)Control)->Color = Color;
      } else if (Control->ClassNameIs("TDBLookupComboBox")) {
         ((TDBLookupComboBox*)Control)->ReadOnly = !Enable;
         ((TDBLookupComboBox*)Control)->Color = Color;
      } else if (Control->ClassNameIs("TDBRadioGroup")) {
         ((TDBRadioGroup*)Control)->ReadOnly = !Enable;
      } else if (Control->ClassNameIs("TDBCheckBox")) {
         ((TDBCheckBox*)Control)->ReadOnly = !Enable;
      } else if (Control->ClassNameIs("TDBDataComboBox")) {
         ((TDBDataComboBox*)Control)->ReadOnly = !Enable;
         ((TDBDataComboBox*)Control)->Color = Color;
		}/* else if (Control->ClassNameIs("TEsDbDateEdit")) {
         ((TEsDbDateEdit*)Control)->ReadOnly = !Enable;
         ((TEsDbDateEdit*)Control)->Color = Color;
      }*/
	}
	if (Enable) {
		SetFieldFocus(EnablePk);
	}
   if (this->AfterWorkEdition != NULL) {
      this->AfterWorkEdition(Enable,Color);
   }
}
//---------------------------------------------------------------------------
void __fastcall SfgWorkEdition::SetFieldFocus(bool bFocusPk)
{
	int i;
	SfgWorkField *WorkField;
	TControl *Control;
	for(i=0; i < FListControls->Count; i++) {
		WorkField = (SfgWorkField*) FListControls->Objects[i];
		if(WorkField == NULL)
			continue;
		//Se o campo for autoincremento não coloca foco
		if(WorkField->Field->AutoGenerateValue == arAutoInc)
			continue;
		//Se é PK e não habilita PK
		if (!bFocusPk && WorkField->Field->ProviderFlags.Contains(pfInKey))
			continue;
		//Se o campo não é nem PK nem atualizável
		if (!WorkField->Field->ProviderFlags.Contains(pfInKey) && !WorkField->Field->ProviderFlags.Contains(pfInUpdate))
			continue;
		Control = WorkField->Control;
		if (Control->InheritsFrom(__classid(TWinControl))) {
			if (((TWinControl*)Control)->CanFocus()) {
				 ((TWinControl*)Control)->SetFocus();
				 break;
			}
		}
	}
}
//---------------------------------------------------------------------------

