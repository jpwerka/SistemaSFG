inherited Frm1020: TFrm1020
  Caption = 'Cadastro de Empresas'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Empresas'
  end
  inherited BodyPanel: TPanel
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 91
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 44
        Height = 13
        Cursor = crArrow
        Caption = '&Empresa:'
        DragCursor = crDefault
        FocusControl = cod_empresa
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 90
        Top = 17
        Width = 74
        Height = 13
        Alignment = taRightJustify
        Caption = '&Nome Fantasia:'
        FocusControl = nome_fantasia
        Transparent = True
      end
      object Label3: TLabel
        Left = 6
        Top = 41
        Width = 66
        Height = 13
        Alignment = taRightJustify
        Caption = '&Raz'#227'o Social:'
        FocusControl = razao_social
        Transparent = True
      end
      object Label20: TLabel
        Left = 8
        Top = 65
        Width = 30
        Height = 13
        Alignment = taRightJustify
        Caption = 'CNP&J:'
        FocusControl = cnpj
        Transparent = True
        WordWrap = True
      end
      object Rtulo98: TLabel
        Left = 403
        Top = 65
        Width = 90
        Height = 13
        Alignment = taRightJustify
        Caption = '&Inscri'#231#227'o Estadual:'
        FocusControl = inscricao_estadual
        Transparent = True
      end
      object cod_empresa: TDBEdit
        Left = 57
        Top = 15
        Width = 28
        Height = 21
        CharCase = ecUpperCase
        Color = clWhite
        DataField = 'cod_empresa'
        DataSource = DsCadEmpresa
        TabOrder = 0
      end
      object nome_fantasia: TDBEdit
        Left = 167
        Top = 15
        Width = 428
        Height = 21
        Color = clWhite
        DataField = 'nome_fantasia'
        DataSource = DsCadEmpresa
        TabOrder = 1
      end
      object razao_social: TDBEdit
        Left = 76
        Top = 39
        Width = 519
        Height = 21
        Color = clWhite
        DataField = 'razao_social'
        DataSource = DsCadEmpresa
        TabOrder = 2
      end
      object cnpj: TDBEdit
        Left = 41
        Top = 63
        Width = 120
        Height = 21
        Color = clWhite
        DataField = 'cnpj'
        DataSource = DsCadEmpresa
        TabOrder = 3
      end
      object inscricao_estadual: TDBEdit
        Left = 496
        Top = 63
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'inscricao_estadual'
        DataSource = DsCadEmpresa
        TabOrder = 4
      end
    end
    object GroupBox3: TGroupBox
      Left = 0
      Top = 134
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
        Caption = 'N&'#250'mero:'
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
        Caption = 'E&stado:'
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
        Caption = 'C&omplemento:'
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
        DataSource = DsCadEmpresa
        TabOrder = 0
      end
      object numero: TDBEdit
        Left = 549
        Top = 15
        Width = 46
        Height = 21
        DataField = 'numero'
        DataSource = DsCadEmpresa
        TabOrder = 1
      end
      object cod_uf: TDBComboBox
        Left = 53
        Top = 39
        Width = 40
        Height = 21
        Hint = 'Duplo clique ou pressione '#39'+'#39'|para cadastrar um novo estado.'
        DataField = 'cod_uf'
        DataSource = DsCadEmpresa
        ItemHeight = 13
        TabOrder = 2
        OnChange = cod_ufChange
      end
      object cod_cidade: TDBDataComboBox
        Left = 201
        Top = 39
        Width = 216
        Height = 21
        Hint = 'Duplo clique ou pressione '#39'+'#39'|para cadastrar uma nova cidade.'
        DataField = 'cod_cidade'
        DataSource = DsCadEmpresa
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
        DataSource = DsCadEmpresa
        TabOrder = 4
      end
      object bairro: TDBEdit
        Left = 47
        Top = 63
        Width = 236
        Height = 21
        DataField = 'bairro'
        DataSource = DsCadEmpresa
        TabOrder = 5
      end
      object complemento: TDBEdit
        Left = 520
        Top = 63
        Width = 75
        Height = 21
        DataField = 'complemento'
        DataSource = DsCadEmpresa
        TabOrder = 6
      end
    end
    object GroupBox4: TGroupBox
      Left = 0
      Top = 225
      Width = 758
      Height = 43
      Cursor = crArrow
      Align = alTop
      Caption = 'Contato'
      TabOrder = 3
      object Label13: TLabel
        Left = 196
        Top = 17
        Width = 20
        Height = 13
        Alignment = taRightJustify
        Caption = 'Fa&x:'
        FocusControl = fax
        Transparent = True
        WordWrap = True
      end
      object Label11: TLabel
        Left = 9
        Top = 17
        Width = 45
        Height = 13
        Alignment = taRightJustify
        Caption = '&Telefone:'
        FocusControl = telefone
        Transparent = True
        WordWrap = True
      end
      object telefone: TDBEdit
        Left = 58
        Top = 15
        Width = 83
        Height = 21
        Color = clWhite
        DataField = 'telefone'
        DataSource = DsCadEmpresa
        TabOrder = 0
      end
      object fax: TDBEdit
        Left = 220
        Top = 15
        Width = 83
        Height = 21
        Color = clWhite
        DataField = 'fax'
        DataSource = DsCadEmpresa
        TabOrder = 1
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 91
      Width = 758
      Height = 43
      Cursor = crArrow
      Align = alTop
      Caption = 'Informa'#231#245'es'
      TabOrder = 1
      object Label12: TLabel
        Left = 323
        Top = 17
        Width = 86
        Height = 13
        Alignment = taRightJustify
        Caption = 'Re&gime Tribut'#225'rio:'
        Transparent = True
      end
      object Label14: TLabel
        Left = 8
        Top = 17
        Width = 94
        Height = 13
        Alignment = taRightJustify
        Caption = 'Inscri'#231#227'o Municip&al:'
        FocusControl = inscricao_municipal
        Transparent = True
      end
      object inscricao_municipal: TDBEdit
        Left = 106
        Top = 15
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'inscricao_municipal'
        DataSource = DsCadEmpresa
        TabOrder = 0
      end
      object regime_tributario: TDBDataComboBox
        Left = 414
        Top = 15
        Width = 181
        Height = 21
        DataField = 'regime_tributario'
        DataSource = DsCadEmpresa
        ItemHeight = 13
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadEmpresa: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterScroll = QyCadEmpresaAfterScroll
    SQL.Strings = (
      'SELECT cod_empresa, nome_fantasia,  razao_social,'
      '       cnpj, inscricao_estadual, inscricao_municipal,  '
      
        '       cep, logradouro, numero, complemento, bairro, cod_cidade,' +
        ' cod_uf,  '
      '       telefone, fax, regime_tributario'
      '  FROM tbl_empresa'
      ' ORDER BY cod_empresa')
    Params = <>
    Left = 616
    Top = 8
  end
  object DsCadEmpresa: TDataSource
    AutoEdit = False
    DataSet = QyCadEmpresa
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
end
