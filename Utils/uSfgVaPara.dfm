object SfgVaPara: TSfgVaPara
  Left = 488
  Top = 260
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'V'#225' Para'
  ClientHeight = 75
  ClientWidth = 198
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 17
    Top = 12
    Width = 36
    Height = 13
    Caption = 'C'#243'&digo:'
  end
  object VaPara: TEdit
    Left = 58
    Top = 9
    Width = 131
    Height = 21
    Hint = 'Digite o c'#243'digo que deseja localizar.'
    TabOrder = 0
  end
  object btOK: TButton
    Left = 12
    Top = 43
    Width = 80
    Height = 25
    Hint = 'Localizar o registro.'
    Caption = '&OK'
    Default = True
    TabOrder = 1
    OnClick = btOKClick
  end
  object btCancelar: TButton
    Left = 106
    Top = 43
    Width = 80
    Height = 25
    Hint = 'Cancela a localiza'#231#227'o do registro.'
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 2
  end
end
