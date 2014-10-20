inherited Vdp2022: TVdp2022
  Caption = 'Comiss'#227'o Representantes'
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
    Caption = 'Comiss'#227'o Representantes'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    TabOrder = 2
    object Space01: TLabel
      Left = 0
      Top = 130
      Width = 758
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object gbFiltros: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 130
      Align = alTop
      Caption = 'Filtros'
      TabOrder = 0
      object Label1: TLabel
        Left = 45
        Top = 42
        Width = 35
        Height = 13
        Caption = '&Cliente:'
        FocusControl = cod_cliente
      end
      object Label2: TLabel
        Left = 9
        Top = 18
        Width = 71
        Height = 13
        Caption = '&Data Cadastro:'
        FocusControl = data_ini
      end
      object Label12: TLabel
        Left = 187
        Top = 18
        Width = 18
        Height = 13
        Cursor = crArrow
        Caption = 'at'#233':'
        DragCursor = crDefault
        FocusControl = data_fim
        Transparent = True
      end
      object Label7: TLabel
        Left = 7
        Top = 66
        Width = 73
        Height = 13
        Caption = '&Representante:'
        FocusControl = cod_representante
      end
      object data_ini: TMaskEdit
        Left = 85
        Top = 15
        Width = 85
        Height = 21
        EditMask = '99/99/9999;0;_'
        MaxLength = 10
        TabOrder = 0
        OnExit = data_iniExit
      end
      object btCalendar01: TCustomImgButton
        Left = 152
        Top = 18
        Width = 16
        Height = 16
        Hint = 'Abre o calend'#225'rio para a pesquisa da data.'
        TabOrder = 1
        TabStop = False
        OnClick = btCalendar01Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object data_fim: TMaskEdit
        Left = 208
        Top = 15
        Width = 85
        Height = 21
        EditMask = '99/99/9999;0;_'
        MaxLength = 10
        TabOrder = 2
        OnExit = data_fimExit
      end
      object btCalendar02: TCustomImgButton
        Left = 275
        Top = 18
        Width = 16
        Height = 16
        Hint = 'Abre o calend'#225'rio para a pesquisa da data.'
        TabOrder = 3
        TabStop = False
        OnClick = btCalendar02Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object cod_cliente: TEdit
        Left = 85
        Top = 39
        Width = 110
        Height = 21
        TabOrder = 4
        OnExit = cod_clienteExit
      end
      object btPesqCliente: TResBitBtn
        Left = 200
        Top = 38
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de clientes.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        TabStop = False
        OnClick = btPesqClienteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_cliente: TEdit
        Left = 227
        Top = 39
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 6
      end
      object cod_representante: TEdit
        Left = 85
        Top = 63
        Width = 110
        Height = 21
        TabOrder = 7
        OnExit = cod_representanteExit
      end
      object btPesqRepresentante: TResBitBtn
        Left = 200
        Top = 62
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de representantes.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
        TabStop = False
        OnClick = btPesqRepresentanteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_representante: TEdit
        Left = 227
        Top = 63
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 9
      end
      object valor_base_calculo: TRadioGroup
        Left = 8
        Top = 86
        Width = 301
        Height = 38
        Caption = 'Valor Base C'#225'lculo'
        Columns = 2
        ItemIndex = 0
        Items.Strings = (
          'Valor faturado pedido'
          'Valor recebido pedido')
        TabOrder = 10
      end
      object btAtualiza: TResBitBtn
        Left = 327
        Top = 99
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
        TabOrder = 11
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
    end
    object grdRepresentantes: TDBGrid
      Left = 0
      Top = 136
      Width = 758
      Height = 281
      Align = alClient
      DataSource = DsComissao
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgCancelOnExit]
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnKeyDown = grdRepresentantesKeyDown
      Columns = <
        item
          Expanded = False
          FieldName = 'cod_representante'
          ReadOnly = True
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'den_representante'
          ReadOnly = True
          Width = 270
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cod_pedido_venda'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'seq_parcela'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 60
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_calculo'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'perc_comissao'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 70
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_comissao'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'mes_comissao'
          ReadOnly = True
          Title.Alignment = taCenter
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'ano_comissao'
          ReadOnly = True
          Title.Alignment = taCenter
          Visible = True
        end>
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 417
    TabOrder = 3
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 417
    TabOrder = 4
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
      OnClick = btExitClick
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
  object ActionList1: TActionList
    Left = 480
    Top = 60
    object execInformar: TAction
      Hint = 
        'Informa os filtros para o c'#225'lculo|das comiss'#245'es dos representant' +
        'es.'
      ShortCut = 16457
      OnExecute = execInformarExecute
    end
    object execProcessar: TAction
      Hint = 
        'Processa a gera'#231#227'o das comiss'#245'es dos|representantes com base nos' +
        ' dados informados.'
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
      Hint = 'Carrega a lista de pedidos pendentes de c'#225'lculo de comiss'#227'o'
      ShortCut = 16469
      OnExecute = execAtualizarExecute
    end
  end
  object DsComissao: TDataSource
    DataSet = CnsComissao
    Left = 438
    Top = 312
  end
  object CnsComissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'cod_representante;cod_pedido_venda;seq_parcela'
    UpdateObject = AtuComissao
    CachedUpdates = True
    BeforeInsert = CnsComissaoBeforeInsert
    SQL.Strings = (
      
        'SELECT cod_representante, '#39'#####################################' +
        '#############'#39' den_representante, cod_pedido_venda, seq_parcela,'
      
        '       valor_calculo, perc_comissao, valor_comissao, valor_base_' +
        'calculo,'
      '       mes_comissao, ano_comissao, data_calculo'
      '  FROM tbl_comissao_representante'
      ' WHERE 1 = 0')
    Params = <>
    IndexFieldNames = 'cod_representante Asc;cod_pedido_venda Asc;seq_parcela Asc'
    Left = 474
    Top = 312
    object CnsComissaocod_representante: TStringField
      DisplayLabel = 'Representante'
      FieldName = 'cod_representante'
      Size = 15
    end
    object CnsComissaoden_representante: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_representante'
      Size = 50
    end
    object CodPedidoVenda: TIntegerField
      DisplayLabel = 'Pedido Venda'
      FieldName = 'cod_pedido_venda'
      Required = True
    end
    object CnsComissaoseq_parcela: TIntegerField
      DisplayLabel = 'Parcela'
      FieldName = 'seq_parcela'
      Required = True
    end
    object CnsComissaovalor_calculo: TFloatField
      DisplayLabel = 'Valor C'#225'lculo'
      FieldName = 'valor_calculo'
      currency = True
    end
    object CnsComissaoperc_comissao: TFloatField
      DisplayLabel = '% Comiss'#227'o'
      FieldName = 'perc_comissao'
      DisplayFormat = '#0.00'
    end
    object CnsComissaovalor_comissao: TFloatField
      DisplayLabel = 'Valor Comiss'#227'o'
      FieldName = 'valor_comissao'
      currency = True
    end
    object CnsComissaovalor_base_calculo: TSmallintField
      FieldName = 'valor_base_calculo'
    end
    object CnsComissaomes_comissao: TSmallintField
      DisplayLabel = 'M'#234's'
      FieldName = 'mes_comissao'
    end
    object CnsComissaoano_comissao: TSmallintField
      DisplayLabel = 'Ano'
      FieldName = 'ano_comissao'
    end
    object CnsComissaodata_calculo: TDateTimeField
      FieldName = 'data_calculo'
    end
  end
  object AtuComissao: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_comissao_representante'
      ' WHERE cod_representante = :cod_representante'
      '   AND cod_pedido_venda = :cod_pedido_venda'
      '   AND seq_parcela = :seq_parcela')
    InsertSQL.Strings = (
      'INSERT INTO tbl_comissao_representante'
      
        '  (cod_representante, cod_pedido_venda, seq_parcela, valor_calcu' +
        'lo, '
      'perc_comissao, '
      
        '   valor_comissao, valor_base_calculo, mes_comissao, ano_comissa' +
        'o, '
      'data_calculo)'
      'VALUES'
      
        '  (:cod_representante, :cod_pedido_venda, :seq_parcela, :valor_c' +
        'alculo, '
      
        '   :perc_comissao, :valor_comissao, :valor_base_calculo, :mes_co' +
        'missao, '
      '   :ano_comissao, :data_calculo)')
    ModifySQL.Strings = (
      'UPDATE tbl_comissao_representante SET'
      '  valor_calculo = :valor_calculo,'
      '  perc_comissao = :perc_comissao,'
      '  valor_comissao = :valor_comissao,'
      '  valor_base_calculo = :valor_base_calculo,'
      '  mes_comissao = :mes_comissao,'
      '  ano_comissao = :ano_comissao,'
      '  data_calculo = :data_calculo'
      ' WHERE cod_representante = :cod_representante'
      '   AND cod_pedido_venda = :cod_pedido_venda'
      '   AND seq_parcela = :seq_parcela')
    UseSequenceFieldForRefreshSQL = False
    Left = 504
    Top = 312
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
      end
      item
        DataType = ftLargeint
        Name = 'cod_pedido_venda'
        ParamType = ptUnknown
      end
      item
        DataType = ftLargeint
        Name = 'seq_parcela'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_calculo'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'perc_comissao'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_comissao'
        ParamType = ptUnknown
      end
      item
        DataType = ftSmallint
        Name = 'valor_base_calculo'
        ParamType = ptUnknown
      end
      item
        DataType = ftSmallint
        Name = 'mes_comissao'
        ParamType = ptUnknown
      end
      item
        DataType = ftSmallint
        Name = 'ano_comissao'
        ParamType = ptUnknown
      end
      item
        DataType = ftSmallint
        Name = 'data_calculo'
        ParamType = ptUnknown
      end>
  end
end
