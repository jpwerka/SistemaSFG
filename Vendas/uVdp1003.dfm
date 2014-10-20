object Vdp1003: TVdp1003
  Left = 324
  Top = 251
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsDialog
  BorderWidth = 6
  Caption = 'Importar Or'#231'amentos'
  ClientHeight = 198
  ClientWidth = 688
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 169
    Width = 688
    Height = 29
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 0
    object btCancel: TButton
      Left = 610
      Top = 7
      Width = 75
      Height = 22
      Cancel = True
      Caption = '&Cancelar'
      ModalResult = 2
      TabOrder = 0
      OnClick = btCancelClick
    end
    object btOK: TButton
      Left = 525
      Top = 7
      Width = 75
      Height = 22
      Caption = '&OK'
      Default = True
      TabOrder = 1
      OnClick = btOKClick
    end
  end
  object ListItens: TDBGrid
    Left = 0
    Top = 0
    Width = 688
    Height = 169
    Align = alClient
    DataSource = DsOrcamento
    Options = [dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs, dgConfirmDelete, dgCancelOnExit]
    TabOrder = 1
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'MS Sans Serif'
    TitleFont.Style = []
    OnCellClick = ListItensCellClick
    OnDrawColumnCell = ListItensDrawColumnCell
    Columns = <
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'importado'
        Title.Alignment = taCenter
        Width = 18
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cod_orcamento'
        Width = 75
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'cod_cliente'
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'den_cliente'
        Width = 280
        Visible = True
      end
      item
        Alignment = taCenter
        Expanded = False
        FieldName = 'data_cadastro'
        Title.Alignment = taCenter
        Width = 90
        Visible = True
      end
      item
        Expanded = False
        FieldName = 'valor_total'
        Title.Alignment = taCenter
        Width = 95
        Visible = True
      end>
  end
  object pnProgress: TPanel
    Left = 251
    Top = 74
    Width = 186
    Height = 47
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 2
    Visible = False
    object lbInfoMail: TLabel
      Left = 6
      Top = 6
      Width = 174
      Height = 13
      AutoSize = False
      Caption = 'Aguarde... Importando or'#231'amentos.'
    end
    object ProgressImport: TProgressBar
      Left = 6
      Top = 24
      Width = 174
      Height = 17
      Min = 0
      Max = 100
      Step = 1
      TabOrder = 0
    end
  end
  object QyOrcamento: TZQuery
    Connection = SfgDataCenter.AppConnection
    CachedUpdates = True
    SQL.Strings = (
      
        'SELECT o.importado, o.cod_orcamento, o.cod_cliente, c.den_client' +
        'e, o.data_cadastro, o.valor_total'
      '  FROM tbl_orcamento o, tbl_cliente c'
      ' WHERE o.cod_cliente = c.cod_cliente'
      '   AND o.ies_situacao = '#39'F'#39' AND o.importado = '#39'N'#39
      'order by o.cod_orcamento')
    Params = <>
    ShowRecordTypes = [usUnmodified, usModified]
    Left = 322
    Top = 52
    object importado: TStringField
      DisplayLabel = 'X'
      FieldName = 'importado'
      Size = 1
    end
    object QyOrcamentocod_orcamento: TIntegerField
      DisplayLabel = 'Or'#231'amento'
      FieldName = 'cod_orcamento'
      ReadOnly = True
      Required = True
    end
    object QyOrcamentocod_cliente: TStringField
      DisplayLabel = 'Cliente'
      FieldName = 'cod_cliente'
      ReadOnly = True
      Required = True
      Size = 15
    end
    object QyOrcamentoden_cliente: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_cliente'
      ReadOnly = True
      Required = True
      Size = 50
    end
    object QyOrcamentodata_cadastro: TDateTimeField
      DisplayLabel = 'Data Cadastro'
      FieldName = 'data_cadastro'
      ReadOnly = True
      Required = True
      DisplayFormat = 'dd/mm/yyyy'
    end
    object QyOrcamentovalor_total: TFloatField
      DisplayLabel = 'Valor Total'
      FieldName = 'valor_total'
      ReadOnly = True
      currency = True
    end
  end
  object DsOrcamento: TDataSource
    AutoEdit = False
    DataSet = QyOrcamento
    Left = 292
    Top = 53
  end
end
