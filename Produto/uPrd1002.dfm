inherited Prd1002: TPrd1002
  Caption = 'Cadastro de Fam'#237'lias'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Fam'#237'lias'
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
        Width = 37
        Height = 13
        Caption = '&Fam'#237'lia:'
        FocusControl = cod_familia
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 167
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_familia
        Transparent = True
        WordWrap = True
      end
      object cod_familia: TDBEdit
        Left = 55
        Top = 15
        Width = 82
        Height = 21
        DataField = 'cod_familia'
        DataSource = DsCadFamilia
        TabOrder = 0
      end
      object den_familia: TDBEdit
        Left = 241
        Top = 15
        Width = 244
        Height = 21
        DataField = 'den_familia'
        DataSource = DsCadFamilia
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadFamilia: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_familia, den_familia'
      '   FROM tbl_familia'
      ' ORDER BY cod_familia')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadFamilia: TDataSource
    AutoEdit = False
    DataSet = QyCadFamilia
    Left = 703
    Top = 6
  end
end
