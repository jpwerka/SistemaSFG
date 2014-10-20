/*
Módulo: Compras
Função: Envio de Pedidos de Compra por Email
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uSup1002H
#define uSup1002H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdMessageClient.hpp>
#include <IdSMTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "IdExplicitTLSClientServerBase.hpp"
#include "IdIOHandler.hpp"
#include "IdIOHandlerSocket.hpp"
#include "IdIOHandlerStack.hpp"
#include "IdSMTPBase.hpp"
#include "IdSSL.hpp"
#include <IdText.hpp>
#include <IdAttachmentFile.hpp>
#include <ExtCtrls.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TSup1002 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *gbInformacao;
	TEdit *Remetente;
	TEdit *Destinatario;
	TLabel *Label4;
	TLabel *Label1;
	TGroupBox *gbMensagem;
	TMemo *Mensagem;
	TLabel *Label5;
	TLabel *Label6;
	TGroupBox *gbItens;
	TDBGrid *ListItens;
	TButton *btOpcoes;
	TIdSMTP *ClienteSMTP;
	TIdSSLIOHandlerSocketOpenSSL *SSLHandlerSMTP;
	TEdit *EmailCopia;
	TLabel *Label7;
	TEdit *Assunto;
	TLabel *Label3;
	TPanel *Panel1;
	TButton *btCancel;
	TButton *btOK;
	TPanel *pnOpcoes;
	TEdit *SenhaEmail;
	TLabel *Label2;
	TCheckBox *SalvarMensagem;
	TCheckBox *LembrarSenha;
	TPanel *pnProgress;
	TProgressBar *ProgressMail;
	TLabel *lbInfoMail;
	TZQuery *QyCadProduto;
	TIntegerField *CodPedidoCompra;
	TIntegerField *QyCadProdutoseq_produto;
	TStringField *QyCadProdutocod_produto;
	TStringField *QyCadProdutoden_produto;
	TFloatField *QyCadProdutoqtd_produto;
	TDataSource *DataSource1;
	void __fastcall btOpcoesClick(TObject *Sender);
	void __fastcall ClienteSMTPStatus(TObject *ASender,
          const TIdStatus AStatus, const AnsiString AStatusText);
	void __fastcall pnOpcoesExit(TObject *Sender);
	void __fastcall btOKClick(TObject *Sender);
	void __fastcall LembrarSenhaClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall ListItensTitleClick(TColumn *Column);
private:	// User declarations
	void __fastcall EnviarEmail();
	void __fastcall MontaEmailText(TIdText *MsgPart);
	void __fastcall MontaEmailHtml(TIdText *MsgPart);
	void __fastcall MontaEmailImage(TIdAttachmentFile *MsgFile);
public:		// User declarations
	__fastcall TSup1002(TComponent* Owner);
	void __fastcall(__closure *OnSendMailSucess)();
};
//---------------------------------------------------------------------------
#endif
