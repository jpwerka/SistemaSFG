/*
Módulo: Vendas - Clientes
Função: Cadastro Clientes
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#include <vcl.h>
#include "uSfgGlobals.h"
#include "uSfgTools.h"
#include "uSfgCalendar.h"
#include "uDataModule.h"
#include "uSfgVdpCustom.h"
#include "uSfgWorkEdition.h"
#include "uSfgBrowseVdp.h"
#pragma hdrstop
#include "uVdp1020.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
void RegisterVdp1020(void) {
   AddAppForm("Vdp1020","Clientes");
   AddAppFormClass("TVdp1020",__classid(TVdp1020));
}
#pragma startup RegisterVdp1020
//---------------------------------------------------------------------------
__fastcall TVdp1020::TVdp1020(TComponent* Owner)
   : TfrmBase02(Owner)
{
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   if(hSfgVdpCustom) {
      SfgVdp1020BeforeCreate = (PSfgVdp1020AfterCreate)GetProcAddress(hSfgVdpCustom,"SfgVdp1020BeforeCreate");
      if (SfgVdp1020BeforeCreate)
         SfgVdp1020BeforeCreate(this);
   }
   CarregarTipoPessoa();
   CarregarEstado();
   CarregarClassificacao();
   QyRepresentante->Active = true;
   SfgToolbar->AfterCreateFields = &AfterCreateFields;
   SfgToolbar->DataSource = DsCadCliente;
   SfgToolbar->ValidInsert = &ValidInsert;
   SfgToolbar->ValidUpdate = &ValidUpdate;
   SfgToolbar->ValidDelete = &ValidDelete;
   SfgToolbar->WorkEdition->AfterWorkEdition = &AfterWorkEdition;
   QyCadCliente->FieldByName("tipo_pessoa")->OnChange = &TipoPessoaChange;
   QyCadCliente->FieldByName("cod_representante")->OnValidate = &CodRepresentanteValidate;
   den_representante->ReadOnly = true;
   den_representante->Color = AppConfig->Colors->Disabled;
   //Carrega as funções customizadas, caso a dll de customização foi encontrada
   if(hSfgVdpCustom) {
      SfgVdp1020AfterCreate = (PSfgVdp1020AfterCreate)GetProcAddress(hSfgVdpCustom,"SfgVdp1020AfterCreate");
      if (SfgVdp1020AfterCreate)
         SfgVdp1020AfterCreate(this);
   }
   UseCodAuto = (bool)(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('cod_aut_cliente');")) == "S");
	if (UseCodAuto) {
      TStrings *pStrings = SfgToolbar->WorkEdition->ListControls;
	   pStrings->Delete(pStrings->IndexOf("cod_cliente"));
	   cod_cliente->ReadOnly = true;
	   cod_cliente->Color = AppConfig->Colors->Disabled;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::AfterCreateFields(TDataSet *DataSet)
{
   TSfgMetaTable *MetaTable = AddMetaTable("tbl_representante");
   TSfgFieldDef *FieldDef = CreateFieldDef(MetaTable->FieldByName("den_representante"),DataSet);
   FieldDef->MetaField = NULL; //Anula o MetaField do campo virtual
   TField *Field = CreateField(FieldDef);
   Field->FieldKind = fkCalculated;
   Field->Index = DataSet->FieldByName("cod_representante")->Index + 1;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::ValidInsert(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
	if (!ValidaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::ValidUpdate(bool &bValid)
{
   if (!VerificaCampos()) {
      bValid = false;
      return;
   }
   bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::ValidDelete(bool &bValid)
{
	String SQL;
	SQL = "SELECT DISTINCT 1 FROM tbl_pedido_venda" \
			" WHERE cod_cliente = " + QuotedStr(cod_cliente->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Cliente possui pedidos de venda relacionados. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
//#ifdef USE_FINANCEIRO
	SQL = "SELECT DISTINCT 1 FROM tbl_conta_receber"\
			" WHERE cod_cliente = " + QuotedStr(cod_cliente->Text);
	if(ValidacoesDB::ExisteForeingKey(AppConnection,SQL)) {
		MessageBox(Handle, "Cliente possui contas a receber relacionadas. Exclusão não permitida!",Caption.c_str(),APP_ATENTION);
		bValid = false;
		return;
	}
//#endif
	bValid = true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::CarregarTipoPessoa()
{
   tipo_pessoa->Clear();
   tipo_pessoa->AddItem("Pessoa Física","F");
   tipo_pessoa->AddItem("Pessoa Jurídica","J");
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::CarregarEstado()
{
  TZQuery *QyUF = new TZQuery(this);
try
{
  QyUF->SQL->Text = "SELECT cod_uf FROM tbl_uf ORDER BY cod_uf";
  QyUF->Connection = AppConnection;
  QyUF->Active = true;
  while(!QyUF->Eof) {
    cod_uf->AddItem(QyUF->FieldByName("cod_uf")->AsString,NULL);
    QyUF->Next();
  }
}__finally{delete(QyUF);}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::CarregarClassificacao()
{
  TZQuery *QyClass = new TZQuery(this);
try
{
  QyClass->SQL->Text = "SELECT cod_classificacao, den_classificacao\
  FROM tbl_class_cliente ORDER BY cod_classificacao";
  QyClass->Connection = AppConnection;
  QyClass->Active = true;
  cod_classificacao->Clear();
  while(!QyClass->Eof) {
    cod_classificacao->AddItem(QyClass->FieldByName("den_classificacao")->AsString,QyClass->FieldByName("cod_classificacao")->Value);
    QyClass->Next();
  }
}__finally{delete(QyClass);}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::cod_ufChange(TObject *Sender)
{
   if(cod_uf->ReadOnly)
      return;
	QyCidade->Filtered = false;
	QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
	QyCidade->Filtered = true;
   cod_cidade->SetTableItems(true);
	cod_cidade->Field->Clear();
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1020::VerificaCampos()
{
	if (!UseCodAuto) {
	  if(!cod_cliente->Text.Length()) {
		   MessageBox(Handle, "Digite o código do cliente!",Caption.c_str(),APP_ATENTION);
		   cod_cliente->SetFocus();
		   return false;
      }
	}
	if(!den_cliente->Text.Length()) {
		MessageBox(Handle, "Digite a denominação do cliente!",Caption.c_str(),APP_ATENTION);
		den_cliente->SetFocus();
		return false;
	}
	if(cpf_cnpj->Text.Trim().Length()) {
      bool bFisica = bool(QyCadCliente->FieldByName("tipo_pessoa")->AsString == "F");
      if (bFisica) {
		   if(!Validacoes::ValidarCPF(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CPF válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      } else {
		   if(!Validacoes::ValidarCNPJ(cpf_cnpj->Text)){
			   MessageBox(Handle, "O valor informado não é um CNPJ válido!",
						Caption.c_str(),APP_ATENTION);
			   cpf_cnpj->SetFocus();
			   return false;
         }
      }
      String Msg = "Cliente com " + String((bFisica) ? "CPF" : "CNPJ");
	   String SQL = "SELECT cod_cliente FROM tbl_cliente" \
			   " WHERE cpf_cnpj = " + QuotedStr(cpf_cnpj->Text);
      //Se foi informado o RG/IE valida usando o mesmo no SQL
      if (rg_ie->Text.Trim().Length()) {
         SQL = SQL + " AND rg_ie = " +  QuotedStr(rg_ie->Text);
         Msg += (bFisica) ? "/RG" : "/IE";
      }
      //Se for modificação deve validar se o código do cliente é diferente
      if (QyCadCliente->State == dsEdit) {
         SQL = SQL + " AND cod_cliente != " +  QuotedStr(cod_cliente->Text);
      }
	   if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
         Msg += " já cadastrado!";
		   MessageBox(Handle, Msg.c_str(),Caption.c_str(),APP_ATENTION);
		   cpf_cnpj->SetFocus();
		   return false;
	   }
      if (rg_ie->Text.Trim().Length()) {
         String Pergunta = "Foi informado " + String((bFisica) ? "o RG" : "a IE") +
                           " do cliente.\nDeseja validar apenas pelo " + ((bFisica) ? "CPF?" : "CNPJ?");
         if (MessageBox(Handle, Pergunta.c_str(),Caption.c_str(),APP_QUESTION) == ID_YES) {
            SQL = "SELECT cod_cliente FROM tbl_cliente" \
                  " WHERE cpf_cnpj = " + QuotedStr(cpf_cnpj->Text);
            //Se for modificação deve validar se o código do cliente é diferente
            if (QyCadCliente->State == dsEdit) {
               SQL = SQL + " AND cod_cliente != " +  QuotedStr(cod_cliente->Text);
            }
            if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
               Msg = "Cliente com " + String((bFisica) ? "CPF" : "CNPJ") + " já cadastrado!";
               MessageBox(Handle, Msg.c_str(),Caption.c_str(),APP_ATENTION);
               cpf_cnpj->SetFocus();
               return false;
            }
         }
      }
	}
	return true;
}
//---------------------------------------------------------------------------
bool __fastcall TVdp1020::ValidaCampos()
{
	String SQL;
	if (!UseCodAuto) {
	SQL = "SELECT cod_cliente FROM tbl_cliente" \
			" WHERE cod_cliente = " + QuotedStr(cod_cliente->Text);
	if(ValidacoesDB::ExistePrimaryKey(AppConnection,SQL)) {
		MessageBox(Handle, "Cliente já cadastrado!",Caption.c_str(),APP_ATENTION);
		cod_cliente->SetFocus();
		return false;
	}
   } else { //Deve buscar o próximo código do cliente
      String ProxCod = "";
      if (!ValidacoesDB::GetProxCod(AppConnection,"prox_cod_cliente",ProxCod)) {
   		MessageBox(Handle, "Erro ao buscar próximo código do cliente!",Caption.c_str(),APP_ATENTION);
         return false;
      }
      QyCadCliente->FieldByName("cod_cliente")->AsString = ProxCod;
   }
	return true;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::btCalendar01Click(TObject *Sender)
{
	ExecCalendar(data_nasc_fund);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::QyCadClienteAfterScroll(TDataSet *DataSet)
{
   TipoPessoaChange(tipo_pessoa->Field);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::TipoPessoaChange(TField *Sender)
{
   if (Sender->AsString == "F") {
      QyCadCliente->FieldByName("cpf_cnpj")->EditMask = CPFMask;
   } else {
      QyCadCliente->FieldByName("cpf_cnpj")->EditMask = CNPJMask;
   }
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::grpObsExit(TObject *Sender)
{
   grpObs->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::btObsClick(TObject *Sender)
{
   TPoint pt;
   pt.x = 0;
   pt.y = 0;
   pt = grpInfo->ClientToParent(pt,this);
	grpObs->Top = pt.y;
	grpObs->Left = pt.x;
	grpObs->Show();
	observacao->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::QyCadClienteCalcFields(TDataSet *DataSet)
{
   QyRepresentante->ParamByName("cod_representante")->Value = QyCadCliente->FieldByName("cod_representante")->Value;
   QyRepresentante->Refresh();
   QyCadCliente->FieldByName("den_representante")->AsString = QyRepresentante->FieldByName("den_representante")->AsString;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::btPesqRepresentanteClick(TObject *Sender)
{
	SfgBrowse::EscolheRepresentante(this,&SearchRepresentante);
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::SearchRepresentante(Variant Value)
{
	cod_representante->Field->Value = Value;
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::CodRepresentanteValidate(TField *Sender)
{
	String sSQL;
	String sRet;
	if(!Sender->AsString.Length()) {
		den_representante->Text = "";
		return;
   }
	sSQL = "SELECT den_representante FROM tbl_representante" \
			" WHERE cod_representante = " + QuotedStr(Sender->AsString);
	sRet = ValidacoesDB::GetDenominacaoByKey(AppConnection,sSQL);
	if(sRet.Length() <= 0) {
		throw Exception("Representante não cadastrado!");
	} else {
		den_representante->Text = sRet;
	}
}
//---------------------------------------------------------------------------
void __fastcall TVdp1020::AfterWorkEdition(bool Enable, TColor Color)
{
   btPesqRepresentante->Enabled = Enable;
   //Retirando os filtros por cidade
   QyCidade->Filtered = false;
   if (Enable) { //Porém se for habilitar, deve filtrar novamente
      QyCidade->Filter = "cod_uf = " + QuotedStr(cod_uf->Text);
      QyCidade->Filtered = true;
   }
   cod_cidade->SetTableItems(true);
}
//---------------------------------------------------------------------------
/*   String SQL = \
"SELECT c.cod_cliente, c.tipo_pessoa, c.den_cliente, c.nome_fantasia,\
       c.cpf_cnpj, c.rg_ie,  c.logradouro, c.numero, c.complemento,\
       c.bairro, d.den_cidade, c.cod_uf, c.cep, c.data_nasc_fund,\
       c.telefone, c.fax, c.celular, c.ies_ativo, c.email,\
       c.contato, c.url, c.observacao,\
       c.cod_representante, r.den_representante,\
       c.cod_classificacao, l.den_classificacao\
  FROM tbl_cliente c\
  LEFT JOIN tbl_cidade d\
    ON d.cod_cidade = c.cod_cidade\
  LEFT JOIN tbl_representante r\
    ON r.cod_representante = c.cod_representante\
  LEFT JOIN tbl_class_cliente l\
    ON l.cod_classificacao = c.cod_classificacao";

   //Recuperando o filtro do formulário
   if (SfgToolbar->WhereFilter.Length() > 0) {
      String WhereFilter = SfgToolbar->WhereFilter;
      //Deve fazer replace dos capos que possam gerar duplicatas
      //  cod_cidade, cod_representante, cod_classificacao
      WhereFilter = StringReplace(WhereFilter, "cod_cidade", "c.cod_cidade", TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
      WhereFilter = StringReplace(WhereFilter, "cod_representante", "c.cod_representante", TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
      WhereFilter = StringReplace(WhereFilter, "cod_classificacao", "c.cod_classificacao", TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
      SQL = SQL + " WHERE " + WhereFilter;
   }
   SQL += ((SfgToolbar->OrderByFilter.Length() > 0) ? (" " + SfgToolbar->OrderByFilter) : (" " + SfgToolbar->OrderByOrigin));
*/
//---------------------------------------------------------------------------


