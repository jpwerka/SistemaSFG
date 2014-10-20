object Sup1002: TSup1002
  Left = 412
  Top = 150
  HorzScrollBar.Visible = False
  VertScrollBar.Visible = False
  BorderStyle = bsDialog
  BorderWidth = 6
  Caption = 'Enviar Pedido Compra por Email'
  ClientHeight = 391
  ClientWidth = 512
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label5: TLabel
    Left = 0
    Top = 111
    Width = 512
    Height = 6
    Align = alTop
    AutoSize = False
  end
  object Label6: TLabel
    Left = 0
    Top = 227
    Width = 512
    Height = 6
    Align = alTop
    AutoSize = False
  end
  object gbInformacao: TGroupBox
    Left = 0
    Top = 0
    Width = 512
    Height = 111
    Align = alTop
    Caption = 'Cabe'#231'alho'
    TabOrder = 0
    object Label4: TLabel
      Left = 6
      Top = 39
      Width = 59
      Height = 13
      Caption = '&Destinat'#225'rio:'
      FocusControl = Destinatario
    end
    object Label1: TLabel
      Left = 10
      Top = 15
      Width = 55
      Height = 13
      Caption = '&Remetente:'
      FocusControl = Remetente
    end
    object Label7: TLabel
      Left = 7
      Top = 63
      Width = 58
      Height = 13
      Caption = 'Email C'#243'&pia:'
      FocusControl = EmailCopia
    end
    object Label3: TLabel
      Left = 24
      Top = 87
      Width = 41
      Height = 13
      Caption = '&Assunto:'
      FocusControl = EmailCopia
    end
    object Remetente: TEdit
      Left = 69
      Top = 12
      Width = 352
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object Destinatario: TEdit
      Left = 69
      Top = 36
      Width = 435
      Height = 21
      TabOrder = 1
    end
    object btOpcoes: TButton
      Left = 430
      Top = 12
      Width = 75
      Height = 21
      Caption = '&Op'#231#245'es'
      TabOrder = 4
      OnClick = btOpcoesClick
    end
    object EmailCopia: TEdit
      Left = 69
      Top = 60
      Width = 435
      Height = 21
      TabOrder = 2
    end
    object Assunto: TEdit
      Left = 69
      Top = 84
      Width = 435
      Height = 21
      TabOrder = 3
    end
  end
  object gbMensagem: TGroupBox
    Left = 0
    Top = 117
    Width = 512
    Height = 110
    Align = alTop
    Caption = '&Mensagem'
    TabOrder = 1
    object Mensagem: TMemo
      Left = 6
      Top = 18
      Width = 498
      Height = 84
      TabOrder = 0
    end
    object pnProgress: TPanel
      Left = 163
      Top = 40
      Width = 186
      Height = 47
      BevelOuter = bvNone
      BorderStyle = bsSingle
      Ctl3D = False
      ParentCtl3D = False
      TabOrder = 1
      Visible = False
      object lbInfoMail: TLabel
        Left = 6
        Top = 6
        Width = 174
        Height = 13
        AutoSize = False
        Caption = 'Aguarde... Enviando email'
      end
      object ProgressMail: TProgressBar
        Left = 6
        Top = 24
        Width = 174
        Height = 17
        Min = 0
        Max = 100
        Step = 20
        TabOrder = 0
      end
    end
  end
  object gbItens: TGroupBox
    Left = 0
    Top = 233
    Width = 512
    Height = 133
    Align = alClient
    Caption = '&Itens'
    TabOrder = 2
    object ListItens: TDBGrid
      Left = 6
      Top = 18
      Width = 498
      Height = 107
      DataSource = DataSource1
      TabOrder = 0
      TitleFont.Charset = DEFAULT_CHARSET
      TitleFont.Color = clWindowText
      TitleFont.Height = -11
      TitleFont.Name = 'MS Sans Serif'
      TitleFont.Style = []
      OnTitleClick = ListItensTitleClick
      Columns = <
        item
          Expanded = False
          FieldName = 'den_produto'
          Title.Caption = 'Denomina'#231#227'o Item'
          Width = 350
          Visible = True
        end
        item
          Expanded = False
          FieldName = 'qtd_produto'
          Title.Alignment = taCenter
          Width = 100
          Visible = True
        end>
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 366
    Width = 512
    Height = 25
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 3
    object btCancel: TButton
      Left = 436
      Top = 3
      Width = 75
      Height = 22
      Caption = '&Cancelar'
      ModalResult = 2
      TabOrder = 0
    end
    object btOK: TButton
      Left = 351
      Top = 3
      Width = 75
      Height = 22
      Caption = '&OK'
      Default = True
      TabOrder = 1
      OnClick = btOKClick
    end
  end
  object pnOpcoes: TPanel
    Left = 264
    Top = 33
    Width = 241
    Height = 84
    BevelOuter = bvNone
    BorderStyle = bsSingle
    Ctl3D = False
    ParentCtl3D = False
    TabOrder = 4
    Visible = False
    OnExit = pnOpcoesExit
    object Label2: TLabel
      Left = 18
      Top = 9
      Width = 62
      Height = 13
      Caption = 'Senha Email:'
    end
    object SenhaEmail: TEdit
      Left = 84
      Top = 6
      Width = 145
      Height = 21
      Ctl3D = True
      ParentCtl3D = False
      PasswordChar = '*'
      TabOrder = 0
    end
    object SalvarMensagem: TCheckBox
      Left = 18
      Top = 54
      Width = 176
      Height = 17
      Caption = 'Salvar mensagem como padr'#227'o.'
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 2
    end
    object LembrarSenha: TCheckBox
      Left = 18
      Top = 30
      Width = 127
      Height = 17
      Caption = 'Lembrar minha senha.'
      Ctl3D = True
      ParentCtl3D = False
      TabOrder = 1
      OnClick = LembrarSenhaClick
    end
  end
  object ClienteSMTP: TIdSMTP
    OnStatus = ClienteSMTPStatus
    SASLMechanisms = <>
    Left = 444
    Top = 42
  end
  object SSLHandlerSMTP: TIdSSLIOHandlerSocketOpenSSL
    MaxLineAction = maException
    Port = 0
    DefaultPort = 0
    SSLOptions.Mode = sslmUnassigned
    SSLOptions.VerifyMode = []
    SSLOptions.VerifyDepth = 0
    Left = 480
    Top = 42
  end
  object QyCadProduto: TZQuery
    Connection = SfgDataCenter.AppConnection
    CachedUpdates = True
    ReadOnly = True
    SQL.Strings = (
      'SELECT v.cod_pedido_compra, v.seq_produto,'
      '       v.cod_produto, p.den_produto, v.qtd_produto'
      '  FROM tbl_pedido_compra_item v,'
      '       tbl_produto p'
      ' WHERE v.cod_pedido_compra = :cod_pedido_compra'
      '   AND v.cod_produto = p.cod_produto'
      ' ORDER BY v.seq_produto')
    Params = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Value = '5'
      end>
    ShowRecordTypes = [usUnmodified, usModified]
    Left = 442
    Top = 304
    ParamData = <
      item
        DataType = ftLargeint
        Name = 'cod_pedido_compra'
        ParamType = ptUnknown
        Value = '5'
      end>
    object CodPedidoCompra: TIntegerField
      FieldName = 'cod_pedido_compra'
      ReadOnly = True
      Required = True
    end
    object QyCadProdutoseq_produto: TIntegerField
      DisplayLabel = 'Seq'
      FieldName = 'seq_produto'
      ReadOnly = True
      Required = True
    end
    object QyCadProdutocod_produto: TStringField
      DisplayLabel = 'Item'
      FieldName = 'cod_produto'
      ReadOnly = True
      Required = True
      Size = 15
    end
    object QyCadProdutoden_produto: TStringField
      DisplayLabel = 'Denomina'#231#227'o'
      FieldName = 'den_produto'
      ReadOnly = True
      Size = 75
    end
    object QyCadProdutoqtd_produto: TFloatField
      DisplayLabel = 'Qtd Solicitada'
      FieldName = 'qtd_produto'
      ReadOnly = True
      DisplayFormat = '#.000'
    end
  end
  object DataSource1: TDataSource
    AutoEdit = False
    DataSet = QyCadProduto
    Left = 412
    Top = 305
  end
end
