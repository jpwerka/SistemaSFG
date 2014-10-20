object SfgToolbar: TSfgToolbar
  Left = 0
  Top = 0
  Width = 670
  Height = 42
  PopupMenu = MenuClicks
  TabOrder = 0
  object btFirst: TResBitBtn
    Left = 6
    Top = 6
    Width = 32
    Height = 32
    Action = execBtFirstClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'PRIMEIRO'
    GlyphResID = 0
  end
  object btPrew: TResBitBtn
    Left = 44
    Top = 6
    Width = 32
    Height = 32
    Action = execBtPrewClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'ANTERIOR'
    GlyphResID = 0
  end
  object btNext: TResBitBtn
    Left = 82
    Top = 6
    Width = 32
    Height = 32
    Action = execBtNextClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'PROXIMO'
    GlyphResID = 0
  end
  object btLast: TResBitBtn
    Left = 120
    Top = 6
    Width = 32
    Height = 32
    Action = execBtLastClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'ULTIMO'
    GlyphResID = 0
  end
  object btSearch: TResBitBtn
    Left = 158
    Top = 6
    Width = 32
    Height = 32
    Action = execBtSearchClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'PESQUISA'
    GlyphResID = 0
  end
  object btBrowse: TResBitBtn
    Left = 196
    Top = 6
    Width = 32
    Height = 32
    Action = execBtBrowseClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 5
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'LISTAR'
    GlyphResID = 0
  end
  object btGoTo: TResBitBtn
    Left = 234
    Top = 6
    Width = 32
    Height = 32
    Action = execBtGoToClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 6
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'VAPARA'
    GlyphResID = 0
  end
  object btEdit: TResBitBtn
    Left = 272
    Top = 6
    Width = 32
    Height = 32
    Action = execBtEditClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 7
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'EDITAR'
    GlyphResID = 0
  end
  object btUndo: TResBitBtn
    Left = 310
    Top = 6
    Width = 32
    Height = 32
    Action = execBtUndoClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 8
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'DESFAZER'
    GlyphResID = 0
  end
  object btSave: TResBitBtn
    Left = 348
    Top = 6
    Width = 32
    Height = 32
    Action = execBtSaveClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 9
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'SALVAR'
    GlyphResID = 0
  end
  object btCancel: TResBitBtn
    Left = 386
    Top = 6
    Width = 32
    Height = 32
    Action = execBtCancelClick
    Cancel = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 10
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'CANCELAR'
    GlyphResID = 0
  end
  object btNew: TResBitBtn
    Left = 424
    Top = 6
    Width = 32
    Height = 32
    Action = execBtNewClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 11
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'NOVO'
    GlyphResID = 0
  end
  object btCopy: TResBitBtn
    Left = 462
    Top = 6
    Width = 32
    Height = 32
    Action = execBtCopyClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 12
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'COPIAR'
    GlyphResID = 0
  end
  object btDelete: TResBitBtn
    Left = 500
    Top = 6
    Width = 32
    Height = 32
    Action = execBtDeleteClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 13
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'EXCLUIR'
    GlyphResID = 0
  end
  object btExport: TResBitBtn
    Left = 538
    Top = 6
    Width = 32
    Height = 32
    Action = execBtExportClick
    ParentShowHint = False
    ShowHint = True
    TabOrder = 14
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'EXPORTTO'
    GlyphResID = 0
  end
  object btExit: TResBitBtn
    Left = 576
    Top = 6
    Width = 32
    Height = 32
    Hint = 'Fechar formul'#225'rio'
    Cancel = True
    ParentShowHint = False
    ShowHint = True
    TabOrder = 15
    OnClick = btExitClick
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'SAIR'
    GlyphResID = 0
  end
  object btajuda: TResBitBtn
    Left = 614
    Top = 6
    Width = 32
    Height = 32
    Hint = 'Ajuda Sobre Fun'#231#227'o'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 16
    Visible = False
    OnClick = btajudaClick
    NumGlyphs = 4
    GlyphLoadType = glByResName
    GlyphResName = 'AJUDA'
    GlyphResID = 0
  end
  object MenuClicks: TPopupMenu
    object Primeiro1: TMenuItem
      Action = execBtFirstClick
      Caption = 'Primeiro'
    end
    object Anterior1: TMenuItem
      Action = execBtPrewClick
      Caption = 'Anterior'
    end
    object Proximo1: TMenuItem
      Action = execBtNextClick
      Caption = 'Pr'#243'ximo'
    end
    object Ultimo1: TMenuItem
      Action = execBtLastClick
      Caption = #218'ltimo'
    end
    object Historico1: TMenuItem
      Action = execBtSearchClick
      Caption = 'Pesquisar'
    end
    object Pesquisa1: TMenuItem
      Action = execBtBrowseClick
      Caption = 'Listar'
    end
    object VaPara1: TMenuItem
      Action = execBtGoToClick
      Caption = 'V'#225' Para'
    end
    object Editar1: TMenuItem
      Action = execBtEditClick
      Caption = 'Editar'
    end
    object Desfazer1: TMenuItem
      Action = execBtUndoClick
      Caption = 'Desfazer'
    end
    object Salvar1: TMenuItem
      Action = execBtSaveClick
      Caption = 'Salvar'
    end
    object Cancelar1: TMenuItem
      Action = execBtCancelClick
      Caption = 'Cancelar'
    end
    object Novo1: TMenuItem
      Action = execBtNewClick
      Caption = 'Novo'
    end
    object Copiar1: TMenuItem
      Action = execBtCopyClick
      Caption = 'Copiar'
    end
    object Excluir1: TMenuItem
      Action = execBtDeleteClick
      Caption = 'Excluir'
    end
    object Exportar1: TMenuItem
      Action = execBtExportClick
      Caption = 'Exportar'
      ShortCut = 16468
    end
  end
  object ActionList1: TActionList
    Left = 30
    object execBtFirstClick: TAction
      Enabled = False
      Hint = 'Primeiro registro.'
      ShortCut = 16464
      OnExecute = btFirstClick
    end
    object execBtPrewClick: TAction
      Enabled = False
      Hint = 'Registro anterior.'
      ShortCut = 16449
      OnExecute = btPrewClick
    end
    object execBtNextClick: TAction
      Enabled = False
      Hint = 'Pr'#243'ximo registro.'
      ShortCut = 16466
      OnExecute = btNextClick
    end
    object execBtLastClick: TAction
      Enabled = False
      Hint = #218'ltimo registro.'
      ShortCut = 16469
      OnExecute = btLastClick
    end
    object execBtSearchClick: TAction
      Hint = 'Pesquisar registros.'
      ShortCut = 16465
      OnExecute = btSearchClick
    end
    object execBtBrowseClick: TAction
      Hint = 'Listar registros.'
      ShortCut = 16460
      OnExecute = btBrowseClick
    end
    object execBtGoToClick: TAction
      Enabled = False
      Hint = 'V'#225' para registro.'
      ShortCut = 16470
      OnExecute = btGoToClick
    end
    object execBtEditClick: TAction
      Enabled = False
      Hint = 'Editar informa'#231#245'es do registro.'
      ShortCut = 16453
      OnExecute = btEditClick
    end
    object execBtUndoClick: TAction
      Enabled = False
      Hint = 'Desfazer altera'#231#245'es do registro.'
      ShortCut = 16452
      OnExecute = btUndoClick
    end
    object execBtSaveClick: TAction
      Enabled = False
      Hint = 'Salvar altera'#231#245'es do registro.'
      ShortCut = 16467
      OnExecute = btSaveClick
    end
    object execBtCancelClick: TAction
      Enabled = False
      Hint = 'Cancelar altera'#231#245'es do registro.'
      ShortCut = 16472
      OnExecute = btCancelClick
    end
    object execBtNewClick: TAction
      Hint = 'Inserir novo registro vazio.'
      ShortCut = 16462
      OnExecute = btNewClick
    end
    object execBtCopyClick: TAction
      Enabled = False
      Hint = 'Copiar informa'#231#245'es para novo registro.'
      ShortCut = 16451
      OnExecute = btCopyClick
    end
    object execBtDeleteClick: TAction
      Enabled = False
      Hint = 'Excluir registro.'
      ShortCut = 16430
      OnExecute = btDeleteClick
    end
    object execBtExportClick: TAction
      Enabled = False
      Hint = 'Exportar registros.'
      OnExecute = btExportClick
    end
  end
end
