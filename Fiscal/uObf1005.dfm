object Obf1005: TObf1005
  Left = 280
  Top = 340
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsDialog
  BorderWidth = 6
  Caption = 'OBF1005 - Impostos Item Nota Fiscal'
  ClientHeight = 342
  ClientWidth = 762
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object pgImpostos: TPageControl
    Left = 0
    Top = 0
    Width = 762
    Height = 312
    ActivePage = pgICMS
    Align = alTop
    TabIndex = 0
    TabOrder = 0
    object pgICMS: TTabSheet
      Caption = '&1 - ICMS'
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 754
        Height = 50
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label1: TLabel
          Left = 12
          Top = 6
          Width = 86
          Height = 13
          Caption = '&Regime Tribut'#225'rio:'
          FocusControl = regime_tributario
        end
        object Label2: TLabel
          Left = 6
          Top = 30
          Width = 92
          Height = 13
          Caption = '&Situa'#231#227'o Tribut'#225'ria:'
          FocusControl = cod_cst_icms
        end
        object regime_tributario: TComboBox
          Left = 102
          Top = 3
          Width = 181
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 0
          OnChange = regime_tributarioChange
          Items.Strings = (
            'Simples Nacional'
            'Tributado Integralmente')
        end
        object cod_cst_icms: TComboBox
          Left = 102
          Top = 27
          Width = 646
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 1
        end
      end
      object Panel2: TPanel
        Left = 0
        Top = 50
        Width = 754
        Height = 234
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 1
        object gbICMS: TGroupBox
          Left = 4
          Top = 4
          Width = 370
          Height = 226
          Align = alLeft
          Caption = 'ICMS - Simples'
          TabOrder = 0
          object Label3: TLabel
            Left = 59
            Top = 18
            Width = 41
            Height = 13
            Alignment = taRightJustify
            Caption = '&Aliquota:'
            FocusControl = aliquota_icms
          end
          object Label4: TLabel
            Left = 8
            Top = 42
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor &Cr'#233'dito ICMS:'
            FocusControl = valor_icms
          end
          object aliquota_icms: TAlignEdit
            Left = 103
            Top = 15
            Width = 110
            Height = 21
            TabOrder = 0
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_icms: TAlignEdit
            Left = 103
            Top = 39
            Width = 110
            Height = 21
            TabOrder = 1
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
        end
        object gbICMSST: TGroupBox
          Left = 380
          Top = 4
          Width = 370
          Height = 226
          Align = alRight
          Caption = 'ICMS ST'
          TabOrder = 1
          object Label5: TLabel
            Left = 39
            Top = 18
            Width = 75
            Height = 13
            Alignment = taRightJustify
            Caption = '&Modalidade BC:'
            FocusControl = mod_bc_icmsst
          end
          object Label20: TLabel
            Left = 39
            Top = 42
            Width = 75
            Height = 13
            Alignment = taRightJustify
            Caption = '% R&edu'#231#227'o BC:'
            FocusControl = perc_red_bc_icmsst
          end
          object Label7: TLabel
            Left = 8
            Top = 66
            Width = 106
            Height = 13
            Alignment = taRightJustify
            Caption = '% Margem Valor A&dic.:'
            FocusControl = perc_marg_add_icmsst
          end
          object Label8: TLabel
            Left = 22
            Top = 90
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor &Base C'#225'lculo:'
            FocusControl = valor_bc_icmsst
          end
          object Label9: TLabel
            Left = 73
            Top = 114
            Width = 41
            Height = 13
            Alignment = taRightJustify
            Caption = 'A&liquota:'
            FocusControl = aliquota_icmsst
          end
          object Label10: TLabel
            Left = 41
            Top = 138
            Width = 73
            Height = 13
            Alignment = taRightJustify
            Caption = '&Valor ICMS ST:'
            FocusControl = valor_icmsst
          end
          object perc_marg_add_icmsst: TAlignEdit
            Left = 118
            Top = 63
            Width = 121
            Height = 21
            TabOrder = 2
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object perc_red_bc_icmsst: TAlignEdit
            Left = 118
            Top = 39
            Width = 121
            Height = 21
            TabOrder = 1
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_bc_icmsst: TAlignEdit
            Left = 118
            Top = 87
            Width = 121
            Height = 21
            TabOrder = 3
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_icmsst: TAlignEdit
            Left = 118
            Top = 111
            Width = 121
            Height = 21
            TabOrder = 4
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_icmsst: TAlignEdit
            Left = 118
            Top = 135
            Width = 121
            Height = 21
            TabOrder = 5
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object mod_bc_icmsst: TComboBox
            Left = 118
            Top = 15
            Width = 243
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 0
          end
        end
      end
    end
    object pgIPI: TTabSheet
      Caption = '&2 - IPI'
      ImageIndex = 1
      object Label11: TLabel
        Left = 6
        Top = 6
        Width = 92
        Height = 13
        Caption = '&Situa'#231#227'o Tribut'#225'ria:'
        FocusControl = cod_cst_ipi
      end
      object Label12: TLabel
        Left = 23
        Top = 30
        Width = 75
        Height = 13
        Alignment = taRightJustify
        Caption = '&Modalidade BC:'
        FocusControl = mod_bc_ipi
      end
      object Label13: TLabel
        Left = 6
        Top = 54
        Width = 92
        Height = 13
        Alignment = taRightJustify
        Caption = 'Valor &Base C'#225'lculo:'
        FocusControl = valor_bc_ipi
      end
      object Label14: TLabel
        Left = 57
        Top = 78
        Width = 41
        Height = 13
        Alignment = taRightJustify
        Caption = '&Aliquota:'
        FocusControl = aliquota_ipi
      end
      object Label15: TLabel
        Left = 32
        Top = 102
        Width = 66
        Height = 13
        Alignment = taRightJustify
        Caption = '&Qtd. Unidade:'
        FocusControl = qtd_unid_ipi
      end
      object Label16: TLabel
        Left = 28
        Top = 126
        Width = 70
        Height = 13
        Alignment = taRightJustify
        Caption = 'Valor &Unidade:'
        FocusControl = valor_unid_ipi
      end
      object Label17: TLabel
        Left = 55
        Top = 150
        Width = 43
        Height = 13
        Alignment = taRightJustify
        Caption = '&Valor IPI:'
        FocusControl = valor_ipi
      end
      object cod_cst_ipi: TComboBox
        Left = 102
        Top = 3
        Width = 646
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 0
      end
      object mod_bc_ipi: TComboBox
        Left = 102
        Top = 27
        Width = 243
        Height = 21
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 1
      end
      object valor_bc_ipi: TAlignEdit
        Left = 102
        Top = 51
        Width = 121
        Height = 21
        TabOrder = 2
        OnEnter = CampoMoedaEnter
        OnExit = CampoMoedaExit
        OnKeyPress = EditKeyPress
        Alignment = taRightJustify
      end
      object aliquota_ipi: TAlignEdit
        Left = 102
        Top = 75
        Width = 121
        Height = 21
        TabOrder = 3
        OnExit = ValorPercentualExit
        OnKeyPress = EditKeyPress
        Alignment = taRightJustify
      end
      object qtd_unid_ipi: TAlignEdit
        Left = 102
        Top = 99
        Width = 121
        Height = 21
        TabOrder = 4
        OnKeyPress = EditKeyPress
        Alignment = taRightJustify
      end
      object valor_unid_ipi: TAlignEdit
        Left = 102
        Top = 123
        Width = 121
        Height = 21
        TabOrder = 5
        OnEnter = CampoMoedaEnter
        OnExit = CampoMoedaExit
        OnKeyPress = EditKeyPress
        Alignment = taRightJustify
      end
      object valor_ipi: TAlignEdit
        Left = 102
        Top = 147
        Width = 121
        Height = 21
        TabOrder = 6
        OnEnter = CampoMoedaEnter
        OnExit = CampoMoedaExit
        OnKeyPress = EditKeyPress
        Alignment = taRightJustify
      end
    end
    object pgPIS: TTabSheet
      Caption = '&3 - PIS'
      ImageIndex = 2
      object Panel3: TPanel
        Left = 0
        Top = 0
        Width = 754
        Height = 28
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label6: TLabel
          Left = 6
          Top = 6
          Width = 92
          Height = 13
          Caption = '&Situa'#231#227'o Tribut'#225'ria:'
          FocusControl = cod_cst_pis
        end
        object cod_cst_pis: TComboBox
          Left = 102
          Top = 3
          Width = 646
          Height = 21
          Style = csDropDownList
          ItemHeight = 0
          TabOrder = 0
        end
      end
      object Panel4: TPanel
        Left = 0
        Top = 28
        Width = 754
        Height = 256
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 1
        object gbPIS: TGroupBox
          Left = 4
          Top = 4
          Width = 370
          Height = 248
          Align = alLeft
          Caption = 'PIS'
          TabOrder = 0
          object Label18: TLabel
            Left = 38
            Top = 18
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = '&Tipo C'#225'lculo:'
            FocusControl = tipo_calc_pis
          end
          object Label19: TLabel
            Left = 8
            Top = 42
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor &Base C'#225'lculo:'
            FocusControl = valor_bc_pis
          end
          object Label21: TLabel
            Left = 48
            Top = 66
            Width = 52
            Height = 13
            Alignment = taRightJustify
            Caption = '&Aliquota %:'
            FocusControl = aliquota_pis_perc
          end
          object Label22: TLabel
            Left = 42
            Top = 90
            Width = 58
            Height = 13
            Alignment = taRightJustify
            Caption = 'A&liquota R$:'
            FocusControl = aliquota_pis_reais
          end
          object Label23: TLabel
            Left = 38
            Top = 114
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = '&Qtd Vendida:'
            FocusControl = qtd_vendida_pis
          end
          object Label24: TLabel
            Left = 53
            Top = 138
            Width = 47
            Height = 13
            Alignment = taRightJustify
            Caption = '&Valor PIS:'
            FocusControl = valor_pis
          end
          object tipo_calc_pis: TComboBox
            Left = 104
            Top = 15
            Width = 121
            Height = 21
            Style = csDropDownList
            ItemHeight = 0
            TabOrder = 0
          end
          object valor_bc_pis: TAlignEdit
            Left = 104
            Top = 39
            Width = 121
            Height = 21
            TabOrder = 1
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_pis_perc: TAlignEdit
            Left = 104
            Top = 63
            Width = 121
            Height = 21
            TabOrder = 2
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_pis_reais: TAlignEdit
            Left = 104
            Top = 87
            Width = 121
            Height = 21
            TabOrder = 3
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object qtd_vendida_pis: TAlignEdit
            Left = 104
            Top = 111
            Width = 121
            Height = 21
            TabOrder = 4
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_pis: TAlignEdit
            Left = 104
            Top = 135
            Width = 121
            Height = 21
            TabOrder = 5
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
        end
        object gbPISST: TGroupBox
          Left = 380
          Top = 4
          Width = 370
          Height = 248
          Align = alRight
          Caption = 'PIS ST'
          TabOrder = 1
          object Label25: TLabel
            Left = 38
            Top = 18
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = 'Tipo &C'#225'lculo:'
            FocusControl = tipo_calc_pisst
          end
          object Label26: TLabel
            Left = 8
            Top = 42
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valo&r Base C'#225'lculo:'
            FocusControl = valor_bc_pisst
          end
          object Label27: TLabel
            Left = 48
            Top = 66
            Width = 52
            Height = 13
            Alignment = taRightJustify
            Caption = 'Al&iquota %:'
            FocusControl = aliquota_pisst_perc
          end
          object Label28: TLabel
            Left = 42
            Top = 90
            Width = 58
            Height = 13
            Alignment = taRightJustify
            Caption = 'Aliq&uota R$:'
            FocusControl = aliquota_pisst_reais
          end
          object Label29: TLabel
            Left = 38
            Top = 114
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = 'Qt&d Vendida:'
            FocusControl = qtd_vendida_pisst
          end
          object Label30: TLabel
            Left = 36
            Top = 138
            Width = 64
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor &PIS ST:'
            FocusControl = valor_pisst
          end
          object tipo_calc_pisst: TComboBox
            Left = 104
            Top = 15
            Width = 121
            Height = 21
            Style = csDropDownList
            ItemHeight = 0
            TabOrder = 0
          end
          object valor_bc_pisst: TAlignEdit
            Left = 104
            Top = 39
            Width = 121
            Height = 21
            TabOrder = 1
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_pisst_perc: TAlignEdit
            Left = 104
            Top = 63
            Width = 121
            Height = 21
            TabOrder = 2
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_pisst_reais: TAlignEdit
            Left = 104
            Top = 87
            Width = 121
            Height = 21
            TabOrder = 3
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object qtd_vendida_pisst: TAlignEdit
            Left = 104
            Top = 111
            Width = 121
            Height = 21
            TabOrder = 4
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_pisst: TAlignEdit
            Left = 104
            Top = 135
            Width = 121
            Height = 21
            TabOrder = 5
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
        end
      end
    end
    object pgCOFINS: TTabSheet
      Caption = '&4 - COFINS'
      ImageIndex = 3
      object Panel6: TPanel
        Left = 0
        Top = 28
        Width = 754
        Height = 256
        Align = alClient
        BevelOuter = bvNone
        BorderWidth = 4
        TabOrder = 1
        object gbCOFINS: TGroupBox
          Left = 4
          Top = 4
          Width = 370
          Height = 248
          Align = alLeft
          Caption = 'COFINS'
          TabOrder = 0
          object Label31: TLabel
            Left = 38
            Top = 18
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = '&Tipo C'#225'lculo:'
            FocusControl = tipo_calc_cofins
          end
          object Label32: TLabel
            Left = 8
            Top = 42
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor &Base C'#225'lculo:'
            FocusControl = valor_bc_cofins
          end
          object Label33: TLabel
            Left = 48
            Top = 66
            Width = 52
            Height = 13
            Alignment = taRightJustify
            Caption = '&Aliquota %:'
            FocusControl = aliquota_cofins_perc
          end
          object Label34: TLabel
            Left = 42
            Top = 90
            Width = 58
            Height = 13
            Alignment = taRightJustify
            Caption = 'A&liquota R$:'
            FocusControl = aliquota_cofins_reais
          end
          object Label35: TLabel
            Left = 38
            Top = 114
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = '&Qtd Vendida:'
            FocusControl = qtd_vendida_cofins
          end
          object Label36: TLabel
            Left = 31
            Top = 138
            Width = 69
            Height = 13
            Alignment = taRightJustify
            Caption = '&Valor COFINS:'
            FocusControl = valor_cofins
          end
          object tipo_calc_cofins: TComboBox
            Left = 104
            Top = 15
            Width = 121
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 0
          end
          object valor_bc_cofins: TAlignEdit
            Left = 104
            Top = 39
            Width = 121
            Height = 21
            TabOrder = 1
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_cofins_perc: TAlignEdit
            Left = 104
            Top = 63
            Width = 121
            Height = 21
            TabOrder = 2
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_cofins_reais: TAlignEdit
            Left = 104
            Top = 87
            Width = 121
            Height = 21
            TabOrder = 3
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object qtd_vendida_cofins: TAlignEdit
            Left = 104
            Top = 111
            Width = 121
            Height = 21
            TabOrder = 4
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_cofins: TAlignEdit
            Left = 104
            Top = 135
            Width = 121
            Height = 21
            TabOrder = 5
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
        end
        object gbCOFINSST: TGroupBox
          Left = 380
          Top = 4
          Width = 370
          Height = 248
          Align = alRight
          Caption = 'COFINS ST'
          TabOrder = 1
          object Label37: TLabel
            Left = 38
            Top = 18
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = 'Tipo &C'#225'lculo:'
            FocusControl = tipo_calc_cofinsst
          end
          object Label38: TLabel
            Left = 8
            Top = 42
            Width = 92
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valo&r Base C'#225'lculo:'
            FocusControl = valor_bc_cofinsst
          end
          object Label39: TLabel
            Left = 48
            Top = 66
            Width = 52
            Height = 13
            Alignment = taRightJustify
            Caption = 'Al&iquota %:'
            FocusControl = aliquota_cofinsst_perc
          end
          object Label40: TLabel
            Left = 42
            Top = 90
            Width = 58
            Height = 13
            Alignment = taRightJustify
            Caption = 'Aliq&uota R$:'
            FocusControl = aliquota_cofinsst_reais
          end
          object Label41: TLabel
            Left = 38
            Top = 114
            Width = 62
            Height = 13
            Alignment = taRightJustify
            Caption = 'Qt&d Vendida:'
            FocusControl = qtd_vendida_cofinsst
          end
          object Label42: TLabel
            Left = 14
            Top = 138
            Width = 86
            Height = 13
            Alignment = taRightJustify
            Caption = 'Valor CO&FINS ST:'
            FocusControl = valor_cofinsst
          end
          object tipo_calc_cofinsst: TComboBox
            Left = 104
            Top = 15
            Width = 121
            Height = 21
            Style = csDropDownList
            ItemHeight = 13
            TabOrder = 0
          end
          object valor_bc_cofinsst: TAlignEdit
            Left = 104
            Top = 39
            Width = 121
            Height = 21
            TabOrder = 1
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_cofinsst_perc: TAlignEdit
            Left = 104
            Top = 63
            Width = 121
            Height = 21
            TabOrder = 2
            OnExit = ValorPercentualExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object aliquota_cofinsst_reais: TAlignEdit
            Left = 104
            Top = 87
            Width = 121
            Height = 21
            TabOrder = 3
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object qtd_vendida_cofinsst: TAlignEdit
            Left = 104
            Top = 111
            Width = 121
            Height = 21
            TabOrder = 4
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
          object valor_cofinsst: TAlignEdit
            Left = 104
            Top = 135
            Width = 121
            Height = 21
            TabOrder = 5
            OnEnter = CampoMoedaEnter
            OnExit = CampoMoedaExit
            OnKeyPress = EditKeyPress
            Alignment = taRightJustify
          end
        end
      end
      object Panel5: TPanel
        Left = 0
        Top = 0
        Width = 754
        Height = 28
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label43: TLabel
          Left = 6
          Top = 6
          Width = 92
          Height = 13
          Caption = '&Situa'#231#227'o Tribut'#225'ria:'
          FocusControl = cod_cst_cofins
        end
        object cod_cst_cofins: TComboBox
          Left = 102
          Top = 3
          Width = 646
          Height = 21
          Style = csDropDownList
          ItemHeight = 13
          TabOrder = 0
        end
      end
    end
    object pgISSQN: TTabSheet
      Caption = '&5 - ISSQN'
      Enabled = False
      ImageIndex = 4
    end
  end
  object btOK: TButton
    Left = 594
    Top = 318
    Width = 75
    Height = 23
    Caption = '&OK'
    TabOrder = 1
    OnClick = btOKClick
  end
  object btCancel: TButton
    Left = 684
    Top = 318
    Width = 75
    Height = 23
    Cancel = True
    Caption = 'Cancelar'
    ModalResult = 2
    TabOrder = 2
  end
end
