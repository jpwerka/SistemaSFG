inherited Frm1012: TFrm1012
  Caption = 'Atualiza'#231#227'o Banco Dados'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Atualiza'#231#227'o Banco Dados'
    TabOrder = 2
  end
  inherited BodyPanel: TPanel
    TabOrder = 3
    object AtuDBInsts: TStringAlignGrid
      Left = 0
      Top = 63
      Width = 758
      Height = 402
      Align = alClient
      ColCount = 9
      DefaultRowHeight = 20
      FixedCols = 0
      RowCount = 2
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
      TabOrder = 0
      OnDblClick = AtuDBInstsDblClick
      OnDrawCell = AtuDBInstsDrawCell
      SelectedCellColor = clHighlight
      SelectedFontColor = clHighlightText
      ColWidths = (
        20
        20
        80
        90
        140
        80
        90
        140
        300)
      Cells = (
        2
        0
        'A'#231#227'o'
        3
        0
        'Tipo Objeto'
        4
        0
        'Objeto'
        5
        0
        'Sub-A'#231#227'o'
        6
        0
        'Sub-Tipo'
        7
        0
        'Objeto Realcionado'
        8
        0
        'Coment'#225'rio')
      PropCell = (
        1
        0
        1
        2
        0
        2
        0
        1
        2
        0
        3
        0
        1
        2
        0
        4
        0
        1
        2
        0
        5
        0
        1
        2
        0
        6
        0
        1
        2
        0
        7
        0
        1
        2
        0)
      PropCol = ()
      PropRow = ()
      PropFixedCol = ()
      PropFixedRow = ()
    end
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 758
      Height = 63
      Align = alTop
      BevelOuter = bvNone
      TabOrder = 1
      object Label1: TLabel
        Left = 0
        Top = 10
        Width = 39
        Height = 13
        Caption = '&Arquivo:'
      end
      object Label2: TLabel
        Left = 0
        Top = 38
        Width = 61
        Height = 13
        Caption = '&Identificador:'
      end
      object Label3: TLabel
        Left = 222
        Top = 38
        Width = 26
        Height = 13
        Caption = '&Data:'
      end
      object Label4: TLabel
        Left = 372
        Top = 38
        Width = 61
        Height = 13
        Caption = 'P&r'#233'-requisito:'
      end
      object XMLPath: TEdit
        Left = 43
        Top = 8
        Width = 400
        Height = 21
        TabOrder = 0
      end
      object btLoadXML: TButton
        Left = 448
        Top = 8
        Width = 21
        Height = 21
        Hint = 
          'Clique para escolher um arquivo xml|para atualiza'#231#227'o do banco de' +
          ' dados.'
        Caption = '...'
        TabOrder = 1
        OnClick = btLoadXMLClick
      end
      object btAtualiza: TResBitBtn
        Left = 525
        Top = 7
        Width = 81
        Height = 24
        Hint = 
          'Atualiza na tabela abaixo os comandos|com base no arquivo xml in' +
          'formado.'
        Caption = 'At&ualizar'
        TabOrder = 2
        OnClick = btAtualizaClick
        NumGlyphs = 4
        Spacing = -1
        GlyphLoadType = glByResName
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
      object btProcessar: TResBitBtn
        Left = 657
        Top = 7
        Width = 81
        Height = 24
        Hint = 'Processa os comandos de atualiza'#231#227'o do banco de dados.'
        Caption = '&Processar'
        TabOrder = 3
        OnClick = btProcessarClick
        Glyph.Data = {
          76020000424D7602000000000000760000002800000040000000100000000100
          04000000000000020000130B0000130B00001000000000000000000000002020
          2000FF00000000FF00000000FF0084848400C6C6C600E2E2E200FFFFFF000000
          0000000000000000000000000000000000000000000000000000800000000000
          0000800000000000000180000000000000008000000000000000808888850588
          8880808888850588888180888885058888808088888505888880808850503050
          5880808850507050588180885050205058808088505040505880808603503053
          0680808607507057068180860250205206808086045040540680808055333335
          5080808055777775508180805522222550808080554444455080808500350530
          0580808500750570058180850025052005808085004505400580808033308033
          3080808077708077708180802220802220808080444080444080808500350530
          0580808500750570058180850025052005808085004505400580808855333335
          5880808855777775588180885522222558808088554444455880808803503053
          0880808807507057088180880250205208808088045040540880808850503050
          5880808850507050588180885050205058808088505040505880808888850588
          8880808888850588888180888885058888808088888505888880808888888888
          0000808888888888001180888888888800008088888888880000808888888888
          0808808888888888080880888888888808088088888888880808808888888888
          0088808888888888008880888888888800888088888888880088800000000000
          0888800000000000088880000000000008888000000000000888}
        NumGlyphs = 4
        Spacing = -1
        GlyphResName = 'ATUALIZAR'
        GlyphResID = 0
      end
      object edtIdent: TEdit
        Left = 65
        Top = 35
        Width = 130
        Height = 21
        ReadOnly = True
        TabOrder = 4
      end
      object edtData: TEdit
        Left = 252
        Top = 35
        Width = 76
        Height = 21
        ReadOnly = True
        TabOrder = 5
      end
      object edtRequisito: TEdit
        Left = 438
        Top = 35
        Width = 130
        Height = 21
        ReadOnly = True
        TabOrder = 6
      end
    end
    object pnProgress: TPanel
      Left = 265
      Top = 394
      Width = 232
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
        Width = 220
        Height = 13
        AutoSize = False
        Caption = 'Aguarde... Atualizando Banco de Dados'
      end
      object ProgressAtuDB: TProgressBar
        Left = 6
        Top = 24
        Width = 220
        Height = 17
        Min = 0
        Max = 100
        Step = 1
        TabOrder = 0
      end
    end
  end
  inherited MargemEsq: TPanel
    TabOrder = 4
  end
  inherited MargemDir: TPanel
    TabOrder = 1
  end
  object gbCmdSQL: TGroupBox
    Left = 144
    Top = 144
    Width = 500
    Height = 300
    Caption = 'Comando SQL'
    TabOrder = 0
    Visible = False
    OnMouseDown = gbCmdSQLMouseDown
    object Panel2: TPanel
      Left = 2
      Top = 15
      Width = 496
      Height = 283
      Align = alClient
      BevelOuter = bvNone
      BorderWidth = 6
      Caption = 'Panel2'
      TabOrder = 0
      object CmdSQL: TMemo
        Left = 6
        Top = 6
        Width = 484
        Height = 271
        Align = alClient
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -12
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'comando_sql')
        ParentFont = False
        ScrollBars = ssBoth
        TabOrder = 0
        OnExit = CmdSQLExit
      end
    end
  end
  object XMLAtuDB: TXMLDocument
    Left = 24
    Top = 30
    DOMVendorDesc = 'MSXML'
  end
  object OpenXML: TOpenDialog
    Ctl3D = False
    DefaultExt = '.xml'
    Filter = 'Arquivos xml (*.xml)|*.xml'
    Options = [ofHideReadOnly, ofExtensionDifferent, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Escolher Arquivo'
    Left = 510
  end
  object QyRegAtuDB: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'SELECT * FROM tbl_execucao_atualizacao'
      'WHERE 1=0')
    Params = <>
    Left = 720
    Top = 12
  end
  object ActionList1: TActionList
    Left = 660
    Top = 18
    object execMetadados: TAction
      Caption = 'execMetadados'
      ShortCut = 49229
      OnExecute = execMetadadosExecute
    end
  end
end
