/*
Módulo: Geral
Função: Funções desenhos de tela auxiliares
Autor.: Jackson Patrick Werka
Data..: 16/09/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
#include <vcl.h>
//---------------------------------------------------------------------------
#pragma hdrstop
#include "uSfgDrawCmp.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
Graphics::TBitmap *pBmpCheck = NULL;
Graphics::TBitmap *pBmpCalendar = NULL;
Graphics::TBitmap *pBmpSearch = NULL;
void LoadDrawBitmaps(void) {
	//Carregando a imagem do checkbox e configurando a mesma
	pBmpCheck = new Graphics::TBitmap();
	pBmpCheck->LoadFromResourceName((UINT)GetModuleHandle(NULL), "SFGCHECKBOX");
	pBmpCheck->Canvas->CopyMode = cmSrcCopy;
	//Carregando a imagem do calendario e configurando a mesma
	pBmpCalendar = new Graphics::TBitmap();
	pBmpCalendar->LoadFromResourceName((UINT)GetModuleHandle(NULL), "CALENDARH");
	pBmpCalendar->Canvas->CopyMode = cmSrcCopy;
	//Carregando a imagem da lupa de pesquisa e configurando a mesma
	pBmpSearch = new Graphics::TBitmap();
	pBmpSearch->LoadFromResourceName((UINT)GetModuleHandle(NULL), "PESQUISAM");
	pBmpSearch->Canvas->CopyMode = cmSrcCopy;
}
void FreeDrawBitmaps(void) {
	if (pBmpCheck != NULL) delete pBmpCheck;
	if (pBmpCalendar != NULL) delete pBmpCalendar;
	if (pBmpSearch != NULL) delete pBmpSearch;
}
#pragma startup LoadDrawBitmaps
#pragma exit FreeDrawBitmaps
//---------------------------------------------------------------------------
void __fastcall DrawCheckBoxGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bChecked)
{
	int iBmpPos;
	TGridCoord gcPos;
	THackCustomGrid *pHackGrid = (THackCustomGrid*)pGrid;
	TRect rSrc, rDest;

	if (pBmpCheck == NULL)
		return;

	if (ACol == -1 || ARow == -1) {
		gcPos = pHackGrid->MouseCoord(Rect.Left,Rect.Top);
		if (ACol == -1) ACol = gcPos.X;
		if (ARow == -1) ARow = gcPos.Y;
	}
	
	if (ARow >= pHackGrid->FixedRows) {
		if (bChecked) {
			if (State.Contains(gdSelected)) {
				iBmpPos = 7;
			} else if (State.Contains(gdFocused)) {
				iBmpPos = 6;
			} else {
				iBmpPos = 4;
			}
		} else {
			if (State.Contains(gdSelected)) {
				iBmpPos = 3;
			} else if (State.Contains(gdFocused)) {
				iBmpPos = 2;
			} else {
				iBmpPos = 0;
			}
		}
		try {
			rSrc.Top = 0;
			rSrc.Left = iBmpPos * (pBmpCheck->Width /8);
			rSrc.Bottom = pBmpCheck->Height;
			rSrc.Right = rSrc.Left + (pBmpCheck->Width /8);
			rDest.Top = Rect.Top + ((Rect.Height() - rSrc.Height()) / 2);
			rDest.Left = Rect.Left + ((Rect.Width() - rSrc.Width()) / 2);
			rDest.Bottom = rDest.Top + rSrc.Height();
			rDest.Right = rDest.Left + rSrc.Width();
			pHackGrid->Canvas->CopyRect(rDest,pBmpCheck->Canvas,rSrc);
		}
		__finally { /*Não faz nada*/ }
	}
}
//---------------------------------------------------------------------------
void __fastcall DrawCalendarGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bDrawText, String sText)
{
	int iBmpPos;
	TGridCoord gcPos;
	THackCustomGrid *pHackGrid = (THackCustomGrid*)pGrid;
	TRect rSrc, rDest;

	if (pBmpCalendar == NULL)
		return;

	if (ACol == -1 || ARow == -1) {
		gcPos = pHackGrid->MouseCoord(Rect.Left,Rect.Top);
		if (ACol == -1) ACol = gcPos.X;
		if (ARow == -1) ARow = gcPos.Y;
	}
	
	if (ARow >= pHackGrid->FixedRows) {
		if (!(pHackGrid->Enabled || pHackGrid->EditorMode)) {
			iBmpPos = 1;
		} else {
			if (State.Contains(gdSelected)) {
				iBmpPos = 2;
			} else if (State.Contains(gdFocused)) {
				iBmpPos = 2;
			} else {
				iBmpPos = 0;
			}
		}
		try {
			rSrc.Top = 0;
			rSrc.Left = iBmpPos * (pBmpCalendar->Width /4);
			rSrc.Bottom = pBmpCalendar->Height;
			rSrc.Right = rSrc.Left + (pBmpCalendar->Width /4);
			rDest.Top = Rect.Top + ((Rect.Height() - rSrc.Height()) / 2);
			rDest.Left = Rect.Right - (rSrc.Width() + 1);
			rDest.Bottom = rDest.Top + rSrc.Height();
			rDest.Right = Rect.Right - 1;
			pHackGrid->Canvas->BrushCopy(rDest,pBmpCalendar,rSrc,pBmpCalendar->Canvas->Pixels[0][0]);
		}
		__finally { /*Não faz nada*/ }
	}
}
//---------------------------------------------------------------------------
void __fastcall DrawSearchGrid(TCustomGrid *pGrid, int ACol, int ARow,
		TRect &Rect, TGridDrawState State, bool bDrawText, String sText)
{
	int iBmpPos;
	TGridCoord gcPos;
	THackCustomGrid *pHackGrid = (THackCustomGrid*)pGrid;
	TRect rSrc, rDest;

	if (pBmpSearch == NULL)
		return;

	if (ACol == -1 || ARow == -1) {
		gcPos = pHackGrid->MouseCoord(Rect.Left,Rect.Top);
		if (ACol == -1) ACol = gcPos.X;
		if (ARow == -1) ARow = gcPos.Y;
	}
	
	if (ARow >= pHackGrid->FixedRows) {
		if (!(pHackGrid->Enabled || pHackGrid->EditorMode)) {
			iBmpPos = 1;
		} else {
			if (State.Contains(gdSelected)) {
				iBmpPos = 2;
			} else if (State.Contains(gdFocused)) {
				iBmpPos = 2;
			} else {
				iBmpPos = 0;
			}
		}
		try {
			rSrc.Top = 0;
			rSrc.Left = iBmpPos * (pBmpSearch->Width /4);
			rSrc.Bottom = pBmpSearch->Height;
			rSrc.Right = rSrc.Left + (pBmpSearch->Width /4);
			rDest.Top = Rect.Top + ((Rect.Height() - rSrc.Height()) / 2);
			rDest.Left = Rect.Right - (rSrc.Width() + 1);
			rDest.Bottom = rDest.Top + rSrc.Height();
			rDest.Right = Rect.Right - 1;
			pHackGrid->Canvas->BrushCopy(rDest,pBmpSearch,rSrc,pBmpSearch->Canvas->Pixels[0][0]);
		}
		__finally { /*Não faz nada*/ }
	}
}

