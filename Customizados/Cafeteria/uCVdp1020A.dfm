object CVdp1020A: TCVdp1020A
  Left = 447
  Top = 195
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Senha'
  ClientHeight = 90
  ClientWidth = 210
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 36
    Top = 9
    Width = 34
    Height = 13
    Caption = '&Senha:'
  end
  object Label2: TLabel
    Left = 12
    Top = 33
    Width = 62
    Height = 13
    Caption = 'Co&nfirma'#231#227'o:'
  end
  object edtPdw: TEdit
    Left = 76
    Top = 6
    Width = 121
    Height = 21
    PasswordChar = '*'
    TabOrder = 0
  end
  object edtCfm: TEdit
    Left = 76
    Top = 30
    Width = 121
    Height = 21
    PasswordChar = '*'
    TabOrder = 1
  end
  object btOK: TButton
    Left = 24
    Top = 60
    Width = 75
    Height = 22
    Caption = '&OK'
    Default = True
    TabOrder = 2
    OnClick = btOKClick
  end
  object btCancel: TButton
    Left = 108
    Top = 60
    Width = 75
    Height = 22
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 3
  end
end
