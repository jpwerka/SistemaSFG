inherited Sup1001: TSup1001
  Caption = 'Cadastro de Pedidos de Compra'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Pedidos de Compra'
  end
  inherited BodyPanel: TPanel
    object gbCadastro: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 9
        Top = 17
        Width = 36
        Height = 13
        Cursor = crArrow
        Caption = '&C'#243'digo:'
        DragCursor = crDefault
        FocusControl = cod_pedido_compra
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 139
        Top = 17
        Width = 26
        Height = 13
        Cursor = crArrow
        Caption = '&Data:'
        DragCursor = crDefault
        FocusControl = data_cadastro
        Transparent = True
        WordWrap = True
      end
      object Label12: TLabel
        Left = 271
        Top = 17
        Width = 66
        Height = 13
        Cursor = crArrow
        Caption = 'R&ecebimento:'
        DragCursor = crDefault
        FocusControl = data_recebimento
        Transparent = True
        WordWrap = True
      end
      object Label6: TLabel
        Left = 440
        Top = 17
        Width = 45
        Height = 13
        Caption = '&Situa'#231#227'o:'
        FocusControl = ies_situacao
      end
      object Label4: TLabel
        Left = 7
        Top = 41
        Width = 72
        Height = 13
        Alignment = taRightJustify
        Caption = 'Conta Cont'#225'&bil:'
        FocusControl = cod_plano_conta
        Transparent = True
      end
      object Label5: TLabel
        Left = 238
        Top = 41
        Width = 64
        Height = 13
        Alignment = taRightJustify
        Caption = 'Centro C&usto:'
        FocusControl = cod_centro_custo
        Transparent = True
      end
      object cod_pedido_compra: TDBEdit
        Left = 49
        Top = 15
        Width = 70
        Height = 21
        Color = clWhite
        DataField = 'cod_pedido_compra'
        DataSource = DsCadCompra
        TabOrder = 0
      end
      object data_cadastro: TDBEdit
        Left = 168
        Top = 15
        Width = 88
        Height = 21
        DataField = 'data_cadastro'
        DataSource = DsCadCompra
        TabOrder = 1
      end
      object btCalendar01: TCustomImgButton
        Left = 238
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
      object data_recebimento: TDBEdit
        Left = 341
        Top = 15
        Width = 88
        Height = 21
        DataField = 'data_recebimento'
        DataSource = DsCadCompra
        TabOrder = 3
      end
      object btCalendar02: TCustomImgButton
        Left = 411
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
      object ies_situacao: TDBDataComboBox
        Left = 488
        Top = 15
        Width = 104
        Height = 21
        AutoDropDown = True
        DataField = 'ies_situacao'
        DataSource = DsSitPedidoCompra
        ItemHeight = 13
        TabOrder = 5
      end
      object cod_plano_conta: TDBEdit
        Left = 83
        Top = 39
        Width = 104
        Height = 21
        DataField = 'cod_plano_conta'
        DataSource = DsCadCompra
        TabOrder = 6
      end
      object btPesqPlanoConta: TResBitBtn
        Left = 192
        Top = 38
        Width = 23
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        TabStop = False
        OnClick = btPesqPlanoContaClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_centro_custo: TDBEdit
        Left = 306
        Top = 39
        Width = 110
        Height = 21
        DataField = 'cod_centro_custo'
        DataSource = DsCadCompra
        TabOrder = 8
      end
      object btPesqCentroCusto: TResBitBtn
        Left = 421
        Top = 38
        Width = 23
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 9
        TabStop = False
        OnClick = btPesqCentroCustoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
    end
    object gbFornecedor: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 43
      Cursor = crArrow
      Align = alTop
      Caption = 'Fornecedor'
      TabOrder = 1
      object Label3: TLabel
        Left = 9
        Top = 17
        Width = 57
        Height = 13
        Alignment = taRightJustify
        Caption = '&Fornecedor:'
        FocusControl = cod_fornecedor
        Transparent = True
        WordWrap = True
      end
      object cod_fornecedor: TDBEdit
        Left = 70
        Top = 15
        Width = 110
        Height = 21
        DataField = 'cod_fornecedor'
        DataSource = DsCadCompra
        TabOrder = 0
      end
      object btPesqFornecedor: TResBitBtn
        Left = 186
        Top = 14
        Width = 24
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btPesqFornecedorClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_fornecedor: TEdit
        Left = 216
        Top = 15
        Width = 388
        Height = 21
        Color = clWhite
        ReadOnly = True
        TabOrder = 2
      end
    end
    object pgDetalhes: TPageControl
      Left = 0
      Top = 110
      Width = 758
      Height = 311
      ActivePage = tbItens
      Align = alClient
      MultiLine = True
      TabIndex = 0
      TabOrder = 2
      object tbItens: TTabSheet
        Caption = '&1 - Itens'
        object grdItens: TDBGrid
          Left = 0
          Top = 0
          Width = 750
          Height = 250
          Align = alClient
          DataSource = DsCadProduto
          Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
          PopupMenu = PopupMenu1
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          OnDrawColumnCell = grdItensDrawColumnCell
          OnEditButtonClick = grdItensEditButtonClick
          OnKeyDown = DbGridKeyDown
          Columns = <
            item
              ButtonStyle = cbsEllipsis
              Expanded = False
              FieldName = 'cod_produto'
              Width = 135
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'den_produto'
              ReadOnly = True
              Width = 240
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'qtd_produto'
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'preco_compra'
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'val_desconto'
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_total'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 95
              Visible = True
            end>
        end
        object Panel6: TPanel
          Left = 0
          Top = 250
          Width = 750
          Height = 33
          Align = alBottom
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 1
          object Label7: TLabel
            Left = 565
            Top = 8
            Width = 41
            Height = 16
            Caption = 'Total:'
            FocusControl = valor_total
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object btAddLinha: TResBitBtn
            Left = 5
            Top = 5
            Width = 108
            Height = 25
            Action = addLine
            Caption = '&Adicionar Linha'
            TabOrder = 0
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'ADICIONARM'
            GlyphResID = 0
          end
          object btDelLinha: TResBitBtn
            Left = 117
            Top = 5
            Width = 108
            Height = 25
            Action = delLine
            Caption = '&Remover Linha'
            TabOrder = 1
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'EXCLUIRM'
            GlyphResID = 0
          end
          object btAddItens: TResBitBtn
            Left = 228
            Top = 5
            Width = 109
            Height = 25
            Action = addItens
            Caption = 'Adicionar &Itens'
            TabOrder = 2
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'ADICIONARM'
            GlyphResID = 0
          end
          object valor_total: TDBEdit
            Left = 609
            Top = 5
            Width = 113
            Height = 24
            TabStop = False
            DataField = 'valor_total'
            DataSource = DsCadCompra
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 3
          end
        end
      end
      object tbObs: TTabSheet
        Caption = '&2 - Observa'#231#227'o'
        ImageIndex = 2
        object observacao: TDBMemo
          Left = 5
          Top = 5
          Width = 587
          Height = 128
          DataField = 'observacao'
          DataSource = DsCadCompra
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -12
          Font.Name = 'Courier New'
          Font.Style = []
          ParentFont = False
          ScrollBars = ssVertical
          TabOrder = 0
        end
      end
      object tbPgto: TTabSheet
        Caption = '&3 - Pagamento'
        ImageIndex = 2
        object pnParcela: TPanel
          Left = 0
          Top = 0
          Width = 750
          Height = 30
          Align = alTop
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 0
          object Label9: TLabel
            Left = 8
            Top = 7
            Width = 57
            Height = 13
            Caption = '&Pagamento:'
            FocusControl = cod_forma_pagto
          end
          object Label10: TLabel
            Left = 252
            Top = 7
            Width = 59
            Height = 13
            Caption = '&N'#186' Parcelas:'
            FocusControl = num_parcelas
          end
          object cod_forma_pagto: TDBDataComboBox
            Left = 69
            Top = 5
            Width = 165
            Height = 21
            AutoDropDown = True
            DataField = 'cod_forma_pagto'
            DataSource = DsCadCompra
            ItemHeight = 13
            TabOrder = 0
            OnChange = cod_forma_pagtoChange
            LookUpField = 'cod_forma_pagto'
            ResultField = 'den_forma_pagto'
          end
          object num_parcelas: TEdit
            Left = 315
            Top = 5
            Width = 40
            Height = 21
            Enabled = False
            ReadOnly = True
            TabOrder = 1
            Text = '1'
          end
          object UpDwNumParcelas: TUpDown
            Left = 355
            Top = 5
            Width = 16
            Height = 21
            Associate = num_parcelas
            Min = 1
            Position = 1
            TabOrder = 2
            Thousands = False
            Wrap = False
            OnClick = UpDwNumParcelasClick
          end
        end
        object grdPagtos: TDBGrid
          Left = 0
          Top = 30
          Width = 750
          Height = 220
          Align = alClient
          DataSource = DsCompraPagto
          Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          OnColEnter = grdPagtosColEnter
          OnColExit = grdPagtosColExit
          OnDrawColumnCell = grdPagtosDrawColumnCell
          OnEditButtonClick = grdPagtosEditButtonClick
          OnKeyDown = DbGridKeyDown
          Columns = <
            item
              Expanded = False
              FieldName = 'seq_parcela'
              ReadOnly = True
              Title.Alignment = taCenter
              Title.Caption = 'Seq'
              Width = 35
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_parcela'
              Title.Alignment = taCenter
              Title.Caption = 'Valor'
              Width = 90
              Visible = True
            end
            item
              Alignment = taCenter
              ButtonStyle = cbsEllipsis
              Expanded = False
              FieldName = 'data_vencimento'
              Title.Alignment = taCenter
              Title.Caption = 'Vencimento'
              Width = 110
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'observacao'
              Title.Caption = 'Observa'#231#227'o'
              Width = 410
              Visible = True
            end
            item
              Alignment = taCenter
              Expanded = False
              FieldName = 'ies_pago'
              Title.Alignment = taCenter
              Title.Caption = 'Pago?'
              Width = 50
              Visible = True
            end>
        end
        object pnTotal: TPanel
          Left = 0
          Top = 250
          Width = 750
          Height = 33
          Align = alBottom
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 2
          object Label8: TLabel
            Left = 565
            Top = 8
            Width = 41
            Height = 16
            Caption = 'Total:'
            FocusControl = pagto_total
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object MsgDifTotalPagto: TLabel
            Left = 4
            Top = 2
            Width = 555
            Height = 28
            Align = alCustom
            Alignment = taCenter
            AutoSize = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -9
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object pagto_total: TDBEdit
            Left = 609
            Top = 5
            Width = 113
            Height = 24
            TabStop = False
            DataField = 'pagto_total'
            DataSource = DsCadCompra
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = []
            ParentFont = False
            ReadOnly = True
            TabOrder = 0
          end
        end
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btDelete: TResBitBtn
      Left = 462
    end
    inherited btExit: TResBitBtn
      Left = 650
    end
    inherited btajuda: TResBitBtn
      Left = 686
    end
    inherited MenuClicks: TPopupMenu
      object PercentualReajuste1: TMenuItem
        Action = execEnviaPedido
        Caption = 'Enviar por Email'
      end
      object PesquisaProdutoCliente2: TMenuItem
        Action = execRecebimento
        Caption = 'Informar Recebimento'
      end
      object FechamentoPedido1: TMenuItem
        Action = execFechamento
        Caption = 'Fechamento Pedido'
      end
      object VisualizarImpresso1: TMenuItem
        Action = execRelatorio
        Caption = 'Visualizar Impress'#227'o'
      end
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = NavegexecBtEditClickExecute
      end
      inherited execBtSaveClick: TAction
        OnExecute = NavegexecBtSaveClickExecute
      end
      inherited execBtCancelClick: TAction
        OnExecute = NavegexecBtCancelClickExecute
      end
      inherited execBtNewClick: TAction
        OnExecute = NavegexecBtNewClickExecute
      end
      inherited execBtCopyClick: TAction
        Visible = False
      end
      inherited execBtDeleteClick: TAction
        OnExecute = NavegexecBtDeleteClickExecute
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object btEnviarPedido: TResBitBtn
    Left = 500
    Top = 61
    Width = 32
    Height = 32
    Action = execEnviaPedido
    TabOrder = 5
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'EMAIL'
    GlyphResID = 0
  end
  object btRelatorio: TResBitBtn
    Left = 614
    Top = 61
    Width = 32
    Height = 32
    Action = execRelatorio
    TabOrder = 6
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'RELATORIO'
    GlyphResID = 0
  end
  object btRecebePedido: TResBitBtn
    Left = 538
    Top = 61
    Width = 32
    Height = 31
    Action = execRecebimento
    TabOrder = 7
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'CAMINHAO'
    GlyphResID = 0
  end
  object btFechamento: TResBitBtn
    Left = 576
    Top = 61
    Width = 32
    Height = 32
    Action = execFechamento
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'FECHANEGC'
    GlyphResID = 0
  end
  object DsCadCompra: TDataSource
    AutoEdit = False
    DataSet = QyCadCompra
    Left = 728
    Top = 8
  end
  object QyCadProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'seq_produto'
    AutoCalcFields = False
    OnCalcFields = QyCadProdutoCalcFields
    UpdateObject = AddItemVenda
    CachedUpdates = True
    BeforeInsert = QyDetalheBeforeInsert
    SQL.Strings = (
      'SELECT v.cod_pedido_compra, v.seq_produto, '
      '       v.cod_produto, p.den_produto,'
      
        '       v.qtd_produto, v.preco_compra, v.val_desconto, p.preco_cu' +
        'sto'
      '  FROM tbl_pedido_compra_item v,'
      '       tbl_produto p'
      ' WHERE v.cod_pedido_compra =:cod_pedido_compra'
      '   AND v.cod_produto = p.cod_produto'
      ' ORDER BY v.seq_produto')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
    DataSource = DsCadCompra
    IndexFieldNames = 'seq_produto Asc'
    Left = 438
    Top = 300
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
    object CodPedidoCompraItem: TIntegerField
      FieldName = 'cod_pedido_compra'
      Required = True
    end
    object QyCadProdutoseq_produto: TIntegerField
      FieldName = 'seq_produto'
      Required = True
    end
    object QyCadProdutocod_produto: TStringField
      DisplayLabel = 'Item'
      FieldName = 'cod_produto'
      OnValidate = CodProdutoValidate
      Size = 15
    end
    object QyCadProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      Size = 75
    end
    object QyCadProdutoqtd_produto: TFloatField
      DisplayLabel = 'Quantidade'
      FieldName = 'qtd_produto'
      OnSetText = QtdProdutoSetText
      DisplayFormat = '#0.000'
    end
    object QyCadProdutopreco_compra: TFloatField
      DisplayLabel = 'Valor Unit'#225'rio'
      FieldName = 'preco_compra'
      OnSetText = PrecoCompraSetText
      currency = True
    end
    object QyCadProdutoval_desconto: TFloatField
      DisplayLabel = 'Desconto'
      FieldName = 'val_desconto'
      OnSetText = ValDescontoSetText
      currency = True
    end
    object QyCadProdutovalor_total: TFloatField
      DisplayLabel = 'Valor Total'
      FieldKind = fkCalculated
      FieldName = 'valor_total'
      currency = True
      Calculated = True
    end
    object QyCadProdutopreco_custo: TFloatField
      FieldName = 'preco_custo'
      currency = True
    end
  end
  object QyCadPagto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'seq_parcela'
    UpdateObject = AddPagto
    CachedUpdates = True
    BeforeInsert = QyDetalheBeforeInsert
    SQL.Strings = (
      'SELECT cod_pedido_compra, seq_parcela, '
      '       valor_parcela, data_vencimento, observacao, ies_pago'
      '  FROM tbl_pedido_compra_pagto'
      ' WHERE cod_pedido_compra =:cod_pedido_compra'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
    DataSource = DsCadCompra
    IndexFieldNames = 'seq_parcela Asc'
    Left = 581
    Top = 300
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
    object CodPedidoCompraPagto: TIntegerField
      DisplayWidth = 10
      FieldName = 'cod_pedido_compra'
      ProviderFlags = [pfInWhere, pfInKey]
      Required = True
    end
    object QyCadPagtoseq_parcela: TIntegerField
      FieldName = 'seq_parcela'
      Required = True
    end
    object QyCadPagtovalor_parcela: TFloatField
      FieldName = 'valor_parcela'
      ProviderFlags = [pfInUpdate]
      OnSetText = ValorParcelaSetText
      currency = True
      Precision = 13
    end
    object QyCadPagtodata_vencimento: TDateTimeField
      FieldName = 'data_vencimento'
      ProviderFlags = [pfInUpdate]
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '90/90/0099;1;_'
    end
    object QyCadPagtoQyCadPagtoobservacao: TStringField
      FieldName = 'observacao'
      ProviderFlags = [pfInUpdate]
      Size = 100
    end
    object QyCadPagtoies_pago: TStringField
      DisplayLabel = 'Pago'
      FieldName = 'ies_pago'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
  end
  object AddItemVenda: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_pedido_compra_item'
      'WHERE cod_pedido_compra = :cod_pedido_compra '
      'AND seq_produto = :seq_produto')
    InsertSQL.Strings = (
      'INSERT INTO tbl_pedido_compra_item '
      '(cod_pedido_compra, seq_produto, cod_produto, qtd_produto, '
      'preco_compra,val_desconto) '
      'VALUES '
      '(:cod_pedido_compra, :seq_produto, :cod_produto, :qtd_produto, '
      ':preco_compra,:val_desconto)')
    ModifySQL.Strings = (
      'UPDATE tbl_pedido_compra_item SET'
      '  cod_produto = :cod_produto,'
      '  qtd_produto = :qtd_produto,'
      '  preco_compra = :preco_compra,'
      '  val_desconto = :val_desconto'
      'WHERE cod_pedido_compra = :cod_pedido_compra '
      'AND seq_produto = :seq_produto')
    UseSequenceFieldForRefreshSQL = False
    Left = 468
    Top = 300
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
        Value = '1.001'
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'qtd_produto'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'preco_compra'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'val_desconto'
        ParamType = ptUnknown
      end
      item
        DataType = ftInteger
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Size = 10
        Value = 1
      end
      item
        DataType = ftInteger
        Precision = 255
        Name = 'seq_produto'
        ParamType = ptUnknown
        Size = 255
        Value = 1
      end>
  end
  object AddPagto: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_pedido_compra_pagto'
      'WHERE cod_pedido_compra = :cod_pedido_compra'
      'AND seq_parcela = :seq_parcela')
    InsertSQL.Strings = (
      'INSERT INTO tbl_pedido_compra_pagto '
      '(cod_pedido_compra, seq_parcela, valor_parcela, '
      'data_vencimento,observacao,ies_pago) '
      'VALUES '
      
        '(:cod_pedido_compra, :seq_parcela, :valor_parcela, :data_vencime' +
        'nto, '
      ':observacao,'#39'N'#39')')
    ModifySQL.Strings = (
      'UPDATE tbl_pedido_compra_pagto SET'
      '  valor_parcela = :valor_parcela,'
      '  data_vencimento = :data_vencimento,'
      '  observacao = :observacao'
      'WHERE cod_pedido_compra = :cod_pedido_compra '
      'AND seq_parcela = :seq_parcela')
    UseSequenceFieldForRefreshSQL = False
    Left = 612
    Top = 300
    ParamData = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_parcela'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_vencimento'
        ParamType = ptUnknown
      end
      item
        DataType = ftString
        Name = 'observacao'
        ParamType = ptUnknown
        Size = 100
      end
      item
        DataType = ftLargeint
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end
      item
        DataType = ftLargeint
        Name = 'seq_parcela'
        ParamType = ptUnknown
      end>
  end
  object QyCadCompra: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    AfterOpen = QyCadCompraAfterOpen
    BeforeClose = QyCadCompraBeforeClose
    AfterScroll = QyCadCompraAfterScroll
    OnCalcFields = QyCadCompraCalcFields
    BeforePost = QyCadCompraBeforePost
    AfterPost = QyCadCompraAfterPost
    BeforeDelete = QyCadCompraBeforeDelete
    OnPostError = QyCadCompraPostError
    SQL.Strings = (
      'SELECT cod_pedido_compra, cod_fornecedor, data_cadastro,'
      
        '       data_recebimento, ies_situacao, cod_plano_conta, cod_cent' +
        'ro_custo,'
      '       cod_forma_pagto, num_parcelas, valor_total, observacao'
      '  FROM tbl_pedido_compra'
      ' ORDER BY cod_pedido_compra')
    Params = <>
    Left = 696
    Top = 8
  end
  object ActionList1: TActionList
    Left = 720
    Top = 66
    object execRecebimento: TAction
      Enabled = False
      Hint = 'Registra o recebimento do pedido de compra.'
      ShortCut = 16468
      OnExecute = execRecebimentoExecute
    end
    object execRelatorio: TAction
      Enabled = False
      Hint = 'Visualiza a impress'#227'o do pedido de compra.'
      ShortCut = 16460
      OnExecute = btRelatorioClick
    end
    object execEnviaPedido: TAction
      Enabled = False
      Hint = 'Envia o pedido de compra por email para o fornecedor.'
      ShortCut = 16461
      OnExecute = btEnviarPedidoClick
    end
    object execFechamento: TAction
      Enabled = False
      Hint = 
        'Fecha o pedido de compra efetuando a entrada|no estoque e a inte' +
        'gra'#231#227'o com o contas a pagar.'
      ShortCut = 16454
      OnExecute = execFechamentoExecute
    end
    object addLine: TAction
      Caption = '&Adicionar Linha'
      ShortCut = 32833
      OnExecute = addLineExecute
    end
    object delLine: TAction
      Caption = '&Remover Linha'
      ShortCut = 32850
      OnExecute = delLineExecute
    end
    object addItens: TAction
      Caption = 'Adicionar &Itens'
      Hint = 'Adicionar v'#225'rios itens por|meio de uma sele'#231#227'o em lista.'
      ShortCut = 32841
      OnExecute = addItensExecute
    end
  end
  object QySitPedidoCompra: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT ies_situacao'
      '  FROM tbl_pedido_compra'
      ' WHERE cod_pedido_compra =:cod_pedido_compra')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
    DataSource = DsCadCompra
    Left = 612
    Top = 114
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
      end>
  end
  object DsSitPedidoCompra: TDataSource
    AutoEdit = False
    DataSet = QySitPedidoCompra
    Left = 648
    Top = 114
  end
  object DsCadProduto: TDataSource
    AutoEdit = False
    DataSet = QyCadProduto
    Left = 498
    Top = 300
  end
  object DsCompraPagto: TDataSource
    AutoEdit = False
    DataSet = QyCadPagto
    Left = 642
    Top = 300
  end
  object PopupMenu1: TPopupMenu
    Left = 48
    Top = 300
    object AdicionarLinha1: TMenuItem
      Action = addLine
    end
    object RemoverLinha1: TMenuItem
      Action = delLine
    end
    object AdicionarItens1: TMenuItem
      Action = addItens
    end
  end
  object QyCnsProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT p.cod_produto, p.den_produto, p.cod_unid_medida, f.preco_' +
        'compra'
      '  FROM tbl_fornecedor_produto f,'
      '       tbl_produto p       '
      ' WHERE f.cod_fornecedor = :cod_fornecedor'
      '   AND f.cod_produto = :cod_produto '
      '   AND p.cod_produto = f.cod_produto'
      '   AND p.ies_ativo = '#39'S'#39)
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_fornecedor'
        ParamType = ptUnknown
        Size = 15
      end
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
      end>
    Left = 86
    Top = 301
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_fornecedor'
        ParamType = ptUnknown
        Size = 15
      end
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
      end>
  end
end
