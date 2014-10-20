inherited Obf1002: TObf1002
  Caption = 'Cadastro de Natureza Opera'#231#227'o'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Natureza Opera'#231#227'o'
  end
  inherited BodyPanel: TPanel
    object gbCadastro: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 42
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 11
        Top = 17
        Width = 36
        Height = 13
        Caption = '&C'#243'digo:'
        FocusControl = cod_natureza_operacao
        Transparent = True
      end
      object Label2: TLabel
        Left = 136
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_natureza_operacao
        Transparent = True
        WordWrap = True
      end
      object cod_natureza_operacao: TDBEdit
        Left = 51
        Top = 15
        Width = 51
        Height = 21
        DataField = 'cod_natureza_operacao'
        DataSource = DsNaturezaOperacao
        TabOrder = 0
      end
      object den_natureza_operacao: TDBEdit
        Left = 209
        Top = 15
        Width = 299
        Height = 21
        DataField = 'den_natureza_operacao'
        DataSource = DsNaturezaOperacao
        TabOrder = 1
      end
    end
    object gbInformacao: TGroupBox
      Left = 0
      Top = 42
      Width = 758
      Height = 139
      Cursor = crArrow
      Align = alTop
      Caption = 'Informa'#231#245'es'
      TabOrder = 1
      object Label4: TLabel
        Left = 21
        Top = 41
        Width = 90
        Height = 13
        Alignment = taRightJustify
        Caption = 'CST &ICMS Padr'#227'o:'
      end
      object Label3: TLabel
        Left = 43
        Top = 17
        Width = 68
        Height = 13
        Alignment = taRightJustify
        Caption = 'C&FOP Padr'#227'o:'
      end
      object Label5: TLabel
        Left = 34
        Top = 65
        Width = 77
        Height = 13
        Alignment = taRightJustify
        Caption = 'CST I&PI Padr'#227'o:'
      end
      object Label6: TLabel
        Left = 30
        Top = 89
        Width = 81
        Height = 13
        Alignment = taRightJustify
        Caption = 'CST PI&S Padr'#227'o:'
      end
      object Label7: TLabel
        Left = 8
        Top = 113
        Width = 103
        Height = 13
        Alignment = taRightJustify
        Caption = 'CST C&OFINS Padr'#227'o:'
      end
      object Label8: TLabel
        Left = 316
        Top = 18
        Width = 40
        Height = 13
        Alignment = taRightJustify
        Caption = '% ICMS:'
      end
      object cod_cst_icms_padrao: TDBDataComboBox
        Left = 114
        Top = 39
        Width = 635
        Height = 21
        DataField = 'cod_cst_icms_padrao'
        DataSource = DsNaturezaOperacao
        ItemHeight = 13
        TabOrder = 0
      end
      object cod_cst_ipi_padrao: TDBDataComboBox
        Left = 114
        Top = 63
        Width = 635
        Height = 21
        DataField = 'cod_cst_ipi_padrao'
        DataSource = DsNaturezaOperacao
        ItemHeight = 13
        TabOrder = 1
      end
      object cod_cst_pis_padrao: TDBDataComboBox
        Left = 114
        Top = 87
        Width = 635
        Height = 21
        DataField = 'cod_cst_pis_padrao'
        DataSource = DsNaturezaOperacao
        ItemHeight = 13
        TabOrder = 2
      end
      object cod_cst_cofins_padrao: TDBDataComboBox
        Left = 114
        Top = 111
        Width = 635
        Height = 21
        DataField = 'cod_cst_cofins_padrao'
        DataSource = DsNaturezaOperacao
        ItemHeight = 13
        TabOrder = 3
      end
      object cod_cfop_padrao: TDBEdit
        Left = 114
        Top = 15
        Width = 85
        Height = 21
        DataField = 'cod_cfop_padrao'
        DataSource = DsNaturezaOperacao
        TabOrder = 4
      end
      object percentual_icms: TDBEdit
        Left = 360
        Top = 15
        Width = 85
        Height = 21
        DataField = 'percentual_icms'
        DataSource = DsNaturezaOperacao
        TabOrder = 5
        OnKeyPress = percentual_icmsKeyPress
      end
    end
    object gbInfoCompl: TGroupBox
      Left = 0
      Top = 181
      Width = 758
      Height = 130
      Align = alTop
      Caption = 'Informa'#231#245'es Complementares'
      TabOrder = 2
      object info_complementar: TDBMemo
        Left = 6
        Top = 15
        Width = 700
        Height = 108
        DataField = 'info_complementar'
        DataSource = DsNaturezaOperacao
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
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyNaturezaOperacao: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_natureza_operacao, den_natureza_operacao, cod_cfop_pa' +
        'drao,      '
      
        '       cod_cst_icms_padrao, cod_cst_ipi_padrao, cod_cst_pis_padr' +
        'ao,'
      '       cod_cst_cofins_padrao, percentual_icms, info_complementar'
      '  FROM tbl_natureza_operacao'
      ' ORDER BY cod_natureza_operacao')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsNaturezaOperacao: TDataSource
    AutoEdit = False
    DataSet = QyNaturezaOperacao
    Left = 703
    Top = 6
  end
end
