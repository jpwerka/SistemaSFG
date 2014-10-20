object Obf1007: TObf1007
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'OBF1007 - Numera'#231#227'o NF'
  ClientHeight = 85
  ClientWidth = 296
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 6
    Top = 6
    Width = 284
    Height = 43
    Caption = 'Numera'#231#227'o NF Venda'
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 18
      Width = 80
      Height = 13
      Caption = 'Pr'#243'ximo N'#250'mero:'
    end
    object Label2: TLabel
      Left = 199
      Top = 18
      Width = 27
      Height = 13
      Caption = 'S'#233'rie:'
    end
    object prox_num_nf: TAlignEdit
      Left = 92
      Top = 15
      Width = 90
      Height = 21
      Hint = 'Pr'#243'ximo n'#250'mero de nota fiscal a ser utilizado.'
      TabOrder = 0
      Alignment = taRightJustify
    end
    object serie_nf: TAlignEdit
      Left = 230
      Top = 15
      Width = 41
      Height = 21
      Hint = 'S'#233'rie das notas fiscais emitidas pelo sistema.'
      TabOrder = 1
      Alignment = taRightJustify
    end
  end
  object BtOk: TButton
    Left = 215
    Top = 56
    Width = 75
    Height = 23
    Hint = 'Altera a numera'#231#227'o para a pr'#243'xima nota fiscal.'
    Caption = '&OK'
    Default = True
    TabOrder = 2
    OnClick = BtOkClick
  end
  object BtCancel: TButton
    Left = 125
    Top = 56
    Width = 75
    Height = 23
    Hint = 'Cancela a altera'#231#227'o da numera'#231#227'o da nota fiscal.'
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 1
  end
end
