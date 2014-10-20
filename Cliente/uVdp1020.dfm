inherited Vdp1020: TVdp1020
  Left = 368
  Top = 71
  Caption = 'Cadastro de Clientes'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Clientes'
  end
  inherited BodyPanel: TPanel
    TabOrder = 5
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 42
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 35
        Height = 13
        Cursor = crArrow
        Caption = '&Cliente:'
        DragCursor = crDefault
        FocusControl = cod_cliente
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 181
        Top = 17
        Width = 24
        Height = 13
        Cursor = crArrow
        Caption = 'T&ipo:'
        DragCursor = crDefault
        FocusControl = tipo_pessoa
        Transparent = True
        WordWrap = True
      end
      object Label18: TLabel
        Left = 353
        Top = 18
        Width = 65
        Height = 13
        Caption = 'Classifica'#231#227'o:'
      end
      object cod_cliente: TDBEdit
        Left = 47
        Top = 15
        Width = 110
        Height = 21
        Color = clWhite
        DataField = 'cod_cliente'
        DataSource = DsCadCliente
        TabOrder = 0
      end
      object tipo_pessoa: TDBDataComboBox
        Left = 209
        Top = 15
        Width = 126
        Height = 21
        AutoDropDown = True
        DataField = 'tipo_pessoa'
        DataSource = DsCadCliente
        ItemHeight = 13
        Sorted = True
        TabOrder = 1
      end
      object ies_ativo: TDBCheckBox
        Left = 613
        Top = 17
        Width = 50
        Height = 14
        Caption = '&Ativo?'
        DataField = 'ies_ativo'
        DataSource = DsCadCliente
        TabOrder = 3
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
      object btObs: TResBitBtn
        Left = 570
        Top = 11
        Width = 24
        Height = 24
        Hint = 'Incluir uma observa'#231#227'o para o cliente.'
        TabOrder = 4
        OnClick = btObsClick
        GlyphLoadType = glByResName
        GlyphResName = 'OBSERVACAO'
        GlyphResID = 0
      end
      object cod_classificacao: TDBDataComboBox
        Left = 422
        Top = 15
        Width = 135
        Height = 21
        AutoDropDown = True
        DataField = 'cod_classificacao'
        DataSource = DsCadCliente
        ItemHeight = 13
        Sorted = True
        TabOrder = 2
      end
    end
    object grpInfo: TGroupBox
      Left = 0
      Top = 42
      Width = 758
      Height = 115
      Cursor = crArrow
      Align = alTop
      Caption = 'Informa'#231#245'es'
      TabOrder = 1
      object Label3: TLabel
        Left = 11
        Top = 17
        Width = 69
        Height = 13
        Alignment = taRightJustify
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_cliente
        Transparent = True
        WordWrap = True
      end
      object Label20: TLabel
        Left = 11
        Top = 65
        Width = 55
        Height = 13
        Alignment = taRightJustify
        Caption = 'CPF/CNP&J:'
        FocusControl = cpf_cnpj
        Transparent = True
        WordWrap = True
      end
      object Rtulo98: TLabel
        Left = 243
        Top = 65
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'R&G/IE:'
        FocusControl = rg_ie
        Transparent = True
        WordWrap = True
      end
      object Label55: TLabel
        Left = 440
        Top = 65
        Width = 63
        Height = 13
        Caption = '&Nasc./Fund.:'
        FocusControl = data_nasc_fund
        Transparent = True
      end
      object Label15: TLabel
        Left = 11
        Top = 41
        Width = 74
        Height = 13
        Alignment = taRightJustify
        Caption = '&Nome Fantasia:'
        FocusControl = nome_fantasia
        Transparent = True
      end
      object Label17: TLabel
        Left = 8
        Top = 89
        Width = 73
        Height = 13
        Cursor = crArrow
        Caption = '&Representante:'
        DragCursor = crDefault
        FocusControl = cod_representante
        Transparent = True
        WordWrap = True
      end
      object den_cliente: TDBEdit
        Left = 83
        Top = 15
        Width = 512
        Height = 21
        Color = clWhite
        DataField = 'den_cliente'
        DataSource = DsCadCliente
        TabOrder = 0
      end
      object cpf_cnpj: TDBEdit
        Left = 69
        Top = 63
        Width = 120
        Height = 21
        Color = clWhite
        DataField = 'cpf_cnpj'
        DataSource = DsCadCliente
        TabOrder = 2
      end
      object rg_ie: TDBEdit
        Left = 280
        Top = 63
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'rg_ie'
        DataSource = DsCadCliente
        TabOrder = 3
      end
      object data_nasc_fund: TDBEdit
        Left = 506
        Top = 63
        Width = 88
        Height = 21
        DataField = 'data_nasc_fund'
        DataSource = DsCadCliente
        TabOrder = 4
      end
      object btCalendar01: TCustomImgButton
        Left = 576
        Top = 66
        Width = 16
        Height = 16
        TabOrder = 5
        TabStop = False
        OnClick = btCalendar01Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object nome_fantasia: TDBEdit
        Left = 88
        Top = 39
        Width = 428
        Height = 21
        Color = clWhite
        DataField = 'nome_fantasia'
        DataSource = DsCadCliente
        TabOrder = 1
      end
      object cod_representante: TDBEdit
        Left = 84
        Top = 87
        Width = 110
        Height = 21
        Color = clWhite
        DataField = 'cod_representante'
        DataSource = DsCadCliente
        TabOrder = 6
      end
      object btPesqRepresentante: TResBitBtn
        Left = 198
        Top = 86
        Width = 24
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        TabStop = False
        OnClick = btPesqRepresentanteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_representante: TDBEdit
        Left = 226
        Top = 87
        Width = 369
        Height = 21
        TabStop = False
        Color = clWhite
        DataField = 'den_representante'
        DataSource = DsCadCliente
        TabOrder = 8
      end
    end
    object GroupBox3: TGroupBox
      Left = 0
      Top = 157
      Width = 758
      Height = 91
      Cursor = crArrow
      Align = alTop
      Caption = 'Endere'#231'o'
      TabOrder = 2
      object Label9: TLabel
        Left = 505
        Top = 17
        Width = 40
        Height = 13
        Caption = 'N'#250'me&ro:'
        FocusControl = numero
        Transparent = True
      end
      object Label8: TLabel
        Left = 492
        Top = 41
        Width = 24
        Height = 13
        Caption = 'CE&P:'
        FocusControl = cep
        Transparent = True
      end
      object Label7: TLabel
        Left = 13
        Top = 65
        Width = 30
        Height = 13
        Caption = '&Bairro:'
        FocusControl = bairro
        Transparent = True
      end
      object Label6: TLabel
        Left = 161
        Top = 41
        Width = 36
        Height = 13
        Caption = 'Ci&dade:'
        Transparent = True
      end
      object Label5: TLabel
        Left = 13
        Top = 41
        Width = 36
        Height = 13
        Caption = '&Estado:'
        FocusControl = cod_uf
        Transparent = True
      end
      object Label4: TLabel
        Left = 13
        Top = 17
        Width = 57
        Height = 13
        Caption = '&Logradouro:'
        FocusControl = logradouro
        Transparent = True
      end
      object Label10: TLabel
        Left = 448
        Top = 65
        Width = 67
        Height = 13
        Caption = 'Comp&lemento:'
        FocusControl = complemento
        Transparent = True
      end
      object logradouro: TDBEdit
        Left = 74
        Top = 15
        Width = 376
        Height = 21
        Color = clWhite
        DataField = 'logradouro'
        DataSource = DsCadCliente
        TabOrder = 0
      end
      object numero: TDBEdit
        Left = 549
        Top = 15
        Width = 46
        Height = 21
        DataField = 'numero'
        DataSource = DsCadCliente
        TabOrder = 1
      end
      object cod_uf: TDBComboBox
        Left = 53
        Top = 39
        Width = 40
        Height = 21
        DataField = 'cod_uf'
        DataSource = DsCadCliente
        ItemHeight = 13
        TabOrder = 2
        OnChange = cod_ufChange
      end
      object cod_cidade: TDBDataComboBox
        Left = 201
        Top = 39
        Width = 216
        Height = 21
        DataField = 'cod_cidade'
        DataSource = DsCadCliente
        ItemHeight = 13
        Sorted = True
        TabOrder = 3
        LookUpDataSet = QyCidade
        LookUpField = 'cod_cidade'
        ResultField = 'den_cidade'
      end
      object cep: TDBEdit
        Left = 520
        Top = 39
        Width = 75
        Height = 21
        Color = clWhite
        DataField = 'cep'
        DataSource = DsCadCliente
        TabOrder = 4
      end
      object bairro: TDBEdit
        Left = 47
        Top = 63
        Width = 236
        Height = 21
        DataField = 'bairro'
        DataSource = DsCadCliente
        TabOrder = 5
      end
      object complemento: TDBEdit
        Left = 520
        Top = 63
        Width = 75
        Height = 21
        DataField = 'complemento'
        DataSource = DsCadCliente
        TabOrder = 6
      end
    end
    object GroupBox4: TGroupBox
      Left = 0
      Top = 248
      Width = 758
      Height = 91
      Cursor = crArrow
      Align = alTop
      Caption = 'Contato'
      TabOrder = 3
      object Rtulo108: TLabel
        Left = 18
        Top = 41
        Width = 31
        Height = 13
        Alignment = taRightJustify
        Caption = 'E-&mail:'
        FocusControl = EmailForn
        Transparent = True
        WordWrap = True
      end
      object Label16: TLabel
        Left = 18
        Top = 17
        Width = 31
        Height = 13
        Alignment = taRightJustify
        Caption = 'N&ome:'
        FocusControl = Contato
        Transparent = True
        WordWrap = True
      end
      object Label14: TLabel
        Left = 13
        Top = 65
        Width = 36
        Height = 13
        Alignment = taRightJustify
        Caption = '&WWW:'
        FocusControl = UrlForn
        Transparent = True
        WordWrap = True
      end
      object Label13: TLabel
        Left = 490
        Top = 41
        Width = 20
        Height = 13
        Alignment = taRightJustify
        Caption = 'Fa&x:'
        FocusControl = FaxForn
        Transparent = True
        WordWrap = True
      end
      object Label12: TLabel
        Left = 475
        Top = 65
        Width = 35
        Height = 13
        Alignment = taRightJustify
        Caption = 'Cel&ular:'
        FocusControl = CelForn
        Transparent = True
        WordWrap = True
      end
      object Label11: TLabel
        Left = 465
        Top = 17
        Width = 45
        Height = 13
        Alignment = taRightJustify
        Caption = '&Telefone:'
        FocusControl = TelefoneForn
        Transparent = True
        WordWrap = True
      end
      object Contato: TDBEdit
        Left = 52
        Top = 15
        Width = 359
        Height = 21
        DataField = 'contato'
        DataSource = DsCadCliente
        TabOrder = 0
      end
      object TelefoneForn: TDBEdit
        Left = 514
        Top = 15
        Width = 83
        Height = 21
        Color = clWhite
        DataField = 'telefone'
        DataSource = DsCadCliente
        TabOrder = 1
      end
      object EmailForn: TDBEdit
        Left = 52
        Top = 39
        Width = 359
        Height = 21
        Color = clWhite
        DataField = 'email'
        DataSource = DsCadCliente
        TabOrder = 2
      end
      object FaxForn: TDBEdit
        Left = 514
        Top = 39
        Width = 83
        Height = 21
        Color = clWhite
        DataField = 'fax'
        DataSource = DsCadCliente
        TabOrder = 3
      end
      object CelForn: TDBEdit
        Left = 514
        Top = 63
        Width = 83
        Height = 21
        DataField = 'celular'
        DataSource = DsCadCliente
        TabOrder = 5
      end
      object UrlForn: TDBEdit
        Left = 52
        Top = 63
        Width = 359
        Height = 21
        Color = clWhite
        DataField = 'url'
        DataSource = DsCadCliente
        TabOrder = 4
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object grpObs: TGroupBox
    Left = 8
    Top = 444
    Width = 600
    Height = 120
    Caption = 'Observa'#231#227'o'
    TabOrder = 4
    Visible = False
    OnExit = grpObsExit
    object TPanel01: TPanel
      Left = 2
      Top = 15
      Width = 596
      Height = 103
      Align = alClient
      BevelOuter = bvNone
      BorderWidth = 4
      TabOrder = 0
      object observacao: TDBMemo
        Left = 4
        Top = 4
        Width = 588
        Height = 95
        Align = alClient
        Ctl3D = True
        DataField = 'observacao'
        DataSource = DsCadCliente
        ParentCtl3D = False
        ScrollBars = ssVertical
        TabOrder = 0
      end
    end
  end
  object QyCadCliente: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterScroll = QyCadClienteAfterScroll
    OnCalcFields = QyCadClienteCalcFields
    SQL.Strings = (
      'SELECT cod_cliente, den_cliente, nome_fantasia, ies_ativo,'
      '       tipo_pessoa, cpf_cnpj, rg_ie, data_nasc_fund,'
      
        '       cep, logradouro, numero, complemento, bairro, cod_cidade,' +
        ' cod_uf,  '
      '       telefone, fax, celular, email, contato, url, observacao,'
      '       cod_representante, cod_classificacao'
      '  FROM tbl_cliente'
      ' ORDER BY cod_cliente')
    Params = <>
    Left = 622
    Top = 8
  end
  object DsCadCliente: TDataSource
    AutoEdit = False
    DataSet = QyCadCliente
    Left = 656
    Top = 8
  end
  object QyCidade: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cidade, den_cidade, cod_uf'
      '  FROM tbl_cidade'
      ' ORDER BY cod_uf, den_cidade;')
    Params = <>
    Left = 429
    Top = 248
  end
  object QyRepresentante: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT den_representante'
      '  FROM tbl_representante'
      ' WHERE cod_representante =:cod_representante')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_representante'
        ParamType = ptUnknown
      end>
    Left = 588
    Top = 8
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_representante'
        ParamType = ptUnknown
      end>
  end
end
