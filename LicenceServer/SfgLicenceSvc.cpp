#include <SysUtils.hpp>
#include <SvcMgr.hpp>
#pragma hdrstop
#define Application Svcmgr::Application
USEFORM("uSfgLicenceSvc.cpp", SfgLicenceSvc); /* TService: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TSfgLicenceSvc), &SfgLicenceSvc);
       Application->Run();
	}
	catch (Exception &exception)
	{
		Sysutils::ShowException(&exception, System::ExceptAddr());
	}
   catch(...)
   {
		try
		{
         throw Exception("");
		}
		catch(Exception &exception)
		{
			Sysutils::ShowException(&exception, System::ExceptAddr());
		}
   }
	return 0;
}
