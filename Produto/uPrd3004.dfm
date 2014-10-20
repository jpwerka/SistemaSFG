inherited Prd3004: TPrd3004
  Caption = 'Prd3004'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.LastChange = 41155.9770057407
    Datasets = <
      item
        DataSet = frxQyEstoque
        DataSetName = 'QyEstoque'
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
            'Consulta de Estoque')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
      end
      inherited RodPagina: TfrxPageFooter
        Top = 412
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
          Width = 113.38582677
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
        Condition = 'QyEstoque."cod_familia"'
        ReprintOnNewPage = True
        object Memo5: TfrxMemoView
          Align = baClient
          Width = 680.315401779394
          Height = 20.78740157
          ShowHint = False
          Clipped = False
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -15
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[QyEstoque."cod_familia"] - [QyEstoque."den_familia"]')
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
        Height = 17
        ParentFont = False
        Top = 220
        Width = 680.315401779394
        object Memo6: TfrxMemoView
          Left = 24
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
          Left = 75
          Top = 1
          Width = 58
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Descri'#195#167#195#163'oo:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 367
          Top = 1
          Width = 78
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Qtde Estoque:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 460
          Top = 1
          Width = 73
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Qtde M'#195#173'nima:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Align = baRight
          Left = 659.315401779394
          Top = 1
          Width = 21
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'UM:')
          WordWrap = False
        end
        object Memo11: TfrxMemoView
          Left = 598
          Top = 1
          Width = 33
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Valor:')
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
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        Height = 17
        ParentFont = False
        Top = 256
        Width = 680.315401779394
        DataSet = frxQyEstoque
        DataSetName = 'QyEstoque'
        RowCount = 0
        object Memo12: TfrxMemoView
          Left = 75
          Top = 1
          Width = 228.29932
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_produto'
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          Memo.UTF8 = (
            '[QyEstoque."den_produto"]')
          WordWrap = False
        end
        object Memo13: TfrxMemoView
          Left = 3
          Top = 1
          Width = 65
          Height = 16
          ShowHint = False
          DataField = 'cod_produto'
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyEstoque."cod_produto"]')
        end
        object Memo14: TfrxMemoView
          Align = baRight
          Left = 653.315401779394
          Top = 1
          Width = 27
          Height = 16
          ShowHint = False
          DataField = 'cod_unid_medida'
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyEstoque."cod_unid_medida"]')
        end
        object Memo15: TfrxMemoView
          Left = 383
          Top = 1
          Width = 61
          Height = 16
          ShowHint = False
          Clipped = False
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          DisplayFormat.DecimalSeparator = ','
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Highlight.Font.Charset = DEFAULT_CHARSET
          Highlight.Font.Color = clRed
          Highlight.Font.Height = -11
          Highlight.Font.Name = 'Arial'
          Highlight.Font.Style = [fsBold]
          Highlight.Condition = 
            'IIF(<QyEstoque."qtd_estoque"><=<QyEstoque."qtd_estoque_min">,1,0' +
            ')'
          Memo.UTF8 = (
            '[QyEstoque."qtd_estoque"]')
          WordWrap = False
        end
        object Memo16: TfrxMemoView
          Left = 450
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyEstoque."qtd_estoque_min"]')
        end
        object Memo17: TfrxMemoView
          Left = 558
          Top = 1
          Width = 70
          Height = 16
          ShowHint = False
          Clipped = False
          DataSet = frxQyEstoque
          DataSetName = 'QyEstoque'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyEstoque."valor_estoque"]')
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
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18.8976378
        ParentFont = False
        Top = 292
        Width = 680.315401779394
        object Shape1: TfrxShapeView
          Align = baWidth
          Width = 680.315401779394
          Height = 18.8976378
          ShowHint = False
          Color = clSilver
          Frame.Color = clNone
        end
        object Memo18: TfrxMemoView
          Left = 282
          Top = 1
          Width = 43
          Height = 20
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo19: TfrxMemoView
          Left = 337
          Top = 1
          Width = 110
          Height = 20
          ShowHint = False
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyEstoque."qtd_estoque">)]')
        end
        object Memo20: TfrxMemoView
          Left = 510
          Top = 1
          Width = 118
          Height = 20
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyEstoque."valor_estoque">)]')
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object ReportSummary1: TfrxReportSummary
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18.8976378
        ParentFont = False
        Top = 372
        Width = 680.315401779394
        object Shape2: TfrxShapeView
          Align = baWidth
          Width = 680.315401779394
          Height = 18.8976378
          ShowHint = False
          Color = clYellow
          Frame.Color = clNone
        end
        object Memo1: TfrxMemoView
          Left = 281.90569
          Width = 43
          Height = 20
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo2: TfrxMemoView
          Left = 336.90569
          Width = 110
          Height = 20
          ShowHint = False
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyEstoque."qtd_estoque">)]')
          WordWrap = False
        end
        object Memo3: TfrxMemoView
          Left = 509.90569
          Width = 118
          Height = 20
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyEstoque."valor_estoque">)]')
          WordWrap = False
        end
        object Line7: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object QyEstoque: TZQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT p.cod_familia, f.den_familia, '
      '       p.cod_produto, p.den_produto,'
      '       p.qtd_estoque, p.qtd_estoque_min, '
      '       (p.preco_custo * p.qtd_estoque) valor_estoque,'
      '       p.cod_unid_medida'
      '  FROM tbl_produto p,'
      '       tbl_familia f'
      ' WHERE p.cod_familia = f.cod_familia'
      ' ORDER BY p.cod_familia,p.cod_produto')
    Params = <>
    Left = 146
    Top = 12
  end
  object frxQyEstoque: TfrxDBDataset
    UserName = 'QyEstoque'
    CloseDataSource = False
    DataSet = QyEstoque
    Left = 108
    Top = 12
  end
end
