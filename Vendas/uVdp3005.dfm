inherited Vdp3005: TVdp3005
  Left = 421
  Top = 290
  Width = 220
  Height = 115
  Caption = 'Vdp3005'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6684074768
    ReportOptions.LastChange = 41112.6684074768
    Datasets = <
      item
        DataSet = frxQyCntPedidoVenda
        DataSetName = 'QyCntPedidoVenda'
      end
      item
        DataSet = frxQyContaContabil
        DataSetName = 'QyContaContabil'
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
            'Conta Cont'#195#161'bil x Pedidos de Venda')
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
          Top = 0.99999998430675
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
            'P'#195#161'gina [Page#]')
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
        Condition = 'QyCntPedidoVenda."cod_plano_conta"'
        object Memo5: TfrxMemoView
          Top = 1.88976378
          Width = 624
          Height = 19
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[QyCntPedidoVenda."cod_plano_conta"] - [QyContaContabil."den_pla' +
              'no_conta"]')
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
            'C'#195#179'digo:')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 316
          Top = 1
          Width = 50
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Situa'#195#167#195#163'o:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 385
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
          Left = 553
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
          Left = 482
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
          Left = 635
          Top = 1
          Width = 78
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Centro Custo:')
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
        DataSet = frxQyCntPedidoVenda
        DataSetName = 'QyCntPedidoVenda'
        RowCount = 0
        object Memo13: TfrxMemoView
          Top = 1
          Width = 52
          Height = 16
          ShowHint = False
          DataField = 'cod_pedido_venda'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCntPedidoVenda."cod_pedido_venda"]')
        end
        object Memo14: TfrxMemoView
          Left = 393
          Top = 1
          Width = 71
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'data_cadastro'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyCntPedidoVenda."data_cadastro"]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 545
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_recebido'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCntPedidoVenda."valor_recebido"]')
        end
        object Memo16: TfrxMemoView
          Left = 463
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_total'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCntPedidoVenda."valor_total"]')
        end
        object Memo17: TfrxMemoView
          Left = 316
          Top = 1
          Width = 66
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_situacao'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          Memo.UTF8 = (
            '[QyCntPedidoVenda."den_situacao"]')
          WordWrap = False
        end
        object Memo18: TfrxMemoView
          Left = 630
          Top = 1
          Width = 88
          Height = 16
          ShowHint = False
          DataField = 'cod_centro_custo'
          DataSet = frxQyCntPedidoVenda
          DataSetName = 'QyCntPedidoVenda'
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyCntPedidoVenda."cod_centro_custo"]')
        end
        object Memo19: TfrxMemoView
          Left = 56
          Top = 1
          Width = 253
          Height = 16
          ShowHint = False
          Memo.UTF8 = (
            
              '[QyCntPedidoVenda."cod_cliente"] - [QyCntPedidoVenda."den_client' +
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
          Left = 463
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyCntPedidoVenda."valor_total">)]')
        end
        object Memo21: TfrxMemoView
          Left = 421
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
          Left = 543
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyCntPedidoVenda."valor_recebido">)]')
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
  object QyCntPedidoVenda: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT *'
      '   FROM cns_pedido_venda'
      '  ORDER BY cod_plano_conta')
    Params = <>
    Left = 114
    Top = 12
  end
  object DsCctPedidoVenda: TDataSource
    DataSet = QyCntPedidoVenda
    Left = 48
    Top = 12
  end
  object QyContaContabil: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT cod_plano_conta, den_plano_conta FROM tbl_plano_conta'
      ' WHERE cod_plano_conta = :cod_plano_conta')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
      end>
    DataSource = DsCctPedidoVenda
    Left = 84
    Top = 12
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
      end>
  end
  object frxQyCntPedidoVenda: TfrxDBDataset
    UserName = 'QyCntPedidoVenda'
    CloseDataSource = False
    DataSet = QyCntPedidoVenda
    Left = 12
    Top = 48
  end
  object frxQyContaContabil: TfrxDBDataset
    UserName = 'QyContaContabil'
    CloseDataSource = False
    DataSet = QyContaContabil
    Left = 48
    Top = 48
  end
end
