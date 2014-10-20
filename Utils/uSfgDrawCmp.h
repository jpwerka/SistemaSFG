/*
Módulo: Geral
Função: Funções desenhos de tela auxiliares
Autor.: Jackson Patrick Werka
Data..: 16/09/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include <DBCtrls.hpp>
//---------------------------------------------------------------------------
#ifndef uSfgDrawCmpH
#define uSfgDrawCmpH
//---------------------------------------------------------------------------
class THackCustomGrid : public TCustomGrid
{
public:
	__property Col;
	__property Row;
	__property FixedCols;
	__property FixedRows;
	__property RowCount;
	__property Canvas;
	__property EditorMode;
	__property InplaceEditor;
	Types::TRect inline __fastcall CellRect(int ACol, int ARow){return TCustomGrid::CellRect(ACol,ARow);};
};
//TDrawGrid
//---------------------------------------------------------------------------
extern PACKAGE void __fastcall DrawCheckBoxGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bChecked);
extern PACKAGE void __fastcall DrawCalendarGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bDrawText, const String sText = "");
extern PACKAGE void __fastcall DrawSearchGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bDrawText, const String sText = "");
#endif
