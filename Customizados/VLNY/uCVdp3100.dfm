inherited CVdp3100: TCVdp3100
  Width = 308
  Caption = 'CVdp3100'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.7219019444
    ReportOptions.LastChange = 41216.8873133681
    Datasets = <
      item
        DataSet = frxCnsPedidoVenda
        DataSetName = 'CnsPedidoVenda'
      end
      item
        DataSet = frxCnsProdutos
        DataSetName = 'CnsProdutos'
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
        Width = 680.315401779394
        inherited Titulo: TfrxMemoView
          Width = 680.315401779394
          Memo.UTF8 = (
            'Amostragem x Representante')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
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
        Top = 456
        Width = 680.315401779394
        inherited RodLivre01: TfrxMemoView
          Left = 265.157702066691
          Top = 1.13385827
          Memo.UTF8 = (
            'RodLivre01')
        end
        inherited RodLivre02: TfrxMemoView
          Left = 265.157702066691
          Top = 0.99999998430675
          Memo.UTF8 = (
            'RodLivre02')
        end
        inherited DataHora: TfrxMemoView
          Left = 265.157702064697
          Top = 0.99999998
          Width = 149.99999765
          Height = 14.99999976
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Top = 0.99999998430675
          Memo.UTF8 = (
            'Joinville - SC')
        end
        inherited PaginaNr: TfrxMemoView
          Left = 530.315404133382
          Top = 0.99999998430675
          Memo.UTF8 = (
            'P'#195#161'gina [Page#]')
        end
        inherited Line5: TfrxLineView
          Width = 680.315401779394
          Frame.Color = clDefault
        end
      end
      object MasterData1: TfrxMasterData
        Height = 18
        Top = 220
        Width = 680.315401779394
        DataSet = frxCnsPedidoVenda
        DataSetName = 'CnsPedidoVenda'
        RowCount = 0
        object Memo6: TfrxMemoView
          Left = 175
          Top = 2
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
        object Memo10: TfrxMemoView
          Left = 118
          Top = 2
          Width = 54
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
          Left = 376
          Top = 2
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
          Left = 430
          Top = 2
          Width = 125
          Height = 15
          ShowHint = False
          Memo.UTF8 = (
            
              '[IIF(<CnsPedidoVenda."ies_situacao"> = '#39'A'#39','#39'Aberto'#39',IIF(<CnsPedi' +
              'doVenda."ies_situacao"> = '#39'F'#39','#39'Fechado'#39',IIF(<CnsPedidoVenda."ies' +
              '_situacao"> = '#39'T'#39','#39'Faturado'#39','#39'Cancelado'#39')))]')
        end
        object Memo2: TfrxMemoView
          Left = 46
          Top = 2
          Width = 71
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = frxCnsPedidoVenda
          DataSetName = 'CnsPedidoVenda'
          Memo.UTF8 = (
            '[CnsPedidoVenda."cod_pedido_venda"]')
          WordWrap = False
        end
        object Memo3: TfrxMemoView
          Align = baLeft
          Top = 2
          Width = 42
          Height = 15
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            'Pedido:')
          ParentFont = False
          WordWrap = False
        end
        object Memo4: TfrxMemoView
          Left = 560
          Top = 2
          Width = 34
          Height = 15
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            'Total:')
          ParentFont = False
          WordWrap = False
        end
        object Memo5: TfrxMemoView
          Align = baRight
          Left = 600.315401779394
          Top = 2
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = []
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsPedidoVenda."valor_total"]')
          ParentFont = False
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
        Top = 336
        Width = 680.315401779394
        object Shape1: TfrxShapeView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          Color = clSilver
          Frame.Color = clGray
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
        Top = 376
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
          DisplayFormat.FormatStr = '%2.3n'
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
        Height = 20
        Top = 180
        Width = 680.315401779394
        Condition = 'CnsPedidoVenda."cod_representante"'
        object Memo1: TfrxMemoView
          Align = baWidth
          Top = 2
          Width = 680.315401779394
          Height = 16
          ShowHint = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -15
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            
              '[CnsPedidoVenda."cod_representante"]-[CnsPedidoVenda."den_repres' +
              'entante"]')
          ParentFont = False
        end
      end
      object GroupHeader1: TfrxGroupHeader
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 296
        Width = 680.315401779394
        Child = RpRelatBase.Child2
        Condition = 'CnsPedidoVenda."cod_pedido_venda"'
        object Memo7: TfrxMemoView
          Align = baLeft
          Width = 80
          Height = 16
          ShowHint = False
          Memo.UTF8 = (
            'Itens:')
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
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 22
        ParentFont = False
        Top = 256
        Width = 680.315401779394
        object Shape2: TfrxShapeView
          Align = baBottom
          Top = 4
          Width = 680.31540178
          Height = 18
          ShowHint = False
          Color = clYellow
          Frame.Color = clNone
        end
        object Memo8: TfrxMemoView
          Align = baRight
          Left = 560.315401779394
          Top = 4
          Width = 120
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsPedidoVenda."valor_total">,MasterData1)]')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 516
          Top = 4
          Width = 42
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Total:')
          WordWrap = False
        end
      end
    end
  end
  object CnsPedidoVenda: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT r.cod_representante, r.den_representante,'
      '       v.cod_pedido_venda, v.data_cadastro, '
      '       v.ies_situacao, v.valor_total'
      '  FROM tbl_pedido_venda v,'
      '       tbl_representante r'
      ' WHERE v.cod_cliente = r.cod_representante '
      ' ORDER BY r.cod_representante , v.cod_pedido_venda')
    Params = <>
    Left = 162
    Top = 6
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
      ' WHERE v.cod_produto = p.cod_produto'
      ' ORDER BY v.cod_pedido_venda, v.seq_produto')
    Params = <>
    MasterFields = 'cod_pedido_venda'
    MasterSource = DsPedidoVenda
    LinkedFields = 'cod_pedido_venda'
    Left = 228
    Top = 6
  end
  object DsPedidoVenda: TDataSource
    DataSet = CnsPedidoVenda
    Left = 192
    Top = 6
  end
  object frxCnsPedidoVenda: TfrxDBDataset
    UserName = 'CnsPedidoVenda'
    CloseDataSource = False
    FieldAliases.Strings = (
      'cod_representante=cod_representante'
      'den_representante=den_representante'
      'cod_pedido_venda=cod_pedido_venda'
      'data_cadastro=data_cadastro'
      'ies_situacao=ies_situacao'
      'valor_total=valor_total')
    DataSet = CnsPedidoVenda
    Left = 48
    Top = 12
  end
  object frxCnsProdutos: TfrxDBDataset
    UserName = 'CnsProdutos'
    CloseDataSource = False
    FieldAliases.Strings = (
      'cod_pedido_venda=cod_pedido_venda'
      'seq_produto=seq_produto'
      'cod_produto=cod_produto'
      'den_produto=den_produto'
      'qtd_produto=qtd_produto'
      'preco_venda=preco_venda'
      'val_desconto=val_desconto'
      'valor_total=valor_total')
    DataSet = CnsProdutos
    Left = 78
    Top = 12
  end
end
