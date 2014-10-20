#ifndef uSfgGlobalsH
#define uSfgGlobalsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------
#define APP_INFORM     MB_OK | MB_ICONINFORMATION
#define APP_ATENTION   MB_OK | MB_ICONEXCLAMATION
#define APP_ERROR      MB_OK | MB_ICONSTOP
#define APP_QUESTION   MB_YESNO | MB_ICONQUESTION
#define APP_CANCEL     MB_OKCANCEL | MB_ICONQUESTION

#define APP_PERM_TOTAL   2
#define APP_PERM_LEITURA 1

//---------------------------------------------------------------------------
const int crMais = 1;
const int VK_MAIS = 0x06B;

const String MesesAno[13] = {"Indefinido","Janeiro","Fevereiro","Março","Abril","Maio","Junho",
                            "Julho","Agosto","Setembro","Outubro","Novembro","Dezembro"};

const String CPFMask = "!000.000.000/00;0;_";
const String CNPJMask  = "!00.000.000/0000-00;0;_";

enum FIELD_DEF {
   FD_NONE = 0,
   FD_KEY = 1,
   FD_LIST = 2,
	FD_ORD = 4,
   FD_KEY_LIST = FD_KEY | FD_LIST
};

enum SMTP_CFG {
	CFG_NONE = 0,
	CFG_AUT = 1,
	CFG_SSL = 2
};
//---------------------------------------------------------------------------
#include "uSfgGlobals.h"
#include "uSfgToolTip.h"
#include "uSfgWorkEdition.h"
#include "uSfgMsgOption.h"
#include "uSfgDrawCmp.h"
#include "uSfgCalendar.h"
#include "uSfgTools.h"
//---------------------------------------------------------------------------
#endif


