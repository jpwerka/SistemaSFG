inherited Vdp3011: TVdp3011
  Left = 470
  Top = 147
  Caption = 'Consulta de Produtos x Venda'
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
    Caption = 'Consulta Produtos x Venda'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    TabOrder = 2
    object gbFiltros: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 145
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
        Left = 17
        Top = 90
        Width = 63
        Height = 13
        Alignment = taRightJustify
        Caption = '&Forma Pagto:'
        FocusControl = forma_pagto
        Transparent = True
      end
      object Label5: TLabel
        Left = 40
        Top = 114
        Width = 40
        Height = 13
        Alignment = taRightJustify
        Caption = '&Produto:'
        FocusControl = cod_produto_ini
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
        FocusControl = den_forma_pagto
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
      object Label6: TLabel
        Left = 235
        Top = 114
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
      object forma_pagto: TEdit
        Left = 85
        Top = 87
        Width = 110
        Height = 21
        TabOrder = 10
        OnExit = forma_pagtoExit
      end
      object btPesqFormaPagto: TResBitBtn
        Left = 200
        Top = 86
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de formas de pagamento.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 11
        TabStop = False
        OnClick = btPesqFormaPagtoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_forma_pagto: TEdit
        Left = 227
        Top = 87
        Width = 390
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 12
      end
      object cod_produto_ini: TEdit
        Left = 85
        Top = 111
        Width = 110
        Height = 21
        TabOrder = 13
      end
      object btPesqProdutoIni: TResBitBtn
        Left = 200
        Top = 110
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 14
        TabStop = False
        OnClick = btPesqProdutoIniClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_produto_fim: TEdit
        Left = 257
        Top = 111
        Width = 110
        Height = 21
        TabOrder = 15
      end
      object btPesqProdutoFim: TResBitBtn
        Left = 372
        Top = 110
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 16
        TabStop = False
        OnClick = btPesqProdutoFimClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
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
        'Visualiza a listagem dos pedidos de venda de |acordo com o agrup' +
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
