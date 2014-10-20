inherited Fin1007: TFin1007
  Caption = 'Baixa em Lote Contas '#224' Receber'
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
    Caption = 'Baixa Contas '#224' Receber'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 384
    object Label5: TLabel
      Left = 0
      Top = 67
      Width = 758
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object gbFiltros: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
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
        Left = 21
        Top = 18
        Width = 59
        Height = 13
        Caption = '&Vencimento:'
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
        Left = 199
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
        Left = 226
        Top = 39
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 6
      end
      object btAtualiza: TResBitBtn
        Left = 651
        Top = 37
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
        TabOrder = 7
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
    end
    object grdParcelas: TDBGrid
      Left = 0
      Top = 73
      Width = 758
      Height = 311
      Align = alClient
      Ctl3D = True
      DataSource = DsAtuCtaRec
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
      ParentCtl3D = False
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnColEnter = grdParcelasColEnter
      OnColExit = grdParcelasColExit
      OnDrawColumnCell = grdParcelasDrawColumnCell
      OnKeyDown = grdParcelasKeyDown
      OnMouseUp = grdParcelasMouseUp
      Columns = <
        item
          Expanded = False
          FieldName = 'ies_recebido'
          ReadOnly = True
          Title.Alignment = taCenter
          Width = 20
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cod_cliente'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'den_cliente'
          Width = 300
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cod_conta_receber'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'seq_parcela'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'data_vencimento'
          Title.Alignment = taCenter
          Width = 100
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
          Expanded = False
          FieldName = 'valor_recebido'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlue
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end>
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 384
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 384
  end
  object SfgToolbar: TPanel
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
    TabOrder = 4
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
  object Panel6: TPanel
    Left = 0
    Top = 487
    Width = 774
    Height = 33
    Align = alBottom
    BevelOuter = bvNone
    ParentColor = True
    TabOrder = 5
    object Label3: TLabel
      Left = 268
      Top = 8
      Width = 113
      Height = 16
      Caption = 'Total Recebido:'
      FocusControl = valor_total
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 8
      Top = 8
      Width = 105
      Height = 16
      Caption = 'Total Receber:'
      FocusControl = valor_recebto
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object valor_total: TAlignEdit
      Left = 386
      Top = 5
      Width = 113
      Height = 24
      TabStop = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      Text = 'R$ 0,00'
      Alignment = taRightJustify
    end
    object valor_recebto: TAlignEdit
      Left = 118
      Top = 5
      Width = 113
      Height = 24
      TabStop = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clGreen
      Font.Height = -15
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      Text = 'R$ 0,00'
      Alignment = taRightJustify
    end
  end
  object ActionList1: TActionList
    Left = 708
    Top = 66
    object execInformar: TAction
      Hint = 'Informa os filtros para a baixa|das contas a receber pendentes'
      ShortCut = 16457
      OnExecute = btInformarClick
    end
    object execProcessar: TAction
      Hint = 
        'Processa a atualiza'#231#227'o da baixa das contas|a receber com base no' +
        's dados informados'
      ShortCut = 16464
      OnExecute = btProcessarClick
    end
    object execConfirmar: TAction
      Hint = 'Confirma os dados informados'
      ShortCut = 16467
      OnExecute = btConfirmarClick
    end
    object execCancelar: TAction
      Hint = 'Cancela a informa'#231#227'o dos dados'
      ShortCut = 16472
      OnExecute = btCancelarClick
    end
    object execAtualizar: TAction
      Caption = 'At&ualizar'
      Hint = 'Carrega a lista de contas a receber pendentes'
      ShortCut = 16469
      OnExecute = btAtualizaClick
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
  object QyCnsCtaRec: TZQuery
    Connection = SfgDataCenter.AppConnection
    CachedUpdates = True
    BeforeInsert = QyCnsCtaRecBeforeInsert
    SQL.Strings = (
      'SELECT '#39'S'#39' ies_recebido, cr.cod_cliente, cl.den_cliente,'
      '       crp.cod_conta_receber, crp.seq_parcela,'
      
        '       crp.data_vencimento, crp.valor_parcela, crp.valor_parcela' +
        ' valor_recebido'
      '  FROM tbl_conta_receber cr'
      ' INNER JOIN tbl_conta_receber_pagto crp'
      '    ON cr.cod_conta_receber = crp.cod_conta_receber'
      ' INNER JOIN tbl_cliente cl'
      '    ON cl.cod_cliente = cr.cod_cliente'
      ' WHERE crp.ies_recebido = '#39'N'#39
      '   AND 1=0;')
    Params = <>
    Left = 366
    Top = 258
    object QyCnsCtaRecies_recebido: TStringField
      DisplayLabel = 'X'
      FieldName = 'ies_recebido'
      Size = 1
    end
    object QyCnsCtaReccod_cliente: TStringField
      DisplayLabel = 'Cliente'
      FieldName = 'cod_cliente'
      ReadOnly = True
      Required = True
      Size = 15
    end
    object QyCnsCtaRecden_cliente: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_cliente'
      ReadOnly = True
      Required = True
      Size = 50
    end
    object QyCnsCtaReccod_conta_receber: TIntegerField
      DisplayLabel = 'Conta Receber'
      FieldName = 'cod_conta_receber'
      ReadOnly = True
      Required = True
    end
    object QyCnsCtaRecseq_parcela: TIntegerField
      DisplayLabel = 'Parcela'
      FieldName = 'seq_parcela'
      ReadOnly = True
      Required = True
    end
    object QyCnsCtaRecdata_vencimento: TDateTimeField
      DisplayLabel = 'Data Vencimento'
      FieldName = 'data_vencimento'
      ReadOnly = True
      DisplayFormat = 'dd/mm/yyyy'
    end
    object QyCnsCtaRecvalor_parcela: TFloatField
      DisplayLabel = 'Valor Parcela'
      FieldName = 'valor_parcela'
      ReadOnly = True
      currency = True
    end
    object QyCnsCtaRecvalor_recebido: TFloatField
      DisplayLabel = 'Valor Recebido'
      FieldName = 'valor_recebido'
      OnSetText = ValorRecebidoSetText
      currency = True
    end
  end
  object DsAtuCtaRec: TDataSource
    AutoEdit = False
    DataSet = QyCnsCtaRec
    Left = 402
    Top = 258
  end
end
