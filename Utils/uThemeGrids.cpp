//---------------------------------------------------------------------------
#pragma hdrstop
#include "uThemeGrids.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
namespace ThemeGrids
{
//---------------------------------------------------------------------------
__fastcall TDBGrid::TDBGrid(Classes::TComponent* AOwner)
	: Dbgrids::TDBGrid(Owner)
{
  FPaintInfo.ColPressed = false;
  FPaintInfo.MouseInCol = -1;
  FPaintInfo.ColPressedIdx = -1;
  FPaintInfo.ColMoving = false;
  FPaintInfo.ColSizing = false;
  FCell.X = -1;
  FCell.Y = -1;
  FAllowTitleClick = True;
}
//---------------------------------------------------------------------------
int __fastcall TDBGrid::CentreV(const Types::TRect &ARect, int ATextHeight)
{
	return (((ARect.Bottom - ARect.Top) - ATextHeight) / 2);
}
//---------------------------------------------------------------------------
int __fastcall TDBGrid::CentreH(const Types::TRect &ARect, int ATextWidth)
{
	return (((ARect.Right - ARect.Left) - ATextWidth) / 2);
}
//---------------------------------------------------------------------------
bool __fastcall TDBGrid::ValidCell(const Grids::TGridCoord &ACell)
{
	return ((ACell.X != -1) && (ACell.Y != -1));
}
//---------------------------------------------------------------------------
bool __fastcall TDBGrid::BeginColumnDrag(int &Origin, int &Destination, const Types::TPoint &MousePt)
{
	FPaintInfo.ColMoving = TCustomGrid::BeginColumnDrag(Origin, Destination, MousePt);
	return FPaintInfo.ColMoving;
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::ColumnMoved(int FromIndex, int ToIndex)
{
	TCustomGrid::ColumnMoved(FromIndex, ToIndex);
	FPaintInfo.ColMoving = false;
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
	TGridCoord lCell;
	if(!ComponentState.Contains(csDesigning)) {
		FPaintInfo.ColSizing = Sizing(X, Y);
		if (!FPaintInfo.ColSizing) {
			FPaintInfo.ColPressedIdx = -1;
			FPaintInfo.ColPressed = false;
			if (AllowTitleClick && Options.Contains(dgColumnResize)) {
				FPaintInfo.MouseInCol = -1;
			}
			lCell = MouseCoord(X,Y);
			if ((Button == mbLeft) && (lCell.X >= FixedCols) && (lCell.Y >= 0) && AllowTitleClick && Options.Contains(dgColumnResize)) {
				FPaintInfo.ColPressed = (lCell.Y < FixedRows);
				if (FPaintInfo.ColPressed) {
					FPaintInfo.ColPressedIdx = lCell.X; //  Columns[RawToDataColumn(lCell.X)].Index + ColumnOffset(Options);
				}
				if (ValidCell(FCell)) {
					InvalidateCell(FCell.X, FCell.Y);
				}
				FCell = lCell;
			}
		}
	}
	TCustomGrid::MouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
	TGridCoord lCell;
   int lMouseInCol;
   if(!ComponentState.Contains(csDesigning)) {
      if (!FPaintInfo.ColSizing && !FPaintInfo.ColMoving) {
         FPaintInfo.MouseInCol = -1;
         lCell = MouseCoord(X,Y);
         if ((lCell.X != FCell.X) || (lCell.Y != FCell.Y)) {
            if ((lCell.X >= FixedCols) && (lCell.Y >= 0)) {
			      if (lCell.Y < FixedRows) {
				      lMouseInCol = lCell.Y;
                  if (lMouseInCol != FPaintInfo.MouseInCol) {
                     InvalidateCell(lCell.X, lCell.Y);
                  }
                  FPaintInfo.MouseInCol = lMouseInCol;
               }
				}
			}
		   if (ValidCell(FCell))
            InvalidateCell(FCell.X, FCell.Y);
         FCell = lCell;
      }
   }
   TCustomGrid::MouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   TCustomGrid::MouseUp(Button, Shift, X, Y);
   FPaintInfo.ColSizing = false;
   FPaintInfo.ColMoving = false;
   FPaintInfo.ColPressedIdx = -1;
   FCell.X = -1;
   FCell.Y = -1;
   Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::CMMouseEnter(Messages::TMessage &Message)
{
	TGridCoord lCell;
	TPoint lPt;
	lPt = Point(Mouse->CursorPos.x, Mouse->CursorPos.y);
	lPt = ScreenToClient(lPt);
	lCell = MouseCoord(lPt.x, lPt.y);
	if ((FixedRows > 0) && (lCell.Y == 0)) {
		InvalidateCell(lCell.X, lCell.Y);
   }
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::CMMouseLeave(Messages::TMessage &Message)
{
	if (ValidCell(FCell)) {
		InvalidateCell(FCell.X, FCell.Y);
   }
	FCell.X = -1;
	FCell.Y = -1;
	FPaintInfo.MouseInCol = -1;
	FPaintInfo.ColPressedIdx = -1;
}
//---------------------------------------------------------------------------
void __fastcall TDBGrid::WMEraseBkgnd(Messages::TWMEraseBkgnd &Message)
{
	TRect R;
	TSize Size;
	// Fill the area between the two scroll bars.
	Size.cx = ::GetSystemMetrics(SM_CXVSCROLL);
	Size.cy = ::GetSystemMetrics(SM_CYHSCROLL);
	if (UseRightToLeftAlignment()) {
		R = Bounds(0, Height - Size.cy, Size.cx, Size.cy);
   } else {
		R = Bounds(Width - Size.cx, Height - Size.cy, Size.cx, Size.cy);
   }
	FillRect(Message.DC, &R, this->Brush->Handle);
	Message.Result = 1; // the grid paints its content in the Paint method
}


//---------------------------------------------------------------------------
__fastcall TStringAlignGrid::TStringAlignGrid(Classes::TComponent* AOwner)
	: SfgAlignGrid::TStringAlignGrid(Owner)
{
  FPaintInfo.ColPressed = false;
  FPaintInfo.MouseInCol = -1;
  FPaintInfo.ColPressedIdx = -1;
  FPaintInfo.ColMoving = false;
  FPaintInfo.ColSizing = false;
  FCell.X = -1;
  FCell.Y = -1;
  FAllowTitleClick = True;
  ShowMessage("Teste");
}
//---------------------------------------------------------------------------
int __fastcall TStringAlignGrid::CentreV(const Types::TRect &ARect, int ATextHeight)
{
	return (((ARect.Bottom - ARect.Top) - ATextHeight) / 2);
}
//---------------------------------------------------------------------------
int __fastcall TStringAlignGrid::CentreH(const Types::TRect &ARect, int ATextWidth)
{
	return (((ARect.Right - ARect.Left) - ATextWidth) / 2);
}
//---------------------------------------------------------------------------
bool __fastcall TStringAlignGrid::ValidCell(const Grids::TGridCoord &ACell)
{
	return ((ACell.X != -1) && (ACell.Y != -1));
}
//---------------------------------------------------------------------------
bool __fastcall TStringAlignGrid::BeginColumnDrag(int &Origin, int &Destination, const Types::TPoint &MousePt)
{
	FPaintInfo.ColMoving = TCustomGrid::BeginColumnDrag(Origin, Destination, MousePt);
	return FPaintInfo.ColMoving;
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::ColumnMoved(int FromIndex, int ToIndex)
{
	TCustomGrid::ColumnMoved(FromIndex, ToIndex);
	FPaintInfo.ColMoving = false;
	Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::MouseDown(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
	TGridCoord lCell;
	if(!ComponentState.Contains(csDesigning)) {
		FPaintInfo.ColSizing = Sizing(X, Y);
		if (!FPaintInfo.ColSizing) {
			FPaintInfo.ColPressedIdx = -1;
			FPaintInfo.ColPressed = false;
			if (AllowTitleClick && Options.Contains(goColMoving)) {
				FPaintInfo.MouseInCol = -1;
			}
			lCell = MouseCoord(X,Y);
			if ((Button == mbLeft) && (lCell.X >= FixedCols) && (lCell.Y >= 0) && AllowTitleClick && Options.Contains(goColMoving)) {
				FPaintInfo.ColPressed = (lCell.Y < FixedRows);
				if (FPaintInfo.ColPressed) {
					FPaintInfo.ColPressedIdx = lCell.X; //  Columns[RawToDataColumn(lCell.X)].Index + ColumnOffset(Options);
				}
				if (ValidCell(FCell)) {
					InvalidateCell(FCell.X, FCell.Y);
				}
				FCell = lCell;
			}
		}
	}
	TCustomGrid::MouseDown(Button, Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::MouseMove(Classes::TShiftState Shift, int X, int Y)
{
	TGridCoord lCell;
   int lMouseInCol;
   if(!ComponentState.Contains(csDesigning)) {
      if (!FPaintInfo.ColSizing && !FPaintInfo.ColMoving) {
         FPaintInfo.MouseInCol = -1;
         lCell = MouseCoord(X,Y);
         if ((lCell.X != FCell.X) || (lCell.Y != FCell.Y)) {
            if ((lCell.X >= FixedCols) && (lCell.Y >= 0)) {
			      if (lCell.Y < FixedRows) {
				      lMouseInCol = lCell.Y;
                  if (lMouseInCol != FPaintInfo.MouseInCol) {
                     InvalidateCell(lCell.X, lCell.Y);
                  }
                  FPaintInfo.MouseInCol = lMouseInCol;
               }
				}
			}
		   if (ValidCell(FCell))
            InvalidateCell(FCell.X, FCell.Y);
         FCell = lCell;
      }
   }
   TCustomGrid::MouseMove(Shift, X, Y);
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::MouseUp(Controls::TMouseButton Button, Classes::TShiftState Shift, int X, int Y)
{
   TCustomGrid::MouseUp(Button, Shift, X, Y);
   FPaintInfo.ColSizing = false;
   FPaintInfo.ColMoving = false;
   FPaintInfo.ColPressedIdx = -1;
   FCell.X = -1;
   FCell.Y = -1;
   Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::CMMouseEnter(Messages::TMessage &Message)
{
	TGridCoord lCell;
	TPoint lPt;
	lPt = Point(Mouse->CursorPos.x, Mouse->CursorPos.y);
	lPt = ScreenToClient(lPt);
	lCell = MouseCoord(lPt.x, lPt.y);
	if ((FixedRows > 0) && (lCell.Y == 0)) {
		InvalidateCell(lCell.X, lCell.Y);
   }
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::CMMouseLeave(Messages::TMessage &Message)
{
	if (ValidCell(FCell)) {
		InvalidateCell(FCell.X, FCell.Y);
   }
	FCell.X = -1;
	FCell.Y = -1;
	FPaintInfo.MouseInCol = -1;
	FPaintInfo.ColPressedIdx = -1;
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::WMEraseBkgnd(Messages::TWMEraseBkgnd &Message)
{
	TRect R;
	TSize Size;
	// Fill the area between the two scroll bars.
	Size.cx = ::GetSystemMetrics(SM_CXVSCROLL);
	Size.cy = ::GetSystemMetrics(SM_CYHSCROLL);
	if (UseRightToLeftAlignment()) {
		R = Bounds(0, Height - Size.cy, Size.cx, Size.cy);
   } else {
		R = Bounds(Width - Size.cx, Height - Size.cy, Size.cx, Size.cy);
   }
	FillRect(Message.DC, &R, this->Brush->Handle);
	Message.Result = 1; // the grid paints its content in the Paint method
}
//---------------------------------------------------------------------------
void __fastcall TStringAlignGrid::DrawCell(int ACol, int ARow, const Types::TRect &ARect, Grids::TGridDrawState AState)
{
	TThemedElementDetails Details;
	TRect lCaptionRect, lCellRect;
	String lStr;
	TPenRecall *PenRecall;
	bool MultiSelected;
	int OldActive;
	int Indicator;
	//Indicators: TImageList;
	int TextX, TextY;

	lCellRect = ARect;
	if ((ARow < FixedRows) && ((ACol - FixedCols) >= 0) && (FixedRows > 0) && ThemeServices()->ThemesEnabled) {
		lCaptionRect = ARect;
		if (!FPaintInfo.ColPressed || (FPaintInfo.ColPressedIdx != ACol)) {
			if ((FPaintInfo.MouseInCol == -1) || (FPaintInfo.MouseInCol != ACol) || (ComponentState.Contains(csDesigning))) {
				Details = ThemeServices()->GetElementDetails(thHeaderItemNormal);
         } else {
				Details = ThemeServices()->GetElementDetails(thHeaderItemHot);
			}
			lCellRect.Right = lCellRect.Right + 1;
			lCellRect.Bottom = lCellRect.Bottom + 2;
		}
		else if (AllowTitleClick && Options.Contains(goColMoving)) {
			Details = ThemeServices()->GetElementDetails(thHeaderItemPressed);
			InflateRect(&lCaptionRect, -1, 1);
		} else {
			if (FPaintInfo.MouseInCol == ACol) { 
				Details = ThemeServices()->GetElementDetails(thHeaderItemHot);
			} else {
				Details = ThemeServices()->GetElementDetails(thHeaderItemNormal);
			}
		}
	//void __fastcall DrawElement(HDC DC, const TThemedElementDetails &Details, const Types::TRect &R, Types::PRect ClipRect = (void *)(0x0));
		//ThemeServices()->DrawElement(Canvas->Handle, Details, lCellRect);
		Canvas->Brush->Style = bsClear;
		Canvas->Font->Assign(this->GetFontCell(ACol, ARow));
		lStr = this->Cells[ACol][ARow];
		TextY = lCaptionRect.Top + CentreV(lCaptionRect, Canvas->TextHeight(lStr));
		switch (this->GetAlignCell(ACol, ARow)) {
			case SfgAlignGrid::alRight:
				TextX = lCaptionRect.Right - 2 - Canvas->TextWidth(lStr);
				break;
			case SfgAlignGrid::alCenter:
				TextX = lCaptionRect.Left + CentreH(lCaptionRect, Canvas->TextWidth(lStr));
				break;
			default:
				TextX = lCaptionRect.Left + 2;
		}
		Canvas->TextRect(lCaptionRect, TextX, TextY, lStr);
   }
	else if ((ACol < FixedCols) && (FixedCols > 0) && ThemeServices()->ThemesEnabled) {
      // indicator column
		if (ARow < FixedRows) {
			Details = ThemeServices()->GetElementDetails(thHeaderItemNormal);
		} else {
			Details = ThemeServices()->GetElementDetails(thHeaderRoot);
      }
		lCellRect.Right = lCellRect.Right + 1;
		lCellRect.Bottom = lCellRect.Bottom + 2;
		//ThemeServices()->DrawElement(Canvas->Handle, Details, lCellRect);
   }
   else {
		SfgAlignGrid::TStringAlignGrid::DrawCell(ACol, ARow, ARect, AState);
	}
}

//---------------------------------------------------------------------------
const vmtNewInstance = System::vmtNewInstance;
void *OrgTAlignStringGrid_NewInstance;

typedef TObject* __fastcall(*NewInstance)(TMetaClass *AClass);

TObject* TAlignStringGrid_NewInstance(TMetaClass *AClass) {
   TComponent *Instance;
   AClass = __classid(ThemeGrids::TStringAlignGrid);
   //void *pFunc =  (void*)((int)AClass + vmtNewInstance);
   //NewInstance pNewInstance = (NewInstance)pFunc;
   //return pNewInstance(AClass);
   //MessageBox(NULL,IntToStr((int)pFunc).c_str(),"PatchAddress",0);
   //TStringAlignGrid->NewInstance();
   //return AClass->InitInstance();

   //TComponent *Instance;
   //Application->CreateForm(AClass, &Instance);
   //ShowMessage("Teste");
   //return Instance;
   //return AClass->InitInstance(GetMemory(AClass->InstanceSize()));
   Application->CreateForm(__classid(ThemeGrids::TStringAlignGrid),&Instance);
   return Instance;
}

void* __fastcall GetVirtualMethod(TMetaClass* AClass) {
   return AClass->MethodAddress("NewInstance");
}

void* __fastcall GetVirtualMethod(TMetaClass* AClass, const int VmtOffset) {
   return (void*)((int)AClass + VmtOffset);
}

//void * __fastcall GetVirtualMethod(TMetaClass* AClass, const int VmtOffset);
void __fastcall SetVirtualMethod(TMetaClass* AClass, const int VmtOffset, const void* Method) {
   void *PatchAddress;
   DWORD WrittenBytes;

   PatchAddress = (void*)((int)AClass + VmtOffset);
   WriteProcessMemory(GetCurrentProcess(), PatchAddress, &Method, sizeof(Method), &WrittenBytes);
   //MessageBox(NULL,IntToStr((int)PatchAddress).c_str(),"PatchAddress",0);
   //MessageBox(NULL,IntToStr((int)Method).c_str(),"Method",0);
   //MessageBox(NULL,IntToStr((int)WrittenBytes).c_str(),"WrittenBytes",0);
}

void WriteNewGridMethods(void) {
   void *PatchAddress;
   DWORD WrittenBytes;

   OrgTAlignStringGrid_NewInstance = GetVirtualMethod(__classid(SfgAlignGrid::TStringAlignGrid),vmtNewInstance);
   SetVirtualMethod(__classid(SfgAlignGrid::TStringAlignGrid), vmtNewInstance, &TAlignStringGrid_NewInstance);
   //OrgTAlignStringGrid_NewInstance = GetVirtualMethod(__classid(ThemeGrids::TStringAlignGrid));
   //PatchAddress = GetVirtualMethod(__classid(SfgAlignGrid::TStringAlignGrid));
   //PatchAddress = GetVirtualMethod(,vmtNewInstance);
   //MessageBox(NULL,IntToStr((int)PatchAddress).c_str(),"Teste",0);
   //WriteProcessMemory(GetCurrentProcess(), PatchAddress, &TAlignStringGrid_NewInstance, sizeof(TAlignStringGrid_NewInstance), &WrittenBytes);
}
void WriteOldGridMethods(void) {
   void *PatchAddress;
   DWORD WrittenBytes;

   //OrgTAlignStringGrid_NewInstance = GetVirtualMethod(__classid(ThemeGrids::TStringAlignGrid));
   PatchAddress = GetVirtualMethod(__classid(SfgAlignGrid::TStringAlignGrid));
   WriteProcessMemory(GetCurrentProcess(), PatchAddress, &OrgTAlignStringGrid_NewInstance, sizeof(OrgTAlignStringGrid_NewInstance), &WrittenBytes);
}
//---------------------------------------------------------------------------
#pragma startup WriteNewGridMethods
#pragma exit WriteOldGridMethods
//---------------------------------------------------------------------------

/*
{ TStringAlignGrid }

{
function TStringAlignGrid.AcquireFocus: Boolean;
begin
  Result := True;
  if FAcquireFocus and CanFocus and not (csDesigning in ComponentState) then
  begin
	 SetFocus;
	 Result := Focused || ((InplaceEditor != nil) and InplaceEditor.Focused);
  end;
end;
}



{
procedure TStringAlignGrid.ColExit;
begin
  inherited ColExit;
  FPaintInfo.MouseInCol := -1;
  if ValidCell(FCell) then
	 InvalidateCell(FCell.X, FCell.Y);
end;
}

{procedure TStringAlignGrid.TitleClick(Column: TColumn);
begin
  inherited TitleClick(Column);
  if AllowTitleClick then
  begin
	 FPaintInfo.ColPressed := False;
	 FPaintInfo.ColPressedIdx := -1;
	 if ValidCell(FCell) then
		InvalidateCell(FCell.X, FCell.Y);
  end;
end;}

*/

};
