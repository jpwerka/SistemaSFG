//---------------------------------------------------------------------------
#ifndef ConverterQR2FRHPP
#define ConverterQR2FRHPP
//---------------------------------------------------------------------------
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit
#include <QuickRpt.hpp>	// Pascal unit
#include <QRCtrls.hpp>
#include <frxClass.hpp>	// Pascal unit
#include <frxRich.hpp>	// Pascal unit
//---------------------------------------------------------------------------
namespace Converterqr2fr
{
//-- type declarations -------------------------------------------------------
class TConverterQr2Fr : public System::TObject
{
	typedef System::TObject inherited;

private:
	Frxclass::TfrxReport* FTarget;
	Quickrpt::TQuickRep* FSource;

protected:
	void __fastcall CreateMainBands(void);
	void __fastcall CreateCustomBand(TQRCustomBand* ABand);
	void __fastcall AddObjects(TQRCustomBand* ABand, TfrxBand* Band);

public:
	__property TQuickRep* Source = {read=FSource, write=FSource};
	__property TfrxReport* Target = {read=FTarget, write=FTarget};
	void __fastcall Convert(void);
public:
	#pragma option push -w-inl
	/* TObject.Create */ inline __fastcall TConverterQr2Fr(void) : System::TObject() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TConverterQr2Fr(void) { }
	#pragma option pop
	
};
}	/* namespace Converterqr2fr */
using namespace Converterqr2fr;
#endif	// ConverterQR2FR 
