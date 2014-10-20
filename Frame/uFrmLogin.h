//---------------------------------------------------------------------------
#ifndef uLoginH
#define uLoginH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TFrmLogin : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label3;
	TEdit *Login;
	TButton *btOK;
	TButton *btCancelar;
	TEdit *Senha;
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall btCancelarClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
	bool __fastcall UserValido();
	bool __fastcall SenhaValida();
	void __fastcall CarregaInfoUser();
   bool __fastcall CadastraUserAdm();
public:		// User declarations
	__fastcall TFrmLogin(TComponent* Owner);
	__fastcall ~TFrmLogin(void);
};
//---------------------------------------------------------------------------
#endif
 