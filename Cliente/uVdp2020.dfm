object Vdp2020: TVdp2020
  Left = 0
  Top = 0
  Width = 774
  Height = 544
  HorzScrollBar.Visible = False
  Caption = 'Telefones dos Clientes'
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
  OnShow = FormShow
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
  object GrdFoneCliente: TDBGrid
    Left = 0
    Top = 0
    Width = 766
    Height = 476
    Align = alClient
    DataSource = DsFoneCliente
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
    ReadOnly = True
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    Columns = <
      item
        Expanded = False
        FieldName = 'cod_cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Cliente'
        Width = 100
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'den_cliente'
        Title.Alignment = taCenter
        Title.Caption = 'Nome Completo'
        Width = 317
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'telefone'
        Title.Alignment = taCenter
        Title.Caption = 'Telefone'
        Width = 99
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'celular'
        Title.Alignment = taCenter
        Title.Caption = 'Celular'
        Width = 99
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'fax'
        Title.Alignment = taCenter
        Title.Caption = 'Fax'
        Width = 99
        Visible = True
      end>
  end
  object QyFoneCliente: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cliente, den_cliente, telefone, celular, fax'
      'FROM tbl_cliente'
      'ORDER BY den_cliente;')
    Params = <>
    Left = 120
    Top = 112
    object QyFoneClientecod_fornec: TStringField
      FieldName = 'cod_cliente'
      Size = 15
    end
    object QyFoneClienteden_fornec: TStringField
      FieldName = 'den_cliente'
      Size = 50
    end
    object QyFoneClientetelefone: TStringField
      FieldName = 'telefone'
      EditMask = '!\(999\) 0000-0000;0;_'
      Size = 15
    end
    object QyFoneClientecelular: TStringField
      FieldName = 'celular'
      EditMask = '!\(999\) 0000-0000;0;_'
      Size = 15
    end
    object QyFoneClientefax: TStringField
      FieldName = 'fax'
      EditMask = '!\(999\) 0000-0000;0;_'
      Size = 15
    end
  end
  object DsFoneCliente: TDataSource
    AutoEdit = False
    DataSet = QyFoneCliente
    Left = 152
    Top = 112
  end
end
