inherited Vdp3001: TVdp3001
  Width = 308
  Caption = 'Vdp3001'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.7219019444
    ReportOptions.LastChange = 41297.8822777315
    Datasets = <
      item
        DataSet = frxCnsPagtos
        DataSetName = 'CnsPagtos'
      end
      item
        DataSet = frxCnsPedidoVenda
        DataSetName = 'CnsPedidoVenda'
      end
      item
        DataSet = frxCnsProdutos
        DataSetName = 'CnsProdutos'
      end
      item
        DataSet = frxCnsRepresentante
        DataSetName = 'CnsRepresentante'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      inherited CabPagina: TfrxPageHeader
        Top = 16
        Width = 680.315401779394
        Child = RpRelatBase.Child1
        inherited CabLivre01: TfrxMemoView
          Memo.UTF8 = (
            'CabLivre01')
        end
        inherited CabLivre02: TfrxMemoView
          Memo.UTF8 = (
            'CabLivre02')
        end
        inherited CabLivre03: TfrxMemoView
          Memo.UTF8 = (
            'CabLivre03')
        end
      end
      inherited Child1: TfrxChild
        Top = 84
        Width = 680.315401779394
        inherited Titulo: TfrxMemoView
          Width = 680.315401779394
          Memo.UTF8 = (
            'Pedido Venda')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
        object Memo5: TfrxMemoView
          Left = 434.66141
          Width = 266
          Height = 35
          ShowHint = False
          Clipped = False
          DataField = 'cod_pedido_venda'
          DataSet = frxCnsPedidoVenda
          DataSetName = 'CnsPedidoVenda'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -29
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[CnsPedidoVenda."cod_pedido_venda"]')
          ParentFont = False
          WordWrap = False
        end
        object Line1: TfrxLineView
          Align = baBottom
          Top = 35.0000011687231
          Width = 680.3154
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      inherited RodPagina: TfrxPageFooter
        Top = 700
        Width = 680.315401779394
        inherited RodLivre01: TfrxMemoView
          Left = 265.157702066691
          Top = 1.13385827
          Memo.UTF8 = (
            'RodLivre01')
        end
        inherited RodLivre02: TfrxMemoView
          Left = 265.157702066691
          Memo.UTF8 = (
            'RodLivre02')
        end
        inherited DataHora: TfrxMemoView
          Left = 265.157702066691
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Memo.UTF8 = (
            'Joinville - SC')
        end
        inherited PaginaNr: TfrxMemoView
          Left = 530.315404133382
          Memo.UTF8 = (
            'P'#195#161'gina [Page#]')
        end
        inherited Line5: TfrxLineView
          Width = 680.315401779394
          Frame.Color = clDefault
        end
      end
      object MasterData1: TfrxMasterData
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        Height = 78
        ParentFont = False
        Top = 180
        Width = 680.315401779394
        DataSet = frxCnsPedidoVenda
        DataSetName = 'CnsPedidoVenda'
        RowCount = 0
        object Memo6: TfrxMemoView
          Left = 89
          Top = 6
          Width = 71
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = frxCnsPedidoVenda
          DataSetName = 'CnsPedidoVenda'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Memo.UTF8 = (
            '[CnsPedidoVenda."data_cadastro"]')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 89
          Top = 24
          Width = 592
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[IIF(Length(<CnsPedidoVenda."cpf_cnpj">)>0,IIF(<CnsPedidoVenda."' +
              'tipo_pessoa">='#39'J'#39',FormatMaskText('#39'!00.000.000/0000-00;0;_'#39',<CnsP' +
              'edidoVenda."cpf_cnpj">) + '#39' - '#39',FormatMaskText('#39'!000.000.000-00;' +
              '0;_'#39',<CnsPedidoVenda."cpf_cnpj">) + '#39' - '#39'),'#39#39')][CnsPedidoVenda."' +
              'den_cliente"]')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 89
          Top = 42
          Width = 1124
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[CnsPedidoVenda."logradouro"][IIF(<CnsPedidoVenda."numero"><>0,'#39 +
              ', '#39'+IntToStr(<CnsPedidoVenda."numero">),'#39#39')][IIF(Length(<CnsPedi' +
              'doVenda."bairro">)>0,'#39' - '#39' + <CnsPedidoVenda."bairro">,'#39#39')][IIF(' +
              'Length(<CnsPedidoVenda."den_cidade">)>0,'#39' - '#39' + <CnsPedidoVenda.' +
              '"den_cidade"> + '#39' - '#39' + <CnsPedidoVenda."cod_uf">,'#39#39')]')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Top = 24
          Width = 85
          Height = 17
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Cliente:')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Top = 6
          Width = 85
          Height = 15
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Cadastro:')
          ParentFont = False
          WordWrap = False
        end
        object Memo11: TfrxMemoView
          Left = 396
          Top = 6
          Width = 50
          Height = 15
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            'Situa'#195#167#195#163'o:')
          ParentFont = False
          WordWrap = False
        end
        object Memo12: TfrxMemoView
          Left = 450
          Top = 6
          Width = 125
          Height = 15
          ShowHint = False
          Memo.UTF8 = (
            
              '[IIF(<CnsPedidoVenda."ies_situacao"> = '#39'A'#39','#39'Aberto'#39',IIF(<CnsPedi' +
              'doVenda."ies_situacao"> = '#39'F'#39','#39'Fechado'#39',IIF(<CnsPedidoVenda."ies' +
              '_situacao"> = '#39'T'#39','#39'Faturado'#39','#39'Cancelado'#39')))]')
        end
        object Memo13: TfrxMemoView
          Top = 42
          Width = 85
          Height = 17
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Endere'#195#167'o:')
          ParentFont = False
          WordWrap = False
        end
        object Memo3: TfrxMemoView
          Top = 60
          Width = 85
          Height = 17
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Representante:')
          ParentFont = False
          WordWrap = False
        end
        object Memo43: TfrxMemoView
          Left = 89
          Top = 60
          Width = 592
          Height = 16
          ShowHint = False
          Memo.UTF8 = (
            
              '[IIF(Length(<CnsRepresentante."cpf_cnpj">)>0,IIF(<CnsRepresentan' +
              'te."tipo_pessoa">='#39'J'#39',FormatMaskText('#39'!00.000.000/0000-00;0;_'#39',<' +
              'CnsRepresentante."cpf_cnpj">) + '#39' - '#39',FormatMaskText('#39'!000.000.0' +
              '00-00;0;_'#39',<CnsRepresentante."cpf_cnpj">) + '#39' - '#39'),'#39#39')][CnsRepre' +
              'sentante."den_representante"]')
        end
      end
      object GroupHeader1: TfrxGroupHeader
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 25
        ParentFont = False
        Top = 280
        Width = 680.315401779394
        Child = RpRelatBase.Child2
        Condition = 'CnsPedidoVenda."cod_pedido_venda"'
        object Memo14: TfrxMemoView
          Align = baLeft
          Top = 7
          Width = 50
          Height = 19
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '1 - Itens')
          WordWrap = False
        end
      end
      object Child2: TfrxChild
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 324
        Width = 680.315401779394
        object Shape1: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          EndColor = clSilver
          Style = gsVertical
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        end
        object Memo15: TfrxMemoView
          Width = 30
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Seq.')
        end
        object Memo16: TfrxMemoView
          Left = 30
          Width = 86
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Item')
        end
        object Memo17: TfrxMemoView
          Left = 118
          Width = 280
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Denomina'#195#167#195#163'o')
        end
        object Memo18: TfrxMemoView
          Left = 400
          Width = 70
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Qtde')
        end
        object Memo19: TfrxMemoView
          Left = 473
          Width = 70
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor Unit.')
        end
        object Memo20: TfrxMemoView
          Left = 605
          Width = 72
          Height = 18
          ShowHint = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor Total')
        end
        object Memo21: TfrxMemoView
          Left = 545
          Width = 58
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Desconto')
        end
      end
      object DetailData1: TfrxDetailData
        Height = 18
        Top = 360
        Width = 680.315401779394
        DataSet = frxCnsProdutos
        DataSetName = 'CnsProdutos'
        RowCount = 0
        object Memo22: TfrxMemoView
          Width = 30
          Height = 18
          ShowHint = False
          DataField = 'seq_produto'
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsProdutos."seq_produto"]')
        end
        object Memo23: TfrxMemoView
          Left = 30
          Width = 86
          Height = 18
          ShowHint = False
          DataField = 'cod_produto'
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsProdutos."cod_produto"]')
          WordWrap = False
        end
        object Memo24: TfrxMemoView
          Left = 118
          Width = 280
          Height = 18
          ShowHint = False
          DataField = 'den_produto'
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          Memo.UTF8 = (
            '[CnsProdutos."den_produto"]')
        end
        object Memo25: TfrxMemoView
          Left = 400
          Width = 70
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.3f'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsProdutos."qtd_produto"]')
        end
        object Memo26: TfrxMemoView
          Left = 473
          Width = 70
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsProdutos."preco_venda"]')
        end
        object Memo27: TfrxMemoView
          Align = baRight
          Left = 608.315401779394
          Width = 72
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsProdutos."valor_total"]')
          WordWrap = False
        end
        object Memo28: TfrxMemoView
          Left = 545
          Width = 58
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsProdutos."val_desconto"]')
        end
        object Line3: TfrxLineView
          Align = baBottom
          Top = 18
          Width = 680.3154
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftTop]
        end
      end
      object GroupHeader2: TfrxGroupHeader
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGreen
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 25
        ParentFont = False
        Top = 440
        Width = 680.315401779394
        Child = RpRelatBase.Child3
        Condition = 'CnsPedidoVenda."cod_pedido_venda"'
        object Memo29: TfrxMemoView
          Align = baLeft
          Top = 7
          Width = 111
          Height = 17
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '2 - Pagamentos - ')
          WordWrap = False
        end
        object Memo30: TfrxMemoView
          Left = 116
          Top = 8
          Width = 112
          Height = 17
          ShowHint = False
          Clipped = False
          DataField = 'den_forma_pagto'
          DataSet = frxCnsPedidoVenda
          DataSetName = 'CnsPedidoVenda'
          Memo.UTF8 = (
            '[CnsPedidoVenda."den_forma_pagto"]')
          WordWrap = False
        end
      end
      object Child3: TfrxChild
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 484
        Width = 680.315401779394
        object Shape2: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          EndColor = clSilver
          Style = gsVertical
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        end
        object Memo31: TfrxMemoView
          Width = 48
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Parcela')
        end
        object Memo32: TfrxMemoView
          Left = 48
          Width = 124
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor')
        end
        object Memo33: TfrxMemoView
          Left = 174
          Width = 103
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Vencimento')
        end
        object Memo34: TfrxMemoView
          Left = 420
          Width = 124
          Height = 18
          ShowHint = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Observa'#195#167#195#163'o')
        end
      end
      object DetailData2: TfrxDetailData
        Height = 18
        Top = 520
        Width = 680.315401779394
        DataSet = frxCnsPagtos
        DataSetName = 'CnsPagtos'
        RowCount = 0
        object Memo35: TfrxMemoView
          Width = 48
          Height = 18
          ShowHint = False
          DataField = 'seq_parcela'
          DataSet = frxCnsPagtos
          DataSetName = 'CnsPagtos'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsPagtos."seq_parcela"]')
        end
        object Memo36: TfrxMemoView
          Left = 48
          Width = 124
          Height = 18
          ShowHint = False
          DataSet = frxCnsPagtos
          DataSetName = 'CnsPagtos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsPagtos."valor_parcela"]')
        end
        object Memo37: TfrxMemoView
          Left = 174
          Width = 103
          Height = 18
          ShowHint = False
          DataSet = frxCnsPagtos
          DataSetName = 'CnsPagtos'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsPagtos."data_vencimento"]')
        end
        object Memo38: TfrxMemoView
          Left = 276
          Width = 395.37817
          Height = 15
          ShowHint = False
          Clipped = False
          DataField = 'observacao'
          DataSet = frxCnsPagtos
          DataSetName = 'CnsPagtos'
          Memo.UTF8 = (
            '[CnsPagtos."observacao"]')
          WordWrap = False
        end
        object Line6: TfrxLineView
          Align = baBottom
          Top = 18
          Width = 680.3154
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftTop]
        end
        object Line7: TfrxLineView
          Align = baLeft
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftLeft]
        end
        object Line8: TfrxLineView
          Align = baRight
          Left = 680.315401779394
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftLeft]
        end
      end
      object GroupFooter1: TfrxGroupFooter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 560
        Width = 680.315401779394
        Child = RpRelatBase.Child4
        object Shape3: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          BeginColor = 14548991
          EndColor = clYellow
          Style = gsVertical
          Frame.Color = clGray
          Frame.ShadowWidth = 1
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        end
        object Memo1: TfrxMemoView
          Left = 48
          Top = 1
          Width = 124
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsPagtos."valor_parcela">)]')
        end
        object Memo2: TfrxMemoView
          Left = 0.31540178
          Top = 1
          Width = 48
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Total:')
          WordWrap = False
        end
      end
      object Child4: TfrxChild
        Height = 40
        Top = 600
        Width = 680.315401779394
        object Memo39: TfrxMemoView
          Align = baLeft
          Top = 7
          Width = 681
          Height = 17
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clGreen
          Font.Height = -13
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '3 - Observa'#195#167#195#181'es')
          ParentFont = False
          WordWrap = False
        end
        object Memo40: TfrxMemoView
          Align = baWidth
          Top = 24
          Width = 680.315401779394
          Height = 15
          ShowHint = False
          Clipped = False
          DataField = 'observacao'
          DataSet = frxCnsPedidoVenda
          DataSetName = 'CnsPedidoVenda'
          Memo.UTF8 = (
            '[CnsPedidoVenda."observacao"]')
          WordWrap = False
        end
      end
      object GroupFooter2: TfrxGroupFooter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 400
        Width = 680.315401779394
        object Shape4: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          BeginColor = 14548991
          EndColor = clYellow
          Style = gsVertical
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        end
        object Memo4: TfrxMemoView
          Left = 473
          Width = 70
          Height = 18
          ShowHint = False
          Clipped = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo41: TfrxMemoView
          Align = baRight
          Left = 608.315401779394
          Width = 72
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsProdutos."valor_total">)]')
          WordWrap = False
        end
        object Memo42: TfrxMemoView
          Left = 545
          Width = 58
          Height = 18
          ShowHint = False
          DataSet = frxCnsProdutos
          DataSetName = 'CnsProdutos'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[SUm(<CnsProdutos."val_desconto">)]')
          WordWrap = False
        end
      end
    end
  end
  object CnsPedidoVenda: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT v.cod_pedido_venda, '
      '       c.tipo_pessoa,'
      '       c.cpf_cnpj,'
      '       c.den_cliente, '
      '       c.logradouro, '
      '       c.numero, '
      '       c.complemento, '
      '       c.bairro,'
      '       d.den_cidade,'
      '       d.cod_uf,'
      '       c.cep,'
      '       v.data_cadastro, '
      '       v.ies_situacao,'
      '       v.observacao, '
      '       f.den_forma_pagto,'
      '       v.valor_total,'
      '       v.cod_representante'
      '  FROM tbl_pedido_venda v,'
      '       tbl_forma_pagto f,'
      '       tbl_cliente c'
      '  LEFT JOIN tbl_cidade d       '
      '    ON d.cod_cidade = c.cod_cidade'
      ' WHERE v.cod_pedido_venda = :cod_pedido_venda'
      '   AND v.cod_cliente = c.cod_cliente '
      '   AND v.cod_forma_pagto = f.cod_forma_pagto'
      ' ORDER BY v.cod_pedido_venda')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_venda'
        ParamType = ptInput
        Value = 7
      end>
    Left = 162
    Top = 6
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_venda'
        ParamType = ptInput
        Value = 7
      end>
  end
  object CnsPagtos: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_pedido_venda, seq_parcela, valor_parcela, data_vencim' +
        'ento, observacao'
      '  FROM tbl_pedido_venda_pagto'
      ' WHERE cod_pedido_venda = :cod_pedido_venda'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_venda'
        ParamType = ptUnknown
      end>
    DataSource = DsPedidoVenda
    Left = 222
    Top = 6
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_venda'
        ParamType = ptUnknown
      end>
  end
  object CnsProdutos: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT v.cod_pedido_venda, v.seq_produto, '
      '       v.cod_produto, p.den_produto,'
      
        '       v.qtd_produto, v.preco_venda, v.val_desconto, (v.qtd_prod' +
        'uto * (v.preco_venda-v.val_desconto)) valor_total'
      '  FROM tbl_pedido_venda_item v,'
      '       tbl_produto p'
      ' WHERE v.cod_pedido_venda = :cod_pedido_venda'
      '   AND v.cod_produto = p.cod_produto'
      ' ORDER BY v.seq_produto')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_venda'
        ParamType = ptUnknown
      end>
    DataSource = DsPedidoVenda
    Left = 252
    Top = 6
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_pedido_venda'
        ParamType = ptUnknown
      end>
  end
  object DsPedidoVenda: TDataSource
    DataSet = CnsPedidoVenda
    Left = 192
    Top = 6
  end
  object frxCnsPedidoVenda: TfrxDBDataset
    UserName = 'CnsPedidoVenda'
    CloseDataSource = False
    DataSet = CnsPedidoVenda
    Left = 48
    Top = 12
  end
  object frxCnsPagtos: TfrxDBDataset
    UserName = 'CnsPagtos'
    CloseDataSource = False
    DataSet = CnsPagtos
    Left = 84
    Top = 12
  end
  object frxCnsProdutos: TfrxDBDataset
    UserName = 'CnsProdutos'
    CloseDataSource = False
    DataSet = CnsProdutos
    Left = 114
    Top = 12
  end
  object CnsRepresentante: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_representante,  den_representante, cpf_cnpj, tipo_pes' +
        'soa'
      '  FROM tbl_representante'
      ' WHERE cod_representante = :cod_representante')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_representante'
        ParamType = ptUnknown
      end>
    DataSource = DsPedidoVenda
    Left = 168
    Top = 38
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_representante'
        ParamType = ptUnknown
      end>
  end
  object frxCnsRepresentante: TfrxDBDataset
    UserName = 'CnsRepresentante'
    CloseDataSource = False
    DataSet = CnsRepresentante
    Left = 60
    Top = 42
  end
end
