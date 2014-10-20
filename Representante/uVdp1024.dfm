inherited Vdp1024: TVdp1024
  Caption = 'Representanteses x Comiss'#227'os'
  OnDestroy = nil
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Representantes x Comiss'#227'o'
  end
  inherited BodyPanel: TPanel
    object Label7: TLabel
      Left = 0
      Top = 109
      Width = 758
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Representantes'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 73
        Height = 13
        Cursor = crArrow
        Caption = 'Representante:'
        DragCursor = crDefault
        FocusControl = cod_representante
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 248
        Top = 17
        Width = 24
        Height = 13
        Cursor = crArrow
        Caption = 'Tipo:'
        DragCursor = crDefault
        FocusControl = tipo_pessoa
        Transparent = True
        WordWrap = True
      end
      object Label3: TLabel
        Left = 12
        Top = 41
        Width = 69
        Height = 13
        Alignment = taRightJustify
        Caption = 'Denomina'#231#227'o:'
        Transparent = True
        WordWrap = True
      end
      object cod_representante: TDBEdit
        Left = 84
        Top = 15
        Width = 110
        Height = 21
        Color = clWhite
        DataField = 'cod_representante'
        DataSource = DsRepresentantes
        TabOrder = 0
      end
      object tipo_pessoa: TDBDataComboBox
        Left = 275
        Top = 15
        Width = 126
        Height = 21
        AutoDropDown = True
        DataField = 'tipo_pessoa'
        DataSource = DsRepresentantes
        ItemHeight = 13
        Sorted = True
        TabOrder = 1
      end
      object ies_ativo: TDBCheckBox
        Left = 544
        Top = 17
        Width = 50
        Height = 14
        Caption = 'Ativo?'
        DataField = 'ies_ativo'
        DataSource = DsRepresentantes
        TabOrder = 2
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
      object den_representante: TDBEdit
        Left = 84
        Top = 39
        Width = 509
        Height = 21
        Color = clWhite
        DataField = 'den_representante'
        DataSource = DsRepresentantes
        TabOrder = 3
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 42
      Cursor = crArrow
      Align = alTop
      Caption = 'Per'#237'odo'
      TabOrder = 1
      DesignSize = (
        758
        42)
      object Label4: TLabel
        Left = 8
        Top = 17
        Width = 23
        Height = 13
        Caption = 'M'#234's:'
      end
      object Label5: TLabel
        Left = 178
        Top = 17
        Width = 22
        Height = 13
        Caption = 'Ano:'
      end
      object mes_comissao: TComboBox
        Left = 34
        Top = 15
        Width = 100
        Height = 21
        Style = csDropDownList
        DropDownCount = 12
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 0
        Text = 'Janeiro'
        OnChange = mes_comissaoChange
        Items.Strings = (
          'Janeiro'
          'Fevereiro'
          'Mar'#231'o'
          'Abril'
          'Maio'
          'Junho'
          'Julho'
          'Agosto'
          'Setembro'
          'Outubro'
          'Novembro'
          'Dezembro')
      end
      object ano_comissao: TAlignEdit
        Left = 204
        Top = 15
        Width = 55
        Height = 21
        ReadOnly = True
        TabOrder = 1
        Text = '2000'
        OnChange = ano_comissaoChange
        Alignment = taLeftJustify
      end
      object UpDownAno: TUpDown
        Left = 259
        Top = 15
        Width = 16
        Height = 21
        Associate = ano_comissao
        Min = 1900
        Max = 2999
        Position = 2000
        TabOrder = 2
        Thousands = False
        Wrap = False
      end
      object UpDownMes: TUpDown
        Left = 134
        Top = 15
        Width = 16
        Height = 21
        Anchors = [akLeft]
        Associate = mes_comissao
        Min = 0
        Max = 11
        Position = 11
        TabOrder = 3
        TabStop = True
        Thousands = False
        Wrap = False
        OnChangingEx = UpDownMesChangingEx
      end
    end
    object grdReprComissao: TDBGrid
      Left = 0
      Top = 115
      Width = 758
      Height = 273
      Align = alClient
      DataSource = DsReprComissao
      Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgAlwaysShowSelection, dgCancelOnExit]
      PopupMenu = PopupMenu1
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnKeyDown = grdReprComissaoKeyDown
      Columns = <
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
          FieldName = 'valor_base_calculo'
          Title.Alignment = taCenter
          Width = 100
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
          Alignment = taCenter
          Expanded = False
          FieldName = 'data_calculo'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cod_conta_pagar'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end>
    end
    object Panel6: TPanel
      Left = 0
      Top = 388
      Width = 758
      Height = 33
      Align = alBottom
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 3
      object Label12: TLabel
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
        DataField = 'valor_comissao'
        DataSource = DsSumComissao
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
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btUndo: TResBitBtn
      Left = 618
    end
    inherited btSave: TResBitBtn
      Left = 310
    end
    inherited btCancel: TResBitBtn
      Left = 348
    end
    inherited btNew: TResBitBtn
      Left = 694
    end
    inherited btCopy: TResBitBtn
      Left = 580
    end
    inherited btDelete: TResBitBtn
      Left = 386
    end
    inherited btExit: TResBitBtn
      Left = 538
    end
    inherited btajuda: TResBitBtn
      Left = 652
    end
    inherited btExport: TResBitBtn
      Left = 730
    end
    inherited MenuClicks: TPopupMenu
      object execFechamento1: TMenuItem
        Action = execFechamento
        Caption = 'Fechamento'
      end
      object VisualizarImpresso1: TMenuItem
        Action = execRelatorio
        Caption = 'Visualizar Impress'#227'o'
      end
      object execParFormaPagto1: TMenuItem
        Action = execParFormaPagto
        Caption = 'Forma Pagamento'
      end
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = SfgToolbarexecBtEditClickExecute
      end
      inherited execBtUndoClick: TAction
        Visible = False
      end
      inherited execBtSaveClick: TAction
        OnExecute = SfgToolbarexecBtSaveClickExecute
      end
      inherited execBtCancelClick: TAction
        OnExecute = SfgToolbarexecBtCancelClickExecute
      end
      inherited execBtNewClick: TAction
        Enabled = False
        Visible = False
      end
      inherited execBtCopyClick: TAction
        Visible = False
      end
      inherited execBtDeleteClick: TAction
        OnExecute = SfgToolbarexecBtDeleteClickExecute
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object btFechamento: TResBitBtn
    Left = 424
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
  object btParFormaPagto: TResBitBtn
    Left = 500
    Top = 61
    Width = 32
    Height = 32
    Action = execParFormaPagto
    TabOrder = 6
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'ANOTAR'
    GlyphResID = 0
  end
  object btRelatorio: TResBitBtn
    Left = 462
    Top = 61
    Width = 32
    Height = 32
    Action = execRelatorio
    TabOrder = 7
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'RELATORIO'
    GlyphResID = 0
  end
  object QyRepresentantes: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterScroll = QyRepresentantesAfterScroll
    SQL.Strings = (
      
        'SELECT cod_representante,  den_representante, ies_ativo, tipo_pe' +
        'ssoa'
      '  FROM tbl_representante'
      ' ORDER BY cod_representante')
    Params = <>
    Left = 616
    Top = 8
  end
  object DsRepresentantes: TDataSource
    AutoEdit = False
    DataSet = QyRepresentantes
    Left = 656
    Top = 8
  end
  object QyReprComissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    AfterScroll = QyReprComissaoAfterScroll
    CachedUpdates = True
    BeforeInsert = QyReprComissaoBeforeInsert
    SQL.Strings = (
      
        'SELECT cod_pedido_venda, seq_parcela, valor_calculo, perc_comiss' +
        'ao, valor_comissao, '
      
        '       CASE WHEN valor_base_calculo = 1 THEN '#39'Valor Faturado'#39' EL' +
        'SE '#39'Valor Recebido'#39' END valor_base_calculo, '
      '       data_calculo, cod_conta_pagar'
      '  FROM tbl_comissao_representante'
      ' WHERE cod_representante = :cod_representante'
      '   AND mes_comissao = :mes_comissao'
      '   AND ano_comissao = :ano_comissao'
      ' ORDER BY cod_pedido_venda, seq_parcela')
    Params = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = '123456789123456'
      end
      item
        DataType = ftLargeint
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '10'
      end
      item
        DataType = ftLargeint
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
    Left = 348
    Top = 306
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = '123456789123456'
      end
      item
        DataType = ftLargeint
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '10'
      end
      item
        DataType = ftLargeint
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
    object CodPedidoVenda: TIntegerField
      DisplayLabel = 'Pedido Venda'
      FieldName = 'cod_pedido_venda'
    end
    object QyReprComissaoseq_parcela: TIntegerField
      DisplayLabel = 'Parcela'
      FieldName = 'seq_parcela'
    end
    object QyReprComissaovalor_calculo: TFloatField
      DisplayLabel = 'Valor C'#225'lculo'
      FieldName = 'valor_calculo'
      currency = True
    end
    object QyReprComissaoperc_comissao: TFloatField
      DisplayLabel = '% Comiss'#227'o'
      FieldName = 'perc_comissao'
      DisplayFormat = '#0.00'
    end
    object ValorComissao: TFloatField
      DisplayLabel = 'Valor Comiss'#227'o'
      FieldName = 'valor_comissao'
      OnSetText = ValorComissaoSetText
      currency = True
    end
    object QyReprComissaovalor_base_calculo: TStringField
      DisplayLabel = 'Valor Base'
      FieldName = 'valor_base_calculo'
      ReadOnly = True
      Size = 14
    end
    object QyReprComissaodata_calculo: TDateTimeField
      DisplayLabel = 'Data C'#225'lculo'
      FieldName = 'data_calculo'
      DisplayFormat = 'dd/mm/yyyy'
    end
    object QyReprComissaocod_conta_pagar: TIntegerField
      DisplayLabel = 'Conta Pagar'
      FieldName = 'cod_conta_pagar'
      ReadOnly = True
    end
    object QyReprComissaovalor_total: TFloatField
      FieldKind = fkCalculated
      FieldName = 'valor_total'
      Calculated = True
    end
  end
  object DsReprComissao: TDataSource
    AutoEdit = False
    DataSet = QyReprComissao
    Left = 384
    Top = 306
  end
  object ActionList1: TActionList
    Left = 720
    Top = 66
    object execFechamento: TAction
      Enabled = False
      Hint = 
        'Fechamento das comiss'#245'es do representante|efetuando a integra'#231#227'o' +
        ' com o contas a pagar.'
      ShortCut = 16454
      OnExecute = execFechamentoExecute
    end
    object execParFormaPagto: TAction
      Hint = 
        'Indicar a forma de pagamento para ser|utilizada na integra'#231#227'o da' +
        's comiss'#245'es.'
      ShortCut = 16463
      OnExecute = execParFormaPagtoExecute
    end
    object execRelatorio: TAction
      Enabled = False
      Hint = 'Visualiza a impress'#227'o das comiss'#245'es do representante.'
      ShortCut = 16457
      OnExecute = execRelatorioExecute
    end
    object delLine: TAction
      Caption = '&Remover Linha'
      Enabled = False
      ShortCut = 32850
      OnExecute = delLineExecute
    end
  end
  object PopupMenu1: TPopupMenu
    Left = 198
    Top = 294
    object RemoverLinha1: TMenuItem
      Action = delLine
    end
  end
  object QySumComissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    AfterScroll = QyReprComissaoAfterScroll
    CachedUpdates = True
    BeforeInsert = QyReprComissaoBeforeInsert
    SQL.Strings = (
      'SELECT SUM(valor_comissao) valor_comissao'
      '  FROM tbl_comissao_representante'
      ' WHERE cod_representante = :cod_representante'
      '   AND mes_comissao = :mes_comissao'
      '   AND ano_comissao = :ano_comissao')
    Params = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = '123456789123456'
      end
      item
        DataType = ftLargeint
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '10'
      end
      item
        DataType = ftLargeint
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
    Left = 420
    Top = 306
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = '123456789123456'
      end
      item
        DataType = ftLargeint
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '10'
      end
      item
        DataType = ftLargeint
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
    object QySumComissaovalor_comissao: TFloatField
      DisplayWidth = 13
      FieldName = 'valor_comissao'
      currency = True
    end
  end
  object DsSumComissao: TDataSource
    DataSet = QySumComissao
    Left = 450
    Top = 306
  end
end
