//---------------------------------------------------------------------------
#ifndef uVaParaH
#define uVaParaH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <DB.hpp>
class TSfgToolbar;
class SfgToolTips;
//---------------------------------------------------------------------------
class PACKAGE TSfgVaPara : public TForm
{
__published:	// IDE-managed Components
   TEdit *VaPara;
   TButton *btOK;
   TButton *btCancelar;
   TLabel *Label1;
   void __fastcall btOKClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   SfgToolTips* Tolltips;
	TField   *FPkField;
   TDataSet *FDataSet;
   void __fastcall SetDataSet(TDataSet *DataSet);
public:		// User declarations
   __property TDataSet *DataSet = { read=FDataSet, write=SetDataSet };
public:		// User declarations
   __fastcall TSfgVaPara(TComponent* Owner);
   void __fastcall(__closure *AfterGoToFind) ();
};
//---------------------------------------------------------------------------
extern PACKAGE TSfgVaPara *SfgVaPara;
//---------------------------------------------------------------------------
#endif
