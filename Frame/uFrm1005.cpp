/*
Módulo: Framework SoftGreen
Função: Configurações Sistema
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#pragma hdrstop
#include "uFrm1005.h"
#define GRP_CLI 1
#define GRP_FOR 2
#define GRP_REP 3
#define GRP_CID 4
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1005(void) {
   AddAppForm("Frm1005","Codificações Sistema");
   AddAppFormClass("TFrm1005",__classid(TFrm1005));
}
#pragma startup RegisterFrm1005
//---------------------------------------------------------------------------
__fastcall TFrm1005::TFrm1005(TComponent* Owner)
	: TfrmBase01(Owner)
{
	SetWindowLong(ProxCli->Handle, GWL_STYLE, GetWindowLong(ProxCli->Handle, GWL_STYLE) | ES_NUMBER);
	SetWindowLong(ProxFor->Handle, GWL_STYLE, GetWindowLong(ProxFor->Handle, GWL_STYLE) | ES_NUMBER);
	SetWindowLong(ProxRep->Handle, GWL_STYLE, GetWindowLong(ProxRep->Handle, GWL_STYLE) | ES_NUMBER);

   CodAutoCli->Checked = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_cliente');")) == "S");
   CodAutoFor->Checked = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_fornecedor');")) == "S");
   CodAutoRep->Checked = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_representa');")) == "S");
   CodAutoCid->Checked = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_cidade');")) == "S");
   CarregaParam();
   EnableFields(CodAutoCli->Checked, GRP_CLI);
   EnableFields(CodAutoFor->Checked, GRP_FOR);
   EnableFields(CodAutoRep->Checked, GRP_REP);
   EnableFields(CodAutoCid->Checked, GRP_CID);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CarregaParam()
{
	TZReadOnlyQuery *QyGetParam;
try {
	QyGetParam = new TZReadOnlyQuery(Application);
	QyGetParam->Connection = AppConnection;
	QyGetParam->SQL->Text = \
"SELECT nome_parametro, valor_flag, valor_texto, valor_decimal\
  FROM tbl_parametro_sistema\
 WHERE nome_parametro IN ('prox_cod_cliente','prox_cod_fornecedor','prox_cod_representa','prox_cod_cidade')";
	QyGetParam->Active = true;
   QyGetParam->First();
	while (!QyGetParam->Eof) {
      if (QyGetParam->FieldByName("nome_parametro")->AsString == "prox_cod_cliente") {
         PreCli->Text = QyGetParam->FieldByName("valor_texto")->AsString;
         ProxCli->Text = QyGetParam->FieldByName("valor_decimal")->AsString;
         UpDownCli->Position = QyGetParam->FieldByName("valor_flag")->AsInteger;
      } else
      if (QyGetParam->FieldByName("nome_parametro")->AsString == "prox_cod_fornecedor") {
         PreFor->Text = QyGetParam->FieldByName("valor_texto")->AsString;
         ProxFor->Text = QyGetParam->FieldByName("valor_decimal")->AsString;
         UpDownFor->Position = QyGetParam->FieldByName("valor_flag")->AsInteger;
      } else
      if (QyGetParam->FieldByName("nome_parametro")->AsString == "prox_cod_representa") {
         PreRep->Text = QyGetParam->FieldByName("valor_texto")->AsString;
         ProxRep->Text = QyGetParam->FieldByName("valor_decimal")->AsString;
         UpDownRep->Position = QyGetParam->FieldByName("valor_flag")->AsInteger;
      } else
      if (QyGetParam->FieldByName("nome_parametro")->AsString == "prox_cod_cidade") {
         PreCid->Text = QyGetParam->FieldByName("valor_texto")->AsString;
         ProxCid->Text = QyGetParam->FieldByName("valor_decimal")->AsString;
         UpDownCid->Position = QyGetParam->FieldByName("valor_flag")->AsInteger;
      }
      QyGetParam->Next();
   }
	QyGetParam->Active = false;
	delete QyGetParam;
} catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao buscar as informações de parametrização:\n";
   Msg = Msg + e.Message;
   MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
}
   if (ProxCli->Text.Length() == 0)
      ProxCli->Text = "1";
   if (ProxFor->Text.Length() == 0)
      ProxFor->Text = "1";
   if (ProxRep->Text.Length() == 0)
      ProxRep->Text = "1";
   if (ProxCid->Text.Length() == 0)
      ProxCid->Text = "1";
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::EnableFields(bool bEnable, int iGrupo)
{
   TColor Color = (bEnable) ? AppConfig->Colors->Enabled : AppConfig->Colors->Disabled;

   if (iGrupo == GRP_CLI) {
      PreCli->ReadOnly = !bEnable;
      PreCli->Color = Color;
      ProxCli->ReadOnly = !bEnable;
      ProxCli->Color = Color;
      ZeroCli->Color = Color;
      UpDownCli->Enabled = bEnable;
   } else
   if (iGrupo == GRP_FOR) {
      PreFor->ReadOnly = !bEnable;
      PreFor->Color = Color;
      ProxFor->ReadOnly = !bEnable;
      ProxFor->Color = Color;
      ZeroFor->Color = Color;
      UpDownFor->Enabled = bEnable;
   } else
   if (iGrupo == GRP_REP) {
      PreRep->ReadOnly = !bEnable;
      PreRep->Color = Color;
      ProxRep->ReadOnly = !bEnable;
      ProxRep->Color = Color;
      ZeroRep->Color = Color;
      UpDownRep->Enabled = bEnable;
   } else
   if (iGrupo == GRP_CID) {
      PreCid->ReadOnly = !bEnable;
      PreCid->Color = Color;
      ProxCid->ReadOnly = !bEnable;
      ProxCid->Color = Color;
      ZeroCid->Color = Color;
      UpDownCid->Enabled = bEnable;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::btConfirmarClick(TObject *Sender)
{
	String SQL;
try {

   SQL = (CodAutoCli->Checked) ? "S" : "N";
	SQL = "CALL set_parametro_texto('cod_aut_cliente','" + SQL + "','" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = (CodAutoFor->Checked) ? "S" : "N";
	SQL = "CALL set_parametro_texto('cod_aut_fornecedor','" + SQL + "','" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = (CodAutoRep->Checked) ? "S" : "N";
	SQL = "CALL set_parametro_texto('cod_aut_representa','" + SQL + "','" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = (CodAutoCid->Checked) ? "S" : "N";
	SQL = "CALL set_parametro_texto('cod_aut_cidade','" + SQL + "','" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = "'prox_cod_cliente'," + QuotedStr(ZeroCli->Text);
	if(PreCli->Text.Length() > 0)
      SQL = SQL + ",'" + PreCli->Text + "',";
   else
      SQL = SQL + ",NULL,";
	if(ProxCli->Text.Length() > 0)
      SQL = SQL + "'" + ProxCli->Text + "',";
   else
      SQL = SQL + "NULL,";
   SQL = "CALL set_parametro_sistema(" + SQL + "NULL,'" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = "'prox_cod_fornecedor'," + QuotedStr(ZeroFor->Text);
	if(PreFor->Text.Length() > 0)
      SQL = SQL + ",'" + PreFor->Text + "',";
   else
      SQL = SQL + ",NULL,";
	if(ProxFor->Text.Length() > 0)
      SQL = SQL + "'" + ProxFor->Text + "',";
   else
      SQL = SQL + "NULL,";
   SQL = "CALL set_parametro_sistema(" + SQL + "NULL,'" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = "'prox_cod_representa'," + QuotedStr(ZeroRep->Text);
	if(PreRep->Text.Length() > 0)
      SQL = SQL + "," + QuotedStr(PreRep->Text);
   else
      SQL = SQL + ",NULL";
	if(ProxRep->Text.Length() > 0)
      SQL = SQL + "," + QuotedStr(ProxRep->Text);
   else
      SQL = SQL + ",NULL,";
   SQL = "CALL set_parametro_sistema(" + SQL + ",NULL,'" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

   SQL = "'prox_cod_cidade'," + QuotedStr(ZeroCid->Text);
	if(PreCid->Text.Length() > 0)
      SQL = SQL + "," + QuotedStr(PreCid->Text);
   else
      SQL = SQL + ",NULL";
	if(ProxCid->Text.Length() > 0)
      SQL = SQL + "," + QuotedStr(ProxCid->Text);
   else
      SQL = SQL + ",NULL,";
   SQL = "CALL set_parametro_sistema(" + SQL + ",NULL,'" + AppUser->Usuario + "');";
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

	Close();
} catch(Exception &e){
	String Msg = "Ocorreu o seguinte erro ao salvar as informações de configuração:\n";
	Msg = Msg + e.Message;
	MessageBox(Handle,Msg.c_str(), Caption.c_str(), APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::btCancelarClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::ClienteExit(TObject *Sender)
{
   //Monta o exemplo de codificação automático
   String ProxCod;
   if (UpDownCli->Position > 0) {
      char mask[5] = "%0";
      strcat(mask,IntToStr(UpDownCli->Position).c_str());
      strcat(mask,"i");
      ProxCod.sprintf(mask,StrToInt(ProxCli->Text));
   } else {
      ProxCod = ProxCli->Text;
   }
   ExeCodCli->Caption = PreCli->Text + ProxCod;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::FornecedorExit(TObject *Sender)
{
   //Monta o exemplo de codificação automático
   String ProxCod;
   if (UpDownFor->Position > 0) {
      char mask[5] = "%0";
      strcat(mask,IntToStr(UpDownFor->Position).c_str());
      strcat(mask,"i");
      ProxCod.sprintf(mask,StrToInt(ProxFor->Text));
   } else {
      ProxCod = ProxFor->Text;
   }
   ExeCodFor->Caption = PreFor->Text + ProxCod;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::RepresentaExit(TObject *Sender)
{
   //Monta o exemplo de codificação automático
   String ProxCod;
   if (UpDownRep->Position > 0) {
      char mask[5] = "%0";
      strcat(mask,IntToStr(UpDownRep->Position).c_str());
      strcat(mask,"i");
      ProxCod.sprintf(mask,StrToInt(ProxRep->Text));
   } else {
      ProxCod = ProxRep->Text;
   }
   ExeCodRep->Caption = PreRep->Text + ProxCod;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CidadeExit(TObject *Sender)
{
   //Monta o exemplo de codificação automático
   String ProxCod;
   if (UpDownCid->Position > 0) {
      char mask[5] = "%0";
      strcat(mask,IntToStr(UpDownCid->Position).c_str());
      strcat(mask,"i");
      ProxCod.sprintf(mask,StrToInt(ProxCid->Text));
   } else {
      ProxCod = ProxCid->Text;
   }
   ExeCodCid->Caption = PreCid->Text + ProxCod;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CodAutoCliClick(TObject *Sender)
{
   EnableFields(CodAutoCli->Checked, GRP_CLI);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CodAutoForClick(TObject *Sender)
{
   EnableFields(CodAutoFor->Checked, GRP_FOR);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CodAutoRepClick(TObject *Sender)
{
   EnableFields(CodAutoRep->Checked, GRP_REP);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::CodAutoCidClick(TObject *Sender)
{
   EnableFields(CodAutoCid->Checked, GRP_CID);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::UpDownCliClick(TObject *Sender, TUDBtnType Button)
{
   ClienteExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::UpDownForClick(TObject *Sender, TUDBtnType Button)
{
   FornecedorExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::UpDownRepClick(TObject *Sender, TUDBtnType Button)
{
   RepresentaExit(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TFrm1005::UpDownCidClick(TObject *Sender,TUDBtnType Button)
{
   CidadeExit(Sender);
}
//---------------------------------------------------------------------------

