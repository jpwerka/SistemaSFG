object Sup1003: TSup1003
  Left = 392
  Top = 263
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsDialog
  BorderWidth = 6
  Caption = 'Recebimento de Pedido Compra'
  ClientHeight = 248
  ClientWidth = 668
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object gbItens: TGroupBox
    Left = 0
    Top = 43
    Width = 668
    Height = 178
    Align = alClient
    Caption = '&Itens'
    TabOrder = 0
    object grdItens: TDBGrid
      Left = 6
      Top = 18
      Width = 654
      Height = 151
      DataSource = DataSource1
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnKeyDown = grdItensKeyDown
      OnTitleClick = grdItensTitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'seq_produto'
          Title.Alignment = taCenter
          Width = 40
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'cod_produto'
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'den_produto'
          Width = 300
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'qtd_produto'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'qtd_recebida'
          Title.Alignment = taCenter
          Width = 90
          Visible = True
        end>
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 221
    Width = 668
    Height = 27
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object btCancel: TButton
      Left = 592
      Top = 5
      Width = 75
      Height = 22
      Caption = '&Cancelar'
      ModalResult = 2
      TabOrder = 0
      OnClick = btCancelClick
    end
    object btOK: TButton
      Left = 507
      Top = 5
      Width = 75
      Height = 22
      Caption = '&OK'
      Default = True
      TabOrder = 1
      OnClick = btOKClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = 0
    Width = 668
    Height = 43
    Cursor = crArrow
    Align = alTop
    Caption = 'Pedido de Compra'
    TabOrder = 2
    object Label1: TLabel
      Left = 9
      Top = 17
      Width = 36
      Height = 13
      Cursor = crArrow
      Caption = '&C'#243'digo:'
      DragCursor = crDefault
      FocusControl = cod_pedido_compra
      Transparent = True
      WordWrap = True
    end
    object Label12: TLabel
      Left = 136
      Top = 17
      Width = 66
      Height = 13
      Cursor = crArrow
      Caption = 'R&ecebimento:'
      DragCursor = crDefault
      FocusControl = data_recebimento
      Transparent = True
      WordWrap = True
    end
    object cod_pedido_compra: TDBEdit
      Left = 49
      Top = 15
      Width = 70
      Height = 21
      Color = clWhite
      DataField = 'cod_pedido_compra'
      DataSource = DataSource1
      TabOrder = 0
    end
    object data_recebimento: TEdit
      Left = 206
      Top = 15
      Width = 88
      Height = 21
      TabOrder = 1
    end
  end
  object QyCadProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    UpdateObject = AddItemVenda
    CachedUpdates = True
    BeforeInsert = QyCadProdutoBeforeInsert
    BeforeEdit = QyCadProdutoBeforeEdit
    SQL.Strings = (
      'SELECT v.cod_pedido_compra, v.seq_produto,'
      '       v.cod_produto, p.den_produto,'
      '       v.qtd_produto, v.qtd_recebida'
      '  FROM tbl_pedido_compra_item v,'
      '       tbl_produto p'
      ' WHERE v.cod_pedido_compra = :cod_pedido_compra'
      '   AND v.cod_produto = p.cod_produto'
      ' ORDER BY v.seq_produto')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Value = '5'
      end>
    ShowRecordTypes = [usUnmodified, usModified]
    Left = 466
    Top = 4
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Value = '5'
      end>
    object CodPedidoCompra: TIntegerField
      FieldName = 'cod_pedido_compra'
      ReadOnly = True
      Required = True
    end
    object QyCadProdutoseq_produto: TIntegerField
      DisplayLabel = 'Seq'
      FieldName = 'seq_produto'
      ReadOnly = True
      Required = True
    end
    object QyCadProdutocod_produto: TStringField
      DisplayLabel = 'Item'
      FieldName = 'cod_produto'
      ReadOnly = True
      Required = True
      Size = 15
    end
    object QyCadProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      ReadOnly = True
      Size = 75
    end
    object QyCadProdutoqtd_produto: TFloatField
      DisplayLabel = 'Qtd Solicitada'
      FieldName = 'qtd_produto'
      ReadOnly = True
      DisplayFormat = '#.000'
    end
    object QyCadProdutoqtd_recebida: TFloatField
      DisplayLabel = 'Qtd Recebida'
      FieldName = 'qtd_recebida'
      DisplayFormat = '#0.000'
    end
  end
  object DataSource1: TDataSource
    DataSet = QyCadProduto
    Left = 436
    Top = 5
  end
  object AddItemVenda: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_pedido_compra_item'
      'WHERE cod_pedido_compra = :cod_pedido_compra '
      'AND seq_produto = :seq_produto')
    InsertSQL.Strings = (
      'INSERT INTO tbl_pedido_compra_item '
      '(cod_pedido_compra, seq_produto, cod_produto, qtd_recebida) '
      'VALUES '
      '(:cod_pedido_compra, :seq_produto, :cod_produto, :qtd_recebida)')
    ModifySQL.Strings = (
      'UPDATE tbl_pedido_compra_item'
      '   SET qtd_recebida = :qtd_recebida'
      ' WHERE cod_pedido_compra = :cod_pedido_compra'
      '   AND seq_produto = :seq_produto')
    UseSequenceFieldForRefreshSQL = False
    Left = 497
    Top = 4
    ParamData = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'qtd_recebida'
        ParamType = ptUnknown
      end
      item
        DataType = ftInteger
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Size = 10
        Value = 1
      end
      item
        DataType = ftInteger
        Precision = 255
        Name = 'seq_produto'
        ParamType = ptUnknown
        Size = 255
        Value = 1
      end
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
        Value = '1.001'
      end>
  end
end
