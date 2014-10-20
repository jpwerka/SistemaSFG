////---------------------------------------------------------------------------
//#include <vcl.h>
//#include "uSfgGlobals.h"
//#include "uSfgTools.h"
//#include "uDataModule.h"
//#include "uFormBase02.h"
//#include "uSfgToolTip.h"
//#include "ZDataset.hpp"
//#pragma hdrstop
//#include "uCVdp1001.h"
////---------------------------------------------------------------------------
//#pragma package(smart_init)
////---------------------------------------------------------------------------
//int forma_pagto_sem_finc;
//TNotifyEvent OldFechamentoClick;
//TZQuery *QyCadVenda;
//TZQuery *QySitPedidoVenda;
//
//class THackVdp1001 : public TfrmBase02 {
//public:
//   void __fastcall btFechamentoClick(TObject *Sender);
//};
////---------------------------------------------------------------------------
//void __fastcall THackVdp1001::btFechamentoClick(TObject *Sender)
//{
//   if (QyCadVenda->FieldByName("cod_forma_pagto")->AsInteger != forma_pagto_sem_finc) {
//      OldFechamentoClick(Sender);
//      return;
//   }
//   //A forma de pagamento é a mesma sem integração com financeiro
//   bool bFechado = false;
//	String Situacao;
//	QySitPedidoVenda->Refresh();
//	Situacao = QySitPedidoVenda->FieldByName("ies_situacao")->AsString;
//	if(Situacao == "F") {
//		MessageBox(Handle, "Pedido de venda já fechado.",Caption.c_str(),APP_INFORM);
//		return;
//	} else if(Situacao == "C") {
//		MessageBox(Handle, "Pedido de venda cancelado.",Caption.c_str(),APP_INFORM);
//		return;
//	} else if(MessageBox(Handle, "Confirma o fechamento do pedido de venda?",Caption.c_str(),APP_QUESTION)==ID_NO) {
//		return;
//	}
//	//Usuário confirmou o pedido de compra
//	String sSQL;
//	TZReadOnlyQuery *QyFechaPedido = new TZReadOnlyQuery(Application);
//	QyFechaPedido->Connection = AppConnection;
//try {
//   if (!SfgDataCenter->StartTrans()) {
//      MessageBox(Handle,"Erro ao iniciar uma transação no banco de dados", "Mensagem de Erro", APP_ERROR);
//      return;
//   }
//	//Fecha o pedido de venda
//	//Baixando os itens no estoque
//	sSQL = "CALL baixa_pedido_venda_estoque("+ QyCadVenda->FieldByName("cod_pedido_venda")->AsString +");";
//	QyFechaPedido->SQL->Text = sSQL;
//	QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
//	sSQL = "UPDATE tbl_pedido_venda SET ies_situacao = 'F', data_fechamento = now()";
//   sSQL += " WHERE cod_pedido_venda = " + QyCadVenda->FieldByName("cod_pedido_venda")->AsString;
//	QyFechaPedido->SQL->Text = sSQL;
//	QyFechaPedido->ExecSQL(); //Neste caso não retorna nada
//	SfgDataCenter->CommitTrans();
//   bFechado = true;
//} catch(Exception &e){
//	SfgDataCenter->RollbackTrans();
//	String Msg = "Ocorreu o seguinte erro ao efetuar o fechamento do pedido de venda:\n";
//	Msg = Msg + e.Message;
//	MessageBox(NULL,Msg.c_str(), "Mensagem de Erro", APP_ERROR);
//}
//	delete QyFechaPedido;
//	QySitPedidoVenda->Refresh();
//   if (bFechado)
//	   MessageBox(Handle,"Pedido de venda fechado com sucesso!",Caption.c_str(), APP_INFORM);
//}
////---------------------------------------------------------------------------
//void AlterButtonFechamento(TForm *pForm)
//{
//   THackVdp1001 *pForm02 = (THackVdp1001*)pForm;
//
//   forma_pagto_sem_finc = StrToInt(VarToStr(ValidacoesDB::GetParamValue(AppConnection,"CALL get_parametro_numero('forma_pagto_sem_finc');")));
//   if (forma_pagto_sem_finc == 0) {
//      MessageBox(NULL,"Não foi parametrizada a forma de pagamento sem integração com o financeiro!", "Parametrização", APP_INFORM);
//      return;
//   }
//   //Se foi parametrizado deve atribuir o novo evento ao botão de fechamento
//   QyCadVenda = (TZQuery*)pForm02->FindComponent("QyCadVenda");
//   if (QyCadVenda == NULL) {
//      MessageBox(NULL,"Não foi possível encontrar a referência da consulta dos dados da venda!", pForm02->Caption.c_str(), APP_INFORM);
//      return;
//   }
//   QySitPedidoVenda = (TZQuery*)pForm02->FindComponent("QySitPedidoVenda");
//   if (QySitPedidoVenda == NULL) {
//      MessageBox(NULL,"Não foi possível encontrar a referência da consulta de situação do pedido de venda!", pForm02->Caption.c_str(), APP_INFORM);
//      return;
//   }
//   TResBitBtn *btFechamento = (TResBitBtn*)pForm02->FindComponent("btFechamento");
//   if (btFechamento) {
//      OldFechamentoClick = btFechamento->OnClick;
//      btFechamento->OnClick = &pForm02->btFechamentoClick;
//      if (btFechamento->Action)
//         ((TCustomAction*)btFechamento->Action)->OnExecute = &pForm02->btFechamentoClick;;
//   } else {
//      MessageBox(NULL,"Não foi possível encontrar a referência do botão fechamento!", pForm02->Caption.c_str(), APP_INFORM);
//   }
//}
////---------------------------------------------------------------------------

