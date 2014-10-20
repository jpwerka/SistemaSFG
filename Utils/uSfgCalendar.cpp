//---------------------------------------------------------------------------
#include <vcl.h>
#include <DBCtrls.hpp>
#include "CallCalendar.h"
#pragma comment(lib, "CallCalendar.lib")
#pragma hdrstop
#include "uSfgCalendar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
void ExecCalendar(TWinControl *Control)
{
	if(Control->InheritsFrom(__classid(TCustomEdit)))
	{
		char retorno[100];
		if( AbrirCalendario(Screen->ActiveForm->Handle, Control->Handle, retorno))
			if(!(GetWindowLong(Control->Handle, GWL_STYLE) & ES_READONLY)) {
				if (Control->InheritsFrom(__classid(TDBEdit))) {
					((TDBEdit*)Control)->Field->AsString = retorno;
				} else {
					((TCustomEdit*)Control)->Text = retorno;
				}
				Control->SetFocus();
			}
	}
}
//---------------------------------------------------------------------------
String ExecCalendarRect(TRect oRect, String sDate)
{
	String sReturn;
	char cReturn[100];
	ZeroMemory(cReturn,sizeof(char)*100);
	strcpy(cReturn,sDate.c_str());
	if(AbrirCalendarioRect(Screen->ActiveForm->Handle, &oRect, cReturn)) {
		sReturn = cReturn;
	}
	return sReturn;
}
//---------------------------------------------------------------------------
