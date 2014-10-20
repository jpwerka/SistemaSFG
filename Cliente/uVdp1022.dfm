inherited Vdp1022: TVdp1022
  Caption = 'Cadastro de Cidades'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Cidades'
  end
  inherited BodyPanel: TPanel
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 17
        Width = 36
        Height = 13
        Caption = '&Cidade:'
        FocusControl = cod_cidade
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 134
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_cidade
        Transparent = True
        WordWrap = True
      end
      object Label5: TLabel
        Left = 8
        Top = 41
        Width = 36
        Height = 13
        Caption = '&Estado:'
        FocusControl = cod_uf
        Transparent = True
      end
      object Label4: TLabel
        Left = 140
        Top = 41
        Width = 64
        Height = 13
        Caption = 'C'#243'digo &IBGE:'
        FocusControl = cod_ibge
      end
      object cod_cidade: TDBEdit
        Left = 48
        Top = 15
        Width = 73
        Height = 21
        CharCase = ecUpperCase
        DataField = 'cod_cidade'
        DataSource = DsCadCidade
        TabOrder = 0
      end
      object den_cidade: TDBEdit
        Left = 207
        Top = 15
        Width = 299
        Height = 21
        DataField = 'den_cidade'
        DataSource = DsCadCidade
        TabOrder = 1
      end
      object cod_uf: TDBComboBox
        Left = 48
        Top = 39
        Width = 40
        Height = 21
        Hint = 'Duplo clique ou pressione '#39'+'#39'|para cadastrar um novo estado.'
        DataField = 'cod_uf'
        DataSource = DsCadCidade
        ItemHeight = 13
        TabOrder = 2
      end
      object cod_ibge: TDBEdit
        Left = 207
        Top = 39
        Width = 90
        Height = 21
        DataField = 'cod_ibge'
        DataSource = DsCadCidade
        TabOrder = 3
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadCidade: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cidade, den_cidade, cod_uf, cod_ibge'
      '  FROM tbl_cidade'
      ' ORDER BY cod_cidade')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadCidade: TDataSource
    AutoEdit = False
    DataSet = QyCadCidade
    Left = 703
    Top = 6
  end
end
