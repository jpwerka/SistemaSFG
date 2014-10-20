inherited Vdp3022: TVdp3022
  Caption = 'Vdp3022'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited RpRelatBase: TfrxReport
    ReportOptions.CreateDate = 41112.6672936458
    ReportOptions.LastChange = 41112.6672936458
    Datasets = <
      item
        DataSet = frxQyFoneRepresentante
        DataSetName = 'QyFoneRepresentante'
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
            'Telefone dos Representantes')
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
        Top = 332
        Width = 680.315401779394
        inherited RodLivre01: TfrxMemoView
          Left = 265.157702066691
          Top = 0.99999998430675
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
        Condition = 'UpperCase(COPY(<QyFoneRepresentante."den_representante">,1,1))'
        object Memo5: TfrxMemoView
          Top = 1.88976378
          Width = 364
          Height = 18.8976378
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            '[UpperCase(COPY(<QyFoneRepresentante."den_representante">,1,1))]')
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
          Top = 1
          Width = 85
          Height = 16
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Arial'
          Font.Style = [fsBold]
          HAlign = haRight
          Memo.UTF8 = (
            'Representante:')
          ParentFont = False
          WordWrap = False
        end
        object Memo7: TfrxMemoView
          Left = 87
          Top = 1
          Width = 93
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Nome Completo:')
          WordWrap = False
        end
        object Memo8: TfrxMemoView
          Left = 450
          Top = 1
          Width = 53
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Telefone:')
          WordWrap = False
        end
        object Memo9: TfrxMemoView
          Left = 633
          Top = 1
          Width = 29
          Height = 16
          ShowHint = False
          Memo.UTF8 = (
            'Fax:')
        end
        object Memo10: TfrxMemoView
          Left = 542
          Top = 1
          Width = 43
          Height = 16
          ShowHint = False
          Clipped = False
          Memo.UTF8 = (
            'Celular:')
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
        DataSet = frxQyFoneRepresentante
        DataSetName = 'QyFoneRepresentante'
        RowCount = 0
        object Memo11: TfrxMemoView
          Top = 1
          Width = 85
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'cod_representante'
          DataSet = frxQyFoneRepresentante
          DataSetName = 'QyFoneRepresentante'
          HAlign = haRight
          Memo.UTF8 = (
            '[QyFoneRepresentante."cod_representante"]')
          WordWrap = False
        end
        object Memo12: TfrxMemoView
          Left = 87
          Top = 1
          Width = 100
          Height = 16
          ShowHint = False
          Clipped = False
          DataField = 'den_representante'
          DataSet = frxQyFoneRepresentante
          DataSetName = 'QyFoneRepresentante'
          Memo.UTF8 = (
            '[QyFoneRepresentante."den_representante"]')
          WordWrap = False
        end
        object Memo13: TfrxMemoView
          Left = 427
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DataSet = frxQyFoneRepresentante
          DataSetName = 'QyFoneRepresentante'
          HAlign = haRight
          Memo.UTF8 = (
            
              '[FormatMaskText('#39'(000) 0999-9999;0;_'#39',<QyFoneRepresentante."tele' +
              'fone">)]')
          WordWrap = False
        end
        object Memo15: TfrxMemoView
          Left = 512
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DataSet = frxQyFoneRepresentante
          DataSetName = 'QyFoneRepresentante'
          HAlign = haRight
          Memo.UTF8 = (
            
              '[FormatMaskText('#39'(000) 0999-9999;0;_'#39',<QyFoneRepresentante."celu' +
              'lar">)]')
          WordWrap = False
        end
        object Memo14: TfrxMemoView
          Align = baRight
          Left = 597.315401779394
          Top = 1
          Width = 83
          Height = 16
          ShowHint = False
          DataSet = frxQyFoneRepresentante
          DataSetName = 'QyFoneRepresentante'
          HAlign = haRight
          Memo.UTF8 = (
            
              '[FormatMaskText('#39'(000) 0999-9999;0;_'#39',<QyFoneRepresentante."fax"' +
              '>)]')
          WordWrap = False
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
  object QyFoneRepresentante: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_representante, den_representante, telefone, celular, ' +
        'fax'
      'FROM tbl_representante'
      'ORDER BY den_representante;')
    Params = <>
    Left = 78
    Top = 10
  end
  object frxQyFoneRepresentante: TfrxDBDataset
    UserName = 'QyFoneRepresentante'
    CloseDataSource = False
    DataSet = QyFoneRepresentante
    Left = 42
    Top = 12
  end
end
