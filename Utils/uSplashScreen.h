//---------------------------------------------------------------------------
#ifndef uSplashScreenH
#define uSplashScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TSplahScreen : public TForm
{
__published:	// IDE-managed Components
	TProgressBar *InitProgress;
	TLabel *Label1;
   TImage *Image1;
private:	// User declarations
public:		// User declarations
	__fastcall TSplahScreen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSplahScreen *SplahScreen;
//---------------------------------------------------------------------------
#endif
