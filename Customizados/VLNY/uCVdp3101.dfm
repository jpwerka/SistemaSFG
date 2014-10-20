inherited CVdp3101: TCVdp3101
  Caption = 'Consulta de Amostragem x Representante'
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
    Caption = 'Amostragem x Representante'
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
      object Label2: TLabel
        Left = 10
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
        Left = 8
        Top = 42
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
      object cod_representante: TEdit
        Left = 85
        Top = 39
        Width = 110
        Height = 21
        TabOrder = 4
        OnExit = cod_representanteExit
      end
      object btPesqRepresentante: TResBitBtn
        Left = 200
        Top = 38
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de representantes.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        TabStop = False
        OnClick = btPesqRepresentanteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_representante: TEdit
        Left = 227
        Top = 39
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 6
      end
      object gbSituacao: TGroupBox
        Left = 8
        Top = 64
        Width = 251
        Height = 38
        Caption = '&Situa'#231#227'o'
        TabOrder = 7
        object ckAberto: TCheckBox
          Left = 8
          Top = 15
          Width = 61
          Height = 17
          Caption = 'Aberto'
          Checked = True
          State = cbChecked
          TabOrder = 0
        end
        object ckFechado: TCheckBox
          Left = 88
          Top = 15
          Width = 67
          Height = 17
          Caption = 'Fechado'
          Checked = True
          State = cbChecked
          TabOrder = 1
        end
        object ckCancelado: TCheckBox
          Left = 168
          Top = 15
          Width = 74
          Height = 17
          Caption = 'Cancelado'
          Checked = True
          State = cbChecked
          TabOrder = 2
        end
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
        'Visualiza a listagem dos pedidos de venda para amostragem|com os' +
        ' representantes de acordo com as op'#231#245'es escolhidas.'
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
