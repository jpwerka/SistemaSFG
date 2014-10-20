//---------------------------------------------------------------------------
#include <Dialogs.hpp>
#include <utilcls.h>
#pragma hdrstop
#include "uSfgToExcel.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_2K_SRVR"

Function ExcelOpenXML("OpenXML");
//---------------------------------------------------------------------------
__fastcall TSfgAnaToExcel::TSfgAnaToExcel() : System::TObject()
{
	pExcel = NULL;
	pWorkbook = NULL;
	pDadosSheet = NULL;
	pPivotSheet = NULL;
	sDadosSheet = "";
	sPivotSheet = "";
	sPivotTable = "";
	QySfgToExcel = NULL;
   hFileXml = NULL;
}
//---------------------------------------------------------------------------
__fastcall TSfgAnaToExcel::~TSfgAnaToExcel()
{
	if (pPivotTable.IsBound()) {
		pPivotTable.Unbind();
	}
	if (pPivotSheet != NULL) {
		pPivotSheet->Disconnect();
		delete pPivotSheet;
	}
	if (pDadosSheet != NULL) {
		pDadosSheet->Disconnect();
		delete pDadosSheet;
	}
	if (pWorkbook != NULL) {
		pWorkbook->Disconnect();
		delete pWorkbook;
	}
	if (pExcel != NULL) {
		pExcel->Quit();
		pExcel->Disconnect();
		delete pExcel;
	}
	if (QySfgToExcel != NULL) {
		delete QySfgToExcel;
	}
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::SetContainer(TOleContainer *OleContainer)
{
	IDispatch *id;
	_WorkbookPtr wbPtr;
	//OleAnalise->CreateObject("Excel.Sheet",false);
	//OleAnalise->CreateObjectFromInfo(pInfo);
	//OleAnalise->DoVerb(ovPrimary);
	//id = OleAnalise->OleObject;

	//exVisible << true;
	//oExcel.Exec(exVisible);
	//oWorkbooks = oExcel.OlePropertyGet("Workbooks");
	//OpenDoc << NamedParm("Filename", WideString("cns_pedidos_venda.xml"))
	//		  << NamedParm("UpdateLinks", 3);
	//OpenDoc << StringToOleStr("d:\\sistemasfg\\cns_pedidos_venda.xml");
	//OpenDoc << NamedParm("Filename", WideString("D:\\SistemaSFG\\cns_pedidos_venda.xml"));
	//oWorkbook = oWorkbooks.Exec(OpenDoc);
try {
   //OleContainer->CreateObject("Excel.Sheet",true);
   oExcel = OleContainer->OleObject.OlePropertyGet("Application");
	oWorkbooks = oExcel.OlePropertyGet("Workbooks");
//	id = OleContainer->OleObject;
/*	HRESULT hr = id->QueryInterface(IID__Workbook, (void**)&wbPtr);
	OleCheck(hr);
	if (SUCCEEDED(hr))
	{
		id->Release();
		pWorkbook = new TExcelWorkbook(OleContainer);
		pWorkbook->ConnectTo(wbPtr);

		pExcel = new TExcelApplication(OleContainer);
		pExcel->ConnectTo(pWorkbook->Application);
	}*/
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar conectar ao Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}

/*try {
	pDadosSheet = new TExcelWorksheet(pWorkbook);
	pDadosSheet->ConnectTo(pWorkbook->Worksheets->get_Item(Variant(sDadosSheet)));
	pPivotSheet = new TExcelWorksheet(pWorkbook);
	pPivotSheet->ConnectTo(pWorkbook->Worksheets->get_Item(Variant(sPivotSheet)));
	pPivotTable = pPivotSheet->PivotTables(Variant(sPivotTable), 0);
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar conectar a planilha do Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}*/
   String sMsgErro = "";
   if (!CreateFileXml(sMsgErro)) {
	   MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	   return false;
   }
try {
   //WCHAR *wcFile = WideString(sFileName).c_bstr();
   //pExcel->Workbooks->OpenXML(wcFile);
	//oWorkbooks = oExcel.OlePropertyGet("Workbooks");
	//OpenDoc << NamedParm("Filename", WideString("cns_pedidos_venda.xml"))
	//		  << NamedParm("UpdateLinks", 3);
	//OpenDoc << StringToOleStr("d:\\sistemasfg\\cns_pedidos_venda.xml");
	//OpenDoc << NamedParm("Filename", WideString("D:\\SistemaSFG\\cns_pedidos_venda.xml"));
	//oWorkbook = oWorkbooks.Exec(OpenDoc);
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar conectar a planilha do Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
	return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::QueryToExcel(TZConnection *AppConnection, String SQL)
{
	/*int nCol, aCol, aRow;
   String sValue;
   WideString wsValue;
try {
	QySfgToExcel = new TZReadOnlyQuery(AppConnection);
	QySfgToExcel->Connection = AppConnection;
	QySfgToExcel->SQL->Text = SQL;
	QySfgToExcel->Active = true;
	if (QySfgToExcel->RecordCount <= 0) {
		QySfgToExcel->Active = false;
		MessageBox(NULL,"Não existem dados para serem analisados.", "Análise", MB_OK|MB_ICONINFORMATION);
		return false;
	}
}
catch(Exception &e){
	delete QySfgToExcel;
	String Msg = "Ocorreu o seguinte erro ao tentar consultar os dados no banco:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
try {
	nCol = QySfgToExcel->FieldCount;
	aRow = 1; //Começa na linha 01 que já possui os cabeçalhos das colunas
	while (!QySfgToExcel->Eof) {
		aRow++;
		for (aCol = 1; aCol <= nCol; aCol++) {
			pRange = pDadosSheet->get_Cells()->get_Item(Variant(aRow),Variant(aCol));
			switch (QySfgToExcel->Fields->Fields[aCol-1]->DataType) {
				case ftString:
               sValue = "'" + QySfgToExcel->Fields->Fields[aCol-1]->AsString;
					pRange->set_Value(Variant(sValue));
					break;
				case ftWideString:
					wsValue = "'" + QySfgToExcel->Fields->Fields[aCol-1]->Value;
               pRange->set_Value(Variant(wsValue));
					break;
				case ftSmallint:
				case ftInteger:
				case ftLargeint:
					pRange->set_Value(Variant(QySfgToExcel->Fields->Fields[aCol-1]->AsInteger));
					break;
				case ftFloat:
				case ftCurrency:
					pRange->set_Value(Variant(QySfgToExcel->Fields->Fields[aCol-1]->AsFloat));
					break;
				case ftDate:
				case ftTime:
				case ftDateTime:
					pRange->set_Value(Variant(QySfgToExcel->Fields->Fields[aCol-1]->AsDateTime));
					break;
				default:
					pRange->set_Value(QySfgToExcel->Fields->Fields[aCol-1]->Value);
			}
			pRange.Unbind();
		}
		QySfgToExcel->Next();
	}
	QySfgToExcel->Active = false;
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
try {
	String sSource = sDadosSheet + "!L1C1:L" + aRow + "C" + nCol;
	pPivotTable->PivotCache()->set_SourceData(Variant(sSource));
	pPivotTable->RefreshTable();
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar atualizar a análise dos dados no Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}*/
	return QueryToExcelEx(AppConnection, SQL);
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::QueryToExcelEx(TZConnection *AppConnection, String SQL)
{
	OleVariant oWorkbook;
	int nCols, nRows, aCol;
   String sTagXml;
   String sMsgErro;
try {
	QySfgToExcel = new TZReadOnlyQuery(AppConnection);
	QySfgToExcel->Connection = AppConnection;
	QySfgToExcel->SQL->Text = SQL;
	QySfgToExcel->Active = true;
   nRows = QySfgToExcel->RecordCount;
	nCols = QySfgToExcel->FieldCount;
	if (nRows <= 0) {
		QySfgToExcel->Active = false;
		MessageBox(NULL,"Não existem dados para serem analisados.", "Análise", MB_OK|MB_ICONINFORMATION);
		return false;
	}
}
catch(Exception &e){
	delete QySfgToExcel;
	sMsgErro = "Ocorreu o seguinte erro ao tentar consultar os dados no banco:\n";
	sMsgErro += e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   //Deve carregar o cabeçalho do arquivo xml excel
   if (!LoadWorkbookHeader(sMsgErro)) {
      MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
      return false;
   }
   //Deve agora montar a planilha que contém os dados
try {
   //Workbook -> Worksheet -> Table -> (Column && Row)
   //Cabeçalho da planilha
   sTagXml = " <Worksheet ss:Name=\"Dados\">";
   WriteFileXml(sTagXml);
   //Cabeçalho da tabela
   sTagXml = "   <Table ss:ExpandedColumnCount=\"" + IntToStr(nCols) + "\" ss:ExpandedRowCount=\"" + IntToStr(nRows+2) + "\" x:FullColumns=\"1\" x:FullRows=\"1\">\r\n";
   WriteFileXml(sTagXml);
   //Titulos das colunas
   sTagXml = "    <Row ss:AutoFitHeight=\"0\" ss:Height=\"13.5\">\r\n";
   for (aCol = 0; aCol < nCols; aCol++) {
      sTagXml += "     <Cell ss:StyleID=\"tbDataField\"><Data ss:Type=\"String\">" + QySfgToExcel->Fields->Fields[aCol]->FieldName + "</Data></Cell>\r\n";
   }
   sTagXml += "    </Row>\r\n";
   WriteFileXml(sTagXml);
	while (!QySfgToExcel->Eof) {
      //Conteúdo das colunas
      sTagXml = "    <Row ss:AutoFitHeight=\"0\" ss:Height=\"12\">\r\n";
		for (aCol = 0; aCol < nCols; aCol++) {
			switch (QySfgToExcel->Fields->Fields[aCol]->DataType) {
				case ftString:
				case ftWideString:
               sTagXml += "     <Cell ss:StyleID=\"tbDataString\"><Data ss:Type=\"String\">" + QySfgToExcel->Fields->Fields[aCol]->AsString + "</Data></Cell>\r\n";
					break;
				case ftSmallint:
				case ftInteger:
				case ftLargeint:
               sTagXml += "     <Cell ss:StyleID=\"tbDataNumber\"><Data ss:Type=\"Number\">" + QySfgToExcel->Fields->Fields[aCol]->AsString + "</Data></Cell>\r\n";
					break;
				case ftFloat:
				case ftCurrency:
               sTagXml += "     <Cell ss:StyleID=\"tbDataNumber\"><Data ss:Type=\"Number\">" + QySfgToExcel->Fields->Fields[aCol]->AsString + "</Data></Cell>\r\n";
					break;
				case ftDate:
				case ftTime:
				case ftDateTime:
               sTagXml += "     <Cell ss:StyleID=\"tbDataDate\"><Data ss:Type=\"DateTime\">" + QySfgToExcel->Fields->Fields[aCol]->AsDateTime.FormatString("yyyy-mm-dd'T'hh:nn:ss") + "</Data></Cell>\r\n";
					break;
				default:
               sTagXml += "     <Cell ss:StyleID=\"tbDataString\"><Data>" + QySfgToExcel->Fields->Fields[aCol]->AsString + "</Data></Cell>\r\n";
			}
		}
      sTagXml += "    </Row>\r\n";
      WriteFileXml(sTagXml);
		QySfgToExcel->Next();
	}
	QySfgToExcel->Active = false;
   sTagXml += "  </Table>\r\n";
   WriteFileXml(sTagXml);
}
catch(Exception &e){
	sMsgErro = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	sMsgErro += e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   //Fim da planilha de dados
   sTagXml = "\
  <WorksheetOptions xmlns=\"urn:schemas-microsoft-com:office:excel\">\r\n\
   <TabColorIndex>39</TabColorIndex>\r\n\
  </WorksheetOptions>\r\n\
 </Worksheet>\r\n";
   WriteFileXml(sTagXml);

   //Agora deve carregar planilha que contém a tabela dinamica
   if (!LoadPivotSheet(sMsgErro)) {
      MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
      return false;
   }
   //Agora deve carregar as configurações da tabela dinamica - pivot table
   if (!LoadPivotTable(nCols, nRows, sMsgErro)) {
      MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
      return false;
   }
   //Fim da planilha que contém a tabela dinâmica
   sTagXml = "\
  <WorksheetOptions xmlns=\"urn:schemas-microsoft-com:office:excel\">\r\n\
   <TabColorIndex>11</TabColorIndex>\r\n\
  </WorksheetOptions>\r\n\
 </Worksheet>\r\n\
</Workbook>";
   WriteFileXml(sTagXml);
   //Fechando o arquivo
   CloseHandle(hFileXml);

	//exVisible << true;
	oExcel.Exec(PropertySet("Visible") << true);
	ExcelOpenXML << StringToOleStr(sFileName);
	oWorkbook = oWorkbooks.Exec(ExcelOpenXML);

	return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::LoadWorkbookHeader(String &sMsgErro)
{
   TStringStream *StrStream = NULL;
	HRSRC HrRes = NULL;
	HGLOBAL hResData = NULL;
	DWORD wSizeRes = 0;
   HANDLE hModule = GetModuleHandle(NULL);

	HrRes = FindResource(hModule, "WKTDPTHEADER", RT_RCDATA);
   if (HrRes == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
	hResData = LoadResource(hModule, HrRes);
   if (hResData == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   wSizeRes = SizeofResource(hModule, HrRes);
   if (wSizeRes == 0) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   StrStream = new TStringStream("");
   StrStream->Write(hResData,wSizeRes);
   StrStream->Seek(0, soFromBeginning);
   WriteFileXml(StrStream->DataString);
   delete StrStream;
   return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::LoadPivotSheet(String &sMsgErro)
{
   String sResName = "TD" + sPivotSheet.UpperCase();
   TStringStream *StrStream = NULL;
	HRSRC HrRes = NULL;
	HGLOBAL hResData = NULL;
	DWORD wSizeRes = 0;
   HANDLE hModule = GetModuleHandle(NULL);

	HrRes = FindResource(hModule, sResName.c_str(), RT_RCDATA);
   if (HrRes == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
	hResData = LoadResource(hModule, HrRes);
   if (hResData == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   wSizeRes = SizeofResource(hModule, HrRes);
   if (wSizeRes == 0) {
      sMsgErro = "Ocorreu um erro ao carregar o template da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   StrStream = new TStringStream("");
   StrStream->Write(hResData,wSizeRes);
   StrStream->Seek(0, soFromBeginning);
   WriteFileXml(StrStream->DataString);
   delete StrStream;
   return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::LoadPivotTable(int iCols, int iRows, String &sMsgErro)
{
   String sResName = "PT" + sPivotTable.UpperCase();
   TStringStream *StrStream = NULL;
	HRSRC HrRes = NULL;
	HGLOBAL hResData = NULL;
	DWORD wSizeRes = 0;
   HANDLE hModule = GetModuleHandle(NULL);

	HrRes = FindResource(hModule, sResName.c_str(), RT_RCDATA);
   if (HrRes == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da configuração da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
	hResData = LoadResource(hModule, HrRes);
   if (hResData == NULL) {
      sMsgErro = "Ocorreu um erro ao carregar o template da configuração da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   wSizeRes = SizeofResource(hModule, HrRes);
   if (wSizeRes == 0) {
      sMsgErro = "Ocorreu um erro ao carregar o template da configuração da tabela dinamica.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   StrStream = new TStringStream("");
   StrStream->Write(hResData,wSizeRes);
   StrStream->Seek(0, soFromBeginning);
   //Copaiando conteúdo para poder alterar
   String sDataString = StrStream->DataString;
   //Deve substituir a origem dos dados
   String sRangeReference = "R1C1:R" + IntToStr(iRows) + "C" + IntToStr(iCols);
   sDataString = StringReplace(sDataString, "[REFERENCE]", sRangeReference, TReplaceFlags() << rfReplaceAll);
   String sFileReference = "["+ ExtractFileName(sFileName) + "]Dados";
   sDataString = StringReplace(sDataString, "[FILENAME]", sFileReference, TReplaceFlags() << rfReplaceAll);

   WriteFileXml(sDataString);
   delete StrStream;
   return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::CreateFileXml(String &sMsgErro)
{
	char bfTempPath[MAX_PATH];
   DWORD dwRetVal = 0;
   UINT uRetVal   = 0;
   TDateTime DataHora = Now();
   unsigned short year, month, day, hour, min, sec, msec;

   DecodeDate(DataHora, year, month, day);
   DecodeTime(DataHora, hour, min, sec, msec);

	ZeroMemory( bfTempPath, sizeof(char)*MAX_PATH);

   dwRetVal = GetTempPath(MAX_PATH, bfTempPath); // buffer for path
   if (dwRetVal > MAX_PATH || (dwRetVal == 0)) {
      sMsgErro = "Não foi possivel determinar o caminho da pasta TEMP.";
      return false;
   }
   sFileName = bfTempPath;
   sFileName = sFileName + "\\" + \
               IntToStr(year) + \
               IntToStr(month) + \
               IntToStr(day) + \
               IntToStr(hour) + \
               IntToStr(min) + \
               IntToStr(sec) + \
               IntToStr(msec) + ".xml";
   //Cria um arquivo para salvar os dados para o excel em formato XML
   hFileXml = CreateFile(sFileName.c_str(),    // create "CnsUserTIME.xml"
             GENERIC_WRITE,                 // open for write
             FILE_SHARE_READ|FILE_SHARE_WRITE,             // shared file other proccess
             NULL,                         // no security
             CREATE_ALWAYS	,                  // create always, if not exists create it
             FILE_ATTRIBUTE_NORMAL,        // normal file
             NULL);                        // no attr. template

   if (hFileXml == INVALID_HANDLE_VALUE) {
      sMsgErro = "Não foi possivel criar um arquivo temporário para salvar os dados para o excel.\n";
      sMsgErro += SysErrorMessage(GetLastError());
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::WriteFileXml(String sTagXml)
{
   int iSize;
   DWORD dwBytesWritten, dwPos;
   iSize = sTagXml.Length();
   dwPos = SetFilePointer(hFileXml, 0, NULL, FILE_END);
   LockFile(hFileXml, dwPos, 0, dwPos + iSize*sizeof(char), 0);
   WriteFile(hFileXml, sTagXml.c_str(), iSize*sizeof(char), &dwBytesWritten, NULL);
   UnlockFile(hFileXml, dwPos, 0, dwPos + iSize*sizeof(char), 0);
   return true;
}
//---------------------------------------------------------------------------

/* Vai ficar todo este comentário de lixo aqui mesmo porque eu preciso destes exemplos
// declare global Variant for Automation interface
//PropertyGet GetItem("Item");
//PropertySet SetCommandText("CommandText");
//PropertySet SetConnection("Connection");

//Function GetPivotCache("PivotCache");

	TCreateInfo pInfo;

	pInfo.CreateType = ctFromFile;
	pInfo.ShowAsIcon = false;
	pInfo.ClassID = ProgIDToClassID("Excel.Application");
	pInfo.FileName = "d:\\sistemasfg\\cns_pedidos_venda.xls";


	IDispatch *id;
	OleVariant oActiveSheet, oPivotTables, oPivotTable, oPivotCache;
	//OleAnalise->CreateObject("Excel.Sheet",false);
	//OleAnalise->CreateObjectFromInfo(pInfo);
	OleAnalise->DoVerb(ovPrimary);
	id = OleAnalise->OleObject;

	oExcel = OleAnalise->OleObject.OlePropertyGet("Application");
	//exVisible << true;
	//oExcel.Exec(exVisible);
	//oWorkbooks = oExcel.OlePropertyGet("Workbooks");
	//OpenDoc << NamedParm("Filename", WideString("cns_pedidos_venda.xml"))
	//		  << NamedParm("UpdateLinks", 3);
	//OpenDoc << StringToOleStr("d:\\sistemasfg\\cns_pedidos_venda.xml");
	//OpenDoc << NamedParm("Filename", WideString("D:\\SistemaSFG\\cns_pedidos_venda.xml"));
	//oWorkbook = oWorkbooks.Exec(OpenDoc);

	//GetItem << WideString("Análise Vendas");
	//oSheet = oWorkbook.OlePropertyGet("Sheets").Exec(GetItem);

	//OleAnalise->DoVerb(ovShow);
	oActiveSheet = OleAnalise->OleObject.OlePropertyGet("ActiveSheet");
	//oPivotTables = oActiveSheet.OlePropertyGet("PivotTables");
	//oPivotTable = oPivotTable.OlePropertyGet("Item" );
	//GetItem << WideString("analise_vendas");
	oPivotTable = oActiveSheet.OlePropertyGet("PivotTables").Exec(PropertyGet("Item") << WideString("analise_vendas"));
	oPivotCache = oPivotTable.Exec(Function("PivotCache"));
	//SetCommandText << WideString("SELECT * FROM cns_pedido_venda WHERE cod_cliente = '00645482951'");
	//oPivotCache.Exec(SetCommandText);
	oPivotCache.OleProcedure("Refresh");

	ExcelWorkbookPtr wbPtr;

	HRESULT hr = id->QueryInterface(IID__Workbook, (void**)&wbPtr);
	OleCheck(hr);

	TExcelWorkbook *myWorkbook = new TExcelWorkbook(OleAnalise);

	myWorkbook->ConnectTo(wbPtr);

	if (SUCCEEDED(hr)) {
		id->Release();

		ExcelApplicationPtr appPtr;

		appPtr = myWorkbook->Application;

		TExcelApplication *myApplication = new TExcelApplication(myWorkbook);
		myApplication->ConnectTo(appPtr);

		//TExcelWorksheet *myWorksheet = new TExcelWorksheet(myWorkbook);

		//myWorksheet->ConnectTo(myApplication->ActiveSheet);

		//IPivotTable *pPivotTable;
		//IDispatch *pPivotTable;
		//myWorksheet->PivotTables(Variant("analise_vendas"), (long)pPivotTable);
		//myWorksheet->PivotTables()
		//PivotCache *pPivot;
		//pPivotTable->PivotCache(&pPivot);
		//pPivot->set_Connection();
		//pPivot->set_CommandText();
		//pPivot->Refresh();


		//myApplication->CommandBars->get_Item(Variant(1))->Visible = false;

		//?hide toolbars
		//myApplication->Toolbars->get_Item(Variant(1))->Visible = false;
		//myApplication->Toolbars->get_Item(Variant(2))->Visible = false;
		//myApplication->Toolbars->get_Item(Variant(3))->Visible = false;
		//myApplication->Toolbars->get_Item(Variant(4))->Visible = false;
		//BSTR _filename = StringToOleStr("d:\\sistemasfg\\cns_pedidos_venda.xml");
		//long l=0;
		//myApplication->Workbooks->Open()
		//ShowMessage(IntToStr(l));
		//->Open(_filename);

		// write new data to a cell
		// changes are reflected immediately
		//RangePtr changeRange;
		//ExcelWorksheetPtr sheetPtr;

		//sheetPtr = myApplication->Worksheets->get_Item(TVariant("Worksheet_Name"));
		//changeRange = sheetPtr->get_Range(TVariant("A2"), TVariant("A2"));
		//changeRange = changeRange->get_Cells()->get_Item(TVariant("A2"), TVariant("A2"));
		//changeRange->set_Value(TVariant("New_Data"));

		// set Excel workbook to read-only
		// redundant since embedded Excel is already read-only
		//myApplication->ActiveWorkbook->ChangeFileAccess(xlReadOnly);

		myApplication->Quit();
		myApplication->Disconnect();
	}
	//oExcel.Exec(Procedure("Quit"));
	oExcel = Unassigned;

*/

