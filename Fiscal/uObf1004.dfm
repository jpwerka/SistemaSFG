object Obf1004: TObf1004
  Left = 192
  Top = 114
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Obf1004 - Sele'#231#227'o de Empresa'
  ClientHeight = 65
  ClientWidth = 298
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 9
    Width = 44
    Height = 13
    Caption = '&Empresa:'
    FocusControl = cod_empresa
  end
  object cod_empresa: TDBDataComboBox
    Left = 56
    Top = 6
    Width = 235
    Height = 21
    DataField = 'cod_empresa'
    DataSource = DsEmpresa
    ItemHeight = 13
    TabOrder = 0
    LookUpDataSet = QyEmpresa
    LookUpField = 'cod_empresa'
    ResultField = 'nome_fantasia'
  end
  object btCancel: TButton
    Left = 216
    Top = 36
    Width = 75
    Height = 23
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 1
  end
  object btOK: TButton
    Left = 126
    Top = 36
    Width = 75
    Height = 23
    Caption = '&OK'
    TabOrder = 2
    OnClick = btOKClick
  end
  object QyEmpresa: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT cod_empresa, nome_fantasia'
      '  FROM tbl_empresa'
      ' ORDER BY cod_empresa ')
    Params = <>
    Left = 186
    Top = 6
  end
  object DsEmpresa: TDataSource
    AutoEdit = False
    DataSet = QyEmpresa
    Left = 222
    Top = 6
  end
end
