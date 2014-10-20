#include <windows.h>
#include <commctrl.h>
#include <comdef.h>
#include <wbemidl.h>
#pragma comment(lib, "bcbatl.lib")
#pragma comment(lib, "wbemuuid.lib")

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
char* GetFirstSerialLic(char *ErrorMsg);

static HWND hwndGroup = 0;
static HWND hwndEdit = 0;
static HWND hwndMain = 0;

/*  Make the class name into a global variable  */
char szClassName[ ] = "SfgLicenceIDApp";

//---------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
   MSG messages;            /* Here messages to the application are saved */
   WNDCLASSEX wincl;        /* Data structure for the windowclass */
	SIZE sz;

   wincl.hInstance = hInstance;
   wincl.lpszClassName = szClassName;
   wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
   wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
   wincl.cbSize = sizeof (WNDCLASSEX);
   wincl.hIcon = LoadIcon (hInstance, "MAINICON");
   wincl.hIconSm = LoadIcon (hInstance, "MAINICON");
   wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
   wincl.lpszMenuName = NULL;                 /* No menu */
   wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
   wincl.cbWndExtra = 0;                      /* structure or the window instance */
   wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);

   if (!RegisterClassEx (&wincl))
      return 0;
	InitCommonControls();
	sz.cx =  GetSystemMetrics(SM_CXSCREEN);
	sz.cy =  GetSystemMetrics(SM_CYSCREEN);
   hwndMain = CreateWindowEx (0, szClassName,"Licença SFG",DS_SYSMODAL | DS_MODALFRAME | DS_CENTER | WS_CAPTION | WS_SYSMENU,        /* Windows decides the position */
		   (sz.cx/2)-100, (sz.cy/2)-50, 200, 96, HWND_DESKTOP, NULL, hInstance, NULL);
	ShowWindow (hwndMain, nFunsterStil);

    while (GetMessage (&messages, NULL, 0, 0))
	{
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
	return messages.wParam;
}
 
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)                  /* handle the messages */
	{
		case WM_CREATE:
			hwndGroup = CreateWindowEx (WS_EX_TRANSPARENT, "BUTTON","&Identificador Máquina:",BS_GROUPBOX | WS_CHILD | WS_VISIBLE | WS_GROUP,
				6, 6, 178, 45,hwnd,(HMENU) -1,((LPCREATESTRUCT) lParam)->hInstance, NULL);
         SendMessage(hwndGroup,WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(TRUE,0));
			hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE,"EDIT","0", WS_CHILD|WS_TABSTOP|WS_VISIBLE|ES_CENTER|ES_READONLY,
				14, 22, 160, 21, hwnd,(HMENU)2000, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
         SendMessage(hwndEdit,WM_SETFONT,(WPARAM)GetStockObject(DEFAULT_GUI_FONT),MAKELPARAM(TRUE,0));
			break;
		case WM_SHOWWINDOW:
         {
         char ErrorMsg[255];
         char *pFirstSerial = GetFirstSerialLic(ErrorMsg);
         if (pFirstSerial != NULL) {
            SendMessage(hwndEdit,WM_SETTEXT,0,(LPARAM)pFirstSerial);
            HeapFree(GetProcessHeap(),0,pFirstSerial);
         } else {
            MessageBox(hwnd,ErrorMsg,"Identificador Máquina", MB_OK | MB_ICONSTOP);
         }
         }
         break;

		case WM_DESTROY:
			PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
			break;
		default:                      /* for messages that we don't deal with */
			return DefWindowProc (hwnd, message, wParam, lParam);
	} 
	return 0;
}
//---------------------------------------------------------------------------
char* ConvertBSTRToStringEx(WCHAR* pSrc)
{
	char *Temp;
	int T = SysStringLen(pSrc)+1;
	Temp = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,T*sizeof(char));
	WideCharToMultiByte(CP_ACP,0,pSrc,T,Temp,T,NULL,NULL);
	return Temp;
}
//---------------------------------------------------------------------------
void __stdcall _com_issue_error(HRESULT hr) throw(_com_error)
{
   RaiseException(EXCEPTION_NONCONTINUABLE_EXCEPTION, EXCEPTION_NONCONTINUABLE, 
		1, (ULONG_PTR *)&hr);
}
void __stdcall _com_issue_errorex(HRESULT hr, IUnknown* pu, REFIID ref) throw(_com_error)
{
	RaiseException(EXCEPTION_NONCONTINUABLE_EXCEPTION, EXCEPTION_NONCONTINUABLE, 
		1, (ULONG_PTR *)&hr);
}
//---------------------------------------------------------------------------
char* GetFirstSerialLic(char *ErrorMsg) {
   HRESULT hres;
   char *cRet = NULL;

   // Initialize COM.
   hres = CoInitialize(NULL); //CoInitializeEx(0, COINIT_MULTITHREADED);
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao inicializar a biblioteca COM. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     return NULL;              // Program has failed.
   }
   
   // Initialize 
   hres =  CoInitializeSecurity(
       NULL,     
       -1,      // COM negotiates service                  
       NULL,    // Authentication services
       NULL,    // Reserved
       RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
       RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
       NULL,             // Authentication info 
       EOAC_NONE,        // Additional capabilities
       NULL              // Reserved
       );
                     
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao inicializar a segurança COM. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     CoUninitialize();
     return NULL;          // Program has failed.
   }
   
   // Obtain the initial locator to Windows Management
   // on a particular host computer.
   IWbemLocator *pLoc = 0;
   
   hres = CoCreateInstance(
       CLSID_WbemLocator,             
       0, 
       CLSCTX_INPROC_SERVER,
       IID_IWbemLocator, (LPVOID *) &pLoc);
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao criar o objeto IWbemLocator. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     CoUninitialize();
     return NULL;       // Program has failed.
   }
   
   IWbemServices *pSvc = 0;
   
   // Connect to the root\cimv2 namespace with the
   // current user and obtain pointer pSvc
   // to make IWbemServices calls.
   
   hres = pLoc->ConnectServer(       
       _bstr_t(L"ROOT\\CIMV2"), // WMI namespace
       NULL,                    // User name
       NULL,                    // User password
       0,                       // Locale
       NULL,                    // Security flags                 
       0,                       // Authority       
       0,                       // Context object
       &pSvc                    // IWbemServices proxy
       );                              
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Não foi possível conectar ao WMI. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     pLoc->Release();
     CoUninitialize();
     return NULL;                // Program has failed.
   }
   // Set the IWbemServices proxy so that impersonation
   // of the user (client) occurs.
   hres = CoSetProxyBlanket(      
      pSvc,                         // the proxy to set
      RPC_C_AUTHN_WINNT,            // authentication service
      RPC_C_AUTHZ_NONE,             // authorization service
      NULL,                         // Server principal name
      RPC_C_AUTHN_LEVEL_CALL,       // authentication level
      RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
      NULL,                         // client identity 
      EOAC_NONE                     // proxy capabilities     
   );
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Não foi possível setar o proxi blanket. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     pSvc->Release();
     pLoc->Release();
     CoUninitialize();
     return NULL;               // Program has failed.
   }

   // Use the IWbemServices pointer to make requests of WMI. 
   // Make requests here:

   // For example, query for all the running processes
   IEnumWbemClassObject* pEnumerator = NULL;
   hres = pSvc->ExecQuery(
       bstr_t("WQL"), 
       bstr_t("SELECT * FROM Win32_Processor WHERE ProcessorType = 3"),
       WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
       NULL,
       &pEnumerator);
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao executar a consulta das informações da máquina. Erro Nº 0x%08X"};
     wsprintf(ErrorMsg,pErrorMsg,hres);
     pSvc->Release();
     pLoc->Release();     
     CoUninitialize();
     return NULL;               // Program has failed.
   }
   else
   { 
      IWbemClassObject *pclsObj;
      ULONG uReturn = 0;
   
      while (pEnumerator)
      {
         hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
         if(0 == uReturn)
         {
             break;
         }

         VARIANT vtProp;

         // Get the value of the Name property
         hres = pclsObj->Get(L"ProcessorID", 0, &vtProp, 0, 0);
         cRet = ConvertBSTRToStringEx(vtProp.bstrVal);
         VariantClear(&vtProp);
      }

   }
 
   // Cleanup
   // ========
   pSvc->Release();
   pLoc->Release();
   CoUninitialize();

   return cRet;
}

