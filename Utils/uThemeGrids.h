//---------------------------------------------------------------------------
#include <System.hpp>
#include <Types.hpp>
#include <Windows.hpp>
#include <Messages.hpp>
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <Graphics.hpp>
#include <Controls.hpp>
#include <Grids.hpp>
#include <SfgAlignGrid.hpp>
#include <DbGrids.hpp>
#include <ThemeSrv.hpp>

  //Windows, Messages, SysUtils, Classes, Graphics, Controls, Grids,
  //DBGrids, DB, ImgList, SfgAlignGrid, ThemeSrv, Dialogs;
//---------------------------------------------------------------------------
#ifndef uThemedGridsH
#define uThemedGridsH
//---------------------------------------------------------------------------
namespace ThemeGrids
{

struct TPaintInfo
{
	int MouseInCol;
	bool ColPressed;
	int ColPressedIdx;
	bool ColSizing;
	bool ColMoving;
} ;

//---------------------------------------------------------------------------
class TDBGrid;
class TDBGrid : public Dbgrids::TDBGrid 
{
	typedef Dbgrids::TDBGrid inherited;
	
private:
	TPaintInfo FPaintInfo;
	Grids::TGridCoord FCell;
	bool FAllowTitleClick;
	Classes::TWndMethod FOldWndProcEdit;
	Classes::TNotifyEvent FOnEditSetFocus;
	int __fastcall CentreV(const Types::TRect &ARect, int ATextHeight);
	int __fastcall CentreH(const Types::TRect &ARect, int ATextWidth);
	//int __fastcall ColumnOffset(Dbgrids::TDBGridOptions AOptions);
	//int __fastcall TitleOffset(Dbgrids::TDBGridOptions AOptions);
	bool __fastcall ValidCell(const Grids::TGridCoord &ACell);
	bool __fastcall RowIsMultiSelected(void);
	
protected:
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	void __fastcall WndProcEdit(Messages::TMessage &Message);
	DYNAMIC bool __fastcall BeginColumnDrag(int &Origin, int &Destination, const Types::TPoint &MousePt);
	//DYNAMIC void __fastcall ColExit(void);
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	virtual void __fastcall DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint(void);
	//DYNAMIC void __fastcall TitleClick(Dbgrids::TColumn* Column);
	DYNAMIC void __fastcall ColWidthsChanged(void);
	//HIDESBASE bool __fastcall AcquireFocus(void);
	virtual Grids::TInplaceEdit* __fastcall CreateEditor(void);
	//DYNAMIC bool __fastcall DoMouseWheelDown(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	//DYNAMIC bool __fastcall DoMouseWheelUp(Classes::TShiftState Shift, const Types::TPoint &MousePos);
	//DYNAMIC bool __fastcall DoMouseWheel(Classes::TShiftState Shift, int WheelDelta, const Types::TPoint &MousePos);
	
public:
	__fastcall virtual TDBGrid(Classes::TComponent* AOwner);
	__property bool AllowTitleClick = {read=FAllowTitleClick, write=FAllowTitleClick, default=1};
	__property Classes::TNotifyEvent OnEditSetFocus = {read=FOnEditSetFocus, write=FOnEditSetFocus};
public:
	#pragma option push -w-inl
	/* TCustomDBGrid.Destroy */ inline __fastcall virtual ~TDBGrid(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TDBGrid(HWND ParentWindow) : Dbgrids::TDBGrid(ParentWindow) { }
	#pragma option pop
	
};


class TThemeDBGrid;
class TThemeDBGrid : public TDBGrid 
{
	typedef TDBGrid inherited;
	
__published:
	__property AllowTitleClick  = {default=1};
	__property OnEditSetFocus ;
public:
	#pragma option push -w-inl
	/* TDBGrid.Create */ inline __fastcall virtual TThemeDBGrid(Classes::TComponent* AOwner) : TDBGrid(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TCustomDBGrid.Destroy */ inline __fastcall virtual ~TThemeDBGrid(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TThemeDBGrid(HWND ParentWindow) : TDBGrid(ParentWindow) { }
	#pragma option pop
	
};

//---------------------------------------------------------------------------
class TStringAlignGrid;
class TStringAlignGrid : public SfgAlignGrid::TStringAlignGrid
{
	typedef SfgAlignGrid::TStringAlignGrid inherited;

private:
	TPaintInfo FPaintInfo;
	Grids::TGridCoord FCell;
	bool FAllowTitleClick;
	int __fastcall CentreV(const Types::TRect &ARect, int ATextHeight);
	int __fastcall CentreH(const Types::TRect &ARect, int ATextWidth);
	bool __fastcall ValidCell(const Grids::TGridCoord &ACell);

protected:
	HIDESBASE MESSAGE void __fastcall WMEraseBkgnd(Messages::TWMEraseBkgnd &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Messages::TMessage &Message);
	DYNAMIC bool __fastcall BeginColumnDrag(int &Origin, int &Destination, const Types::TPoint &MousePt);
	DYNAMIC void __fastcall ColumnMoved(int FromIndex, int ToIndex);
	DYNAMIC void __fastcall MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState);
	   
public:
	__fastcall virtual TStringAlignGrid(Classes::TComponent* AOwner);
	__property bool AllowTitleClick = {read=FAllowTitleClick, write=FAllowTitleClick, default=1};
public:
	#pragma option push -w-inl
	/* TStringAlignGrid.Destroy */ inline __fastcall virtual ~TStringAlignGrid(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TStringAlignGrid(HWND ParentWindow) : SfgAlignGrid::TStringAlignGrid(ParentWindow) { }
	#pragma option pop
	
};


class TThemeStringAlignGrid;
class TThemeStringAlignGrid : public TStringAlignGrid 
{
	typedef TStringAlignGrid inherited;
	
__published:
	__property AllowTitleClick  = {default=1};
public:
	#pragma option push -w-inl
	/* TStringAlignGrid.Create */ inline __fastcall virtual TThemeStringAlignGrid(Classes::TComponent* AOwner) : TStringAlignGrid(AOwner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TStringAlignGrid.Destroy */ inline __fastcall virtual ~TThemeStringAlignGrid(void) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TWinControl.CreateParented */ inline __fastcall TThemeStringAlignGrid(HWND ParentWindow) : TStringAlignGrid(ParentWindow) { }
	#pragma option pop
	
};
} // namespace ThemeGrids
using namespace ThemeGrids;
#endif
