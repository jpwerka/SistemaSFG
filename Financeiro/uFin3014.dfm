inherited Fin3014: TFin3014
  Caption = 'Consulta de Recebimento x Cliente'
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
    Caption = 'Recebimento x Cliente'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    TabOrder = 2
    object gbFiltros: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 109
      Align = alTop
      Caption = 'Filtros'
      TabOrder = 0
      object Label1: TLabel
        Left = 59
        Top = 42
        Width = 35
        Height = 13
        Caption = '&Cliente:'
        FocusControl = cod_cliente
      end
      object Label2: TLabel
        Left = 9
        Top = 18
        Width = 85
        Height = 13
        Caption = '&Data Vencimento:'
        FocusControl = data_ini
      end
      object Label12: TLabel
        Left = 201
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
        Left = 99
        Top = 15
        Width = 85
        Height = 21
        EditMask = '99/99/9999;0;_'
        MaxLength = 10
        TabOrder = 0
        OnExit = data_iniExit
      end
      object btCalendar01: TCustomImgButton
        Left = 166
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
        Left = 222
        Top = 15
        Width = 85
        Height = 21
        EditMask = '99/99/9999;0;_'
        MaxLength = 10
        TabOrder = 2
        OnExit = data_fimExit
      end
      object btCalendar02: TCustomImgButton
        Left = 289
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
        Left = 99
        Top = 39
        Width = 110
        Height = 21
        TabOrder = 4
        OnExit = cod_clienteExit
      end
      object btPesqCliente: TResBitBtn
        Left = 213
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
        Left = 240
        Top = 39
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 6
      end
      object gbSituacao: TRadioGroup
        Left = 8
        Top = 65
        Width = 347
        Height = 38
        Caption = '&Situa'#231#227'o Parcela'
        Columns = 4
        ItemIndex = 0
        Items.Strings = (
          'Todas'
          'Recebida'
          'Pendente'
          'Em Atraso')
        TabOrder = 7
      end
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
    TabOrder = 1
    object btRelatorio: TResBitBtn
      Left = 6
      Top = 6
      Width = 32
      Height = 32
      Hint = 
        'Visualiza a listagem das contas '#224' receber| x parcelas de acordo ' +
        'com as op'#231#245'es escolhidas.'
      TabOrder = 0
      OnClick = btRelatorioClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'RELATORIO'
      GlyphResID = 0
    end
    object btExit: TResBitBtn
      Left = 44
      Top = 6
      Width = 32
      Height = 32
      Hint = 'Fechar Formul'#225'rio'
      Cancel = True
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = btExitClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'SAIR'
      GlyphResID = 0
    end
  end
end
