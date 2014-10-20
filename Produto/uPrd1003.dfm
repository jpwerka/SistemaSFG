inherited Prd1003: TPrd1003
  Caption = 'Cadastro de Unidades de Medida'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Unidades Medida'
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
        Width = 80
        Height = 13
        Caption = '&Unidade medida:'
        FocusControl = cod_unid_medida
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 214
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_unid_medida
        Transparent = True
        WordWrap = True
      end
      object cod_unid_medida: TDBEdit
        Left = 97
        Top = 15
        Width = 81
        Height = 21
        DataField = 'cod_unid_medida'
        DataSource = DsCadUnidMedida
        TabOrder = 0
      end
      object den_unid_medida: TDBEdit
        Left = 287
        Top = 15
        Width = 244
        Height = 21
        DataField = 'den_unid_medida'
        DataSource = DsCadUnidMedida
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadUnidMedida: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_unid_medida, den_unid_medida'
      '  FROM tbl_unid_medida'
      ' ORDER BY cod_unid_medida')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadUnidMedida: TDataSource
    AutoEdit = False
    DataSet = QyCadUnidMedida
    Left = 703
    Top = 6
  end
end
