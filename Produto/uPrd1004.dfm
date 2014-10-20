inherited Prd1004: TPrd1004
  Caption = 'Atualiza'#231#227'o de Pre'#231'o de Produtos'
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
    Caption = 'Atualiza'#231#227'o Pre'#231'o Produtos'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    Caption = 'Panel2'
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 4
    object Label5: TLabel
      Left = 0
      Top = 91
      Width = 758
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 91
      Cursor = crArrow
      Align = alTop
      Caption = 'Parametros'
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 0
      object Label4: TLabel
        Left = 25
        Top = 67
        Width = 40
        Height = 13
        Caption = '&Produto:'
        FocusControl = cod_produto_ini
        Transparent = True
        WordWrap = True
      end
      object Label1: TLabel
        Left = 28
        Top = 42
        Width = 37
        Height = 13
        Caption = 'F&am'#237'lia:'
        FocusControl = cod_familia
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 224
        Top = 67
        Width = 18
        Height = 13
        Alignment = taRightJustify
        Caption = 'a&t'#233':'
        FocusControl = cod_produto_fim
        Transparent = True
        WordWrap = True
      end
      object Label3: TLabel
        Left = 8
        Top = 18
        Width = 57
        Height = 13
        Caption = '&Fornecedor:'
        FocusControl = cod_fornecedor
        Transparent = True
        WordWrap = True
      end
      object Label6: TLabel
        Left = 485
        Top = 67
        Width = 54
        Height = 13
        Alignment = taRightJustify
        Caption = 'P&ercentual:'
        FocusControl = cod_produto_ini
        Transparent = True
        WordWrap = True
      end
      object den_familia: TEdit
        Left = 201
        Top = 39
        Width = 270
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 5
      end
      object den_fornecedor: TEdit
        Left = 212
        Top = 15
        Width = 393
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 2
      end
      object cod_familia: TEdit
        Left = 71
        Top = 39
        Width = 97
        Height = 21
        TabOrder = 3
        OnExit = cod_familiaExit
      end
      object btSearchFamilia: TResBitBtn
        Left = 173
        Top = 38
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de fam'#237'lias.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        TabStop = False
        OnClick = btSearchFamiliaClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_produto_ini: TEdit
        Left = 71
        Top = 63
        Width = 110
        Height = 21
        TabOrder = 6
      end
      object btSearchProdutoIni: TResBitBtn
        Left = 185
        Top = 62
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        TabStop = False
        OnClick = btSearchProdutoIniClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_produto_fim: TEdit
        Left = 245
        Top = 63
        Width = 110
        Height = 21
        TabOrder = 8
      end
      object btSearchProdutoFim: TResBitBtn
        Left = 358
        Top = 62
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 9
        TabStop = False
        OnClick = btSearchProdutoFimClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_fornecedor: TEdit
        Left = 71
        Top = 15
        Width = 110
        Height = 21
        TabOrder = 0
        OnExit = cod_fornecedorExit
      end
      object btSearchFornecedor: TResBitBtn
        Left = 185
        Top = 14
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de fornecedores.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btSearchFornecedorClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object percentual: TAlignEdit
        Left = 544
        Top = 63
        Width = 48
        Height = 21
        BevelInner = bvNone
        TabOrder = 11
        Text = '0'
        OnKeyPress = percentualKeyPress
        Alignment = taRightJustify
      end
      object btAtualiza: TResBitBtn
        Left = 393
        Top = 61
        Width = 81
        Height = 24
        Action = execAtualizar
        Caption = 'At&ualizar'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -9
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 10
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
      object UpDownPercent: TUpDown
        Left = 592
        Top = 63
        Width = 16
        Height = 21
        Associate = percentual
        Min = 0
        Position = 0
        TabOrder = 12
        Wrap = False
      end
    end
    object grdProdutos: TStringAlignGrid
      Left = 0
      Top = 97
      Width = 758
      Height = 320
      Align = alClient
      ColCount = 7
      Ctl3D = True
      DefaultRowHeight = 18
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goDrawFocusSelected, goColSizing, goTabs, goRowSelect]
      ParentCtl3D = False
      TabOrder = 1
      OnDrawCell = grdProdutosDrawCell
      SelectedCellColor = clHighlight
      SelectedFontColor = clHighlightText
      ColWidths = (
        14
        22
        100
        90
        400
        90
        90)
      Cells = (
        1
        0
        'X'
        2
        0
        'Fam'#237'lia'
        3
        0
        'Produto'
        4
        0
        'Denomina'#231#227'o'
        5
        0
        'Pre'#231'o Venda'
        5
        1
        'R$ 0,00'
        6
        0
        'Pre'#231'o Final'
        6
        1
        'R$ 0,00')
      PropCell = (
        1
        0
        1
        2
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        1
        1
        1
        1
        0
        2
        0
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        3
        0
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        4
        0
        1
        2
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        5
        0
        1
        2
        0
        6
        0
        1
        2
        0)
      PropCol = (
        0
        1
        2
        0
        1
        1
        2
        0
        2
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        3
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        4
        6
        -2147483640
        -11
        'MS Sans Serif'
        0
        '[]'
        0
        5
        1
        0
        0
        6
        1
        0
        6
        16711680
        -11
        'MS Sans Serif'
        0
        '[]'
        0)
      PropRow = ()
      PropFixedCol = ()
      PropFixedRow = ()
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
  object Panel1: TPanel
    Left = 0
    Top = 55
    Width = 774
    Height = 46
    Align = alTop
    BevelOuter = bvNone
    BorderWidth = 6
    Ctl3D = False
    ParentCtl3D = False
    PopupMenu = PopupMenu1
    TabOrder = 1
    object btInformar: TResBitBtn
      Left = 6
      Top = 6
      Width = 32
      Height = 32
      Action = execInformar
      TabOrder = 0
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'ANOTAR'
      GlyphResID = 0
    end
    object btProcessar: TResBitBtn
      Left = 44
      Top = 6
      Width = 32
      Height = 32
      Action = execProcessar
      TabOrder = 1
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'PROCESSAR'
      GlyphResID = 0
    end
    object btSair: TResBitBtn
      Left = 82
      Top = 6
      Width = 32
      Height = 32
      Hint = 'Fechar Formul'#225'rio'
      Cancel = True
      TabOrder = 2
      OnClick = btSairClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'SAIR'
      GlyphResID = 0
    end
    object btConfirmar: TResBitBtn
      Left = 120
      Top = 6
      Width = 32
      Height = 32
      Action = execConfirmar
      TabOrder = 3
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'CONFIRMAR'
      GlyphResID = 0
    end
    object btCancelar: TResBitBtn
      Left = 158
      Top = 6
      Width = 32
      Height = 32
      Action = execCancelar
      TabOrder = 4
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'CANCELAR'
      GlyphResID = 0
    end
  end
  object ActionList1: TActionList
    Left = 708
    Top = 66
    object execPesquisa: TAction
      ShortCut = 16465
      OnExecute = execPesquisaExecute
    end
    object execInformar: TAction
      Hint = 'Informa os filtros para a|atuliza'#231#227'o dos pre'#231'os dos produtos.'
      ShortCut = 16457
      OnExecute = execInformarExecute
    end
    object execProcessar: TAction
      Hint = 
        'Processa a atualiza'#231#227'o dos pre'#231'os dos|produtos com base nos dado' +
        's informados.'
      ShortCut = 16464
      OnExecute = execProcessarExecute
    end
    object execConfirmar: TAction
      Hint = 'Confirma os dados informados'
      ShortCut = 16467
      OnExecute = execConfirmarExecute
    end
    object execCancelar: TAction
      Hint = 'Cancela a informa'#231#227'o dos dados'
      ShortCut = 16472
      OnExecute = execCancelarExecute
    end
    object execAtualizar: TAction
      Caption = 'At&ualizar'
      Hint = 'Carrega a lista de itens a serem atualizados'
      ShortCut = 16469
      OnExecute = btAtualizaClick
    end
  end
  object QyAtuProdutos: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT f.den_familia,'
      '       p.cod_produto, p.den_produto,'
      '       p.preco_venda'
      '  FROM tbl_produto p, tbl_familia f'
      ' WHERE p.cod_familia = f.cod_familia')
    Params = <>
    Left = 420
    Top = 264
    object QyAtuProdutosden_familia: TStringField
      FieldName = 'den_familia'
      Size = 30
    end
    object QyAtuProdutoscod_produto: TStringField
      FieldName = 'cod_produto'
      Size = 15
    end
    object QyAtuProdutosden_produto: TStringField
      FieldName = 'den_produto'
      Size = 75
    end
    object QyAtuProdutospreco_custo: TFloatField
      FieldName = 'preco_venda'
      currency = True
      Precision = 13
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 444
    Top = 60
    object Informar1: TMenuItem
      Action = execInformar
      Caption = 'Informar'
    end
    object Processar1: TMenuItem
      Action = execProcessar
      Caption = 'Processar'
    end
    object Pesquisar1: TMenuItem
      Action = execPesquisa
      Caption = 'Pesquisar'
    end
    object Atualizar1: TMenuItem
      Action = execAtualizar
    end
    object Confirmar1: TMenuItem
      Action = execConfirmar
      Caption = 'Confirmar'
    end
    object Cancelar1: TMenuItem
      Action = execCancelar
      Caption = 'Cancelar'
    end
  end
  object QyAtuPrecoProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'UPDATE tbl_produto'
      #9'SET preco_venda = :preco_final'
      ' WHERE cod_produto = :cod_produto')
    Params = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'preco_final'
        ParamType = ptUnknown
      end
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
      end>
    Left = 456
    Top = 264
    ParamData = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'preco_final'
        ParamType = ptUnknown
      end
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
      end>
  end
end
