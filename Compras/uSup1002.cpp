/*
Módulo: Compras
Função: Envio de Pedidos de Compra por Email
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
#include "uSup1002.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
__fastcall TSup1002::TSup1002(TComponent* Owner)
	: TForm(Owner)
{
	Variant MsgMail;
	Remetente->Color = AppConfig->Colors->Disabled;
	Remetente->Text = AppParEmail->SMTPNomeExibicao + " <" + AppParEmail->SMTPUsername + ">";
	SenhaEmail->Text = AppParEmail->SMTPPassword;
	if (SenhaEmail->Text.Length()) {
		LembrarSenha->Checked = true;
	}
	MsgMail = ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_texto('msg_mail_ped_compra');");
	Mensagem->Text = VarToStr(MsgMail);
	OnSendMailSucess = NULL;
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::btOpcoesClick(TObject *Sender)
{
	pnOpcoes->Show();
	SenhaEmail->SetFocus();
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::ClienteSMTPStatus(TObject *ASender,
		const TIdStatus AStatus, const AnsiString AStatusText)
{
	//ShowMessage("Status " + AStatusText + " " + IntToStr(AStatus));
	ProgressMail->StepIt();
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::pnOpcoesExit(TObject *Sender)
{
	pnOpcoes->Hide();
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::btOKClick(TObject *Sender)
{
	String SQL;
	if (!Destinatario->Text.Length()) {
		MessageBox(Handle,"Informe o destinatário da mensagem!",Caption.c_str(),APP_ATENTION);
		Destinatario->SetFocus();
		return;
	}
	if (!Assunto->Text.Length()) {
		MessageBox(Handle,"Informe o assunto da mensagem!",Caption.c_str(),APP_ATENTION);
		Assunto->SetFocus();
		return;
	}
	if (AppParEmail->SMTPAutenticacao && !SenhaEmail->Text.Length()) {
		MessageBox(Handle,"Informe a senha do email nas opções!",Caption.c_str(),APP_ATENTION);
		btOpcoes->SetFocus();
		return;
	}
	if (SalvarMensagem->Checked) {
		if (Mensagem->Text.Length() > 255) {
			MessageBox(Handle,"A mensagem que pode ser salva não deve ultrapassar 255 caracteres!",Caption.c_str(),APP_ATENTION);
			Mensagem->SetFocus();
			return;
		}
		SQL = "CALL set_parametro_texto('msg_mail_ped_compra','" + Mensagem->Text + "','" + AppUser->Usuario + "');";
		if (!ValidacoesDB::SetParamValue(AppConnection,SQL)) {
			MessageBox(Handle,"A mensagem informada em tela não pode ser salva!",Caption.c_str(),APP_ATENTION);
		}
	}
	if (LembrarSenha->Checked) {
		AppParEmail->SMTPPassword = SenhaEmail->Text;
		SQL = "CALL set_parametro_texto('epw_" + AppUser->Usuario + "','" + String(EncryptText(SenhaEmail->Text.c_str())) + "','" + AppUser->Usuario + "');";
		if (!ValidacoesDB::SetParamValue(AppConnection,SQL)) {
			MessageBox(Handle,"A senha informada em tela não pode ser salva!",Caption.c_str(),APP_ATENTION);
		}
	}
	EnviarEmail();
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::EnviarEmail()
{
	TIdMessage *MailMessage = new TIdMessage(this);
	TIdText *MsgPart;
	TIdAttachmentFile *MsgFile;

	bool AutenticouSMTP;

	pnProgress->Show();
	ProgressMail->Position = 0;
	Application->ProcessMessages();
	if (ClienteSMTP->Connected()) {
		ClienteSMTP->Disconnect();
	}

	ClienteSMTP->Host = AppParEmail->SMTPHost; // atribui o host (pop.gmail.com)
	ClienteSMTP->Port = AppParEmail->SMTPPorta; // atribui a porta (465)

	if (AppParEmail->SMTPAutenticacao) { // se requer autenticacao
		ClienteSMTP->Username = AppParEmail->SMTPUsername; // atribui o nome do usuario
		ClienteSMTP->Password = SenhaEmail->Text; // atribui a senha
	} else { // se não requer autenticacao
		ClienteSMTP->Username = ""; // limpa o usuario
		ClienteSMTP->Password = ""; // limpa a senha
	}

	if (AppParEmail->SMTPSSL) { // se requer conexao segura
		ClienteSMTP->IOHandler = SSLHandlerSMTP; // vincula o manipulador de SMTP ao cliente SMTP
		ClienteSMTP->UseTLS = utUseImplicitTLS; // atribui ao cliente SMTP o suporte implícito a TLS

		SSLHandlerSMTP->Port = ClienteSMTP->Port; // atribui a porta ao manipulador (igual a do cliente FTP)
		SSLHandlerSMTP->Destination = ClienteSMTP->Host + ":" + IntToStr(ClienteSMTP->Port); // indica o destino da conexão (pop.gmail.com:465)
		SSLHandlerSMTP->Host = ClienteSMTP->Host; // atribui o host (pop.gmail.com)
	} else { // se não requer conexao segura
		ClienteSMTP->IOHandler = NULL; // desvincula o manipulador de SMTP
		ClienteSMTP->UseTLS = utNoTLSSupport; // indica que nao ha suporte a TLS
	}

	AutenticouSMTP = false; // variavel para indicar se a autenticacao foi bem sucedida
	// *** montagem da mensagem ***
	// ****************************
	// cabecalho
	MailMessage->Clear();
	MailMessage->ContentType = "multipart/alternative";
	MailMessage->ContentDisposition = "inline";
	MailMessage->ContentTransferEncoding = "7bit";
	MailMessage->Encoding = meMIME;
	MailMessage->From->Address = AppParEmail->SMTPConta; // conta do remetente
	MailMessage->From->Name = AppParEmail->SMTPNomeExibicao; // nome do remetente
	MailMessage->Recipients->EMailAddresses = Destinatario->Text; // destinatarios (separados por vírgula! não é ponto e vírgula!)
	if (EmailCopia->Text.Length()) {
		MailMessage->CCList->EMailAddresses = EmailCopia->Text;
	}
	MailMessage->Subject = Assunto->Text;

	MsgPart = new TIdText(MailMessage->MessageParts, new TStringList());
	MontaEmailText(MsgPart);

	MsgPart = new TIdText(MailMessage->MessageParts, new TStringList());
	MsgPart->ContentType = "multipart/related";

	MsgPart = new TIdText(MailMessage->MessageParts, new TStringList());
	MontaEmailHtml(MsgPart);

	if (AppConfig->Images->LogotipoPath.Length() > 0) {
		MsgFile = new TIdAttachmentFile(MailMessage->MessageParts, AppConfig->Images->LogotipoPath);
		MontaEmailImage(MsgFile);
	}
	ProgressMail->StepIt();

	// efetua a conexao ao servidor SMTP
	if (!ClienteSMTP->Connected()) {
	try {
		ClienteSMTP->Connect(); // conecta ao SMTP
		if (AppParEmail->SMTPAutenticacao) { // se requer autenticacao
		  AutenticouSMTP = ClienteSMTP->Authenticate(); // efetua a atenticacao e retorna o resultado para a variável
		} else { // se nao requer autenticacao
			AutenticouSMTP = True; // assume que a conexao foi bem sucedida
		}
	} catch(Exception &E) { // em caso de erro gera um log com a mensagem de erro
		String Msg = "Não foi possível conectar ao servidor SMTP:\n" + E.Message;
		MessageBox(Handle, Msg.c_str(), Caption.c_str(), APP_ERROR);
		pnProgress->Hide();
		return;
	}
	}
	//ProgressMail->StepIt();

	// se a conexao foi bem sucedida, envia a mensagem
	if (AutenticouSMTP && ClienteSMTP->Connected()) {
	try {
		ClienteSMTP->Send(MailMessage);
	} catch(Exception &E) { // em caso de erro gera um log com a mensagem de erro
		String Msg = "Não foi possível enviar o email. Ocorreu o seguinte erro:\n" + E.Message;
		MessageBox(Handle, Msg.c_str(), Caption.c_str(), APP_ERROR);
		pnProgress->Hide();
	}
	}

	// depois de tudo pronto, desconecta do servidor SMTP
	if (ClienteSMTP->Connected()) {
		ClienteSMTP->Disconnect();
	}
	pnProgress->Hide();
	MessageBox(Handle, "Email enviado com sucesso!", Caption.c_str(), APP_INFORM);
	if (OnSendMailSucess != NULL)
		OnSendMailSucess();
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::MontaEmailText(TIdText *MsgPart)
{
	MsgPart->ContentType = "text/plain";
	//MsgPart->ContentTransfer = "quoted-printable";
	MsgPart->Body->Clear();
	MsgPart->Body->Add(Mensagem->Text);
	MsgPart->Body->Add("Itens:");
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::MontaEmailHtml(TIdText *MsgPart)
{
	int i;
	TListItem *ListItem;
	TStringStream *StrStream = new TStringStream("");
	TStrings *StrHtml = new TStringList();
	String HtmlMsg = "";
	String Rodape = "";
	String Itens = "";
	HRSRC html = FindResource(HInstance, "MAILPEDCOMPRA", RT_RCDATA);
	HGLOBAL HtmlData = LoadResource(HInstance, html);
	DWORD szbf = SizeofResource(HInstance, html);

	StrStream->Write(HtmlData,szbf);
	HtmlMsg = StrStream->DataString;

	if(AppConfig->Reports->RodCidade.Length() > 0) {
		Rodape = AppConfig->Reports->RodCidade + " - " + FormatDateTime("dd/mm/yyyy", Date());
	} else {
		Rodape = FormatDateTime("dd/mm/yyyy", Date());
	}

	i=0;
	QyCadProduto->First();
	while(!QyCadProduto->Eof) {
		i++;
		if (i%2) {
			Itens += "<tr style=\"background-color:#EFFAFF;\"><td style=\"border-right: 1px solid #CACACA;\">" + QyCadProduto->FieldByName("den_produto")->AsString + "</td><td style=\"text-align:right;\">" + FloatToStrF(QyCadProduto->FieldByName("qtd_produto")->AsFloat,ffNumber,13,3) + "</td></tr>";
		} else {
			Itens += "<tr style=\"background-color:#DEEBF5;\"><td style=\"border-right: 1px solid #CACACA;\">" + QyCadProduto->FieldByName("den_produto")->AsString + "</td><td style=\"text-align:right;\">" + FloatToStrF(QyCadProduto->FieldByName("qtd_produto")->AsFloat,ffNumber,13,3) + "</td></tr>";
		}
		QyCadProduto->Next();
	}

	//ShowMessage(StrStream->DataString);
	HtmlMsg = StringReplace(HtmlMsg, "[PEDIDO]", VarToStr(QyCadProduto->ParamByName("cod_pedido_compra")->Value), TReplaceFlags());
	//HtmlMsg = StringReplace(HtmlMsg, "[MENSAGEM]", Mensagem->Text, TReplaceFlags() << rfReplaceAll << rfIgnoreCase);
	HtmlMsg = StringReplace(HtmlMsg, "[MENSAGEM]", StringReplace(Mensagem->Text,'\n',"<br>",TReplaceFlags() << rfReplaceAll), TReplaceFlags());
	HtmlMsg = StringReplace(HtmlMsg, "[ITENS]", Itens, TReplaceFlags());
	HtmlMsg = StringReplace(HtmlMsg, "[RODAPE]", Rodape, TReplaceFlags());

	StrHtml->Text = HtmlMsg;

	MsgPart->ContentType = "text/html";
	//MsgFile->ContentTransfer = "7bit";
	MsgPart->ParentPart = 1;
	MsgPart->ContentTransfer = "quoted-printable";
	MsgPart->Body->Clear();
	MsgPart->Body->AddStrings(StrHtml);
	//MsgPart->Body->SaveToFile("email.html");
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::MontaEmailImage(TIdAttachmentFile *MsgFile)
{
	MsgFile->ContentType = "image/jpeg";
	MsgFile->ContentTransfer = "base64";
	MsgFile->ContentDisposition = "inline";
	MsgFile->ContentID = "<1234567890>";
	MsgFile->ParentPart = 1;
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::LembrarSenhaClick(TObject *Sender)
{
	if (!LembrarSenha->Checked) {
		AppParEmail->SMTPPassword = "";
		String SQL = "CALL set_parametro_texto('epw_" + AppUser->Usuario + "',NULL,'" + AppUser->Usuario + "');";
		if (!ValidacoesDB::SetParamValue(AppConnection,SQL)) {
			MessageBox(Handle,"Não foi possível excluir a senha do usuário!",Caption.c_str(),APP_ATENTION);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSup1002::ListItensTitleClick(TColumn *Column)
{
	QyCadProduto->SortedFields = Column->FieldName;
}
//---------------------------------------------------------------------------

