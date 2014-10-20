inherited Frm1011: TFrm1011
  Caption = 'Permiss'#227'o Menu'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  inherited HeaderPanel: TPanel
    Caption = 'Permiss'#227'o Menu'
  end
  inherited BodyPanel: TPanel
    Left = 0
    Width = 774
    object Panel1: TPanel
      Left = 0
      Top = 0
      Width = 774
      Height = 465
      Align = alClient
      BevelOuter = bvNone
      ParentColor = True
      TabOrder = 0
      object Splitter1: TSplitter
        Left = 300
        Top = 0
        Width = 3
        Height = 465
        Cursor = crHSplit
        MinSize = 100
      end
      object TreeMenu: TTreeView
        Left = 0
        Top = 0
        Width = 300
        Height = 465
        Align = alLeft
        HideSelection = False
        Images = ImageList2
        Indent = 19
        ReadOnly = True
        RowSelect = True
        StateImages = ImageList2
        TabOrder = 1
        OnMouseDown = TreeMenuMouseDown
      end
      object Panel2: TPanel
        Left = 303
        Top = 0
        Width = 471
        Height = 465
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Panel4: TPanel
          Left = 0
          Top = 47
          Width = 471
          Height = 110
          Align = alTop
          BevelOuter = bvNone
          Enabled = False
          TabOrder = 0
          object Label2: TLabel
            Left = 6
            Top = 57
            Width = 73
            Height = 13
            Caption = 'Usu'#225'rio/Grupo:'
          end
          object permissao_por: TRadioGroup
            Left = 6
            Top = 6
            Width = 185
            Height = 40
            Caption = 'Permiss'#227'o por'
            Columns = 2
            Items.Strings = (
              'Usu'#225'rio'
              'Grupo')
            TabOrder = 0
          end
          object usuario_grupo: TEdit
            Left = 83
            Top = 54
            Width = 91
            Height = 21
            ReadOnly = True
            TabOrder = 1
          end
          object denominacao: TEdit
            Left = 180
            Top = 54
            Width = 276
            Height = 21
            ReadOnly = True
            TabOrder = 2
          end
        end
        object Panel3: TPanel
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
          object btPesquisa: TResBitBtn
            Left = 6
            Top = 6
            Width = 32
            Height = 32
            Action = execBtPesquisa
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            NumGlyphs = 4
            GlyphLoadType = glByResName
            GlyphResName = 'PESQUISA'
            GlyphResID = 0
          end
          object btDelete: TResBitBtn
            Left = 44
            Top = 6
            Width = 32
            Height = 32
            Action = execBtDelete
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            NumGlyphs = 4
            GlyphLoadType = glByResName
            GlyphResName = 'EXCLUIR'
            GlyphResID = 0
          end
          object btExit: TResBitBtn
            Left = 82
            Top = 6
            Width = 32
            Height = 32
            Hint = 'Fechar Formul'#225'rio'
            Cancel = True
            ParentShowHint = False
            ShowHint = True
            TabOrder = 2
            OnClick = btExitClick
            NumGlyphs = 4
            GlyphLoadType = glByResName
            GlyphResName = 'SAIR'
            GlyphResID = 0
          end
        end
      end
    end
  end
  inherited MargemEsq: TPanel
    Width = 0
  end
  inherited MargemDir: TPanel
    Left = 774
    Width = 0
  end
  object PopupMenu1: TPopupMenu
    Left = 558
    Top = 12
    object Adicionarfilho1: TMenuItem
      Action = execBtPesquisa
      Caption = 'Pesquisar usu'#225'rio/grupo'
    end
    object Excluirtodasaspermisses1: TMenuItem
      Action = execBtDelete
      Caption = 'Excluir todas as permiss'#245'es'
    end
  end
  object ActionList1: TActionList
    Left = 594
    Top = 12
    object execBtPesquisa: TAction
      Hint = 'Pesquisa por usu'#225'rio/grupo para alterar permiss'#227'o.'
      ShortCut = 16465
      OnExecute = execBtPesquisaExecute
    end
    object execBtDelete: TAction
      Hint = 'Excluir todas as permiss'#245'es do usu'#225'rio/grupo.'
      ShortCut = 16430
      OnExecute = execBtDeleteExecute
    end
  end
  object PermissaoMenu: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'CALL carrega_permissao_menu(:usuario_grupo,:tip_permissao);')
    Params = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptInput
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptInput
        Size = 1
      end>
    Left = 630
    Top = 12
    ParamData = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptInput
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptInput
        Size = 1
      end>
  end
  object DeletePermissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      'DELETE FROM tbl_permissao_usuario_grupo'
      ' WHERE usuario_grupo = :usuario_grupo'
      '   AND tip_permissao = :tip_permissao')
    Params = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptInput
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptInput
        Size = 1
      end>
    Left = 666
    Top = 12
    ParamData = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptInput
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptInput
        Size = 1
      end>
  end
  object ImageList2: TImageList
    Left = 517
    Top = 11
    Bitmap = {
      494C010105000900040010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000E9F2F400C2BEBC00A7908900A3837A00A1837B009F949000B9C1C300E7F2
      F400000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FCFFFF00C8BE
      BC00B76C5800D1593800DD5D3900E0633F00DE613D00D75A3700B95338009672
      6900BCC9CB000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FBFFFF00CBA89E00D15F
      3D00F17C5600FA987400FCB69B00F9926E00F88E6900F3846000EF744F00DE5B
      3600A2564200B2B9BA00FEFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CEB5AF00D9644200FB99
      7300FB9B7500F9BB9B00FFE5CD00F9A88900FA926D00FA947000F78F6B00F180
      5C00E6623C00A0574400BFCCCE00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000ECE9E900D16F5300F99A7500FCA4
      7E00F69F7D00FBDDC900FFE4CB00FCC8B100F8946F00F9957000F9947000F991
      6D00F17F5B00DC59360096787000ECF5F7000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CEA69C00EA8F6900FCB08B00F9A4
      7E00F7C0A800FFF3E800FFE8D400FEE1CD00F9A58400F9977200F9957100FA93
      7000F78F6B00EF734D00B3553B00BCC8CA000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000CD816B00F9B68E00FCB28D00F8AE
      8A00FBEBE400FCEBE200FCE4D500FFECDA00FCC4AB00F9987300F9997500F995
      7100FA957000F3835F00D5583600A29B98000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D97F6000FCC8A100FBB78F00F8D3
      C200FDF6F200F7B89800F0B49D00FFF5E800FEE4D300FAA68300F99B7500F998
      7400FA967100F88D6900DC5F3B00A18881000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000DA7C5B00FCD5AC00F8C1A200F8D8
      CA00FAC6A500FBBC9300F1A17E00F9DED300FFF4EA00FCC6AE00F99B7500F99B
      7600F9977300FA926E00DE623D00A4877E000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D9836600FCDCB400F9C4A000FBCA
      A300FCC9A300FCC7A200FABA9300F1AB8F00FDF0E800FFEDE000FAAA8900FA9A
      7500F9987400FA936F00DC603D00A7958F000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000D28C7800F7CFA600FFE4BD00FDD9
      B200FDD5AE00FCCEA800FDC7A200F7B38C00F2B79E00FDF5EE00FCD8C500F99C
      7600F9997500F9906C00D0593900C2C2C1000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000E1C2BB00E4987400FFF8D000FDE5
      BE00FDDEB700FDD6AE00FCCBA500FCC39D00F9B18A00F6B99D00FCEBE100FBBF
      A500FB9B7600F17E5700B56C5900ECF3F5000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000F9FBFB00D4857000F4CDA600FFFE
      D600FDE4BE00FDD9B200FCCFA800FCC49F00FBBC9600FBAE8700F8AF8E00FCC7
      AF00FC9F7A00D25E3D00C8BDBA00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000EEE2E100D97C6100F6D2
      AB00FFFAD200FEE2BB00FCCFA900FCC49E00FBBA9400FCB28D00FCAD8700FB9C
      7600DC674400C9A39900FBFFFF00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000EEE1DE00D180
      6900E8A07900FBD9B100FDE1B900FED7B000FCCBA500FBBB9500F0977000D56E
      4F00CDAAA100FBFFFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F1F4
      F600D5B0A800CF816A00DE805F00E2856100DF805D00D37A5E00C6918300E7DF
      DD00FEFFFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000F0EBF100BDC0BD008FA08F00849A830084988300939B9300C0BBC100F0EA
      F100000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B1996000B19
      96000C1A9D000B19960000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000FDFCFE00BFC5
      BE006FA16D005FAE5A0063B85E0066BC630064BA61005FB35B00599C5500758C
      7300C5BFC7000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000142394001036E200083E
      FF000840FF000C27BB000B199600000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000001C82B5001A80
      B300177DB0001A80B000177DAD001379AA000F75A6000A70A300076DA000056B
      9E0003699C0001679A00006699000000000000000000FDFCFE00A9C1A80061B0
      5E007BCE790092DC9300B1E6B2008EDA8D008AD8890083D2810076CB73005FB8
      5B005A8C5700B7B4B800FFFEFF00000000000000000000000000CE1C1C00CE1C
      1C00CE1C1C00CE1C1C00CE1C1C00AD1C1C00AD1C1C00AD1C1C00AD1C1C00AD1C
      1C009C1C1C009C1C1C009C1C1C0000000000212EB100578FFA00336DFF000D41
      FF001348FF001148FF001229AC000B199600000000001229AC000B1996000724
      C7000B199600000000000000000000000000000000002187BA0066CCFF001F85
      B80099FFFF0000000000868686000000000071D3FF006ED4FF006ED4FF006ED4
      FF006ED4FF003AA0D30099FFFF000066990000000000B7C7B60068B7640091DC
      920093DD9400B0E4B400D8F4DD00A2E0A3008CDA8C008FDB8F008BD78A007FCF
      7D0066C062005B8B5800C8C2CA000000000000000000CE1C1C00FF687100CE1C
      1C00FF8D8A001C1C1C00A5A5A5001C1C1C00FF687100FF687100FF687100FF68
      7100FF687100EC1C1C00FF8D8A009C1C1C002936B20081BCFD0080BCFF002A60
      FE00194EFF001D53FF001A4CFA001229AC000B1996000F27B9000938F4000039
      FF00022FF0000B199600000000000000000000000000248ABD0066CCFF00268C
      BF0099FFFF00C0C0C00086868600C0C0C0007CE2FF007AE0FF007AE0FF007AE0
      FF007AE0FF0043A9DC0099FFFF0001679A00EAEBE90071B46F0092DB93009ADF
      9C0098DB9900D4F0D700D6F3DC00C2EBC4008ED98E008FDA8F008FDA8F008DD9
      8C007ECF7C0060B65B00798D7800F3EEF40000000000CE1C1C00FF687100CE1C
      1C00FF8D8A00A5A5A500A5A5A500A5A5A500FF778C00FF778C00FF778C00FF77
      8C00FF778C00FF313100FF8D8A009C1C1C00174CFF00475FC30095D6FF0070AA
      FE002A61FE00265CFE00255BFF001F48E9001941E600154CFF000F45FF00093D
      FF000138FF00052ADF001229AC000000000000000000278DC00066CCFF002C92
      C50099FFFF0000000000868686000000000086ECFF0085EBFF0085EBFF0085EB
      FF0085EBFF004DB3E60099FFFF0003699C00A9C3A70086CD8800A4E2A70099DD
      9B00B9E5BA00EDFAF000DDF5E200D8F3DB009EDE9F0090DA91008FDA8F0090DB
      8F008BD78A0073CA71005A985600C6BFC70000000000EC1C1C00FF687100EC1C
      1C00FF8D8A001C1C1C00A5A5A5001C1C1C00FF778C00FF778C00FF778C00FF77
      8C00FF778C00FF313100FF8D8A009C1C1C00000000001C1C9A00658EDE008BCA
      FF00538CFD003066FE003066FE002B61FF00255CFF001F54FE00174CFF000F45
      FF00073EFF000829D8001229AC000000000000000000298FC20066CCFF003298
      CB0099FFFF00C0C0C00086868600C0C0C00092F8FF0091F7FF0091F7FF0091F7
      FF0091F7FF0056BCEF0099FFFF00056B9E0083B78100A6E1AC00A6E3AA00A2DF
      A500E9F6EA00E8F6E900DEF3E000E2F6E600BDEABF0091DB920092DB93008FDA
      8F008FDB8F0082D280005DB159009AA09A0000000000EC1C1C00FF687100EC1C
      1C00FF8D8A00A5A5A500A5A5A500A5A5A500FF8D8A00FF8D8A00FF8D8A00FF8D
      8A00FF8D8A00FF4E4E00FF8D8A00AD1C1C000000000000000000191986004C77
      E1003A72FF003B72FE003B72FE00356BFE002E64FE00275CFE001F54FF001648
      FB000F2CC8000B1996000000000000000000000000002C92C5006ED4FF003399
      CC0099FFFF0000000000868686000000000099FFFF0099FFFF0099FFFF0099FF
      FF0099FFFF005FC5F80099FFFF00076DA0007CBE7B00B5E7BD00A7E2AD00CEEC
      D000F4FAF400ADE1B100AFDDAF00EDFAF100DCF4DF009DDF9E0092DB940092DB
      930090DB90008AD8890062B85F00899A880000000000EC1C1C00FF687100EC1C
      1C00FF8D8A001C1C1C00A5A5A5001C1C1C00FF8D8A00FF8D8A00FF8D8A00FF8D
      8A00FF8D8A00FF4E4E00FF8D8A00AD1C1C000000000000000000174CFF001C34
      BA003F79FF004A83FE00457DFE003F75FE00376EFE002E65FF002455F6000B19
      96000B199600000000000000000000000000000000002E94C7007AE0FF002C92
      C500FFFFFF00D0D0D00000000000C0C0C000F9FFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF0080E6FF00FFFFFF000A70A30078BD7700BEEAC900B5E4B900D4ED
      D500B8E7BD00AAE3B10098D79A00DBF0DB00EEFAF100BFEAC00092DB940093DB
      940091DB92008EDA8D0064BA6100879B860000000000EC1C1C00FF778C00EC1C
      1C00EEEAEA00A5A5A5001C1C1C00A5A5A500EEEAEA00EEEAEA00EEEAEA00EEEA
      EA00EEEAEA00FF778C00EEEAEA00AD1C1C00000000000B1996002842B500548C
      FD005B95FF00558EFE005088FE00477FFE003F76FE00366EFF00295BF5000B19
      960000000000000000000000000000000000000000003096C90085EBFF0080E6
      FF002C92C50070899600C0C0C00000000000389ECB002C92C500278DC0002389
      BC001F85B8001B81B4001A80B3001A80B30081BF8000C4ECD000B4E5BB00B7E7
      BF00B7E8BE00B6E8BE00AAE3B100A5DBA600ECF8EE00E7F8EA00A2E0A30093DC
      940092DB93008FDB8E0064B8600094A1940000000000EC1C1C00FF778C00FF77
      8C00EC1C1C00EC1C1C00A5A5A5001C1C1C00EC1C1C00EC1C1C00EC1C1C00CE1C
      1C00CE1C1C00CE1C1C00CE1C1C00CE1C1C0014169100335CE300609DFF0067A1
      FE00659FFE00619BFE005B96FF004E87FE00447CFE003B72FE003168FF002452
      F0000B199600000000000000000000000000000000003298CB0091F7FF008EF4
      FF008EF4FF0088A2A400F8F8F80000000000F2FFFF00FFFFFF00FFFFFF00FFFF
      FF00FFFFFF00157BAE0000000000000000008FBE8C00B8E5C200CCF0D800C3EC
      CD00BFEBC900BBE9C300B6E8BC00A4DFAA00B1DFB200F1F9F200D1EFD40093DB
      950092DB93008CD98B0060AE5B00C1C2C20000000000EC1C1C00FF8D8A00FF8D
      8A00FF8D8A00FF453200EEEAEA001C1C1C00EEEAEA00EEEAEA00EEEAEA00EEEA
      EA00EEEAEA00CE1C1C0000000000000000002836B40073B1FF007CB8FE0071AB
      FD0074B1FF006DA9FD005A8EF40070ACFD00629BFD003E75FE00346AFE002861
      FF001939CA000B1996000000000000000000000000003399CC00FFFFFF0099FF
      FF0099FFFF008EBBBB00BEC4C400303030003096C0002187BA001E84B7001C82
      B5001A80B300177DB0000000000000000000C5D8C3008DCB9000DAF4E900CCEF
      D900C6EDD100BFEBC900B8E8C000B2E6B900A3E0A800B1E2B300E7F6E900B8E7
      B90094DD95007ACE790070A06D00F3EEF30000000000EC1C1C00EEEAEA00FF8D
      8A00FF8D8A00FF4E4E00FF778C0044444400E91C2800CE1C1C00CE1C1C00CE1C
      1C00CE1C1C00CE1C1C00000000000000000017169A006691E00091D2FF008AC9
      FF0078B1F8004A6BCB000B199600628EE30076B4FF004C84FE00346BFE002A60
      FF001F56FF001229AC001229AC000000000000000000000000003399CC00FFFF
      FF00FFFFFF00FFFFFF00A4A4A4002B91C3000000000000000000000000000000
      000000000000000000000000000000000000FAF9FA0089BD8600B7E2C100DFF6
      EF00CCEFD800C3ECCD00BBE9C400B4E7BB00ACE4B200A1E1A500A6E0A900C0EA
      C20097DF990062B05E00BEC5BD00000000000000000000000000EC1C1C00EEEA
      EA00EEEAEA00EEEAEA00A5A5A500EC1C1C000000000000000000000000000000
      000000000000000000000000000000000000000000001B1A9B005F83D9006B97
      E200272F98000B199600000000002B37B1005F97FB00538DFF00386FFE002A61
      FF001F58FF00153EE4000B199600000000000000000000000000000000003399
      CC003298CB003096C9002E94C700000000000000000000000000000000000000
      00000000000000000000000000000000000000000000E6EBE4007FBE7C00BCE5
      C600DCF5EB00CAEFD600BBE9C300B3E7BA00ABE4B100A6E3AA00A1E1A40094DD
      960069BA6600A6BEA400FDFCFE0000000000000000000000000000000000EC1C
      1C00EC1C1C00EC1C1C00EC1C1C00000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B1996001B1D
      9100174CFF000000000000000000000000002A3FBF004079FF002F68FF00265D
      FE001D46EB0012198E000B199600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000E2EAE10083B9
      800092CF9700C1EACC00C8EDD400C1ECCB00B8E8C000ACE4B2008DD38F006FB7
      6D00ADC3AB00FDFCFE0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001E33C6001840E7001321
      AE000B199600174CFF0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000F5F2
      F500B5CBB20082B880007CC17B007EC57F007AC27B007AB8780094B79200E0E5
      DF00FFFEFF000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000F00F000000000000C007000000000000
      8001000000000000800100000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000010000000000008001000000000000
      C003000000000000E007000000000000FFFFFFFFF00FFFFFC3FFFFFFC007FFFF
      81FFC0018001C001008780008001800000038000000080000001800000008000
      8001800000008000C003800000008000C007800000008000800F800000008000
      000780030000800300038003000080030001C0FF0001C0FF8201E1FF8001E1FF
      C701FFFFC003FFFFFF83FFFFE007FFFF00000000000000000000000000000000
      000000000000}
  end
  object menu_tree: TPopupMenu
    Images = ImageList2
    Left = 72
    Top = 96
    object sem_permissao: TMenuItem
      Caption = 'Sem permiss'#227'o'
      ImageIndex = 0
      OnClick = sem_permissaoClick
    end
    object somente_leitura: TMenuItem
      Caption = 'Somente leitura'
      ImageIndex = 1
      OnClick = somente_leituraClick
    end
    object permissao_total: TMenuItem
      Caption = 'Permiss'#227'o total'
      ImageIndex = 2
      OnClick = permissao_totalClick
    end
    object somente_leitura_g: TMenuItem
      Caption = 'Somente leitura (grupo)'
      ImageIndex = 3
    end
    object permissao_total_g: TMenuItem
      Caption = 'Permiss'#227'o total (grupo)'
      ImageIndex = 4
    end
  end
  object ModificaPermissao: TZQuery
    Connection = SfgDataCenter.AppConnection
    SQL.Strings = (
      
        'CALL modifica_permissao_menu(:usuario_grupo,:tip_permissao,:cod_' +
        'rotina,:nivel_permissao);')
    Params = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptUnknown
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptUnknown
        Size = 1
      end
      item
        DataType = ftString
        Name = 'cod_rotina'
        ParamType = ptUnknown
        Size = 10
      end
      item
        DataType = ftSmallint
        Name = 'nivel_permissao'
        ParamType = ptUnknown
      end>
    Left = 108
    Top = 96
    ParamData = <
      item
        DataType = ftString
        Name = 'usuario_grupo'
        ParamType = ptUnknown
        Size = 16
      end
      item
        DataType = ftString
        Name = 'tip_permissao'
        ParamType = ptUnknown
        Size = 1
      end
      item
        DataType = ftString
        Name = 'cod_rotina'
        ParamType = ptUnknown
        Size = 10
      end
      item
        DataType = ftSmallint
        Name = 'nivel_permissao'
        ParamType = ptUnknown
      end>
  end
end