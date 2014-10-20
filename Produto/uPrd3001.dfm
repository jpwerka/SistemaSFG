inherited Prd3001: TPrd3001
  Caption = 'Rela'#231#227'o de Produtos'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    Datasets = <
      item
        DataSet = frxTbCnsProduto
        DataSetName = 'TbCnsProduto'
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
            'Lista de Produtos')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
      end
      inherited RodPagina: TfrxPageFooter
        Top = 332
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
          Left = 265.157702066691
          Top = 0.99999998430675
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Top = 0.99999998430675
          Width = 88.45671
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
        Condition = 'UpperCase(COPY(<TbCnsProduto."den_produto">,1,1))'
        ReprintOnNewPage = True
        object Memo5: TfrxMemoView
          Align = baClient
          Width = 680.315401779394
          Height = 20.78740157
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '[UpperCase(COPY(<TbCnsProduto."den_produto">,1,1))]')
          WordWrap = False
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
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
          Width = 84
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Qtde Estoque:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 554
          Top = 1
          Width = 84
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Pre'#195#167'o Custo:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Align = baRight
          Left = 642.315401779394
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Ativo?')
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
        DataSet = frxTbCnsProduto
        DataSetName = 'TbCnsProduto'
        RowCount = 0
        object Memo11: TfrxMemoView
          Top = 1
          Width = 68
          Height = 16
          ShowHint = False
          DataField = 'cod_produto'
          DataSet = frxTbCnsProduto
          DataSetName = 'TbCnsProduto'
          HAlign = haRight
          Memo.UTF8 = (
            '[TbCnsProduto."cod_produto"]')
        end
        object Memo12: TfrxMemoView
          Left = 72
          Top = 1
          Width = 390
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_produto'
          DataSet = frxTbCnsProduto
          DataSetName = 'TbCnsProduto'
          Memo.UTF8 = (
            '[TbCnsProduto."den_produto"]')
          WordWrap = False
        end
        object Memo13: TfrxMemoView
          Left = 466
          Top = 1
          Width = 84
          Height = 16
          ShowHint = False
          Clipped = False
          DataSet = frxTbCnsProduto
          DataSetName = 'TbCnsProduto'
          DisplayFormat.FormatStr = '%2.3n'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[TbCnsProduto."qtd_estoque"]')
          WordWrap = False
        end
        object Memo14: TfrxMemoView
          Left = 554
          Top = 1
          Width = 84
          Height = 16
          ShowHint = False
          Clipped = False
          DataSet = frxTbCnsProduto
          DataSetName = 'TbCnsProduto'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[TbCnsProduto."preco_custo"]')
          WordWrap = False
        end
        object CheckBox1: TfrxCheckBoxView
          Left = 656
          Width = 18
          Height = 18
          ShowHint = False
          CheckColor = clBlack
          CheckStyle = csCross
          Expression = 'IIF(<TbCnsProduto."ies_ativo">='#39'S'#39',1,0)'
        end
        object Line4: TfrxLineView
          Align = baWidth
          Width = 680.315401779394
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object TbCnsProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_produto, den_produto, preco_custo,'
      '       qtd_estoque, ies_ativo'
      '  FROM tbl_produto'
      ' ORDER BY den_produto, cod_produto')
    Params = <>
    Left = 90
    Top = 14
  end
  object frxTbCnsProduto: TfrxDBDataset
    UserName = 'TbCnsProduto'
    CloseDataSource = False
    FieldAliases.Strings = (
      'cod_produto=cod_produto'
      'den_produto=den_produto'
      'preco_custo=preco_custo'
      'qtd_estoque=qtd_estoque'
      'ies_ativo=ies_ativo')
    DataSet = TbCnsProduto
    Left = 54
    Top = 12
  end
end
