inherited Obf1001: TObf1001
  Left = 382
  Top = 157
  Caption = 'Cadastro de Notas Fiscais Sa'#237'da'
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Notas Fiscais Sa'#237'da'
    object lbEmpresa: TLabel
      Left = 666
      Top = 0
      Width = 100
      Height = 53
      Align = alRight
      Alignment = taRightJustify
      Caption = 'Empresa: XX'
      Font.Charset = ANSI_CHARSET
      Font.Color = clGreen
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentFont = False
      OnClick = lbEmpresaClick
    end
  end
  inherited BodyPanel: TPanel
    object gbNotaFiscal: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 67
      Align = alTop
      Caption = 'Nota Fiscal'
      TabOrder = 0
      object Label2: TLabel
        Left = 226
        Top = 17
        Width = 68
        Height = 13
        Cursor = crArrow
        Caption = 'Data &Emiss'#227'o:'
        DragCursor = crDefault
        FocusControl = data_hora_emissao
        Transparent = True
      end
      object Label6: TLabel
        Left = 596
        Top = 17
        Width = 45
        Height = 13
        Caption = 'Situa'#231#227'o:'
        FocusControl = ies_situacao
      end
      object Label5: TLabel
        Left = 8
        Top = 17
        Width = 40
        Height = 13
        Alignment = taRightJustify
        Caption = '&N'#250'mero:'
        FocusControl = num_nota_fiscal
        Transparent = True
      end
      object Label7: TLabel
        Left = 150
        Top = 17
        Width = 27
        Height = 13
        Alignment = taRightJustify
        Caption = '&S'#233'rie:'
        FocusControl = serie_nota_fiscal
        Transparent = True
      end
      object Label12: TLabel
        Left = 426
        Top = 41
        Width = 58
        Height = 13
        Cursor = crArrow
        Caption = 'Data S&a'#237'da:'
        DragCursor = crDefault
        FocusControl = data_saida
        Transparent = True
      end
      object Label1: TLabel
        Left = 8
        Top = 42
        Width = 96
        Height = 13
        Caption = 'Nature&za Opera'#231#227'o:'
        FocusControl = natureza_operacao
      end
      object Label16: TLabel
        Left = 402
        Top = 17
        Width = 57
        Height = 13
        Alignment = taRightJustify
        Caption = '&Pagamento:'
        FocusControl = serie_nota_fiscal
        Transparent = True
      end
      object Label19: TLabel
        Left = 601
        Top = 41
        Width = 58
        Height = 13
        Alignment = taRightJustify
        Caption = '&Hora Sa'#237'da:'
        FocusControl = hora_saida
        Transparent = True
      end
      object num_nota_fiscal: TDBEdit
        Left = 53
        Top = 15
        Width = 80
        Height = 21
        DataField = 'num_nota_fiscal'
        DataSource = DsNotaFiscal
        TabOrder = 0
      end
      object serie_nota_fiscal: TDBEdit
        Left = 181
        Top = 15
        Width = 30
        Height = 21
        DataField = 'serie_nota_fiscal'
        DataSource = DsNotaFiscal
        TabOrder = 1
      end
      object data_hora_emissao: TDBEdit
        Left = 299
        Top = 15
        Width = 88
        Height = 21
        DataField = 'data_hora_emissao'
        DataSource = DsNotaFiscal
        TabOrder = 2
      end
      object btCalendar01: TCustomImgButton
        Left = 369
        Top = 18
        Width = 16
        Height = 16
        TabOrder = 3
        TabStop = False
        OnClick = btCalendar01Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object cod_forma_pagto: TDBDataComboBox
        Left = 462
        Top = 15
        Width = 121
        Height = 21
        DataField = 'cod_forma_pagto'
        DataSource = DsNotaFiscal
        ItemHeight = 13
        TabOrder = 4
      end
      object ies_situacao: TDBDataComboBox
        Left = 644
        Top = 15
        Width = 104
        Height = 21
        AutoDropDown = True
        DataField = 'ies_situacao'
        DataSource = DsSitNotaFiscal
        ItemHeight = 13
        TabOrder = 5
      end
      object natureza_operacao: TDBEdit
        Left = 108
        Top = 39
        Width = 66
        Height = 21
        DataField = 'cod_natureza_operacao'
        DataSource = DsNotaFiscal
        TabOrder = 6
      end
      object btPesqNatOp: TResBitBtn
        Left = 180
        Top = 38
        Width = 24
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 7
        TabStop = False
        OnClick = btPesqNatOpClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object den_natureza_operacao: TEdit
        Left = 208
        Top = 39
        Width = 207
        Height = 21
        Color = clWhite
        TabOrder = 8
      end
      object data_saida: TDBEdit
        Left = 488
        Top = 39
        Width = 88
        Height = 21
        DataField = 'data_saida'
        DataSource = DsNotaFiscal
        TabOrder = 9
      end
      object btCalendar02: TCustomImgButton
        Left = 558
        Top = 42
        Width = 16
        Height = 16
        TabOrder = 10
        TabStop = False
        OnClick = btCalendar02Click
        NumGlyphs = 5
        GlyphLoadType = glByResName
        GlyphResName = 'CALENDAR'
        TextMargin = -1
      end
      object hora_saida: TDBEdit
        Left = 663
        Top = 39
        Width = 66
        Height = 21
        DataField = 'hora_saida'
        DataSource = DsNotaFiscal
        TabOrder = 11
      end
    end
    object gbDestinatario: TGroupBox
      Left = 0
      Top = 67
      Width = 750
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Destinat'#225'rio'
      TabOrder = 1
      object Label3: TLabel
        Left = 8
        Top = 17
        Width = 59
        Height = 13
        Caption = '&Destinat'#225'rio:'
        FocusControl = cod_cliente
        Transparent = True
        WordWrap = True
      end
      object Label20: TLabel
        Left = 8
        Top = 41
        Width = 55
        Height = 13
        Alignment = taRightJustify
        Caption = 'CPF/CNPJ:'
        FocusControl = cpf_cnpj
        Transparent = True
        WordWrap = True
      end
      object Rtulo98: TLabel
        Left = 214
        Top = 41
        Width = 34
        Height = 13
        Alignment = taRightJustify
        Caption = 'RG/IE:'
        FocusControl = rg_ie
        Transparent = True
        WordWrap = True
      end
      object Label4: TLabel
        Left = 371
        Top = 41
        Width = 45
        Height = 13
        Alignment = taRightJustify
        Caption = 'Telefone:'
        FocusControl = telefone
        Transparent = True
        WordWrap = True
      end
      object den_cliente: TDBEdit
        Left = 215
        Top = 15
        Width = 407
        Height = 21
        Color = clWhite
        DataField = 'den_cliente'
        DataSource = DsClientes
        ReadOnly = True
        TabOrder = 2
      end
      object cpf_cnpj: TDBEdit
        Left = 67
        Top = 39
        Width = 120
        Height = 21
        DataField = 'cpf_cnpj'
        DataSource = DsClientes
        ReadOnly = True
        TabOrder = 3
      end
      object rg_ie: TDBEdit
        Left = 251
        Top = 39
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'rg_ie'
        DataSource = DsClientes
        ReadOnly = True
        TabOrder = 4
      end
      object cod_cliente: TDBEdit
        Left = 70
        Top = 15
        Width = 110
        Height = 21
        DataField = 'cod_cliente'
        DataSource = DsNotaFiscal
        TabOrder = 0
      end
      object btPesqCliente: TResBitBtn
        Left = 185
        Top = 14
        Width = 24
        Height = 23
        Enabled = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btPesqClienteClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object btEndereco: TResBitBtn
        Left = 545
        Top = 38
        Width = 78
        Height = 24
        Caption = '&Endere'#231'o'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = btEnderecoClick
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'CASAM'
        GlyphResID = 0
      end
      object telefone: TDBEdit
        Left = 420
        Top = 39
        Width = 99
        Height = 21
        Color = clWhite
        DataField = 'telefone'
        DataSource = DsClientes
        ReadOnly = True
        TabOrder = 5
      end
    end
    object pgDetalhes: TPageControl
      Left = 0
      Top = 134
      Width = 750
      Height = 283
      ActivePage = tbItens
      Align = alClient
      MultiLine = True
      TabIndex = 0
      TabOrder = 2
      object tbItens: TTabSheet
        Caption = '&1 - Produtos/Servi'#231'os'
        object grdItens: TDBGrid
          Left = 0
          Top = 0
          Width = 742
          Height = 222
          Align = alClient
          DataSource = DsCadProduto
          Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
          TabOrder = 0
          TitleFont.Charset = DEFAULT_CHARSET
          TitleFont.Color = clWindowText
          TitleFont.Height = -11
          TitleFont.Name = 'MS Sans Serif'
          TitleFont.Style = []
          OnCellClick = grdItensCellClick
          OnColEnter = grdItensColEnter
          OnColExit = grdItensColExit
          OnDrawColumnCell = grdItensDrawColumnCell
          OnEditButtonClick = grdItensEditButtonClick
          OnKeyDown = DbGridKeyDown
          Columns = <
            item
              ButtonStyle = cbsEllipsis
              Expanded = False
              FieldName = 'cod_produto'
              ReadOnly = True
              Width = 135
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'den_produto'
              ReadOnly = True
              Width = 240
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_ncm'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 65
              Visible = True
            end
            item
              Alignment = taLeftJustify
              Expanded = False
              FieldName = 'cod_cfop'
              Title.Alignment = taCenter
              Width = 40
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_unid_medida'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 25
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'qtd_produto'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_unitario'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_total'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 95
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'valor_desconto'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 90
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'impostos'
              ReadOnly = True
              Title.Alignment = taCenter
              Title.Caption = 'Impostos'
              Width = 50
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_pedido'
              ReadOnly = True
              Title.Alignment = taCenter
              Width = 70
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'seq_pedido'
              ReadOnly = True
              Title.Alignment = taCenter
              Title.Caption = 'Seq'
              Width = 40
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_extipi'
              Title.Alignment = taCenter
              Width = 45
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'classe_enq_ipi'
              Visible = True
            end
            item
              Expanded = False
              FieldName = 'cod_enq_ipi'
              Visible = True
            end>
        end
        object Panel6: TPanel
          Left = 0
          Top = 222
          Width = 742
          Height = 33
          Align = alBottom
          BevelOuter = bvNone
          ParentColor = True
          TabOrder = 1
          object btAddLinha: TResBitBtn
            Left = 5
            Top = 5
            Width = 108
            Height = 25
            Action = addLine
            Caption = '&Adicionar Linha'
            TabOrder = 0
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'ADICIONARM'
            GlyphResID = 0
          end
          object btDelLinha: TResBitBtn
            Left = 117
            Top = 5
            Width = 108
            Height = 25
            Action = delLine
            Caption = '&Remover Linha'
            TabOrder = 1
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'EXCLUIRM'
            GlyphResID = 0
          end
          object btAddItens: TResBitBtn
            Left = 228
            Top = 5
            Width = 109
            Height = 25
            Action = addItens
            Caption = 'Adicionar &Itens'
            TabOrder = 2
            NumGlyphs = 4
            Spacing = -1
            GlyphLoadType = glByResName
            GlyphResName = 'ADICIONARM'
            GlyphResID = 0
          end
        end
      end
      object tbTransportador: TTabSheet
        BorderWidth = 6
        Caption = '&2 - Transportador/Volumes'
        ImageIndex = 2
        object gbTransportador: TGroupBox
          Left = 0
          Top = 0
          Width = 730
          Height = 91
          Cursor = crArrow
          Align = alTop
          Caption = 'Transportador'
          TabOrder = 0
          object Label22: TLabel
            Left = 8
            Top = 41
            Width = 69
            Height = 13
            Caption = '&Transportador:'
            FocusControl = cod_transportador
            Transparent = True
            WordWrap = True
          end
          object Label31: TLabel
            Left = 8
            Top = 18
            Width = 51
            Height = 13
            Caption = 'Tipo &Frete:'
            FocusControl = tipo_frete
          end
          object Label32: TLabel
            Left = 8
            Top = 65
            Width = 70
            Height = 13
            Caption = '&Placa Ve'#237'culo:'
            FocusControl = placa_veiculo
          end
          object Label33: TLabel
            Left = 215
            Top = 65
            Width = 66
            Height = 13
            Caption = 'Estad&o Placa:'
            FocusControl = cod_uf_placa_veiculo
            Transparent = True
          end
          object den_transportador: TEdit
            Left = 226
            Top = 39
            Width = 407
            Height = 21
            Color = clWhite
            ReadOnly = True
            TabOrder = 2
          end
          object cod_transportador: TDBEdit
            Left = 81
            Top = 39
            Width = 110
            Height = 21
            DataField = 'cod_transportador'
            DataSource = DsNotaFiscal
            TabOrder = 0
          end
          object btPesqTransportador: TResBitBtn
            Left = 196
            Top = 38
            Width = 24
            Height = 23
            Enabled = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            TabStop = False
            OnClick = btPesqTransportadorClick
            NumGlyphs = 4
            GlyphLoadType = glByResName
            GlyphResName = 'PESQUISAM'
            GlyphResID = 0
          end
          object tipo_frete: TDBDataComboBox
            Left = 64
            Top = 15
            Width = 190
            Height = 21
            AutoDropDown = True
            DataField = 'tipo_frete'
            DataSource = DsNotaFiscal
            ItemHeight = 13
            TabOrder = 3
          end
          object placa_veiculo: TDBEdit
            Left = 81
            Top = 63
            Width = 103
            Height = 21
            DataField = 'placa_veiculo'
            DataSource = DsNotaFiscal
            TabOrder = 4
          end
          object cod_uf_placa_veiculo: TDBComboBox
            Left = 285
            Top = 63
            Width = 40
            Height = 21
            DataField = 'estado_placa_veiculo'
            DataSource = DsNotaFiscal
            ItemHeight = 13
            TabOrder = 5
          end
        end
        object gbVolumes: TGroupBox
          Left = 0
          Top = 91
          Width = 730
          Height = 67
          Align = alTop
          Caption = 'Volumes'
          TabOrder = 1
          object Label18: TLabel
            Left = 8
            Top = 17
            Width = 58
            Height = 13
            Caption = '&Quantidade:'
            FocusControl = qtd_volume
          end
          object Label21: TLabel
            Left = 198
            Top = 18
            Width = 41
            Height = 13
            Caption = 'Esp'#233'c&ie:'
            FocusControl = especie_volume
          end
          object Label34: TLabel
            Left = 468
            Top = 18
            Width = 33
            Height = 13
            Caption = '&Marca:'
            FocusControl = marca_volume
          end
          object Label35: TLabel
            Left = 8
            Top = 41
            Width = 58
            Height = 13
            Caption = 'N&umera'#231#227'o:'
            FocusControl = mumeracao_volume
          end
          object Label36: TLabel
            Left = 203
            Top = 41
            Width = 66
            Height = 13
            Caption = 'Peso &L'#237'quido:'
            FocusControl = peso_liquido
          end
          object Label37: TLabel
            Left = 392
            Top = 42
            Width = 55
            Height = 13
            Caption = 'Peso &Bruto:'
            FocusControl = peso_bruto
          end
          object Label38: TLabel
            Left = 570
            Top = 42
            Width = 38
            Height = 13
            Caption = '&Volume:'
            FocusControl = volume_cubico
          end
          object qtd_volume: TDBEdit
            Left = 70
            Top = 14
            Width = 100
            Height = 21
            DataField = 'qtd_volume'
            DataSource = DsNotaFiscal
            TabOrder = 0
          end
          object especie_volume: TDBEdit
            Left = 243
            Top = 14
            Width = 190
            Height = 21
            DataField = 'especie_volume'
            DataSource = DsNotaFiscal
            TabOrder = 1
          end
          object marca_volume: TDBEdit
            Left = 505
            Top = 14
            Width = 210
            Height = 21
            DataField = 'marca_volume'
            DataSource = DsNotaFiscal
            TabOrder = 2
          end
          object mumeracao_volume: TDBEdit
            Left = 70
            Top = 39
            Width = 120
            Height = 21
            DataField = 'numeracao_volume'
            DataSource = DsNotaFiscal
            TabOrder = 3
          end
          object peso_liquido: TDBEdit
            Left = 272
            Top = 39
            Width = 110
            Height = 21
            DataField = 'peso_liquido'
            DataSource = DsNotaFiscal
            TabOrder = 4
            OnKeyPress = grdEditCtrlKeyPress
          end
          object peso_bruto: TDBEdit
            Left = 452
            Top = 39
            Width = 110
            Height = 21
            DataField = 'peso_bruto'
            DataSource = DsNotaFiscal
            TabOrder = 5
            OnKeyPress = grdEditCtrlKeyPress
          end
          object volume_cubico: TDBEdit
            Left = 612
            Top = 39
            Width = 110
            Height = 21
            DataField = 'volume_cubico'
            DataSource = DsNotaFiscal
            TabOrder = 6
            OnKeyPress = grdEditCtrlKeyPress
          end
        end
      end
      object tbTotais: TTabSheet
        Caption = '&3 - Impostos/Totais'
        ImageIndex = 2
        object Label39: TLabel
          Left = 23
          Top = 105
          Width = 99
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor Total Produtos:'
          FocusControl = valor_mercadoria
        end
        object Label40: TLabel
          Left = 309
          Top = 129
          Width = 83
          Height = 13
          Caption = 'Valor Nota Fiscal:'
          FocusControl = valor_nota_fiscal
        end
        object Label41: TLabel
          Left = 316
          Top = 105
          Width = 76
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor Desconto:'
          FocusControl = valor_desconto
        end
        object Label42: TLabel
          Left = 68
          Top = 9
          Width = 54
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor Frete:'
          FocusControl = valor_frete
        end
        object Label43: TLabel
          Left = 328
          Top = 9
          Width = 64
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor Seguro:'
          FocusControl = valor_seguro
        end
        object Label44: TLabel
          Left = 28
          Top = 33
          Width = 94
          Height = 13
          Alignment = taRightJustify
          Caption = 'Base Calculo ICMS:'
          FocusControl = valor_frete
        end
        object Label45: TLabel
          Left = 11
          Top = 57
          Width = 111
          Height = 13
          Alignment = taRightJustify
          Caption = 'Base Calculo ICMS ST:'
          FocusControl = valor_frete
        end
        object Label46: TLabel
          Left = 41
          Top = 81
          Width = 81
          Height = 13
          Alignment = taRightJustify
          Caption = 'Base Calculo IPI:'
          FocusControl = valor_frete
        end
        object Label47: TLabel
          Left = 38
          Top = 129
          Width = 84
          Height = 13
          Alignment = taRightJustify
          Caption = 'Outras Despesas:'
          FocusControl = valor_frete
        end
        object Label48: TLabel
          Left = 336
          Top = 33
          Width = 56
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor ICMS:'
          FocusControl = valor_frete
        end
        object Label49: TLabel
          Left = 319
          Top = 57
          Width = 73
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor ICMS ST:'
          FocusControl = valor_frete
        end
        object Label51: TLabel
          Left = 349
          Top = 81
          Width = 43
          Height = 13
          Alignment = taRightJustify
          Caption = 'Valor IPI:'
          FocusControl = valor_frete
        end
        object valor_mercadoria: TDBEdit
          Left = 126
          Top = 102
          Width = 120
          Height = 21
          DataField = 'valor_mercadoria'
          DataSource = DsNotaFiscal
          TabOrder = 8
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_nota_fiscal: TDBEdit
          Left = 396
          Top = 126
          Width = 120
          Height = 21
          DataField = 'valor_nota_fiscal'
          DataSource = DsNotaFiscal
          TabOrder = 11
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_desconto: TDBEdit
          Left = 396
          Top = 102
          Width = 120
          Height = 21
          DataField = 'valor_desconto'
          DataSource = DsNotaFiscal
          TabOrder = 9
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_frete: TDBEdit
          Left = 126
          Top = 6
          Width = 120
          Height = 21
          DataField = 'valor_frete'
          DataSource = DsNotaFiscal
          TabOrder = 0
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_seguro: TDBEdit
          Left = 396
          Top = 6
          Width = 120
          Height = 21
          DataField = 'valor_seguro'
          DataSource = DsNotaFiscal
          TabOrder = 1
          OnKeyPress = grdEditCtrlKeyPress
        end
        object base_calc_icms_st: TDBEdit
          Left = 126
          Top = 54
          Width = 120
          Height = 21
          DataField = 'base_calc_icms_st'
          DataSource = DsNotaFiscal
          TabOrder = 4
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_icms: TDBEdit
          Left = 396
          Top = 30
          Width = 120
          Height = 21
          DataField = 'valor_icms'
          DataSource = DsNotaFiscal
          TabOrder = 3
          OnKeyPress = grdEditCtrlKeyPress
        end
        object base_calc_icms: TDBEdit
          Left = 126
          Top = 30
          Width = 120
          Height = 21
          DataField = 'base_calc_icms'
          DataSource = DsNotaFiscal
          TabOrder = 2
          OnKeyPress = grdEditCtrlKeyPress
        end
        object base_calc_ipi: TDBEdit
          Left = 126
          Top = 78
          Width = 120
          Height = 21
          DataField = 'base_calc_ipi'
          DataSource = DsNotaFiscal
          TabOrder = 6
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_icms_st: TDBEdit
          Left = 396
          Top = 54
          Width = 120
          Height = 21
          DataField = 'valor_icms_st'
          DataSource = DsNotaFiscal
          TabOrder = 5
          OnKeyPress = grdEditCtrlKeyPress
        end
        object valor_ipi: TDBEdit
          Left = 396
          Top = 78
          Width = 120
          Height = 21
          DataField = 'valor_ipi'
          DataSource = DsNotaFiscal
          TabOrder = 7
          OnKeyPress = grdEditCtrlKeyPress
        end
        object outras_despesas: TDBEdit
          Left = 126
          Top = 126
          Width = 120
          Height = 21
          DataField = 'outras_despesas'
          DataSource = DsNotaFiscal
          TabOrder = 10
          OnKeyPress = grdEditCtrlKeyPress
        end
      end
      object tbObs: TTabSheet
        BorderWidth = 6
        Caption = '&4 - Observa'#231#245'es'
        ImageIndex = 3
        object lbTotCredICMS: TLabel
          Left = 0
          Top = 234
          Width = 149
          Height = 13
          Caption = 'Valor Total de Cr'#233'dito do ICMS:'
        end
        object val_cred_icms: TDBText
          Left = 154
          Top = 234
          Width = 65
          Height = 17
          DataField = 'val_cred_icms'
          DataSource = DsTotCredICMS
        end
        object gbInfoFisco: TGroupBox
          Left = 0
          Top = 130
          Width = 738
          Height = 100
          Align = alTop
          Caption = 'Informa'#231#245'es Adicionais Fisco'
          TabOrder = 1
          object info_adicional_fisco: TDBMemo
            Left = 6
            Top = 15
            Width = 700
            Height = 78
            DataField = 'info_adicional_fisco'
            DataSource = DsNotaFiscal
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
        object gbInfoCompl: TGroupBox
          Left = 0
          Top = 0
          Width = 738
          Height = 130
          Align = alTop
          Caption = 'Informa'#231#245'es Complementares'
          TabOrder = 0
          object info_complementar: TDBMemo
            Left = 6
            Top = 15
            Width = 700
            Height = 108
            DataField = 'info_complementar'
            DataSource = DsNotaFiscal
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
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btDelete: TResBitBtn
      Left = 462
    end
    inherited btExit: TResBitBtn
      Left = 652
    end
    inherited btajuda: TResBitBtn
      Left = 704
    end
    inherited MenuClicks: TPopupMenu
      object Fechar1: TMenuItem
        Action = execFechamento
        Caption = 'Fechamento Nota Fiscal'
      end
      object PesquisaProdutoCliente2: TMenuItem
        Action = execRelatorio
        Caption = 'Visualizar Impress'#227'o'
      end
      object ImportarOramento1: TMenuItem
        Action = execImportar
        Caption = 'Importar Pedido Venda'
      end
      object NumeraoNotaFiscal1: TMenuItem
        Action = execNumeracaoNF
        Caption = 'Numera'#231#227'o Nota Fiscal'
      end
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = NavegexecBtEditClickExecute
      end
      inherited execBtSaveClick: TAction
        OnExecute = NavegexecBtSaveClickExecute
      end
      inherited execBtCancelClick: TAction
        OnExecute = NavegexecBtCancelClickExecute
      end
      inherited execBtNewClick: TAction
        OnExecute = NavegexecBtNewClickExecute
      end
      inherited execBtCopyClick: TAction
        Visible = False
      end
      inherited execBtDeleteClick: TAction
        OnExecute = NavegexecBtDeleteClickExecute
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object btFechamento: TResBitBtn
    Left = 500
    Top = 61
    Width = 32
    Height = 32
    Action = execFechamento
    TabOrder = 5
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'FECHANEGC'
    GlyphResID = 0
  end
  object btRelatorio: TResBitBtn
    Left = 538
    Top = 61
    Width = 32
    Height = 32
    Action = execRelatorio
    TabOrder = 6
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'RELATORIO'
    GlyphResID = 0
  end
  object btImportar: TResBitBtn
    Left = 576
    Top = 61
    Width = 32
    Height = 32
    Action = execImportar
    TabOrder = 7
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'PROCESSAR'
    GlyphResID = 0
  end
  object grpEndereco: TGroupBox
    Left = 384
    Top = 486
    Width = 600
    Height = 91
    Cursor = crArrow
    Caption = 'Endere'#231'o'
    TabOrder = 8
    Visible = False
    OnExit = grpEnderecoExit
    object Label9: TLabel
      Left = 503
      Top = 17
      Width = 40
      Height = 13
      Caption = 'N&'#250'mero:'
      FocusControl = numero
      Transparent = True
    end
    object Label8: TLabel
      Left = 492
      Top = 41
      Width = 24
      Height = 13
      Caption = 'CE&P:'
      FocusControl = cep
      Transparent = True
    end
    object Label10: TLabel
      Left = 13
      Top = 65
      Width = 30
      Height = 13
      Caption = '&Bairro:'
      FocusControl = bairro
      Transparent = True
    end
    object Label11: TLabel
      Left = 160
      Top = 41
      Width = 36
      Height = 13
      Caption = 'Ci&dade:'
      Transparent = True
    end
    object Label13: TLabel
      Left = 13
      Top = 41
      Width = 36
      Height = 13
      Caption = '&Estado:'
      FocusControl = cod_uf_cliente
      Transparent = True
    end
    object Label14: TLabel
      Left = 13
      Top = 17
      Width = 57
      Height = 13
      Caption = '&Logradouro:'
      FocusControl = logradouro
      Transparent = True
    end
    object Label15: TLabel
      Left = 447
      Top = 65
      Width = 67
      Height = 13
      Caption = '&Complemento:'
      FocusControl = complemento
      Transparent = True
    end
    object logradouro: TDBEdit
      Left = 75
      Top = 15
      Width = 400
      Height = 21
      Color = clWhite
      DataField = 'logradouro'
      DataSource = DsClientes
      ReadOnly = True
      TabOrder = 0
    end
    object numero: TDBEdit
      Left = 547
      Top = 15
      Width = 46
      Height = 21
      DataField = 'numero'
      DataSource = DsClientes
      ReadOnly = True
      TabOrder = 1
    end
    object cod_uf_cliente: TDBComboBox
      Left = 53
      Top = 39
      Width = 40
      Height = 21
      DataField = 'cod_uf'
      DataSource = DsClientes
      ItemHeight = 13
      ReadOnly = True
      TabOrder = 2
    end
    object cep: TDBEdit
      Left = 520
      Top = 39
      Width = 74
      Height = 21
      Color = clWhite
      DataField = 'cep'
      DataSource = DsClientes
      ReadOnly = True
      TabOrder = 4
    end
    object bairro: TDBEdit
      Left = 47
      Top = 63
      Width = 236
      Height = 21
      DataField = 'bairro'
      DataSource = DsClientes
      ReadOnly = True
      TabOrder = 5
    end
    object complemento: TDBEdit
      Left = 519
      Top = 63
      Width = 75
      Height = 21
      DataField = 'complemento'
      DataSource = DsClientes
      ReadOnly = True
      TabOrder = 6
    end
    object cod_cidade_cliente: TDBDataComboBox
      Left = 200
      Top = 39
      Width = 216
      Height = 21
      DataField = 'cod_cidade'
      DataSource = DsClientes
      ItemHeight = 13
      ReadOnly = True
      Sorted = True
      TabOrder = 3
      LookUpDataSet = QyCidade
      LookUpField = 'cod_cidade'
      ResultField = 'den_cidade'
    end
  end
  object btNumNF: TResBitBtn
    Left = 614
    Top = 61
    Width = 32
    Height = 32
    Action = execNumeracaoNF
    ParentShowHint = False
    ShowHint = True
    TabOrder = 9
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'ANOTAR'
    GlyphResID = 0
  end
  object DsNotaFiscal: TDataSource
    AutoEdit = False
    DataSet = QyNotaFiscal
    Left = 728
    Top = 26
  end
  object QyCliente: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_cliente, den_cliente, tipo_pessoa, cpf_cnpj, rg_ie, t' +
        'elefone,'
      
        '               logradouro, numero, complemento, bairro, cod_cida' +
        'de, cod_uf, cep'
      '  FROM tbl_cliente'
      ' WHERE cod_cliente =:cod_cliente')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_cliente'
        ParamType = ptUnknown
      end>
    Left = 636
    Top = 26
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_cliente'
        ParamType = ptUnknown
      end>
  end
  object DsClientes: TDataSource
    AutoEdit = False
    DataSet = QyCliente
    Left = 666
    Top = 26
  end
  object QyCadProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'seq_produto'
    AutoCalcFields = False
    UpdateObject = AddItemNota
    CachedUpdates = True
    BeforeInsert = QyDetalheBeforeInsert
    SQL.Strings = (
      'SELECT ni.cod_empresa, ni.cod_nota_fiscal, ni.seq_produto, '
      '       ni.cod_produto, ni.den_produto, ni.cod_ncm, ni.cod_cfop,'
      '       ni.cod_unid_medida, ni.qtd_produto, ni.valor_unitario,'
      '       ni.valor_desconto, ni.valor_frete, ni.valor_seguro,'
      '       ni.valor_total, ni.cod_pedido, ni.seq_pedido,'
      '       ni.cod_extipi, ni.classe_enq_ipi, ni.cod_enq_ipi'
      '  FROM tbl_nota_fiscal_item ni'
      ' WHERE ni.cod_empresa = :cod_empresa'
      '   AND ni.cod_nota_fiscal = :cod_nota_fiscal'
      ' ORDER BY ni.seq_produto')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_empresa'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
    DataSource = DsNotaFiscal
    IndexFieldNames = 'seq_produto Asc'
    Left = 426
    Top = 234
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_empresa'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
    object QyCadProdutocod_empresa: TStringField
      FieldName = 'cod_empresa'
      Required = True
      Size = 2
    end
    object QyCadProdutocod_nota_fiscal: TIntegerField
      FieldName = 'cod_nota_fiscal'
      Required = True
    end
    object QyCadProdutoseq_produto: TIntegerField
      FieldName = 'seq_produto'
      Required = True
    end
    object QyCadProdutocod_produto: TStringField
      DisplayLabel = 'Item'
      FieldName = 'cod_produto'
      OnValidate = CodProdutoValidate
      Size = 15
    end
    object QyCadProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      Size = 75
    end
    object QyCadProdutocod_unid_medida: TStringField
      DisplayLabel = 'UM'
      FieldName = 'cod_unid_medida'
      Size = 3
    end
    object QyCadProdutoqtd_produto: TFloatField
      DisplayLabel = 'Quantidade'
      FieldName = 'qtd_produto'
      OnSetText = QtdProdutoSetText
      DisplayFormat = '#0.000'
    end
    object QyCadProdutovalor_unitario: TFloatField
      DisplayLabel = 'Valor Unit'#225'rio'
      FieldName = 'valor_unitario'
      OnSetText = PrecoVendaSetText
      currency = True
    end
    object QyCadProdutovalor_desconto: TFloatField
      DisplayLabel = 'Valor Desconto'
      FieldName = 'valor_desconto'
      currency = True
    end
    object QyCadProdutovalor_frete: TFloatField
      FieldName = 'valor_frete'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object QyCadProdutovalor_seguro: TFloatField
      FieldName = 'valor_seguro'
      ProviderFlags = [pfInUpdate]
      currency = True
    end
    object QyCadProdutovalor_total: TFloatField
      DisplayLabel = 'Valor Total'
      FieldName = 'valor_total'
      currency = True
    end
    object QyCadProdutocod_ncm: TStringField
      DisplayLabel = 'NCM'
      FieldName = 'cod_ncm'
      Size = 8
    end
    object QyCadProdutocod_cfop: TSmallintField
      DisplayLabel = 'CFOP'
      DisplayWidth = 4
      FieldName = 'cod_cfop'
    end
    object QyCadProdutocod_pedido: TIntegerField
      DisplayLabel = 'Pedido'
      FieldName = 'cod_pedido'
    end
    object QyCadProdutoseq_pedido: TSmallintField
      DisplayLabel = 'Seq Pedido'
      FieldName = 'seq_pedido'
    end
    object Impostos: TStringField
      FieldKind = fkCalculated
      FieldName = 'impostos'
      Size = 1
      Calculated = True
    end
    object CodEXTIPI: TStringField
      DisplayLabel = 'EX TIPI'
      DisplayWidth = 3
      FieldName = 'cod_extipi'
      Size = 3
    end
    object QyCadProdutoclasse_enq_ipi: TStringField
      DisplayLabel = 'Classe IPI'
      FieldName = 'classe_enq_ipi'
      Size = 5
    end
    object QyCadProdutocod_enq_ipi: TStringField
      DisplayLabel = 'C'#243'd. IPI'
      FieldName = 'cod_enq_ipi'
      Size = 3
    end
  end
  object AddItemNota: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_nota_fiscal_item'
      'WHERE cod_empresa = :cod_empresa'
      'AND cod_nota_fiscal = :cod_nota_fiscal'
      'AND seq_produto = :seq_produto')
    InsertSQL.Strings = (
      'INSERT INTO tbl_nota_fiscal_item '
      '(cod_empresa,cod_nota_fiscal,seq_produto, '
      'cod_produto,den_produto,cod_ncm,cod_ean,  '
      'cod_cfop, cod_unid_medida,qtd_produto,'
      'valor_unitario,valor_desconto,valor_frete, '
      'valor_seguro,valor_total,cod_pedido,seq_pedido,'
      'cod_extipi,classe_enq_ipi,cod_enq_ipi)'
      'VALUES '
      '(:cod_empresa, :cod_nota_fiscal, :seq_produto,'
      ':cod_produto, :den_produto, :cod_ncm, :cod_ean,'
      ':cod_cfop, :cod_unid_medida, :qtd_produto,'
      ':valor_unitario, :valor_desconto, :valor_frete,'
      ':valor_seguro, :valor_total, :cod_pedido, :seq_pedido,'
      ':cod_extipi, :classe_enq_ipi, :cod_enq_ipi)')
    ModifySQL.Strings = (
      'UPDATE tbl_nota_fiscal_item SET'
      '   cod_produto = :cod_produto,'
      '   qtd_produto = :qtd_produto,'
      '   den_produto = :den_produto,'
      '   cod_ncm = :cod_ncm,'
      '   cod_ean = :cod_ean,'
      '   cod_cfop = :cod_cfop,'
      '   cod_unid_medida = :cod_unid_medida,'
      '   qtd_produto = :qtd_produto,'
      '   valor_unitario = :valor_unitario,'
      '   valor_desconto = :valor_desconto,'
      '   valor_frete = :valor_frete,'
      '   valor_seguro = :valor_seguro,'
      '   valor_total = :valor_total,'
      '   cod_pedido = :cod_pedido,'
      '   seq_pedido = :seq_pedido,'
      '   cod_extipi = :cod_extipi,'
      '   classe_enq_ipi = :classe_enq_ipi,'
      '   cod_enq_ipi = :cod_enq_ipi'
      'WHERE cod_empresa = :cod_empresa'
      'AND cod_nota_fiscal = :cod_nota_fiscal'
      'AND seq_produto = :seq_produto')
    UseSequenceFieldForRefreshSQL = False
    Left = 456
    Top = 234
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
        Value = '1.001'
      end
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'qtd_produto'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'den_produto'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_ncm'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_ean'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_cfop'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_unid_medida'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'valor_unitario'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'valor_desconto'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'valor_frete'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'valor_seguro'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'valor_total'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_pedido'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'seq_pedido'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_extipi'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'classe_enq_ipi'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_enq_ipi'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_empresa'
        ParamType = ptUnknown
      end
      item
        DataType = ftInteger
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
        Size = 10
        Value = 1
      end
      item
        DataType = ftInteger
        Precision = 255
        Name = 'seq_produto'
        ParamType = ptUnknown
        Size = 255
        Value = 1
      end>
  end
  object QyNotaFiscal: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    AfterOpen = QyNotaFiscalAfterOpen
    BeforeClose = QyNotaFiscalBeforeClose
    AfterScroll = QyNotaFiscalAfterScroll
    OnCalcFields = QyNotaFiscalCalcFields
    BeforePost = QyNotaFiscalBeforePost
    AfterPost = QyNotaFiscalAfterPost
    BeforeDelete = QyNotaFiscalBeforeDelete
    SQL.Strings = (
      
        'SELECT cod_empresa,cod_nota_fiscal,tipo_nota_fiscal,num_nota_fis' +
        'cal,serie_nota_fiscal,'
      
        '       modelo_nota_fiscal,ies_situacao,cod_natureza_operacao,cod' +
        '_forma_pagto,cod_cliente,cod_transportador,'
      
        '       tipo_frete,placa_veiculo,estado_placa_veiculo,placa_reboq' +
        'ue,estado_placa_reboque,'
      
        '       qtd_volume,especie_volume,marca_volume,numeracao_volume,p' +
        'eso_liquido,peso_bruto,'
      
        '       volume_cubico,valor_mercadoria,valor_desconto,valor_dupli' +
        'cata,valor_frete,valor_seguro,'
      
        '       outras_despesas,valor_nota_fiscal,usuario_inclusao,data_h' +
        'ora_emissao,data_hora_saida,'
      
        '       data_hora_cancelamento,motivo_cancelamento,usuario_cancel' +
        'amento,'
      
        '       0.0 base_calc_icms, 0.0 valor_icms, 0.0 base_calc_icms_st' +
        ', 0.0 valor_icms_st,'
      
        '       0.0 base_calc_ipi, 0.0 valor_ipi, date(data_hora_saida) d' +
        'ata_saida, '#39'00:00:00'#39' hora_saida,'
      '       info_complementar, info_adicional_fisco'
      '  FROM tbl_nota_fiscal'
      ' WHERE cod_empresa = :cod_empresa'
      '   AND tipo_nota_fiscal = 1'
      ' ORDER BY num_nota_fiscal,serie_nota_fiscal ')
    Params = <
      item
        DataType = ftString
        Name = 'cod_empresa'
        ParamType = ptUnknown
        Value = '01'
      end>
    Left = 696
    Top = 26
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_empresa'
        ParamType = ptUnknown
        Value = '01'
      end>
  end
  object ActionList1: TActionList
    Left = 690
    Top = 72
    object execRelatorio: TAction
      Hint = 'Visualiza a impress'#227'o da DANFE da nota fiscal.'
      ShortCut = 16457
      OnExecute = btRelatorioClick
    end
    object execFechamento: TAction
      Hint = 
        'Fecha a nota fiscal habilitando a mesma para gera'#231#227'o|do xml para' +
        ' posterior envio a SEFAZ.'
      ShortCut = 16454
      OnExecute = btFechamentoClick
    end
    object execNumeracaoNF: TAction
      Hint = 'Parametriza'#231#227'o da numera'#231#227'o das notas fiscais de venda.'
      ShortCut = 16461
      OnExecute = execNumeracaoNFExecute
    end
    object execImportar: TAction
      Hint = 'Importa um pedido de venda gerando os dados da nota fiscal.'
      ShortCut = 16463
      OnExecute = execImportarExecute
    end
    object addLine: TAction
      Caption = '&Adicionar Linha'
      Enabled = False
      ShortCut = 32833
      Visible = False
      OnExecute = addLineExecute
    end
    object delLine: TAction
      Caption = '&Remover Linha'
      Enabled = False
      ShortCut = 32850
      Visible = False
      OnExecute = delLineExecute
    end
    object addItens: TAction
      Caption = 'Adicionar &Itens'
      Enabled = False
      Hint = 'Adicionar v'#225'rios itens por|meio de uma sele'#231#227'o em lista.'
      ShortCut = 32841
      Visible = False
      OnExecute = addItensExecute
    end
  end
  object QySitNotaFiscal: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT ies_situacao'
      '  FROM tbl_nota_fiscal'
      ' WHERE cod_nota_fiscal =:cod_nota_fiscal')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
    DataSource = DsNotaFiscal
    Left = 726
    Top = 78
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
  end
  object DsSitNotaFiscal: TDataSource
    AutoEdit = False
    DataSet = QySitNotaFiscal
    Left = 744
    Top = 54
  end
  object DsCadProduto: TDataSource
    AutoEdit = False
    DataSet = QyCadProduto
    Left = 486
    Top = 234
  end
  object PopupMenu1: TPopupMenu
    Left = 516
    Top = 234
    object AdicionarLinha1: TMenuItem
      Action = addLine
    end
    object RemoverLinha1: TMenuItem
      Action = delLine
    end
    object AdicionarItens1: TMenuItem
      Action = addItens
    end
  end
  object QyCnsProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_produto, den_produto, cod_unid_medida, preco_venda'
      '  FROM tbl_produto'
      ' WHERE cod_produto = :cod_produto '
      '   AND ies_ativo = '#39'S'#39)
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
      end>
    Left = 548
    Top = 234
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_produto'
        ParamType = ptUnknown
      end>
  end
  object QyCidade: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_cidade, den_cidade, cod_uf'
      '  FROM tbl_cidade'
      ' ORDER BY cod_uf, den_cidade;')
    Params = <>
    Left = 729
    Top = 236
  end
  object QyTotCredICMS: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT sum(valor_tributo) val_cred_icms'
      '  FROM tbl_nota_fiscal_item_tributo'
      ' WHERE cod_empresa = :cod_empresa'
      '   AND cod_nota_fiscal = :cod_nota_fiscal'
      '   AND cod_tributo = '#39'ICMS'#39)
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_empresa'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
    DataSource = DsNotaFiscal
    Left = 732
    Top = 204
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_empresa'
        ParamType = ptUnknown
      end
      item
        DataType = ftUnknown
        Name = 'cod_nota_fiscal'
        ParamType = ptUnknown
      end>
    object QyTotCredICMSval_cred_icms: TFloatField
      FieldName = 'val_cred_icms'
      ReadOnly = True
      currency = True
    end
  end
  object DsTotCredICMS: TDataSource
    DataSet = QyTotCredICMS
    Left = 702
    Top = 204
  end
end
