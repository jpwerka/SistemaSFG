/*
Módulo: Vendas
Função: Análise Comissão Representantes (Filtros)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp2022H
#define uVdp2022H
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
#include <Grids.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include <DBGrids.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"
#include <DB.hpp>
//---------------------------------------------------------------------------
class TVdp2022 : public TfrmBase01
{
__published:	// IDE-managed Components
	TPanel *SfgToolbar;
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
   TLabel *Label7;
   TEdit *cod_representante;
   TResBitBtn *btPesqRepresentante;
   TEdit *den_representante;
   TDBGrid *grdRepresentantes;
   TLabel *Space01;
   TRadioGroup *valor_base_calculo;
   TResBitBtn *btInformar;
   TResBitBtn *btProcessar;
   TResBitBtn *btSair;
   TResBitBtn *btConfirmar;
   TResBitBtn *btCancelar;
   TResBitBtn *btAtualiza;
   TPopupMenu *PopupMenu1;
   TMenuItem *Informar1;
   TMenuItem *Processar1;
   TMenuItem *Atualizar1;
   TMenuItem *Confirmar1;
   TMenuItem *Cancelar1;
   TActionList *ActionList1;
   TAction *execInformar;
   TAction *execProcessar;
   TAction *execConfirmar;
   TAction *execCancelar;
   TAction *execAtualizar;
   TDataSource *DsComissao;
   TZQuery *CnsComissao;
   TZUpdateSQL *AtuComissao;
   TStringField *CnsComissaocod_representante;
   TFloatField *CnsComissaovalor_calculo;
   TFloatField *CnsComissaoperc_comissao;
   TFloatField *CnsComissaovalor_comissao;
   TSmallintField *CnsComissaovalor_base_calculo;
   TStringField *CnsComissaoden_representante;
   TSmallintField *CnsComissaomes_comissao;
   TSmallintField *CnsComissaoano_comissao;
   TDateTimeField *CnsComissaodata_calculo;
   TIntegerField *CodPedidoVenda;
   TIntegerField *CnsComissaoseq_parcela;
	void __fastcall cod_clienteExit(TObject *Sender);
	void __fastcall btPesqClienteClick(TObject *Sender);
	void __fastcall data_iniExit(TObject *Sender);
	void __fastcall data_fimExit(TObject *Sender);
	void __fastcall btExitClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
   void __fastcall btPesqRepresentanteClick(TObject *Sender);
   void __fastcall cod_representanteExit(TObject *Sender);
   void __fastcall execInformarExecute(TObject *Sender);
   void __fastcall execConfirmarExecute(TObject *Sender);
   void __fastcall execCancelarExecute(TObject *Sender);
   void __fastcall execProcessarExecute(TObject *Sender);
   void __fastcall execAtualizarExecute(TObject *Sender);
   void __fastcall grdRepresentantesKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall CnsComissaoBeforeInsert(TDataSet *DataSet);
   void __fastcall EditItemSetFocus(TObject *Sender);
   void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
private:	// User declarations
	TEdit *pEditRet;
	void __fastcall SearchReturn(Variant Value);
   void __fastcall HabilitaCampos(bool);
   void __fastcall RestauraGrid();
public:		// User declarations
	__fastcall TVdp2022(TComponent* Owner);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
