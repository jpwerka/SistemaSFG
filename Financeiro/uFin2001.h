/*
Módulo: Financeiro
Função: Movimentações Caixa (Entradas x Saídas)
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uFin2001H
#define uFin2001H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase01.h"
#include "SfgResButtons.hpp"
#include <ExtCtrls.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include <DB.hpp>
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include "CustomButtons.h"
#include "SfgAlignEdit.hpp"
#include <Buttons.hpp>
//---------------------------------------------------------------------------
class TFin2001 : public TfrmBase01
{
__published:	// IDE-managed Components
	TGroupBox *gbParam;
	TGroupBox *gbSaida;
	TGroupBox *gbEntrada;
   TGroupBox *FooterPanel;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TDBGrid *DBGrid1;
	TZReadOnlyQuery *QyEntrada;
	TDataSource *DsEntrada;
	TIntegerField *QyEntradacod_lancamento;
	TIntegerField *QyEntradacod_documento;
	TStringField *QyEntradacod_cliente;
	TStringField *QyEntradanum_documento;
	TIntegerField *QyEntradaseq_documento;
	TDateTimeField *QyEntradadata_lancamento;
	TFloatField *QyEntradavalor_lancamento;
	TStringField *QyEntradacod_centro_custo;
	TStringField *QyEntradacod_plano_conta;
	TSplitter *SplitterBody;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TDBGrid *DBGrid2;
	TZReadOnlyQuery *QySaida;
	TIntegerField *LargeintField1;
	TIntegerField *LargeintField2;
	TStringField *StringField1;
	TStringField *StringField2;
	TIntegerField *IntegerField1;
	TDateTimeField *DateTimeField1;
	TFloatField *FloatField1;
	TStringField *StringField3;
	TStringField *StringField4;
	TDataSource *DsSaida;
	TLabel *Label7;
	TMaskEdit *data_ini;
	TCustomImgButton *btCalendar01;
	TLabel *Label12;
	TMaskEdit *data_fim;
	TCustomImgButton *btCalendar02;
	TComboBox *cbPeriodo;
	TLabel *Label8;
	TCustomImgButton *btAbaixo;
	TCustomImgButton *btAcima;
	TPanel *GridPanel;
	TResBitBtn *btAtualiza;
	TAlignEdit *edtTotalSaida;
	TAlignEdit *edtTotalEntrada;
	TLabel *Label9;
	TLabel *Label10;
	TStringField *QyEntradatipo_registro;
	TStringField *QySaidatipo_registro;
	TPopupMenu *PopupMenu1;
	TPopupMenu *PopupMenu2;
	TMenuItem *IrParaContaReceber1;
	TMenuItem *VisualizarPedidoVenda1;
	TImageList *ImageList1;
	TMenuItem *N1;
	TMenuItem *IncluirContaReceber1;
	TMenuItem *IncluirPedidoVenda1;
	TMenuItem *N11;
	TMenuItem *N21;
	TMenuItem *N2;
	TMenuItem *N31;
	TMenuItem *N41;
   TLabel *Label11;
   TAlignEdit *edtDiferenca;
	void __fastcall SplitterBodyMoved(TObject *Sender);
	void __fastcall btAcimaClick(TObject *Sender);
	void __fastcall btAbaixoClick(TObject *Sender);
	void __fastcall GridPanelResize(TObject *Sender);
	void __fastcall cbPeriodoChange(TObject *Sender);
	void __fastcall btAtualizaClick(TObject *Sender);
	void __fastcall btCalendar01Click(TObject *Sender);
	void __fastcall btCalendar02Click(TObject *Sender);
	void __fastcall IrParaContaReceber1Click(TObject *Sender);
	void __fastcall PopupMenu1Popup(TObject *Sender);
	void __fastcall VisualizarPedidoVenda1Click(TObject *Sender);
	void __fastcall IncluirContaReceber1Click(TObject *Sender);
	void __fastcall IncluirPedidoVenda1Click(TObject *Sender);
	void __fastcall PopupMenu2Popup(TObject *Sender);
	void __fastcall N11Click(TObject *Sender);
	void __fastcall N21Click(TObject *Sender);
	void __fastcall N31Click(TObject *Sender);
	void __fastcall N41Click(TObject *Sender);
private:	// User declarations
   int NivelPerm;
	void __fastcall RefazConsulta();
public:		// User declarations
	__fastcall TFin2001(TComponent* Owner);
   void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
