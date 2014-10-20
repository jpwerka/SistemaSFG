//---------------------------------------------------------------------------
#ifndef uCVdp1010H
#define uCVdp1010H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include "SfgResButtons.hpp"
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
namespace uCVdp1010
{
//---------------------------------------------------------------------------
void CreateButtonParametro(TForm *pForm);
//---------------------------------------------------------------------------
class TCVdp1010A : public TForm
{
public:
   void __fastcall BtOKClick(TObject *Sender);
private:
   TForm *pFormPgto;
   TAlignEdit *pEdtPgto;
   TLabel *pLabel;
   TButton *pBtOK;
   TButton *pBtCancel;
public:
	__fastcall TCVdp1010A(TComponent* Owner);
};
//---------------------------------------------------------------------------
} //end namespace uCVdp1010
#endif
