/*
Módulo: Vendas - Representantes
Função: Cadastro Representantes x Comissão
Autor.: Jackson Patrick Werka
Data..: 01/07/2012
© Copyright 2012-2012 SoftGreen - All Rights Reserved
*/
//---------------------------------------------------------------------------
#ifndef uVdp1024H
#define uVdp1024H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "uFormBase02.h"
#include "uSfgToolbar.h"
#include <ExtCtrls.hpp>
#include <DB.hpp>
#include "SfgResButtons.hpp"
#include "CustomDbControls.h"
#include <DBCtrls.hpp>
#include <Mask.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <ActnList.hpp>
#include <Menus.hpp>
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "ZSqlUpdate.hpp"
#include "CustomButtons.h"
#include <Buttons.hpp>
#include "SfgAlignEdit.hpp"
#include <ComCtrls.hpp>
class SfgWorkEdition;
//---------------------------------------------------------------------------
class TVdp1024 : public TfrmBase02
{
__published:	// IDE-managed Components
   TZQuery *QyRepresentantes;
   TDataSource *DsRepresentantes;
   TLabel *Label1;
   TDBEdit *cod_representante;
   TGroupBox *GroupBox1;
   TDBCheckBox *ies_ativo;
   TDBDataComboBox *tipo_pessoa;
   TLabel *Label2;
   TGroupBox *GroupBox2;
	TLabel *Label3;
	TDBEdit *den_representante;
   TDBGrid *grdReprComissao;
   TZQuery *QyReprComissao;
   TDataSource *DsReprComissao;
	TLabel *Label7;
   TComboBox *mes_comissao;
   TLabel *Label4;
   TLabel *Label5;
   TAlignEdit *ano_comissao;
   TUpDown *UpDownAno;
   TIntegerField *CodPedidoVenda;
   TIntegerField *QyReprComissaoseq_parcela;
   TFloatField *QyReprComissaovalor_calculo;
   TFloatField *QyReprComissaoperc_comissao;
   TFloatField *ValorComissao;
   TStringField *QyReprComissaovalor_base_calculo;
   TDateTimeField *QyReprComissaodata_calculo;
   TIntegerField *QyReprComissaocod_conta_pagar;
   TResBitBtn *btFechamento;
   TActionList *ActionList1;
   TAction *execFechamento;
   TAction *delLine;
   TPopupMenu *PopupMenu1;
   TMenuItem *RemoverLinha1;
   TMenuItem *execFechamento1;
   TUpDown *UpDownMes;
   TResBitBtn *btParFormaPagto;
   TAction *execParFormaPagto;
   TMenuItem *execParFormaPagto1;
   TFloatField *QyReprComissaovalor_total;
   TZQuery *QySumComissao;
   TFloatField *QySumComissaovalor_comissao;
   TDataSource *DsSumComissao;
   TPanel *Panel6;
   TLabel *Label12;
   TDBEdit *valor_total;
   TResBitBtn *btRelatorio;
   TAction *execRelatorio;
   TMenuItem *VisualizarImpresso1;
   void __fastcall QyRepresentantesAfterScroll(TDataSet *DataSet);
   void __fastcall mes_comissaoChange(TObject *Sender);
   void __fastcall ano_comissaoChange(TObject *Sender);
   void __fastcall grdReprComissaoKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
   void __fastcall QyReprComissaoBeforeInsert(TDataSet *DataSet);
   void __fastcall SfgToolbarexecBtEditClickExecute(TObject *Sender);
   void __fastcall SfgToolbarexecBtSaveClickExecute(TObject *Sender);
   void __fastcall SfgToolbarexecBtCancelClickExecute(TObject *Sender);
   void __fastcall SfgToolbarexecBtDeleteClickExecute(TObject *Sender);
   void __fastcall execFechamentoExecute(TObject *Sender);
   void __fastcall delLineExecute(TObject *Sender);
   void __fastcall UpDownMesChangingEx(TObject *Sender, bool &AllowChange,
          short NewValue, TUpDownDirection Direction);
   void __fastcall EditItemSetFocus(TObject *Sender);
   void __fastcall grdEditCtrlKeyPress(TObject *Sender, char &Key);
   void __fastcall execParFormaPagtoExecute(TObject *Sender);
   void __fastcall BtOKClick(TObject *Sender);
   void __fastcall QyReprComissaoAfterScroll(TDataSet *DataSet);
   void __fastcall ValorComissaoSetText(TField *Sender,
          const AnsiString Text);
   void __fastcall execRelatorioExecute(TObject *Sender);
private:	// User declarations
   TForm *pFormPgto;
   TAlignEdit *pEdtPgto;
   float ValorTotal;
   float LastValorTotal;
	void __fastcall CarregarTipoPessoa();
   void __fastcall HabilitarItens(bool);
public:		// User declarations
   __fastcall TVdp1024(TComponent* Owner);
	void __fastcall SetPermissao(int Nivel);
};
//---------------------------------------------------------------------------
#endif
