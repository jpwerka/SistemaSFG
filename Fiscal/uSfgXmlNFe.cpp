//---------------------------------------------------------------------------
#include <vcl.h>
#include <DateUtils.hpp>
#include "uSfgGlobals.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uSfgXmlNFe.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall TSfgXmlNFe::TSfgXmlNFe() : System::TObject()
{
   pXmlNFe = NULL;
   pNodeNFe = NULL;
   sFileName = "";
   sCodEmpresa = "";
   iCodNotaFiscal = 0;
   sChaveNFe = "";
   QyEmitente = new TZQuery(Application);
   QyDestinatario = new TZQuery(Application);
   QyNotaFiscal = new TZQuery(Application);
   QyItemNotaFiscal = new TZQuery(Application);
   QyImpostoItem = new TZQuery(Application);
}
//---------------------------------------------------------------------------
__fastcall TSfgXmlNFe::~TSfgXmlNFe()
{
   delete QyEmitente;
   delete QyDestinatario;
   delete QyNotaFiscal;
   delete QyItemNotaFiscal;
   delete QyImpostoItem;
   pNodeNFe = NULL;
   pXmlNFe = NULL;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::GetDadosNotaFiscal()
{
   String sSQL = "\
SELECT nf.tipo_nota_fiscal,nf.num_nota_fiscal,nf.serie_nota_fiscal,nf.modelo_nota_fiscal,nf.ies_situacao,\
       nf.cod_natureza_operacao,nf.cod_forma_pagto,nf.cod_cliente,nf.tipo_frete,nf.cod_transportador,nf.placa_veiculo,\
       nf.estado_placa_veiculo,nf.placa_reboque,nf.estado_placa_reboque,nf.qtd_volume,nf.especie_volume,\
       nf.marca_volume,nf.numeracao_volume,nf.peso_liquido,nf.peso_bruto,nf.volume_cubico,nf.valor_mercadoria,\
       nf.valor_desconto,nf.valor_duplicata,nf.valor_frete,nf.valor_seguro,nf.outras_despesas,nf.valor_nota_fiscal,\
       nf.data_hora_emissao,nf.data_hora_saida,nf.info_complementar,nf.info_adicional_fisco,nt.den_natureza_operacao\
  FROM tbl_nota_fiscal nf\
 INNER JOIN tbl_natureza_operacao nt\
    ON nt.cod_natureza_operacao = nf.cod_natureza_operacao\
 WHERE nf.cod_empresa = " + QuotedStr(sCodEmpresa) + "\
   AND nf.cod_nota_fiscal = " + IntToStr(iCodNotaFiscal);
try {
   QyNotaFiscal->Connection = AppConnection;
   QyNotaFiscal->SQL->Text = sSQL;
   QyNotaFiscal->Active = true;
   if (QyNotaFiscal->RecordCount > 0) {
      QyNotaFiscal->First();
      return true;
   } else {
      MessageBox(NULL,"Não foi possível carregar todos os dados da nota fiscal para gerar da NFe.", "Dados NFe", APP_ERROR);
      return false;
   }
} catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao carregar as informações da nota fiscal:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::GetDadosEmitente()
{
   String sSQL = "\
SELECT e.cnpj, e.razao_social, e.nome_fantasia, e.logradouro, e.numero,\
       e.complemento, e.bairro, c.den_cidade, c.cod_ibge, e.cod_uf,\
       u.cod_ibge cod_ibge_uf, e.cep, e.inscricao_estadual, e.inscricao_municipal,\
       e.telefone, e.regime_tributario\
  FROM tbl_empresa e\
 INNER JOIN tbl_cidade c\
    ON e.cod_cidade = c.cod_cidade\
 INNER JOIN tbl_uf u\
    ON u.cod_uf = e.cod_uf\
 WHERE e.cod_empresa = " + QuotedStr(sCodEmpresa);
try {
   QyEmitente->Connection = AppConnection;
   QyEmitente->SQL->Text = sSQL;
   QyEmitente->Active = true;
   if (QyEmitente->RecordCount > 0) {
      QyEmitente->First();
      return true;
   } else {
      MessageBox(NULL,"Não foi possível carregar todos os dados da empresa emitente da NFe.", "Emitente NFe", APP_ERROR);
      return false;
   }
} catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do emitente:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::GetDadosDestinatario()
{
   String sSQL = "\
SELECT cl.tipo_pessoa, cl.cpf_cnpj, cl.den_cliente, cl.logradouro, cl.numero,\
       cl.complemento, cl.bairro, c.den_cidade, c.cod_ibge, cl.cod_uf,\
       u.cod_ibge cod_ibge_uf, cl.cep, cl.rg_ie, cl.telefone, cl.email\
  FROM tbl_nota_fiscal nf\
 INNER JOIN tbl_cliente cl\
    ON nf.cod_cliente = cl.cod_cliente\
 INNER JOIN tbl_cidade c\
    ON cl.cod_cidade = c.cod_cidade\
 INNER JOIN tbl_uf u\
    ON u.cod_uf = cl.cod_uf\
 WHERE nf.cod_empresa = " + QuotedStr(sCodEmpresa) + "\
   AND nf.cod_nota_fiscal = " + IntToStr(iCodNotaFiscal);
try {
   QyDestinatario->Connection = AppConnection;
   QyDestinatario->SQL->Text = sSQL;
   QyDestinatario->Active = true;
   if (QyDestinatario->RecordCount > 0) {
      QyDestinatario->First();
      return true;
   } else {
      MessageBox(NULL,"Não foi possível carregar todos os dados do destinatário da NFe.", "Destinatário NFe", APP_ERROR);
      return false;
   }
} catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao carregar as informações do destinatário:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::GetDadosItemNotaFiscal()
{
   String sSQL = "\
SELECT nfi.seq_produto,nfi.cod_produto,nfi.den_produto,nfi.cod_ncm,nfi.cod_ean,\
       nfi.cod_cfop,nfi.cod_extipi,nfi.origem_mercadoria,nfi.cod_unid_medida,\
       nfi.qtd_produto,nfi.valor_unitario,nfi.valor_desconto,nfi.valor_frete,\
       nfi.valor_seguro,nfi.valor_total,nfi.cod_pedido,nfi.seq_pedido,\
       nfi.classe_enq_ipi,nfi.cod_enq_ipi\
  FROM tbl_nota_fiscal_item nfi\
 WHERE nfi.cod_empresa = " + QuotedStr(sCodEmpresa) + "\
   AND nfi.cod_nota_fiscal = " + IntToStr(iCodNotaFiscal) + "\
 ORDER BY nfi.seq_produto";

   String sSQLImp = "\
SELECT cod_tributo, cod_cst, mod_def_base_calc, perc_tributo,\
       base_calculo, valor_tributo, perc_red_base_calc,\
       perc_marg_valor_add, valor_unit_tributo, qtd_total_tributo\
  FROM tbl_nota_fiscal_item_tributo\
 WHERE cod_empresa = " + QuotedStr(sCodEmpresa) + "\
   AND cod_nota_fiscal = " + IntToStr(iCodNotaFiscal) + "\
   AND seq_produto = :seq_produto";
try {
   QyItemNotaFiscal->Connection = AppConnection;
   QyItemNotaFiscal->SQL->Text = sSQL;
   QyItemNotaFiscal->Active = true;
   if (QyItemNotaFiscal->RecordCount > 0) {
      QyItemNotaFiscal->First();
   } else {
      MessageBox(NULL,"Não foi possível carregar todos os dados dos itens da NFe.", "Itens NFe", APP_ERROR);
      return false;
   }
   //Deixa preparado para fazer a carga dos impostos
   QyImpostoItem->Connection = AppConnection;
   QyImpostoItem->SQL->Text = sSQLImp;
   return true;
} catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao carregar as informações dos itens:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::GetDadosImpostoItem(int iSeqProduto)
{
try {
   QyImpostoItem->Active = false;
   QyImpostoItem->ParamByName("seq_produto")->AsInteger = iSeqProduto;
   QyImpostoItem->Active = true;
   if (QyImpostoItem->RecordCount > 0) {
      QyImpostoItem->First();
      return true;
   } else {
      MessageBox(NULL,"Não foi possível carregar todos os dados dos impostos dos itens da NFe.", "Impostos Itens NFe", APP_ERROR);
      return false;
   }
} catch (Exception &e) {
	String sMsgErro = "Ocorreu o seguinte erro ao carregar as informações dos impostos dos itens:\n";
	sMsgErro = sMsgErro + e.Message;
	MessageBox(NULL,sMsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
   return false;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::CreateXmlFile(String sVersion,String sEncoding)
{
   if (pXmlNFe != NULL) {
      pXmlNFe = NULL;
   }
   pXmlNFe = new TXMLDocument("");
   pXmlNFe->Active = true;
   pXmlNFe->Version = sVersion;
   pXmlNFe->Encoding = sEncoding;
   pXmlNFe->Options = TXMLDocOptions() << doNodeAutoCreate << doNodeAutoIndent;
   pNodeNFe = pXmlNFe->AddChild("NFe",WideString("http://www.portalfiscal.inf.br/nfe"));
   pXmlNFe->DocumentElement = pNodeNFe;
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::SaveXmlFile(String sFile)
{
   if (sFile.Length() > 0)
      sFileName = sFile;

   char bfPath[MAX_PATH];
   char *pPath;
   ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

   if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
      pPath = strrchr(bfPath,'\\');
      pPath++;
      *pPath = '\0';
   } else {
      pPath = bfPath;
   }

   sFileName = bfPath + sFileName;
   pXmlNFe->SaveToFile(sFileName);
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::SaveTxtFile(String sFile)
{
   if (sFile.Length() > 0)
      sFileName = sFile;

   char bfPath[MAX_PATH];
   char *pPath;
   ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

   if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
      pPath = strrchr(bfPath,'\\');
      pPath++;
      *pPath = '\0';
   } else {
      pPath = bfPath;
   }

   sFileName = bfPath + sFileName;
   //Cria um arquivo para salvar os dados da licença
   hTxtFile = CreateFile(sFileName.c_str(),    // create SfgLicence.lic
             GENERIC_WRITE,                // open for writing
             0,                            // do not share
             NULL,                         // no security
             CREATE_ALWAYS,                // overwrite existing
             FILE_ATTRIBUTE_NORMAL,        // normal file
             NULL);                        // no attr. template

   if (hTxtFile == INVALID_HANDLE_VALUE) {
      MessageBox(NULL,"Não foi possível efetuar a criação do arquivo texto da nota fiscal.", "Mensagem de Erro", APP_ERROR);
      return false;
   }
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TSfgXmlNFe::CalcChaveNFe(int &iDV)
{
   String sCharPos;
   int iPos, iValPos, iNumPos, iSumTotal;

   iNumPos = 2;
   iSumTotal = 0;
   for (iPos = sChaveNFe.Length(); iPos > 0; iPos--) {
      sCharPos = sChaveNFe.SubString(iPos,1);
      iValPos = StrToInt(sCharPos);
      if (iNumPos > 9)
         iNumPos = 2;
      iSumTotal += (iValPos * iNumPos);
      iNumPos++;
   }
   if ((iSumTotal % 11) < 2)
      iDV = 0;
   else
      iDV = 11 - (iSumTotal % 11);
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::LoadNfe()
{
   String sStrAux;
   String sCST;
   int iSerieNF = 0;
   int iDV = 0;
   _di_IXMLNode pNivel1 = pNodeNFe->AddChild("infNFe");
   _di_IXMLNode pNivel2 = NULL;
   _di_IXMLNode pNivel3 = NULL;
   _di_IXMLNode pNivel4 = NULL;
   _di_IXMLNode pNivel5 = NULL;
   //Os impostos tem nodes separados
   _di_IXMLNode pNdICMS = NULL;
   _di_IXMLNode pNdIPI  = NULL;
   _di_IXMLNode pNdPIS  = NULL;
   _di_IXMLNode pNdCOFINS = NULL;

   if (!GetDadosNotaFiscal())
      return false;
   if (!GetDadosEmitente())
      return false;
   if (!GetDadosDestinatario())
      return false;
   if (!GetDadosItemNotaFiscal())
      return false;

   sChaveNFe = "";
   //Montagem da Chave da NFe
   // UF (IBGE) | AAMM Emissão | CNPJ Emit | Modelo | Série | Num NF | Forma Emissão | Cod Num | DV |
   //    02     |      04      |     14    |   02   |  03   |   09   |       01      |    08   | 01 |
   if (QyEmitente->FieldByName("cod_ibge_uf")->AsString.Length() == 0) {
      MessageBox(NULL,"Informe o código do IBGE no estado da empresa emitente!","Emitente",APP_ATENTION);
      return false;
   }
   //Código IBGE UF Emissão
   sChaveNFe += QyEmitente->FieldByName("cod_ibge_uf")->AsString;
   //Ano/Mês emissão
   sStrAux = "";
   DateTimeToString(sStrAux, "yymm", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
   sChaveNFe += sStrAux;
   //CNPJ Emitente
   sChaveNFe += QyEmitente->FieldByName("cnpj")->AsString;
   //Modelo da NFe - Fixo 55
   sChaveNFe += "55";
   //Série da NF
   iSerieNF = QyNotaFiscal->FieldByName("serie_nota_fiscal")->AsInteger;
   sStrAux = Format("%3.3d",ARRAYOFCONST(((int)iSerieNF)));
   sChaveNFe += sStrAux;
   //Número da NF
   sStrAux = Format("%9.9d",ARRAYOFCONST(((int)QyNotaFiscal->FieldByName("num_nota_fiscal")->AsInteger)));
   sChaveNFe += sStrAux;
   //Forma de emissão da NFe
   sChaveNFe += "1"; //Sempre normal
   //Código numérico da NF - Serial do banco
   sStrAux = Format("%8.8d",ARRAYOFCONST(((int)iCodNotaFiscal)));
   sChaveNFe += sStrAux;
   //Digito Verificador
   CalcChaveNFe(iDV);
   sChaveNFe += IntToStr(iDV);

   sFileName = "nfe\\NFe" + sChaveNFe + ".xml";
   //Informações da NFe
   pNivel1->Attributes["Id"] = WideString("NFe" + sChaveNFe);
   pNivel1->Attributes["versao"] = WideString("2.00");

   //************************************************************//
   //         IDENTIFICAÇÃO DA NOTA FISCAL ELETRÔNICA            //
   //************************************************************//
   pNivel2 = pNivel1->AddChild("ide");
   pNivel3 = pNivel2->AddChild("cUF");
   pNivel3->SetText(QyEmitente->FieldByName("cod_ibge_uf")->AsString);
   sStrAux = Format("%8.8d",ARRAYOFCONST(((int)iCodNotaFiscal)));
   pNivel3 = pNivel2->AddChild("cNF");
   pNivel3->SetText(sStrAux);
   pNivel3 = pNivel2->AddChild("natOp");
   pNivel3->SetText(QyNotaFiscal->FieldByName("den_natureza_operacao")->AsString);
   pNivel3 = pNivel2->AddChild("indPag");
   pNivel3->SetText(QyNotaFiscal->FieldByName("cod_forma_pagto")->AsString);
   pNivel3 = pNivel2->AddChild("mod");
   pNivel3->SetText("55");
   pNivel3 = pNivel2->AddChild("serie");
   pNivel3->SetText(IntToStr(iSerieNF));
   pNivel3 = pNivel2->AddChild("nNF");
   pNivel3->SetText(QyNotaFiscal->FieldByName("num_nota_fiscal")->AsString);
   pNivel3 = pNivel2->AddChild("dEmi");
   sStrAux = "";
   DateTimeToString(sStrAux, "yyyy-mm-dd", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
   pNivel3->SetText(sStrAux);

   if (!VarIsNull(QyNotaFiscal->FieldByName("data_hora_emissao")->Value)) {
      sStrAux = "";
      DateTimeToString(sStrAux, "yyyy-mm-dd", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
      pNivel3 = pNivel2->AddChild("dSaiEnt");
      pNivel3->SetText(sStrAux);
      pNivel3 = pNivel2->AddChild("hSaiEnt");
      pNivel3->SetText(TimeToStr(TimeOf(QyNotaFiscal->FieldByName("data_hora_saida")->AsDateTime)));
   }

   pNivel3 = pNivel2->AddChild("tpNF");
   pNivel3->SetText(QyNotaFiscal->FieldByName("tipo_nota_fiscal")->AsString);
   pNivel3 = pNivel2->AddChild("cMunFG");
   pNivel3->SetText(QyEmitente->FieldByName("cod_ibge")->AsString);
   //Se tivesse notas referenciadas deveria ir neste ponto
   pNivel3 = pNivel2->AddChild("tpImp");
   pNivel3->SetText("1"); // 1-Retrato/ 2-Paisagem
   pNivel3 = pNivel2->AddChild("tpEmis");
   pNivel3->SetText("1"); // 1-Normal
   pNivel3 = pNivel2->AddChild("cDV");
   pNivel3->SetText(IntToStr(iDV));
   pNivel3 = pNivel2->AddChild("tpAmb");
   pNivel3->SetText("1"); // 1-Produção/ 2-Homologação
   pNivel3 = pNivel2->AddChild("finNFe");
   pNivel3->SetText("1"); // 1- NF-e normal
   pNivel3 = pNivel2->AddChild("procEmi");
   pNivel3->SetText("1"); // 3- Emitida por programa do Fisco
   pNivel3 = pNivel2->AddChild("verProc");
   pNivel3->SetText("2.2.4"); // Versão do programa

   //************************************************************//
   //     IDENTIFICAÇÃO DO EMITENTE DA NOTA FISCAL ELETRÔNICA    //
   //************************************************************//
   pNivel2 = pNivel1->AddChild("emit");
   pNivel3 = pNivel2->AddChild("CNPJ");
   pNivel3->SetText(QyEmitente->FieldByName("cnpj")->AsString);
   pNivel3 = pNivel2->AddChild("xNome");
   pNivel3->SetText(QyEmitente->FieldByName("razao_social")->AsString);
   if (!VarIsNull(QyEmitente->FieldByName("nome_fantasia")->Value)) {
      pNivel3 = pNivel2->AddChild("xFant");
      pNivel3->SetText(QyEmitente->FieldByName("nome_fantasia")->AsString);
   }
   //Endereço do emitente
   pNivel3 = pNivel2->AddChild("enderEmit");
   pNivel4 = pNivel3->AddChild("xLgr");
   pNivel4->SetText(QyEmitente->FieldByName("logradouro")->AsString);
   pNivel4 = pNivel3->AddChild("nro");
   pNivel4->SetText(QyEmitente->FieldByName("numero")->AsString);
   if (!VarIsNull(QyEmitente->FieldByName("complemento")->Value)) {
      pNivel4 = pNivel3->AddChild("xCpl");
      pNivel4->SetText(QyEmitente->FieldByName("complemento")->AsString);
   }
   pNivel4 = pNivel3->AddChild("xBairro");
   pNivel4->SetText(QyEmitente->FieldByName("bairro")->AsString);

   pNivel4 = pNivel3->AddChild("cMun");
   if (QyEmitente->FieldByName("cod_uf")->AsString == "EX")
      pNivel4->SetText("9999999");
   else
      pNivel4->SetText(QyEmitente->FieldByName("cod_ibge")->AsString);

   pNivel4 = pNivel3->AddChild("xMun");
   if (QyEmitente->FieldByName("cod_uf")->AsString == "EX")
      pNivel4->SetText("EXTERIOR");
   else 
      pNivel4->SetText(QyEmitente->FieldByName("den_cidade")->AsString);

   pNivel4 = pNivel3->AddChild("UF");
   pNivel4->SetText(QyEmitente->FieldByName("cod_uf")->AsString);
   if (!VarIsNull(QyEmitente->FieldByName("cep")->Value)) {
      pNivel4 = pNivel3->AddChild("CEP");
      pNivel4->SetText(QyEmitente->FieldByName("cep")->AsString);
   }
   pNivel4 = pNivel3->AddChild("cPais");
   pNivel4->SetText("1058");
   pNivel4 = pNivel3->AddChild("xPais");
   pNivel4->SetText("Brasil");
   if (!VarIsNull(QyEmitente->FieldByName("telefone")->Value)) {
      pNivel4 = pNivel3->AddChild("fone");
      pNivel4->SetText(QyEmitente->FieldByName("telefone")->AsString);
   }
   //Fim endereço
   pNivel3 = pNivel2->AddChild("IE");
   pNivel3->SetText(QyEmitente->FieldByName("inscricao_estadual")->AsString);
   //pNivel3 = pNivel2->AddChild("IEST");
   //pNivel3->SetText();
   if (!VarIsNull(QyEmitente->FieldByName("inscricao_municipal")->Value)) {
      pNivel3 = pNivel2->AddChild("IM");
      pNivel3->SetText(QyEmitente->FieldByName("inscricao_municipal")->AsString);
   }
   //pNivel3 = pNivel2->AddChild("CNAE");
   //pNivel3->SetText();
   pNivel3 = pNivel2->AddChild("CRT");
   pNivel3->SetText(QyEmitente->FieldByName("regime_tributario")->AsString);

   //****************************************************************//
   //     IDENTIFICAÇÃO DO DESTINATÁRIO DA NOTA FISCAL ELETRÔNICA    //
   //****************************************************************//
   pNivel2 = pNivel1->AddChild("dest");
   if (QyDestinatario->FieldByName("tipo_pessoa")->AsString == "J") {
      pNivel3 = pNivel2->AddChild("CNPJ");
   } else {
      pNivel3 = pNivel2->AddChild("CPF");
   }
   pNivel3->SetText(QyDestinatario->FieldByName("cpf_cnpj")->AsString);
   pNivel3 = pNivel2->AddChild("xNome");
   pNivel3->SetText(QyDestinatario->FieldByName("den_cliente")->AsString);
   pNivel3 = pNivel2->AddChild("enderDest");
   //Endereço do destinatário
   pNivel4 = pNivel3->AddChild("xLgr");
   pNivel4->SetText(QyDestinatario->FieldByName("logradouro")->AsString);
   pNivel4 = pNivel3->AddChild("nro");
   pNivel4->SetText(QyDestinatario->FieldByName("numero")->AsString);
   if (!VarIsNull(QyDestinatario->FieldByName("complemento")->Value)) {
      pNivel4 = pNivel3->AddChild("xCpl");
      pNivel4->SetText(QyDestinatario->FieldByName("complemento")->AsString);
   }
   pNivel4 = pNivel3->AddChild("xBairro");
   pNivel4->SetText(QyDestinatario->FieldByName("bairro")->AsString);

   pNivel4 = pNivel3->AddChild("cMun");
   if (QyDestinatario->FieldByName("cod_uf")->AsString == "EX")
      pNivel4->SetText("9999999");
   else
      pNivel4->SetText(QyDestinatario->FieldByName("cod_ibge")->AsString);

   pNivel4 = pNivel3->AddChild("xMun");
   if (QyDestinatario->FieldByName("cod_uf")->AsString == "EX")
      pNivel4->SetText("EXTERIOR");
   else 
      pNivel4->SetText(QyDestinatario->FieldByName("den_cidade")->AsString);

   pNivel4 = pNivel3->AddChild("UF");
   pNivel4->SetText(QyDestinatario->FieldByName("cod_uf")->AsString);
   if (!VarIsNull(QyDestinatario->FieldByName("cep")->Value)) {
      pNivel4 = pNivel3->AddChild("CEP");
      pNivel4->SetText(QyDestinatario->FieldByName("cep")->AsString);
   }
   pNivel4 = pNivel3->AddChild("cPais");
   pNivel4->SetText("1058");
   pNivel4 = pNivel3->AddChild("xPais");
   pNivel4->SetText("Brasil");
   if (!VarIsNull(QyDestinatario->FieldByName("telefone")->Value)) {
      pNivel4 = pNivel3->AddChild("fone");
      pNivel4->SetText(QyDestinatario->FieldByName("telefone")->AsString);
   }
   //Fim endereço
   pNivel3 = pNivel2->AddChild("IE");
   pNivel3->SetText(QyDestinatario->FieldByName("rg_ie")->AsString);
   //pNivel3 = pNivel2->AddChild("ISUF");
   //pNivel3->SetText();
   if (!VarIsNull(QyDestinatario->FieldByName("email")->Value)) {
      pNivel3 = pNivel2->AddChild("email");
      pNivel3->SetText(QyDestinatario->FieldByName("email")->AsString);
   }
//   //****************************************************************//
//   //              IDENTIFICAÇÃO DO LOCAL DE RETIRADA                //
//   //****************************************************************//
//   pNivel2 = pNivel1->AddChild("retirada");
//   pNivel3 = pNivel2->AddChild("CNPJ");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("CPF");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xLgr");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xCpl");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xBairro");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("cMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("UF");
//   pNivel3->SetText();

//   //****************************************************************//
//   //              IDENTIFICAÇÃO DO LOCAL DE ENTREGA                 //
//   //****************************************************************//
//   pNivel2 = pNivel1->AddChild("entrega");
//   pNivel3 = pNivel2->AddChild("CNPJ");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("CPF");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xLgr");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xCpl");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xBairro");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("cMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("UF");
//   pNivel3->SetText();

   //****************************************************************//
   //           IDENTIFICAÇÃO DOS PRODUTOS DA NOTA FISCAL            //
   //****************************************************************//
   while (!QyItemNotaFiscal->Eof) {
      pNivel2 = pNivel1->AddChild("det");
      pNivel2->Attributes["nItem"] = WideString(QyItemNotaFiscal->FieldByName("seq_produto")->AsString);
      pNivel3 = pNivel2->AddChild("prod");
      //Informações do produto
      pNivel4 = pNivel3->AddChild("cProd");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_produto")->AsString);
      pNivel4 = pNivel3->AddChild("cEAN"); // Por ora vai ficar vazio
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_ean")->AsString);
      pNivel4 = pNivel3->AddChild("xProd");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("den_produto")->AsString);
      pNivel4 = pNivel3->AddChild("NCM");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_ncm")->AsString);
      if (!VarIsNull(QyItemNotaFiscal->FieldByName("cod_extipi")->Value)) {
         pNivel4 = pNivel3->AddChild("EXTIPI");
         pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_extipi")->AsString);
      }
      pNivel4 = pNivel3->AddChild("CFOP");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_cfop")->AsString);
      pNivel4 = pNivel3->AddChild("uCom");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_unid_medida")->AsString);
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("qtd_produto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("qCom");
      pNivel4->SetText(sStrAux);
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_unitario")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("vUnCom");
      pNivel4->SetText(sStrAux);
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_total")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("vProd");
      pNivel4->SetText(sStrAux);
      pNivel4 = pNivel3->AddChild("cEANTrib"); // Por ora vai ficar vazio
      pNivel4 = pNivel3->AddChild("uTrib");
      pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_unid_medida")->AsString);
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("qtd_produto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("qTrib");
      pNivel4->SetText(sStrAux);
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_unitario")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("vUnTrib");
      pNivel4->SetText(sStrAux);
      if (QyItemNotaFiscal->FieldByName("valor_frete")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_frete")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
         pNivel4 = pNivel3->AddChild("vFrete");
         pNivel4->SetText(sStrAux);
      }
      if (QyItemNotaFiscal->FieldByName("valor_seguro")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_seguro")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
         pNivel4 = pNivel3->AddChild("vSeg");
         pNivel4->SetText(sStrAux);
      }
      if (QyItemNotaFiscal->FieldByName("valor_desconto")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_desconto")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
         pNivel4 = pNivel3->AddChild("vDesc");
         pNivel4->SetText(sStrAux);
      }
      //pNivel4 = pNivel3->AddChild("vOutro"); //Por ora não tem o campo "Outras despesas acessórias"
      //pNivel4->SetText(sStrAux);
      
      pNivel4 = pNivel3->AddChild("indTot");
      pNivel4->SetText("1"); //A princípio sempre compõe o valor da NF

      if (QyItemNotaFiscal->FieldByName("cod_pedido")->AsInteger > 0) {
         pNivel4 = pNivel3->AddChild("xPed");
         pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_pedido")->AsString);
         pNivel4 = pNivel3->AddChild("nItemPed");
         pNivel4->SetText(QyItemNotaFiscal->FieldByName("seq_pedido")->AsString);
      }

      pNivel3 = pNivel2->AddChild("imposto");
      //Impostos do item
      pNdICMS   = NULL;
      pNdIPI    = NULL;
      pNdPIS    = NULL;
      pNdCOFINS = NULL;
      //Se não carregar os impostos deste item retorna
      if (!GetDadosImpostoItem(QyItemNotaFiscal->FieldByName("seq_produto")->AsInteger))
         return false;
      while (!QyImpostoItem->Eof) {
         //****************************************************************//
         //       IDENTIFICAÇÃO DO ICMS DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "ICMS") {
            pNdICMS = pXmlNFe->CreateElement("ICMS",pXmlNFe->DocumentElement->NamespaceURI);
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            //Somente para o simples nacional por enquanto
            sStrAux = "ICMSSN" + sCST;
            pNivel4 = pNdICMS->AddChild(sStrAux);
            pNivel5 = pNivel4->AddChild("orig");
            pNivel5->SetText(QyItemNotaFiscal->FieldByName("origem_mercadoria")->AsString);
            pNivel5 = pNivel4->AddChild("CSOSN");
            pNivel5->SetText(sCST);
            
            switch(StrToInt(sCST)) {
               case 101:
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("pCredSN");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vCredICMSSN");
                  pNivel5->SetText(sStrAux);
                  break;
               case 102:
               case 103:
               case 300:
               case 400:
                  //Não faz nada
                  break;
               case 201:
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.30
//                IF mr_t_trib_sn.pmvast > 0 THEN
//                   PRINT COLUMN 001,  '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'                #245.31
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'          #245.32
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.33
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.34
//                PRINT COLUMN 001,     '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'             #245.35
//                PRINT COLUMN 001,     '<pCredSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pCredSN) CLIPPED ,'</pCredSN>'             #245.36
//                PRINT COLUMN 001,     '<vCredICMSSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vCredICMSSN) CLIPPED ,'</vCredICMSSN>' #245.37
                  break;
               case 202:
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.41
//                IF mr_t_trib_sn.pmvast > 0  THEN
//                   PRINT COLUMN 001,     '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'             #245.42
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,     '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'       #245.43
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.44
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.45
//                PRINT COLUMN 001,     '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'             #245.46
                  break;
               case 500:
//                 PRINT COLUMN 001,     '<vBCSTRet>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCSTRet) CLIPPED ,'</vBCSTRet>'          #245.50
//                 PRINT COLUMN 001,     '<vICMSSTRet>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSSTRet) CLIPPED ,'</vICMSSTRet>'    #245.51
                 break;
               case 900:
//                PRINT COLUMN 001,     '<modBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.MODBC) CLIPPED ,'</modBC>'                   #245.55
//                PRINT COLUMN 001,     '<vBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.VBC) CLIPPED ,'</vBC>'                         #245.56
//                IF mr_t_trib_sn.PREDBC > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.PREDBC) CLIPPED ,'</pRedBC>'                #245.57
//                END IF
//                PRINT COLUMN 001,     '<pICMS>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.Aliquota) CLIPPED ,'</pICMS>'                #245.58
//                PRINT COLUMN 001,     '<vICMS>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.Valor) CLIPPED ,'</vICMS>'                   #245.59
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.60
//                IF mr_t_trib_sn.pmvast > 0 THEN
//                   PRINT COLUMN 001,  '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'                #245.61
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'          #245.62
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.63
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.64
//                PRINT COLUMN 001,      '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'            #245.65
//                PRINT COLUMN 001,     '<pCredSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pCredSN) CLIPPED ,'</pCredSN>'             #245.52 v2.00
//                PRINT COLUMN 001,     '<vCredICMSSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vCredICMSSN) CLIPPED ,'</vCredICMSSN>' #245.53 v2.00
                  break;
               default:
                  //Não faz nada
                  break;
            }
         } // FIM ICMS
         else
         //****************************************************************//
         //        IDENTIFICAÇÃO DO IPI DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "IPI") {
            pNdIPI = pXmlNFe->CreateElement("IPI",pXmlNFe->DocumentElement->NamespaceURI);
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            if (!VarIsNull(QyItemNotaFiscal->FieldByName("classe_enq_ipi")->Value)) {
               pNivel4 = pNdIPI->AddChild("clEnq");
               pNivel4->SetText(QyItemNotaFiscal->FieldByName("classe_enq_ipi")->AsString);
            }
            //pNivel4 = pNdIPI->AddChild("CNPJProd");
            //pNivel4 = pNdIPI->AddChild("cSelo");
            //pNivel4 = pNdIPI->AddChild("qSelo");
            pNivel4 = pNdIPI->AddChild("cEnq");
            if (!VarIsNull(QyItemNotaFiscal->FieldByName("cod_enq_ipi")->Value)) {
               pNivel4->SetText(QyItemNotaFiscal->FieldByName("cod_enq_ipi")->AsString);
            } else {
               pNivel4->SetText("999");
            }
            if (sCST == "00" || sCST == "49" ||
                sCST == "50" || sCST == "99") {
               pNivel4 = pNdIPI->AddChild("IPITrib");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vBC");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("pIPI");
                  pNivel5->SetText(sStrAux);
               } else {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("qUnid");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vUnid");
                  pNivel5->SetText(sStrAux);
               }
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vIPI");
               pNivel5->SetText(sStrAux);
            } else {
               pNivel4 = pNdIPI->AddChild("IPINT");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
            }          
         } // FIM IPI
         else
         //****************************************************************//
         //        IDENTIFICAÇÃO DO PIS DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "PIS") {
            pNdPIS = pXmlNFe->CreateElement("PIS",pXmlNFe->DocumentElement->NamespaceURI);
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            if (sCST == "01" || sCST == "02") {
               pNivel4 = pNdPIS->AddChild("PISAliq");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vBC");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("pPIS");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vPIS");
               pNivel5->SetText(sStrAux);
            } else if (sCST == "03") {
               pNivel4 = pNdPIS->AddChild("PISQtde");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("qBCProd");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vAliqProd");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vPIS");
               pNivel5->SetText(sStrAux);
            } else if (sCST == "04" || sCST == "06" ||
               sCST == "07" || sCST == "08" || sCST == "09") {
               pNivel4 = pNdPIS->AddChild("PISNT");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
            } else {               
               pNivel4 = pNdPIS->AddChild("PISOutr");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vBC");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("pPIS");
                  pNivel5->SetText(sStrAux);
               } else {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("qBCProd");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vAliqProd");
                  pNivel5->SetText(sStrAux);
               }
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vPIS");
               pNivel5->SetText(sStrAux);
            }
         } // FIM PIS
         else
         //****************************************************************//
         //       IDENTIFICAÇÃO DO COFINS DOS PRODUTOS DA NOTA FISCAL      //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "COFINS") {
            pNdCOFINS = pXmlNFe->CreateElement("COFINS",pXmlNFe->DocumentElement->NamespaceURI);
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            if (sCST == "01" || sCST == "02") {
               pNivel4 = pNdCOFINS->AddChild("COFINSAliq");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vBC");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("pCOFINS");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vCOFINS");
               pNivel5->SetText(sStrAux);
            } else if (sCST == "03") {
               pNivel4 = pNdCOFINS->AddChild("COFINSQtde");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("qBCProd");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vAliqProd");
               pNivel5->SetText(sStrAux);
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vCOFINS");
               pNivel5->SetText(sStrAux);
            } else if (sCST == "04" || sCST == "06" ||
               sCST == "07" || sCST == "08" || sCST == "09") {
               pNivel4 = pNdCOFINS->AddChild("COFINSNT");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
            } else {               
               pNivel4 = pNdCOFINS->AddChild("COFINSOutr");
               pNivel5 = pNivel4->AddChild("CST");
               pNivel5->SetText(sCST);
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vBC");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("pCOFINS");
                  pNivel5->SetText(sStrAux);
               } else {
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("qBCProd");
                  pNivel5->SetText(sStrAux);
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  pNivel5 = pNivel4->AddChild("vAliqProd");
                  pNivel5->SetText(sStrAux);
               }
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               pNivel5 = pNivel4->AddChild("vCOFINS");
               pNivel5->SetText(sStrAux);
            }
         }
         QyImpostoItem->Next();
      }
      //Deve adicionar os impostos no item
      if (pNdICMS != NULL)
         pNivel3->ChildNodes->Add(pNdICMS);
      if (pNdIPI != NULL)
         pNivel3->ChildNodes->Add(pNdIPI);
      if (pNdPIS != NULL)
         pNivel3->ChildNodes->Add(pNdPIS);
      if (pNdCOFINS != NULL)
         pNivel3->ChildNodes->Add(pNdCOFINS);
      QyItemNotaFiscal->Next();
   }

   //****************************************************************//
   //     INFORMAÇÕES DO TOTAL DA NOTA FISCAL ELETRÔNICA             //
   //****************************************************************//
   pNivel2 = pNivel1->AddChild("total");
   pNivel3 = pNivel2->AddChild("ICMSTot");
   //Impostos todos zerados por enquanto
   pNivel4 = pNivel3->AddChild("vBC");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vICMS");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vBCST");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vST");
   pNivel4->SetText("0.00");
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_mercadoria")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vProd");
   pNivel4->SetText(sStrAux);
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_frete")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vFrete");
   pNivel4->SetText(sStrAux);
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_seguro")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vSeg");
   pNivel4->SetText(sStrAux);
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_desconto")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vDesc");
   pNivel4->SetText(sStrAux);
   //Impostos todos zerados por enquanto
   pNivel4 = pNivel3->AddChild("vII");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vIPI");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vPIS");
   pNivel4->SetText("0.00");
   pNivel4 = pNivel3->AddChild("vCOFINS");
   pNivel4->SetText("0.00");
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("outras_despesas")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vOutro");
   pNivel4->SetText(sStrAux);
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_nota_fiscal")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   pNivel4 = pNivel3->AddChild("vNF");
   pNivel4->SetText(sStrAux);

   //****************************************************************//
   //     INFORMAÇÕES DO TRANSPORTE DA NOTA FISCAL ELETRÔNICA        //
   //****************************************************************//
   pNivel2 = pNivel1->AddChild("transp");
   pNivel3 = pNivel2->AddChild("modFrete");
   pNivel3->SetText(QyNotaFiscal->FieldByName("tipo_frete")->AsString);

