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
#include "uFrm1001.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterFrm1001(void) {
   AddAppForm("Frm1001","Configurações Sistema");
   AddAppFormClass("TFrm1001",__classid(TFrm1001));
}
#pragma startup RegisterFrm1001
//---------------------------------------------------------------------------
__fastcall TFrm1001::TFrm1001(TComponent* Owner)
	: TfrmBase01(Owner)
{
	SetWindowLong(PortaServerEmail->Handle, GWL_STYLE, GetWindowLong(PortaServerEmail->Handle, GWL_STYLE) | ES_NUMBER);
   AssignImage(AppConfig->Images->Logotipo,RelatLogotipo);
   AssignImage(AppConfig->Images->MarcaDagua,MarcaDagua);
	LogotipoPath->Text = AppConfig->Images->LogotipoPath;
	MarcaDaguaPath->Text = AppConfig->Images->MarcaDaguaPath;

	if(AppConfig->Reports->CabLivre01.Length() > 0)
		edtCabLivre01->Text = AppConfig->Reports->CabLivre01;
	if(AppConfig->Reports->CabLivre02.Length() > 0)
		edtCabLivre02->Text = AppConfig->Reports->CabLivre02;
	if(AppConfig->Reports->CabLivre03.Length() > 0)
		edtCabLivre03->Text = AppConfig->Reports->CabLivre03;

	if(AppConfig->Reports->RodCidade.Length() > 0)
		edtCidade->Text = AppConfig->Reports->RodCidade;
	if(AppConfig->Reports->RodLivre01.Length() > 0)
		edtRodLivre01->Text = AppConfig->Reports->RodLivre01;
	if(AppConfig->Reports->RodLivre02.Length() > 0)
		edtRodLivre02->Text = AppConfig->Reports->RodLivre02;
	ServerEmail->Text = AppParEmail->SMTPHost;
	PortaServerEmail->Text = IntToStr(AppParEmail->SMTPPorta);
    RequerAutenticacao->Checked = AppParEmail->SMTPAutenticacao;
    ConexaoSegura->Checked = AppParEmail->SMTPSSL;
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::btLogotipoClick(TObject *Sender)
{
	OpenPicture->Title = "Escolher Logotipo";
   if(OpenPicture->Execute()){
	   LogotipoPath->Text = OpenPicture->FileName;
	   Logotipo->Picture->LoadFromFile(LogotipoPath->Text);
	   Logotipo->Invalidate();
      RelatLogotipo->Picture->Assign(Logotipo->Picture);
	   AppConfig->Images->LogotipoPath = LogotipoPath->Text;
   }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::btMarcaDaguaClick(TObject *Sender)
{
	OpenPicture->Title = "Escolher Imagem de Fundo";
  if(OpenPicture->Execute()){
	  MarcaDaguaPath->Text = OpenPicture->FileName;
	  MarcaDagua->Picture->LoadFromFile(MarcaDaguaPath->Text);
	  MarcaDagua->Invalidate();
     AppConfig->Images->MarcaDaguaPath = MarcaDaguaPath->Text;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::btDelLogotipoClick(TObject *Sender)
{
	LogotipoPath->Text = "";
	Logotipo->Picture->Assign(NULL);
	Logotipo->Invalidate();
	RelatLogotipo->Picture->Assign(NULL);
   RelatLogotipo->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::btDelMarcaDaguaClick(TObject *Sender)
{
	MarcaDaguaPath->Text = "";
	MarcaDagua->Picture->Assign(NULL);
	MarcaDagua->Invalidate();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::btConfirmarClick(TObject *Sender)
{
	String SQL;
	SMTP_CFG smtp_cfg = CFG_NONE;
try {
	if(LogotipoPath->Text.Length() > 0) {
		SQL = "CALL set_parametro_texto('logotipo_path','" + StringReplace(LogotipoPath->Text,"\\","\\\\",TReplaceFlags() << rfReplaceAll) + "','" + AppUser->Usuario + "');";
	} else {
		SQL = "CALL set_parametro_texto('logotipo_path',NULL,'" + AppUser->Usuario + "');";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;
	if(MarcaDaguaPath->Text.Length() > 0) {
		SQL = "CALL set_parametro_texto('marcadagua_path','" +  StringReplace(MarcaDaguaPath->Text,"\\","\\\\",TReplaceFlags() << rfReplaceAll) + "','" + AppUser->Usuario + "');";
	} else {
		SQL = "CALL set_parametro_texto('marcadagua_path',NULL,'" + AppUser->Usuario + "');";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

	if(edtCabLivre01->Text != "Linha Rodapé Livre 01") {
		SQL = "CALL set_parametro_texto('report_cab_livre01','" + edtCabLivre01->Text + "','" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre01 = edtCabLivre01->Text;
	} else {
		SQL = "CALL set_parametro_texto('report_cab_livre01',NULL,'" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre01 = "";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

	if(edtCabLivre02->Text != "Linha Rodapé Livre 02") {
		SQL = "CALL set_parametro_texto('report_cab_livre02','" + edtCabLivre02->Text + "','" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre02 = edtCabLivre02->Text;
	} else {
		SQL = "CALL set_parametro_texto('report_cab_livre02',NULL,'" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre02 = "";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

	if(edtCabLivre03->Text != "Linha Rodapé Livre 03") {
		SQL = "CALL set_parametro_texto('report_cab_livre03','" + edtCabLivre03->Text + "','" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre03 = edtCabLivre03->Text;
	} else {
		SQL = "CALL set_parametro_texto('report_cab_livre03',NULL,'" + AppUser->Usuario + "');";
		AppConfig->Reports->CabLivre03 = "";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;

	if(edtCidade->Text != "Cidade") {
		SQL = "CALL set_parametro_texto('report_rod_cidade','" + edtCidade->Text + "','" + AppUser->Usuario + "');";
	} else {
		SQL = "CALL set_parametro_texto('report_rod_cidade',NULL,'" + AppUser->Usuario + "');";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;
	if(edtRodLivre01->Text != "Linha Rodapé Livre 01") {
		SQL = "CALL set_parametro_texto('report_rod_livre01','" + edtRodLivre01->Text + "','" + AppUser->Usuario + "');";
		AppConfig->Reports->RodLivre01 = edtRodLivre01->Text;
	} else {
		SQL = "CALL set_parametro_texto('report_rod_livre01',NULL,'" + AppUser->Usuario + "');";
		AppConfig->Reports->RodLivre01 = "";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;
	if(edtRodLivre02->Text != "Linha Rodapé Livre 02") {
		SQL = "CALL set_parametro_texto('report_rod_livre02','" + edtRodLivre02->Text + "','" + AppUser->Usuario + "');";
		AppConfig->Reports->RodLivre02 = edtRodLivre02->Text;
	} else {
		SQL = "CALL set_parametro_texto('report_rod_livre02',NULL,'" + AppUser->Usuario + "');";
		AppConfig->Reports->RodLivre02 = "";
	}
	if (!ValidacoesDB::SetParamValue(AppConnection,SQL))
		return;
	AppConfig->Images->LogotipoPath = LogotipoPath->Text;
	AppConfig->Images->MarcaDaguaPath = MarcaDaguaPath->Text;
	AppConfig->Reports->RodCidade = edtCidade->Text;
	if(Logotipo->Picture) {
		AppConfig->Images->Logotipo->Picture->Assign(Logotipo->Picture);
	} else {
		AppConfig->Images->Logotipo->Picture->Assign(NULL);
	}
	if(MarcaDagua->Picture) {
		AppConfig->Images->MarcaDagua->Picture->Assign(MarcaDagua->Picture);
	} else {
		AppConfig->Images->MarcaDagua->Picture->Assign(NULL);
	}
	if(RequerAutenticacao->Checked) {
		smtp_cfg |= CFG_AUT;
	}
	if(ConexaoSegura->Checked) {
		smtp_cfg |= CFG_SSL;
	}
	AppParEmail->SMTPHost = ServerEmail->Text;
	AppParEmail->SMTPPorta = StrToInt(PortaServerEmail->Text);
	AppParEmail->SMTPAutenticacao = (smtp_cfg & CFG_AUT); // requer autenticacao
	AppParEmail->SMTPSSL = (smtp_cfg & CFG_SSL); // requer conexao segura

	if(ServerEmail->Text.Length() > 0) {
		SQL = "CALL set_server_smtp('" + ServerEmail->Text + "',"+ PortaServerEmail->Text +",'"+ IntToStr(smtp_cfg) +"','" + AppUser->Usuario + "');";
	} else {
		SQL = "CALL set_server_smtp(NULL,0,0,'" + AppUser->Usuario + "');";
	}
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
void __fastcall TFrm1001::btCancelarClick(TObject *Sender)
{
	Close();
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtRodLivre01Enter(TObject *Sender)
{
	if (edtRodLivre01->Text == "Linha Rodapé Livre 01") {
		edtRodLivre01->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtRodLivre01Exit(TObject *Sender)
{
	if (!edtRodLivre01->Text.Length()) {
		edtRodLivre01->Text = "Linha Rodapé Livre 01";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtRodLivre02Enter(TObject *Sender)
{
	if (edtRodLivre02->Text == "Linha Rodapé Livre 02") {
		edtRodLivre02->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtRodLivre02Exit(TObject *Sender)
{
	if (!edtRodLivre02->Text.Length()) {
		edtRodLivre02->Text = "Linha Rodapé Livre 02";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCidadeEnter(TObject *Sender)
{
	if (edtCidade->Text == "Cidade") {
		edtCidade->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCidadeExit(TObject *Sender)
{
	if (!edtCidade->Text.Length()) {
		edtCidade->Text = "Cidade";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre01Enter(TObject *Sender)
{
	if (edtCabLivre01->Text == "Linha Cabeçalho Livre 01") {
		edtCabLivre01->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre01Exit(TObject *Sender)
{
	if (!edtCabLivre01->Text.Length()) {
		edtCabLivre01->Text = "Linha Cabeçalho Livre 01";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre02Enter(TObject *Sender)
{
	if (edtCabLivre02->Text == "Linha Cabeçalho Livre 02") {
		edtCabLivre02->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre02Exit(TObject *Sender)
{
	if (!edtCabLivre02->Text.Length()) {
		edtCabLivre02->Text = "Linha Cabeçalho Livre 02";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre03Enter(TObject *Sender)
{
	if (edtCabLivre03->Text == "Linha Cabeçalho Livre 03") {
		edtCabLivre03->Text = "";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::edtCabLivre03Exit(TObject *Sender)
{
	if (!edtCabLivre03->Text.Length()) {
		edtCabLivre03->Text = "Linha Cabeçalho Livre 03";
	}
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::LogotipoPathExit(TObject *Sender)
{
   if (AppConfig->Images->LogotipoPath != LogotipoPath->Text) {
	   try {
		   Logotipo->Picture->LoadFromFile(LogotipoPath->Text);
      }
      catch (...) {
         MessageBox(Handle,"Não foi possível carregar a imagem de logotipo!","Mensagem de Erro",APP_ERROR);
         return;
      }
      AssignImage(Logotipo,RelatLogotipo);
      Logotipo->Invalidate();
      AppConfig->Images->LogotipoPath = LogotipoPath->Text;
  }
}
//---------------------------------------------------------------------------
void __fastcall TFrm1001::MarcaDaguaPathExit(TObject *Sender)
{
   if (AppConfig->Images->MarcaDaguaPath != MarcaDaguaPath->Text) {
	   try {
		   MarcaDagua->Picture->LoadFromFile(MarcaDaguaPath->Text);
      }
      catch (...) {
         MessageBox(Handle,"Não foi possível carregar a imagem de fundo!","Mensagem de Erro",APP_ERROR);
         return;
      }
      MarcaDagua->Invalidate();
      AppConfig->Images->MarcaDaguaPath = MarcaDaguaPath->Text;
  }
}
//---------------------------------------------------------------------------

