inherited Fin3003: TFin3003
  Caption = 'Fin3003'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbEdit, pbNavigator, pbExportQuick, pbNoClose, pbNoFullScreen, pbNoEmail]
    ReportOptions.CreateDate = 41112.6683083681
    ReportOptions.LastChange = 41157.0407490509
    Datasets = <
      item
        DataSet = frxQyForContaPagar
        DataSetName = 'QyForContaPagar'
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
            'Fornecedor x Contas '#195#160' Pagar')
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
        Top = 185.19697
        Width = 718.1107
        Child = RpRelatBase.Child2
        Condition = 'QyForContaPagar."cod_fornecedor"'
        object Memo5: TfrxMemoView
          Align = baClient
          Width = 718.1107
          Height = 20.78740157
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            
              '[QyForContaPagar."cod_fornecedor"] - [QyForContaPagar."den_forne' +
              'cedor"]')
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
          Left = 535
          Top = 1
          Width = 78
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Centro Custo:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 150
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
          Left = 412
          Top = 1
          Width = 87
          Height = 16
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'Valor Pago:')
          WordWrap = False
        end
        object Memo10: TfrxMemoView
          Left = 337
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
          Width = 50
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Situa'#195#167#195#163'o:')
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
        Top = 272.12616
        Width = 718.1107
        DataSet = frxQyForContaPagar
        DataSetName = 'QyForContaPagar'
        RowCount = 0
        object Memo13: TfrxMemoView
          Top = 1
          Width = 52
          Height = 16
          ShowHint = False
          DataField = 'cod_conta_pagar'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyForContaPagar."cod_conta_pagar"]')
        end
        object Memo14: TfrxMemoView
          Left = 152
          Top = 1
          Width = 71
          Height = 16
          ShowHint = False
          Clipped = False
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          DisplayFormat.Kind = fkDateTime
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyForContaPagar."data_cadastro"]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 418
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_pago'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyForContaPagar."valor_pago"]')
        end
        object Memo16: TfrxMemoView
          Left = 318
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'valor_total'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[QyForContaPagar."valor_total"]')
        end
        object Memo17: TfrxMemoView
          Left = 532
          Top = 1
          Width = 90
          Height = 16
          ShowHint = False
          DataField = 'cod_centro_custo'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          HAlign = haCenter
          Memo.UTF8 = (
            '[QyForContaPagar."cod_centro_custo"]')
        end
        object Memo18: TfrxMemoView
          Align = baRight
          Left = 638.1107
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DataField = 'cod_plano_conta'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyForContaPagar."cod_plano_conta"]')
        end
        object Memo19: TfrxMemoView
          Left = 58
          Top = 1
          Width = 66
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_situacao'
          DataSet = frxQyForContaPagar
          DataSetName = 'QyForContaPagar'
          Memo.UTF8 = (
            '[QyForContaPagar."den_situacao"]')
          WordWrap = False
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
          Left = 276
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo21: TfrxMemoView
          Left = 318
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyForContaPagar."valor_total">)]')
        end
        object Memo22: TfrxMemoView
          Left = 416
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyForContaPagar."valor_pago">)]')
        end
        object Line6: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
      object ReportSummary1: TfrxReportSummary
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Arial'
        Font.Style = [fsBold]
        Height = 18.1417322834646
        ParentFont = False
        Top = 393.07112
        Width = 718.1107
        object Gradient1: TfrxGradientView
          Align = baClient
          Width = 718.1107
          Height = 18.1417322834646
          ShowHint = False
          EndColor = clSilver
          Style = gsVertical
        end
        object Memo1: TfrxMemoView
          Left = 276
          Top = 1
          Width = 38
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Totais:')
          WordWrap = False
        end
        object Memo2: TfrxMemoView
          Left = 318
          Top = 1
          Width = 80
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyForContaPagar."valor_total">)]')
        end
        object Memo3: TfrxMemoView
          Left = 416
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DisplayFormat.FormatStr = '%2.2m'
          DisplayFormat.Kind = fkNumeric
          HAlign = haRight
          Memo.UTF8 = (
            '[SUM(<QyForContaPagar."valor_pago">)]')
        end
        object Line7: TfrxLineView
          Align = baWidth
          Width = 718.1107
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
  object QyForContaPagar: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT *'
      '   FROM cns_conta_pagar'
      '  ORDER BY cod_fornecedor')
    Params = <>
    Left = 90
    Top = 6
  end
  object frxQyForContaPagar: TfrxDBDataset
    UserName = 'QyForContaPagar'
    CloseDataSource = False
    DataSet = QyForContaPagar
    Left = 48
    Top = 12
  end
end
