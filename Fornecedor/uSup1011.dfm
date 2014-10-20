inherited Sup1011: TSup1011
  Caption = 'Fornecedores x Produtos'
  OnDestroy = nil
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Fornecedores x Produtos'
  end
  inherited BodyPanel: TPanel
    object Label7: TLabel
      Left = 0
      Top = 67
      Width = 750
      Height = 6
      Align = alTop
      AutoSize = False
    end
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 750
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Fornecedor'
      TabOrder = 0
      object Label1: TLabel
        Left = 10
        Top = 17
        Width = 57
        Height = 13
        Cursor = crArrow
        Caption = 'Fornecedor:'
        DragCursor = crDefault
        FocusControl = cod_fornecedor
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 248
        Top = 17
        Width = 24
        Height = 13
        Cursor = crArrow
        Caption = 'Tipo:'
        DragCursor = crDefault
        FocusControl = tipo_pessoa
        Transparent = True
        WordWrap = True
      end
      object Label3: TLabel
        Left = 11
        Top = 41
        Width = 69
        Height = 13
        Alignment = taRightJustify
        Caption = 'Denomina'#231#227'o:'
        Transparent = True
        WordWrap = True
      end
      object cod_fornecedor: TDBEdit
        Left = 71
        Top = 15
        Width = 110
        Height = 21
        Color = clWhite
        DataField = 'cod_fornecedor'
        DataSource = DsCnsFornecedor
        TabOrder = 0
      end
      object tipo_pessoa: TDBDataComboBox
        Left = 275
        Top = 15
        Width = 126
        Height = 21
        AutoDropDown = True
        DataField = 'tipo_pessoa'
        DataSource = DsCnsFornecedor
        ItemHeight = 13
        Sorted = True
        TabOrder = 1
      end
      object ies_ativo: TDBCheckBox
        Left = 544
        Top = 17
        Width = 50
        Height = 14
        Caption = 'Ativo?'
        DataField = 'ies_ativo'
        DataSource = DsCnsFornecedor
        TabOrder = 2
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
      object den_fornecedor: TDBEdit
        Left = 83
        Top = 39
        Width = 510
        Height = 21
        Color = clWhite
        DataField = 'den_fornecedor'
        DataSource = DsCnsFornecedor
        TabOrder = 3
      end
    end
    object pnAddProduto: TPanel
      Left = 0
      Top = 384
      Width = 750
      Height = 33
      Align = alBottom
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 1
      object btAddLinha: TResBitBtn
        Left = 5
        Top = 5
        Width = 108
        Height = 25
        Action = addLine
        Caption = '&Adicionar Linha'
        TabOrder = 0
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ADICIONARM'
        GlyphResID = 0
      end
      object btDelLinha: TResBitBtn
        Left = 117
        Top = 5
        Width = 108
        Height = 25
        Action = delLine
        Caption = '&Remover Linha'
        TabOrder = 1
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'EXCLUIRM'
        GlyphResID = 0
      end
      object btAddItens: TResBitBtn
        Left = 228
        Top = 5
        Width = 109
        Height = 25
        Action = addItens
        Caption = 'Adicionar &Itens'
        TabOrder = 2
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ADICIONARM'
        GlyphResID = 0
      end
    end
    object grdAddProduto: TDBGrid
      Left = 0
      Top = 73
      Width = 750
      Height = 311
      Align = alClient
      DataSource = DsFornecProduto
      Options = [dgEditing, dgTitles, dgIndicator, dgColumnResize, dgColLines, dgRowLines, dgTabs]
      PopupMenu = PopupMenu1
      TabOrder = 2
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnDrawColumnCell = grdAddProdutoDrawColumnCell
      OnEditButtonClick = grdAddProdutoEditButtonClick
      OnKeyDown = grdAddProdutoKeyDown
      Columns = <
        item
          ButtonStyle = cbsEllipsis
          Expanded = False
          FieldName = 'cod_produto'
          Width = 110
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'den_produto'
          Width = 389
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'preco_compra'
          Title.Alignment = taCenter
          Width = 110
          Visible = True
        end
        item
          Alignment = taCenter
          ButtonStyle = cbsEllipsis
          Expanded = False
          FieldName = 'data_atualizacao'
          Title.Alignment = taCenter
          Title.Caption = 'Data Atualiz.'
          Width = 105
          Visible = True
        end>
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited btSave: TResBitBtn
      Left = 310
    end
    inherited btCancel: TResBitBtn
      Left = 348
    end
    inherited btNew: TResBitBtn
      Visible = False
    end
    inherited btCopy: TResBitBtn
      Visible = False
    end
    inherited btDelete: TResBitBtn
      Visible = False
    end
    inherited btExit: TResBitBtn
      Left = 386
    end
    inherited btajuda: TResBitBtn
      Left = 574
    end
    inherited MenuClicks: TPopupMenu
      inherited Editar1: TMenuItem
        Visible = False
      end
      inherited Salvar1: TMenuItem
        Visible = False
      end
      inherited Cancelar1: TMenuItem
        Visible = False
      end
      inherited Novo1: TMenuItem
        Visible = False
      end
      inherited Copiar1: TMenuItem
        Visible = False
      end
      inherited Excluir1: TMenuItem
        Visible = False
      end
    end
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = btEditClickExecute
      end
      inherited execBtUndoClick: TAction
        Visible = False
      end
      inherited execBtSaveClick: TAction
        OnExecute = btSaveClickExecute
      end
      inherited execBtCancelClick: TAction
        OnExecute = btCancelClickExecute
      end
      inherited execBtNewClick: TAction
        Enabled = False
      end
      inherited execBtExportClick: TAction
        Visible = False
      end
    end
  end
  object QyCnsFornecedor: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterOpen = QyCnsFornecedorAfterOpen
    BeforeClose = QyCnsFornecedorBeforeClose
    SQL.Strings = (
      'SELECT cod_fornecedor, den_fornecedor, ies_ativo, tipo_pessoa'
      '  FROM tbl_fornecedor'
      ' ORDER BY cod_fornecedor')
    Params = <>
    Left = 616
    Top = 8
  end
  object DsCnsFornecedor: TDataSource
    AutoEdit = False
    DataSet = QyCnsFornecedor
    Left = 656
    Top = 8
  end
  object QyFornecProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'cod_produto'
    UpdateObject = AtuSup1011
    CachedUpdates = True
    BeforeInsert = QyFornecProdutoBeforeInsert
    SQL.Strings = (
      'SELECT fp.cod_fornecedor, fp.cod_produto, p.den_produto,'
      '       fp.preco_compra, fp.data_atualizacao'
      '  FROM tbl_fornecedor_produto fp,'
      '       tbl_produto p'
      ' WHERE fp.cod_fornecedor = :cod_fornecedor'
      '   AND fp.cod_produto = p.cod_produto'
      ' ORDER BY fp.cod_produto')
    Params = <
      item
        DataType = ftUnknown
        Name = 'cod_fornecedor'
        ParamType = ptUnknown
      end>
    DataSource = DsCnsFornecedor
    MasterFields = 'cod_fornecedor'
    MasterSource = DsCnsFornecedor
    LinkedFields = 'cod_fornecedor'
    IndexFieldNames = 'cod_produto Asc'
    Left = 348
    Top = 306
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'cod_fornecedor'
        ParamType = ptUnknown
      end>
    object QyFornecProdutocod_fornecedor: TStringField
      DisplayLabel = 'Fornecedor'
      FieldName = 'cod_fornecedor'
      ProviderFlags = [pfInWhere, pfInKey]
      Size = 15
    end
    object QyFornecProdutocod_produto: TStringField
      DisplayLabel = 'Produto'
      FieldName = 'cod_produto'
      ProviderFlags = [pfInWhere, pfInKey]
      OnValidate = CodProdutoValidate
      Size = 15
    end
    object QyFornecProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      ProviderFlags = []
      Size = 75
    end
    object QyFornecProdutopreco_compra: TFloatField
      DisplayLabel = 'Pre'#231'o Compra'
      FieldName = 'preco_compra'
      ProviderFlags = [pfInUpdate]
      currency = True
      Precision = 13
    end
    object QyFornecProdutodata_atualizacao: TDateTimeField
      DisplayLabel = 'Data Atualiza'#231#227'o'
      DisplayWidth = 10
      FieldName = 'data_atualizacao'
      ProviderFlags = [pfInUpdate]
      DisplayFormat = 'dd/mm/yyyy'
      EditMask = '!90/90/0099;1;_'
    end
  end
  object DsFornecProduto: TDataSource
    AutoEdit = False
    DataSet = QyFornecProduto
    Left = 384
    Top = 306
  end
  object ActionList1: TActionList
    Left = 210
    Top = 434
    object addLine: TAction
      Caption = '&Adicionar Linha'
      Enabled = False
      Hint = 'Adicionar um produto ao fornecedor.'
      ShortCut = 32833
      OnExecute = addLineExecute
    end
    object delLine: TAction
      Caption = '&Remover Linha'
      Enabled = False
      Hint = 'Exclui produto atual do fornecedor.'
      ShortCut = 32850
      OnExecute = delLineExecute
    end
    object addItens: TAction
      Caption = 'Adicionar &Itens'
      Enabled = False
      Hint = 'Adicionar v'#225'rios produtos ao fornecedor.'
      OnExecute = addItensExecute
    end
  end
  object AtuSup1011: TZUpdateSQL
    DeleteSQL.Strings = (
      'DELETE FROM tbl_fornecedor_produto'
      'WHERE tbl_fornecedor_produto.cod_fornecedor = :cod_fornecedor'
      '  AND tbl_fornecedor_produto.cod_produto = :cod_produto')
    InsertSQL.Strings = (
      'INSERT INTO tbl_fornecedor_produto'
      '  (cod_fornecedor, cod_produto, preco_compra, data_atualizacao)'
      'VALUES'
      
        '  (:cod_fornecedor, :cod_produto, :preco_compra, :data_atualizac' +
        'ao)')
    ModifySQL.Strings = (
      'UPDATE tbl_fornecedor_produto'
      #9'SET preco_compra = :preco_compra,'
      '  data_atualizacao = :data_atualizacao'
      'WHERE cod_fornecedor = :cod_fornecedor'
      '  AND cod_produto = :cod_produto')
    UseSequenceFieldForRefreshSQL = False
    Left = 420
    Top = 306
    ParamData = <
      item
        DataType = ftFloat
        Precision = 13
        NumericScale = 3
        Name = 'preco_compra'
        ParamType = ptUnknown
      end
      item
        DataType = ftDateTime
        Name = 'data_atualizacao'
        ParamType = ptUnknown
      end
      item
        DataType = ftString
        Name = 'cod_fornecedor'
        ParamType = ptUnknown
        Size = 15
      end
      item
        DataType = ftString
        Name = 'cod_produto'
        ParamType = ptUnknown
        Size = 15
      end>
  end
  object PopupMenu1: TPopupMenu
    Left = 48
    Top = 300
    object AdicionarLinha1: TMenuItem
      Action = addLine
    end
    object RemoverLinha1: TMenuItem
      Action = delLine
    end
    object MenuItem1: TMenuItem
      Action = addItens
    end
  end
end
