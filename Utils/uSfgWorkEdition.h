//---------------------------------------------------------------------------
#ifndef uSfgWorkEditionH
#define uSfgWorkEditionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
typedef struct {
   TControl*  Control;
   TField*    Field;
} SfgWorkField;

class PACKAGE SfgWorkEdition : public System::TObject
{
private:
   TStrings*     FListControls;
   void __fastcall SetListControls(TDataSource* DataSource, TWinControl* ParentWindow);
public:
   __fastcall SfgWorkEdition(TDataSource* DataSource, TWinControl* ParentWindow);
   __fastcall ~SfgWorkEdition();
	__property TStrings* ListControls = {read=FListControls};
	void __fastcall SetWorkEdition(bool Enable, bool EnablePk, TColor Color);
	void __fastcall SetFieldFocus(bool FocusPk);
   void __fastcall(__closure *AfterWorkEdition) (bool Enable, TColor Color);
};
#endif
