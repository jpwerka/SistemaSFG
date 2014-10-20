inherited Vdp3012: TVdp3012
  Left = 527
  Top = 314
  Caption = 'Vdp3012'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6683083681
    ReportOptions.LastChange = 41304.5575420255
    Datasets = <
      item
        DataSet = frxQyPrdPedidoVenda
        DataSetName = 'QyPrdPedidoVenda'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      inherited CabPagina: TfrxPageHeader
        Top = 16
        Width = 680.315401779394
        Child = RpRelatBase.Child1
        inherited CabLivre01: TfrxMemoView
          Top = 0.99999998430675
        end
        inherited CabLivre02: TfrxMemoView
          Top = 16.9999993896174
        end
      end
      inherited Child1: TfrxChild
        Top = 84
        Width = 680.315401779394
        inherited Titulo: TfrxMemoView
          Width = 680.315401779394
          Memo.UTF8 = (
            'Produto Pedido Venda x Pagto')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
        object Line10: TfrxLineView
          Align = baWidth
          Top = 35.0000011687231
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      inherited RodPagina: TfrxPageFooter
        Top = 404
        Width = 680.315401779394
        inherited RodLivre01: TfrxMemoView
          Left = 265.157702066691
          Top = 0.99999998430675
        end
        inherited RodLivre02: TfrxMemoView
          Left = 265.157702066691
          Top = 0.99999998430675
        end
        inherited DataHora: TfrxMemoView
          Left = 265.157702066691
          Top = 0.99999998430675
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Top = 0.99999998430675
        end
        inherited PaginaNr: TfrxMemoView
          Left = 530.315404133382
          Top = 0.99999998430675
          Memo.UTF8 = (
            'P'#195#161'gina [Page#] de [TotalPages#]')
        end
        inherited Line5: TfrxLineView
          Width = 680.315401779394
        end
      end
      object GroupHeader1: TfrxGroupHeader
        Font.Charset = ANSI_CHARSET
        Font.Color = clNavy
        Font.Height = -15
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold]
        Height = 20.78740157
        ParentFont = False
        Top = 180
        Width = 680.315401779394
        Child = RpRelatBase.Child2
        Condition = '<QyPrdPedidoVenda."cod_forma_pagto">'
        KeepTogether = True
        object Memo5: TfrxMemoView
          Align = baWidth
          Top = 1.88976378
          Width = 680.315401779394
          Height = 19
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[QyPrdPedidoVenda."cod_forma_pagto"] - [QyPrdPedidoVenda."den_fo' +
              'rma_pagto"]')
          WordWrap = False
        end
      end
      object Child2: TfrxChild
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 17
        ParentFont = False
        Top = 220
        Width = 680.315401779394
        object Memo6: TfrxMemoView
          Top = 1
          Width = 68
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'C'#195#179'digo:')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 72
          Top = 1
          Width = 390
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Descri'#195#167#195#163'o:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 466
          Top = 1
          Width = 95
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Qtde Vendida:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Align = baRight
          Left = 590.315401779394
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Valor Total: ')
          WordWrap = False
        end
        object Line3: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object MasterData1: TfrxMasterData
        Height = 17
        Top = 256
        Width = 680.315401779394
        DataSet = frxQyPrdPedidoVenda
        DataSetName = 'QyPrdPedidoVenda'
        RowCount = 0
        object Memo11: TfrxMemoView
          Top = 1
          Width = 68
          Height = 16
          ShowHint = False
          HAlign = haRight
          Memo.UTF8 = (
            '[QyPrdPedidoVenda."cod_produto"]')
        end
        object Memo12: TfrxMemoView
          Left = 72
          Top = 1
          Width = 390
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '[QyPrdPedidoVenda."den_produto"]')
          WordWrap = False
        end
        object Memo13: TfrxMemoView
          Left = 466
          Top = 1
          Width = 95
          Height = 16
          ShowHint = False
          Clipped = False
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyPrdPedidoVenda."total_produto"]')
          WordWrap = False
        end
        object Memo14: TfrxMemoView
          Align = baRight
          Left = 590.315401779394
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          Clipped = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyPrdPedidoVenda."valor_total"]')
          WordWrap = False
        end
        object Line4: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object GroupFooter1: TfrxGroupFooter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 17
        ParentFont = False
        Top = 292
        Width = 680.315401779394
        object Shape1: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 17
          ShowHint = False
          BeginColor = 14548991
          EndColor = clYellow
          Style = gsVertical
        end
        object Memo20: TfrxMemoView
          Left = 466
          Top = 1
          Width = 95
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyPrdPedidoVenda."total_produto">)]')
        end
        object Memo21: TfrxMemoView
          Left = 424
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo22: TfrxMemoView
          Align = baRight
          Left = 590.315401779394
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyPrdPedidoVenda."valor_total">)]')
        end
      end
      object ReportSummary1: TfrxReportSummary
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 17
        ParentFont = False
        Top = 368
        Width = 680.315401779394
        object Shape2: TfrxGradientView
          Align = baClient
          Width = 680.315401779394
          Height = 17
          ShowHint = False
          BeginColor = 14548991
          EndColor = clSilver
          Style = gsVertical
        end
        object Memo25: TfrxMemoView
          Left = 466
          Top = 1
          Width = 95
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyPrdPedidoVenda."total_produto">)]')
        end
        object Memo23: TfrxMemoView
          Left = 424
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Line7: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo24: TfrxMemoView
          Align = baRight
          Left = 590.315401779394
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyPrdPedidoVenda."valor_total">)]')
        end
      end
    end
  end
  object QyPrdPedidoVenda: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT pagto.cod_forma_pagto, pagto.den_forma_pagto,'
      '       pvi.cod_produto, prd.den_produto,'
      '       sum(pvi.qtd_produto) total_produto, '
      '       sum(pvi.qtd_produto * pvi.preco_venda) valor_total      '
      '  FROM tbl_pedido_venda pv'
      ' INNER JOIN tbl_pedido_venda_item pvi'
      '    ON pv.cod_pedido_venda = pvi.cod_pedido_venda'
      ' INNER JOIN tbl_produto prd'
      '    ON prd.cod_produto = pvi.cod_produto'
      ' INNER JOIN tbl_forma_pagto pagto'
      '    ON pagto.cod_forma_pagto = pv.cod_forma_pagto'
      ' GROUP BY pagto.cod_forma_pagto, pagto.den_forma_pagto,'
      '       pvi.cod_produto, prd.den_produto'
      ' ORDER BY pagto.cod_forma_pagto, pvi.cod_produto')
    Params = <>
    Left = 90
    Top = 12
  end
  object frxQyPrdPedidoVenda: TfrxDBDataset
    UserName = 'QyPrdPedidoVenda'
    CloseDataSource = False
    DataSet = QyPrdPedidoVenda
    Left = 48
    Top = 12
  end
end
