inherited Frm1001: TFrm1001
  Caption = 'Configura'#231#245'es'
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
    Caption = 'Configura'#231#245'es'
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
    object MarcaDagua: TImage
      Left = 0
      Top = 0
      Width = 758
      Height = 417
      Align = alClient
      Center = True
      Transparent = True
    end
    object Label3: TLabel
      Left = 342
      Top = 323
      Width = 85
      Height = 13
      Anchors = []
      Caption = 'Imagem de Fundo'
    end
    object gbRodRelatorio: TGroupBox
      Left = 0
      Top = 191
      Width = 693
      Height = 78
      Caption = 'Rodap'#233' Relat'#243'rios'
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 3
      object edtCidade: TEdit
        Left = 6
        Top = 17
        Width = 122
        Height = 19
        MaxLength = 30
        TabOrder = 0
        Text = 'Cidade'
        OnEnter = edtCidadeEnter
        OnExit = edtCidadeExit
      end
      object Edit1: TAlignEdit
        Left = 284
        Top = 16
        Width = 121
        Height = 18
        BorderStyle = bsNone
        Color = clSilver
        ReadOnly = True
        TabOrder = 1
        Text = 'Data/Hora'
        Alignment = taCenter
      end
      object Edit2: TAlignEdit
        Left = 564
        Top = 16
        Width = 122
        Height = 18
        BorderStyle = bsNone
        Color = clSilver
        ReadOnly = True
        TabOrder = 2
        Text = 'P'#225'gina X'
        Alignment = taRightJustify
      end
      object edtRodLivre01: TAlignEdit
        Left = 6
        Top = 35
        Width = 680
        Height = 19
        MaxLength = 255
        TabOrder = 3
        Text = 'Linha Rodap'#233' Livre 01'
        OnEnter = edtRodLivre01Enter
        OnExit = edtRodLivre01Exit
        Alignment = taCenter
      end
      object edtRodLivre02: TAlignEdit
        Left = 6
        Top = 53
        Width = 680
        Height = 19
        MaxLength = 255
        TabOrder = 4
        Text = 'Linha Rodap'#233' Livre 02'
        OnEnter = edtRodLivre02Enter
        OnExit = edtRodLivre02Exit
        Alignment = taCenter
      end
    end
    object gbImagens: TGroupBox
      Left = 0
      Top = 6
      Width = 693
      Height = 64
      Align = alCustom
      Caption = 'Imagens'
      TabOrder = 0
      object Label5: TLabel
        Left = 42
        Top = 15
        Width = 44
        Height = 13
        Caption = '&Logotipo:'
        FocusControl = LogotipoPath
        Transparent = True
      end
      object Label4: TLabel
        Left = 6
        Top = 39
        Width = 80
        Height = 13
        Caption = 'Figura do &Fundo:'
        FocusControl = MarcaDaguaPath
        Transparent = True
      end
      object btMarcaDagua: TButton
        Left = 397
        Top = 36
        Width = 21
        Height = 21
        Hint = 'Clique para escolher|uma figura para o fundo.'
        Caption = '...'
        TabOrder = 4
        OnClick = btMarcaDaguaClick
      end
      object btLogotipo: TButton
        Left = 397
        Top = 12
        Width = 21
        Height = 21
        Hint = 'Clique para escolher|uma figura para o logotipo.'
        Caption = '...'
        TabOrder = 1
        OnClick = btLogotipoClick
      end
      object btDelLogotipo: TButton
        Left = 423
        Top = 12
        Width = 85
        Height = 21
        Caption = 'Sem Logotipo'
        TabOrder = 2
        OnClick = btDelLogotipoClick
      end
      object btDelMarcaDagua: TButton
        Left = 423
        Top = 36
        Width = 85
        Height = 21
        Caption = 'Sem Fundo'
        TabOrder = 5
        OnClick = btDelMarcaDaguaClick
      end
      object LogotipoPath: TEdit
        Left = 91
        Top = 12
        Width = 301
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        TabOrder = 0
        OnExit = LogotipoPathExit
      end
      object MarcaDaguaPath: TEdit
        Left = 91
        Top = 36
        Width = 301
        Height = 21
        BevelInner = bvLowered
        BevelOuter = bvRaised
        TabOrder = 3
        OnExit = MarcaDaguaPathExit
      end
    end
    object gbServerMail: TGroupBox
      Left = 0
      Top = 70
      Width = 693
      Height = 42
      Caption = 'Servidor Sa'#237'da Email'
      TabOrder = 1
      object Label2: TLabel
        Left = 12
        Top = 18
        Width = 42
        Height = 13
        Caption = '&Servidor:'
        FocusControl = ServerEmail
      end
      object Label6: TLabel
        Left = 276
        Top = 18
        Width = 28
        Height = 13
        Caption = '&Porta:'
        FocusControl = PortaServerEmail
      end
      object ServerEmail: TEdit
        Left = 58
        Top = 15
        Width = 195
        Height = 21
        AutoSize = False
        BevelInner = bvLowered
        BevelOuter = bvRaised
        TabOrder = 0
      end
      object PortaServerEmail: TEdit
        Left = 307
        Top = 15
        Width = 62
        Height = 21
        TabOrder = 1
      end
      object RequerAutenticacao: TCheckBox
        Left = 400
        Top = 18
        Width = 129
        Height = 13
        Caption = '&Requer autentica'#231#227'o?'
        TabOrder = 2
      end
      object ConexaoSegura: TCheckBox
        Left = 550
        Top = 18
        Width = 134
        Height = 13
        Caption = '&Conex'#227'o segura? (SSL)'
        TabOrder = 3
      end
    end
    object gbCabRelatorio: TGroupBox
      Left = 0
      Top = 112
      Width = 693
      Height = 78
      Caption = 'Cabe'#231'alho Relat'#243'rios'
      Ctl3D = False
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentCtl3D = False
      ParentFont = False
      TabOrder = 2
      object RelatLogotipo: TImage
        Left = 6
        Top = 17
        Width = 170
        Height = 53
        Align = alCustom
        AutoSize = True
        Center = True
        Proportional = True
        Stretch = True
      end
      object Label7: TLabel
        Left = 69
        Top = 36
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
      object edtCabLivre01: TEdit
        Left = 180
        Top = 17
        Width = 505
        Height = 19
        MaxLength = 255
        TabOrder = 0
        Text = 'Linha Cabe'#231'alho Livre 01'
        OnEnter = edtCabLivre01Enter
        OnExit = edtCabLivre01Exit
      end
      object edtCabLivre02: TEdit
        Left = 180
        Top = 35
        Width = 505
        Height = 19
        MaxLength = 255
        TabOrder = 1
        Text = 'Linha Cabe'#231'alho Livre 02'
        OnEnter = edtCabLivre02Enter
        OnExit = edtCabLivre02Exit
      end
      object edtCabLivre03: TEdit
        Left = 180
        Top = 53
        Width = 505
        Height = 19
        MaxLength = 255
        TabOrder = 2
        Text = 'Linha Cabe'#231'alho Livre 03'
        OnEnter = edtCabLivre03Enter
        OnExit = edtCabLivre03Exit
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
  object OpenPicture: TOpenPictureDialog
    Ctl3D = False
    DefaultExt = '.bmp'
    Filter = 
      'Todos os formatos (*.bmp;*.jpeg;*.jpg)|*.bmp;*.jpeg;*.jpg|Bitmap' +
      's (*.bmp)|*.bmp|JPEG (*.jpg;*.jpeg)|*jpg;*.jpeg'
    Options = [ofHideReadOnly, ofExtensionDifferent, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Escolher Fundo'
    Left = 510
  end
end