//          WHEN l_tipo_registro = "X.A"
//             PRINT COLUMN 001,     '<transporta>'                                                                                        #358
//             IF mr_t_transporte_nfe.Cnpj IS NOT NULL AND
//                mr_t_transporte_nfe.Cnpj <> " " AND
//                mr_t_transporte_nfe.Cnpj > 0 THEN
//                PRINT COLUMN 001,    '<CNPJ>',mr_t_transporte_nfe.Cnpj CLIPPED,'</CNPJ>'                                                 #359
//             END IF
//             IF mr_t_transporte_nfe.CPF IS NOT NULL AND
//                mr_t_transporte_nfe.CPF <> " " AND
//                mr_t_transporte_nfe.CPF > 0 THEN
//                PRINT COLUMN 001,    '<CPF>',mr_t_transporte_nfe.CPF CLIPPED,'</CPF>'                                                    #360
//             END IF
//             IF mr_t_transporte_nfe.Nome IS NOT NULL AND mr_t_transporte_nfe.Nome <> " " THEN
//                PRINT COLUMN 001,    '<xNome>',obf9246_retira_espacos(mr_t_transporte_nfe.Nome CLIPPED) CLIPPED,'</xNome>'               #361
//             END IF
//             IF mr_t_transporte_nfe.Ie IS NOT NULL AND mr_t_transporte_nfe.Ie <> " " THEN
//                PRINT COLUMN 001,    '<IE>',mr_t_transporte_nfe.Ie CLIPPED,'</IE>'                                                       #362
//             END IF
//             IF mr_t_transporte_nfe.ender IS NOT NULL AND mr_t_transporte_nfe.ender <> " " THEN
//                PRINT COLUMN 001,    '<xEnder>',obf9246_retira_espacos(mr_t_transporte_nfe.ender CLIPPED) CLIPPED,'</xEnder>'            #363
//             END IF
//             IF mr_t_transporte_nfe.mun IS NOT NULL AND mr_t_transporte_nfe.mun <> " " THEN
//                PRINT COLUMN 001,    '<xMun>',obf9246_retira_espacos(mr_t_transporte_nfe.mun CLIPPED) CLIPPED,'</xMun>'                  #364
//             END IF
//             IF mr_t_transporte_nfe.Uf IS NOT NULL AND mr_t_transporte_nfe.Uf <> " " THEN
//                PRINT COLUMN 001,    '<UF>',mr_t_transporte_nfe.Uf CLIPPED,'</UF>'                                                        #365
//             END IF
//             PRINT COLUMN 001,     '</transporta>'

