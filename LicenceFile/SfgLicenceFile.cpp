//---------------------------------------------------------------------------
#include "AppBase.h"
#include "FormControls.h"
#include "uFrmLicFile.h"
#include <exception>
//---------------------------------------------------------------------------
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SIZE sz;
	HICON Icone = LoadIcon(hInstance,"MAINICON");
	HBRUSH Fundo = CreateSolidBrush(GetSysColor(COLOR_APPWORKSPACE));
	if(!Fundo)
		Fundo = (HBRUSH)(COLOR_BTNFACE+1);

	App = new AppBase(hInstance,Fundo,Icone); //Criamos uma instância da classe aplicação
                                            //passando para ela a nossa cor do fundo e o ícone
	if(App == NULL)
		return GetLastError();
	try{
	App->SetFontParam(8,400,"MS Sans Serif");//Indicamos uma fonte para os nossos controles
	InitCommonControls();//Usado para dar suporte aos temas do XP e controles adicionais
				  //como barra de status, barras de rolagem entre outros

	sz.cx =  GetSystemMetrics(SM_CXSCREEN);
	sz.cy =  GetSystemMetrics(SM_CYSCREEN);

#ifdef _USE_XPTHEMES
	HINSTANCE uxtheme = NULL;
	PFNISAPPTHEMED IsAppThemed = NULL;
	uxtheme = LoadLibrary("uxtheme.dll");
	if(uxtheme)
		IsAppThemed = (PFNISAPPTHEMED)GetProcAddress(uxtheme,"IsAppThemed");
	if(IsAppThemed)
		AppIsVisualStyle = (bool)IsAppThemed();
	FreeLibrary(uxtheme);
#endif

	FrmLicFile = new TFrmLicFile();
	FrmLicFile->LoadDialogFromResource("LICENCEFILE", NULL, FALSE);
	ShowWindow(FrmLicFile->gethWnd(),nCmdShow);
	//esta parte é só para mudar o mouse dos botões para mãozinha
	HWND btClass = CreateWindow("BUTTON",NULL,0,0,0,10,10,NULL,NULL,hInstance,NULL);
	SetClassLong(btClass,GCL_HCURSOR, (long)LoadCursor(NULL, IDC_HAND));
	DestroyWindow(btClass); //fim mãozinha
	App->AppRun();//Roda o loop de mensagens da aplicação
	}
	catch (...)
	{
		MessageBox(NULL,"Ocorreu um erro inesperado","Erro",0);
	}
	return 0;
}
//---------------------------------------------------------------------------
