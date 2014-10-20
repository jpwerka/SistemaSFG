object frmSearch: TfrmSearch
  Left = 288
  Top = 181
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  BorderWidth = 6
  Caption = 'Pesquisar Registros'
  ClientHeight = 278
  ClientWidth = 680
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = True
  Position = poMainFormCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Separador: TLabel
    Left = 0
    Top = 151
    Width = 680
    Height = 6
    Align = alTop
    AutoSize = False
  end
  object btAddWhere: TButton
    Left = 0
    Top = 254
    Width = 130
    Height = 23
    Hint = 
      'Permite ao usu'#225'rio adicionar um filtro customizado.|Este filtro ' +
      'sempre deve estar no formato SQL ANSI.'
    Caption = '&Adicionar Cl'#225'usula'
    TabOrder = 2
    OnClick = btAddWhereClick
  end
  object btExibe: TButton
    Left = 145
    Top = 254
    Width = 130
    Height = 23
    Hint = 'Alterna a visualiza'#231#227'o do comando entre SQL e texto.'
    Caption = '&Exibir Comando SQL'
    TabOrder = 3
    OnClick = btExibeClick
  end
  object btProfile: TButton
    Left = 290
    Top = 254
    Width = 130
    Height = 23
    Caption = 'Configura'#231#245'es &Perfil'
    TabOrder = 4
    OnClick = btProfileClick
  end
  object BtOk: TButton
    Left = 513
    Top = 254
    Width = 75
    Height = 23
    Hint = 'Aplica o filtro retornando os registros encontrados.'
    Caption = '&OK'
    Default = True
    TabOrder = 6
    OnClick = BtOkClick
  end
  object BtCancel: TButton
    Left = 605
    Top = 254
    Width = 75
    Height = 23
    Hint = 'Cancela a aplica'#231#227'o do filtro.'
    Cancel = True
    Caption = '&Cancelar'
    ModalResult = 2
    TabOrder = 5
    OnClick = BtCancelClick
  end
  object pgFilter: TPageControl
    Left = 0
    Top = 0
    Width = 680
    Height = 151
    ActivePage = pgFtBasico
    Align = alTop
    TabIndex = 0
    TabOrder = 0
    object pgFtBasico: TTabSheet
      Caption = '&1 - B'#225'sico'
      object grdBasico: TStringAlignGrid
        Left = 0
        Top = 0
        Width = 672
        Height = 123
        Hint = 'Listagem de filtros b'#225'sicos a serem aplicados.'
        Align = alClient
        ColCount = 4
        DefaultRowHeight = 18
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goTabs]
        PopupMenu = PopupMenu1
        TabOrder = 0
        OnDblClick = grdDblClick
        OnDrawCell = grdBasicoDrawCell
        OnKeyPress = grdKeyPress
        OnSelectCell = grdSelectCell
        SelectedCellColor = clHighlight
        SelectedFontColor = clHighlightText
        ColWidths = (
          14
          180
          64
          385)
        Cells = (
          1
          0
          'Campo'
          2
          0
          'Condi'#231#227'o'
          3
          0
          'Valor')
        PropCell = (
          0
          0
          1
          2
          0
          2
          0
          1
          2
          0)
        PropCol = (
          0
          3
          1
          0
          1
          3
          1
          0
          2
          1
          2
          3
          1
          0)
        PropRow = ()
        PropFixedCol = ()
        PropFixedRow = ()
      end
      object cbCampoBas: TComboBox
        Left = 18
        Top = 46
        Width = 180
        Height = 21
        Hint = 'Escolha um campo para aplicar o filtro.'
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
        Visible = False
        OnChange = cbCampoBasChange
        OnExit = LastEditExit
      end
      object cbCondicaoBas: TComboBox
        Left = 208
        Top = 46
        Width = 50
        Height = 21
        Hint = 'Escolha o tipo de condi'#231#227'o a ser aplicada ao filtro.'
        Style = csDropDownList
        ItemHeight = 13
        ItemIndex = 0
        TabOrder = 2
        Text = '='
        Visible = False
        OnChange = cbCondicaoBasChange
        OnExit = LastEditExit
        Items.Strings = (
          '='
          '!='
          '>='
          '<='
          '>'
          '<')
      end
      object edtValorBas: TMaskEdit
        Left = 270
        Top = 46
        Width = 121
        Height = 19
        Hint = 
          'Entre com o valor para aplicar o filtro.|Pode ser utilizado * pa' +
          'ra filtrar por partes da informa'#231#227'o.'
        BevelOuter = bvNone
        Ctl3D = False
        ParentCtl3D = False
        TabOrder = 3
        Text = 'edtValorBas'
        Visible = False
        OnExit = LastEditExit
      end
      object cbValorBas: TComboBox
        Left = 270
        Top = 66
        Width = 145
        Height = 21
        Hint = 'Escolha um valor para aplicar o filtro.'
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 4
        Visible = False
        OnChange = cbValorBasChange
        OnExit = LastEditExit
      end
      object ckCampoBas: TCheckBox
        Left = 270
        Top = 96
        Width = 97
        Height = 17
        Color = clBtnFace
        Ctl3D = True
        ParentColor = False
        ParentCtl3D = False
        TabOrder = 5
        Visible = False
        OnClick = ckCampoBasClick
        OnExit = LastEditExit
      end
    end
    object pgFtAvancado: TTabSheet
      Caption = '&2 - Avan'#231'ado'
      ImageIndex = 1
      object grdAvancado: TStringAlignGrid
        Left = 0
        Top = 0
        Width = 672
        Height = 123
        Hint = 
          'Listagem de filtros avan'#231'ados a serem aplicados.|Podem ser utili' +
          'zados os condicionais: = , != , >= , <= , > , <|Pode ser utiliza' +
          'do * para filtrar por partes da informa'#231#227'o.'
        Align = alClient
        ColCount = 2
        DefaultRowHeight = 18
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goEditing]
        PopupMenu = PopupMenu1
        TabOrder = 0
        OnDblClick = grdDblClick
        OnKeyPress = grdKeyPress
        OnSelectCell = grdSelectCell
        SelectedCellColor = clHighlight
        SelectedFontColor = clHighlightText
        OnValidateEdit = grdAvancadoValidateEdit
        ColWidths = (
          14
          45)
        Cells = (
          1
          0
          'E/OU')
        PropCell = ()
        PropCol = (
          0
          3
          1
          0)
        PropRow = ()
        PropFixedCol = ()
        PropFixedRow = ()
      end
      object cbCondicaoAdv: TComboBox
        Left = 18
        Top = 42
        Width = 45
        Height = 21
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 1
        Visible = False
        OnChange = cbCondicaoAdvChange
        OnExit = LastEditExit
        Items.Strings = (
          'E'
          'OU')
      end
    end
    object pgFtOrder: TTabSheet
      Caption = '&3 - Ordena'#231#227'o'
      ImageIndex = 2
      object grdOrder: TStringAlignGrid
        Left = 0
        Top = 0
        Width = 672
        Height = 123
        Hint = 'Listagem de sequencia de ordena'#231#227'o customizada.'
        Align = alClient
        ColCount = 3
        DefaultRowHeight = 18
        RowCount = 2
        Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goTabs]
        PopupMenu = PopupMenu1
        TabOrder = 0
        OnDblClick = grdDblClick
        OnKeyPress = grdKeyPress
        OnSelectCell = grdSelectCell
        SelectedCellColor = clHighlight
        SelectedFontColor = clHighlightText
        ColWidths = (
          14
          180
          100)
        Cells = (
          1
          0
          'Campo'
          2
          0
          'Ordena'#231#227'o')
        PropCell = (
          0
          0
          1
          2
          0)
        PropCol = (
          0
          3
          1
          0)
        PropRow = ()
        PropFixedCol = ()
        PropFixedRow = ()
      end
      object cbCampoOrd: TComboBox
        Left = 18
        Top = 46
        Width = 180
        Height = 21
        Hint = 'Escolha um campo para aplicar a ordena'#231#227'o.'
        Style = csDropDownList
        ItemHeight = 0
        TabOrder = 1
        Visible = False
        OnChange = cbCampoOrdChange
        OnExit = LastEditExit
      end
      object cbCondicaoOrd: TComboBox
        Left = 202
        Top = 46
        Width = 100
        Height = 21
        Hint = 'Escolha o tipo de condi'#231#227'o a ser aplicada a ordena'#231#227'o.'
        Style = csDropDownList
        ItemHeight = 13
        TabOrder = 2
        Visible = False
        OnChange = cbCondicaoOrdChange
        OnExit = LastEditExit
        Items.Strings = (
          'Ascendente'
          'Descendente')
      end
    end
  end
  object StrResultFilter: TMemo
    Left = 0
    Top = 157
    Width = 680
    Height = 90
    Align = alTop
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 1
  end
  object PopupMenu1: TPopupMenu
    Left = 576
    Top = 108
    object AdicionarLinha1: TMenuItem
      Action = addLine
    end
    object RemoverLinha1: TMenuItem
      Action = delLine
    end
  end
  object ActionList1: TActionList
    Left = 544
    Top = 108
    object delLine: TAction
      Caption = '&Remover Linha'
      ShortCut = 32850
      OnExecute = delLineExecute
    end
    object addLine: TAction
      Caption = '&Adicionar Linha'
      ShortCut = 32833
      OnExecute = addLineExecute
    end
  end
end
