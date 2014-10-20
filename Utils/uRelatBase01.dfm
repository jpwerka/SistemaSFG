object frmRelatBase01: TfrmRelatBase01
  Left = 397
  Top = 263
  Width = 272
  Height = 109
  Caption = 'frmRelatBase01'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Scaled = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object RpRelatBase: TfrxReport
    Version = '4.6.8'
    DotMatrixReport = False
    IniFile = '\Software\Fast Reports'
    PreviewOptions.AllowEdit = False
    PreviewOptions.Buttons = [pbPrint, pbLoad, pbSave, pbExport, pbZoom, pbFind, pbOutline, pbPageSetup, pbTools, pbNavigator, pbExportQuick]
    PreviewOptions.Zoom = 0.99999998430675
    PrintOptions.Printer = 'Default'
    PrintOptions.PrintOnSheet = 0
    ReportOptions.CreateDate = 41112.4508775154
    ReportOptions.Name = 'Relat'#243'rio'
    ReportOptions.LastChange = 41154.9710537458
    ScriptLanguage = 'PascalScript'
    ScriptText.Strings = (
      'begin'
      ''
      'end.')
    OnBeginDoc = RpRelatBaseBeginDoc
    Left = 12
    Top = 12
    Datasets = <>
    Variables = <>
    Style = <>
    object Data: TfrxDataPage
      Height = 999.999984306749
      Width = 999.999984306749
    end
    object Page1: TfrxReportPage
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Arial'
      Font.Style = []
      PaperWidth = 210
      PaperHeight = 297
      PaperSize = 9
      LeftMargin = 14.9999997646012
      RightMargin = 14.9999997646012
      TopMargin = 14.9999997646012
      BottomMargin = 14.9999997646012
      object CabPagina: TfrxPageHeader
        Height = 49.9999992153375
        Top = 16.0000004361028
        Width = 680.315397982913
        Child = RpRelatBase.Child1
        object Logotipo: TfrxPictureView
          Width = 149.999997646012
          Height = 49.9999992153375
          ShowHint = False
          HightQuality = False
        end
        object CabLivre01: TfrxMemoView
          Left = 152.99999794253
          Top = 0.99999998430675
          Width = 526.00000617644
          Height = 14.9999997646012
          ShowHint = False
          WordWrap = False
        end
        object CabLivre02: TfrxMemoView
          Left = 152.99999794253
          Top = 16.9999993896174
          Width = 526.00000617644
          Height = 14.9999997646012
          ShowHint = False
          WordWrap = False
        end
        object CabLivre03: TfrxMemoView
          Left = 152.99999794253
          Top = 32.9999998257201
          Width = 526.00000617644
          Height = 14.9999997646012
          ShowHint = False
          WordWrap = False
        end
      end
      object Child1: TfrxChild
        Height = 35.0000011687231
        Top = 87.9999972446044
        Width = 680.315397982913
        object Titulo: TfrxMemoView
          Align = baClient
          Width = 680.315397982913
          Height = 35.0000011687231
          ShowHint = False
          Clipped = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -29
          Font.Name = 'Times New Roman'
          Font.Style = [fsBold]
          HAlign = haCenter
          ParentFont = False
          WordWrap = False
        end
        object Line2: TfrxLineView
          Align = baWidth
          Width = 680.315397982913
          ShowHint = False
          Frame.Typ = [ftTop]
          Frame.Width = 1.9999999686135
        end
      end
      object RodPagina: TfrxPageFooter
        Height = 17.3858266097385
        Top = 184.000006733169
        Width = 680.315397982913
        object RodLivre01: TfrxMemoView
          Align = baCenter
          Left = 265.157691578515
          Top = 0.99999998430675
          Width = 149.999997646012
          Height = 14.9999997646012
          Visible = False
          ShowHint = False
          Clipped = False
          HAlign = haCenter
          WordWrap = False
        end
        object RodLivre02: TfrxMemoView
          Align = baCenter
          Left = 265.157691578515
          Top = 0.99999998430675
          Width = 149.999997646012
          Height = 14.9999997646012
          Visible = False
          ShowHint = False
          Clipped = False
          HAlign = haCenter
          WordWrap = False
        end
        object DataHora: TfrxMemoView
          Align = baCenter
          Left = 265.157691578515
          Top = 0.99999998430675
          Width = 149.999997646012
          Height = 14.9999997646012
          ShowHint = False
          Clipped = False
          DisplayFormat.FormatStr = 'dd/mm/yyyy'
          HAlign = haCenter
          Memo.UTF8 = (
            '[DATE] [TIME]')
          WordWrap = False
        end
        object Cidade: TfrxMemoView
          Align = baLeft
          Top = 0.99999998430675
          Width = 149.999997646012
          Height = 14.9999997646012
          ShowHint = False
          Clipped = False
          WordWrap = False
        end
        object PaginaNr: TfrxMemoView
          Align = baRight
          Left = 530.315383157031
          Top = 0.99999998430675
          Width = 149.999997646012
          Height = 14.9999997646012
          ShowHint = False
          Clipped = False
          HAlign = haRight
          Memo.UTF8 = (
            'P'#195#161'gina [Page#] de [TotalPages#]')
          WordWrap = False
        end
        object Line5: TfrxLineView
          Align = baWidth
          Width = 680.315397982913
          ShowHint = False
          Frame.Typ = [ftTop]
        end
      end
    end
  end
end