//          WHEN l_tipo_registro = "X.1"
//
//             PRINT COLUMN 001,     '<retTransp>'                                                                                        #366
//             PRINT COLUMN 001,       '<vServ>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Vserv),'</vServ>'                        #367
//             PRINT COLUMN 001,       '<vBCRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.VBC),'</vBCRet>'                        #368
//             PRINT COLUMN 001,       '<pICMSRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Aliquota),'</pICMSRet>'               #369
//             PRINT COLUMN 001,       '<vICMSRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Valor),'</vICMSRet>'                  #370
//             PRINT COLUMN 001,       '<CFOP>',mr_t_trib_transp.Cfop CLIPPED,'</CFOP>'                                                    #371
//             PRINT COLUMN 001,       '<cMunFG>',mr_t_trib_transp.CMUNFG CLIPPED,'</cMunFG>'                                              #372
//             PRINT COLUMN 001,     '</retTransp>'

   if (!VarIsNull(QyNotaFiscal->FieldByName("placa_veiculo")->Value)) {
      pNivel3 = pNivel2->AddChild("veicTransp");
      pNivel4 = pNivel3->AddChild("placa");
      pNivel4->SetText(QyNotaFiscal->FieldByName("placa_veiculo")->AsString);
      pNivel4 = pNivel3->AddChild("UF");
      pNivel4->SetText(QyNotaFiscal->FieldByName("estado_placa_veiculo")->AsString);
      //pNivel4 = pNivel3->AddChild("RNTC");
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("placa_reboque")->Value)) {
      pNivel3 = pNivel2->AddChild("reboque");
      pNivel4 = pNivel3->AddChild("placa");
      pNivel4->SetText(QyNotaFiscal->FieldByName("placa_reboque")->AsString);
      pNivel4 = pNivel3->AddChild("UF");
      pNivel4->SetText(QyNotaFiscal->FieldByName("estado_placa_reboque")->AsString);
      //pNivel4 = pNivel3->AddChild("RNTC");
   }
   //Faz assim, pois pode ser que não tenha nehhum filho pro volume
   pNivel3 = pXmlNFe->CreateElement("vol",pXmlNFe->DocumentElement->NamespaceURI);
   if (QyNotaFiscal->FieldByName("qtd_volume")->AsInteger > 0) {
      pNivel4 = pNivel3->AddChild("qVol");
      pNivel4->SetText(QyNotaFiscal->FieldByName("qtd_volume")->AsString);
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("especie_volume")->Value)) {
      pNivel4 = pNivel3->AddChild("esp");
      pNivel4->SetText(QyNotaFiscal->FieldByName("especie_volume")->AsString);
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("marca_volume")->Value)) {
      pNivel4 = pNivel3->AddChild("marca");
      pNivel4->SetText(QyNotaFiscal->FieldByName("marca_volume")->AsString);
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("numeracao_volume")->Value)) {
      pNivel4 = pNivel3->AddChild("nVol");
      pNivel4->SetText(QyNotaFiscal->FieldByName("numeracao_volume")->AsString);
   }
   if (QyNotaFiscal->FieldByName("peso_liquido")->AsFloat > 0) {
      sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("peso_liquido")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("pesoL");
      pNivel4->SetText(sStrAux);
   }
   if (QyNotaFiscal->FieldByName("peso_bruto")->AsFloat > 0) {
      sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("peso_bruto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      pNivel4 = pNivel3->AddChild("pesoB");
      pNivel4->SetText(sStrAux);
   }
//          WHEN l_tipo_registro = "X.5"
//             PRINT COLUMN 001,       '<lacres>'
//
//          WHEN l_tipo_registro = "X.6"                                                                                                #387a
//             PRINT COLUMN 001,          '<nLacre>',obf9246_retira_espacos(mr_t_lacres_transp.Lacre CLIPPED) CLIPPED,'</nLacre>'       #388
//
//          WHEN l_tipo_registro = "X.7"
//             PRINT COLUMN 001,       '</lacres>'
   //Se adicionou algum filho deve adicionar no xml
   if (pNivel3->ChildNodes->Count > 0)
      pNivel2->ChildNodes->Add(pNivel3);

   //****************************************************************//
   //       INFORMAÇÕES ADICIONAIS DA NOTA FISCAL ELETRÔNICA         //
   //****************************************************************//
   if ((!VarIsNull(QyNotaFiscal->FieldByName("info_complementar")->Value)) || 
       (!VarIsNull(QyNotaFiscal->FieldByName("info_adicional_fisco")->Value))) {
      pNivel2 = pNivel1->AddChild("infAdic");        
      if (!VarIsNull(QyNotaFiscal->FieldByName("info_adicional_fisco")->Value)) {
         pNivel3 = pNivel2->AddChild("infAdFisco");
         pNivel3->SetText(QyNotaFiscal->FieldByName("info_adicional_fisco")->AsString);
      }
      if (!VarIsNull(QyNotaFiscal->FieldByName("info_complementar")->Value)) {
         pNivel3 = pNivel2->AddChild("infCpl");
         pNivel3->SetText(QyNotaFiscal->FieldByName("info_complementar")->AsString);
      }
   }

   //****************************************************************//
   //       INFORMAÇÕES ASSINATURA DA NOTA FISCAL ELETRÔNICA         //
   //****************************************************************//
   pNivel1 = pXmlNFe->CreateElement("Signature","http://www.w3.org/2000/09/xmldsig#");
   pNodeNFe->ChildNodes->Add(pNivel1);
   pNivel2 = pNivel1->AddChild("SignedInfo");
   pNivel3 = pNivel2->AddChild("CanonicalizationMethod");
   pNivel3->Attributes["Algorithm"] = WideString("http://www.w3.org/TR/2001/REC-xml-c14n-20010315");
   pNivel3 = pNivel2->AddChild("SignatureMethod");
   pNivel3->Attributes["Algorithm"] = WideString("http://www.w3.org/2000/09/xmldsig#rsa-sha1");
   pNivel3 = pNivel2->AddChild("Reference");
   pNivel3->Attributes["URI"] = WideString("#NFe" + sChaveNFe);
   pNivel4 = pNivel3->AddChild("Transforms");
   pNivel5 = pNivel4->AddChild("Transform");
   pNivel5->Attributes["Algorithm"] = WideString("http://www.w3.org/2000/09/xmldsig#enveloped-signature");
   pNivel5 = pNivel4->AddChild("Transform");
   pNivel5->Attributes["Algorithm"] = WideString("http://www.w3.org/TR/2001/REC-xml-c14n-20010315");
   pNivel4 = pNivel3->AddChild("DigestMethod");
   pNivel4->Attributes["Algorithm"] = WideString("http://www.w3.org/2000/09/xmldsig#sha1");
   pNivel4 = pNivel3->AddChild("DigestValue");
   
   pNivel2 = pNivel1->AddChild("SignatureValue");
   
   pNivel2 = pNivel1->AddChild("KeyInfo");
   pNivel3 = pNivel2->AddChild("X509Data");
   pNivel4 = pNivel3->AddChild("X509Certificate");

   String sCertificate = "\
MIIH/DCCBeSgAwIBAgIIRalYSun5ghEwDQYJKoZIhvcNAQELBQAwdTELMAkGA1UEBhMCQlIxEzAR\
BgNVBAoTCklDUC1CcmFzaWwxNjA0BgNVBAsTLVNlY3JldGFyaWEgZGEgUmVjZWl0YSBGZWRlcmFs\
IGRvIEJyYXNpbCAtIFJGQjEZMBcGA1UEAxMQQUMgU0VSQVNBIFJGQiB2MjAeFw0xMjA3MTgyMTAw\
MDBaFw0xNTA3MTgyMTAwMDBaMIHvMQswCQYDVQQGEwJCUjELMAkGA1UECBMCU0MxDzANBgNVBAcT\
BklUQUpBSTETMBEGA1UEChMKSUNQLUJyYXNpbDE2MDQGA1UECxMtU2VjcmV0YXJpYSBkYSBSZWNl\
aXRhIEZlZGVyYWwgZG8gQnJhc2lsIC0gUkZCMRYwFAYDVQQLEw1SRkIgZS1DTlBKIEEzMRIwEAYD\
VQQLEwlBUiBTRVJBU0ExSTBHBgNVBAMTQEJNTFggRElTVFJJQlVJRE9SQSBERSBBQ0VTU09SSU9T\
IERBIE1PREEgTFREQSBFUFA6MTU1NDMzMDUwMDAxMTcwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAw\
ggEKAoIBAQCWgMg++N+AjbWXbE6+NBoSbRuk3rAXSa+MN2z1fOq/oq476NwL93PJthx45Jhm3Je6\
ajYV99SPw19niCTuaRMIy/DZtIDZeeVkCryngMEfQ0IAmbvQympdY4waR8l/x8L0Cft8KKbGJVxU\
JILI533W4KNBXJD0KasJhQ2v2n240peLj6F1Kx5Jjq3v+WWvRJdTSv6vU7y0X8LsL5LTxkaDtKTm\
vt617f4P8HBmnQmeGqQTMUSNHGloy+0GmHrXdSYt2IATwyHOuT4rTU1FxkUA0Vo891l77vlrZwRq\
bNCgmpTdSZSUe5MvKL5fejwgpy1vYFWlc3aP2Kdy5Uqk5LGFAgMBAAGjggMTMIIDDzCBmQYIKwYB\
BQUHAQEEgYwwgYkwSAYIKwYBBQUHMAKGPGh0dHA6Ly93d3cuY2VydGlmaWNhZG9kaWdpdGFsLmNv\
bS5ici9jYWRlaWFzL3NlcmFzYXJmYnYyLnA3YjA9BggrBgEFBQcwAYYxaHR0cDovL29jc3AuY2Vy\
dGlmaWNhZG9kaWdpdGFsLmNvbS5ici9zZXJhc2FyZmJ2MjAJBgNVHRMEAjAAMB8GA1UdIwQYMBaA\
FLKgxD1GnnzIhWwIHhAylGVGcEFzMHEGA1UdIARqMGgwZgYGYEwBAgMKMFwwWgYIKwYBBQUHAgEW\
Tmh0dHA6Ly9wdWJsaWNhY2FvLmNlcnRpZmljYWRvZGlnaXRhbC5jb20uYnIvcmVwb3NpdG9yaW8v\
ZHBjL2RlY2xhcmFjYW8tcmZiLnBkZjCB8wYDVR0fBIHrMIHoMEqgSKBGhkRodHRwOi8vd3d3LmNl\
cnRpZmljYWRvZGlnaXRhbC5jb20uYnIvcmVwb3NpdG9yaW8vbGNyL3NlcmFzYXJmYnYyLmNybDBE\
oEKgQIY+aHR0cDovL2xjci5jZXJ0aWZpY2Fkb3MuY29tLmJyL3JlcG9zaXRvcmlvL2xjci9zZXJh\
c2FyZmJ2Mi5jcmwwVKBSoFCGTmh0dHA6Ly9yZXBvc2l0b3Jpby5pY3BicmFzaWwuZ292LmJyL2xj\
ci9TZXJhc2EvcmVwb3NpdG9yaW8vbGNyL3NlcmFzYXJmYnYyLmNybDAOBgNVHQ8BAf8EBAMCBeAw\
HQYDVR0lBBYwFAYIKwYBBQUHAwIGCCsGAQUFBwMEMIGsBgNVHREEgaQwgaGBEUJSVU5PQFZMTlku\
Q09NLkJSoB4GBWBMAQMCoBUTE0JSVU5PIEVEVUFSRE8gSkVSS0WgGQYFYEwBAwOgEBMOMTU1NDMz\
MDUwMDAxMTegOAYFYEwBAwSgLxMtMTMxMTE5ODcwNjUyMTgwNDkzNjAwMDAwMDAwMDAwMDAwMDAw\
MDAwMDAwMDAwoBcGBWBMAQMHoA4TDDAwMDAwMDAwMDAwMDANBgkqhkiG9w0BAQsFAAOCAgEAEcnQ\
BEmbo7dfWuZUpsyvnEtLcxLMmYGP1EZLnY9VnHrSAlTyeF5OYNmeZQNKru33xyCWxe+g+836T2sk\
fXxM+iKT5NAeqjZ6j3n2Rowge1TG9E/gTqoeFYR9GeXI/8KN8wlrRuS7iuXI9ACXZACh3mau3XFH\
3RfkoyaTFhpyIUABW1Zs26L+C1AurR2Sz67kVa2zj8gIF1Y/9xblAwz5J1StuTHoWv31jHmtEuYy\
2Zq9YO310tZA3KNRs9g/qIT489+/5HnvAEns/de/+C2guKpPRnYjlFIBLIPaoBIkq0uPFohCq4SJ\
wL3r8EwiqCb+8kUGMYAiOEb4kdRMdYdEJ/2cc0ocil9ZRrk8bBscqKRyiNrX0WoQutP9UftwG4fk\
RE1eB6adDZe1QWajeOT6uw+/Ukrwu5nPHDngNUbDVM1wFqdXZzqi5cpkkq9wKQvtB9mhacaBdHFK\
kgvb0zuF4jBUytU/DzmeWkPNbKezf5W2XJ0nrkN1I1AmFFFVmDNSWdznw9HjxJnr+X/x8DV5RMsD\
KrNbrpKOyP4hHXf69tsg5kHLj3EwNlCZ/zPfJiUBPEDkKup0khITzeOoH5GXvt8d8uskHlyk56gp\
2ba3KfEPikF7+GEIQmr9lkNKPqvhy5rNyleQK1QE08ITVCSnZ8DdwTx16M45DLl2KAYnotw=";

   pNivel4->SetText(sCertificate);
   
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::LoadNfeToTxt()
{
   String sStrLine;
   String sStrAux;
   String sCST;
   int iSerieNF = 0;
   int iDV = 0;
struct TxtICMS {
   String StrICMS;
};
   struct TipoIPI {
      String StrValIPI;
   };
struct TxtIPI {
   String StrIPI;
   String StrTipoIPI;
   TipoIPI *pTipoIPI;
};
   struct TipoPIS {
      String StrValPIS;
   };
struct TxtPIS {
   String StrPIS;
   String StrTipoPIS;
   TipoPIS *pTipoPIS;
};
   struct TipoCOFINS {
      String StrValCOFINS;
   };
struct TxtCOFINS {
   String StrCOFINS;
   String StrTipoCOFINS;
   TipoCOFINS *pTipoCOFINS;
};
   TxtICMS *pTxtICMS;
   TxtIPI *pTxtIPI;
   TxtPIS *pTxtPIS;
   TxtCOFINS *pTxtCOFINS;

   if (!GetDadosNotaFiscal())
      return false;
   if (!GetDadosEmitente())
      return false;
   if (!GetDadosDestinatario())
      return false;
   if (!GetDadosItemNotaFiscal())
      return false;

   sChaveNFe = "";
   //Montagem da Chave da NFe
   // UF (IBGE) | AAMM Emissão | CNPJ Emit | Modelo | Série | Num NF | Forma Emissão | Cod Num | DV |
   //    02     |      04      |     14    |   02   |  03   |   09   |       01      |    08   | 01 |
   if (QyEmitente->FieldByName("cod_ibge_uf")->AsString.Length() == 0) {
      MessageBox(NULL,"Informe o código do IBGE no estado da empresa emitente!","Emitente",APP_ATENTION);
      return false;
   }
   //Código IBGE UF Emissão
   sChaveNFe += QyEmitente->FieldByName("cod_ibge_uf")->AsString;
   //Ano/Mês emissão
   sStrAux = "";
   DateTimeToString(sStrAux, "yymm", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
   sChaveNFe += sStrAux;
   //CNPJ Emitente
   sChaveNFe += QyEmitente->FieldByName("cnpj")->AsString;
   //Modelo da NFe - Fixo 55
   sChaveNFe += "55";
   //Série da NF
   iSerieNF = QyNotaFiscal->FieldByName("serie_nota_fiscal")->AsInteger;
   sStrAux = Format("%3.3d",ARRAYOFCONST(((int)iSerieNF)));
   sChaveNFe += sStrAux;
   //Número da NF
   sStrAux = Format("%9.9d",ARRAYOFCONST(((int)QyNotaFiscal->FieldByName("num_nota_fiscal")->AsInteger)));
   sChaveNFe += sStrAux;
   //Forma de emissão da NFe
   sChaveNFe += "1"; //Sempre normal
   //Código numérico da NF - Serial do banco
   sStrAux = Format("%8.8d",ARRAYOFCONST(((int)iCodNotaFiscal)));
   sChaveNFe += sStrAux;
   //Digito Verificador
   CalcChaveNFe(iDV);
   sChaveNFe += IntToStr(iDV);

   sFileName = "nfe\\NFe" + sChaveNFe + ".txt";

   //Criando o arquivo texto
   if (!SaveTxtFile())
      return false;
   //Informações da NFe
   if (!WriteTxtLine("NOTAFISCAL|1")) return false;
   //A|versão do schema|id|
   sStrLine = "A|2.00|NFe" + sChaveNFe + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;

   //************************************************************//
   //         IDENTIFICAÇÃO DA NOTA FISCAL ELETRÔNICA            //
   //************************************************************//
   //B|cUF|cNF|NatOp|intPag|mod|serie|nNF|dEmi|dSaiEnt|hSaiEnt|tpNF|cMunFG|TpImp|TpEmis|cDV|tpAmb|finNFe|procEmi|VerProc|dhCont|xJust|
   sStrLine = "B|" + QyEmitente->FieldByName("cod_ibge_uf")->AsString + "|" + \
              Format("%8.8d",ARRAYOFCONST(((int)iCodNotaFiscal))) + "|" + \
              QyNotaFiscal->FieldByName("den_natureza_operacao")->AsString + "|" + \
              QyNotaFiscal->FieldByName("cod_forma_pagto")->AsString + "|" + \
              "55|" + IntToStr(iSerieNF) + "|" + \
              QyNotaFiscal->FieldByName("num_nota_fiscal")->AsString + "|";
   sStrAux = "";
   DateTimeToString(sStrAux, "yyyy-mm-dd", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
   sStrLine = sStrLine + sStrAux + "|";

   if (!VarIsNull(QyNotaFiscal->FieldByName("data_hora_emissao")->Value)) {
      sStrAux = "";
      DateTimeToString(sStrAux, "yyyy-mm-dd", QyNotaFiscal->FieldByName("data_hora_emissao")->AsDateTime);
      sStrAux = sStrAux + "|" + TimeToStr(TimeOf(QyNotaFiscal->FieldByName("data_hora_saida")->AsDateTime));
   } else {
      sStrAux = "|";
   }
   sStrLine = sStrLine + sStrAux + "|" + \
              QyNotaFiscal->FieldByName("tipo_nota_fiscal")->AsString + "|" + \
              QyEmitente->FieldByName("cod_ibge")->AsString + "|1|1|" + \
              IntToStr(iDV) +  "|1|1|1|2.2.5|||";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //************************************************************//
   //     IDENTIFICAÇÃO DO EMITENTE DA NOTA FISCAL ELETRÔNICA    //
   //************************************************************//
   //C|XNome|XFant|IE|IEST|IM|CNAE|CRT|
   sStrLine = "C|" + QyEmitente->FieldByName("razao_social")->AsString + "|";
   if (!VarIsNull(QyEmitente->FieldByName("nome_fantasia")->Value)) {
      sStrAux = QyEmitente->FieldByName("nome_fantasia")->AsString;
   } else {
      sStrAux = "";
   }
   sStrLine = sStrLine + sStrAux + "|" + \
              QyEmitente->FieldByName("inscricao_estadual")->AsString + "||";

   if (!VarIsNull(QyEmitente->FieldByName("inscricao_municipal")->Value)) {
      sStrAux = QyEmitente->FieldByName("inscricao_municipal")->AsString;
   } else {
      sStrAux = "";
   }
   sStrLine = sStrLine + sStrAux + "||" + \
              QyEmitente->FieldByName("regime_tributario")->AsString + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //C02|CNPJ|
   sStrLine = "C02|" + QyEmitente->FieldByName("cnpj")->AsString + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //Endereço do emitente
   //C05|XLgr|Nro|Cpl|Bairro|CMun|XMun|UF|CEP|cPais|xPais|fone|
   sStrLine = "C05|" + QyEmitente->FieldByName("logradouro")->AsString + "|" + \
              QyEmitente->FieldByName("numero")->AsString + "|";
   if (!VarIsNull(QyEmitente->FieldByName("complemento")->Value)) {
      sStrAux = QyEmitente->FieldByName("complemento")->AsString;
   } else {
      sStrAux = "";
   }
   sStrLine = sStrLine + sStrAux + "|" + \
              QyEmitente->FieldByName("bairro")->AsString + "|";
   if (QyEmitente->FieldByName("cod_uf")->AsString == "EX")
      sStrAux = "9999999";
   else
      sStrAux = QyEmitente->FieldByName("cod_ibge")->AsString;
   sStrLine = sStrLine + sStrAux + "|";
   if (QyEmitente->FieldByName("cod_uf")->AsString == "EX")
      sStrAux = "EXTERIOR";
   else 
      sStrAux = QyEmitente->FieldByName("den_cidade")->AsString;
   sStrLine = sStrLine + sStrAux + "|" + \
              QyEmitente->FieldByName("cod_uf")->AsString + "|";
   if (!VarIsNull(QyEmitente->FieldByName("cep")->Value)) {
      sStrAux = QyEmitente->FieldByName("cep")->AsString;
   } else {
      sStrAux = "";
   }
   sStrLine = sStrLine + sStrAux + "|1058|Brasil|";
   if (!VarIsNull(QyEmitente->FieldByName("telefone")->Value)) {
      sStrAux = QyEmitente->FieldByName("telefone")->AsString;
   } else {
      sStrAux = "";
   }
   sStrLine = sStrLine + sStrAux + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //Fim endereço

   //****************************************************************//
   //     IDENTIFICAÇÃO DO DESTINATÁRIO DA NOTA FISCAL ELETRÔNICA    //
   //****************************************************************//
   //E|xNome|IE|ISUF|email|
   sStrLine = "E|" + QyDestinatario->FieldByName("den_cliente")->AsString + "|" + \
              QyDestinatario->FieldByName("rg_ie")->AsString + "||" + \
              QyDestinatario->FieldByName("email")->AsString + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   if (QyDestinatario->FieldByName("tipo_pessoa")->AsString == "J") {
      sStrLine = "E02|" + QyDestinatario->FieldByName("cpf_cnpj")->AsString + "|";
   } else {
      sStrLine = "E03|" + QyDestinatario->FieldByName("cpf_cnpj")->AsString + "|";
   }
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //Endereço do destinatário
   //E05|xLgr|nro|xCpl|xBairro|cMun|xMun|UF|CEP|cPais|xPais|fone|
   sStrLine = "E05|" + QyDestinatario->FieldByName("logradouro")->AsString + "|" + \
              QyDestinatario->FieldByName("numero")->AsString + "|" + \
              QyDestinatario->FieldByName("complemento")->AsString + "|" + \
              QyDestinatario->FieldByName("bairro")->AsString + "|";
   if (QyDestinatario->FieldByName("cod_uf")->AsString == "EX")
      sStrAux = "9999999";
   else
      sStrAux = QyDestinatario->FieldByName("cod_ibge")->AsString;
   sStrLine = sStrLine + sStrAux + "|";
   if (QyDestinatario->FieldByName("cod_uf")->AsString == "EX")
      sStrAux = "EXTERIOR";
   else
      sStrAux = QyDestinatario->FieldByName("den_cidade")->AsString;
   sStrLine = sStrLine + sStrAux + "|" + \
              QyDestinatario->FieldByName("cod_uf")->AsString + "|" + \
              QyDestinatario->FieldByName("cep")->AsString + "|1058|Brasil|" + \
              QyDestinatario->FieldByName("telefone")->AsString + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;
   //Fim endereço
//   //****************************************************************//
//   //              IDENTIFICAÇÃO DO LOCAL DE RETIRADA                //
//   //****************************************************************//
//   pNivel2 = pNivel1->AddChild("retirada");
//   pNivel3 = pNivel2->AddChild("CNPJ");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("CPF");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xLgr");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xCpl");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xBairro");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("cMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("UF");
//   pNivel3->SetText();

//   //****************************************************************//
//   //              IDENTIFICAÇÃO DO LOCAL DE ENTREGA                 //
//   //****************************************************************//
//   pNivel2 = pNivel1->AddChild("entrega");
//   pNivel3 = pNivel2->AddChild("CNPJ");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("CPF");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xLgr");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xCpl");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xBairro");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("cMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("xMun");
//   pNivel3->SetText();
//   pNivel3 = pNivel2->AddChild("UF");
//   pNivel3->SetText();

   //****************************************************************//
   //           IDENTIFICAÇÃO DOS PRODUTOS DA NOTA FISCAL            //
   //****************************************************************//
   while (!QyItemNotaFiscal->Eof) {
      //H|nItem|infAdProd|
      sStrLine = "H|" + QyItemNotaFiscal->FieldByName("seq_produto")->AsString + "||";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
      //Informações do produto
      //I|CProd|CEAN|XProd|NCM|EXTIPI|CFOP|UCom|QCom|VUnCom|VProd|CEANTrib|UTrib|QTrib|VUnTrib|VFrete|VSeg|VDesc|vOutro|indTot|xPed|nItemPed|
      sStrLine = "I|" + QyItemNotaFiscal->FieldByName("cod_produto")->AsString + "||" + \
                 QyItemNotaFiscal->FieldByName("den_produto")->AsString + "|" + \
                 QyItemNotaFiscal->FieldByName("cod_ncm")->AsString + "|" + \
                 QyItemNotaFiscal->FieldByName("cod_extipi")->AsString + "|" + \
                 QyItemNotaFiscal->FieldByName("cod_cfop")->AsString + "|" + \
                 QyItemNotaFiscal->FieldByName("cod_unid_medida")->AsString + "|";
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("qtd_produto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + sStrAux + "|";
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_unitario")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + sStrAux + "|";
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_total")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + sStrAux + "||" + \
                 QyItemNotaFiscal->FieldByName("cod_unid_medida")->AsString + "|";
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("qtd_produto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + sStrAux + "|";
      sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_unitario")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,3
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + sStrAux + "|";
      if (QyItemNotaFiscal->FieldByName("valor_frete")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_frete")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      } else {
         sStrAux = "";
      }
      sStrLine = sStrLine + sStrAux + "|";
      if (QyItemNotaFiscal->FieldByName("valor_seguro")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_seguro")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      } else {
         sStrAux = "";
      }
      sStrLine = sStrLine + sStrAux + "|";
      if (QyItemNotaFiscal->FieldByName("valor_desconto")->AsFloat > 0) {
         sStrAux = FloatToStrF(QyItemNotaFiscal->FieldByName("valor_desconto")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
         sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      } else {
         sStrAux = "";
      }
      sStrLine = sStrLine + sStrAux + "||1|"; //Por ora não tem o campo "Outras despesas acessórias"
                                              //A princípio sempre compõe o valor da NF

      if (QyItemNotaFiscal->FieldByName("cod_pedido")->AsInteger > 0) {
         sStrAux = QyItemNotaFiscal->FieldByName("cod_pedido")->AsString + "|" + \
                   QyItemNotaFiscal->FieldByName("seq_pedido")->AsString;
      } else {
         sStrAux = "|";
      }
      sStrLine = sStrLine + sStrAux + "|";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
      if (!WriteTxtLine("M|")) return false;

      //Impostos do item
      pTxtICMS   = NULL;
      pTxtIPI    = NULL;
      pTxtPIS    = NULL;
      pTxtCOFINS = NULL;
      //Se não carregar os impostos deste item retorna
      if (!GetDadosImpostoItem(QyItemNotaFiscal->FieldByName("seq_produto")->AsInteger))
         return false;
      while (!QyImpostoItem->Eof) {
         //****************************************************************//
         //       IDENTIFICAÇÃO DO ICMS DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "ICMS") {
            pTxtICMS = new TxtICMS();
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            //Somente para o simples nacional por enquanto
            switch(StrToInt(sCST)) {
               case 101:
                  //N10c|Orig|CSOSN|pCredSN|vCredICMSSN|
                  sStrLine = "N10c|" + \
                             QyItemNotaFiscal->FieldByName("origem_mercadoria")->AsString + "|" + sCST + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtICMS->StrICMS = sStrLine;
                  break;
               case 102:
               case 103:
               case 300:
               case 400:
                  //N10d|Orig|CSOSN|
                  sStrLine = "N10d|" + \
                             QyItemNotaFiscal->FieldByName("origem_mercadoria")->AsString + "|" + sCST + "|";
                  pTxtICMS->StrICMS = sStrLine;
                  break;
               case 201:
                  //N10e|Orig|CSOSN|modBCST|pMVAST|pRedBCST|vBCST|pICMSST|vICMSST|pCredSN|vCredICMSSN|
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.30
//                IF mr_t_trib_sn.pmvast > 0 THEN
//                   PRINT COLUMN 001,  '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'                #245.31
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'          #245.32
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.33
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.34
//                PRINT COLUMN 001,     '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'             #245.35
//                PRINT COLUMN 001,     '<pCredSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pCredSN) CLIPPED ,'</pCredSN>'             #245.36
//                PRINT COLUMN 001,     '<vCredICMSSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vCredICMSSN) CLIPPED ,'</vCredICMSSN>' #245.37
                  break;
               case 202:
                  //N10f|Orig|CSOSN|modBCST|pMVAST|pRedBCST|vBCST|pICMSST|vICMSST|
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.41
//                IF mr_t_trib_sn.pmvast > 0  THEN
//                   PRINT COLUMN 001,     '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'             #245.42
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,     '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'       #245.43
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.44
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.45
//                PRINT COLUMN 001,     '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'             #245.46
                  break;
               case 500:
                  //N10g|Orig|CSOSN|modBCST|vBCSTRet|vICMSSTRet|
//                 PRINT COLUMN 001,     '<vBCSTRet>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCSTRet) CLIPPED ,'</vBCSTRet>'          #245.50
//                 PRINT COLUMN 001,     '<vICMSSTRet>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSSTRet) CLIPPED ,'</vICMSSTRet>'    #245.51
                 break;
               case 900:
                  //N10h|Orig|CSOSN|modBC|vBC|pRedBC|pICMS|vICMS|modBCST|pMVAST|pRedBCST|vBCST|pICMSST|vICMSST|pCredSN|vCredICMSSN|
//                PRINT COLUMN 001,     '<modBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.MODBC) CLIPPED ,'</modBC>'                   #245.55
//                PRINT COLUMN 001,     '<vBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.VBC) CLIPPED ,'</vBC>'                         #245.56
//                IF mr_t_trib_sn.PREDBC > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBC>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.PREDBC) CLIPPED ,'</pRedBC>'                #245.57
//                END IF
//                PRINT COLUMN 001,     '<pICMS>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.Aliquota) CLIPPED ,'</pICMS>'                #245.58
//                PRINT COLUMN 001,     '<vICMS>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.Valor) CLIPPED ,'</vICMS>'                   #245.59
//                PRINT COLUMN 001,     '<modBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.modBCST ) CLIPPED ,'</modBCST>'            #245.60
//                IF mr_t_trib_sn.pmvast > 0 THEN
//                   PRINT COLUMN 001,  '<pMVAST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pmvast) CLIPPED ,'</pMVAST>'                #245.61
//                END IF
//                IF mr_t_trib_sn.pRedBCST > 0 THEN
//                   PRINT COLUMN 001,  '<pRedBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pRedBCST) CLIPPED ,'</pRedBCST>'          #245.62
//                END IF
//                PRINT COLUMN 001,     '<vBCST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vBCST) CLIPPED ,'</vBCST>'                   #245.63
//                PRINT COLUMN 001,     '<pICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pICMSST) CLIPPED ,'</pICMSST>'             #245.64
//                PRINT COLUMN 001,      '<vICMSST>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vICMSST) CLIPPED ,'</vICMSST>'            #245.65
//                PRINT COLUMN 001,     '<pCredSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.pCredSN) CLIPPED ,'</pCredSN>'             #245.52 v2.00
//                PRINT COLUMN 001,     '<vCredICMSSN>',log2260_troca_virgula_por_ponto(mr_t_trib_sn.vCredICMSSN) CLIPPED ,'</vCredICMSSN>' #245.53 v2.00
                  break;
               default:
                  //Não faz nada
                  break;
            }
         } // FIM ICMS
         else
         //****************************************************************//
         //        IDENTIFICAÇÃO DO IPI DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "IPI") {
            //O|ClEnq|CNPJProd|CSelo|QSelo|CEnq|
            pTxtIPI = new TxtIPI();
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            sStrLine = "O|" + QyItemNotaFiscal->FieldByName("classe_enq_ipi")->AsString + "||||";
            if (!VarIsNull(QyItemNotaFiscal->FieldByName("cod_enq_ipi")->Value)) {
               sStrLine = sStrLine + QyItemNotaFiscal->FieldByName("cod_enq_ipi")->AsString + "|";
            } else {
               sStrLine = sStrLine + "999|";
            }
            pTxtIPI->StrIPI = sStrLine;
            if (sCST == "00" || sCST == "49" ||
                sCST == "50" || sCST == "99") {
               //O07|CST|VIPI|
               sStrLine = "O07|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtIPI->StrTipoIPI = sStrLine;
               pTxtIPI->pTipoIPI = new TipoIPI();
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  //O10|VBC|PIPI|
                  sStrLine = "O10|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtIPI->pTipoIPI->StrValIPI = sStrLine;
               } else {
                  //O11|QUnid|VUnid|
                  sStrLine = "O11|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtIPI->pTipoIPI->StrValIPI = sStrLine;
               }
            } else {
               //O08|CST|
               pTxtIPI->pTipoIPI = NULL;
               pTxtIPI->StrTipoIPI = "O08|" + sCST + "|";
            }          
         } // FIM IPI
         else
         //****************************************************************//
         //        IDENTIFICAÇÃO DO PIS DOS PRODUTOS DA NOTA FISCAL        //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "PIS") {
            pTxtPIS = new TxtPIS();
            pTxtPIS->StrPIS = "Q|";
            pTxtPIS->pTipoPIS = NULL;
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            if (sCST == "01" || sCST == "02") {
               //Q02|CST|VBC|PPIS|VPIS|
               sStrLine = "Q02|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtPIS->StrTipoPIS = sStrLine;
            } else if (sCST == "03") {
               //Q03|CST|QBCProd|VAliqProd|VPIS|
               sStrLine = "Q03|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtPIS->StrTipoPIS = sStrLine;
            } else if (sCST == "04" || sCST == "06" ||
               sCST == "07" || sCST == "08" || sCST == "09") {
               //Q04|CST|
               sStrLine = "Q04|" + sCST + "|";
               pTxtPIS->StrTipoPIS = sStrLine;
            } else {
               //Q05|CST|VPIS|
               sStrLine = "Q05|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtPIS->StrTipoPIS = sStrLine;
               pTxtPIS->pTipoPIS = new TipoPIS();
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  //Q07|VBC|PPIS|
                  sStrLine = "Q07|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtPIS->pTipoPIS->StrValPIS = sStrLine;
               } else {
                  //Q10|QBCProd|VAliqProd|
                  sStrLine = "Q10|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtPIS->pTipoPIS->StrValPIS = sStrLine;
               }
            }
         } // FIM PIS
         else
         //****************************************************************//
         //       IDENTIFICAÇÃO DO COFINS DOS PRODUTOS DA NOTA FISCAL      //
         //****************************************************************//
         if (QyImpostoItem->FieldByName("cod_tributo")->AsString == "COFINS") {
            pTxtCOFINS = new TxtCOFINS();
            pTxtCOFINS->StrCOFINS = "S|";
            pTxtCOFINS->pTipoCOFINS = NULL;
            sCST = QyImpostoItem->FieldByName("cod_cst")->AsString;
            if (sCST == "01" || sCST == "02") {
               //S02|CST|VBC|PCOFINS|VCOFINS|
               sStrLine = "S02|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtCOFINS->StrTipoCOFINS = sStrLine;
            } else if (sCST == "03") {
               //S03|CST|QBCProd|VAliqProd|VCOFINS|
               sStrLine = "S03|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtCOFINS->StrTipoCOFINS = sStrLine;
            } else if (sCST == "04" || sCST == "06" ||
               sCST == "07" || sCST == "08" || sCST == "09") {
               //S04|CST|
               sStrLine = "S04|" + sCST + "|";
               pTxtCOFINS->StrTipoCOFINS = sStrLine;
            } else {               
               //S05|CST|VCOFINS|
               sStrLine = "S05|" + sCST + "|";
               sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_tributo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
               sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
               sStrLine = sStrLine + sStrAux + "|";
               pTxtCOFINS->StrTipoCOFINS = sStrLine;
               if (QyImpostoItem->FieldByName("mod_def_base_calc")->AsInteger == 0) {
                  //S07|VBC|PCOFINS|
                  sStrLine = "S07|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("base_calculo")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("perc_tributo")->AsFloat,ffFixed,5,2); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtCOFINS->pTipoCOFINS->StrValCOFINS = sStrLine;
               } else {
                  //S09|QBCProd|VAliqProd|
                  sStrLine = "S09|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("qtd_total_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  sStrAux = FloatToStrF(QyImpostoItem->FieldByName("valor_unit_tributo")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
                  sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
                  sStrLine = sStrLine + sStrAux + "|";
                  pTxtCOFINS->pTipoCOFINS->StrValCOFINS = sStrLine;
               }
            }
         }
         QyImpostoItem->Next();
      }
      //Deve adicionar os impostos no item
      if (pTxtICMS != NULL) {
         if (!WriteTxtLine("N|")) return false;
         if (!WriteTxtLine(pTxtICMS->StrICMS.c_str())) return false;
         delete pTxtICMS;
      }
      if (pTxtIPI != NULL) {
         if (!WriteTxtLine(pTxtIPI->StrIPI.c_str())) return false;
         if (!WriteTxtLine(pTxtIPI->StrTipoIPI.c_str())) return false;
         if (pTxtIPI->pTipoIPI != NULL) {
            if (!WriteTxtLine(pTxtIPI->pTipoIPI->StrValIPI.c_str())) return false;
            delete pTxtIPI->pTipoIPI;
         }
      }
      if (pTxtPIS != NULL) {
         if (!WriteTxtLine(pTxtPIS->StrPIS.c_str())) return false;
         if (!WriteTxtLine(pTxtPIS->StrTipoPIS.c_str())) return false;
         if (pTxtPIS->pTipoPIS != NULL) {
            if (!WriteTxtLine(pTxtPIS->pTipoPIS->StrValPIS.c_str())) return false;
            delete pTxtPIS->pTipoPIS;
         }
      }
      if (pTxtCOFINS != NULL) {
         if (!WriteTxtLine(pTxtCOFINS->StrCOFINS.c_str())) return false;
         if (!WriteTxtLine(pTxtCOFINS->StrTipoCOFINS.c_str())) return false;
         if (pTxtCOFINS->pTipoCOFINS != NULL) {
            if (!WriteTxtLine(pTxtCOFINS->pTipoCOFINS->StrValCOFINS.c_str())) return false;
            delete pTxtCOFINS->pTipoCOFINS;
         }
      }
      QyItemNotaFiscal->Next();
   }

   //****************************************************************//
   //     INFORMAÇÕES DO TOTAL DA NOTA FISCAL ELETRÔNICA             //
   //****************************************************************//
   if (!WriteTxtLine("W|")) return false;
   //W02|vBC|vICMS|vBCST|vST|vProd|vFrete|vSeg|vDesc|vII|vIPI|vPIS|vCOFINS|vOutro|vNF|
   sStrLine = "W02|0.00|0.00|0.00|0.00|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_mercadoria")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_frete")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_seguro")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_desconto")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   //Impostos todos zerados por enquanto
   sStrLine = sStrLine + "0.00|0.00|0.00|0.00|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("outras_despesas")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("valor_nota_fiscal")->AsFloat,ffFixed,15,2); //Formatando como decimal 15,2
   sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
   sStrLine = sStrLine + sStrAux + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;

   //****************************************************************//
   //     INFORMAÇÕES DO TRANSPORTE DA NOTA FISCAL ELETRÔNICA        //
   //****************************************************************//
   //X|ModFrete|
   sStrLine = "X|" + QyNotaFiscal->FieldByName("tipo_frete")->AsString + "|";
   if (!WriteTxtLine(sStrLine.c_str())) return false;

//          WHEN l_tipo_registro = "X.A"
//             PRINT COLUMN 001,     '<transporta>'                                                                                        #358
//             IF mr_t_transporte_nfe.Cnpj IS NOT NULL AND
//                mr_t_transporte_nfe.Cnpj <> " " AND
//                mr_t_transporte_nfe.Cnpj > 0 THEN
//                PRINT COLUMN 001,    '<CNPJ>',mr_t_transporte_nfe.Cnpj CLIPPED,'</CNPJ>'                                                 #359
//             END IF
//             IF mr_t_transporte_nfe.CPF IS NOT NULL AND
//                mr_t_transporte_nfe.CPF <> " " AND
//                mr_t_transporte_nfe.CPF > 0 THEN
//                PRINT COLUMN 001,    '<CPF>',mr_t_transporte_nfe.CPF CLIPPED,'</CPF>'                                                    #360
//             END IF
//             IF mr_t_transporte_nfe.Nome IS NOT NULL AND mr_t_transporte_nfe.Nome <> " " THEN
//                PRINT COLUMN 001,    '<xNome>',obf9246_retira_espacos(mr_t_transporte_nfe.Nome CLIPPED) CLIPPED,'</xNome>'               #361
//             END IF
//             IF mr_t_transporte_nfe.Ie IS NOT NULL AND mr_t_transporte_nfe.Ie <> " " THEN
//                PRINT COLUMN 001,    '<IE>',mr_t_transporte_nfe.Ie CLIPPED,'</IE>'                                                       #362
//             END IF
//             IF mr_t_transporte_nfe.ender IS NOT NULL AND mr_t_transporte_nfe.ender <> " " THEN
//                PRINT COLUMN 001,    '<xEnder>',obf9246_retira_espacos(mr_t_transporte_nfe.ender CLIPPED) CLIPPED,'</xEnder>'            #363
//             END IF
//             IF mr_t_transporte_nfe.mun IS NOT NULL AND mr_t_transporte_nfe.mun <> " " THEN
//                PRINT COLUMN 001,    '<xMun>',obf9246_retira_espacos(mr_t_transporte_nfe.mun CLIPPED) CLIPPED,'</xMun>'                  #364
//             END IF
//             IF mr_t_transporte_nfe.Uf IS NOT NULL AND mr_t_transporte_nfe.Uf <> " " THEN
//                PRINT COLUMN 001,    '<UF>',mr_t_transporte_nfe.Uf CLIPPED,'</UF>'                                                        #365
//             END IF
//             PRINT COLUMN 001,     '</transporta>'

//          WHEN l_tipo_registro = "X.1"
//
//             PRINT COLUMN 001,     '<retTransp>'                                                                                        #366
//             PRINT COLUMN 001,       '<vServ>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Vserv),'</vServ>'                        #367
//             PRINT COLUMN 001,       '<vBCRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.VBC),'</vBCRet>'                        #368
//             PRINT COLUMN 001,       '<pICMSRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Aliquota),'</pICMSRet>'               #369
//             PRINT COLUMN 001,       '<vICMSRet>',log2260_troca_virgula_por_ponto(mr_t_trib_transp.Valor),'</vICMSRet>'                  #370
//             PRINT COLUMN 001,       '<CFOP>',mr_t_trib_transp.Cfop CLIPPED,'</CFOP>'                                                    #371
//             PRINT COLUMN 001,       '<cMunFG>',mr_t_trib_transp.CMUNFG CLIPPED,'</cMunFG>'                                              #372
//             PRINT COLUMN 001,     '</retTransp>'

   if (!VarIsNull(QyNotaFiscal->FieldByName("placa_veiculo")->Value)) {
      //X18|Placa|UF|RNTC|
      sStrLine = "X18|" + QyNotaFiscal->FieldByName("placa_veiculo")->AsString  + "|" + \
                 QyNotaFiscal->FieldByName("estado_placa_veiculo")->AsString + "||";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("placa_reboque")->Value)) {
      //X22|Placa|UF|RNTC|
      sStrLine = "X22|" + QyNotaFiscal->FieldByName("placa_reboque")->AsString  + "|" + \
                 QyNotaFiscal->FieldByName("estado_placa_reboque")->AsString + "||";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
   }
   //Faz assim, pois pode ser que não tenha nehhum filho pro volume
   //X26|QVol|Esp|Marca|NVol|PesoL|PesoB|
   bool bPossuiVolume = false;
   sStrLine = "";
   if (QyNotaFiscal->FieldByName("qtd_volume")->AsInteger > 0) {
      sStrLine = sStrLine + "|" + QyNotaFiscal->FieldByName("qtd_volume")->AsString;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("especie_volume")->Value)) {
      sStrLine = sStrLine + "|" + QyNotaFiscal->FieldByName("especie_volume")->AsString;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("marca_volume")->Value)) {
      sStrLine = sStrLine + "|" + QyNotaFiscal->FieldByName("marca_volume")->AsString;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
   if (!VarIsNull(QyNotaFiscal->FieldByName("numeracao_volume")->Value)) {
      sStrLine = sStrLine + "|" + QyNotaFiscal->FieldByName("numeracao_volume")->AsString;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
   if (QyNotaFiscal->FieldByName("peso_liquido")->AsFloat > 0) {
      sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("peso_liquido")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + "|" + sStrAux;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
   if (QyNotaFiscal->FieldByName("peso_bruto")->AsFloat > 0) {
      sStrAux = FloatToStrF(QyNotaFiscal->FieldByName("peso_bruto")->AsFloat,ffFixed,15,3); //Formatando como decimal 15,2
      sStrAux = StringReplace(sStrAux,",",".",TReplaceFlags() << rfReplaceAll); //Substituindo separador decimal por ponto
      sStrLine = sStrLine + "|" + sStrAux;
      bPossuiVolume = true;
   } else {
      sStrLine = sStrLine + "|";
   }
//          WHEN l_tipo_registro = "X.5"
//             PRINT COLUMN 001,       '<lacres>'
//
//          WHEN l_tipo_registro = "X.6"                                                                                                #387a
//             PRINT COLUMN 001,          '<nLacre>',obf9246_retira_espacos(mr_t_lacres_transp.Lacre CLIPPED) CLIPPED,'</nLacre>'       #388
//
//          WHEN l_tipo_registro = "X.7"
//             PRINT COLUMN 001,       '</lacres>'
   //Se adicionou algum filho deve adicionar no xml
   if (bPossuiVolume) {
      sStrLine = "X26" + sStrLine + "|";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
   }

   //****************************************************************//
   //       INFORMAÇÕES ADICIONAIS DA NOTA FISCAL ELETRÔNICA         //
   //****************************************************************//
   if ((!VarIsNull(QyNotaFiscal->FieldByName("info_complementar")->Value)) ||
       (!VarIsNull(QyNotaFiscal->FieldByName("info_adicional_fisco")->Value))) {
      //Z|InfAdFisco|InfCpl|
      sStrLine = "Z|";
      sStrAux = StringReplace(QyNotaFiscal->FieldByName("info_adicional_fisco")->AsString,"\r\n"," ", TReplaceFlags() << rfReplaceAll);
      sStrLine = sStrLine + sStrAux + "|";
      sStrAux = StringReplace(QyNotaFiscal->FieldByName("info_complementar")->AsString,"\r\n"," ", TReplaceFlags() << rfReplaceAll);
      sStrLine = sStrLine + sStrAux + "|";
      if (!WriteTxtLine(sStrLine.c_str())) return false;
   }
   CloseHandle(hTxtFile);
   return true;
}
//---------------------------------------------------------------------------
bool __fastcall TSfgXmlNFe::WriteTxtLine(char *Line)
{
   DWORD dwBytesWritten;

   int iSizeH = strlen(Line);
   iSizeH += 3;
   char *Buffer = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSizeH*sizeof(char));
   strcpy(Buffer,Line);
   strcat(Buffer,"\r\n");
   if (!WriteFile(hTxtFile, Buffer, (iSizeH-1)*sizeof(char), &dwBytesWritten, NULL)) {
      MessageBox(NULL,"Não foi possível efetuar a gravação do arquivo texto da nota fiscal.", "Mensagem de Erro", APP_ERROR);
      return false;
   }
   HeapFree(GetProcessHeap(),0,Buffer);  //Apaga o Buffer
   return true;
}
//---------------------------------------------------------------------------





