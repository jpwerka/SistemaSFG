//---------------------------------------------------------------------------
#ifndef uFormBase02H
#define uFormBase02H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class PACKAGE TfrmBase02 : public TfrmBase01
{
__published:	// IDE-managed Components
   TSfgToolbar *SfgToolbar;
	TBevel *Bevel2;
private:	// User declarations
public:		// User declarations
	__fastcall TfrmBase02(TComponent* Owner);
	virtual void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
