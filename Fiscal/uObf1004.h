//---------------------------------------------------------------------------

#ifndef uObf1004H
#define uObf1004H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include "CustomDbControls.h"
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
class TObf1004 : public TForm
{
__published:	// IDE-managed Components
   TZQuery *QyEmpresa;
   TDBDataComboBox *cod_empresa;
   TLabel *Label1;
   TDataSource *DsEmpresa;
   TButton *btCancel;
   TButton *btOK;
   void __fastcall btOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
   __fastcall TObf1004(TComponent* Owner);
};
//---------------------------------------------------------------------------
#endif
