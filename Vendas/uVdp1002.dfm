inherited Vdp1002: TVdp1002
  Caption = 'Cadastro de Or'#231'amentos'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Or'#231'amentos'
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
        Left = 8
        Top = 17
        Width = 36
        Height = 13
        Cursor = crArrow
        Caption = '&C'#243'digo:'
        DragCursor = crDefault
        FocusControl = cod_orcamento
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 147
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
        Left = 287
        Top = 17
        Width = 50
        Height = 13
        Cursor = crArrow
        Caption = '&V'#225'lido at'#233':'
        DragCursor = crDefault
        FocusControl = data_validade
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
      object Label5: TLabel
        Left = 7
        Top = 41
        Width = 72
        Height = 13
        Alignment = taRightJustify
        Caption = 'Co&nta Cont'#225'bil:'
        FocusControl = cod_plano_conta
        Transparent = True
      end
      object Label7: TLabel
        Left = 238
        Top = 41
        Width = 64
        Height = 13
        Alignment = taRightJustify
        Caption = 'Centro C&usto:'
        FocusControl = cod_centro_custo
        Transparent = True
      end
      object cod_orcamento: TDBEdit
        Left = 48
        Top = 15
        Width = 70
        Height = 21
        Color = clWhite
        DataField = 'cod_orcamento'
        DataSource = DsOrcamento
        TabOrder = 0
      end
      object data_cadastro: TDBEdit
        Left = 176
        Top = 15
        Width = 88
        Height = 21
        DataField = 'data_cadastro'
        DataSource = DsOrcamento
        TabOrder = 1
      end
      object btCalendar01: TCustomImgButton
        Left = 246
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 4
        TabStop = False
        OnClick = btCalendar01Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object data_validade: TDBEdit
        Left = 341
        Top = 15
        Width = 88
        Height = 21
        DataField = 'data_validade'
        DataSource = DsOrcamento
        TabOrder = 2
        OnExit = data_validadeExit
      end
      object btCalendar02: TCustomImgButton
        Left = 411
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 5
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
        DataSource = DsSitPedidoVenda
        ItemHeight = 13
        TabOrder = 3
      end
      object cod_plano_conta: TDBEdit
        Left = 83
        Top = 39
        Width = 104
        Height = 21
        DataField = 'cod_plano_conta'
        DataSource = DsOrcamento
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
        DataSource = DsOrcamento
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
    object gbCliente: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Cliente'
      TabOrder = 1
      object Label3: TLabel
        Left = 13
        Top = 17
        Width = 35
        Height = 13
        Alignment = taRightJustify
        Caption = 'C&liente:'
        FocusControl = cod_cliente
        Transparent = True
        WordWrap = True
      end
      object Label20: TLabel
        Left = 190
        Top = 41
        Width = 55
        Height = 13
        Alignment = taRightJustify
        Caption = 'CPF/CNP&J:'
        FocusControl = cpf_cnpj
        Transparent = True
        WordWrap = True
      end
      object Rtulo98: TLabel
        Left = 382
        Top = 41
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'R&G/IE:'
        FocusControl = rg_ie
        Transparent = True
        WordWrap = True
      end
      object Label4: TLabel
        Left = 24
        Top = 41
        Width = 24
        Height = 13
        Cursor = crArrow
        Caption = '&Tipo:'
        DragCursor = crDefault
        FocusControl = tipo_pessoa
        Transparent = True
        WordWrap = True
      end
      object den_cliente: TDBEdit
        Left = 196
        Top = 15
        Width = 407
        Height = 21
        Color = clWhite
        DataField = 'den_cliente'
        DataSource = DsClientes
        TabOrder = 2
      end
      object cpf_cnpj: TDBEdit
        Left = 248
        Top = 39
        Width = 120
        Height = 21
        DataField = 'cpf_cnpj'
        DataSource = DsClientes
        TabOrder = 4
      end
      object rg_ie: TDBEdit
        Left = 419
        Top = 39
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'rg_ie'
        DataSource = DsClientes
        TabOrder = 5
      end
      object cod_cliente: TDBEdit
        Left = 51
        Top = 15
        Width = 110
        Height = 21
        DataField = 'cod_cliente'
        DataSource = DsOrcamento
        TabOrder = 0
      end
      object btPesqCliente: TResBitBtn
        Left = 166
        Top = 14
        Width = 24
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btPesqClienteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object tipo_pessoa: TDBDataComboBox
        Left = 50
        Top = 39
        Width = 126
        Height = 21
        AutoDropDown = True
        DataField = 'tipo_pessoa'
        DataSource = DsClientes
        ItemHeight = 13
        Sorted = True
        TabOrder = 3
      end
      object btEndereco: TResBitBtn
        Left = 526
        Top = 37
        Width = 78
        Height = 24
        Caption = '&Endere'#231'o'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = btEnderecoClick
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'CASAM'
        GlyphResID = 0
      end
    end
    object pgDetalhes: TPageControl
      Left = 0
      Top = 134
      Width = 758
      Height = 287
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
          Height = 226
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
              FieldName = 'preco_venda'
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
          Top = 226
          Width = 750
          Height = 33
          Align = alBottom
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 1
          object Label19: TLabel
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
            DataSource = DsOrcamento
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
          DataSource = DsOrcamento
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
          object Label17: TLabel
            Left = 8
            Top = 7
            Width = 57
            Height = 13
            Caption = '&Pagamento:'
            FocusControl = cod_forma_pagto
          end
          object Label18: TLabel
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
            DataSource = DsOrcamento
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
          Height = 196
          Align = alClient
          DataSource = DsCompraPagto
          Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
          TabOrder = 1
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
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
            end>
        end
        object pnTotal: TPanel
          Left = 0
          Top = 226
          Width = 750
          Height = 33
          Align = alBottom
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 2
          object Label16: TLabel
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
            DataSource = DsOrcamento
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
    inherited MenuClicks: TPopupMenu
      object Fechar1: TMenuItem
        Action = execFechamento
        Caption = 'Fechamento Pedido'
      end
      object PesquisaProdutoCliente2: TMenuItem
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
  object btFechamento: TResBitBtn
    Left = 500
    Top = 61
    Width = 32
    Height = 32
    Action = execFechamento
    TabOrder = 5
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'FECHANEGC'
    GlyphResID = 0
  end
  object btRelatorio: TResBitBtn
    Left = 538
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
  object grpEndereco: TGroupBox
    Left = 68
    Top = 355
    Width = 600
    Height = 91
    Cursor = crArrow
    Caption = 'Endere'#231'o'
    TabOrder = 7
    Visible = False
    OnExit = grpEnderecoExit
    object Label9: TLabel
      Left = 503
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
    object Label10: TLabel
      Left = 13
      Top = 65
      Width = 30
      Height = 13
      Caption = '&Bairro:'
      FocusControl = bairro
      Transparent = True
    end
    object Label11: TLabel
      Left = 160
      Top = 41
      Width = 36
      Height = 13
      Caption = 'Ci&dade:'
      Transparent = True
    end
    object Label13: TLabel
      Left = 13
      Top = 41
      Width = 36
      Height = 13
      Caption = '&Estado:'
      FocusControl = cod_uf
      Transparent = True
    end
    object Label14: TLabel
      Left = 13
      Top = 17
      Width = 57
      Height = 13
      Caption = '&Logradouro:'
      FocusControl = logradouro
      Transparent = True
    end
    object Label15: TLabel
      Left = 447
      Top = 65
      Width = 67
      Height = 13
      Caption = '&Complemento:'
      FocusControl = complemento
      Transparent = True
    end
    object logradouro: TDBEdit
      Left = 75
      Top = 15
      Width = 400
      Height = 21
      Color = clWhite
      DataField = 'logradouro'
      DataSource = DsClientes
      TabOrder = 0
    end
    object numero: TDBEdit
      Left = 547
      Top = 15
      Width = 46
      Height = 21
      DataField = 'numero'
      DataSource = DsClientes
      TabOrder = 1
    end
    object cod_uf: TDBComboBox
      Left = 53
      Top = 39
      Width = 40
      Height = 21
      Hint = 'Duplo clique ou pressione '#39'+'#39'|para cadastrar um novo estado.'
      DataField = 'cod_uf'
      DataSource = DsClientes
      ItemHeight = 13
      TabOrder = 2
      OnChange = cod_ufChange
    end
    object cep: TDBEdit
      Left = 520
      Top = 39
      Width = 74
      Height = 21
      Color = clWhite
      DataField = 'cep'
      DataSource = DsClientes
      TabOrder = 4
    end
    object bairro: TDBEdit
      Left = 47
      Top = 63
      Width = 236
      Height = 21
      DataField = 'bairro'
      DataSource = DsClientes
      TabOrder = 5
    end
    object complemento: TDBEdit
      Left = 519
      Top = 63
      Width = 75
      Height = 21
      DataField = 'complemento'
      DataSource = DsClientes
      TabOrder = 6
    end
    object cod_cidade: TDBDataComboBox
      Left = 200
      Top = 39
      Width = 216
      Height = 21
      Hint = 'Duplo clique ou pressione '#39'+'#39'|para cadastrar uma nova cidade.'
      DataField = 'cod_cidade'
      DataSource = DsClientes
      ItemHeight = 13
      Sorted = True
      TabOrder = 3
      LookUpDataSet = QyCidade
      LookUpField = 'cod_cidade'
      ResultField = 'den_cidade'
    end
  end
  object DsOrcamento: TDataSource
    AutoEdit = False
    DataSet = QyOrcamento
    Left = 728
    Top = 8
  end
  object QyCliente: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cliente, tipo_pessoa, den_cliente, cpf_cnpj, rg_ie,'
      
        '               logradouro, numero, complemento, bairro, cod_cida' +
        'de, cod_uf, cep'
      '  FROM tbl_cliente'
      ' WHERE cod_cliente =:cod_cliente')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_cliente'
        ParamType = ptUnknown
      end>
    Left = 636
    Top = 8
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_cliente'
        ParamType = ptUnknown
      end>
  end
  object DsClientes: TDataSource
    AutoEdit = False
    DataSet = QyCliente
    Left = 666
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
      'SELECT v.cod_orcamento, v.seq_produto, '
      '       v.cod_produto, p.den_produto,'
      
        '       v.qtd_produto, v.val_desconto, v.preco_venda, p.preco_ven' +
        'da preco_produto'
      '  FROM tbl_orcamento_item v,'
      '       tbl_produto p'
      ' WHERE v.cod_orcamento = :cod_orcamento'
      '   AND v.cod_produto = p.cod_produto'
      ' ORDER BY v.seq_produto')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
    DataSource = DsOrcamento
    IndexFieldNames = 'seq_produto Asc'
    Left = 438
    Top = 300
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
    object QyCadProdutocod_orcamento: TIntegerField
      FieldName = 'cod_orcamento'
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
    object QyCadProdutopreco_venda: TFloatField
      DisplayLabel = 'Valor Unit'#225'rio'
      FieldName = 'preco_venda'
      OnSetText = PrecoVendaSetText
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
      FieldName = 'preco_produto'
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
      'SELECT cod_orcamento, seq_parcela, '
      '       valor_parcela, data_vencimento, observacao'
      '  FROM tbl_orcamento_pagto'
      ' WHERE cod_orcamento = :cod_orcamento'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
    DataSource = DsOrcamento
    IndexFieldNames = 'seq_parcela Asc'
    Left = 581
    Top = 300
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
    object QyCadPagtocod_orcamento: TIntegerField
      DisplayWidth = 10
      FieldName = 'cod_orcamento'
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
    object QyCadPagtoobservacao: TStringField
      FieldName = 'observacao'
      ProviderFlags = [pfInUpdate]
      Size = 100
    end
  end
  object AddItemVenda: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_orcamento_item'
      'WHERE cod_orcamento = :cod_orcamento '
      'AND seq_produto = :seq_produto')
    InsertSQL.Strings = (
      'INSERT INTO tbl_orcamento_item '
      '(cod_orcamento, seq_produto, cod_produto, qtd_produto, '
      'preco_venda,val_desconto) '
      'VALUES '
      '(:cod_orcamento, :seq_produto, :cod_produto, :qtd_produto, '
      ':preco_venda,:val_desconto)')
    ModifySQL.Strings = (
      'UPDATE tbl_orcamento_item SET'
      '  cod_produto = :cod_produto,'
      '  qtd_produto = :qtd_produto,'
      '  preco_venda = :preco_venda,'
      '  val_desconto = :val_desconto'
      'WHERE cod_orcamento = :cod_orcamento '
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
        Name = 'preco_venda'
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
        Name = 'cod_orcamento'
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
      'DELETE FROM tbl_orcamento_pagto'
      'WHERE cod_orcamento = :cod_orcamento '
      'AND seq_parcela = :seq_parcela')
    InsertSQL.Strings = (
      'INSERT INTO tbl_orcamento_pagto '
      '(cod_orcamento, seq_parcela, valor_parcela, data_vencimento, '
      'observacao) '
      'VALUES '
      
        '(:cod_orcamento, :seq_parcela, :valor_parcela, :data_vencimento,' +
        '  '
      ':observacao)')
    ModifySQL.Strings = (
      'UPDATE tbl_orcamento_pagto SET'
      '  valor_parcela = :valor_parcela,'
      '  data_vencimento = :data_vencimento,'
      '  observacao = :observacao'
      'WHERE cod_orcamento = :cod_orcamento '
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
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end
      item
        DataType = ftLargeint
        Name = 'seq_parcela'
        ParamType = ptUnknown
      end>
  end
  object QyOrcamento: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    AfterOpen = QyOrcamentoAfterOpen
    BeforeClose = QyOrcamentoBeforeClose
    AfterScroll = QyOrcamentoAfterScroll
    OnCalcFields = QyOrcamentoCalcFields
    BeforePost = QyOrcamentoBeforePost
    AfterPost = QyOrcamentoAfterPost
    BeforeDelete = QyOrcamentoBeforeDelete
    SQL.Strings = (
      'SELECT cod_orcamento, cod_cliente, data_cadastro,'
      
        #9#9' data_validade, ies_situacao, cod_plano_conta, cod_centro_cust' +
        'o,'
      '       cod_forma_pagto, num_parcelas, valor_total, observacao'
      '  FROM tbl_orcamento'
      ' ORDER BY cod_orcamento')
    Params = <>
    Left = 696
    Top = 8
  end
  object ActionList1: TActionList
    Left = 702
    Top = 72
    object execRelatorio: TAction
      Enabled = False
      Hint = 'Visualiza a impress'#227'o do or'#231'amento.'
      ShortCut = 16460
      OnExecute = btRelatorioClick
    end
    object execFechamento: TAction
      Enabled = False
      Hint = 'Fecha o or'#231'amento.'
      ShortCut = 16454
      OnExecute = btFechamentoClick
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
  object QySitPedidoVenda: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT ies_situacao'
      '  FROM tbl_orcamento'
      ' WHERE cod_orcamento =:cod_orcamento')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
    DataSource = DsOrcamento
    Left = 612
    Top = 114
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_orcamento'
        ParamType = ptUnknown
      end>
  end
  object DsSitPedidoVenda: TDataSource
    AutoEdit = False
    DataSet = QySitPedidoVenda
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
      'SELECT cod_produto, den_produto, cod_unid_medida, preco_venda'
      '  FROM tbl_produto'
      ' WHERE cod_produto = :cod_produto '
      '   AND ies_ativo = '#39'S'#39)
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
      end>
    Left = 80
    Top = 300
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
      end>
  end
  object QyCidade: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cidade, den_cidade, cod_uf'
      '  FROM tbl_cidade'
      ' ORDER BY cod_uf, den_cidade;')
    Params = <>
    Left = 489
    Top = 392
  end
end
