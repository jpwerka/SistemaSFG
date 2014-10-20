inherited Frm1005: TFrm1005
  Caption = 'Codifica'#231#245'es'
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
    Caption = 'Codifica'#231#245'es'
    object Label1: TLabel
      Left = 63
      Top = 18
      Width = 41
      Height = 13
      Caption = 'Logotipo'
      Font.Charset = ANSI_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    TabOrder = 4
    object gbCodigos: TGroupBox
      Left = 0
      Top = 4
      Width = 693
      Height = 141
      Align = alCustom
      Caption = 'Codifica'#231#245'es Atutom'#225'ticas'
      TabOrder = 0
      object Label5: TLabel
        Left = 46
        Top = 42
        Width = 35
        Height = 13
        Caption = '&Cliente:'
        FocusControl = PreCli
        Transparent = True
      end
      object Label4: TLabel
        Left = 24
        Top = 66
        Width = 57
        Height = 13
        Caption = '&Fornecedor:'
        FocusControl = PreFor
        Transparent = True
      end
      object Label2: TLabel
        Left = 142
        Top = 18
        Width = 32
        Height = 13
        Caption = 'Prefixo'
        Transparent = True
      end
      object Label3: TLabel
        Left = 222
        Top = 18
        Width = 77
        Height = 13
        Caption = 'Pr'#243'ximo N'#250'mero'
        Transparent = True
      end
      object Label6: TLabel
        Left = 8
        Top = 90
        Width = 73
        Height = 13
        Caption = '&Representante:'
        FocusControl = PreRep
        Transparent = True
      end
      object CheckBox1: TLabel
        Left = 320
        Top = 18
        Width = 106
        Height = 13
        Caption = 'Completar com &Zeros?'
      end
      object Label7: TLabel
        Left = 448
        Top = 18
        Width = 40
        Height = 13
        Caption = 'Exemplo'
        Transparent = True
      end
      object ExeCodCli: TLabel
        Left = 448
        Top = 42
        Width = 139
        Height = 13
        AutoSize = False
        Caption = 'Exemplo'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object ExeCodFor: TLabel
        Left = 448
        Top = 66
        Width = 139
        Height = 13
        AutoSize = False
        Caption = 'Exemplo'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object ExeCodRep: TLabel
        Left = 448
        Top = 90
        Width = 139
        Height = 13
        AutoSize = False
        Caption = 'Exemplo'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object Bevel3: TBevel
        Left = 86
        Top = 33
        Width = 461
        Height = 2
        Shape = bsTopLine
      end
      object Label8: TLabel
        Left = 91
        Top = 18
        Width = 37
        Height = 13
        Caption = 'Utilizar?'
        Transparent = True
      end
      object Label9: TLabel
        Left = 45
        Top = 115
        Width = 36
        Height = 13
        Caption = '&Cidade:'
        FocusControl = PreCid
        Transparent = True
      end
      object ExeCodCid: TLabel
        Left = 448
        Top = 115
        Width = 139
        Height = 13
        AutoSize = False
        Caption = 'Exemplo'
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        ParentFont = False
        Transparent = True
      end
      object PreCli: TEdit
        Left = 132
        Top = 39
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 5
        TabOrder = 0
        OnExit = ClienteExit
      end
      object PreFor: TEdit
        Left = 132
        Top = 63
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 5
        TabOrder = 12
        OnExit = FornecedorExit
      end
      object ZeroCli: TEdit
        Left = 352
        Top = 39
        Width = 25
        Height = 21
        ReadOnly = True
        TabOrder = 2
        Text = '0'
        OnClick = ClienteExit
      end
      object CodAutoCli: TCheckBox
        Left = 96
        Top = 42
        Width = 15
        Height = 13
        Alignment = taLeftJustify
        TabOrder = 1
        OnClick = CodAutoCliClick
      end
      object ProxCli: TAlignEdit
        Left = 221
        Top = 39
        Width = 80
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 10
        TabOrder = 3
        OnExit = ClienteExit
        Alignment = taRightJustify
      end
      object ProxFor: TAlignEdit
        Left = 221
        Top = 63
        Width = 80
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 10
        TabOrder = 4
        OnExit = FornecedorExit
        Alignment = taRightJustify
      end
      object PreRep: TEdit
        Left = 132
        Top = 87
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 5
        TabOrder = 5
        OnExit = RepresentaExit
      end
      object ProxRep: TAlignEdit
        Left = 221
        Top = 87
        Width = 80
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 10
        TabOrder = 6
        OnExit = RepresentaExit
        Alignment = taRightJustify
      end
      object ZeroFor: TEdit
        Left = 352
        Top = 63
        Width = 25
        Height = 21
        ReadOnly = True
        TabOrder = 7
        Text = '0'
        OnClick = FornecedorExit
      end
      object ZeroRep: TEdit
        Left = 352
        Top = 87
        Width = 25
        Height = 21
        ReadOnly = True
        TabOrder = 8
        Text = '0'
        OnClick = RepresentaExit
      end
      object UpDownCli: TUpDown
        Left = 377
        Top = 39
        Width = 16
        Height = 21
        Associate = ZeroCli
        Min = 0
        Max = 10
        Position = 0
        TabOrder = 9
        Wrap = False
        OnClick = UpDownCliClick
      end
      object UpDownFor: TUpDown
        Left = 377
        Top = 63
        Width = 16
        Height = 21
        Associate = ZeroFor
        Min = 0
        Max = 10
        Position = 0
        TabOrder = 10
        Wrap = False
        OnClick = UpDownForClick
      end
      object UpDownRep: TUpDown
        Left = 377
        Top = 87
        Width = 16
        Height = 21
        Associate = ZeroRep
        Min = 0
        Max = 10
        Position = 0
        TabOrder = 11
        Wrap = False
        OnClick = UpDownRepClick
      end
      object CodAutoFor: TCheckBox
        Left = 96
        Top = 66
        Width = 15
        Height = 13
        Alignment = taLeftJustify
        TabOrder = 13
        OnClick = CodAutoForClick
      end
      object CodAutoRep: TCheckBox
        Left = 96
        Top = 90
        Width = 15
        Height = 13
        Alignment = taLeftJustify
        TabOrder = 14
        OnClick = CodAutoRepClick
      end
      object CodAutoCid: TCheckBox
        Left = 96
        Top = 115
        Width = 15
        Height = 13
        Alignment = taLeftJustify
        TabOrder = 15
        OnClick = CodAutoCidClick
      end
      object PreCid: TEdit
        Left = 132
        Top = 112
        Width = 60
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 2
        TabOrder = 16
        OnExit = CidadeExit
      end
      object ProxCid: TAlignEdit
        Left = 221
        Top = 112
        Width = 80
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        CharCase = ecUpperCase
        MaxLength = 5
        TabOrder = 17
        OnExit = CidadeExit
        Alignment = taRightJustify
      end
      object ZeroCid: TEdit
        Left = 352
        Top = 112
        Width = 25
        Height = 21
        ReadOnly = True
        TabOrder = 18
        Text = '0'
        OnClick = RepresentaExit
      end
      object UpDownCid: TUpDown
        Left = 377
        Top = 112
        Width = 16
        Height = 21
        Associate = ZeroCid
        Min = 0
        Max = 5
        Position = 0
        TabOrder = 19
        Wrap = False
        OnClick = UpDownCidClick
      end
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 417
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 417
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
    TabOrder = 1
    object btConfirmar: TResBitBtn
      Left = 6
      Top = 6
      Width = 32
      Height = 32
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
