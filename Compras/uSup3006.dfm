inherited Sup3006: TSup3006
  Caption = 'Sup3006'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6684508796
    ReportOptions.LastChange = 41112.6684508796
    Left = 18
    Top = 18
    Datasets = <
      item
        DataSet = frxQyCctPedidoCompra
        DataSetName = 'QyCctPedidoCompra'
      end
      item
        DataSet = frxQyCentroCusto
        DataSetName = 'QyCentroCusto'
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
            'Centro Custo x Pedidos de Compra')
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
        Condition = 'QyCctPedidoCompra."cod_centro_custo"'
        object Memo5: TfrxMemoView
          Top = 1.88976378
          Width = 624
          Height = 19
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[QyCctPedidoCompra."cod_centro_custo"] - [QyCentroCusto."den_cen' +
              'tro_custo"]')
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
          Left = 390
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
          Left = 556
          Top = 1
          Width = 74
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Valor Pago:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Left = 487
          Top = 1
          Width = 63
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
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
            'Conta Cont'#195#161'bil:')
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
        DataSet = frxQyCctPedidoCompra
        DataSetName = 'QyCctPedidoCompra'
        RowCount = 0
        object Memo13: TfrxMemoView
          Top = 1
          Width = 52
          Height = 16
          ShowHint = False
          DataField = 'cod_pedido_compra'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCctPedidoCompra."cod_pedido_compra"]')
        end
        object Memo14: TfrxMemoView
          Left = 398
          Top = 1
          Width = 71
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'data_cadastro'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyCctPedidoCompra."data_cadastro"]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 550
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_pago'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCctPedidoCompra."valor_pago"]')
        end
        object Memo16: TfrxMemoView
          Left = 468
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_total'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCctPedidoCompra."valor_total"]')
        end
        object Memo17: TfrxMemoView
          Left = 316
          Top = 1
          Width = 66
          Height = 15
          ShowHint = False
          Clipped = False
          DataField = 'den_situacao'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          Memo.UTF8 = (
            '[QyCctPedidoCompra."den_situacao"]')
          WordWrap = False
        end
        object Memo18: TfrxMemoView
          Align = baRight
          Left = 638.1107
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'cod_plano_conta'
          DataSet = frxQyCctPedidoCompra
          DataSetName = 'QyCctPedidoCompra'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyCctPedidoCompra."cod_plano_conta"]')
        end
        object Memo19: TfrxMemoView
          Left = 56
          Top = 1
          Width = 253
          Height = 15
          ShowHint = False
          Memo.UTF8 = (
            
              '[QyCctPedidoCompra."cod_fornecedor"] - [QyCctPedidoCompra."den_f' +
              'ornecedor"]')
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
        object Shape1: TfrxShapeView
          Align = baWidth
          Width = 718.1107
          Height = 17
          ShowHint = False
          Color = clYellow
          Frame.Color = clNone
        end
        object Memo20: TfrxMemoView
          Left = 468
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyCctPedidoCompra."valor_total">)]')
        end
        object Memo21: TfrxMemoView
          Left = 423.55906
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
          Left = 550.77953
          Top = 1
          Width = 79.22047
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyCctPedidoCompra."valor_pago">)]')
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
  object QyCctPedidoCompra: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT *'
      '   FROM cns_pedido_compra'
      '  ORDER BY cod_centro_custo')
    Params = <>
    Left = 204
    Top = 6
  end
  object QyCentroCusto: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT cod_centro_custo, den_centro_custo FROM tbl_centro_custo'
      ' WHERE cod_centro_custo = :cod_centro_custo')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_centro_custo'
        ParamType = ptUnknown
      end>
    DataSource = DsCctPedidoCompra
    Left = 168
    Top = 6
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_centro_custo'
        ParamType = ptUnknown
      end>
  end
  object DsCctPedidoCompra: TDataSource
    DataSet = QyCctPedidoCompra
    Left = 132
    Top = 6
  end
  object frxQyCentroCusto: TfrxDBDataset
    UserName = 'QyCentroCusto'
    CloseDataSource = False
    DataSet = QyCentroCusto
    Left = 49
    Top = 12
  end
  object frxQyCctPedidoCompra: TfrxDBDataset
    UserName = 'QyCctPedidoCompra'
    CloseDataSource = False
    DataSet = QyCctPedidoCompra
    Left = 90
    Top = 12
  end
end
