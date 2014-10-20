//---------------------------------------------------------------------------
#ifndef uCFin1003AH
#define uCFin1003AH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
//---------------------------------------------------------------------------
namespace uCFin1003
{
//---------------------------------------------------------------------------
void Determina5DiaUtil(Word wMonth);
bool ValidFormPgtoSenha(TForm *pForm);
bool AfterValidInsert(TForm *pForm, TDataSet *pDataSet);
//---------------------------------------------------------------------------
class TCFin1003A : public TForm
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
	__fastcall TCFin1003A(TComponent* Owner);
};
//---------------------------------------------------------------------------
class TCFin1003B : public TForm
{
private:
   TImage *Image;
   TLabel *ClienteMsg;
   TLabel *LiberaMsg;
   TButton *pBtLibera;
   TButton *pBtCancel;
public:
   __fastcall TCFin1003B(TComponent* Owner, String sMsg);
};
//---------------------------------------------------------------------------
class TCFin1003C : public TForm
{
private:
   TImage *Image;
   TLabel *ClienteMsg;
   TLabel *LiberaMsg;
   TButton *pBtOK;
public:
   __fastcall TCFin1003C(TComponent* Owner, String sMsg);
};
//---------------------------------------------------------------------------
} //end namespace uFin1003
#endif
