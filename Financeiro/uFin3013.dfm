inherited Fin3013: TFin3013
  Width = 308
  Caption = 'Fin3013'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.7219019444
    ReportOptions.LastChange = 41297.9818976042
    Datasets = <
      item
        DataSet = frxCnsContaPagar
        DataSetName = 'CnsContaPagar'
      end
      item
        DataSet = frxCnsPagtos
        DataSetName = 'CnsPagtos'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      inherited CabPagina: TfrxPageHeader
        Top = 18.89765
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
        Top = 90.70872
        Width = 680.315401779394
        inherited Titulo: TfrxMemoView
          Width = 680.315401779394
          Memo.UTF8 = (
            'Conta Pagar')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
        object Memo5: TfrxMemoView
          Left = 430.66141
          Width = 266
          Height = 35
          ShowHint = False
          Clipped = False
          DataField = 'cod_conta_pagar'
          DataSet = frxCnsContaPagar
          DataSetName = 'CnsContaPagar'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -29
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[CnsContaPagar."cod_conta_pagar"]')
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
        Top = 544.25232
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
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = []
        Height = 60
        ParentFont = False
        Top = 185.19697
        Width = 680.315401779394
        DataSet = frxCnsContaPagar
        DataSetName = 'CnsContaPagar'
        RowCount = 0
        object Memo6: TfrxMemoView
          Left = 73
          Top = 6
          Width = 71
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = frxCnsContaPagar
          DataSetName = 'CnsContaPagar'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Memo.UTF8 = (
            '[CnsContaPagar."data_cadastro"]')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 73
          Top = 24
          Width = 608
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[IIF(Length(<CnsContaPagar."cpf_cnpj">)>0,IIF(<CnsContaPagar."ti' +
              'po_pessoa">='#39'J'#39',FormatMaskText('#39'!00.000.000/0000-00;0;_'#39',<CnsCon' +
              'taPagar."cpf_cnpj">) + '#39' - '#39',FormatMaskText('#39'!000.000.000-00;0;_' +
              #39',<CnsContaPagar."cpf_cnpj">) + '#39' - '#39'),'#39#39')][CnsContaPagar."den_f' +
              'ornecedor"]')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 73
          Top = 42
          Width = 608
          Height = 15
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[CnsContaPagar."logradouro"][IIF(<CnsContaPagar."numero"><>0,'#39', ' +
              #39'+IntToStr(<CnsContaPagar."numero">),'#39#39')][IIF(Length(<CnsContaPa' +
              'gar."bairro">)>0,'#39' - '#39' + <CnsContaPagar."bairro">,'#39#39')][IIF(Lengt' +
              'h(<CnsContaPagar."den_cidade">)>0,'#39' - '#39' + <CnsContaPagar."den_ci' +
              'dade"> + '#39' - '#39' + <CnsContaPagar."cod_uf">,'#39#39')]')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Top = 24
          Width = 70
          Height = 17
          ShowHint = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Fornecedor:')
          ParentFont = False
        end
        object Memo10: TfrxMemoView
          Top = 6
          Width = 70
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
          Left = 496
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
          Left = 550
          Top = 6
          Width = 125
          Height = 15
          ShowHint = False
          Memo.UTF8 = (
            
              '[IIF(<CnsContaPagar."ies_situacao"> = '#39'P'#39','#39'Pendente'#39',IIF(<CnsCon' +
              'taPagar."ies_situacao"> = '#39'A'#39','#39'Andamento'#39',IIF(<CnsContaPagar."ie' +
              's_situacao"> = '#39'L'#39','#39'Liquidado'#39','#39'Cancelado'#39')))]')
        end
        object Memo13: TfrxMemoView
          Top = 42
          Width = 70
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
        object Memo4: TfrxMemoView
          Left = 276
          Top = 6
          Width = 159
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = Fin3012.frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          Memo.UTF8 = (
            '[CnsContaPagar."num_documento"]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 204
          Top = 6
          Width = 70
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
            'Documento:')
          ParentFont = False
          WordWrap = False
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
        Top = 268.34663
        Width = 680.315401779394
        Child = RpRelatBase.Child3
        Condition = 'CnsContaPagar."cod_conta_pagar"'
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
          DataSet = frxCnsContaPagar
          DataSetName = 'CnsContaPagar'
          Memo.UTF8 = (
            '[CnsContaPagar."den_forma_pagto"]')
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
        Top = 317.48052
        Width = 680.315401779394
        object Shape2: TfrxShapeView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          Color = clSilver
          Frame.Color = clGray
        end
        object Memo31: TfrxMemoView
          Width = 45
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Parcela')
        end
        object Memo32: TfrxMemoView
          Left = 45
          Width = 100
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Valor')
        end
        object Memo33: TfrxMemoView
          Left = 146
          Width = 70
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Vencimento')
        end
        object Memo3: TfrxMemoView
          Left = 216
          Width = 25
          Height = 16
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Pg?')
        end
        object Memo16: TfrxMemoView
          Left = 241
          Width = 70
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            'Pagamento')
        end
        object Memo34: TfrxMemoView
          Left = 311
          Width = 369
          Height = 18
          ShowHint = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Observa'#195#167#195#163'o')
        end
      end
      object DetailData2: TfrxDetailData
        Height = 18
        Top = 359.05535
        Width = 680.315401779394
        DataSet = frxCnsPagtos
        DataSetName = 'CnsPagtos'
        RowCount = 0
        object Memo35: TfrxMemoView
          Width = 45
          Height = 18
          ShowHint = False
          DataSet = Fin3012.frxCnsPagtos
          DataSetName = 'CnsPagtos'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsPagtos."seq_parcela"]')
        end
        object Memo36: TfrxMemoView
          Left = 45
          Width = 100
          Height = 18
          ShowHint = False
          DataSet = Fin3012.frxCnsPagtos
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
          Left = 146
          Width = 70
          Height = 18
          ShowHint = False
          DataSet = Fin3012.frxCnsPagtos
          DataSetName = 'CnsPagtos'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            '[CnsPagtos."data_vencimento"]')
        end
        object CheckBox1: TfrxCheckBoxView
          Left = 216
          Width = 25
          Height = 18
          ShowHint = False
          CheckColor = clBlack
          CheckStyle = csCross
          Expression = 'IIF(<CnsPagtos."ies_pago">='#39'S'#39',True,False)'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
        end
        object Memo14: TfrxMemoView
          Left = 241
          Width = 70
          Height = 18
          ShowHint = False
          DataSet = Fin3012.frxCnsPagtos
          DataSetName = 'CnsPagtos'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            
              '[IIF(<CnsPagtos."data_pagamento"><>0,FormatDateTime('#39'dd/mm/yyyy'#39 +
              ',<CnsPagtos."data_pagamento">),'#39#39')]')
        end
        object Memo38: TfrxMemoView
          Left = 311
          Width = 369
          Height = 15
          ShowHint = False
          Clipped = False
          DataField = 'observacao'
          DataSet = Fin3012.frxCnsPagtos
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
        Top = 400.63018
        Width = 680.315401779394
        Child = RpRelatBase.Child4
        object Shape3: TfrxShapeView
          Align = baClient
          Width = 680.315401779394
          Height = 18
          ShowHint = False
          Color = clYellow
          Frame.Color = clGray
          Frame.ShadowWidth = 1
        end
        object Memo1: TfrxMemoView
          Left = 45
          Top = 1
          Width = 100
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<CnsPagtos."valor_parcela">)]')
        end
        object Memo2: TfrxMemoView
          Top = 1
          Width = 45
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
        Top = 442.20501
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
          DataSet = frxCnsContaPagar
          DataSetName = 'CnsContaPagar'
          Memo.UTF8 = (
            '[CnsContaPagar."observacao"]')
          WordWrap = False
        end
      end
    end
  end
  object CnsContaPagar: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cp.cod_conta_pagar, '
      '       cp.num_documento, '
      '       cp.data_cadastro, '
      '       cp.ies_situacao,'
      '       cp.tipo_registro,'
      '       cp.cod_fornecedor, '
      '       c.tipo_pessoa,'
      '       c.cpf_cnpj,'
      '       c.den_fornecedor, '
      '       c.logradouro, '
      '       c.numero, '
      '       c.complemento, '
      '       c.bairro,'
      '       d.den_cidade,'
      '       d.cod_uf,'
      '       c.cep,'
      '       cp.observacao, '
      '       f.den_forma_pagto,'
      '       cp.valor_total'
      '  FROM tbl_conta_pagar cp,'
      '       tbl_forma_pagto f,'
      '       tbl_fornecedor c'
      '  LEFT JOIN tbl_cidade d       '
      '    ON d.cod_cidade = c.cod_cidade'
      ' WHERE cp.cod_conta_pagar = :cod_conta_pagar'
      '   AND cp.cod_fornecedor = c.cod_fornecedor '
      '   AND cp.cod_forma_pagto = f.cod_forma_pagto'
      ' ORDER BY cp.cod_conta_pagar')
    Params = <
      item
        DataType = ftInteger
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
        Value = '1'
      end>
    Left = 162
    Top = 6
    ParamData = <
      item
        DataType = ftInteger
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
        Value = '1'
      end>
  end
  object CnsPagtos: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_conta_pagar, seq_parcela, valor_parcela, data_vencime' +
        'nto, data_pagamento, ies_pago, observacao'
      '  FROM tbl_conta_pagar_pagto'
      ' WHERE cod_conta_pagar = :cod_conta_pagar'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftInteger
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
    DataSource = DsContaPagar
    Left = 222
    Top = 6
    ParamData = <
      item
        DataType = ftInteger
        Name = 'cod_conta_pagar'
        ParamType = ptUnknown
      end>
  end
  object DsContaPagar: TDataSource
    DataSet = CnsContaPagar
    Left = 192
    Top = 6
  end
  object frxCnsContaPagar: TfrxDBDataset
    UserName = 'CnsContaPagar'
    CloseDataSource = False
    DataSet = CnsContaPagar
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
end
