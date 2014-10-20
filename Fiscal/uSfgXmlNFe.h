//---------------------------------------------------------------------------
#ifndef uSfgXmlNFeH
#define uSfgXmlNFeH
#include <DB.hpp>
#include "ZConnection.hpp"
#include "ZDataset.hpp"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
//---------------------------------------------------------------------------
class PACKAGE TSfgXmlNFe : public System::TObject
{
private:
   HANDLE hTxtFile;
   TXMLDocument *pXmlNFe;
   _di_IXMLNode pNodeNFe;
   String sFileName;
   String sCodEmpresa;
   int iCodNotaFiscal;
   String sChaveNFe;
   TZQuery *QyNotaFiscal;
   TZQuery *QyEmitente;
   TZQuery *QyDestinatario;
   TZQuery *QyItemNotaFiscal;
   TZQuery *QyImpostoItem;
private:
   void __fastcall CalcChaveNFe(int &iDV);
   bool __fastcall GetDadosNotaFiscal();
   bool __fastcall GetDadosEmitente();
   bool __fastcall GetDadosDestinatario();
   bool __fastcall GetDadosItemNotaFiscal();
   bool __fastcall GetDadosImpostoItem(int iSeqProduto);
   bool __fastcall WriteTxtLine(char *Line);
public:
	__fastcall TSfgXmlNFe();
	__fastcall ~TSfgXmlNFe();
   __property String FileName = {read=sFileName, write=sFileName};
   __property TXMLDocument *XmlNFe = {read=pXmlNFe};
   __property String CodEmpresa = {read=sCodEmpresa, write=sCodEmpresa};
   __property int CodNotaFiscal = {read=iCodNotaFiscal, write=iCodNotaFiscal};
   __property String ChaveNFe = {read=sChaveNFe};
   bool __fastcall CreateXmlFile(const String sVersion = "1.0",const String sEncoding = "utf-8");
   bool __fastcall LoadNfe();
   bool __fastcall LoadNfeToTxt();
   bool __fastcall SaveXmlFile(const String sFile = "");
   bool __fastcall SaveTxtFile(const String sFile = "");
};
#endif
