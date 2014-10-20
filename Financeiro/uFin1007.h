/*
Módulo: Financeiro
Função: Baixa em Lote Contas à Receber
Autor.: Jackson Patrick Werka
Data..: 25/11/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin1007H
#define uFin1007H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "SfgResButtons.hpp"
#include "uFormBase01.h"
#include <ExtCtrls.hpp>
#include <Mask.hpp>
#include <DBCtrls.hpp>
#include "CustomButtons.h"
#include <Buttons.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include "SfgAlignGrid.hpp"
#include <Grids.hpp>
#include "SfgAlignEdit.hpp"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBGrids.hpp>
//---------------------------------------------------------------------------
class TFin1007 : public TfrmBase01
{
__published:	// IDE-managed Components
	TBevel *Bevel2;
	TGroupBox *gbFiltros;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *cod_cliente;
	TResBitBtn *btPesqCliente;
	TEdit *den_cliente;
	TMaskEdit *data_ini;
	TCustomImgButton *btCalendar01;
	TMaskEdit *data_fim;
	TCustomImgButton *btCalendar02;
	TLabel *Label12;
   TActionList *ActionList1;
   TAction *execInformar;
   TAction *execProcessar;
   TAction *execConfirmar;
   TAction *execCancelar;
   TAction *execAtualizar;
   TPopupMenu *PopupMenu1;
   TMenuItem *Informar1;
   TMenuItem *Processar1;
   TMenuItem *Atualizar1;
   TMenuItem *Confirmar1;
   TMenuItem *Cancelar1;
   TPanel *SfgToolbar;
   TResBitBtn *btInformar;
   TResBitBtn *btProcessar;
   TResBitBtn *btSair;
   TResBitBtn *btConfirmar;
   TResBitBtn *btCancelar;
   TLabel *Label5;
   TDBGrid *grdParcelas;
   TResBitBtn *btAtualiza;
   TPanel *Panel6;
   TLabel *Label3;
   TAlignEdit *valor_total;
   TAlignEdit *valor_recebto;
   TLabel *Label4;
   TZQuery *QyCnsCtaRec;
   TDataSource *DsAtuCtaRec;
   TStringField *QyCnsCtaReccod_cliente;
   TStringField *QyCnsCtaRecden_cliente;
   TIntegerField *QyCnsCtaReccod_conta_receber;
   TIntegerField *QyCnsCtaRecseq_parcela;
   TDateTimeField *QyCnsCtaRecdata_vencimento;
   TFloatField *QyCnsCtaRecvalor_parcela;
   TStringField *QyCnsCtaRecies_recebido;
   TFloatField *QyCnsCtaRecvalor_recebido;
	void __fastcall cod_clienteExit(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
   void __fastcall btInformarClick(TObject *Sender);
   void __fastcall btAtualizaClick(TObject *Sender);
   void __fastcall btConfirmarClick(TObject *Sender);
   void __fastcall btCancelarClick(TObject *Sender);
	void __fastcall btProcessarClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
   void __fastcall grdParcelasMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
   void __fastcall EditItemSetFocus(TObject *Sender);
   void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
   void __fastcall grdParcelasDrawColumnCell(TObject *Sender,
          const TRect &Rect, int DataCol, TColumn *Column,
          TGridDrawState State);
   void __fastcall grdParcelasColEnter(TObject *Sender);
   void __fastcall grdParcelasColExit(TObject *Sender);
   void __fastcall QyCnsCtaRecBeforeInsert(TDataSet *DataSet);
   void __fastcall ValorRecebidoSetText(TField *Sender,
          const AnsiString Text);
   void __fastcall grdParcelasKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
	TEdit *pEditRet;
   float FValorRecebto;
   float FValorTotal;
	void __fastcall SearchReturn(Variant Value);
	void __fastcall HabilitaCampos(bool Habilita);
public:		// User declarations
	__fastcall TFin1007(TComponent* Owner);
	void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
