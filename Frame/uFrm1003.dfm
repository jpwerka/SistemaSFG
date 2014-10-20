inherited Frm1003: TFrm1003
  Caption = 'Alterar Senha'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel2: TBevel [1]
    Left = 0
    Top = 101
    Width = 774
    Height = 2
    Align = alTop
    Shape = bsTopLine
  end
  inherited HeaderPanel: TPanel
    Caption = 'Alterar Senha'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    TabOrder = 3
    object Label1: TLabel
      Left = 19
      Top = 12
      Width = 61
      Height = 13
      Alignment = taRightJustify
      Caption = 'Senha Atual:'
    end
    object Label2: TLabel
      Left = 18
      Top = 64
      Width = 62
      Height = 13
      Alignment = taRightJustify
      Caption = 'Confirma'#231#227'o:'
    end
    object Label3: TLabel
      Left = 17
      Top = 38
      Width = 63
      Height = 13
      Alignment = taRightJustify
      Caption = 'Nova Senha:'
    end
    object Senha: TEdit
      Left = 83
      Top = 9
      Width = 135
      Height = 21
      MaxLength = 16
      PasswordChar = '*'
      TabOrder = 0
    end
    object CfSenha: TEdit
      Left = 83
      Top = 61
      Width = 135
      Height = 21
      MaxLength = 16
      PasswordChar = '*'
      TabOrder = 2
    end
    object NvSenha: TEdit
      Left = 83
      Top = 35
      Width = 135
      Height = 21
      MaxLength = 16
      PasswordChar = '*'
      TabOrder = 1
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 417
    TabOrder = 1
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 417
    TabOrder = 2
  end
  object SfgToolbar: TPanel
    Left = 0
    Top = 55
    Width = 774
    Height = 46
    Align = alTop
    BevelOuter = bvNone
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 4
    object btConfirmar: TResBitBtn
      Left = 6
      Top = 6
      Width = 32
      Height = 32
      Hint = 'Confirma a altera'#231#227'o da senha.'
      TabOrder = 0
      OnClick = btConfirmarClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'CONFIRMAR'
      GlyphResID = 0
    end
    object btCancelar: TResBitBtn
      Left = 44
      Top = 6
      Width = 32
      Height = 32
      Hint = 'Cancela a altera'#231#227'o da senha.'
      Cancel = True
      ModalResult = 2
      TabOrder = 1
      OnClick = btCancelarClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'CANCELAR'
      GlyphResID = 0
    end
  end
end
