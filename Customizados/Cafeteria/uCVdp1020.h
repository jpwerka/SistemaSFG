//---------------------------------------------------------------------------
#ifndef uCVdp1020H
#define uCVdp1020H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
namespace uCVdp1020
{
//---------------------------------------------------------------------------
void CreateButtonSenha(TForm *pForm);
void CreateFieldInadimplente(TForm *pForm);
//---------------------------------------------------------------------------
class TCVdp1020A : public TForm
{
__published:	// IDE-managed Components
   TLabel *Label1;
   TLabel *Label2;
   TEdit *edtPdw;
   TEdit *edtCfm;
   TButton *btOK;
   TButton *btCancel;
   void __fastcall btOKClick(TObject *Sender);
private:	// User declarations
   bool __fastcall SalvarSenha();
public:		// User declarations
   __fastcall TCVdp1020A(TComponent* Owner);
};
//---------------------------------------------------------------------------
} //end namespace uCVdp1020
#endif
