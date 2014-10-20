object FrmLogin: TFrmLogin
  Left = 551
  Top = 313
  BorderIcons = []
  BorderStyle = bsNone
  ClientHeight = 113
  ClientWidth = 240
  Color = clBtnFace
  ParentFont = True
  OldCreateOrder = True
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 240
    Height = 113
    Align = alClient
    Caption = 'Login'
    TabOrder = 0
    object Label1: TLabel
      Left = 28
      Top = 22
      Width = 39
      Height = 13
      Caption = 'Usu'#225'rio:'
    end
    object Label3: TLabel
      Left = 33
      Top = 50
      Width = 34
      Height = 13
      Caption = 'Senha:'
    end
    object Login: TEdit
      Left = 72
      Top = 19
      Width = 145
      Height = 21
      Hint = 'Entre com o usu'#225'rio.'
      MaxLength = 16
      TabOrder = 0
    end
    object btOK: TButton
      Left = 24
      Top = 78
      Width = 80
      Height = 25
      Hint = 'Efetua o login e entra no sistema.'
      Caption = '&OK'
      Default = True
      ParentShowHint = False
      ShowHint = False
      TabOrder = 2
      OnClick = btOKClick
    end
    object btCancelar: TButton
      Left = 126
      Top = 78
      Width = 80
      Height = 25
      Hint = 'Cancela o login e sai do sistema.'
      Cancel = True
      Caption = '&Cancelar'
      ParentShowHint = False
      ShowHint = False
      TabOrder = 3
      OnClick = btCancelarClick
    end
    object Senha: TEdit
      Left = 72
      Top = 47
      Width = 145
      Height = 21
      Hint = 'Entre com a senha do usu'#225'rio.'
      MaxLength = 16
      PasswordChar = '*'
      TabOrder = 1
    end
  end
end
