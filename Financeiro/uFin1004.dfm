inherited Fin1004: TFin1004
  Caption = 'Pagamento de Contas'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Pagamentos'
  end
  inherited BodyPanel: TPanel
    object Label15: TLabel
      Left = 0
      Top = 182
      Width = 750
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object gpCadastro: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 91
      Cursor = crArrow
      Align = alTop
      Caption = 'Conta '#224' Pagar'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 36
        Height = 13
        Cursor = crArrow
        Caption = 'C'#243'digo:'
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
        Caption = 'Data:'
        DragCursor = crDefault
        FocusControl = data_cadastro
        Transparent = True
        WordWrap = True
      end
      object Label12: TLabel
        Left = 254
        Top = 17
        Width = 58
        Height = 13
        Cursor = crArrow
        Caption = 'Documento:'
        DragCursor = crDefault
        FocusControl = num_documento
        Transparent = True
        WordWrap = True
      end
      object Label6: TLabel
        Left = 475
        Top = 17
        Width = 45
        Height = 13
        Caption = 'Situa'#231#227'o:'
        FocusControl = ies_situacao
      end
      object Label4: TLabel
        Left = 7
        Top = 41
        Width = 72
        Height = 13
        Alignment = taRightJustify
        Caption = 'Conta Cont'#225'bil:'
        FocusControl = cod_plano_conta
        Transparent = True
      end
      object Label5: TLabel
        Left = 213
        Top = 41
        Width = 64
        Height = 13
        Alignment = taRightJustify
        Caption = 'Centro Custo:'
        FocusControl = cod_centro_custo
        Transparent = True
      end
      object Label3: TLabel
        Left = 8
        Top = 65
        Width = 57
        Height = 13
        Alignment = taRightJustify
        Caption = 'Fornecedor:'
        FocusControl = cod_fornecedor
        Transparent = True
        WordWrap = True
      end
      object Label7: TLabel
        Left = 427
        Top = 41
        Width = 57
        Height = 13
        Caption = 'Pagamento:'
        FocusControl = cod_forma_pagto
      end
      object cod_conta_pagar: TDBEdit
        Left = 48
        Top = 15
        Width = 69
        Height = 21
        TabStop = False
        Color = clWhite
        DataField = 'cod_conta_pagar'
        DataSource = DsContaPagar
        TabOrder = 0
      end
      object data_cadastro: TDBEdit
        Left = 162
        Top = 15
        Width = 79
        Height = 21
        TabStop = False
        DataField = 'data_cadastro'
        DataSource = DsContaPagar
        TabOrder = 1
      end
      object num_documento: TDBEdit
        Left = 315
        Top = 15
        Width = 120
        Height = 21
        TabStop = False
        DataField = 'num_documento'
        DataSource = DsContaPagar
        TabOrder = 2
      end
      object ies_situacao: TDBDataComboBox
        Left = 524
        Top = 15
        Width = 104
        Height = 21
        DataField = 'ies_situacao'
        DataSource = DsSitContaPagar
        ItemHeight = 13
        ReadOnly = True
        TabOrder = 3
        TabStop = False
      end
      object cod_plano_conta: TDBEdit
        Left = 83
        Top = 39
        Width = 110
        Height = 21
        TabStop = False
        DataField = 'cod_plano_conta'
        DataSource = DsContaPagar
        TabOrder = 4
      end
      object cod_centro_custo: TDBEdit
        Left = 281
        Top = 39
        Width = 110
        Height = 21
        TabStop = False
        DataField = 'cod_centro_custo'
        DataSource = DsContaPagar
        TabOrder = 5
      end
      object cod_fornecedor: TDBEdit
        Left = 69
        Top = 63
        Width = 110
        Height = 21
        TabStop = False
        DataField = 'cod_fornecedor'
        DataSource = DsContaPagar
        TabOrder = 7
      end
      object den_fornecedor: TDBEdit
        Left = 186
        Top = 63
        Width = 442
        Height = 21
        TabStop = False
        Color = clWhite
        DataField = 'den_fornecedor'
        DataSource = DsContaPagar
        ReadOnly = True
        TabOrder = 8
      end
      object cod_forma_pagto: TDBEdit
        Left = 488
        Top = 39
        Width = 140
        Height = 21
        TabStop = False
        DataField = 'den_forma_pagto'
        DataSource = DsContaPagar
        TabOrder = 6
      end
    end
    object gbPagtos: TGroupBox
      Left = 0
      Top = 91
      Width = 750
      Height = 91
      Align = alTop
      Caption = 'Pagamentos'
      TabOrder = 1
      object Label8: TLabel
        Left = 11
        Top = 17
        Width = 76
        Height = 13
        Cursor = crArrow
        Caption = 'Valor &Desconto:'
        DragCursor = crDefault
        FocusControl = valor_desconto
        Transparent = True
      end
      object Label9: TLabel
        Left = 31
        Top = 41
        Width = 56
        Height = 13
        Cursor = crArrow
        Caption = 'Valor &Multa:'
        DragCursor = crDefault
        FocusControl = valor_multa
        Transparent = True
      end
      object Label10: TLabel
        Left = 8
        Top = 65
        Width = 79
        Height = 13
        Cursor = crArrow
        Caption = 'Valor &Acr'#233'scimo:'
        DragCursor = crDefault
        FocusControl = valor_acrescimo
        Transparent = True
      end
      object Label11: TLabel
        Left = 235
        Top = 17
        Width = 66
        Height = 13
        Cursor = crArrow
        Caption = 'Valor &Parcela:'
        DragCursor = crDefault
        FocusControl = valor_parcela
        Transparent = True
      end
      object Label13: TLabel
        Left = 246
        Top = 41
        Width = 55
        Height = 13
        Cursor = crArrow
        Caption = '&Valor Pago:'
        DragCursor = crDefault
        FocusControl = valor_pago
        Transparent = True
      end
      object Label14: TLabel
        Left = 218
        Top = 65
        Width = 83
        Height = 13
        Cursor = crArrow
        Caption = 'Da&ta Pagamento:'
        DragCursor = crDefault
        FocusControl = data_pagamento
        Transparent = True
      end
      object valor_parcela: TDBEdit
        Left = 304
        Top = 15
        Width = 100
        Height = 21
        DataField = 'valor_parcela'
        DataSource = DsContaPagarPagto
        TabOrder = 3
      end
      object valor_pago: TDBEdit
        Left = 304
        Top = 39
        Width = 100
        Height = 21
        DataField = 'valor_pago'
        DataSource = DsContaPagarPagto
        TabOrder = 4
      end
      object data_pagamento: TDBEdit
        Left = 304
        Top = 63
        Width = 100
        Height = 21
        DataField = 'data_pagamento'
        DataSource = DsContaPagarPagto
        TabOrder = 5
      end
      object valor_desconto: TDBEdit
        Left = 90
        Top = 15
        Width = 100
        Height = 21
        DataField = 'valor_desconto'
        DataSource = DsContaPagarPagto
        TabOrder = 0
      end
      object valor_multa: TDBEdit
        Left = 90
        Top = 39
        Width = 100
        Height = 21
        DataField = 'valor_multa'
        DataSource = DsContaPagarPagto
        TabOrder = 1
      end
      object valor_acrescimo: TDBEdit
        Left = 90
        Top = 63
        Width = 100
        Height = 21
        DataField = 'valor_acrescimo'
        DataSource = DsContaPagarPagto
        TabOrder = 2
      end
      object btPagarPagto: TResBitBtn
        Left = 416
        Top = 12
        Width = 32
        Height = 32
        Hint = 'Efetuar pagamento da conta.'
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
        OnClick = btPagarPagtoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'CIFRAO'
        GlyphResID = 0
      end
      object btSavePagto: TResBitBtn
        Left = 488
        Top = 12
        Width = 32
        Height = 32
        Hint = 'Salvar informa'#231#245'es do pagamento.'
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        OnClick = btSavePagtoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'SALVAR'
        GlyphResID = 0
      end
      object btCancelPagto: TResBitBtn
        Left = 524
        Top = 12
        Width = 32
        Height = 32
        Hint = 'Cancelar pagamento.'
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
        OnClick = btCancelPagtoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'CANCELAR'
        GlyphResID = 0
      end
      object btEstornaPagto: TResBitBtn
        Left = 452
        Top = 12
        Width = 32
        Height = 32
        Hint = 'Estornar pagamento da conta.'
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 9
        OnClick = btEstornaPagtoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'DESFAZER'
        GlyphResID = 0
      end
      object bt_data_pagamento: TCustomImgButton
        Left = 385
        Top = 66
        Width = 16
        Height = 16
        TabOrder = 10
        TabStop = False
        OnClick = bt_data_pagamentoClick
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
    end
    object grdPagtos: TDBGrid
      Left = 0
      Top = 188
      Width = 750
      Height = 229
      Align = alClient
      DataSource = DsContaPagarPagto
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgRowSelect, dgConfirmDelete, dgCancelOnExit]
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnDrawColumnCell = grdPagtosDrawColumnCell
      Columns = <
        item
          Expanded = False
          FieldName = 'seq_parcela'
          Title.Alignment = taCenter
          Width = 35
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_parcela'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'data_vencimento'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_desconto'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_multa'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_acrescimo'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'valor_pago'
          Title.Alignment = taCenter
          Title.Caption = 'Valor Pago'
          Width = 90
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'data_pagamento'
          Title.Alignment = taCenter
          Title.Caption = 'Data Pagamento'
          Width = 90
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'ies_pago'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end>
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btExit: TResBitBtn
      Left = 272
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        Visible = False
      end
      inherited execBtUndoClick: TAction
        Visible = False
      end
      inherited execBtSaveClick: TAction
        Visible = False
      end
      inherited execBtCancelClick: TAction
        Visible = False
      end
      inherited execBtNewClick: TAction
        Enabled = False
        Visible = False
      end
      inherited execBtCopyClick: TAction
        Visible = False
      end
      inherited execBtDeleteClick: TAction
        Visible = False
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object CnsContaPagar: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterOpen = CnsContaPagarAfterOpen
    BeforeClose = CnsContaPagarBeforeClose
    AfterScroll = CnsContaPagarAfterScroll
    SQL.Strings = (
      
        'SELECT cod_conta_pagar,cod_fornecedor,den_fornecedor,data_cadast' +
        'ro,num_documento,'
      
        '       ies_situacao,cod_plano_conta,cod_centro_custo,den_forma_p' +
        'agto'
      '  FROM cns_conta_pagar'
      'ORDER BY cod_conta_pagar'
      '')
    Params = <>
    Left = 612
    Top = 6
  end
  object DsContaPagar: TDataSource
    AutoEdit = False
    DataSet = CnsContaPagar
    Left = 642
    Top = 6
  end
  object QyCadPagto: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterScroll = QyCadPagtoAfterScroll
    UpdateObject = AtuPagto
    SQL.Strings = (
      'SELECT cod_conta_pagar, seq_parcela, '
      '       valor_parcela, data_vencimento, ies_pago,'
      
        '       valor_pago, valor_desconto, valor_acrescimo, valor_multa,' +
        ' data_pagamento'
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
    MasterFields = 'cod_conta_pagar'
    MasterSource = DsContaPagar
    LinkedFields = 'cod_conta_pagar'
    Left = 575
    Top = 247
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
      DisplayLabel = 'Seq'
      FieldName = 'seq_parcela'
      ProviderFlags = [pfInUpdate, pfInWhere, pfInKey]
      Required = True
    end
    object QyCadPagtovalor_desconto: TFloatField
      DisplayLabel = 'Desconto'
      DisplayWidth = 13
      FieldName = 'valor_desconto'
      currency = True
      Precision = 13
    end
    object QyCadPagtovalor_multa: TFloatField
      DisplayLabel = 'Multa'
      DisplayWidth = 13
      FieldName = 'valor_multa'
      currency = True
      Precision = 13
    end
    object QyCadPagtovalor_acrescimo: TFloatField
      DisplayLabel = 'Acr'#233'scimo'
      DisplayWidth = 13
      FieldName = 'valor_acrescimo'
      currency = True
      Precision = 13
    end
    object QyCadPagtovalor_parcela: TFloatField
      DisplayLabel = 'Valor Parcela'
      DisplayWidth = 13
      FieldName = 'valor_parcela'
      ProviderFlags = [pfInKey]
      currency = True
      Precision = 13
    end
    object QyCadPagtodata_vencimento: TDateTimeField
      DisplayLabel = 'Data Vencimento'
      FieldName = 'data_vencimento'
      ProviderFlags = [pfInUpdate]
      DisplayFormat = 'dd/mm/yyyy'
    end
    object QyCadPagtovalor_pago: TFloatField
      DisplayLabel = 'Valor Recebido'
      DisplayWidth = 13
      FieldName = 'valor_pago'
      currency = True
      Precision = 13
    end
    object QyCadPagtodata_pagamento: TDateTimeField
      DisplayLabel = 'Data Recebimento'
      FieldName = 'data_pagamento'
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '!90/90/0099;1;_'
    end
    object QyCadPagtoies_pago: TStringField
      DisplayLabel = 'Pago'
      FieldName = 'ies_pago'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
  end
  object DsContaPagarPagto: TDataSource
    AutoEdit = False
    DataSet = QyCadPagto
    Left = 606
    Top = 246
  end
  object AtuPagto: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_conta_pagar_pagto '
      'WHERE cod_conta_pagar = :cod_conta_pagar')
    ModifySQL.Strings = (
      'UPDATE tbl_conta_pagar_pagto '
      '   SET valor_pago = :valor_pago,'
      '       data_pagamento = :data_pagamento,'
      '       valor_desconto = :valor_desconto,'
      '       valor_acrescimo = :valor_acrescimo, '
      '       valor_multa = :valor_multa,'
      '       ies_pago= :ies_pago'
      'WHERE cod_conta_pagar = :cod_conta_pagar'
      ' AND seq_parcela = :seq_parcela')
    UseSequenceFieldForRefreshSQL = False
    Left = 636
    Top = 246
    ParamData = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_pago'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_pagamento'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_desconto'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_acrescimo'
        ParamType = ptUnknown
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'valor_multa'
        ParamType = ptUnknown
      end
      item
        DataType = ftString
        Name = 'ies_pago'
        ParamType = ptUnknown
        Size = 1
      end
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
    Left = 618
    Top = 42
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
  end
  object DsSitContaPagar: TDataSource
    DataSet = QySitContaPagar
    Left = 654
    Top = 42
  end
end
