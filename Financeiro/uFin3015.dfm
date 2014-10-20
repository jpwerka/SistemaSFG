inherited Fin3015: TFin3015
  Caption = 'Fin3015'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6683083681
    ReportOptions.LastChange = 41112.6683083681
    ScriptText.Strings = (
      'procedure Memo2OnBeforePrint(Sender: TfrxComponent);'
      'begin'
      '       if <QyRecebtoCliente."ies_recebido"> = ''N'' then '
      '       begin'
      '           if  <QyRecebtoCliente."data_vencimento"> < Date then'
      '              TfrxMemoView(Sender).Font.Color := clRed'
      '           else'
      
        '              TfrxMemoView(Sender).Font.Color := clBlue;        ' +
        '                                                      '
      '       end '
      '       else'
      '         TfrxMemoView(Sender).Font.Color := clBlack;  '
      'end;'
      ''
      'begin'
      ''
      'end.')
    Top = 6
    Datasets = <
      item
        DataSet = frxQyRecebtoCliente
        DataSetName = 'QyRecebtoCliente'
      end>
    Variables = <>
    Style = <>
    inherited Page1: TfrxReportPage
      LeftMargin = 10
      RightMargin = 10
      inherited CabPagina: TfrxPageHeader
        Top = 18.89765
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
        Top = 90.70872
        Width = 718.1107
        inherited Titulo: TfrxMemoView
          Width = 718.1107
          Memo.UTF8 = (
            'Recebimento x Cliente')
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
        Top = 434.64595
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
        Top = 185.19697
        Width = 718.1107
        Child = RpRelatBase.Child2
        Condition = 'QyRecebtoCliente."cod_cliente"'
        KeepTogether = True
        object Memo5: TfrxMemoView
          Align = baClient
          Width = 718.1107
          Height = 20.78740157
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[QyRecebtoCliente."cod_cliente"] - [QyRecebtoCliente."den_client' +
              'e"]')
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
        Top = 230.55133
        Width = 718.1107
        object Line3: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo6: TfrxMemoView
          Top = 1
          Width = 66
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Conta:')
          WordWrap = False
        end
        object Memo11: TfrxMemoView
          Left = 68
          Top = 1
          Width = 45
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Parcela:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Left = 125
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Valor Parcela:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 222
          Top = 1
          Width = 70
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haCenter
          Memo.UTF8 = (
            'Data Vencto:')
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 297
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Situação:')
          WordWrap = False
        end
        object Memo95: TfrxMemoView
          Left = 380
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Desconto:')
          WordWrap = False
        end
        object Memo94: TfrxMemoView
          Left = 463
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Acrescimo:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 546
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Multa:')
          WordWrap = False
        end
        object Memo12: TfrxMemoView
          Align = baRight
          Left = 631.1107
          Top = 1
          Width = 87
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Valor Recebido:')
          WordWrap = False
        end
      end
      object MasterData1: TfrxMasterData
        Height = 17
        Top = 272.12616
        Width = 718.1107
        DataSet = frxQyRecebtoCliente
        DataSetName = 'QyRecebtoCliente'
        RowCount = 0
        object Line4: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo13: TfrxMemoView
          Top = 1
          Width = 66
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."cod_conta_receber"]')
        end
        object Memo19: TfrxMemoView
          Left = 68
          Top = 1
          Width = 45
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."seq_parcela"]')
          WordWrap = False
        end
        object Memo16: TfrxMemoView
          Left = 125
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."valor_parcela"]')
        end
        object Memo14: TfrxMemoView
          Left = 222
          Top = 1
          Width = 70
          Height = 16
          OnBeforePrint = 'Memo2OnBeforePrint'
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyRecebtoCliente."data_vencimento"]')
          WordWrap = False
        end
        object Memo2: TfrxMemoView
          Left = 297
          Width = 80
          Height = 16
          OnBeforePrint = 'Memo2OnBeforePrint'
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          Memo.UTF8 = (
            
              '[IIF(<QyRecebtoCliente."ies_recebido">=''S'',''Recebido'',IIF(<QyRec' +
              'ebtoCliente."data_vencimento"><Date(),''Em Atraso'',''A Receber''))]')
          WordWrap = False
        end
        object Memo91: TfrxMemoView
          Left = 380
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."valor_desconto"]')
        end
        object Memo92: TfrxMemoView
          Left = 463
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."valor_acrescimo"]')
        end
        object Memo17: TfrxMemoView
          Left = 546
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."valor_multa"]')
        end
        object Memo18: TfrxMemoView
          Align = baRight
          Left = 631.1107
          Top = 1
          Width = 87
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyRecebtoCliente."valor_recebido"]')
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
        Top = 313.70099
        Width = 718.1107
        object Shape1: TfrxGradientView
          Align = baClient
          Width = 718.1107
          Height = 17
          ShowHint = False
          BeginColor = 14548991
          EndColor = clYellow
          Style = gsVertical
          Frame.Color = clNone
        end
        object Memo20: TfrxMemoView
          Left = 124.72440945
          Top = 1
          Width = 90.70866142
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_parcela">)]')
        end
        object Memo22: TfrxMemoView
          Left = 380
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_desconto">)]')
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo21: TfrxMemoView
          Width = 54
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo3: TfrxMemoView
          Left = 463
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_acrescimo">)]')
        end
        object Memo4: TfrxMemoView
          Left = 546
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_multa">)]')
        end
        object Memo15: TfrxMemoView
          Align = baRight
          Left = 631.1107
          Width = 87
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_recebido">)]')
        end
      end
      object ReportSummary1: TfrxReportSummary
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18
        ParentFont = False
        Top = 393.07112
        Width = 718.1107
        object Gradient1: TfrxGradientView
          Align = baClient
          Width = 718.1107
          Height = 18
          ShowHint = False
          EndColor = clSilver
          Style = gsVertical
        end
        object Line8: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
        object Memo40: TfrxMemoView
          Left = 124.724409448819
          Top = 1
          Width = 90.7086614173228
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_parcela">)]')
        end
        object Memo42: TfrxMemoView
          Left = 380
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_desconto">)]')
        end
        object Memo31: TfrxMemoView
          Width = 54
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo33: TfrxMemoView
          Left = 463
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_acrescimo">)]')
        end
        object Memo34: TfrxMemoView
          Left = 546
          Width = 80
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_multa">)]')
        end
        object Memo35: TfrxMemoView
          Align = baRight
          Left = 631.1107
          Width = 87
          Height = 16
          ShowHint = False
          DataSet = frxQyRecebtoCliente
          DataSetName = 'QyRecebtoCliente'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyRecebtoCliente."valor_recebido">)]')
        end
      end
    end
  end
  object QyRecebtoCliente: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT tbl_cliente.cod_cliente, tbl_cliente.den_cliente,'
      
        '       pagto.cod_conta_receber, pagto.seq_parcela, pagto.valor_p' +
        'arcela, '
      
        '       pagto.data_vencimento, pagto.data_recebimento, pagto.ies_' +
        'recebido,'
      
        '       pagto.valor_recebido, pagto.valor_desconto, pagto.valor_a' +
        'crescimo, pagto.valor_multa'
      '  FROM tbl_conta_receber_pagto pagto'
      ' INNER JOIN tbl_conta_receber conta '
      '    ON conta.cod_conta_receber = pagto.cod_conta_receber'
      ' INNER JOIN tbl_cliente'
      '    ON tbl_cliente.cod_cliente = conta.cod_cliente'
      
        ' ORDER BY tbl_cliente.cod_cliente, pagto.cod_conta_receber, pagt' +
        'o.seq_parcela')
    Params = <>
    Left = 90
    Top = 6
  end
  object frxQyRecebtoCliente: TfrxDBDataset
    UserName = 'QyRecebtoCliente'
    CloseDataSource = False
    DataSet = QyRecebtoCliente
    Left = 48
    Top = 6
  end
end
