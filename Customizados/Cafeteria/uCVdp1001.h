//---------------------------------------------------------------------------
#ifndef uCVdp1001H
#define uCVdp1001H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
namespace uCVdp1001
{
//---------------------------------------------------------------------------
bool ValidFormPgtoSenha(TForm *pForm);
bool AfterValidInsert(TForm *pForm, TDataSet *pDataSet);
//---------------------------------------------------------------------------
class TCVdp1001A : public TForm
{
public:
   void __fastcall BtOKClick(TObject *Sender);
private:
   TEdit *pEdtPdw;
   TLabel *pLabel;
   TButton *pBtOK;
   TButton *pBtCancel;
public:
   String cod_cliente;
	__fastcall TCVdp1001A(TComponent* Owner);
};
//---------------------------------------------------------------------------
} //end namespace uCVdp1001
#endif
