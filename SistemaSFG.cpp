//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSplashScreen.h"
#include "uDataModule.h"
#include "uSfgClientLicence.h"
#include "uFrm1012.h"
#pragma hdrstop
#pragma link "ThemedDBGrid.obj"
#pragma link "uSfgPreview.obj"
#pragma comment(lib, "xmlrtl.lib")
#define STEP_INIT_PROGREES 25
//---------------------------------------------------------------------------
USEFORM("Frame\uFrmMain.cpp", FrmMain);
USEFORM("Frame\uFrmLogin.cpp", FrmLogin);
USEFORM("Utils\uSplashScreen.cpp", SplahScreen);
USEFORM("Frame\uSobre.cpp", frmSobre);
USEFORM("Frame\uFrm1001.cpp", Frm1001);
USEFORM("Frame\uFrm1002.cpp", Frm1002);
USEFORM("Frame\uFrm1003.cpp", Frm1003);
USEFORM("Frame\uFrm1004.cpp", Frm1004);
USEFORM("Frame\uFrm1005.cpp", Frm1005);
USEFORM("Frame\uFrm1010.cpp", Frm1010);
USEFORM("Frame\uFrm1011.cpp", Frm1011);
USEFORM("Frame\uFrm1012.cpp", Frm1012);
USEFORM("Frame\uFrm1013.cpp", Frm1013);
USEFORM("Frame\uFrm1020.cpp", Frm1020);
//---------------------------------------------------------------------------
void ParserCmdLine(LPSTR lpCmdLine);
bool ValidAppInit();
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   bool bInitApp = false;
   try
   {
      AppArgs = new SfgArgs();
      ParserCmdLine(lpCmdLine);
      if (AppArgs->Database.Length() == 0) {
          AppArgs->Database = "SistemaSFG";
      }

      Application->Initialize();

      if(AppArgs->Splash) {
         SplahScreen = new TSplahScreen(Application);
         SplahScreen->Show();
         SplahScreen->Update();
         Sleep(0500);
         SplahScreen->InitProgress->StepBy(STEP_INIT_PROGREES);
      }
      Application->CreateForm(__classid(TSfgDataCenter), &SfgDataCenter);
      if(AppArgs->Splash) {
         SplahScreen->InitProgress->StepBy(STEP_INIT_PROGREES);
      }
      bInitApp = ValidAppInit();

      Application->Title = "Sistema Softgreen";
      
      if (bInitApp) {
         Application->CreateForm(__classid(TFrmMain), &FrmMain);
       }
      if(AppArgs->Splash) {
         SplahScreen->InitProgress->StepBy(25);
         SplahScreen->Hide();
         delete SplahScreen;
      }
      if (bInitApp) {
         Application->Run();
      }
   }
   catch (Exception &exception)
   {
      Application->ShowException(&exception);
   }
   catch (...)
   {
      try
      {
         throw Exception("");
      }
      catch (Exception &exception)
      {
         Application->ShowException(&exception);
      }
   }
   if(AppArgs != NULL) delete AppArgs;
   return 0;
}
//---------------------------------------------------------------------------
void ParserCmdLine(LPSTR lpCmdLine)
{
  int i,j,k,ArgLen;
  const BYTE MAX_ARG = 8;
  const BYTE MAX_INFO_ARG = 255;
  char Args[MAX_ARG][MAX_INFO_ARG];
  ZeroMemory(Args,sizeof(char)*(MAX_ARG*MAX_INFO_ARG));

  //strlwr(lpCmdLine);
  ArgLen = strlen(lpCmdLine);
  if(!ArgLen) return;

  while(lpCmdLine[0] == 32)//Elimina os espa�os do in�cio do Comando se houver
       lpCmdLine++;

  i = j = k = 0;
  while(i<=ArgLen && j<MAX_ARG)
  {
    if(lpCmdLine[i] != 32)//Encontra a primeira ocorr�ncia de espa�o
       Args[j][k++] = lpCmdLine[i++];//Copia o argumento para a matriz
    else
    {
       while(lpCmdLine[i] == 32)//Elimina os espa�os do meio do comando
         i++;
       Args[j][k] = '\0';//Finaliza o argumento
       k=0;
       j++;
    }
  }
  Args[j][k] = '\0';//Finaliza o ultimo argumento
/* Exemplos de parametros do sistema
  -db SistemaVFG
  -u administrador
  -p senha
  -ns  (nosplash)
*/
   for(i=0;i<=j;i++) {
      if((strcmp(Args[i],"-db")==0) || (strcmp(Args[i],"/db")==0)) {//pega o banco de dados pela linha de comando
         //Se na linha tem o comando -db na linha seguinte deve ter o nome do banco de dados (obrigat�riamente)
         i++;
         if(!strlen(Args[i])) {
            MessageBox(NULL,"Banco de dados n�o especificado na linha de comando.","Inicializa��o",MB_OK);
         } else {
            if(Args[i][0] == '-' || Args[i][0] == '/') {
               MessageBox(NULL,"Banco de dados inv�lido.","Inicializa��o",MB_OK);
            } else {
               AppArgs->Database = Args[i];
            }
         }
      } else if((strcmp(Args[i],"-u")==0) || (strcmp(Args[i],"/u")==0)) {//Pega o usu�rio passado pela linha de comando
         //Se na linha tem o comando -u na linha seguinte deve ter o nome do usu�rio (obrigat�riamente)
         i++;
         if(!strlen(Args[i])) {
            MessageBox(NULL,"Usu�rio n�o especificado na linha de comando.","Inicializa��o",MB_OK);
         } else {
            if(Args[i][0] == '-' || Args[i][0] == '/') {
               MessageBox(NULL,"Usu�rio inv�lido.","Inicializa��o",MB_OK);
            } else {
               AppArgs->Usuario = Args[i];
            }
         }
      } else if((strcmp(Args[i],"-s")==0) || (strcmp(Args[i],"/s")==0)) {//Pega a senha do usu�rio passado pela linha de comando
         //Se na linha tem o comando -s na linha seguinte deve ter o senha do usu�rio (obrigat�riamente)
         i++;
         if(!strlen(Args[i])) {
            MessageBox(NULL,"Senha do usu�rio n�o especificado na linha de comando.","Inicializa��o",MB_OK);
         } else {
            if(Args[i][0] == '-' || Args[i][0] == '/') {
               MessageBox(NULL,"Senha do usu�rio inv�lida.","Inicializa��o",MB_OK);
            } else {
               AppArgs->Password = Args[i];
            }
         }
      } else if(strcmp(Args[i],"-ns")==0) {
         AppArgs->Splash = false;
      } else {
         char bf[50];
         wsprintf(bf,"Argumento inv�lido: %s",Args[i]);
         MessageBox(NULL,bf,"Inicializa��o",MB_OK);
      }
   }
}
//---------------------------------------------------------------------------
bool ValidAppInit() {

   //Valida a licen�a de uso do sistema
   //Apenas valida caso utilize servidor se conseguiu conectar
   //e caso utilize arquivo local valida a propria licen�a
   //por�m local n�o retorna falso caso n�o licenciou, apenas seta que n�o est� licenciado
   if (!SfgDataCenter->ValidLicence()) {
      return false;
   }
   if(AppArgs->Splash) {
      SplahScreen->InitProgress->StepBy(STEP_INIT_PROGREES);
   }

   //Valida se conseguiu conex�o com o servisor do banco de dados
   //Valida se existe o banco de dados selecionado
   //por�m n�o retorna falso caso n�o existe, apenas seta que n�o est� existe
   if (!SfgDataCenter->ValidDatabase()) {
      return false;
   }
   if(AppArgs->Splash) {
      SplahScreen->InitProgress->StepBy(STEP_INIT_PROGREES);
   }
   //Se n�o utilizar o servidor deve validar o arquivo de licen�as local
   if (!AppLicence->UseServer) {
      SfgDataCenter->IsLicenceOK = TSfgClientLicence::LicenceValidFile();
   }
   //Se tem licen�a e conectou no banco de dados - OK
   if (SfgDataCenter->IsLicenceOK && SfgDataCenter->ExistDataBase) {
      return true;
   }
   //Se somente n�o tem licen�a vai permitir iniciar o sistema
   //Para o usu�rio poder acessar a rotina no sobre que licencia o mesmo
   if (!SfgDataCenter->IsLicenceOK) {
      return true;
   }
   //Se tem licen�a, por�m n�o existe o banco de dados deve criar o mesmo
   if (!SfgDataCenter->ExistDataBase) {
      if (!TFrm1012::CreateDataBase()) {
         return false;
      }
   }
   return true;
}



