//---------------------------------------------------------------------------
#ifndef uFormBase01H
#define uFormBase01H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class SfgToolTips;
//---------------------------------------------------------------------------
class PACKAGE TfrmBase01 : public TForm
{
__published:	// IDE-managed Components
	TPanel *HeaderPanel;
	TImage *Logotipo;
	TBevel *Bevel1;
   TPanel *BodyPanel;
   TPanel *MargemDir;
   TPanel *MargemEsq;
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
protected:
	inline virtual void __fastcall SetPermissao(int Nivel){};
	virtual void __fastcall DummyMethod(void *pVoid);
public:		// User declarations
	SfgToolTips *Tolltips;
	__fastcall TfrmBase01(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
