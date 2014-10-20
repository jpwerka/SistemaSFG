//---------------------------------------------------------------------------
#ifndef uObf1007H
#define uObf1007H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgAlignEdit.hpp"
//---------------------------------------------------------------------------
class SfgToolTips;
class TObf1007 : public TForm
{
__published:	// IDE-managed Components
   TGroupBox *GroupBox1;
   TAlignEdit *prox_num_nf;
   TLabel *Label1;
   TAlignEdit *serie_nf;
   TLabel *Label2;
   TButton *BtOk;
   TButton *BtCancel;
   void __fastcall BtOkClick(TObject *Sender);
   void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
   bool bExistNumNF;
   SfgToolTips* Tolltips;
   void GetNumeracaoNF();
   bool SetNumeracaoNF();
public:		// User declarations
   __fastcall TObf1007(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
