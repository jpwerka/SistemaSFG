inherited Frm1002: TFrm1002
  Caption = 'Cadastro de Usu'#225'rios'
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Usu'#225'rios'
  end
  inherited BodyPanel: TPanel
    object GroupBox1: TGroupBox
      Left = 0
      Top = 0
      Width = 758
      Height = 67
      Cursor = crArrow
      Align = alTop
      Caption = 'Cadastro'
      TabOrder = 0
      object Label1: TLabel
        Left = 12
        Top = 17
        Width = 39
        Height = 13
        Caption = '&Usu'#225'rio:'
        FocusControl = usuario
        Transparent = True
        WordWrap = True
      end
      object Label2: TLabel
        Left = 223
        Top = 17
        Width = 31
        Height = 13
        Caption = '&Nome:'
        FocusControl = nome
        Transparent = True
        WordWrap = True
      end
      object Label3: TLabel
        Left = 16
        Top = 41
        Width = 34
        Height = 13
        Caption = '&Senha:'
        FocusControl = senha
        Transparent = True
        WordWrap = True
      end
      object Label4: TLabel
        Left = 223
        Top = 41
        Width = 62
        Height = 13
        Caption = '&Confirma'#231#227'o:'
        FocusControl = confirmacao
        Transparent = True
        WordWrap = True
      end
      object usuario: TDBEdit
        Left = 55
        Top = 15
        Width = 136
        Height = 21
        CharCase = ecLowerCase
        DataField = 'usuario'
        DataSource = DsCadUsuario
        TabOrder = 0
      end
      object nome: TDBEdit
        Left = 258
        Top = 15
        Width = 321
        Height = 21
        DataField = 'nome'
        DataSource = DsCadUsuario
        TabOrder = 1
      end
      object senha: TDBEdit
        Left = 54
        Top = 39
        Width = 136
        Height = 21
        DataField = 'senha'
        DataSource = DsCadUsuario
        PasswordChar = '*'
        TabOrder = 2
        OnExit = senhaExit
      end
      object confirmacao: TEdit
        Left = 289
        Top = 39
        Width = 136
        Height = 21
        PasswordChar = '*'
        TabOrder = 3
        OnExit = confirmacaoExit
      end
      object ies_administrador: TDBCheckBox
        Left = 496
        Top = 42
        Width = 91
        Height = 17
        Caption = '&Administrador'
        DataField = 'ies_administrador'
        DataSource = DsCadUsuario
        TabOrder = 4
        ValueChecked = 'S'
        ValueUnchecked = 'N'
      end
    end
    object GroupBox2: TGroupBox
      Left = 0
      Top = 110
      Width = 758
      Height = 155
      Align = alTop
      Caption = 'Grupos'
      TabOrder = 1
      object ListGrupos: TListBox
        Left = 6
        Top = 15
        Width = 145
        Height = 133
        Align = alCustom
        ItemHeight = 13
        TabOrder = 0
      end
      object btSearchGrupo: TResBitBtn
        Left = 158
        Top = 15
        Width = 23
        Height = 23
        Hint = 'Abre a pesquisa de grupos.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        TabStop = False
        OnClick = btSearchGrupoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'PESQUISAM'
        GlyphResID = 0
      end
      object btDeleteGrupo: TResBitBtn
        Left = 158
        Top = 39
        Width = 23
        Height = 23
        Hint = 'Exclui um grupo do usu'#225'rio.'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        TabStop = False
        OnClick = btDeleteGrupoClick
        NumGlyphs = 4
        GlyphLoadType = glByResName
        GlyphResName = 'EXCLUIRM'
        GlyphResID = 0
      end
    end
    object GroupBox3: TGroupBox
      Left = 0
      Top = 67
      Width = 758
      Height = 43
      Align = alTop
      Caption = 'Informa'#231#245'es'
      TabOrder = 2
      object Label6: TLabel
        Left = 20
        Top = 17
        Width = 28
        Height = 13
        Caption = '&Email:'
        FocusControl = email
        Transparent = True
        WordWrap = True
      end
      object email: TDBEdit
        Left = 51
        Top = 15
        Width = 321
        Height = 21
        DataField = 'email'
        DataSource = DsCadUsuario
        TabOrder = 0
      end
    end
  end
  inherited SfgToolbar: TSfgToolbar
    PopupMenu = SfgToolbar.MenuClicks
    inherited ActionList1: TActionList
      inherited execBtEditClick: TAction
        OnExecute = NavegbtEditClick
      end
      inherited execBtSaveClick: TAction
        OnExecute = NavegbtSaveClick
      end
      inherited execBtCancelClick: TAction
        OnExecute = NavegbtCancelClick
      end
      inherited execBtNewClick: TAction
        OnExecute = NavegbtNewClick
      end
    end
  end
  object QyCadUsuario: TZQuery
    Connection = SfgDataCenter.AppConnection
    AfterOpen = QyCadUsuarioAfterOpen
    BeforeClose = QyCadUsuarioBeforeClose
    AfterScroll = QyCadUsuarioAfterScroll
    BeforePost = QyCadUsuarioBeforePost
    AfterPost = QyCadUsuarioAfterPost
    BeforeDelete = QyCadUsuarioBeforeDelete
    SQL.Strings = (
      'SELECT usuario, nome, senha, email, ies_administrador'
      '  FROM tbl_usuario '
      ' ORDER BY usuario')
    Params = <>
    Left = 668
    Top = 6
  end
  object DsCadUsuario: TDataSource
    AutoEdit = False
    DataSet = QyCadUsuario
    Left = 703
    Top = 6
  end
  object QyUsuarioGrupo: TZQuery
    Connection = SfgDataCenter.AppConnection
    SortedFields = 'cod_grupo'
    CachedUpdates = True
    SQL.Strings = (
      'SELECT usuario, cod_grupo'
      '  FROM tbl_usuario_grupo'
      ' WHERE usuario = :usuario'
      ' ORDER BY cod_grupo ')
    Params = <
      item
        DataType = ftUnknown
        Name = 'usuario'
        ParamType = ptUnknown
      end>
    DataSource = DsCadUsuario
    IndexFieldNames = 'cod_grupo Asc'
    Left = 630
    Top = 6
    ParamData = <
      item
        DataType = ftUnknown
        Name = 'usuario'
        ParamType = ptUnknown
      end>
  end
end
