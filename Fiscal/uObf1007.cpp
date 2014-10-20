//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uDataModule.h"
#include "uSfgToolTip.h"
#pragma hdrstop
#include "uObf1007.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TObf1007::TObf1007(TComponent* Owner)
   : TForm(Owner)
{
   bExistNumNF = false;
   GetNumeracaoNF();
   SetWindowLong(prox_num_nf->Handle, GWL_STYLE, GetWindowLong(prox_num_nf->Handle, GWL_STYLE) | ES_NUMBER);
   SetWindowLong(serie_nf->Handle, GWL_STYLE, GetWindowLong(serie_nf->Handle, GWL_STYLE) | ES_NUMBER);
	Tolltips = new SfgToolTips(this,"",(TTIcon)AppConfig->Icon, false,AppConfig->Colors->TTFontColor,AppConfig->Colors->TTBackColor);
	Tolltips->CreateToolTips();
}
//---------------------------------------------------------------------------
void TObf1007::GetNumeracaoNF()
{
	TZReadOnlyQuery *QyNumNF;
try {
	QyNumNF = new TZReadOnlyQuery(Application);
	QyNumNF->Connection = AppConnection;
	QyNumNF->SQL->Text = "\
SELECT nf.valor_decimal prox_num_nf,\
       sr.valor_decimal serie_nf\
  FROM tbl_parametro_sistema nf,\
       tbl_parametro_sistema sr\
 WHERE nf.nome_parametro = 'prox_num_nf_venda'\
   AND nf.valor_texto = " + QuotedStr(AppUser->CodEmpresa) + "\
   AND sr.nome_parametro = 'serie_nf_venda'\
   AND sr.valor_texto = " + QuotedStr(AppUser->CodEmpresa);
	QyNumNF->Active = true;
	if(QyNumNF->RecordCount) {
      bExistNumNF = true;
		prox_num_nf->Text = QyNumNF->FieldByName("prox_num_nf")->AsString;
		serie_nf->Text = QyNumNF->FieldByName("serie_nf")->AsString;
	} else {
		prox_num_nf->Text = "1";
		serie_nf->Text = "1";
   }
	QyNumNF->Active = false;
	delete QyNumNF;
} catch(Exception &e){
	String MsgErro = "Ocorreu o seguinte erro ao buscar as informações de parametrização de numeração da NF:\n";
   MsgErro = MsgErro + e.Message;
   MessageBox(NULL,MsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
}
}
//---------------------------------------------------------------------------
void __fastcall TObf1007::BtOkClick(TObject *Sender)
{
   if (prox_num_nf->Text.Length() <= 0) {
      MessageBox(Handle,"Informe o próximo número de nota fiscal!",Caption.c_str(),APP_ATENTION);
      prox_num_nf->SetFocus();
      return;
   }
   if (serie_nf->Text.Length() <= 0) {
      MessageBox(Handle,"Informe a série a ser usada para as notas fiscais!",Caption.c_str(),APP_ATENTION);
      serie_nf->SetFocus();
      return;
   }
   if (!SetNumeracaoNF())
      return;
   this->ModalResult = mrOk;
}
//---------------------------------------------------------------------------
bool TObf1007::SetNumeracaoNF()
{
	TZQuery *QyNumNF;
   String DataHoraAtual = FormatDateTime("yyyy-mm-dd hh:nn:ss",Now());
try {
	QyNumNF = new TZQuery(Application);
	QyNumNF->Connection = AppConnection;
   QyNumNF->ParamCheck = false;
   if (bExistNumNF) {
	   QyNumNF->SQL->Text = "\
UPDATE tbl_parametro_sistema\
   SET valor_decimal = " + prox_num_nf->Text + "\
       ,data_atualizacao = " + QuotedStr(DataHoraAtual) + "\
       ,user_atualizacao = " + QuotedStr(AppUser->Usuario) + "\
 WHERE nome_parametro = 'prox_num_nf_venda'\
   AND valor_texto = " + QuotedStr(AppUser->CodEmpresa);
   } else {
	   QyNumNF->SQL->Text = "\
INSERT INTO tbl_parametro_sistema\
       (nome_parametro, valor_texto, valor_decimal, data_atualizacao, user_atualizacao)\
VALUES ('prox_num_nf_venda'," + QuotedStr(AppUser->CodEmpresa) + "," + prox_num_nf->Text + "," + \
        QuotedStr(DataHoraAtual) + "," + QuotedStr(AppUser->Usuario) + ")";
   }
   QyNumNF->ExecSQL();
   if (bExistNumNF) {
      QyNumNF->SQL->Text = "\
UPDATE tbl_parametro_sistema\
   SET valor_decimal = " + serie_nf->Text + "\
       ,data_atualizacao = " + QuotedStr(DataHoraAtual) + "\
       ,user_atualizacao = " + QuotedStr(AppUser->Usuario) + "\
 WHERE nome_parametro = 'serie_nf_venda'\
   AND valor_texto = " + QuotedStr(AppUser->CodEmpresa);
   } else {
      QyNumNF->SQL->Text = "\
INSERT INTO tbl_parametro_sistema\
       (nome_parametro, valor_texto, valor_decimal, data_atualizacao, user_atualizacao)\
VALUES ('serie_nf_venda'," + QuotedStr(AppUser->CodEmpresa) + "," + serie_nf->Text + "," + \
        QuotedStr(DataHoraAtual) + "," + QuotedStr(AppUser->Usuario) + ")";
   }
   QyNumNF->ExecSQL();
	delete QyNumNF;
} catch(Exception &e){
	String MsgErro = "Ocorreu o seguinte erro ao atualizar as informações de parametrização de numeração da NF:\n";
   MsgErro = MsgErro + e.Message;
   MessageBox(NULL,MsgErro.c_str(), "Mensagem de Erro", APP_ERROR);
   return false;
}
   return true;
}
//---------------------------------------------------------------------------
void __fastcall TObf1007::FormClose(TObject *Sender, TCloseAction &Action)
{
	delete Tolltips;
	Action = caFree;
}
//---------------------------------------------------------------------------

