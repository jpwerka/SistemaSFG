inherited Fin1006: TFin1006
  Caption = 'Cadastro de Centros de Custo'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Centros de Custo'
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
        Width = 64
        Height = 13
        Caption = '&Centro Custo:'
        FocusControl = cod_centro_custo
        Transparent = True
      end
      object Label2: TLabel
        Left = 226
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_centro_custo
        Transparent = True
        WordWrap = True
      end
      object cod_centro_custo: TDBEdit
        Left = 80
        Top = 15
        Width = 126
        Height = 21
        CharCase = ecUpperCase
        DataField = 'cod_centro_custo'
        DataSource = DsCentroCusto
        TabOrder = 0
      end
      object den_centro_custo: TDBEdit
        Left = 298
        Top = 15
        Width = 303
        Height = 21
        DataField = 'den_centro_custo'
        DataSource = DsCentroCusto
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object DsCentroCusto: TDataSource
    AutoEdit = False
    DataSet = CentroCusto
    Left = 703
    Top = 6
  end
  object CentroCusto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_centro_custo, den_centro_custo FROM tbl_centro_custo ' +
        'ORDER BY cod_centro_custo')
    Params = <>
    Left = 666
    Top = 6
    object CentroCustocod_centro_custo: TStringField
      Tag = 7
      DisplayLabel = 'Centro Custo'
      FieldName = 'cod_centro_custo'
      ProviderFlags = [pfInWhere, pfInKey]
      Required = True
      Size = 15
    end
    object CentroCustoden_centro_custo: TStringField
      Tag = 2
      ConstraintErrorMessage = 'A denomina'#231#227'o do centro de custo deve ser informada!'
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_centro_custo'
      ProviderFlags = [pfInUpdate]
      Required = True
      Size = 45
    end
  end
end
