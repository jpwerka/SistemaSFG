inherited Prd1001: TPrd1001
  Left = 402
  Top = 158
  Caption = 'Cadastro de Produtos'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Produtos'
  end
  inherited BodyPanel: TPanel
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 40
        Height = 13
        Caption = '&Produto:'
        FocusControl = cod_produto
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 219
        Top = 17
        Width = 37
        Height = 13
        Caption = '&Fam'#237'lia:'
        FocusControl = cod_familia
        Transparent = True
        WordWrap = True
      end
      object Label3: TLabel
        Left = 8
        Top = 41
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_produto
        Transparent = True
        WordWrap = True
      end
      object Label7: TLabel
        Left = 522
        Top = 42
        Width = 20
        Height = 13
        Caption = '&UM:'
        FocusControl = cod_unid_medida
      end
      object cod_produto: TDBEdit
        Left = 52
        Top = 15
        Width = 110
        Height = 21
        DataField = 'cod_produto'
        DataSource = DsProduto
        TabOrder = 0
      end
      object cod_familia: TDBDataComboBox
        Left = 260
        Top = 15
        Width = 203
        Height = 21
        DataField = 'cod_familia'
        DataSource = DsProduto
        ItemHeight = 13
        TabOrder = 1
        LookUpDataSet = QyFamilia
        LookUpField = 'cod_familia'
        ResultField = 'den_familia'
      end
      object ies_ativo: TDBCheckBox
        Left = 546
        Top = 17
        Width = 50
        Height = 14
        Caption = '&Ativo?'
        DataField = 'ies_ativo'
        DataSource = DsProduto
        TabOrder = 2
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
      object den_produto: TDBEdit
        Left = 81
        Top = 39
        Width = 436
        Height = 21
        DataField = 'den_produto'
        DataSource = DsProduto
        TabOrder = 3
      end
      object cod_unid_medida: TDBDataComboBox
        Left = 545
        Top = 39
        Width = 47
        Height = 21
        Style = csDropDownList
        DataField = 'cod_unid_medida'
        DataSource = DsProduto
        ItemHeight = 13
        Sorted = True
        TabOrder = 4
        LookUpDataSet = QyCnsUnidMedida
        LookUpField = 'cod_unid_medida'
        ResultField = 'cod_unid_medida'
      end
    end
    object pgDetItem: TPageControl
      Left = 0
      Top = 67
      Width = 750
      Height = 350
      ActivePage = TabSheet5
      Align = alClient
      TabIndex = 3
      TabOrder = 1
      object TabSheet1: TTabSheet
        Caption = '&1 - Geral'
        object DBRadioGroup1: TDBRadioGroup
          Left = 6
          Top = 6
          Width = 161
          Height = 37
          Caption = 'Tipo Item'
          Columns = 2
          DataField = 'ies_tipo_produto'
          DataSource = DsProduto
          Items.Strings = (
            'Produto'
            'Servi'#231'o')
          TabOrder = 0
          TabStop = True
          Values.Strings = (
            'P'
            'S')
        end
      end
      object TabSheet4: TTabSheet
        Caption = '&2 - Estoque'
        ImageIndex = 3
        object Label4: TLabel
          Left = 7
          Top = 29
          Width = 62
          Height = 13
          Caption = 'Qtd &Estoque:'
          FocusControl = qtd_estoque
        end
        object Label5: TLabel
          Left = 178
          Top = 29
          Width = 79
          Height = 13
          Caption = 'Estoque &m'#237'nimo:'
          FocusControl = qtd_estoque_min
        end
        object qtd_estoque: TDBEdit
          Left = 72
          Top = 27
          Width = 94
          Height = 21
          DataField = 'qtd_estoque'
          DataSource = DsProduto
          TabOrder = 0
        end
        object qtd_estoque_min: TDBEdit
          Left = 260
          Top = 27
          Width = 93
          Height = 21
          DataField = 'qtd_estoque_min'
          DataSource = DsProduto
          TabOrder = 1
        end
        object DBCheckBox1: TDBCheckBox
          Left = 72
          Top = 6
          Width = 109
          Height = 14
          Caption = '&Controla Estoque?'
          DataField = 'ies_ativo'
          DataSource = DsProduto
          TabOrder = 2
          ValueChecked = 'S'
          ValueUnchecked = 'N'
        end
      end
      object TabSheet2: TTabSheet
        Caption = '&3 - Valores'
        ImageIndex = 1
        object Label6: TLabel
          Left = 48
          Top = 8
          Width = 60
          Height = 13
          Caption = 'Pre'#231'o &custo:'
          FocusControl = preco_custo
        end
        object Label8: TLabel
          Left = 44
          Top = 32
          Width = 64
          Height = 13
          Caption = 'Pre'#231'o &venda:'
          FocusControl = preco_venda
        end
        object Label9: TLabel
          Left = 8
          Top = 56
          Width = 100
          Height = 13
          Caption = #218'ltimo pre'#231'o compra:'
          FocusControl = preco_compra
        end
        object preco_custo: TDBEdit
          Left = 112
          Top = 6
          Width = 93
          Height = 21
          DataField = 'preco_custo'
          DataSource = DsProduto
          TabOrder = 0
        end
        object preco_venda: TDBEdit
          Left = 112
          Top = 30
          Width = 93
          Height = 21
          DataField = 'preco_venda'
          DataSource = DsProduto
          TabOrder = 1
        end
        object preco_compra: TDBEdit
          Left = 112
          Top = 54
          Width = 93
          Height = 21
          DataField = 'preco_compra'
          DataSource = DsProduto
          TabOrder = 2
        end
      end
      object TabSheet5: TTabSheet
        Caption = '&4 - Fiscal'
        ImageIndex = 4
        object Label10: TLabel
          Left = 72
          Top = 9
          Width = 27
          Height = 13
          Caption = '&NCM:'
          FocusControl = cod_ncm
        end
        object Label11: TLabel
          Left = 7
          Top = 33
          Width = 92
          Height = 13
          Caption = '&Origem Mercadoria:'
          FocusControl = origem_mercadoria
        end
        object Label12: TLabel
          Left = 59
          Top = 57
          Width = 40
          Height = 13
          Caption = 'E&X TIPI:'
          FocusControl = cod_extipi
        end
        object Label13: TLabel
          Left = 184
          Top = 57
          Width = 50
          Height = 13
          Caption = '&Classe IPI:'
          FocusControl = classe_enq_ipi
        end
        object Label14: TLabel
          Left = 346
          Top = 57
          Width = 52
          Height = 13
          Caption = 'C'#243'&digo IPI:'
          FocusControl = cod_enq_ipi
        end
        object cod_ncm: TDBEdit
          Left = 103
          Top = 6
          Width = 108
          Height = 21
          DataField = 'cod_ncm'
          DataSource = DsProduto
          TabOrder = 0
        end
        object origem_mercadoria: TDBDataComboBox
          Left = 103
          Top = 30
          Width = 634
          Height = 21
          DataField = 'origem_mercadoria'
          DataSource = DsProduto
          ItemHeight = 13
          TabOrder = 1
        end
        object cod_extipi: TDBEdit
          Left = 103
          Top = 54
          Width = 43
          Height = 21
          DataField = 'cod_extipi'
          DataSource = DsProduto
          TabOrder = 2
        end
        object classe_enq_ipi: TDBEdit
          Left = 238
          Top = 54
          Width = 69
          Height = 21
          DataField = 'classe_enq_ipi'
          DataSource = DsProduto
          TabOrder = 3
        end
        object cod_enq_ipi: TDBEdit
          Left = 402
          Top = 54
          Width = 43
          Height = 21
          DataField = 'cod_enq_ipi'
          DataSource = DsProduto
          TabOrder = 4
        end
      end
      object TabSheet3: TTabSheet
        Caption = '&5 - Observa'#231#245'es'
        ImageIndex = 2
        object observacoes: TDBMemo
          Left = 6
          Top = 6
          Width = 587
          Height = 128
          Align = alCustom
          DataField = 'observacao'
          DataSource = DsProduto
          Font.Charset = DEFAULT_CHARSET
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
  end
  object QyProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_produto, den_produto, ies_ativo, cod_familia, cod_uni' +
        'd_medida,'
      
        '       controla_estoque, qtd_estoque, qtd_estoque_min, preco_cus' +
        'to, preco_venda, preco_compra,'
      '        ies_tipo_produto, cod_ncm, origem_mercadoria,'
      '        cod_extipi,classe_enq_ipi,cod_enq_ipi, observacao'
      '  FROM tbl_produto'
      ' ORDER BY cod_produto')
    Params = <>
    Left = 616
    Top = 8
  end
  object DsProduto: TDataSource
    AutoEdit = False
    DataSet = QyProduto
    Left = 656
    Top = 8
  end
  object QyCnsUnidMedida: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_unid_medida'
      '  FROM tbl_unid_medida')
    Params = <>
    Left = 582
    Top = 8
  end
  object QyFamilia: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_familia, den_familia'
      '  FROM tbl_familia'
      ' ORDER BY cod_familia')
    Params = <>
    Left = 546
    Top = 8
  end
end
