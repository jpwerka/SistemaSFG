inherited Fin1002: TFin1002
  Caption = 'Cadastro de Contas '#224' Pagar'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Contas '#224' Pagar'
  end
  inherited BodyPanel: TPanel
    object gpCadastro: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 36
        Height = 13
        Cursor = crArrow
        Caption = '&C'#243'digo:'
        DragCursor = crDefault
        FocusControl = cod_conta_pagar
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 132
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
        Left = 257
        Top = 17
        Width = 58
        Height = 13
        Cursor = crArrow
        Caption = 'D&ocumento:'
        DragCursor = crDefault
        FocusControl = num_documento
        Transparent = True
        WordWrap = True
      end
      object Label6: TLabel
        Left = 456
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
        Left = 241
        Top = 41
        Width = 64
        Height = 13
        Alignment = taRightJustify
        Caption = 'Centro C&usto:'
        FocusControl = cod_centro_custo
        Transparent = True
      end
      object Label7: TLabel
        Left = 477
        Top = 41
        Width = 24
        Height = 13
        Caption = '&Tipo:'
        FocusControl = tipo_registro
      end
      object cod_conta_pagar: TDBEdit
        Left = 48
        Top = 15
        Width = 69
        Height = 21
        Color = clWhite
        DataField = 'cod_conta_pagar'
        DataSource = DsContaPagar
        TabOrder = 0
      end
      object data_cadastro: TDBEdit
        Left = 162
        Top = 15
        Width = 87
        Height = 21
        DataField = 'data_cadastro'
        DataSource = DsContaPagar
        TabOrder = 1
      end
      object num_documento: TDBEdit
        Left = 319
        Top = 15
        Width = 120
        Height = 21
        DataField = 'num_documento'
        DataSource = DsContaPagar
        TabOrder = 3
      end
      object ies_situacao: TDBDataComboBox
        Left = 504
        Top = 15
        Width = 104
        Height = 21
        AutoDropDown = True
        DataField = 'ies_situacao'
        DataSource = DsSitContaPagar
        ItemHeight = 13
        ReadOnly = True
        TabOrder = 4
      end
      object bt_data_cadastro: TCustomImgButton
        Left = 231
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 2
        TabStop = False
        OnClick = bt_data_cadastroClick
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object cod_plano_conta: TDBEdit
        Left = 83
        Top = 39
        Width = 110
        Height = 21
        DataField = 'cod_plano_conta'
        DataSource = DsContaPagar
        TabOrder = 5
      end
      object btPesqPlanoConta: TResBitBtn
        Left = 198
        Top = 38
        Width = 23
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
        TabStop = False
        OnClick = btPesqPlanoContaClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_centro_custo: TDBEdit
        Left = 309
        Top = 39
        Width = 110
        Height = 21
        DataField = 'cod_centro_custo'
        DataSource = DsContaPagar
        TabOrder = 7
      end
      object btPesqCentroCusto: TResBitBtn
        Left = 424
        Top = 38
        Width = 23
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
        TabStop = False
        OnClick = btPesqCentroCustoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object tipo_registro: TDBDataComboBox
        Left = 504
        Top = 39
        Width = 104
        Height = 21
        AutoDropDown = True
        DataField = 'tipo_registro'
        DataSource = DsContaPagar
        ItemHeight = 13
        ReadOnly = True
        TabOrder = 9
      end
    end
    object gpCredor: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 43
      Cursor = crArrow
      Align = alTop
      Caption = 'Credor'
      TabOrder = 1
      object Label3: TLabel
        Left = 10
        Top = 17
        Width = 57
        Height = 13
        Alignment = taRightJustify
        Caption = '&Fornecedor:'
        FocusControl = cod_fornecedor
        Transparent = True
        WordWrap = True
      end
      object den_fornecedor: TEdit
        Left = 212
        Top = 15
        Width = 394
        Height = 21
        Color = clWhite
        ReadOnly = True
        TabOrder = 2
      end
      object cod_fornecedor: TDBEdit
        Left = 70
        Top = 15
        Width = 110
        Height = 21
        DataField = 'cod_fornecedor'
        DataSource = DsContaPagar
        TabOrder = 0
        OnExit = cod_fornecedorExit
      end
      object btPesqFornecedor: TResBitBtn
        Left = 185
        Top = 14
        Width = 23
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
        Caption = '&1 - Pagamentos'
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
            DataSource = DsContaPagar
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
          DataSource = DsContaPagarPagto
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
          OnKeyDown = grdPagtosKeyDown
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
            FocusControl = valor_total
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clNavy
            Font.Height = -15
            Font.Name = 'MS Sans Serif'
            Font.Style = [fsBold]
            ParentFont = False
          end
          object valor_total: TDBEdit
            Left = 609
            Top = 5
            Width = 113
            Height = 24
            TabStop = False
            DataField = 'valor_total'
            DataSource = DsContaPagar
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
      object tbObs: TTabSheet
        Caption = '&2 - Observa'#231#227'o'
        ImageIndex = 2
        object observacao: TDBMemo
          Left = 5
          Top = 5
          Width = 587
          Height = 128
          DataField = 'observacao'
          DataSource = DsContaPagar
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
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btDelete: TResBitBtn
      Left = 462
    end
    inherited btajuda: TResBitBtn
      Left = 640
    end
    inherited MenuClicks: TPopupMenu
      object execRelatorio1: TMenuItem
        Action = execRelatorio
        Caption = 'Visualizar Impress'#227'o'
      end
      object execVisualizaPagto1: TMenuItem
        Action = execVisualizaPagto
        Caption = 'Visualizar Pagamento'
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
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object btRecContaPagar: TResBitBtn
    Left = 538
    Top = 61
    Width = 32
    Height = 32
    Action = execVisualizaPagto
    TabOrder = 5
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'CIFRAO'
    GlyphResID = 0
  end
  object btRelatorio: TResBitBtn
    Left = 500
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
  object QyContaPagar: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterOpen = QyContaPagarAfterOpen
    BeforeClose = QyContaPagarBeforeClose
    AfterScroll = QyContaPagarAfterScroll
    BeforePost = QyContaPagarBeforePost
    AfterPost = QyContaPagarAfterPost
    BeforeDelete = QyContaPagarBeforeDelete
    OnPostError = QyContaPagarPostError
    SQL.Strings = (
      
        'SELECT cod_conta_pagar, cod_fornecedor, data_cadastro, num_docum' +
        'ento, ies_situacao,'
      '       tipo_registro, cod_centro_custo, cod_plano_conta,'
      '       cod_forma_pagto, num_parcelas, valor_total, observacao'
      '  FROM tbl_conta_pagar'
      ' ORDER BY cod_conta_pagar')
    Params = <>
    Left = 600
    Top = 12
  end
  object QyCadPagto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'seq_parcela'
    UpdateObject = AddPagto
    CachedUpdates = True
    BeforeInsert = QyCadPagtoBeforeInsert
    SQL.Strings = (
      'SELECT cod_conta_pagar, seq_parcela, '
      '       valor_parcela, data_vencimento, observacao, ies_pago'
      '  FROM tbl_conta_pagar_pagto'
      ' WHERE cod_conta_pagar =:cod_conta_pagar'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
    DataSource = DsContaPagar
    IndexFieldNames = 'seq_parcela Asc'
    Left = 485
    Top = 213
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
    object QyCadPagtocod_conta_pagar: TIntegerField
      DisplayWidth = 10
      FieldName = 'cod_conta_pagar'
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
      OnSetText = QyCadPagtovalor_parcelaSetText
      currency = True
      Precision = 13
    end
    object QyCadPagtodata_vencimento: TDateTimeField
      FieldName = 'data_vencimento'
      ProviderFlags = [pfInUpdate]
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '90/90/0099;1;_'
    end
    object QyCadPagtoobservacao: TStringField
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
  object DsContaPagar: TDataSource
    AutoEdit = False
    DataSet = QyContaPagar
    Left = 636
    Top = 12
  end
  object DsContaPagarPagto: TDataSource
    AutoEdit = False
    DataSet = QyCadPagto
    Left = 516
    Top = 216
  end
  object AddPagto: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_conta_pagar_pagto'
      'WHERE cod_conta_pagar = :cod_conta_pagar')
    InsertSQL.Strings = (
      'INSERT INTO tbl_conta_pagar_pagto'
      
        '  (cod_conta_pagar ,seq_parcela, valor_parcela, data_vencimento,' +
        ' '
      'ies_pago,  observacao)'
      'VALUES'
      
        '  (:cod_conta_pagar ,:seq_parcela, :valor_parcela, :data_vencime' +
        'nto, '
      #39'N'#39',:observacao)')
    ModifySQL.Strings = (
      'UPDATE tbl_conta_pagar_pagto '
      '   SET  valor_parcela = :valor_parcela,'
      '  data_vencimento = :data_vencimento,'
      '  observacao = :observacao'
      'WHERE cod_conta_pagar = :cod_conta_pagar'
      ' AND seq_parcela = :seq_parcela'
      '  ')
    UseSequenceFieldForRefreshSQL = False
    Left = 552
    Top = 216
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptInput
        Value = 0
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
      end>
  end
  object QySitContaPagar: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT ies_situacao'
      '  FROM tbl_conta_pagar'
      ' WHERE cod_conta_pagar = :cod_conta_pagar')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
    DataSource = DsContaPagar
    Left = 612
    Top = 114
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
  end
  object DsSitContaPagar: TDataSource
    AutoEdit = False
    DataSet = QySitContaPagar
    Left = 648
    Top = 114
  end
  object ActionList1: TActionList
    Left = 720
    Top = 66
    object execVisualizaPagto: TAction
      Enabled = False
      Hint = 'Visualiza o pagamento da conta.'
      ShortCut = 16463
      OnExecute = btRecContaPagarClick
    end
    object execRelatorio: TAction
      Enabled = False
      Hint = 'Visualiza a impress'#227'o da conta.'
      ShortCut = 16457
      OnExecute = execRelatorioExecute
    end
    object delLine: TAction
      Caption = '&Remover Linha'
      Enabled = False
      ShortCut = 32850
    end
  end
end
