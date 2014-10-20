inherited Fin1001: TFin1001
  Caption = 'Cadastro de Plano de Contas'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Plano de Contas'
  end
  inherited BodyPanel: TPanel
    Left = 0
    Width = 774
    object Splitter1: TSplitter
      Left = 300
      Top = 0
      Width = 3
      Height = 465
      Cursor = crHSplit
      MinSize = 100
    end
    object TreeContas: TTreeView
      Left = 0
      Top = 0
      Width = 300
      Height = 465
      Align = alLeft
      HideSelection = False
      Indent = 19
      ReadOnly = True
      RowSelect = True
      TabOrder = 1
      OnChange = TreeContasChange
      OnChanging = TreeContasChanging
      Items.Data = {
        07000000250000000000000000000000FFFFFFFFFFFFFFFF0000000000000000
        0C31202D205245434549544153250000000000000000000000FFFFFFFFFFFFFF
        FF00000000000000000C32202D20444553504553415328000000000000000000
        0000FFFFFFFFFFFFFFFF00000000000000000F33202D20434F4D50454E5341C7
        C34F220000000000000000000000FFFFFFFFFFFFFFFF00000000000000000934
        202D20415449564F240000000000000000000000FFFFFFFFFFFFFFFF00000000
        000000000B35202D205041535349564F260000000000000000000000FFFFFFFF
        FFFFFFFF00000000000000000D36202D20474552454E4349414C260000000000
        000000000000FFFFFFFFFFFFFFFF00000000000000000D37202D20524553554C
        5441444F}
    end
    object Panel2: TPanel
      Left = 303
      Top = 0
      Width = 471
      Height = 465
      Align = alClient
      BevelOuter = bvNone
      TabOrder = 0
      object Label5: TLabel
        Left = 150
        Top = 306
        Width = 32
        Height = 13
        Caption = 'Label5'
        Color = clActiveCaption
        ParentColor = False
      end
      object Panel4: TPanel
        Left = 0
        Top = 47
        Width = 471
        Height = 157
        Align = alTop
        BevelOuter = bvNone
        TabOrder = 0
        object Label1: TLabel
          Left = 17
          Top = 9
          Width = 67
          Height = 13
          Caption = '&C'#243'digo Conta:'
          FocusControl = cod_plano_conta
        end
        object Label2: TLabel
          Left = 10
          Top = 33
          Width = 74
          Height = 13
          Caption = 'Conta &reduzida:'
          FocusControl = cod_plano_conta_reduz
        end
        object Label3: TLabel
          Left = 15
          Top = 57
          Width = 69
          Height = 13
          Caption = '&Denomina'#231#227'o:'
          FocusControl = den_plano_conta
        end
        object Label6: TLabel
          Left = 14
          Top = 126
          Width = 70
          Height = 13
          Caption = 'Da&ta cadastro:'
        end
        object Label4: TLabel
          Left = 261
          Top = 126
          Width = 49
          Height = 13
          Caption = 'Conta Pai:'
          FocusControl = cod_plano_conta_pai
        end
        object cod_plano_conta: TDBEdit
          Left = 88
          Top = 6
          Width = 135
          Height = 21
          DataField = 'cod_plano_conta'
          DataSource = DsPlanoConta
          TabOrder = 0
        end
        object cod_plano_conta_reduz: TDBEdit
          Left = 88
          Top = 30
          Width = 85
          Height = 21
          DataField = 'cod_plano_conta_reduz'
          DataSource = DsPlanoConta
          TabOrder = 2
        end
        object den_plano_conta: TDBEdit
          Left = 88
          Top = 54
          Width = 361
          Height = 21
          DataField = 'den_plano_conta'
          DataSource = DsPlanoConta
          TabOrder = 3
        end
        object ies_ativo: TDBCheckBox
          Left = 269
          Top = 11
          Width = 50
          Height = 14
          Caption = '&Ativo?'
          DataField = 'ies_ativo'
          DataSource = DsPlanoConta
          TabOrder = 1
          ValueChecked = 'S'
          ValueUnchecked = 'N'
        end
        object tipo_plano_conta: TDBRadioGroup
          Left = 88
          Top = 78
          Width = 153
          Height = 41
          Caption = '&Natureza cont'#225'bil saldo'
          Columns = 2
          DataField = 'tipo_plano_conta'
          DataSource = DsPlanoConta
          Items.Strings = (
            'D'#233'bito'
            'Cr'#233'dito')
          TabOrder = 4
          TabStop = True
          Values.Strings = (
            'D'
            'C')
        end
        object data_cadastro: TDBEdit
          Left = 88
          Top = 123
          Width = 88
          Height = 21
          DataField = 'data_cadastro'
          DataSource = DsPlanoConta
          TabOrder = 5
        end
        object btCalendar02: TCustomImgButton
          Left = 159
          Top = 126
          Width = 16
          Height = 16
          TabOrder = 6
          TabStop = False
          NumGlyphs = 5
          GlyphLoadType = glByResName
          GlyphResName = 'CALENDAR'
          TextMargin = -1
        end
        object cod_plano_conta_pai: TDBEdit
          Left = 314
          Top = 123
          Width = 135
          Height = 21
          DataField = 'cod_plano_conta_pai'
          DataSource = DsPlanoConta
          TabOrder = 7
        end
      end
      object Panel1: TPanel
        Left = 0
        Top = 0
        Width = 471
        Height = 47
        Align = alTop
        BevelOuter = bvNone
        PopupMenu = PopupMenu1
        TabOrder = 1
        object Bevel2: TBevel
          Left = 0
          Top = 44
          Width = 471
          Height = 3
          Align = alBottom
          Shape = bsBottomLine
        end
        object btEdit: TResBitBtn
          Left = 82
          Top = 6
          Width = 32
          Height = 32
          Action = execBtEdit
          ParentShowHint = False
          ShowHint = True
          TabOrder = 2
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'EDITAR'
          GlyphResID = 0
        end
        object btSave: TResBitBtn
          Left = 120
          Top = 6
          Width = 32
          Height = 32
          Action = execBtSave
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'SALVAR'
          GlyphResID = 0
        end
        object btCancel: TResBitBtn
          Left = 158
          Top = 6
          Width = 32
          Height = 32
          Action = execBtCancel
          Cancel = True
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'CANCELAR'
          GlyphResID = 0
        end
        object btAddChild: TResBitBtn
          Left = 44
          Top = 6
          Width = 32
          Height = 32
          Action = execBtAddChild
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'ADDCHILD'
          GlyphResID = 0
        end
        object btAddItem: TResBitBtn
          Left = 6
          Top = 6
          Width = 32
          Height = 32
          Action = execBtAddItem
          ParentShowHint = False
          ShowHint = True
          TabOrder = 0
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'ADDITEM'
          GlyphResID = 0
        end
        object btDelete: TResBitBtn
          Left = 196
          Top = 6
          Width = 32
          Height = 32
          Action = execBtDelete
          ParentShowHint = False
          ShowHint = True
          TabOrder = 5
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'EXCLUIR'
          GlyphResID = 0
        end
        object btExit: TResBitBtn
          Left = 234
          Top = 6
          Width = 32
          Height = 32
          Hint = 'Fechar Formul'#225'rio'
          Cancel = True
          ParentShowHint = False
          ShowHint = True
          TabOrder = 6
          OnClick = btExitClick
          NumGlyphs = 4
          GlyphLoadType = glByResName
          GlyphResName = 'SAIR'
          GlyphResID = 0
        end
      end
    end
  end
  inherited MargemEsq: TPanel
    Width = 0
    Visible = False
  end
  inherited MargemDir: TPanel
    Left = 774
    Width = 0
    Visible = False
  end
  object PlanoConta: TZTable
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'cod_plano_conta'
    Filter = 'cod_plano_conta_pai = 1'
    TableName = 'tbl_plano_conta'
    IndexFieldNames = 'cod_plano_conta Asc'
    Left = 630
    Top = 12
    object PlanoContacod_plano_conta: TStringField
      DisplayLabel = 'C'#243'digo Conta'
      FieldName = 'cod_plano_conta'
      ProviderFlags = [pfInWhere, pfInKey]
      Required = True
      Size = 18
    end
    object PlanoContacod_plano_conta_reduz: TStringField
      DisplayLabel = 'Conta Reduzida'
      FieldName = 'cod_plano_conta_reduz'
      ProviderFlags = [pfInUpdate]
      Required = True
      Size = 8
    end
    object PlanoContaden_plano_conta: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_plano_conta'
      ProviderFlags = [pfInUpdate]
      Required = True
      Size = 45
    end
    object PlanoContatipo_plano_conta: TStringField
      FieldName = 'tipo_plano_conta'
      ProviderFlags = [pfInUpdate]
      Required = True
      Size = 1
    end
    object PlanoContacod_plano_conta_pai: TStringField
      FieldName = 'cod_plano_conta_pai'
      ProviderFlags = [pfInUpdate, pfInKey]
      Size = 18
    end
    object PlanoContaies_ativo: TStringField
      DisplayLabel = 'Ativo?'
      FieldName = 'ies_ativo'
      ProviderFlags = [pfInUpdate]
      Size = 1
    end
    object PlanoContadata_cadastro: TDateTimeField
      DisplayLabel = 'Data cadastro'
      FieldName = 'data_cadastro'
      ProviderFlags = [pfInUpdate, pfInKey]
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '!90/90/0099;1;_'
    end
  end
  object DsPlanoConta: TDataSource
    AutoEdit = False
    DataSet = PlanoConta
    Left = 666
    Top = 12
  end
  object PopupMenu1: TPopupMenu
    Left = 558
    Top = 12
    object Adicionarfilho1: TMenuItem
      Action = execBtAddItem
      Caption = 'Adicionar item'
    end
    object Adicionarfilho2: TMenuItem
      Action = execBtAddChild
      Caption = 'Adicionar filho'
    end
    object Editar1: TMenuItem
      Action = execBtEdit
      Caption = 'Editar'
    end
    object Salvar1: TMenuItem
      Action = execBtSave
      Caption = 'Salvar'
    end
    object Cancelar1: TMenuItem
      Action = execBtCancel
      Caption = 'Cancelar'
    end
    object Excluir1: TMenuItem
      Action = execBtDelete
      Caption = 'Excluir'
    end
  end
  object ActionList1: TActionList
    Left = 594
    Top = 12
    object execBtAddItem: TAction
      Hint = 'Adiciona um item no mesmo n'#237'vel'
      ShortCut = 16457
      OnExecute = btAddItemClick
    end
    object execBtAddChild: TAction
      Hint = 'Adiciona um item como filho'
      ShortCut = 16454
      OnExecute = btAddChildClick
    end
    object execBtEdit: TAction
      Hint = 'Editar informa'#231#245'es do registro.'
      ShortCut = 16453
      OnExecute = btEditClick
    end
    object execBtSave: TAction
      Enabled = False
      Hint = 'Salvar altera'#231#245'es do registro.'
      ShortCut = 16467
      OnExecute = btSaveClick
    end
    object execBtCancel: TAction
      Enabled = False
      Hint = 'Cancelar altera'#231#245'es do registro.'
      ShortCut = 16472
      OnExecute = btCancelClick
    end
    object execBtDelete: TAction
      Hint = 'Excluir registro.'
      ShortCut = 16430
      OnExecute = btDeleteClick
    end
  end
  object CanDelete: TZReadOnlyQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'call can_delete_plano_conta(:cod_plano_conta);')
    Params = <
      item
        DataType = ftString
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
        Size = 18
      end>
    Left = 702
    Top = 12
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
        Size = 18
      end>
    object CanDeletecan_delete: TIntegerField
      FieldName = 'can_delete'
    end
  end
  object DelPlanoConta: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'call delete_plano_conta(:cod_plano_conta);')
    Params = <
      item
        DataType = ftString
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
        Size = 18
        Value = '1.1'
      end>
    Left = 702
    Top = 54
    ParamData = <
      item
        DataType = ftString
        Name = 'cod_plano_conta'
        ParamType = ptUnknown
        Size = 18
        Value = '1.1'
      end>
  end
end
