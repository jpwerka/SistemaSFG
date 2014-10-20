//---------------------------------------------------------------------------

#ifndef uRelatBase02H
#define uRelatBase02H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "frxClass.hpp"
//---------------------------------------------------------------------------
class PACKAGE TfrmRelatBase01 : public TForm
{
__published:	// IDE-managed Components
   TfrxReport *RpRelatBase;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
   void __fastcall RpRelatBaseBeginDoc(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TfrmRelatBase01(TComponent* Owner);
};
void AppPreviewReport(void *pReport);
//---------------------------------------------------------------------------
#endif
