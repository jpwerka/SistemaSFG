object Sup1004: TSup1004
  Left = 248
  Top = 172
  BorderStyle = bsDialog
  Caption = 'Escolher Produto'
  ClientHeight = 303
  ClientWidth = 478
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
  object Label1: TLabel
    Left = 7
    Top = 7
    Width = 37
    Height = 13
    Caption = '&Fam'#237'lia:'
    FocusControl = cbFamilia
  end
  object lbQtde: TLabel
    Left = 254
    Top = 7
    Width = 58
    Height = 13
    Caption = '&Quantidade:'
    FocusControl = edtQtd
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 29
    Width = 219
    Height = 245
    Caption = 'Itens a adicionar'
    Color = clBtnFace
    ParentColor = False
    TabOrder = 2
    DesignSize = (
      219
      245)
    object ItensAll: TListBox
      Left = 5
      Top = 15
      Width = 210
      Height = 225
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelInner = bvLowered
      BevelKind = bkFlat
      BorderStyle = bsNone
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
    end
  end
  object GroupBox2: TGroupBox
    Left = 254
    Top = 29
    Width = 219
    Height = 245
    Caption = 'Itens escolhidos'
    Color = clBtnFace
    ParentColor = False
    TabOrder = 5
    DesignSize = (
      219
      245)
    object ItensAdd: TListBox
      Left = 5
      Top = 15
      Width = 210
      Height = 225
      Anchors = [akLeft, akTop, akRight, akBottom]
      BevelInner = bvLowered
      BevelKind = bkFlat
      BorderStyle = bsNone
      ItemHeight = 13
      MultiSelect = True
      TabOrder = 0
    end
  end
  object cbFamilia: TComboBox
    Left = 49
    Top = 5
    Width = 176
    Height = 21
    ItemHeight = 13
    TabOrder = 0
    Text = 'Escolha a fam'#237'lia...'
    OnChange = cbFamiliaChange
  end
  object edtQtd: TAlignEdit
    Left = 317
    Top = 5
    Width = 88
    Height = 21
    TabOrder = 1
    Text = '0'
    OnKeyPress = edtQtdKeyPress
    Alignment = taRightJustify
  end
  object btAdd: TButton
    Left = 229
    Top = 137
    Width = 20
    Height = 20
    Caption = '>>'
    TabOrder = 3
    OnClick = btAddClick
  end
  object btRemove: TButton
    Left = 229
    Top = 161
    Width = 20
    Height = 20
    Caption = '<<'
    TabOrder = 4
    OnClick = btRemoveClick
  end
  object btCancel: TButton
    Left = 410
    Top = 278
    Width = 60
    Height = 21
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 7
  end
  object btOK: TButton
    Left = 341
    Top = 278
    Width = 61
    Height = 21
    Caption = '&OK'
    Default = True
    TabOrder = 6
    OnClick = btOKClick
  end
  object QyCnsProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'SELECT cod_produto, den_produto, cod_unid_medida, preco_venda va' +
        'l_produto'
      '  FROM tbl_produto'
      ' WHERE cod_familia =:cod_familia'
      '   AND ies_ativo = '#39'S'#39
      ' ORDER BY cod_produto')
    Params = <
      item
        DataType = ftLargeint
        Precision = 13
        Name = 'cod_familia'
        ParamType = ptUnknown
        Size = 10
      end>
    Left = 438
    Top = 5
    ParamData = <
      item
        DataType = ftLargeint
        Precision = 13
        Name = 'cod_familia'
        ParamType = ptUnknown
        Size = 10
      end>
  end
end
