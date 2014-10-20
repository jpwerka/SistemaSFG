//---------------------------------------------------------------------------
#include <ole2.h> // OLE2 Definitions
#include <stdio.h>
#include <DateUtils.hpp>
#pragma hdrstop
#include "uSfgToExcel.h"
#include <Excel_Xp.h>
#define MAX_STEPS_IMPORT 5
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
void FmtMsgFuncErr(OLECHAR **ErrorMsg, OLECHAR *ptFmt, ...) {
    va_list argList;
    va_start(argList, ptFmt);
    size_t size = vsnwprintf(NULL, 0, ptFmt, argList);
    if (*ErrorMsg != NULL)
      delete[] *ErrorMsg;
    *ErrorMsg = new OLECHAR[sizeof(OLECHAR) * (size+1)];
    vsnwprintf(*ErrorMsg, size + 1, ptFmt, argList);
    va_end(argList);
    (*ErrorMsg)[size] = L'\0';
}
//---------------------------------------------------------------------------
void OleResultCheck(HRESULT hr, OLECHAR *ptFmt, ...) {
   
    if (SUCCEEDED(hr))
        return;

    va_list argList;
    va_start(argList, ptFmt);

    size_t size = vsnwprintf(NULL, 0, ptFmt, argList);
         
    OLECHAR *OleErrorMsg = new OLECHAR[sizeof(OLECHAR) * (size+1)];
    vsnwprintf(OleErrorMsg, size + 1, ptFmt, argList);
    OleErrorMsg[size] = L'\0';

    va_end(argList);
      
    String strErrorMsg = OleErrorMsg;
    delete[] OleErrorMsg;
    
    throw Exception(strErrorMsg);
}
//---------------------------------------------------------------------------
DISPID GetDispIdByName(IDispatch *pDisp, LPOLESTR ptName, OLECHAR **ErrorMsg, LCID lcid = LOCALE_USER_DEFAULT) {
   DISPID dispID = 0;
   HRESULT hr;

   // Convert down to ANSI
   //WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
   ErrorMsg = NULL;
   // Get DISPID for name passed...
   hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, lcid, &dispID);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("IDispatch::GetIDsOfNames(\"%s\") falhou com o erro 0x%08lX");
      FmtMsgFuncErr(ErrorMsg, ptFmt, ptName, hr);
   }
   return dispID;
}
//---------------------------------------------------------------------------
OLECHAR* Pos2Str(int iPos, OLECHAR* wPos) {
   char cPos[3]; //Max IV
   int i, j;

   if (iPos > 26) {
      i = iPos % 26;
      j = iPos / 26;
      if (i == 0)
         cPos[0] = (char)(64 + j - 1);
      else
         cPos[0] = (char)(64 + j);
      if (i == 0)
         cPos[1] = (char)(90);
      else
         cPos[1] = (char)(64 + i);
      cPos[2] = '\0';
   } else {
      cPos[0] = (char)(64 + iPos);
      cPos[1] = '\0';
   }

   MultiByteToWideChar(CP_ACP, MB_COMPOSITE, cPos, -1, wPos, 3);

   return wPos;
}
//---------------------------------------------------------------------------
// AutoWrap() - Automation helper function...
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, DISPID dispID, OLECHAR **ErrorMsg, LCID lcid, int cArgs, va_list argList) {
   HRESULT hr;

   if(!pDisp) {
      OLECHAR *ptFmt = OLESTR("%s");
      FmtMsgFuncErr(ErrorMsg, ptFmt, OLESTR("Passado NULL para IDispatch em AutoWrap()"));
      return -1;
   }

   if (!lcid)
      lcid = LOCALE_SYSTEM_DEFAULT;

   // Variables used...
   DISPPARAMS dp = { NULL, NULL, 0, 0 };
   DISPID dispidNamed = DISPID_PROPERTYPUT;

   // Allocate memory for arguments...
   VARIANT *pArgs = new VARIANT[cArgs+1];
   // Extract arguments...
   //for(int i=0; i<cArgs; i++) {
   for(int i=cArgs-1; i>=0; i--) {
      pArgs[i] = va_arg(argList, VARIANT);
   }

   // Build DISPPARAMS
   dp.cArgs = cArgs;
   dp.rgvarg = pArgs;

   // Handle special-case for property-puts!
   if(autoType & DISPATCH_PROPERTYPUT) {
      dp.cNamedArgs = 1;
      dp.rgdispidNamedArgs = &dispidNamed;
   }

   // Reset Error Information
   UINT ErrArg = 0;
   EXCEPINFO ExcepInfo;
   ::ZeroMemory(&ExcepInfo, sizeof(ExcepInfo));

   // Make the call!
   hr = pDisp->Invoke(dispID, IID_NULL, lcid, autoType, &dp, pvResult, &ExcepInfo, &ErrArg);

   if(FAILED(hr)) {
      if (hr == DISP_E_EXCEPTION) {
         if (ExcepInfo.pfnDeferredFillIn)
            (*(ExcepInfo.pfnDeferredFillIn))(&ExcepInfo);
         OLECHAR *ptFmt = OLESTR("IDispatch::Invoke() falhou com o erro:\nDescrição: %s.\nErro Nº: 0x%08lX");
         FmtMsgFuncErr(ErrorMsg, ptFmt, ExcepInfo.bstrDescription, ((ExcepInfo.wCode) ? ExcepInfo.wCode : ExcepInfo.scode));
      } else {
         OLECHAR *ptFmt = OLESTR("IDispatch::Invoke() falhou com o erro 0x%08lX");
         FmtMsgFuncErr(ErrorMsg, ptFmt, hr);
      }
   }

   delete [] pArgs;

   return hr;
}
//---------------------------------------------------------------------------
HRESULT AutoWrapByName(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, OLECHAR **ErrorMsg, LCID lcid, int cArgs...) {
   HRESULT hr;
   // Begin variable-argument list...
   va_list argList;
   va_start(argList, cArgs);

   DISPID dispID = GetDispIdByName(pDisp, ptName, ErrorMsg, lcid);
   if (dispID == 0)
      return -1;

   // Make the call!
   hr = AutoWrap(autoType, pvResult, pDisp, dispID, ErrorMsg, lcid, cArgs, argList);

   // End variable-argument section...
   va_end(argList);

   return hr;
}
//---------------------------------------------------------------------------
HRESULT AutoWrapByDispID(int autoType, VARIANT *pvResult, IDispatch *pDisp, DISPID dispID, OLECHAR **ErrorMsg, LCID lcid, int cArgs...) {
   HRESULT hr;
   // Begin variable-argument list...
   va_list argList;
   va_start(argList, cArgs);

   // Make the call!
   hr = AutoWrap(autoType, pvResult, pDisp, dispID, ErrorMsg, lcid, cArgs, argList);

   // End variable-argument section...
   va_end(argList);

   return hr;
}
//---------------------------------------------------------------------------
__fastcall TSfgToExcel::TSfgToExcel() : System::TObject()
{
	VariantClear(&vExcelApp);
	VariantClear(&vWorkBook);
	VariantClear(&vDadosSheet);
   VariantClear(&vDataRange);
	FDadosSheet = "Dados";
   FFileName = "";
   FShowProgress = false;
   FProgress = NULL;
	QySfgToExcel = new TZReadOnlyQuery(Application);
   OnGetTitle = NULL;
   OnGetValue = NULL;
   // Initialize the OLE Library...
   OleInitialize(NULL);
}
//---------------------------------------------------------------------------
__fastcall TSfgToExcel::~TSfgToExcel()
{
   // Close the OLE Library...
   OleUninitialize();
   if (QySfgToExcel != NULL)
      delete QySfgToExcel;
   if (FProgress != NULL)
      delete FProgress;
}
//---------------------------------------------------------------------------
String TSfgToExcel::GetExcelFileName(TCustomForm *Parent)
{
   String FileName = ExtractFilePath(Application->ExeName);
   FileName = FileName + "xls\\";
   String xlsName = Parent->ClassName();
   xlsName = xlsName.SubString(2,xlsName.Length());
   String DataHora = "";
   DataHora.sprintf("%04d%02d%02d%02d%02d%02d",
             YearOf(Now()),
             MonthOf(Now()),
             DayOf(Now()),
             HourOf(Now()),
             MinuteOf(Now()),
             SecondOf(Now()));
   xlsName = xlsName + "-" + DataHora; // + ".xls";

   if (!DirectoryExists(FileName))  {
      if (!CreateDir(FileName))
         throw Exception("Não foi possível criar o diretório: " + FileName);
   }
   FileName += xlsName;

   return FileName;
}
//---------------------------------------------------------------------------
bool TSfgToExcel::QueryToExcel(TZConnection *Connection, String SQL)
{
   bool bRet = true;

   if (vExcelApp.vt == VT_EMPTY) {
      MessageBox(NULL,"A integração com Excel não foi iniciada.", "Mensagem de Erro", MB_OK|MB_ICONSTOP);   
      return false;
   }

   if (FShowProgress) {
      FProgress = new TfrxProgress(Application);
      FProgress->Execute(MAX_STEPS_IMPORT,"Consultando dados...",false,true);
   }

try {
	QySfgToExcel->Connection = Connection;
	QySfgToExcel->SQL->Text = SQL;
	QySfgToExcel->Active = true;
	if (QySfgToExcel->RecordCount <= 0) {
		QySfgToExcel->Active = false;
		MessageBox(NULL,"Não existem dados para serem analisados.", "Análise", MB_OK|MB_ICONINFORMATION);
		return false;
	}
}
catch(Exception &e) {
	String Msg = "Ocorreu o seguinte erro ao tentar consultar os dados no banco:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}

   if (!DataSetToExcel(QySfgToExcel))
      bRet = false;

	QySfgToExcel->Active = false;
	return bRet;
}
//---------------------------------------------------------------------------
bool TSfgToExcel::StartExcel()
{
   VARIANT rVal = {0}; // Temporary result holder
   OLECHAR *ErrorMsg = NULL;
try {

   CLSID clsid;
   CLSIDFromProgID(L"Excel.Application", &clsid);
   HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER|CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&vExcelApp.pdispVal);
   OleResultCheck(hr, OLESTR("CoCreateInstance() para \"Excel.Application\" falhou com o erro 0x%08lX"), hr);
   vExcelApp.vt = VT_DISPATCH;

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &rVal, vExcelApp.pdispVal, L"Workbooks", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Excel.Workbooks\" falhou com o erro:\n%s"), ErrorMsg);
   rVal.vt = VT_DISPATCH;

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vWorkBook, rVal.pdispVal, L"Add", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbooks.Add\" falhou com o erro:\n%s"), ErrorMsg);
   vWorkBook.vt = VT_DISPATCH;
   VariantClear(&rVal);

   rVal.vt = VT_I4; rVal.lVal = 1;
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vDadosSheet, vWorkBook.pdispVal, L"Sheets", &ErrorMsg, 0, 1, rVal);
   OleResultCheck(hr, OLESTR("\"Workbook.Sheets(1)\" falhou com o erro:\n%s"), ErrorMsg);
   vDadosSheet.vt = VT_DISPATCH;
   VariantClear(&rVal);

   rVal.vt = VT_BSTR; rVal.bstrVal = ::SysAllocString(WideString(FDadosSheet).c_bstr());
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vDadosSheet.pdispVal, L"Name", &ErrorMsg, 0, 1, rVal);
   OleResultCheck(hr, OLESTR("\"Worksheet.Name\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&rVal);
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar conectar ao Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   return true;
}
//---------------------------------------------------------------------------
bool TSfgToExcel::FinishExcel()
{
   VARIANT parm = {0}; // Generic Parameters
   OLECHAR *ErrorMsg = NULL;
   HRESULT hr = -1;
   bool bRet = true;

   if (vExcelApp.vt == VT_EMPTY) {
      MessageBox(NULL,"A integração com Excel não foi iniciada.", "Mensagem de Erro", MB_OK|MB_ICONSTOP);   
      return false;
   }
   
try {
   parm.vt = VT_BSTR; parm.bstrVal = ::SysAllocString(WideString(FFileName).c_bstr());
   hr = AutoWrapByName(DISPATCH_METHOD, NULL, vWorkBook.pdispVal, L"SaveAs", &ErrorMsg, 0, 1, parm);
   OleResultCheck(hr, OLESTR("\"WorkBook.SaveAs()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm);

   parm.vt = VT_I4; parm.lVal = TRUE;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vExcelApp.pdispVal, L"Visible", &ErrorMsg, 0, 1, parm);
   OleResultCheck(hr, OLESTR("\"Application.Visible\" falhou com o erro:\n%s"), ErrorMsg);
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar salvar o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	bRet = false;
}
	if (vDadosSheet.vt != VT_EMPTY) {
      VariantClear(&vDataRange);
	}
	if (vDadosSheet.vt != VT_EMPTY) {
		VariantClear(&vDadosSheet);
	}
	if (vWorkBook.vt != VT_EMPTY) {
		VariantClear(&vWorkBook);
	}
	if (vExcelApp.vt != VT_EMPTY) {
		VariantClear(&vExcelApp);
	}

   return bRet;
}
//---------------------------------------------------------------------------
bool TSfgToExcel::DataSetToExcel(TDataSet *DataSet)
{
	int nCol, aCol, aRow, nRow, iIndex, iInc;
   VARIANT parm[10] = {0}; // Generic Parameters
   OleVariant oValue;
   VARIANT ExlArray;
   VARIANT HUGEP *ArrData;
   TField *Field;
   OLECHAR *ErrorMsg = NULL;
   HRESULT hr = -1;
   bool bRet = true;

   if (vExcelApp.vt == VT_EMPTY) {
      MessageBox(NULL,"A integração com Excel não foi iniciada.", "Mensagem de Erro", MB_OK|MB_ICONSTOP);   
      return false;
   }
   
   if (FShowProgress) {
      if (FProgress == NULL) {
         FProgress = new TfrxProgress(Application);
         FProgress->Execute(MAX_STEPS_IMPORT - 1,"Calculando dados...",false,true);
      } else {
         FProgress->Tick();
         FProgress->Message = "Calculando dados...";
      }
   }
try {
   
	nRow = DataSet->RecordCount;
   nCol = DataSet->FieldCount;
   ExlArray.vt = VT_ARRAY | VT_VARIANT;
   {
      SAFEARRAYBOUND sab[2];
      sab[0].lLbound = 1; sab[0].cElements = nRow+1;
      sab[1].lLbound = 1; sab[1].cElements = nCol+1;
      ExlArray.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
   }
   SafeArrayAccessData(ExlArray.parray, (void HUGEP* FAR*)&ArrData);

   if (FShowProgress) {
      iInc = (nRow < 1000) ? 10 : ((nRow < 10000) ? 100 : 300);
      FProgress->Tick();
      FProgress->Execute((int)(nRow/iInc),"Carregando dados...",false,true);
   }

	aRow = 0;
   //Deve carregas as colunas com os títulos do ARRAY
   for (aCol = 0; aCol < nCol; aCol++) {
      Field = DataSet->Fields->Fields[aCol];
      if (OnGetTitle != NULL)
         OnGetTitle(Field, oValue);
      else
         oValue = (Field->DisplayLabel.Length() > 0) ? Field->DisplayLabel : Field->FieldName;
      iIndex = (aRow + ((nRow + 1) * aCol));
      ArrData[iIndex] = oValue;
   }
   //Agora carrega os dados das colunas
	while (!DataSet->Eof) {
      aRow++;
		for (aCol = 0; aCol < nCol; aCol++) {
         Field = DataSet->Fields->Fields[aCol];
         if (Field->IsNull)
            oValue = Null();
         else
			switch (Field->DataType) {
				case ftString:
               oValue = "'" + Field->DisplayText;
					break;
				case ftWideString:
               oValue = "'" + Field->DisplayText;
					break;
				case ftSmallint:
				case ftInteger:
				case ftLargeint:
               oValue = Field->AsInteger;
					break;
				case ftFloat:
				case ftCurrency:
               oValue = Field->AsFloat;
					break;
				case ftDate:
				case ftTime:
				case ftDateTime:
               oValue = Field->AsDateTime;
					break;
				default:
               oValue = Field->Value;
			}
         if (OnGetValue != NULL)
            OnGetValue(Field, oValue);
         iIndex = (aRow + ((nRow + 1) * aCol));
         ArrData[iIndex] = oValue;
		}
      if (FShowProgress) {
         if ((aRow % iInc) == 0)
            FProgress->Tick();
      }
		DataSet->Next();
	}
   SafeArrayUnaccessData(ExlArray.parray);

   if (FShowProgress) {
      FProgress->Execute(MAX_STEPS_IMPORT,"Exportando dados...",false,true);
      FProgress->Position = 3;
   }

   //Começa na linha 01, porque a linha 01 já possui os cabeçalhos das colunas
   OLECHAR wCells[20]; //max - IV65536
   OLECHAR wCell[3]; //max - IV
   swprintf(wCells,L"A1:%s%d",Pos2Str(nCol, wCell),(aRow+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vDataRange, vDadosSheet.pdispVal, L"Range", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&parm[0]);

   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vDataRange.pdispVal, L"Value2", &ErrorMsg, 0, 1, ExlArray);
   OleResultCheck(hr, OLESTR("\"Range.Value2\" falhou com o erro:\n%s"), ErrorMsg);

   SafeArrayDestroy(ExlArray.parray);
   VariantClear(&ExlArray);

   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Message = "Abrindo excel...";
   }
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	bRet = false;
}
   if (!ApplyStyles(DataSet))
      bRet = false;
      
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Close();
   }
	return bRet;
}
//---------------------------------------------------------------------------
bool TSfgToExcel::ApplyStyles(TDataSet *DataSet)
{
   int aCol;
   TField *Field = NULL;
   OLECHAR Format[100];
   VARIANT vRange; // Generic IDispatchs
   VARIANT root[10] = {0}; // Generic IDispatchs
   VARIANT parm[10] = {0}; // Generic Parameters
   VARIANT XStyle1 = {0};
   VARIANT XStyle2 = {0};
   OLECHAR *ErrorMsg = NULL;
   OLECHAR wCells[20]; //max - IV65536
   OLECHAR wCell[2][3]; //max - IV
   HRESULT hr = -1;
   DISPID dispID = 0;
   DISPID dIDRange = 0;
   int level=-1; // Current index into root[]
   int nData = DataSet->RecordCount;
   int nCol = DataSet->FieldCount;
   
try {
   //Definido a palete de cores do Excel
   parm[0].vt = VT_I4; parm[0].lVal = 40;
   parm[1].vt = VT_I4; parm[1].lVal = 0x59BB9B;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vWorkBook.pdispVal, L"Colors", &ErrorMsg, 0, 2, parm[0], parm[1]);
   OleResultCheck(hr, OLESTR("\"Workbook.Colors(%d)\" falhou com o erro:\n%s"), parm[0].lVal, ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = 41;
   parm[1].vt = VT_I4; parm[1].lVal = 0xDDF1EA;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vWorkBook.pdispVal, L"Colors", &ErrorMsg, 0, 2, parm[0], parm[1]);
   OleResultCheck(hr, OLESTR("\"Workbook.Colors(%d)\" falhou com o erro:\n%s"), parm[0].lVal, ErrorMsg);
   VariantClear(&parm[0]);
   VariantClear(&parm[1]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vWorkBook.pdispVal, L"Styles", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles\" falhou com o erro:\n%s"), ErrorMsg);

   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(L"sfgT");
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &XStyle1, root[level].pdispVal, L"Add", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.Add('%s')\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   VariantClear(&parm[0]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle1.pdispVal, L"Font", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.('%s').Font\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = TRUE;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Bold", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.('%s').Font.Bold\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = 0xFFFFFF;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Color", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.('%s').Font.Color\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   VariantClear(&root[level--]); //Liberando o Objeto Font

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle1.pdispVal, L"Interior", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.('%s').Interior\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.('%s').Interior.ColorIndex\" falhou com o erro:\n%s"), L"sfgT", ErrorMsg);
   VariantClear(&root[level--]); //Liberando o Objeto Interior

   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(L"sfgD");
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &XStyle2, root[level].pdispVal, L"Add", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles.Add('%s')\" falhou com o erro:\n%s"), L"sfgD", ErrorMsg);
   VariantClear(&parm[0]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle2.pdispVal, L"Interior", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles('%s').Interior\" falhou com o erro:\n%s"), L"sfgD", ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = 41;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Workbook.Styles('%s').Interior.ColorIndex\" falhou com o erro:\n%s"), L"sfgD", ErrorMsg);
   VariantClear(&root[level--]); //Liberando o Objeto Interior

   //Adicionando a formatação dos títulos da planilha  
   swprintf(wCells,L"A1:%s%d",Pos2Str(nCol, wCell[0]),(int)1);
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   dIDRange = GetDispIdByName(vDadosSheet.pdispVal, L"Range", &ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Style", &ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   hr = AutoWrapByDispID(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, dispID, &ErrorMsg, 0, 1, XStyle1);
   OleResultCheck(hr, OLESTR("\"Range('%s').Style\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&vRange);

   //Agora vai adicionar a formatação de cada linha - zebrada
   for (int i=2; i <= (nData+1); i+=2) {
      swprintf(wCells,L"A%d:%s%d",i, Pos2Str(nCol, wCell[0]), (int)i);
      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

      hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
      VariantClear(&parm[0]);

      hr = AutoWrapByDispID(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, dispID, &ErrorMsg, 0, 1, XStyle2);
      OleResultCheck(hr, OLESTR("\"Range('%s').Style\" falhou com o erro:\n%s"), wCells, ErrorMsg);
      VariantClear(&vRange);
   }
   VariantClear(&XStyle1);
   VariantClear(&XStyle2);
   VariantClear(&root[level--]); //Liberando o Objeto Styles

   //Margem inferior da tabela
   swprintf(wCells,L"A2:%s%d", Pos2Str(nCol, wCell[0]), (int)(nData+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", &ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeBottom;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeBottom)\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeBottom).LineStyle\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeBottom).Weight\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeBottom).ColorIndex\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeBottom]

   parm[0].vt = VT_I4; parm[0].lVal = xlInsideHorizontal;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlInsideHorizontal)\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlInsideHorizontal).LineStyle\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   
   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlInsideHorizontal).Weight\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlInsideHorizontal).ColorIndex\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlInsideHorizontal]
   VariantClear(&vRange);

   //Margem esquerda da tabela
   swprintf(wCells,L"A2:A%d", (int)(nData+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", &ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeLeft;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeLeft)\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeLeft).LineStyle\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeLeft).Weight\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeLeft).ColorIndex\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeLeft]
   VariantClear(&vRange);

   //Margem direita da tabela
   swprintf(wCells,L"%s2:%s%d", Pos2Str(nCol, wCell[0]), Pos2Str(nCol, wCell[1]), (int)(nData+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", &ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeRight;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeRight)\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeRight).LineStyle\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeRight).Weight\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Range('%s').Borders(xlEdgeRight).ColorIndex\" falhou com o erro:\n%s"), wCells, ErrorMsg);

   VariantClear(&parm[0]); 
   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeRight]
   VariantClear(&vRange);

   //Deve formatar as colunas com os formatos de campo
   for (aCol = 0; aCol < nCol; aCol++) {
      Field = DataSet->Fields->Fields[aCol];
      ::ZeroMemory(Format,sizeof(Format));
      switch (Field->DataType) {
         case ftFloat:
         case ftCurrency:
            if (((TFloatField*)Field)->currency)
               wcscpy(Format, L"_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)");
            break;
         case ftDate:
            wcscpy(Format, L"dd/mm/yyyy");
            break;
         case ftTime:
            wcscpy(Format, L"hh:mm:ss");
            break;
         case ftDateTime:
            wcscpy(Format, L"dd/mm/yyyy\\ hh:mm:ss");
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (wcslen(Format) > 0) {
         swprintf(wCells,L"%s2:%s%d", Pos2Str(aCol+1, wCell[0]), Pos2Str(aCol+1, wCell[1]), (int)(nData+1));
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

         hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vDadosSheet.pdispVal, dIDRange, &ErrorMsg, 0, 1, parm[0]);
         OleResultCheck(hr, OLESTR("\"Worksheet.Range('%s')\" falhou com o erro:\n%s"), wCells, ErrorMsg);
         VariantClear(&parm[0]);
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(Format);
         hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, L"NumberFormat", &ErrorMsg, 0x0409, 1, parm[0]);
         OleResultCheck(hr, OLESTR("\"Range('%s').NumberFormat\" falhou com o erro:\n%s"), wCells, ErrorMsg);
         VariantClear(&parm[0]);
         VariantClear(&vRange);
      }
   }

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vDadosSheet.pdispVal, L"Cells", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Worksheet.Cells\" falhou com o erro:\n%s"), ErrorMsg);
   level++;
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[level], root[level-1].pdispVal, L"EntireColumn", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Worksheet.Cells.EntireColumn\" falhou com o erro:\n%s"), ErrorMsg);
   hr = AutoWrapByName(DISPATCH_METHOD, NULL, root[level].pdispVal, L"AutoFit", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Worksheet.Cells.EntireColumn.AutoFit()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&root[level--]); //Liberando o Objeto EntireColumn
   VariantClear(&root[level--]); //Liberando o Objeto Cells

}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar formatar o arquivo Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   return true;

}
//---------------------------------------------------------------------------
__fastcall TSfgAnaToExcel::TSfgAnaToExcel() : TSfgToExcel()
{
	VariantClear(&vPivotSheet);
	FPivotSheet = "Análise Dados";
   FPivotTable = "analise_dados";
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::FinishExcel()
{
	if (vPivotSheet.vt != VT_EMPTY) {
		VariantClear(&vPivotSheet);
	}
   return TSfgToExcel::FinishExcel();
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::GeneratePivotTable(SfgPivotFdPageList *PageFields,
      SfgPivotFdRowList *RowFields, SfgPivotFdDataList *DataFields)
 {
   OLECHAR Format[100];
   VARIANT rVal = {0}; // Temporary result holder
   VARIANT vPivotTable; // Generic IDispatchs
   VARIANT root[10] = {0}; // Generic IDispatchs
   VARIANT parm[10] = {0}; // Generic Parameters
   OLECHAR *ErrorMsg = NULL;
   HRESULT hr = -1;
   int level= -1; // Current index into root[]
   SfgPivotFdPage *FieldPage = NULL;
   SfgPivotFdRow *FieldRow = NULL;
   SfgPivotFdData *FieldData = NULL;
   int Index = 0;

try {
   //Adicionando uma planilha onde deve gerar a tabela
   hr = AutoWrapByName(DISPATCH_PROPERTYGET, &root[++level], vWorkBook.pdispVal, L"Sheets", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Sheets\" falhou com o erro:\n%s"), ErrorMsg);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET, &rVal, root[level].pdispVal, L"Count", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"Workbook.Sheets.Count\" falhou com o erro:\n%s"), ErrorMsg);

   if (rVal.lVal > 1) {
      parm[0].vt = VT_I4; parm[0].lVal = 2;
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vPivotSheet, root[level].pdispVal, L"Item", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"Sheets.Item(2)\" falhou com o erro:\n%s"), ErrorMsg);
      VariantClear(&parm[0]);
   } else {
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vPivotSheet, root[level].pdispVal, L"Add", &ErrorMsg, 0, 0);
      OleResultCheck(hr, OLESTR("\"Sheets.Add()\" falhou com o erro:\n%s"), ErrorMsg);
   }
   VariantClear(&root[level--]); //Liberando o Objeto Sheets
   VariantClear(&rVal);

   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(WideString(FPivotSheet).c_bstr());
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vPivotSheet.pdispVal, L"Name", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Name\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm[0]);

   //Adicionando um cache para a tabela
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vWorkBook.pdispVal, L"PivotCaches", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"WorkBook.PivotCaches\" falhou com o erro:\n%s"), ErrorMsg);

   //String sSource = DadosSheet + "!L1C1:L" + (nData + 1) + "C" + nCol;
   parm[0].vt = VT_I4; parm[0].lVal = xlDatabase; //SourceType
   VariantCopy(&parm[1], &vDataRange);
   //parm[1].vt = VT_BSTR; parm[1].bstrVal = ::SysAllocString(WideString(sSource).c_bstr()); //SourceData
   level++;
   //hr = AutoWrapByName(DISPATCH_METHOD, &root[level], root[level-1].pdispVal, L"Create", &ErrorMsg, 0, 2, parm[0], parm[1]);
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[level], root[level-1].pdispVal, L"Add", &ErrorMsg, 0, 2, parm[0], parm[1]);
   OleResultCheck(hr, OLESTR("\"WorkBook.PivotCaches.Create()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm[0]);
   VariantClear(&parm[1]);

   String sDest = "$A$1";
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(WideString(sDest).c_bstr()); //TableDestination
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &rVal, vPivotSheet.pdispVal, L"Range", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"Worksheet.Range\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm[0]);

   VariantCopy(&parm[0], &rVal);
   //parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(WideString(sDest).c_bstr()); //TableDestination
   parm[1].vt = VT_BSTR; parm[1].bstrVal = ::SysAllocString(WideString(FPivotTable).c_bstr()); //TableName
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vPivotTable, root[level].pdispVal, L"CreatePivotTable", &ErrorMsg, 0, 2, parm[0], parm[1]);
   OleResultCheck(hr, OLESTR("\"PivotCaches.CreatePivotTable()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&rVal);
   VariantClear(&parm[0]);
   VariantClear(&parm[1]);
   
   VariantClear(&parm[level--]); //Liberando o Objeto PivotCache
   VariantClear(&parm[level--]); //Liberando o Objeto PivotCaches

   parm[0].vt = VT_I4; parm[0].lVal = xlOverThenDown;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vPivotTable.pdispVal, L"PageFieldOrder", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"PivotTable.PageFieldOrder\" falhou com o erro:\n%s"), ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = 2;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vPivotTable.pdispVal, L"PageFieldWrapCount", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"PivotTable.PageFieldWrapCount\" falhou com o erro:\n%s"), ErrorMsg);
   parm[0].vt = VT_I4; parm[0].lVal = xlTable10;
   hr = AutoWrapByName(DISPATCH_METHOD, NULL, vPivotTable.pdispVal, L"Format", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"PivotTable.Format()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm[0]);

   SfgPivotFdPageList::reverse_iterator iPg = PageFields->rbegin();
   Index = 0;
   for(; iPg != PageFields->rend(); ++iPg, ++Index) {
      FieldPage = ((SfgPivotFdPage*)*iPg);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldPage->FieldName);
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vPivotTable.pdispVal, L"PivotFields", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotTable.PivotFields('%s')\" falhou com o erro:\n%s"), FieldPage->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldPage->Caption);
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Caption", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Caption\" falhou com o erro:\n%s"), FieldPage->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      ::ZeroMemory(Format,sizeof(Format));
      switch (FieldPage->FieldType) {
         case ftCurrency:
            wcscpy(Format, L"_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)");
            break;
         case ftDate:
            wcscpy(Format, L"dd/mm/yyyy");
            break;
         case ftTime:
            wcscpy(Format, L"hh:mm:ss");
            break;
         case ftDateTime:
            wcscpy(Format, L"dd/mm/yyyy\\ hh:mm:ss");
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (wcslen(Format) > 0) {
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(Format);
         hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"NumberFormat", &ErrorMsg, 0x0409, 1, parm[0]);
         OleResultCheck(hr, OLESTR("\"PivotField('%s').NumberFormat\" falhou com o erro:\n%s"), FieldPage->FieldName, ErrorMsg);
         VariantClear(&parm[0]);
      }

      parm[0].vt = VT_I4; parm[0].lVal = xlPageField;
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Orientation", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Orientation\" falhou com o erro:\n%s"), FieldPage->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      VariantClear(&root[level--]); //Liberando o Objeto PivotField
   }

   VARIANT SubTArray;
   BOOL HUGEP *ArrData;
   SubTArray.vt = VT_ARRAY | VT_BOOL;
   {
      SAFEARRAYBOUND sab;
      sab.lLbound = 1; sab.cElements = 12;
      SubTArray.parray = SafeArrayCreate(VT_I4, 1, &sab);
   }
   SafeArrayAccessData(SubTArray.parray, (void HUGEP* FAR*)&ArrData);
   for (Index = 0; Index < 12; Index++)
      ArrData[Index] = FALSE;
   SafeArrayUnaccessData(SubTArray.parray);

   SfgPivotFdRowList::iterator iRw = RowFields->begin();
   Index = 0;
   for(; iRw != RowFields->end(); ++iRw, ++Index) {
      FieldRow = ((SfgPivotFdRow*)*iRw);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldRow->FieldName);
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vPivotTable.pdispVal, L"PivotFields", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotTable.PivotFields('%s')\" falhou com o erro:\n%s"), FieldRow->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldRow->Caption);
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Caption", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Caption\" falhou com o erro:\n%s"), FieldRow->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      ::ZeroMemory(Format,sizeof(Format));
      switch (FieldRow->FieldType) {
         case ftCurrency:
            wcscpy(Format, L"_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)");
            break;
         case ftDate:
            wcscpy(Format, L"dd/mm/yyyy");
            break;
         case ftTime:
            wcscpy(Format, L"hh:mm:ss");
            break;
         case ftDateTime:
            wcscpy(Format, L"dd/mm/yyyy\\ hh:mm:ss");
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (wcslen(Format) > 0) {
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(Format);
         hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"NumberFormat", &ErrorMsg, 0x0409, 1, parm[0]);
         OleResultCheck(hr, OLESTR("\"PivotField('%s').NumberFormat\" falhou com o erro:\n%s"), FieldRow->FieldName, ErrorMsg);
         VariantClear(&parm[0]);
      }

      parm[0].vt = VT_I4; parm[0].lVal = xlRowField;
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Orientation", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Orientation\" falhou com o erro:\n%s"), FieldRow->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Subtotals", &ErrorMsg, 0, 1,SubTArray);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Subtotals\" falhou com o erro:\n%s"), FieldRow->FieldName, ErrorMsg);

      VariantClear(&root[level--]); //Liberando o Objeto PivotField
   }
   SafeArrayDestroy(SubTArray.parray);
   VariantClear(&SubTArray);

   SfgPivotFdDataList::iterator iDt = DataFields->begin();
   Index = 0;
   for(; iDt != DataFields->end(); ++iDt, ++Index) {
      FieldData = ((SfgPivotFdData*)*iDt);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldData->FieldName);
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vPivotTable.pdispVal, L"PivotFields", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotTable.PivotFields('%s')\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldData->Caption);
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Caption", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Caption\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_I4; parm[0].lVal = xlDataField;
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Orientation", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Orientation\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_I4; parm[0].lVal = Index + 1;
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vPivotTable.pdispVal, L"DataFields", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotTable.DataFields(%d)\" falhou com o erro:\n%s"), (Index + 1), ErrorMsg);
      VariantClear(&parm[0]);

      parm[0].vt = VT_I4; parm[0].lVal = FieldData->FieldFunction;
      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Function", &ErrorMsg, 0, 1, parm[0]);
      OleResultCheck(hr, OLESTR("\"PivotField('%s').Function\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
      VariantClear(&parm[0]);

      /*level++;
      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(FieldData->Caption);
      parm[1].vt = VT_I4; parm[1].lVal = FieldData->FieldFunction;
      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[level], vPivotTable.pdispVal, L"AddDataField", &ErrorMsg, 0, 3, root[level-1], parm[0], parm[1]);
      OleResultCheck(hr, OLESTR("\"PivotTable.AddDataField('%s')\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
      VariantClear(&parm[1]);
      VariantClear(&parm[0]);*/

      ::ZeroMemory(Format,sizeof(Format));
      switch (FieldData->FieldType) {
         case ftCurrency:
            wcscpy(Format, L"_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)");
            break;
         case ftDate:
            wcscpy(Format, L"dd/mm/yyyy");
            break;
         case ftTime:
            wcscpy(Format, L"hh:mm:ss");
            break;
         case ftDateTime:
            wcscpy(Format, L"dd/mm/yyyy\\ hh:mm:ss");
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (wcslen(Format) > 0) {
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(Format);
         hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"NumberFormat", &ErrorMsg, 0x0409, 1, parm[0]);
         OleResultCheck(hr, OLESTR("\"PivotField('%s').NumberFormat\" falhou com o erro:\n%s"), FieldData->FieldName, ErrorMsg);
         VariantClear(&parm[0]);
      }

      VariantClear(&root[level--]); //Liberando o Objeto DataField
      VariantClear(&root[level--]); //Liberando o Objeto PivotField
   }

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vPivotTable.pdispVal, L"DataPivotField", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"PivotTable.DataPivotField\" falhou com o erro:\n%s"), ErrorMsg);

   parm[0].vt = VT_I4; parm[0].lVal = xlColumnField;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Orientation", &ErrorMsg, 0, 1, parm[0]);
   OleResultCheck(hr, OLESTR("\"PivotTable.DataPivotField.Orientation\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&parm[0]);
   VariantClear(&root[level--]); //Liberando o Objeto DataPivotField

   hr = AutoWrapByName(DISPATCH_METHOD, NULL, vPivotTable.pdispVal, L"RefreshTable", &ErrorMsg, 0, 0);
   OleResultCheck(hr, OLESTR("\"PivotTable.RefreshTable()\" falhou com o erro:\n%s"), ErrorMsg);
   VariantClear(&vPivotTable); //Liberando o Objeto PivotTable

}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar gerar a tabela dinâmica no Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   return true;
}
//---------------------------------------------------------------------------



