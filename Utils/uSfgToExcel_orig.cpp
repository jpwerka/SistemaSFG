//---------------------------------------------------------------------------
#include <Dialogs.hpp>
#pragma hdrstop
#include "uSfgToExcel.h"
#define MAX_STEPS_IMPORT 5
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Excel_2K_SRVR"
//---------------------------------------------------------------------------
__fastcall TSfgAnaToExcel::TSfgAnaToExcel() : System::TObject()
{
	pExcel = NULL;
	pWorkbook = NULL;
	pDadosSheet = NULL;
	pPivotSheet = NULL;
	FDadosSheet = "";
	FPivotSheet = "";
	FPivotTable = "";
   FShowProgress = false;
   FProgress = NULL;
	QySfgToExcel = new TZReadOnlyQuery(Application);
}
//---------------------------------------------------------------------------
__fastcall TSfgAnaToExcel::~TSfgAnaToExcel()
{
	if (pPivotTable.IsBound()) {
      pPivotTable->Release();
		pPivotTable.Unbind();
	}
	if (pPivotSheet != NULL) {
		delete pPivotSheet;
	}
	if (pDadosSheet != NULL) {
		delete pDadosSheet;
	}
	if (pWorkbook != NULL) {
		delete pWorkbook;
	}
	if (pExcel != NULL) {
		pExcel->Quit();
		delete pExcel;
	}
   if (FProgress != NULL) {
      delete FProgress;
   }
	if (QySfgToExcel != NULL) {
		delete QySfgToExcel;
	}
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::SetContainer(TOleContainer *OleContainer)
{
	IDispatch *iDispatch;
	_WorkbookPtr wbPtr;
try {
	iDispatch = OleContainer->OleObject;
	HRESULT hr = iDispatch->QueryInterface(IID__Workbook, (void**)&wbPtr);
	OleCheck(hr);
	if (SUCCEEDED(hr))
	{
		iDispatch->Release();
		pWorkbook = new TExcelWorkbook(OleContainer);
		pWorkbook->ConnectTo(wbPtr);
      pExcel = new _ApplicationDisp(pWorkbook->Application);
      pExcel->DisplayAlerts = false;
	}
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar conectar ao Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
try {
	pDadosSheet = new TExcelWorksheet(OleContainer);
	pDadosSheet->ConnectTo(pWorkbook->Worksheets->get_Item(Variant(FDadosSheet)));
	pPivotSheet = new TExcelWorksheet(OleContainer);
	pPivotSheet->ConnectTo(pWorkbook->Worksheets->get_Item(Variant(FPivotSheet)));
	pPivotTable = pPivotSheet->PivotTables(Variant(FPivotTable), 0);
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
bool TSfgAnaToExcel::QueryToExcel(TZConnection *Connection, String SQL)
{
	int nCol, aCol, aRow, nRow, iIndex, iInc;
   OleVariant oValue;
   Variant ExlArray;
   OleVariant *ArrData;
   int Bounds[4] = {0,0,0,0};
   TField *Field;

   if (FShowProgress) {
      FProgress = new TfrxProgress(Application);
      FProgress->Execute(MAX_STEPS_IMPORT,"Consultando dados...",false,true);
   }

try {
	//QySfgToExcel = new TZReadOnlyQuery(Connection);
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
	delete QySfgToExcel;
	String Msg = "Ocorreu o seguinte erro ao tentar consultar os dados no banco:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Message = "Calculando dados...";
   }
try {
	nRow = QySfgToExcel->RecordCount;
   nCol = QySfgToExcel->FieldCount;
   Bounds[1] = nRow - 1;
   Bounds[3] = nCol - 1;
   ExlArray = VarArrayCreate(Bounds,3,varVariant);
   ArrData = (OleVariant*)VarArrayLock(ExlArray);

   if (FShowProgress) {
      iInc = (nRow < 1000) ? 10 : ((nRow < 10000) ? 100 : 300);
      FProgress->Tick();
      FProgress->Execute((int)(nRow/iInc),"Carregando dados...",false,true);
   }

	aRow = 0;
	while (!QySfgToExcel->Eof) {
		for (aCol = 0; aCol < nCol; aCol++) {
         Field = QySfgToExcel->Fields->Fields[aCol];
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
         iIndex = (aRow + (nRow * aCol));
         ArrData[iIndex] = oValue;
		}
      aRow++;
      if (FShowProgress) {
         if ((aRow % iInc) == 0)
            FProgress->Tick();
      }
		QySfgToExcel->Next();
	}
   if (FShowProgress) {
      FProgress->Execute(MAX_STEPS_IMPORT,"Importando dados...",false,true);
      FProgress->Position = 3;
   }
   VarArrayUnlock(ExlArray);
   //Começa na linha 02, porque a linha 01 já possui os cabeçalhos das colunas
   RangePtr pCells = pDadosSheet->Cells;
   VARIANT pCell01 = pCells->get_Item(Variant(2),Variant(1));
   VARIANT pCell02 = pCells->get_Item(Variant(aRow+1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   pRange->set_Value2(ExlArray);
   pRange.Release();
   pCells.Release();
   pCell01.pdispVal->Release();
   pCell02.pdispVal->Release();
   //pCell01.operator IDispatch *()->Release();
   //pCell02.operator IDispatch *()->Release();
   //pCell01.Release();
   //pCell02.Release();
   ApplyStyles(QySfgToExcel);
	QySfgToExcel->Active = false;
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Message = "Atualizando dados...";
   }
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
try {
	String sSource = FDadosSheet + "!L1C1:L" + aRow + "C" + nCol;
   PivotCachePtr pPivotCache = pPivotTable->PivotCache();
   pPivotCache->set_SourceData(Variant(sSource));
   pPivotCache.Release();
	pPivotTable->RefreshTable();
   pExcel->DisplayAlerts = true;
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Close();
   }
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar atualizar a análise dos dados no Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
	return true;
}
//---------------------------------------------------------------------------
bool TSfgAnaToExcel::ApplyStyles(TDataSet *DataSet)
{
   int aCol;
   TField *Field = NULL;
   String Format = "";
   StylesPtr pStyle = pWorkbook->Styles;
   Excel_2k::Border *Border = NULL;
   Excel_2k::Style *XStyle1 = NULL;
   Excel_2k::Style *XStyle2 = NULL;
   int nRow = DataSet->RecordCount;
   int nCol = DataSet->FieldCount;
try {     
   //Definido a palete de cores do Excel
   pWorkbook->set_Colors(TVariant(40), LOCALE_SYSTEM_DEFAULT, TVariant(0x59BB9B));
   pWorkbook->set_Colors(TVariant(41), LOCALE_SYSTEM_DEFAULT, TVariant(0xDDF1EA));

   XStyle1 = pStyle->Add(TVariant("sfgT")); //Títulos da tabela
   XStyle1->Font->set_Bold(Variant(TRUE));
   XStyle1->Font->set_Color(Variant(0xFFFFFF));
   XStyle1->Interior->set_ColorIndex(TVariant(40));

   XStyle2 = pStyle->Add(TVariant("sfgD")); //Linha zebrada ON
   XStyle2->Interior->set_ColorIndex(TVariant(41));

   //Adicionando a formatação dos títulos da planilha
   RangePtr pCells = pDadosSheet->Cells;
   RangeDispT<Range> *pDispT = new RangeDispT<Range>(pCells);
   VARIANT pCell01 = pDispT->get_Item(Variant(1),Variant(1));
   VARIANT pCell02 = pDispT->get_Item(Variant(1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   pDispT->Bind(pRange,true);
   pDispT->set_Style((Variant)XStyle1);
   //pDispT->Bind(pCells,true);
   //Agora vai adicionar a formatação de cada linha - zebrada
   for (int i=2; i <= (nRow+1); i+=2) {
      pDispT->Bind(pCells,true);
      pCell01 = pDispT->get_Item(Variant(i),Variant(1));
      pCell02 = pDispT->get_Item(Variant(i),Variant(nCol));
      pRange = pDadosSheet->get_Range(pCell01,pCell02);
      pDispT->Bind(pRange,true);
      pDispT->set_Style((Variant)XStyle2);
      //pRange->set_Style((Variant)XStyle2);
   }
   //Margem inferior da tabela
   pDispT->Bind(pCells,true);
   pCell01 = pDispT->get_Item(Variant(2),Variant(1));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeBottom);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   Border = pRange->Borders->get_Item(xlInsideHorizontal);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   //Margem esquerda da tabela
   pCell01 = pDispT->get_Item(Variant(1),Variant(1));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(1));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeLeft);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   //pRange->set_NumberFormat()

   //Margem direita da tabela
   pCell01 = pDispT->get_Item(Variant(1),Variant(nCol));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeRight);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));

   LCID oldLcid = pExcel->lcid;
   pExcel->lcid = 0x0409; //Altera a formatação Excel para o padrão americano
   //Deve formatar as colunas com os formatos de campo
   for (aCol = 0; aCol < nCol; aCol++) {
      Field = DataSet->Fields->Fields[aCol];
      Format = "";
      switch (Field->DataType) {
         case ftFloat:
         case ftCurrency:
            if (((TFloatField*)Field)->currency)
               Format = "_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)";
            break;
         case ftDate:
            Format = "dd/mm/yyyy";
            break;
         case ftTime:
            Format = "hh:mm:ss";
            break;
         case ftDateTime:
            Format = "dd/mm/yyyy\\ hh:mm:ss";
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (Format.Length() > 0) {
         pCell01 = pCells->get_Item(Variant(2),Variant(aCol+1));
         pCell02 = pCells->get_Item(Variant(nRow+1),Variant(aCol+1));
         pRange = pDadosSheet->get_Range(pCell01,pCell02);
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         //
         pDispT->Bind(pRange,true);
         pDispT->set_lcid(0x0409); //Altera a formatação Excel para o padrão americano
         pDispT->set_NumberFormat(TVariant(Format));
         delete pDispT;
      }
   }
   pExcel->lcid = oldLcid;
   pRange.Release();
   pCells.Release();
   pCell01.pdispVal->Release();
   pCell02.pdispVal->Release();

   pDadosSheet->Cells->EntireColumn->AutoFit();

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
/*__fastcall TSfgLstToExcel::TSfgLstToExcel() : System::TObject()
{
	pExcel = NULL;
	pWorkbook = NULL;
	pDadosSheet = NULL;
	FDadosSheet = "";
   FFileName = "";
   FShowProgress = false;
   FProgress = NULL;
	QySfgToExcel = NULL;
   OnGetTitle = NULL;
   OnGetValue = NULL;
}
//---------------------------------------------------------------------------
__fastcall TSfgLstToExcel::~TSfgLstToExcel()
{
	if (pDadosSheet != NULL) {
		delete pDadosSheet;
	}
	if (pWorkbook != NULL) {
		delete pWorkbook;
	}
	if (pExcel != NULL) {
		delete pExcel;
	}
   if (FProgress != NULL) {
      delete FProgress;
   }
	if (QySfgToExcel != NULL) {
		delete QySfgToExcel;
	}
}
//---------------------------------------------------------------------------
bool TSfgLstToExcel::QueryToExcel(TZConnection *Connection, String SQL)
{
   bool bRet = true;

   if (FShowProgress) {
      FProgress = new TfrxProgress(Application);
      FProgress->Execute(MAX_STEPS_IMPORT,"Consultando dados...",false,true);
   }

try {
	QySfgToExcel = new TZReadOnlyQuery(Connection);
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
bool TSfgLstToExcel::DataSetToExcel(TDataSet *DataSet)
{
	int nCol, aCol, aRow, nRow, iIndex, iInc;
   OleVariant oValue;
   Variant ExlArray;
   OleVariant *ArrData;
   int Bounds[4] = {0,0,0,0};
   TField *Field;
   bool bRet = true;

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
   Bounds[1] = nRow;
   Bounds[3] = nCol - 1;
   ExlArray = VarArrayCreate(Bounds,3,varVariant);
   ArrData = (OleVariant*)VarArrayLock(ExlArray);

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
   if (FShowProgress) {
      FProgress->Execute(MAX_STEPS_IMPORT,"Exportando dados...",false,true);
      FProgress->Position = 3;
   }
   VarArrayUnlock(ExlArray);
   //Começa na linha 01, porque a linha 01 já possui os cabeçalhos das colunas
   if (OpenExcel()) {
      RangePtr pCells = pDadosSheet->Cells;
      VARIANT pCell01 = pCells->get_Item(Variant(1),Variant(1));
      VARIANT pCell02 = pCells->get_Item(Variant(aRow+1),Variant(nCol));
      pRange = pDadosSheet->get_Range(pCell01,pCell02);
      pRange->set_Value2(ExlArray);
      pRange.Release();
      pCells.Release();
      pCell01.pdispVal->Release();
      pCell02.pdispVal->Release();
      if (FShowProgress) {
         FProgress->Tick();
         FProgress->Message = "Abrindo excel...";
      }
   }
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   if (!ApplyStyles(DataSet))
      bRet = false;
   if (!CloseExcel())
      bRet = false;
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Close();
   }
	return bRet;
}
//---------------------------------------------------------------------------
bool TSfgLstToExcel::OpenExcel()
{
	IDispatch *iDispatch;
   _WorkbookPtr wbPtr;
   Variant excelApp = Unassigned;
try {
   excelApp = CreateOleObject("Excel.Sheet"); //open excel
	iDispatch = excelApp;
   HRESULT hr = iDispatch->QueryInterface(IID__Workbook, (void**)&wbPtr);

	OleCheck(hr);
	if (SUCCEEDED(hr))
	{
		iDispatch->Release();
		pWorkbook = new TExcelWorkbook(Application);
		pWorkbook->ConnectTo(wbPtr);
      pExcel = new _ApplicationDisp(pWorkbook->Application);
      pDadosSheet = new TExcelWorksheet(Application);
      pDadosSheet->ConnectTo(pWorkbook->Sheets->get_Item(TVariant(1)));
	}
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
bool TSfgLstToExcel::ApplyStyles(TDataSet *DataSet)
{
   int aCol;
   TField *Field = NULL;
   String Format = "";
   StylesPtr pStyle = pWorkbook->Styles;
   Excel_2k::Border *Border = NULL;
   Excel_2k::Style *XStyle1 = NULL;
   Excel_2k::Style *XStyle2 = NULL;
   int nRow = DataSet->RecordCount;
   int nCol = DataSet->FieldCount;
try {     
   //Definido a palete de cores do Excel
   pWorkbook->set_Colors(TVariant(40), LOCALE_SYSTEM_DEFAULT, TVariant(0x59BB9B));
   pWorkbook->set_Colors(TVariant(41), LOCALE_SYSTEM_DEFAULT, TVariant(0xDDF1EA));

   XStyle1 = pStyle->Add(TVariant("s01")); //Títulos da tabela
   XStyle1->Font->set_Bold(Variant(TRUE));
   XStyle1->Font->set_Color(Variant(0xFFFFFF));
   XStyle1->Interior->set_ColorIndex(TVariant(40));

   XStyle2 = pStyle->Add(TVariant("s02")); //Linha zebrada ON
   XStyle2->Interior->set_ColorIndex(TVariant(41));

   //Adicionando a formatação dos títulos da planilha
   RangePtr pCells = pDadosSheet->Cells;
   RangeDispT<Range> *pDispT = new RangeDispT<Range>(pCells);
   VARIANT pCell01 = pDispT->get_Item(Variant(1),Variant(1));
   VARIANT pCell02 = pDispT->get_Item(Variant(1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   pDispT->Bind(pRange,true);
   pDispT->set_Style((Variant)XStyle1);
   //pDispT->Bind(pCells,true);
   //Agora vai adicionar a formatação de cada linha - zebrada
   for (int i=2; i <= (nRow+1); i+=2) {
      pDispT->Bind(pCells,true);
      pCell01 = pDispT->get_Item(Variant(i),Variant(1));
      pCell02 = pDispT->get_Item(Variant(i),Variant(nCol));
      pRange = pDadosSheet->get_Range(pCell01,pCell02);
      pDispT->Bind(pRange,true);
      pDispT->set_Style((Variant)XStyle2);
      //pRange->set_Style((Variant)XStyle2);
   }
   //Margem inferior da tabela
   pDispT->Bind(pCells,true);
   pCell01 = pDispT->get_Item(Variant(2),Variant(1));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeBottom);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   Border = pRange->Borders->get_Item(xlInsideHorizontal);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   //Margem esquerda da tabela
   pCell01 = pDispT->get_Item(Variant(1),Variant(1));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(1));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeLeft);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));
   //pRange->set_NumberFormat()

   //Margem direita da tabela
   pCell01 = pDispT->get_Item(Variant(1),Variant(nCol));
   pCell02 = pDispT->get_Item(Variant(nRow+1),Variant(nCol));
   pRange = pDadosSheet->get_Range(pCell01,pCell02);
   Border = pRange->Borders->get_Item(xlEdgeRight);
   Border->set_LineStyle(Variant(xlContinuous));
   Border->set_Weight(Variant(xlThin));
   Border->set_ColorIndex(TVariant(40));

   LCID oldLcid = pExcel->lcid;
   pExcel->lcid = 0x0409; //Altera a formatação Excel para o padrão americano
   //Deve formatar as colunas com os formatos de campo
   for (aCol = 0; aCol < nCol; aCol++) {
      Field = DataSet->Fields->Fields[aCol];
      Format = "";
      switch (Field->DataType) {
         case ftFloat:
         case ftCurrency:
            if (((TFloatField*)Field)->currency)
               Format = "_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)";
            break;
         case ftDate:
            Format = "dd/mm/yyyy";
            break;
         case ftTime:
            Format = "hh:mm:ss";
            break;
         case ftDateTime:
            Format = "dd/mm/yyyy\\ hh:mm:ss";
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (Format.Length() > 0) {
         pCell01 = pCells->get_Item(Variant(2),Variant(aCol+1));
         pCell02 = pCells->get_Item(Variant(nRow+1),Variant(aCol+1));
         pRange = pDadosSheet->get_Range(pCell01,pCell02);
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         //
         pDispT->Bind(pRange,true);
         pDispT->set_lcid(0x0409); //Altera a formatação Excel para o padrão americano
         pDispT->set_NumberFormat(TVariant(Format));
         delete pDispT;
      }
   }
   pExcel->lcid = oldLcid;
   pRange.Release();
   pCells.Release();
   pCell01.pdispVal->Release();
   pCell02.pdispVal->Release();

   pDadosSheet->Cells->EntireColumn->AutoFit();

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
bool TSfgLstToExcel::CloseExcel()
{
try {
   pWorkbook->SaveAs(TVariant(FFileName), TNoParam(), TNoParam(), TNoParam(), TNoParam(), TNoParam(), xlNoChange, TNoParam(), TNoParam(), TNoParam(), TNoParam(), LOCALE_SYSTEM_DEFAULT);
   pExcel->Visible = TRUE;
   //pExcel->Quit();
   pExcel->Reset();
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar salvar o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   return true;
}
*/
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

	OleVariant oExcel = OleAnalise->OleObject.OlePropertyGet("Application");
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
//#ifndef UNICODE
//#define LOCAL_UNICODE
//#define UNICODE
//#endif

#include <ole2.h> // OLE2 Definitions
#include <stdio.h>
static OLECHAR *ErrMsgBuffer = NULL;

//---------------------------------------------------------------------------
OLECHAR* FmtMsgFuncErr(OLECHAR *ptFmt, ...) {
    va_list argList;
    va_start(argList, ptFmt);
    size_t size = vsnwprintf(NULL, 0, ptFmt, argList);
    if (ErrMsgBuffer != NULL)
      delete[] ErrMsgBuffer;
    ErrMsgBuffer = new OLECHAR[sizeof(OLECHAR) * size];
    vsnwprintf(ErrMsgBuffer, size + 1, ptFmt, argList);
    va_end(ptFmt);
    ErrMsgBuffer[size] = L'\0';
    return ErrMsgBuffer;
}
//---------------------------------------------------------------------------
DISPID GetDispIdByName(IDispatch *pDisp, LPOLESTR ptName, OLECHAR *ErrorMsg, LCID lcid = LOCALE_USER_DEFAULT) {
   DISPID dispID = 0;
   HRESULT hr;

   // Convert down to ANSI
   //WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
   ErrorMsg = NULL;
   // Get DISPID for name passed...
   hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, lcid, &dispID);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("IDispatch::GetIDsOfNames(\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, ptName, hr);
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
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, DISPID dispID, OLECHAR *ErrorMsg, LCID lcid, int cArgs, va_list argList) {
   HRESULT hr;

   if(!pDisp) {
      OLECHAR *ptFmt = OLESTR("%s");
      ErrorMsg = FmtMsgFuncErr(ptFmt, OLESTR("Passado NULL para IDispatch em AutoWrap()"));
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
         OLECHAR *ptFmt = OLESTR("IDispatch::Invoke() falhou com o erro:\nDescrição:%s.\nErro Nº:0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, ExcepInfo.bstrDescription, ((ExcepInfo.wCode) ? ExcepInfo.wCode : ExcepInfo.scode));
      } else {
         OLECHAR *ptFmt = OLESTR("IDispatch::Invoke() falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      }
   }

   delete [] pArgs;

   return hr;
}
//---------------------------------------------------------------------------
HRESULT AutoWrapByName(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, OLECHAR *ErrorMsg, LCID lcid, int cArgs...) {
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
HRESULT AutoWrapByDispID(int autoType, VARIANT *pvResult, IDispatch *pDisp, DISPID dispID, OLECHAR *ErrorMsg, LCID lcid, int cArgs...) {
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
__fastcall TSfgLstToExcel::TSfgLstToExcel() : System::TObject()
{
	VariantClear(&vExcelApp);
	VariantClear(&vWorkBook);
	VariantClear(&vWorkSheet);
	VariantClear(&vRange);
	FDadosSheet = "";
   FFileName = "";
   FShowProgress = false;
   FProgress = NULL;
	QySfgToExcel = NULL;
   OnGetTitle = NULL;
   OnGetValue = NULL;
}
//---------------------------------------------------------------------------
__fastcall TSfgLstToExcel::~TSfgLstToExcel()
{
	if (vRange.vt != VT_EMPTY) {
		VariantClear(&vRange);
	}
	if (vWorkSheet.vt != VT_EMPTY) {
		VariantClear(&vWorkSheet);
	}
	if (vWorkBook.vt != VT_EMPTY) {
		VariantClear(&vWorkBook);
	}
	if (vExcelApp.vt != VT_EMPTY) {
		VariantClear(&vExcelApp);
	}
	if (QySfgToExcel != NULL) {
		delete QySfgToExcel;
	}
   // Close the OLE Library...
   OleUninitialize();
}
//---------------------------------------------------------------------------
bool TSfgLstToExcel::QueryToExcel(TZConnection *Connection, String SQL)
{
   bool bRet = true;

   if (FShowProgress) {
      FProgress = new TfrxProgress(Application);
      FProgress->Execute(MAX_STEPS_IMPORT,"Consultando dados...",false,true);
   }

try {
	QySfgToExcel = new TZReadOnlyQuery(Connection);
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
bool TSfgLstToExcel::OpenExcel()
{
   VARIANT rVal = {0}; // Temporary result holder
   OLECHAR *ErrorMsg = NULL;
try {
   // Initialize the OLE Library...
   OleInitialize(NULL);

   CLSID clsid;
   CLSIDFromProgID(L"Excel.Application", &clsid);
   HRESULT hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER|CLSCTX_INPROC_SERVER, IID_IDispatch, (void **)&vExcelApp.pdispVal);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("CoCreateInstance() para \"Excel.Application\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
   vExcelApp.vt = VT_DISPATCH;

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &rVal, vExcelApp.pdispVal, L"Workbooks", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Excel.Workbooks\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
   rVal.vt = VT_DISPATCH;

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vWorkBook, rVal.pdispVal, L"Add", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbooks.Add\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
   vWorkBook.vt = VT_DISPATCH;
   VariantClear(&rVal);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vWorkSheet, vWorkBook.pdispVal, L"ActiveSheet", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.ActiveSheet\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
   vWorkSheet.vt = VT_DISPATCH;
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
bool TSfgLstToExcel::DataSetToExcel(TDataSet *DataSet)
{
	int nCol, aCol, aRow, nRow, iIndex, iInc;
   VARIANT parm[10] = {0}; // Generic Parameters
   VARIANT rVal = {0}; // Temporary result holder
   OleVariant oValue;
   VARIANT ExlArray;
   VARIANT HUGEP *ArrData;
   TField *Field;
   OLECHAR *ErrorMsg = NULL;
   HRESULT hr = -1;
   bool bRet = true;

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
   if (FShowProgress) {
      FProgress->Execute(MAX_STEPS_IMPORT,"Exportando dados...",false,true);
      FProgress->Position = 3;
   }
   //VarArrayUnlock(ExlArray);
   SafeArrayUnaccessData(ExlArray.parray);
   //Começa na linha 01, porque a linha 01 já possui os cabeçalhos das colunas
   if (OpenExcel()) {
      OLECHAR wCells[20]; //max - IV65536
      OLECHAR wCell[3]; //max - IV
      Pos2Str(nCol, wCell);
      swprintf(wCells,L"A1:%s%d",wCell,(aRow+1));
      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

      hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, L"Range", ErrorMsg, 0, 1, parm[0]);
      if(FAILED(hr)) {
         OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
         throw new Exception(String(ErrorMsg));
      }
      vRange.vt = VT_DISPATCH;
      VariantClear(&parm[0]);

      hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, L"Value2", ErrorMsg, 0, 1, ExlArray);
      if(FAILED(hr)) {
         OLECHAR *ptFmt = OLESTR("\"Range.Value2\" falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
         throw new Exception(String(ErrorMsg));
      }

      hr = AutoWrapByName(DISPATCH_METHOD, NULL, vRange.pdispVal, L"AutoFit", ErrorMsg, 0, 0);
      if(FAILED(hr)) {
         OLECHAR *ptFmt = OLESTR("\"Range.AutoFit\" falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
         throw new Exception(String(ErrorMsg));
      }
      VariantClear(&vRange);

      if (FShowProgress) {
         FProgress->Tick();
         FProgress->Message = "Abrindo excel...";
      }
   }
   SafeArrayDestroy(ExlArray.parray);
   VariantClear(&ExlArray);
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar recuperar a consulta para o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   if (!ApplyStyles(DataSet))
      bRet = false;
   if (!CloseExcel())
      bRet = false;
   if (FShowProgress) {
      FProgress->Tick();
      FProgress->Close();
   }
	return bRet;
}
//---------------------------------------------------------------------------
bool TSfgLstToExcel::ApplyStyles(TDataSet *DataSet)
{
   int aCol;
   TField *Field = NULL;
   String Format = "";
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
   int nRow = DataSet->RecordCount;
   int nCol = DataSet->FieldCount;
   
try {
   //Definido a palete de cores do Excel
   parm[0].vt = VT_I4; parm[0].lVal = 40;
   parm[1].vt = VT_I4; parm[1].lVal = 0x59BB9B;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vWorkBook.pdispVal, L"Colors", ErrorMsg, 0, 2, parm[0], parm[1]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Colors\" (%d) falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, parm[0].lVal, hr);
      throw new Exception(String(ErrorMsg));
   }
   parm[0].vt = VT_I4; parm[0].lVal = 41;
   parm[1].vt = VT_I4; parm[1].lVal = 0xDDF1EA;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vWorkBook.pdispVal, L"Colors", ErrorMsg, 0, 2, parm[0], parm[1]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Colors\" (%d) falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, parm[0].lVal, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);
   VariantClear(&parm[1]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vWorkBook.pdispVal, L"Styles", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Colors\" (%d) falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, parm[0].lVal, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(L"sfgT");
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &XStyle1, root[level].pdispVal, L"Add", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Styles.Add\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle1.pdispVal, L"Font", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Font\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   parm[0].vt = VT_I4; parm[0].lVal = TRUE;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Bold", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Font.Bold\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   parm[0].vt = VT_I4; parm[0].lVal = 0xFFFFFF;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Color", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Font.Color\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&root[level--]); //Liberando o Objeto Font

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle1.pdispVal, L"Interior", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Interior\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Interior.ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgT", hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&root[level--]); //Liberando o Objeto Interior

   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(L"sfgD");
   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &XStyle2, root[level].pdispVal, L"Add", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Styles.Add\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgD", hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   hr = AutoWrapByName(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], XStyle2.pdispVal, L"Interior", ErrorMsg, 0, 0);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Interior\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgD", hr);
      throw new Exception(String(ErrorMsg));
   }
   parm[0].vt = VT_I4; parm[0].lVal = 41;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Workbook.Style(\"%s\").Interior.ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, L"sfgD", hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&root[level--]); //Liberando o Objeto Interior

   //Adicionando a formatação dos títulos da planilha  
   swprintf(wCells,L"A1:%s%d",Pos2Str(nCol, wCell[0]),(int)1);
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   dIDRange = GetDispIdByName(vWorkSheet.pdispVal, L"Range", ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Style", ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   hr = AutoWrapByDispID(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, dispID, ErrorMsg, 0, 1, XStyle1);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range(\"%s\").Style\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&vRange);

   //Agora vai adicionar a formatação de cada linha - zebrada
   for (int i=2; i <= (nRow+1); i+=2) {
      swprintf(wCells,L"A%d:%s%d",i, Pos2Str(nCol, wCell[0]), (int)i);
      parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

      hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
      if(FAILED(hr)) {
         OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
         throw new Exception(String(ErrorMsg));
      }
      VariantClear(&parm[0]);

      hr = AutoWrapByDispID(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, dispID, ErrorMsg, 0, 1, XStyle2);
      if(FAILED(hr)) {
         OLECHAR *ptFmt = OLESTR("\"Range(\"%s\").Style\" falhou com o erro 0x%08lX");
         ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
         throw new Exception(String(ErrorMsg));
      }
      VariantClear(&vRange);
   }
   VariantClear(&XStyle1);
   VariantClear(&XStyle2);
   VariantClear(&root[level--]); //Liberando o Objeto Styles

   //Margem inferior da tabela
   swprintf(wCells,L"A2:%s%d", Pos2Str(nCol, wCell[0]), (int)(nRow+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeBottom;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeBottom)\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeBottom).LineStyle\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeBottom).Weight\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeBottom).ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeBottom]

   parm[0].vt = VT_I4; parm[0].lVal = xlInsideHorizontal;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlInsideHorizontal)\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlInsideHorizontal).LineStyle\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlInsideHorizontal).Weight\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlInsideHorizontal).ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlInsideHorizontal]
   VariantClear(&vRange);

   //Margem esquerda da tabela
   swprintf(wCells,L"A2:A%d", (int)(nRow+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeBottom;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeLeft)\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeLeft).LineStyle\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeLeft).Weight\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeLeft).ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeLeft]
   VariantClear(&vRange);

   //Margem direita da tabela
   swprintf(wCells,L"%s2:%s%d", Pos2Str(nCol, wCell[0]), Pos2Str(nCol, wCell[1]), (int)(nRow+1));
   parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm[0]);

   dispID = GetDispIdByName(vRange.pdispVal, L"Borders", ErrorMsg, LOCALE_SYSTEM_DEFAULT);
   parm[0].vt = VT_I4; parm[0].lVal = xlEdgeRight;
   hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &root[++level], vRange.pdispVal, dispID, ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeRight)\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlContinuous;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"LineStyle", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeRight).LineStyle\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = xlThin;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"Weight", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeRight).Weight\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   parm[0].vt = VT_I4; parm[0].lVal = 40;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, root[level].pdispVal, L"ColorIndex", ErrorMsg, 0, 1, parm[0]);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeRight).ColorIndex\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }

   VariantClear(&parm[0]); 
   VariantClear(&root[level--]); //Liberando o Objeto Border[xlEdgeRight]
   VariantClear(&vRange);

   //Deve formatar as colunas com os formatos de campo
   for (aCol = 0; aCol < nCol; aCol++) {
      Field = DataSet->Fields->Fields[aCol];
      Format = "";
      switch (Field->DataType) {
         case ftFloat:
         case ftCurrency:
            if (((TFloatField*)Field)->currency)
               Format = "_(\"R$ \"* #,##0.00_);_(\"R$ \"* \\(#,##0.00\\);_(\"R$ \"* \"-\"??_);_(@_)";
            break;
         case ftDate:
            Format = "dd/mm/yyyy";
            break;
         case ftTime:
            Format = "hh:mm:ss";
            break;
         case ftDateTime:
            Format = "dd/mm/yyyy\\ hh:mm:ss";
            break;
      }
      //Se tem um formato deve aplicar a coluna desejada
      if (Format.Length() > 0) {
         swprintf(wCells,L"%s2:%s%d", Pos2Str(aCol+1, wCell[0]), Pos2Str(aCol+1, wCell[1]), (int)(nRow+1));
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(wCells);

         hr = AutoWrapByDispID(DISPATCH_PROPERTYGET|DISPATCH_METHOD, &vRange, vWorkSheet.pdispVal, dIDRange, ErrorMsg, 0, 1, parm[0]);
         if(FAILED(hr)) {
            OLECHAR *ptFmt = OLESTR("\"ActiveSheet.Range\" (\"%s\") falhou com o erro 0x%08lX");
            ErrorMsg = FmtMsgFuncErr(ptFmt, wCells, hr);
            throw new Exception(String(ErrorMsg));
         }
         VariantClear(&parm[0]);
         //Não pode chamar o método de despacho direto do Range
         //Pois o método do range usa a formatação local que pode ser diferente
         //Gerando caracteres estranhos na formatação dos dados
         //http://msdn.microsoft.com/en-us/goglobal/bb896001.aspx
         parm[0].vt = VT_BSTR; parm[0].bstrVal = ::SysAllocString(WideString(Format.c_str()).c_bstr());
         hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vRange.pdispVal, L"NumberFormat", ErrorMsg, 0x0409, 1, parm[0]);
         if(FAILED(hr)) {
            OLECHAR *ptFmt = OLESTR("\"Range.Borders(xlEdgeRight).ColorIndex\" falhou com o erro 0x%08lX");
            ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
            throw new Exception(String(ErrorMsg));
         }
         VariantClear(&parm[0]);
         VariantClear(&vRange);
      }
   }

   //pDadosSheet->Cells->EntireColumn->AutoFit();

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
bool TSfgLstToExcel::CloseExcel()
{
   VARIANT parm = {0}; // Generic Parameters
   OLECHAR *ErrorMsg = NULL;
   HRESULT hr = -1;
try {
   parm.vt = VT_BSTR; parm.bstrVal = ::SysAllocString(WideString(FFileName.c_str()).c_bstr());
   hr = AutoWrapByName(DISPATCH_METHOD, NULL, vWorkBook.pdispVal, L"SaveAs", ErrorMsg, 0, 1, parm);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"WorkBook.SaveAs()\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
   VariantClear(&parm);

   parm.vt = VT_I4; parm.lVal = TRUE;
   hr = AutoWrapByName(DISPATCH_PROPERTYPUT, NULL, vExcelApp.pdispVal, L"Visible", ErrorMsg, 0, 1, parm);
   if(FAILED(hr)) {
      OLECHAR *ptFmt = OLESTR("\"Application.Visible\" falhou com o erro 0x%08lX");
      ErrorMsg = FmtMsgFuncErr(ptFmt, hr);
      throw new Exception(String(ErrorMsg));
   }
}
catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao tentar salvar o Excel:\n";
	Msg = Msg + e.Message;
	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", MB_OK|MB_ICONSTOP);
	return false;
}
   return true;
}
//---------------------------------------------------------------------------

//#ifdef LOCAL_UNICODE
//#undef UNICODE
//#endif


