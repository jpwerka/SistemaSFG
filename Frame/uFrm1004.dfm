inherited Frm1004: TFrm1004
  Caption = 'Cadastro de Grupos'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Grupos'
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
        Width = 32
        Height = 13
        Caption = '&Grupo:'
        FocusControl = cod_grupo
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 203
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_grupo
        Transparent = True
        WordWrap = True
      end
      object cod_grupo: TDBEdit
        Left = 48
        Top = 15
        Width = 136
        Height = 21
        DataField = 'cod_grupo'
        DataSource = DsCadGrupo
        TabOrder = 0
      end
      object den_grupo: TDBEdit
        Left = 276
        Top = 15
        Width = 321
        Height = 21
        DataField = 'den_grupo'
        DataSource = DsCadGrupo
        TabOrder = 1
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadGrupo: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_grupo, den_grupo'
      '  FROM tbl_grupo'
      ' ORDER BY cod_grupo')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadGrupo: TDataSource
    AutoEdit = False
    DataSet = QyCadGrupo
    Left = 703
    Top = 6
  end
end
