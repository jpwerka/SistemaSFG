inherited Vdp3004: TVdp3004
  Caption = 'Vdp3004'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6683656944
    ReportOptions.LastChange = 41112.6683656944
    Datasets = <
      item
        DataSet = frxQySitPedidoVenda
        DataSetName = 'QySitPedidoVenda'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      LeftMargin = 10
      RightMargin = 10
      inherited CabPagina: TfrxPageHeader
        Top = 16
        Width = 718.1107
        Child = RpRelatBase.Child1
        inherited CabLivre01: TfrxMemoView
          Top = 0.99999998430675
          Memo.UTF8 = (
            'CabLivre01')
        end
        inherited CabLivre02: TfrxMemoView
          Top = 16.9999993896174
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
        Width = 718.1107
        inherited Titulo: TfrxMemoView
          Width = 718.1107
          Memo.UTF8 = (
            'Situação x Pedidos de Venda')
        end
        inherited Line2: TfrxLineView
          Width = 718.1107
        end
        object Line1: TfrxLineView
          Align = baBottom
          Top = 35.0000011687231
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      inherited RodPagina: TfrxPageFooter
        Top = 368
        Width = 718.1107
        inherited RodLivre01: TfrxMemoView
          Left = 284.055351176994
          Top = 1.13385827
          Memo.UTF8 = (
            'RodLivre01')
        end
        inherited RodLivre02: TfrxMemoView
          Left = 284.055351176994
          Top = 0.99999998430675
          Memo.UTF8 = (
            'RodLivre02')
        end
        inherited DataHora: TfrxMemoView
          Left = 284.055351176994
          Top = 0.99999998430675
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Top = 0.99999998430675
          Memo.UTF8 = (
            'Joinville - SC')
        end
        inherited PaginaNr: TfrxMemoView
          Left = 568.110702353988
          Top = 0.99999998430675
          Memo.UTF8 = (
            'Página [Page#]')
        end
        inherited Line5: TfrxLineView
          Width = 718.1107
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
        Width = 718.1107
        Child = RpRelatBase.Child2
        Condition = 'QySitPedidoVenda."ies_situacao"'
        object Memo5: TfrxMemoView
          Top = 1.88976378
          Width = 251
          Height = 19
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '[QySitPedidoVenda."den_situacao"]')
          WordWrap = False
        end
      end
      object Child2: TfrxChild
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 17
        ParentFont = False
        Top = 220
        Width = 718.1107
        object Memo6: TfrxMemoView
          Top = 1
          Width = 43
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Código:')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 553
          Top = 1
          Width = 78
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Centro Custo:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 306
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Data Cadastro:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 474
          Top = 1
          Width = 74
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Valor Recbto:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Left = 403
          Top = 1
          Width = 63
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Valor Total:')
          WordWrap = False
        end
        object Memo11: TfrxMemoView
          Left = 56
          Top = 1
          Width = 43
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Cliente:')
          WordWrap = False
        end
        object Memo12: TfrxMemoView
          Align = baRight
          Left = 634.1107
          Top = 1
          Width = 84
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Conta Contábil:')
          WordWrap = False
        end
        object Line3: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object MasterData1: TfrxMasterData
        Height = 17
        Top = 256
        Width = 718.1107
        DataSet = frxQySitPedidoVenda
        DataSetName = 'QySitPedidoVenda'
        RowCount = 0
        object Memo13: TfrxMemoView
          Top = 1
          Width = 52
          Height = 16
          ShowHint = False
          DataField = 'cod_pedido_venda'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          HAlign = haRight
          Memo.UTF8 = (
            '[QySitPedidoVenda."cod_pedido_venda"]')
        end
        object Memo14: TfrxMemoView
          Left = 314
          Top = 1
          Width = 71
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'data_cadastro'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          HAlign = haCenter
          Memo.UTF8 = (
            '[QySitPedidoVenda."data_cadastro"]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 466
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_recebido'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QySitPedidoVenda."valor_recebido"]')
        end
        object Memo16: TfrxMemoView
          Left = 384
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_total'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QySitPedidoVenda."valor_total"]')
        end
        object Memo17: TfrxMemoView
          Left = 550
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          DataField = 'cod_centro_custo'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          HAlign = haCenter
          Memo.UTF8 = (
            '[QySitPedidoVenda."cod_centro_custo"]')
        end
        object Memo18: TfrxMemoView
          Align = baRight
          Left = 638.1107
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'cod_plano_conta'
          DataSet = frxQySitPedidoVenda
          DataSetName = 'QySitPedidoVenda'
          HAlign = haRight
          Memo.UTF8 = (
            '[QySitPedidoVenda."cod_plano_conta"]')
        end
        object Memo19: TfrxMemoView
          Left = 56
          Top = 1
          Width = 253
          Height = 16
          ShowHint = False
          Memo.UTF8 = (
            
              '[QySitPedidoVenda."cod_cliente"] - [QySitPedidoVenda."den_client' +
              'e"]')
        end
        object Line4: TfrxLineView
          Align = baWidth
          Width = 718.1107
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
        Width = 718.1107
        object Shape1: TfrxGradientView
          Align = baWidth
          Width = 718.1107
          Height = 17
          ShowHint = False
          BeginColor = 14548991
          EndColor = clYellow
          Style = gsVertical
        end
        object Memo20: TfrxMemoView
          Left = 384
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QySitPedidoVenda."valor_total">)]')
        end
        object Memo21: TfrxMemoView
          Left = 342
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo22: TfrxMemoView
          Left = 464
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QySitPedidoVenda."valor_recebido">)]')
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object QySitPedidoVenda: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT *'
      '   FROM cns_pedido_venda'
      '  ORDER BY ord_situacao')
    Params = <>
    Left = 90
    Top = 12
  end
  object frxQySitPedidoVenda: TfrxDBDataset
    UserName = 'QySitPedidoVenda'
    CloseDataSource = False
    DataSet = QySitPedidoVenda
    Left = 48
    Top = 12
  end
end
