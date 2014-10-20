inherited Sup3010: TSup3010
  Caption = 'Sup3010'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.9486002546
    ReportOptions.LastChange = 41112.9486002546
    Datasets = <
      item
        DataSet = frxQyFornecEnd
        DataSetName = 'QyFornecEnd'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      inherited CabPagina: TfrxPageHeader
        Height = 49
        Top = 16
        Width = 680.315401779394
        Child = RpRelatBase.Child1
        inherited Logotipo: TfrxPictureView
          Width = 169
          Height = 47
        end
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
            'Fornecedor x Estado x Cidade')
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
        Height = 18
        Top = 372
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
        Font.Height = -16
        Font.Name = 'Times New Roman'
        Font.Style = [fsBold]
        Height = 20
        ParentFont = False
        Top = 180
        Width = 680.315401779394
        Condition = 'QyFornecEnd."cod_uf"'
        StartNewPage = True
        object Memo5: TfrxMemoView
          Align = baClient
          Width = 680.315401779394
          Height = 20
          ShowHint = False
          Clipped = False
          DataField = 'cod_uf'
          DataSet = frxQyFornecEnd
          DataSetName = 'QyFornecEnd'
          Font.Charset = ANSI_CHARSET
          Font.Color = clNavy
          Font.Height = -15
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[QyFornecEnd."cod_uf"]')
          ParentFont = False
          WordWrap = False
        end
      end
      object GroupHeader2: TfrxGroupHeader
        Font.Charset = ANSI_CHARSET
        Font.Color = clTeal
        Font.Height = -13
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 19
        ParentFont = False
        Top = 220
        Width = 680.315401779394
        Child = RpRelatBase.Child2
        Condition = 'QyFornecEnd."den_cidade"'
        object Memo6: TfrxMemoView
          Left = 18
          Width = 662
          Height = 17
          ShowHint = False
          Clipped = False
          DataField = 'den_cidade'
          DataSet = frxQyFornecEnd
          DataSetName = 'QyFornecEnd'
          Font.Charset = ANSI_CHARSET
          Font.Color = clTeal
          Font.Height = -12
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[QyFornecEnd."den_cidade"]')
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
        Top = 260
        Width = 680.315401779394
        object Memo7: TfrxMemoView
          Width = 86
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Fornecedor:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 88
          Width = 592
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Nome Completo:')
          WordWrap = False
        end
        object Line3: TfrxLineView
          Align = baBottom
          Top = 17
          Width = 681
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
        Top = 296
        Width = 680.315401779394
        DataSet = frxQyFornecEnd
        DataSetName = 'QyFornecEnd'
        RowCount = 0
        object Memo9: TfrxMemoView
          Top = 1
          Width = 86
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'cod_fornecedor'
          DataSet = frxQyFornecEnd
          DataSetName = 'QyFornecEnd'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyFornecEnd."cod_fornecedor"]')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Left = 88
          Top = 1
          Width = 592
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_fornecedor'
          DataSet = frxQyFornecEnd
          DataSetName = 'QyFornecEnd'
          Memo.UTF8 = (
            '[QyFornecEnd."den_fornecedor"]')
          WordWrap = False
        end
        object Line4: TfrxLineView
          Align = baBottom
          Top = 17
          Width = 681
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object QyFornecEnd: TZQuery
    Connection = SfgDataCenter.AppConnection

    SQL.Strings = (
      'SELECT c.cod_uf, c.den_cidade,'
      '       f.cod_fornecedor, f.den_fornecedor'
      '  FROM tbl_fornecedor f,'
      '       tbl_cidade c'
      ' WHERE f.cod_cidade = c.cod_cidade'
      ' ORDER BY c.cod_uf, c.den_cidade, f.den_fornecedor ')
    Params = <>
    Left = 86
    Top = 14
  end
  object frxQyFornecEnd: TfrxDBDataset
    UserName = 'QyFornecEnd'
    CloseDataSource = False
    DataSet = QyFornecEnd
    Left = 48
    Top = 12
  end
end
