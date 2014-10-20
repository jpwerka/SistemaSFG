inherited Vdp1025: TVdp1025
  Caption = 'Cadastro de Classifica'#231#227'o Cliente'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Classifica'#231#227'o Cliente'
  end
  inherited BodyPanel: TPanel
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 42
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 13
        Top = 17
        Width = 36
        Height = 13
        Caption = '&C'#243'digo:'
        FocusControl = cod_classificacao
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 155
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_classificacao
        Transparent = True
        WordWrap = True
      end
      object cod_classificacao: TDBEdit
        Left = 53
        Top = 15
        Width = 70
        Height = 21
        DataField = 'cod_classificacao'
        DataSource = DsClassCliente
        TabOrder = 0
      end
      object den_classificacao: TDBEdit
        Left = 228
        Top = 15
        Width = 299
        Height = 21
        DataField = 'den_classificacao'
        DataSource = DsClassCliente
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyClassCliente: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_classificacao, den_classificacao'
      '  FROM tbl_class_cliente'
      ' ORDER BY cod_classificacao')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsClassCliente: TDataSource
    AutoEdit = False
    DataSet = QyClassCliente
    Left = 703
    Top = 6
  end
end
