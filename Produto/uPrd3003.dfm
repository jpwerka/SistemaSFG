inherited Prd3003: TPrd3003
  Caption = 'Consulta de Estoque'
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
    Caption = 'Consulta Estoque'
  end
  inherited BodyPanel: TPanel
    Top = 103
    Height = 417
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Filtros'
      TabOrder = 0
      object Label4: TLabel
        Left = 8
        Top = 42
        Width = 40
        Height = 13
        Caption = '&Produto:'
        FocusControl = cod_produto_ini
        Transparent = True
        WordWrap = True
      end
      object Label1: TLabel
        Left = 11
        Top = 18
        Width = 37
        Height = 13
        Caption = '&Fam'#237'lia:'
        FocusControl = cod_familia
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 216
        Top = 42
        Width = 18
        Height = 13
        Alignment = taRightJustify
        Caption = 'a&t'#233':'
        FocusControl = cod_produto_fim
        Transparent = True
        WordWrap = True
      end
      object den_familia: TEdit
        Left = 184
        Top = 15
        Width = 270
        Height = 21
        TabStop = False
        ReadOnly = True
        TabOrder = 2
      end
      object cod_familia: TEdit
        Left = 54
        Top = 15
        Width = 97
        Height = 21
        TabOrder = 0
        OnExit = cod_familiaExit
      end
      object btSearchFamilia: TResBitBtn
        Left = 156
        Top = 14
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de fam'#237'lias.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btSearchFamiliaClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_produto_ini: TEdit
        Left = 54
        Top = 39
        Width = 110
        Height = 21
        TabOrder = 3
      end
      object btSearchProdutoIni: TResBitBtn
        Left = 168
        Top = 38
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        TabStop = False
        OnClick = btSearchProdutoIniClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object cod_produto_fim: TEdit
        Left = 237
        Top = 39
        Width = 110
        Height = 21
        TabOrder = 5
      end
      object btSearchProdutoFim: TResBitBtn
        Left = 351
        Top = 38
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de produtos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 6
        TabStop = False
        OnClick = btSearchProdutoFimClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 42
      Align = alTop
      Caption = 'Quantidade em estoque'
      TabOrder = 1
      object Independente: TRadioButton
        Left = 7
        Top = 17
        Width = 157
        Height = 14
        Hint = 'Mostra todos os registros de produtos.'
        Caption = 'Independente da Quantidade'
        Checked = True
        TabOrder = 0
        TabStop = True
      end
      object Abaixo: TRadioButton
        Left = 187
        Top = 17
        Width = 146
        Height = 14
        Hint = 
          'Mostra apenas os registros de produtos |que estejam abaixo do es' +
          'toque m'#237'nimo.'
        Caption = 'Abaixo do Estoque M'#237'nimo'
        TabOrder = 1
      end
    end
  end
  inherited MargemEsq: TPanel
    Top = 103
    Height = 417
  end
  inherited MargemDir: TPanel
    Top = 103
    Height = 417
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
    TabOrder = 4
    object btRelatorio: TResBitBtn
      Left = 6
      Top = 6
      Width = 32
      Height = 32
      Hint = 
        'Visualiza a listagem de estoque de|acordo com as op'#231#245'es escolhid' +
        'as.'
      TabOrder = 0
      OnClick = BtOKClick
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
      OnClick = BtCancelClick
      NumGlyphs = 4
      GlyphLoadType = glByResName
      GlyphResName = 'SAIR'
      GlyphResID = 0
    end
  end
  object ActionList1: TActionList
    Left = 696
    Top = 60
    object execPesquisa: TAction
      Caption = 'execPesquisa'
      ShortCut = 16465
      OnExecute = execPesquisaExecute
    end
  end
end
