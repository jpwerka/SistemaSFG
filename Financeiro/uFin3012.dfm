inherited Fin3012: TFin3012
  Width = 308
  Caption = 'Fin3012'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.7219019444
    ReportOptions.LastChange = 41297.9816290509
    Datasets = <
      item
        DataSet = frxCnsContaReceber
        DataSetName = 'CnsContaReceber'
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
          Memo.UTF8 = (
            'CabLivre01')
        end
        inherited CabLivre02: TfrxMemoView
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
            'Conta Receber')
        end
        inherited Line2: TfrxLineView
          Width = 680.315401779394
        end
        object Memo5: TfrxMemoView
          Left = 442.66141
          Width = 266
          Height = 35
          ShowHint = False
          Clipped = False
          DataField = 'cod_conta_receber'
          DataSet = frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          Font.Charset = ANSI_CHARSET
          Font.Color = clWindowText
          Font.Height = -29
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          Memo.UTF8 = (
            '[CnsContaReceber."cod_conta_receber"]')
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
          Memo.UTF8 = (
            'RodLivre02')
        end
        inherited DataHora: TfrxMemoView
          Left = 265.157702066691
          Memo.UTF8 = (
            '[DATE] [TIME]')
        end
        inherited Cidade: TfrxMemoView
          Memo.UTF8 = (
            'Joinville - SC')
        end
        inherited PaginaNr: TfrxMemoView
          Left = 530.315404133382
          Memo.UTF8 = (
            'Página [Page#]')
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
        DataSet = frxCnsContaReceber
        DataSetName = 'CnsContaReceber'
        RowCount = 0
        object Memo6: TfrxMemoView
          Left = 73
          Top = 6
          Width = 71
          Height = 15
          ShowHint = False
          Clipped = False
          DataSet = frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          Memo.UTF8 = (
            '[CnsContaReceber."data_cadastro"]')
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
            
              '[IIF(Length(<CnsContaReceber."cpf_cnpj">)>0,IIF(<CnsContaReceber' +
              '."tipo_pessoa">=''J'',FormatMaskText(''!00.000.000/0000-00;0;_'',<Cn' +
              'sContaReceber."cpf_cnpj">) + '' - '',FormatMaskText(''!000.000.000-' +
              '00;0;_'',<CnsContaReceber."cpf_cnpj">) + '' - ''),'''')][CnsContaRece' +
              'ber."den_cliente"]')
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
            
              '[CnsContaReceber."logradouro"][IIF(<CnsContaReceber."numero"><>0' +
              ','', ''+IntToStr(<CnsContaReceber."numero">),'''')][IIF(Length(<CnsC' +
              'ontaReceber."bairro">)>0,'' - '' + <CnsContaReceber."bairro">,'''')]' +
              '[IIF(Length(<CnsContaReceber."den_cidade">)>0,'' - '' + <CnsContaR' +
              'eceber."den_cidade"> + '' - '' + <CnsContaReceber."cod_uf">,'''')]')
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
            'Cliente:')
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
            'Situação:')
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
            
              '[IIF(<CnsContaReceber."ies_situacao"> = ''P'',''Pendente'',IIF(<CnsC' +
              'ontaReceber."ies_situacao"> = ''A'',''Andamento'',IIF(<CnsContaReceb' +
              'er."ies_situacao"> = ''L'',''Liquidado'',''Cancelado'')))]')
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
            'Endereço:')
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
          DataSet = frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          Memo.UTF8 = (
            '[CnsContaReceber."num_documento"]')
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
        Condition = 'CnsContaReceber."cod_conta_receber"'
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
          DataSet = frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          Memo.UTF8 = (
            '[CnsContaReceber."den_forma_pagto"]')
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
            'Rec?')
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
            'Recebto')
        end
        object Memo34: TfrxMemoView
          Left = 311
          Width = 369
          Height = 18
          ShowHint = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Observação')
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
          Expression = 'IIF(<CnsPagtos."ies_recebido">=''S'',True,False)'
          Frame.Color = clGray
          Frame.Typ = [ftRight]
        end
        object Memo14: TfrxMemoView
          Left = 241
          Width = 70
          Height = 18
          ShowHint = False
          Frame.Color = clGray
          Frame.Typ = [ftRight]
          HAlign = haCenter
          Memo.UTF8 = (
            
              '[IIF(<CnsPagtos."data_recebimento"><>0,FormatDateTime(''dd/mm/yyy' +
              'y'',<CnsPagtos."data_recebimento">),'''')]')
        end
        object Memo38: TfrxMemoView
          Left = 311
          Width = 369
          Height = 15
          ShowHint = False
          Clipped = False
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
          Left = 0.31540178
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
            '3 - Observações')
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
          DataSet = frxCnsContaReceber
          DataSetName = 'CnsContaReceber'
          Memo.UTF8 = (
            '[CnsContaReceber."observacao"]')
          WordWrap = False
        end
      end
    end
  end
  object CnsContaReceber: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cr.cod_conta_receber, '
      '       cr.num_documento, '
      '       cr.data_cadastro, '
      '       cr.ies_situacao,'
      '       cr.tipo_registro,'
      '       cr.cod_cliente, '
      '       c.tipo_pessoa,'
      '       c.cpf_cnpj,'
      '       c.den_cliente, '
      '       c.logradouro, '
      '       c.numero, '
      '       c.complemento, '
      '       c.bairro,'
      '       d.den_cidade,'
      '       d.cod_uf,'
      '       c.cep,'
      '       cr.observacao, '
      '       f.den_forma_pagto,'
      '       cr.valor_total'
      '  FROM tbl_conta_receber cr,'
      '       tbl_forma_pagto f,'
      '       tbl_cliente c'
      '  LEFT JOIN tbl_cidade d       '
      '    ON d.cod_cidade = c.cod_cidade'
      ' WHERE cr.cod_conta_receber = :cod_conta_receber'
      '   AND cr.cod_cliente = c.cod_cliente '
      '   AND cr.cod_forma_pagto = f.cod_forma_pagto'
      ' ORDER BY cr.cod_conta_receber')
    Params = <
      item
        DataType = ftInteger
        Name = 'cod_conta_receber'
        ParamType = ptUnknown
        Value = 80159
      end>
    Left = 162
    Top = 6
    ParamData = <
      item
        DataType = ftInteger
        Name = 'cod_conta_receber'
        ParamType = ptUnknown
        Value = 80159
      end>
  end
  object CnsPagtos: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_conta_receber, seq_parcela, valor_parcela, data_venci' +
        'mento, data_recebimento, ies_recebido, observacao'
      '  FROM tbl_conta_receber_pagto'
      ' WHERE cod_conta_receber = :cod_conta_receber'
      ' ORDER BY seq_parcela')
    Params = <
      item
        DataType = ftInteger
        Name = 'cod_conta_receber'
        ParamType = ptUnknown
      end>
    DataSource = DsContaReceber
    Left = 222
    Top = 6
    ParamData = <
      item
        DataType = ftInteger
        Name = 'cod_conta_receber'
        ParamType = ptUnknown
      end>
  end
  object DsContaReceber: TDataSource
    DataSet = CnsContaReceber
    Left = 192
    Top = 6
  end
  object frxCnsContaReceber: TfrxDBDataset
    UserName = 'CnsContaReceber'
    CloseDataSource = False
    DataSet = CnsContaReceber
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
