inherited Fin3007: TFin3007
  Caption = 'Consulta de Contas '#224' Receber'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel2: TBevel [1]
    Left = 0
    Top = 101
    Width = 766
    Height = 2
    Align = alTop
    Shape = bsTopLine
  end
  inherited HeaderPanel: TPanel
    Caption = 'Consulta Contas '#224' Receber'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 406
    TabOrder = 2
    object gbFiltros: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 191
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
      object Label4: TLabel
        Left = 8
        Top = 66
        Width = 72
        Height = 13
        Alignment = taRightJustify
        Caption = 'Co&nta Cont'#225'bil:'
        FocusControl = cod_plano_conta_ini
        Transparent = True
      end
      object Label5: TLabel
        Left = 16
        Top = 90
        Width = 64
        Height = 13
        Alignment = taRightJustify
        Caption = 'Centro C&usto:'
        FocusControl = cod_centro_custo_ini
        Transparent = True
      end
      object Label3: TLabel
        Left = 235
        Top = 66
        Width = 18
        Height = 13
        Cursor = crArrow
        Caption = 'at'#233':'
        DragCursor = crDefault
        FocusControl = cod_plano_conta_fim
        Transparent = True
      end
      object Label6: TLabel
        Left = 235
        Top = 90
        Width = 18
        Height = 13
        Cursor = crArrow
        Caption = 'at'#233':'
        DragCursor = crDefault
        FocusControl = cod_centro_custo_fim
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
      object cod_plano_conta_ini: TEdit
        Left = 85
        Top = 63
        Width = 110
        Height = 21
        TabOrder = 7
      end
      object btPesqPlanoContaIni: TResBitBtn
        Left = 200
        Top = 62
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de plano de contas.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 8
        TabStop = False
        OnClick = btPesqPlanoContaIniClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_plano_conta_fim: TEdit
        Left = 257
        Top = 63
        Width = 110
        Height = 21
        TabOrder = 9
      end
      object btPesqPlanoContaFim: TResBitBtn
        Left = 372
        Top = 62
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de plano de contas.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 10
        TabStop = False
        OnClick = btPesqPlanoContaFimClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_centro_custo_ini: TEdit
        Left = 85
        Top = 87
        Width = 110
        Height = 21
        TabOrder = 11
      end
      object btPesqCentroCustoIni: TResBitBtn
        Left = 200
        Top = 86
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de centros de custo.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 12
        TabStop = False
        OnClick = btPesqCentroCustoIniClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_centro_custo_fim: TEdit
        Left = 257
        Top = 87
        Width = 110
        Height = 21
        TabOrder = 13
      end
      object btPesqCentroCustoFim: TResBitBtn
        Left = 372
        Top = 86
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de centros de custo.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 14
        TabStop = False
        OnClick = btPesqCentroCustoFimClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object rbAgrupamento: TRadioGroup
        Left = 8
        Top = 147
        Width = 421
        Height = 38
        Caption = '&Agrupar por:'
        Columns = 4
        ItemIndex = 0
        Items.Strings = (
          'Cliente'
          'Situa'#231#227'o'
          'Conta Cont'#225'bil'
          'Centro Custo')
        TabOrder = 15
      end
      object gbSituacao: TGroupBox
        Left = 8
        Top = 109
        Width = 371
        Height = 38
        Caption = '&Situa'#231#227'o'
        TabOrder = 16
        object ckPendente: TCheckBox
          Left = 8
          Top = 15
          Width = 70
          Height = 17
          Caption = 'Pendente'
          Checked = True
          State = cbChecked
          TabOrder = 0
        end
        object ckAndamento: TCheckBox
          Left = 100
          Top = 15
          Width = 75
          Height = 17
          Caption = 'Andamento'
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
        object ckLiquidado: TCheckBox
          Left = 192
          Top = 15
          Width = 73
          Height = 17
          Caption = 'Liquidado'
          Checked = True
          State = cbChecked
          TabOrder = 2
        end
        object ckCancelado: TCheckBox
          Left = 286
          Top = 15
          Width = 74
          Height = 17
          Caption = 'Cancelado'
          Checked = True
          State = cbChecked
          TabOrder = 3
        end
      end
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 406
    TabOrder = 3
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 406
    TabOrder = 4
  end
  object SfgToolbar: TPanel
    Left = 0
    Top = 55
    Width = 766
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
        'Visualiza a listagem das contas '#224' receber de |acordo com o agrup' +
        'amento e as op'#231#245'es escolhidas.'
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
