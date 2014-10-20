inherited Frm1013: TFrm1013
  Caption = 'Metadados'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Metadados'
  end
  inherited BodyPanel: TPanel
    object Label2: TLabel
      Left = 0
      Top = 43
      Width = 750
      Height = 6
      Align = alTop
      AutoSize = False
      Transparent = True
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 43
      Align = alTop
      Caption = 'Tabelas'
      TabOrder = 0
      object Label1: TLabel
        Left = 8
        Top = 18
        Width = 36
        Height = 13
        Caption = 'Tabela:'
      end
      object Label3: TLabel
        Left = 408
        Top = 18
        Width = 24
        Height = 13
        Caption = 'Tipo:'
      end
      object table_name: TDBEdit
        Left = 49
        Top = 15
        Width = 318
        Height = 21
        DataField = 'TABLE_NAME'
        DataSource = DsTables
        TabOrder = 0
      end
      object table_type: TDBEdit
        Left = 438
        Top = 15
        Width = 121
        Height = 21
        DataField = 'TABLE_TYPE'
        DataSource = DsTables
        TabOrder = 1
      end
    end
    object grdFields: TDBGrid
      Left = 0
      Top = 49
      Width = 750
      Height = 368
      Align = alClient
      DataSource = DsMetaFields
      TabOrder = 1
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnCellClick = grdFieldsCellClick
      OnColEnter = grdFieldsColEnter
      OnColExit = grdFieldsColExit
      OnDrawColumnCell = grdFieldsDrawColumnCell
      OnKeyDown = grdFieldsKeyDown
      Columns = <
        item
          Expanded = False
          FieldName = 'column_order'
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_name'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_label'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_datatype'
          Width = 100
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_size'
          Width = 55
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_precision'
          Width = 55
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_ispkkey'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_isnull'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_isindex'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_isbrowse'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_orderb'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_issearch'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_orders'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_isfkkey'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_fklist'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'fk_table_name'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'fk_column_name'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_editcmp'
          PickList.Strings = (
            'TextBox'
            'ComboBox'
            'CheckBox')
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_editmask'
          Width = 200
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_format'
          Width = 200
          Visible = True
        end
        item
          Alignment = taCenter
          Expanded = False
          FieldName = 'column_ismoney'
          Title.Alignment = taCenter
          Width = 50
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'column_checkvalues'
          Width = 200
          Visible = True
        end>
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btUndo: TResBitBtn
      Left = 616
    end
    inherited btSave: TResBitBtn
      Left = 310
    end
    inherited btCancel: TResBitBtn
      Left = 348
    end
    inherited btNew: TResBitBtn
      Left = 496
    end
    inherited btCopy: TResBitBtn
      Left = 534
    end
    inherited btDelete: TResBitBtn
      Left = 458
    end
    inherited btExit: TResBitBtn
      Left = 386
    end
    inherited btajuda: TResBitBtn
      Left = 654
    end
    inherited btExport: TResBitBtn
      Left = 578
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = BtEditClickExecute
      end
      inherited execBtUndoClick: TAction
        Visible = False
      end
      inherited execBtSaveClick: TAction
        OnExecute = BtSaveClickExecute
      end
      inherited execBtCancelClick: TAction
        OnExecute = BtCancelClickExecute
      end
      inherited execBtNewClick: TAction
        Enabled = False
        Visible = False
      end
      inherited execBtCopyClick: TAction
        Visible = False
      end
      inherited execBtDeleteClick: TAction
        Visible = False
        OnExecute = nil
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object QyTables: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterOpen = QyTablesAfterOpen
    SQL.Strings = (
      'SELECT table_name, table_type'
      '  FROM information_schema.tables'
      ' WHERE table_schema = DATABASE()'
      ' ORDER BY table_type, table_name')
    Params = <>
    Left = 708
    Top = 18
  end
  object DsTables: TDataSource
    AutoEdit = False
    DataSet = QyTables
    Left = 672
    Top = 18
  end
  object QyMetaFields: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterScroll = QyMetaFieldsAfterScroll
    OnCalcFields = QyMetaFieldsCalcFields
    CachedUpdates = True
    BeforeInsert = QyMetaFieldsBeforeInsert
    SQL.Strings = (
      
        'SELECT table_name,column_name,column_order,column_datatype,colum' +
        'n_typename,'
      
        '       column_size,column_precision,column_ispkkey,column_isnull' +
        ',column_isindex,'
      
        '       column_isbrowse, column_orderb, column_issearch, column_o' +
        'rders, column_ismoney,'
      
        '       column_fklist, column_isfkkey,fk_table_name,fk_column_nam' +
        'e,column_label,'
      
        '       column_editmask,column_checkvalues,more_fkkey, column_edi' +
        'tcmp, column_format'
      '  FROM tt_meta_fields'
      ' WHERE table_name = :table_name'
      'ORDER BY column_order')
    Params = <
      item
        DataType = ftUnknown
        Name = 'table_name'
        ParamType = ptUnknown
      end>
    DataSource = DsTables
    MasterSource = DsTables
    Left = 654
    Top = 234
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'table_name'
        ParamType = ptUnknown
      end>
    object QyMetaFieldstable_name: TStringField
      FieldName = 'table_name'
      ReadOnly = True
      Visible = False
      Size = 64
    end
    object QyMetaFieldscolumn_order: TIntegerField
      DisplayLabel = 'Ordem'
      FieldName = 'column_order'
      ReadOnly = True
    end
    object QyMetaFieldscolumn_name: TStringField
      DisplayLabel = 'Nome Coluna'
      FieldName = 'column_name'
      ReadOnly = True
      Size = 64
    end
    object QyMetaFieldscolumn_label: TStringField
      DisplayLabel = 'T'#237'tulo Coluna'
      FieldName = 'column_label'
      Size = 100
    end
    object QyMetaFieldscolumn_datatype2: TStringField
      DisplayLabel = 'Tipo'
      FieldName = 'column_datatype'
      ReadOnly = True
      Size = 64
    end
    object QyMetaFieldscolumn_typename: TStringField
      FieldName = 'column_typename'
      ReadOnly = True
      Visible = False
      Size = 64
    end
    object QyMetaFieldscolumn_size: TIntegerField
      DisplayLabel = 'Tamanho'
      FieldName = 'column_size'
      ReadOnly = True
    end
    object QyMetaFieldscolumn_precision: TIntegerField
      DisplayLabel = 'Precis'#227'o'
      FieldName = 'column_precision'
      ReadOnly = True
    end
    object QyMetaFieldscolumn_ispkkey: TStringField
      DisplayLabel = 'PK'
      FieldName = 'column_ispkkey'
      ReadOnly = True
      Size = 1
    end
    object QyMetaFieldscolumn_isnull: TStringField
      DisplayLabel = 'NULL'
      FieldName = 'column_isnull'
      ReadOnly = True
      Size = 1
    end
    object QyMetaFieldscolumn_isindex: TStringField
      DisplayLabel = #205'ndice'
      FieldName = 'column_isindex'
      ReadOnly = True
      Size = 1
    end
    object QyMetaFieldscolumn_isbrowse: TStringField
      DisplayLabel = 'Lista'
      FieldName = 'column_isbrowse'
      Size = 1
    end
    object QyMetaFieldscolumn_orderb: TStringField
      DisplayLabel = 'Ord Lista'
      FieldName = 'column_orderb'
      Size = 1
    end
    object QyMetaFieldscolumn_isserach: TStringField
      DisplayLabel = 'Pesq'
      FieldName = 'column_issearch'
      Size = 1
    end
    object QyMetaFieldscolumn_orders: TStringField
      DisplayLabel = 'Ord Pesq'
      FieldName = 'column_orders'
      Size = 1
    end
    object QyMetaFieldscolumn_isfkkey: TStringField
      DisplayLabel = 'FK'
      FieldName = 'column_isfkkey'
      ReadOnly = True
      Size = 1
    end
    object QyMetaFieldscolumn_isfklist: TStringField
      DisplayLabel = 'Lista FK'
      FieldName = 'column_fklist'
      Size = 1
    end
    object QyMetaFieldsfk_table_name: TStringField
      DisplayLabel = 'Tabela Referenciada'
      FieldName = 'fk_table_name'
      Size = 64
    end
    object QyMetaFieldsfk_column_name: TStringField
      DisplayLabel = 'Coluna Referenciada'
      FieldName = 'fk_column_name'
      Size = 64
    end
    object QyMetaFieldscolumn_editcmp: TStringField
      DisplayLabel = 'Componente Edi'#231#227'o'
      DisplayWidth = 16
      FieldName = 'column_editcmp'
      Size = 16
    end
    object QyMetaFieldscolumn_editmask: TStringField
      DisplayLabel = 'M'#225'scara Edi'#231#227'o'
      FieldName = 'column_editmask'
      Size = 64
    end
    object QyMetaFieldscolumn_format: TStringField
      DisplayLabel = 'Formato Exibi'#231#227'o'
      FieldName = 'column_format'
      Size = 64
    end
    object QyMetaFieldscolumn_ismoney: TStringField
      DisplayLabel = 'Moeda'
      FieldName = 'column_ismoney'
      Size = 1
    end
    object QyMetaFieldscolumn_checkvalues: TStringField
      DisplayLabel = 'Valores Check'
      FieldName = 'column_checkvalues'
      Size = 64
    end
    object QyMetaFieldsmore_fkkey: TStringField
      FieldName = 'more_fkkey'
      Size = 1
    end
  end
  object DsMetaFields: TDataSource
    AutoEdit = False
    DataSet = QyMetaFields
    Left = 624
    Top = 234
  end
  object QyAddFields: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'INSERT INTO tbl_meta_fiedls '
      
        '    (table_name, column_name, column_order, column_datatype, col' +
        'umn_typename, '
      
        '     column_size, column_precision, column_properties, fk_table_' +
        'name, fk_column_name,'
      
        '     column_label, column_editcmp, column_editmask, column_forma' +
        't, column_checkvalues)'
      
        'VALUES (:table_name, :column_name, :column_order, :column_dataty' +
        'pe, :column_typename, '
      
        '     :column_size, :column_precision, :column_properties, :fk_ta' +
        'ble_name, :fk_column_name,'
      
        '     :column_label, :column_editcmp, :column_editmask, :column_f' +
        'ormat, :column_checkvalues)')
    Params = <
      item
        DataType = ftString
        Name = 'table_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_name'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_order'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_datatype'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_typename'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_size'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_precision'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_properties'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'fk_table_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'fk_column_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_label'
        ParamType = ptInput
      end
      item
        DataType = ftSmallint
        Name = 'column_editcmp'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_editmask'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_format'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_checkvalues'
        ParamType = ptInput
      end>
    Left = 654
    Top = 270
    ParamData = <
      item
        DataType = ftString
        Name = 'table_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_name'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_order'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_datatype'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_typename'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_size'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_precision'
        ParamType = ptInput
      end
      item
        DataType = ftInteger
        Name = 'column_properties'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'fk_table_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'fk_column_name'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_label'
        ParamType = ptInput
      end
      item
        DataType = ftSmallint
        Name = 'column_editcmp'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_editmask'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_format'
        ParamType = ptInput
      end
      item
        DataType = ftString
        Name = 'column_checkvalues'
        ParamType = ptInput
      end>
  end
end
