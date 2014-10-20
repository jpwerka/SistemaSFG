inherited Vdp3008: TVdp3008
  Width = 308
  Caption = 'Vdp3008'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.7219019444
    ReportOptions.LastChange = 41297.857869456
    Datasets = <
      item
        DataSet = frxCnsReprComissao
        DataSetName = 'CnsReprComissao'
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
            'Representante x Comiss'#195#163'o')
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
        Top = 372
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
        Top = 260
        Width = 680.315401779394
        DataSet = frxCnsReprComissao
        DataSetName = 'CnsReprComissao'
        RowCount = 0
        object Memo3: TfrxMemoView
          Width = 85
          Height = 18
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsReprComissao."cod_pedido_venda"]')
        end
        object Memo35: TfrxMemoView
          Left = 88
          Width = 45
          Height = 18
          ShowHint = False
          DataField = 'seq_parcela'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsReprComissao."seq_parcela"]')
        end
        object Memo36: TfrxMemoView
          Left = 136
          Width = 130
          Height = 18
          ShowHint = False
          DataField = 'valor_base_calculo'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          Memo.UTF8 = (
            '[CnsReprComissao."valor_base_calculo"]')
        end
        object Memo37: TfrxMemoView
          Left = 269
          Width = 115
          Height = 18
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsReprComissao."valor_calculo"]')
        end
        object Memo38: TfrxMemoView
          Left = 460
          Width = 115
          Height = 18
          ShowHint = False
          Clipped = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsReprComissao."valor_comissao"]')
          WordWrap = False
        end
        object Memo4: TfrxMemoView
          Align = baRight
          Left = 580.315401779394
          Width = 100
          Height = 18
          ShowHint = False
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsReprComissao."data_calculo"]')
        end
        object Memo5: TfrxMemoView
          Left = 387
          Width = 70
          Height = 18
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2f'
          DisplayFormat.Kind = fkNumeric
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haRight
          Memo.UTF8 = (
            '[CnsReprComissao."perc_comissao"]')
        end
        object Line3: TfrxLineView
          Align = baWidth
          Top = 18
          Width = 680.315401779394
          ShowHint = False
          Frame.Color = clGray
          Diagonal = True
        end
      end
      object GroupHeader2: TfrxGroupHeader
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        Height = 59.57483
        ParentFont = False
        Top = 180
        Width = 680.315401779394
        Condition = 
          'VarToStr(<CnsReprComissao."cod_representante">)+Format('#39'%.2d'#39',[<' +
          'CnsReprComissao."mes_comissao">])+IntToStr(<CnsReprComissao."ano' +
          '_comissao">)'
        object Shape2: TfrxShapeView
          Align = baBottom
          Top = 40.6771922
          Width = 680.31540178
          Height = 18.8976378
          ShowHint = False
          Color = clScrollBar
          Frame.Color = clGray
        end
        object Memo6: TfrxMemoView
          Left = 88
          Top = 21.77953
          Width = 591
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = frxCnsReprComissao
          DataSetName = 'CnsReprComissao'
          Memo.UTF8 = (
            
              '[Format('#39'%.2d/%.4d'#39',[<CnsReprComissao."mes_comissao">,<CnsReprCo' +
              'missao."ano_comissao">])]')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 88
          Top = 3.77953
          Width = 484
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[IIF(Length(<CnsReprComissao."cpf_cnpj">)>0,IIF(<CnsReprComissao' +
              '."tipo_pessoa">='#39'J'#39',FormatMaskText('#39'!00.000.000/0000-00;0;_'#39',<Cn' +
              'sReprComissao."cpf_cnpj">) + '#39' - '#39',FormatMaskText('#39'!000.000.000-' +
              '00;0;_'#39',<CnsReprComissao."cpf_cnpj">) + '#39' - '#39'),'#39#39')][CnsReprComis' +
              'sao."den_representante"]')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Top = 3.77953
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
            'Representante:')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Top = 21.77953
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
            'M'#195#170's/Ano:')
          ParentFont = False
          WordWrap = False
        end
        object Memo1: TfrxMemoView
          Top = 41.57483
          Width = 85
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Pedido Venda')
          ParentFont = False
          WordWrap = False
        end
        object Memo31: TfrxMemoView
          Left = 88
          Top = 41.57483
          Width = 45
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Parcela')
          ParentFont = False
        end
        object Memo34: TfrxMemoView
          Left = 136
          Top = 41.57483
          Width = 130
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor Base')
          ParentFont = False
        end
        object Memo32: TfrxMemoView
          Left = 269
          Top = 41.57483
          Width = 115
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor C'#195#161'lculo')
          ParentFont = False
        end
        object Memo13: TfrxMemoView
          Left = 387
          Top = 41.57483
          Width = 70
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '% Comiss'#195#163'o')
          ParentFont = False
        end
        object Memo2: TfrxMemoView
          Left = 460
          Top = 41.57483
          Width = 115
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor Comiss'#195#163'o')
          ParentFont = False
        end
        object Memo33: TfrxMemoView
          Left = 578
          Top = 41.57483
          Width = 100
          Height = 18
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          Frame.Color = clGray
          HAlign = haCenter
          Memo.UTF8 = (
            'Data C'#195#161'lculo')
          ParentFont = False
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
        Top = 296
        Width = 680.315401779394
        object Shape1: TfrxShapeView
          Align = baClient
          Width = 680.315401779394
          Height = 17
          ShowHint = False
          Color = clYellow
          Frame.Color = clGray
          Frame.Typ = [ftLeft, ftRight, ftTop, ftBottom]
        end
        object Memo20: TfrxMemoView
          Left = 269
          Top = 1
          Width = 115
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsReprComissao."valor_calculo">)]')
        end
        object Memo21: TfrxMemoView
          Top = 1
          Width = 266
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo22: TfrxMemoView
          Left = 460
          Top = 1
          Width = 115
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsReprComissao."valor_comissao">)]')
        end
      end
    end
  end
  object frxCnsReprComissao: TfrxDBDataset
    UserName = 'CnsReprComissao'
    CloseDataSource = False
    DataSet = CnsReprComissao
    Left = 52
    Top = 12
  end
  object CnsReprComissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    AutoCalcFields = False
    CachedUpdates = True

    SQL.Strings = (
      
        'SELECT r.cod_representante, r.den_representante, r.cpf_cnpj, r.t' +
        'ipo_pessoa,'
      
        '       cr.ano_comissao, cr.mes_comissao, cr.cod_pedido_venda, cr' +
        '.seq_parcela,'
      '       cr.valor_calculo, cr.perc_comissao, cr.valor_comissao,'
      
        '       CASE WHEN cr.valor_base_calculo = 1 THEN '#39'Valor Faturado'#39 +
        ' ELSE '#39'Valor Recebido'#39' END valor_base_calculo,'
      '       cr.data_calculo, cr.cod_conta_pagar'
      '  FROM tbl_comissao_representante cr'
      ' INNER JOIN tbl_representante r'
      '    ON r.cod_representante = cr.cod_representante'
      ' WHERE cr.cod_representante = :cod_representante'
      '   AND cr.ano_comissao = :ano_comissao'
      '   AND cr.mes_comissao = :mes_comissao'
      ' ORDER BY cr. cod_representante, cod_pedido_venda, seq_parcela')
    Params = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = 'CE001'
      end
      item
        DataType = ftInteger
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '12'
      end
      item
        DataType = ftInteger
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
    Left = 90
    Top = 10
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_representante'
        ParamType = ptUnknown
        Size = 15
        Value = 'CE001'
      end
      item
        DataType = ftInteger
        Name = 'mes_comissao'
        ParamType = ptUnknown
        Value = '12'
      end
      item
        DataType = ftInteger
        Name = 'ano_comissao'
        ParamType = ptUnknown
        Value = '2012'
      end>
  end
end
