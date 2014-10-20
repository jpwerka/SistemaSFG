object Prd2002: TPrd2002
  Left = 0
  Top = 0
  Width = 774
  Height = 544
  HorzScrollBar.Visible = False
  ActiveControl = TODOS
  Caption = 'Lista de Produtos x Fam'#237'lia'
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = True
  Position = poMainFormCenter
  Visible = True
  WindowState = wsMaximized
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object FooterPanel: TPanel
    Left = 0
    Top = 476
    Width = 766
    Height = 34
    Align = alBottom
    BevelOuter = bvLowered
    Color = 13434879
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Default'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object A: TButton
      Left = 4
      Top = 6
      Width = 17
      Height = 23
      Caption = '&A'
      TabOrder = 0
      OnClick = AClick
    end
    object B: TButton
      Left = 23
      Top = 6
      Width = 17
      Height = 23
      Caption = '&B'
      TabOrder = 1
      OnClick = BClick
    end
    object C: TButton
      Left = 42
      Top = 6
      Width = 17
      Height = 23
      Caption = '&C'
      TabOrder = 2
      OnClick = CClick
    end
    object D: TButton
      Left = 61
      Top = 6
      Width = 17
      Height = 23
      Caption = '&D'
      TabOrder = 3
      OnClick = DClick
    end
    object E: TButton
      Left = 81
      Top = 6
      Width = 17
      Height = 23
      Caption = '&E'
      TabOrder = 4
      OnClick = EClick
    end
    object F: TButton
      Left = 100
      Top = 6
      Width = 17
      Height = 23
      Caption = '&F'
      TabOrder = 5
      OnClick = FClick
    end
    object G: TButton
      Left = 119
      Top = 6
      Width = 17
      Height = 23
      Caption = '&G'
      TabOrder = 6
      OnClick = GClick
    end
    object H: TButton
      Left = 139
      Top = 6
      Width = 17
      Height = 23
      Caption = '&H'
      TabOrder = 7
      OnClick = HClick
    end
    object I: TButton
      Left = 158
      Top = 6
      Width = 17
      Height = 23
      Caption = '&I'
      TabOrder = 8
      OnClick = IClick
    end
    object J: TButton
      Left = 177
      Top = 6
      Width = 17
      Height = 23
      Caption = '&J'
      TabOrder = 9
      OnClick = JClick
    end
    object K: TButton
      Left = 196
      Top = 6
      Width = 17
      Height = 23
      Caption = '&K'
      TabOrder = 10
      OnClick = KClick
    end
    object L: TButton
      Left = 216
      Top = 6
      Width = 17
      Height = 23
      Caption = '&L'
      TabOrder = 11
      OnClick = LClick
    end
    object M: TButton
      Left = 235
      Top = 6
      Width = 20
      Height = 23
      Caption = '&M'
      TabOrder = 12
      OnClick = MClick
    end
    object N: TButton
      Left = 257
      Top = 6
      Width = 17
      Height = 23
      Caption = '&N'
      TabOrder = 13
      OnClick = NClick
    end
    object O: TButton
      Left = 276
      Top = 6
      Width = 17
      Height = 23
      Caption = '&O'
      TabOrder = 14
      OnClick = OClick
    end
    object P: TButton
      Left = 295
      Top = 6
      Width = 17
      Height = 23
      Caption = '&P'
      TabOrder = 15
      OnClick = PClick
    end
    object Q: TButton
      Left = 315
      Top = 6
      Width = 17
      Height = 23
      Caption = '&Q'
      TabOrder = 16
      OnClick = QClick
    end
    object R: TButton
      Left = 334
      Top = 6
      Width = 17
      Height = 23
      Caption = '&R'
      TabOrder = 17
      OnClick = RClick
    end
    object T: TButton
      Left = 372
      Top = 6
      Width = 17
      Height = 23
      Caption = '&T'
      TabOrder = 19
      OnClick = TClick
    end
    object S: TButton
      Left = 353
      Top = 6
      Width = 17
      Height = 23
      Caption = '&S'
      TabOrder = 18
      OnClick = SClick
    end
    object U: TButton
      Left = 392
      Top = 6
      Width = 17
      Height = 23
      Caption = '&U'
      TabOrder = 20
      OnClick = UClick
    end
    object V: TButton
      Left = 411
      Top = 6
      Width = 17
      Height = 23
      Caption = '&V'
      TabOrder = 21
      OnClick = VClick
    end
    object W: TButton
      Left = 430
      Top = 6
      Width = 20
      Height = 23
      Caption = '&W'
      TabOrder = 22
      OnClick = WClick
    end
    object X: TButton
      Left = 453
      Top = 6
      Width = 17
      Height = 23
      Caption = '&X'
      TabOrder = 23
      OnClick = XClick
    end
    object Y: TButton
      Left = 472
      Top = 6
      Width = 17
      Height = 23
      Caption = '&Y'
      TabOrder = 24
      OnClick = YClick
    end
    object Z: TButton
      Left = 491
      Top = 6
      Width = 17
      Height = 23
      Caption = '&Z'
      TabOrder = 25
      OnClick = ZClick
    end
    object TODOS: TButton
      Left = 510
      Top = 6
      Width = 53
      Height = 23
      Caption = 'TODOS'
      Default = True
      TabOrder = 26
      OnClick = TODOSClick
    end
    object BtRelat: TResBitBtn
      Left = 574
      Top = 6
      Width = 23
      Height = 23
      TabOrder = 27
      OnClick = BtRelatClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'RELATORIO'
      GlyphResID = 0
    end
  end
  object grdCnsProduto: TDBGrid
    Left = 0
    Top = 0
    Width = 766
    Height = 476
    Align = alClient
    DataSource = DsCnsProduto
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ParentColor = True
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnDrawColumnCell = grdCnsProdutoDrawColumnCell
    Columns = <
      item
        Expanded = False
        FieldName = 'cod_familia'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'den_familia'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cod_produto'
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'den_produto'
        Width = 405
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'preco_custo'
        Title.Alignment = taCenter
        Width = 80
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'qtd_estoque'
        Title.Alignment = taCenter
        Width = 80
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'ies_ativo'
        Title.Alignment = taCenter
        Visible = True
      end>
  end
  object TbCnsProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT p.cod_familia, f.den_familia, '
      '       p.cod_produto, p.den_produto, p.preco_custo,'
      '       p.qtd_estoque, p.ies_ativo'
      '  FROM tbl_produto p,'
      '       tbl_familia f'
      ' WHERE p.cod_familia = f.cod_familia'
      ' ORDER BY p.cod_familia,p.cod_produto')
    Params = <>
    Left = 528
    Top = 104
    object TbCnsProdutocod_familia: TIntegerField
      DisplayLabel = 'Fam'#237'lia'
      FieldName = 'cod_familia'
    end
    object TbCnsProdutoden_familia: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_familia'
      Size = 30
    end
    object TbCnsProdutocod_produto: TStringField
      DisplayLabel = 'Produto'
      FieldName = 'cod_produto'
      Size = 15
    end
    object TbCnsProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      Size = 75
    end
    object TbCnsProdutopreco_custo: TFloatField
      DisplayLabel = 'Pre'#231'o Custo'
      FieldName = 'preco_custo'
      currency = True
      Precision = 13
    end
    object TbCnsProdutoqtd_estoque: TFloatField
      DisplayLabel = 'Qtd Estoque'
      FieldName = 'qtd_estoque'
      DisplayFormat = '#0.000'
      Precision = 13
    end
    object TbCnsProdutoies_ativo: TStringField
      DisplayLabel = 'Ativo?'
      FieldName = 'ies_ativo'
      FixedChar = True
      Size = 1
    end
  end
  object DsCnsProduto: TDataSource
    AutoEdit = False
    DataSet = TbCnsProduto
    Left = 560
    Top = 104
  end
end
