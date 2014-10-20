inherited Fin2001: TFin2001
  Caption = 'Movimenta'#231#245'es Caixa'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Movimenta'#231#245'es Caixa'
  end
  inherited BodyPanel: TPanel
    object gbParam: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 43
      Align = alTop
      Caption = 'Par'#226'metros'
      TabOrder = 0
      object Label7: TLabel
        Left = 182
        Top = 17
        Width = 56
        Height = 13
        Cursor = crArrow
        Caption = 'Data &Inicial:'
        DragCursor = crDefault
        FocusControl = data_ini
        Transparent = True
      end
      object Label12: TLabel
        Left = 345
        Top = 17
        Width = 51
        Height = 13
        Cursor = crArrow
        Caption = 'Data &Final:'
        DragCursor = crDefault
        FocusControl = data_fim
        Transparent = True
      end
      object Label8: TLabel
        Left = 8
        Top = 17
        Width = 41
        Height = 13
        Caption = '&Per'#237'odo:'
      end
      object data_ini: TMaskEdit
        Left = 242
        Top = 15
        Width = 88
        Height = 21
        EditMask = '90/90/0099;1;_'
        MaxLength = 10
        TabOrder = 1
        Text = '  /  /    '
      end
      object btCalendar01: TCustomImgButton
        Left = 312
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 2
        TabStop = False
        OnClick = btCalendar01Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object data_fim: TMaskEdit
        Left = 400
        Top = 15
        Width = 88
        Height = 21
        EditMask = '90/90/0099;1;_'
        MaxLength = 10
        TabOrder = 3
        Text = '  /  /    '
      end
      object btCalendar02: TCustomImgButton
        Left = 470
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 4
        TabStop = False
        OnClick = btCalendar02Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object cbPeriodo: TComboBox
        Left = 54
        Top = 15
        Width = 115
        Height = 21
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'Dia Atual'
        OnChange = cbPeriodoChange
        Items.Strings = (
          'Dia Atual'
          'Semana Atual'
          'M'#234's Atual'
          'Informado')
      end
      object btAtualiza: TResBitBtn
        Left = 504
        Top = 13
        Width = 81
        Height = 24
        Caption = '&Atualizar'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -9
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = btAtualizaClick
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
    end
    object GridPanel: TPanel
      Left = 0
      Top = 43
      Width = 758
      Height = 372
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 1
      OnResize = GridPanelResize
      object SplitterBody: TSplitter
        Left = 0
        Top = 203
        Width = 758
        Height = 3
        Cursor = crVSplit
        Align = alBottom
        MinSize = 1
        OnMoved = SplitterBodyMoved
      end
      object gbEntrada: TGroupBox
        Left = 0
        Top = 0
        Width = 758
        Height = 203
        Align = alClient
        Caption = 'Entradas'
        TabOrder = 0
        object Label1: TLabel
          Left = 2
          Top = 195
          Width = 754
          Height = 6
          Align = alBottom
          AutoSize = False
        end
        object Label2: TLabel
          Left = 750
          Top = 15
          Width = 6
          Height = 180
          Align = alRight
          AutoSize = False
        end
        object Label3: TLabel
          Left = 2
          Top = 15
          Width = 6
          Height = 180
          Align = alLeft
          AutoSize = False
        end
        object DBGrid1: TDBGrid
          Left = 8
          Top = 15
          Width = 742
          Height = 180
          Align = alClient
          DataSource = DsEntrada
          PopupMenu = PopupMenu1
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'cod_lancamento'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'cod_documento'
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_cliente'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'num_documento'
              Width = 140
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'seq_documento'
              Title.Alignment = taCenter
              Width = 50
              Visible = True
            end
            item
              Alignment = taCenter
              Expanded = False
              FieldName = 'data_lancamento'
              Title.Alignment = taCenter
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_lancamento'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_centro_custo'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end
            item
              Alignment = taRightJustify
              Expanded = False
              FieldName = 'cod_plano_conta'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end>
        end
        object btAcima: TCustomImgButton
          Left = 323
          Top = 166
          Width = 37
          Height = 5
          TabOrder = 1
          Visible = False
          OnClick = btAcimaClick
          Picture.Data = {
            6A020000424D6A02000000000000760000002800000025000000190000000100
            040000000000F4010000C21E0000C21E0000100000000000000040404000FE00
            0000FF000000FFFF40000000FF00FF00FF0000FFFF0080808000FF808000C0C0
            C000000000000000000000000000000000000000000000000000522222222222
            2222222222222222222222225000552888888888888844444888888888888825
            5000555288888888888884448888888888888255500055552888888888888848
            8888888888882555500055555222222222222222222222222222555550005222
            2222222222222222222222222222222250005528888888888888666668888888
            8888882550005552888888888888866688888888888882555000555528888888
            8888886888888888888825555000555552222222222222222222222222225555
            5000522222222222222222222222222222222222500055288888888888886666
            6888888888888825500055528888888888888666888888888888825550005555
            2888888888888868888888888888255550005555522222222222222222222222
            2222555550005777777777777777777777777777777777775000557999999999
            9999000009999999999999755000555799999999999990009999999999999755
            5000555579999999999999099999999999997555500055555777777777777777
            7777777777775555500052222222222222222222222222222222222250005528
            8888888888883333388888888888882550005552888888888888833388888888
            8888825550005555288888888888883888888888888825555000555552222222
            2222222222222222222255555000}
          NumGlyphs = 5
        end
      end
      object gbSaida: TGroupBox
        Left = 0
        Top = 206
        Width = 758
        Height = 166
        Align = alBottom
        Caption = 'Sa'#237'das'
        TabOrder = 1
        object Label4: TLabel
          Left = 2
          Top = 15
          Width = 6
          Height = 143
          Align = alLeft
          AutoSize = False
        end
        object Label5: TLabel
          Left = 750
          Top = 15
          Width = 6
          Height = 143
          Align = alRight
          AutoSize = False
        end
        object Label6: TLabel
          Left = 2
          Top = 158
          Width = 754
          Height = 6
          Align = alBottom
          AutoSize = False
        end
        object DBGrid2: TDBGrid
          Left = 8
          Top = 15
          Width = 742
          Height = 143
          Align = alClient
          DataSource = DsSaida
          PopupMenu = PopupMenu2
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          Columns = <
            item
              Expanded = False
              FieldName = 'cod_lancamento'
              Visible = False
            end
            item
              Expanded = False
              FieldName = 'cod_documento'
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_fornecedor'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'num_documento'
              Width = 140
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'seq_documento'
              Title.Alignment = taCenter
              Width = 50
              Visible = True
            end
            item
              Alignment = taCenter
              Expanded = False
              FieldName = 'data_lancamento'
              Title.Alignment = taCenter
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_lancamento'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_centro_custo'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end
            item
              Alignment = taRightJustify
              Expanded = False
              FieldName = 'cod_plano_conta'
              Title.Alignment = taCenter
              Width = 100
              Visible = True
            end>
        end
        object btAbaixo: TCustomImgButton
          Left = 324
          Top = 6
          Width = 37
          Height = 5
          TabOrder = 1
          Visible = False
          OnClick = btAbaixoClick
          Picture.Data = {
            6A020000424D6A02000000000000760000002800000025000000190000000100
            040000000000F4010000C21E0000C21E0000100000000000000040404000FE00
            0000FF000000FFFF40000000FF00FF00FF0000FFFF0080808000FF808000C0C0
            C000000000000000000000000000000000000000000000000000555552222222
            2222222222222222222255555000555528888888888888488888888888882555
            5000555288888888888884448888888888888255500055288888888888884444
            4888888888888825500052222222222222222222222222222222222250005555
            5222222222222222222222222222555550005555288888888888886888888888
            8888255550005552888888888888866688888888888882555000552888888888
            8888666668888888888888255000522222222222222222222222222222222222
            5000555552222222222222222222222222225555500055552888888888888868
            8888888888882555500055528888888888888666888888888888825550005528
            8888888888886666688888888888882550005222222222222222222222222222
            2222222250005555577777777777777777777777777755555000555579999999
            9999990999999999999975555000555799999999999990009999999999999755
            5000557999999999999900000999999999999975500057777777777777777777
            7777777777777777500055555222222222222222222222222222555550005555
            2888888888888838888888888888255550005552888888888888833388888888
            8888825550005528888888888888333338888888888888255000522222222222
            2222222222222222222222225000}
          NumGlyphs = 5
        end
      end
    end
    object FooterPanel: TGroupBox
      Left = 0
      Top = 415
      Width = 758
      Height = 50
      Align = alBottom
      Caption = 'Totais'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      object Label9: TLabel
        Left = 6
        Top = 15
        Width = 70
        Height = 24
        Caption = 'Entrada:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label10: TLabel
        Left = 262
        Top = 15
        Width = 52
        Height = 24
        Caption = 'Sa'#237'da:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 500
        Top = 15
        Width = 85
        Height = 24
        Caption = 'Diferen'#231'a:'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object edtTotalSaida: TAlignEdit
        Left = 318
        Top = 12
        Width = 162
        Height = 32
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        Text = 'R$ 00.000.000,00'
        Alignment = taRightJustify
      end
      object edtTotalEntrada: TAlignEdit
        Left = 80
        Top = 12
        Width = 162
        Height = 32
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Text = 'R$ 00.000.000,00'
        Alignment = taRightJustify
      end
      object edtDiferenca: TAlignEdit
        Left = 590
        Top = 12
        Width = 162
        Height = 32
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -19
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        Text = 'R$ 00.000.000,00'
        Alignment = taRightJustify
      end
    end
  end
  object QyEntrada: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cx.cod_lancamento, cx.cod_documento, cr.cod_cliente, '
      
        '       cr.tipo_registro, cr.num_documento, cx.seq_documento, cx.' +
        'data_lancamento, '
      
        '       cx.valor_lancamento, cx.cod_centro_custo, cx.cod_plano_co' +
        'nta'
      '  FROM tbl_lancamento_caixa cx,'
      '       tbl_conta_receber cr'
      ' WHERE cx.tipo_lancamento = '#39'E'#39
      '   AND cx.data_lancamento >= :data_ini'
      '   AND cx.data_lancamento <= :data_fim'
      '   AND cx.cod_documento = cr.cod_conta_receber'
      '   AND cx.tipo_documento = cr.tipo_registro '
      ' ORDER BY data_lancamento')
    Params = <
      item
        DataType = ftDateTime
        Name = 'data_ini'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_fim'
        ParamType = ptUnknown
      end>
    Left = 426
    Top = 168
    ParamData = <
      item
        DataType = ftDateTime
        Name = 'data_ini'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_fim'
        ParamType = ptUnknown
      end>
    object QyEntradacod_lancamento: TIntegerField
      FieldName = 'cod_lancamento'
      Required = True
      Visible = False
    end
    object QyEntradacod_documento: TIntegerField
      DisplayLabel = 'Conta Receber'
      FieldName = 'cod_documento'
      Required = True
    end
    object QyEntradacod_cliente: TStringField
      DisplayLabel = 'Cliente'
      FieldName = 'cod_cliente'
      Required = True
      Size = 15
    end
    object QyEntradanum_documento: TStringField
      DisplayLabel = 'Documento'
      FieldName = 'num_documento'
      Size = 25
    end
    object QyEntradaseq_documento: TIntegerField
      DisplayLabel = 'Seq'
      FieldName = 'seq_documento'
      Required = True
    end
    object QyEntradadata_lancamento: TDateTimeField
      DisplayLabel = 'Data Entrada'
      FieldName = 'data_lancamento'
      Required = True
      DisplayFormat = 'dd/mm/yyyy hh:mm:ss'
    end
    object QyEntradavalor_lancamento: TFloatField
      DisplayLabel = 'Valor'
      FieldName = 'valor_lancamento'
      Required = True
      currency = True
    end
    object QyEntradacod_centro_custo: TStringField
      DisplayLabel = 'Centro Custo'
      FieldName = 'cod_centro_custo'
      Size = 15
    end
    object QyEntradacod_plano_conta: TStringField
      DisplayLabel = 'Conta Cont'#225'bil'
      FieldName = 'cod_plano_conta'
      Size = 18
    end
    object QyEntradatipo_registro: TStringField
      FieldName = 'tipo_registro'
      Required = True
      Size = 2
    end
  end
  object DsEntrada: TDataSource
    AutoEdit = False
    DataSet = QyEntrada
    Left = 462
    Top = 168
  end
  object QySaida: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cx.cod_lancamento, cx.cod_documento, cp.cod_fornecedor, '
      
        '       cp.tipo_registro, cp.num_documento, cx.seq_documento, cx.' +
        'data_lancamento, '
      
        '       cx.valor_lancamento, cx.cod_centro_custo, cx.cod_plano_co' +
        'nta'
      '  FROM tbl_lancamento_caixa cx,'
      '       tbl_conta_pagar cp'
      ' WHERE cx.tipo_lancamento = '#39'S'#39
      '   AND cx.data_lancamento >= :data_ini'
      '   AND cx.data_lancamento <= :data_fim'
      '   AND cx.cod_documento = cp.cod_conta_pagar'
      '   AND cx.tipo_documento = cp.tipo_registro '
      ' ORDER BY cx.data_lancamento')
    Params = <
      item
        DataType = ftDateTime
        Name = 'data_ini'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_fim'
        ParamType = ptUnknown
      end>
    Left = 444
    Top = 348
    ParamData = <
      item
        DataType = ftDateTime
        Name = 'data_ini'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_fim'
        ParamType = ptUnknown
      end>
    object LargeintField1: TIntegerField
      FieldName = 'cod_lancamento'
      Required = True
      Visible = False
    end
    object LargeintField2: TIntegerField
      DisplayLabel = 'Conta Pagar'
      FieldName = 'cod_documento'
      Required = True
    end
    object StringField1: TStringField
      DisplayLabel = 'Fornecedor'
      FieldName = 'cod_fornecedor'
      Required = True
      Size = 15
    end
    object StringField2: TStringField
      DisplayLabel = 'Documento'
      FieldName = 'num_documento'
      Size = 25
    end
    object IntegerField1: TIntegerField
      DisplayLabel = 'Seq'
      FieldName = 'seq_documento'
      Required = True
    end
    object DateTimeField1: TDateTimeField
      DisplayLabel = 'Data Sa'#237'da'
      FieldName = 'data_lancamento'
      Required = True
      DisplayFormat = 'dd/mm/yyyy hh:mm:ss'
    end
    object FloatField1: TFloatField
      DisplayLabel = 'Valor'
      FieldName = 'valor_lancamento'
      Required = True
      currency = True
    end
    object StringField3: TStringField
      DisplayLabel = 'Centro Custo'
      FieldName = 'cod_centro_custo'
      Size = 15
    end
    object StringField4: TStringField
      DisplayLabel = 'Conta Cont'#225'bil'
      FieldName = 'cod_plano_conta'
      Size = 18
    end
    object QySaidatipo_registro: TStringField
      FieldName = 'tipo_registro'
      Required = True
      Size = 2
    end
  end
  object DsSaida: TDataSource
    AutoEdit = False
    DataSet = QySaida
    Left = 480
    Top = 348
  end
  object PopupMenu1: TPopupMenu
    Images = ImageList1
    OnPopup = PopupMenu1Popup
    Left = 498
    Top = 168
    object IrParaContaReceber1: TMenuItem
      Caption = 'Visualizar Conta Receber'
      ImageIndex = 1
      OnClick = IrParaContaReceber1Click
    end
    object VisualizarPedidoVenda1: TMenuItem
      Caption = 'Visualizar Pedido Venda'
      ImageIndex = 1
      OnClick = VisualizarPedidoVenda1Click
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object IncluirContaReceber1: TMenuItem
      Caption = 'Incluir Conta Receber'
      ImageIndex = 0
      OnClick = IncluirContaReceber1Click
    end
    object IncluirPedidoVenda1: TMenuItem
      Caption = 'Incluir Pedido Venda'
      ImageIndex = 0
      OnClick = IncluirPedidoVenda1Click
    end
  end
  object PopupMenu2: TPopupMenu
    Images = ImageList1
    OnPopup = PopupMenu2Popup
    Left = 516
    Top = 348
    object N11: TMenuItem
      Caption = 'Visualizar Conta Pagar'
      ImageIndex = 1
      OnClick = N11Click
    end
    object N21: TMenuItem
      Caption = 'Visualizar Pedido Compra'
      ImageIndex = 1
      OnClick = N21Click
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object N31: TMenuItem
      Caption = 'Incluir Conta Pagar'
      ImageIndex = 0
      OnClick = N31Click
    end
    object N41: TMenuItem
      Caption = 'Incluir Pedido Compra'
      ImageIndex = 0
      OnClick = N41Click
    end
  end
  object ImageList1: TImageList
    Left = 594
    Top = 12
    Bitmap = {
      494C010102000400040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000001000000001002000000000000010
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6
      C600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF000000000000000000FFFFFF00FFFFFF00FFFFFF00C6C6
      C600000000000000000000000000000000000000000000000000000000000000
      0000848484000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C60000BDBD000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000BDBD0000FFFF00FFFFFF0000BD
      BD00000000000000000000000000000000000000000000000000000000008484
      8400FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF0000FFFF0000848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000BDBD0000FFFF00FFFF
      FF0000BDBD00848484000000000000000000000000008484840000000000FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF0000FFFFFF000000
      0000848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C60000BDBD0000FF
      FF0000BDBD000000000000000000000000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF0000FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF0000BD
      BD00000000000000000000000000BD0000000000000000000000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6
      C6000000000000000000FF000000BD0000000000000000000000FFFFFF00FFFF
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400C6C6C600C6C6C600C6C6
      C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6C600C6C6
      C60000000000BD000000FFFFFF00FF0000000000000000000000FFFFFF00FFFF
      0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFF
      FF00000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6
      C60000000000BD000000FF000000FFFFFF00000000008484840000000000FFFF
      0000FFFF0000FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF000000
      0000848484000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00C6C6
      C6000000000000000000BD000000FF0000000000000000000000000000008484
      8400FFFF0000FFFF0000FFFF0000FFFFFF00FFFFFF00FFFFFF00848484000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000084848400FFFFFF0000000000FFFF
      FF0000000000FFFFFF0000000000FFFFFF0000000000FFFFFF0000000000FFFF
      FF00000000000000000000000000BD0000000000000000000000000000000000
      000000000000FFFFFF00FFFFFF00FFFFFF00FFFFFF0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF008484
      8400FFFFFF0084848400FFFFFF0084848400FFFFFF0084848400FFFFFF000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000848484000000000000000000000000000000000084848400000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000100000000100010000000000800000000000000000000000
      000000000000000000000000FFFFFF00800FFFFC000000000007FFF800000000
      0007FFF1000000000007F023000000000007E007000000000003C00F00000000
      0001800700000000000080070000000000008007000000000000800700000000
      000080070000000000008007000000000004C00F000000000006E01F00000000
      800FF03F00000000D55FFFFF0000000000000000000000000000000000000000
      000000000000}
  end
end
