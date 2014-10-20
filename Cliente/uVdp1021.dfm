inherited Vdp1021: TVdp1021
  Caption = 'Cadastro de Estados'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Estados'
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
        Caption = '&Estado:'
        FocusControl = cod_uf
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 136
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_uf
        Transparent = True
        WordWrap = True
      end
      object Label4: TLabel
        Left = 539
        Top = 17
        Width = 64
        Height = 13
        Caption = 'C'#243'digo &IBGE:'
        FocusControl = cod_ibge
      end
      object cod_uf: TDBEdit
        Left = 53
        Top = 15
        Width = 51
        Height = 21
        DataField = 'cod_uf'
        DataSource = DsCadEstado
        TabOrder = 0
      end
      object den_uf: TDBEdit
        Left = 209
        Top = 15
        Width = 299
        Height = 21
        DataField = 'den_uf'
        DataSource = DsCadEstado
        TabOrder = 1
      end
      object cod_ibge: TDBEdit
        Left = 606
        Top = 15
        Width = 90
        Height = 21
        DataField = 'cod_ibge'
        DataSource = DsCadEstado
        TabOrder = 2
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadEstado: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_uf, den_uf, cod_ibge'
      '  FROM tbl_uf'
      ' ORDER BY cod_uf')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadEstado: TDataSource
    AutoEdit = False
    DataSet = QyCadEstado
    Left = 703
    Top = 6
  end
end
