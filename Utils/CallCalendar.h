#ifndef CallCalendarH
#define CallCalendarH
//---------------------------------------------------------------------------
extern "C" BOOL __declspec(dllexport) WINAPI AbrirCalendario(HWND hWndParent, HWND hWndEdit, LPTSTR lpString);
extern "C" BOOL __declspec(dllexport) WINAPI AbrirCalendarioRect(HWND hWndParent, LPRECT rectOrig, LPTSTR lpString);

BOOL WINAPI AbrirCalendario(HWND hWndParent, HWND hWndEdit, LPTSTR lpString);
BOOL WINAPI AbrirCalendarioRect(HWND hWndParent, LPRECT rectOrig, LPTSTR lpString);

//---------------------------------------------------------------------------
#endif
 