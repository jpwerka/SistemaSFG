inherited Vdp1010: TVdp1010
  Caption = 'Cadastro de Formas de Pagamento'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Formas de Pagamento'
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
        Left = 13
        Top = 17
        Width = 89
        Height = 13
        Caption = '&Forma Pagamento:'
        FocusControl = cod_forma_pagto
        Transparent = True
      end
      object Label2: TLabel
        Left = 197
        Top = 17
        Width = 69
        Height = 13
        Caption = '&Denomina'#231#227'o:'
        FocusControl = den_forma_pagto
        Transparent = True
        WordWrap = True
      end
      object cod_forma_pagto: TDBEdit
        Left = 108
        Top = 15
        Width = 71
        Height = 21
        DataField = 'cod_forma_pagto'
        DataSource = DsCadFormaPagto
        TabOrder = 0
      end
      object den_forma_pagto: TDBEdit
        Left = 272
        Top = 15
        Width = 236
        Height = 21
        DataField = 'den_forma_pagto'
        DataSource = DsCadFormaPagto
        TabOrder = 1
      end
      object ies_parcelado: TDBCheckBox
        Left = 108
        Top = 44
        Width = 75
        Height = 14
        Caption = '&Parcelado?'
        DataField = 'ies_parcelado'
        DataSource = DsCadFormaPagto
        TabOrder = 2
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
      object ies_financeiro: TDBCheckBox
        Left = 272
        Top = 44
        Width = 164
        Height = 14
        Caption = '&Gera Conta Pagar/Receber?'
        DataField = 'ies_financeiro'
        DataSource = DsCadFormaPagto
        TabOrder = 3
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
  end
  object QyCadFormaPagto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_forma_pagto, den_forma_pagto, ies_parcelado, ies_fina' +
        'nceiro'
      '  FROM tbl_forma_pagto'
      ' ORDER BY cod_forma_pagto')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadFormaPagto: TDataSource
    AutoEdit = False
    DataSet = QyCadFormaPagto
    Left = 703
    Top = 6
  end
end
