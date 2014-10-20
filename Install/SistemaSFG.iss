#define MyAppName "SoftGreen\Sistema SFG"
#define MyAppVersion "1.5.0.1"
#define MyAppPublisher "SoftGreen Softwares"
#define MyAppURL "http://www.softgreen.inf.br"
#define MyAppExeName "SistemaSFG.exe"

[Setup]
LanguageDetectionMethod=locale
AppId={{A568327D-7CBD-43D5-945E-8C5D95EF26B4}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
VersionInfoVersion={#MyAppVersion}
AppCopyright=© Copyright 2012 By SoftGreen
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf32}\{#MyAppName}
DefaultGroupName=SoftGreen\Sistema SFG
AppComments=Software para gestão de pequenas e micro-empresas
MinVersion=0,5.01sp3
WizardImageFile=installn.bmp
WizardSmallImageFile=installm.bmp
;AppReadmeFile={app}\leiame.txt
LicenseFile=license.txt
OutputBaseFilename=SistemaSFG-Install
SetupIconFile=sfgicon.ico

[Dirs]
Name: "{app}"; Permissions: admins-full

[UninstallDelete]
Type: files; Name: "{app}\connection.ini"
Type: files; Name: "{app}\sqlmonitor.log"
Type: files; Name: "{app}\license.txt"

[Files]
Source: "SfgLicenceCon.dll"; Flags: dontcopy
Source: "SistemaSFG.exe"; DestDir: "{app}"; Flags: confirmoverwrite 32bit sortfilesbyextension
Source: "libmysql.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "libeay32.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "ssleay32.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "borlndmm.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "cc3260mt.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "CallCalendar.dll"; DestDir: "{app}"; Flags: confirmoverwrite onlyifdoesntexist 32bit
Source: "connection.ini"; DestDir: "{app}"; Flags: onlyifdoesntexist; AfterInstall: AfterInstallIni
;Source: "leiame.txt"; DestDir: "{app}"; Flags: isreadme; Attribs: readonly
Source: "license.txt"; DestDir: "{app}"; Flags: overwritereadonly; Attribs: readonly
Source: "Feriados.xml"; DestDir: "{app}"; Flags: confirmoverwrite
Source: "SfgEstoque.dll"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "SfgCompras.dll"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "SfgVendas.dll"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "SfgFinancas.dll"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "SfgFiscal.dll"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "SfgPackage.bpl"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "bpl\rtl60.bpl"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "bpl\vcl60.bpl"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "bpl\dbrtl60.bpl"; DestDir: "{app}"; Flags: confirmoverwrite 32bit
Source: "bpl\vcldb60.bpl"; DestDir: "{app}"; Flags: confirmoverwrite 32bit

[Icons]
Name: "{group}\Sistema SFG"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\{#MyAppExeName}"; IconIndex:0; Parameters: "-db SistemaSFG"; Comment: "Atalho para o sistema SFG.";
Name: "{group}\Desinstalar Sistema SFG"; Filename: "{uninstallexe}"
Name: "{userdesktop}\Sistema SFG"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\{#MyAppExeName}"; IconIndex:0; Parameters: "-db SistemaSFG"; Comment: "Atalho para o sistema SFG."; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\Sistema SFG";  Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"; IconFilename: "{app}\{#MyAppExeName}"; IconIndex:0; Parameters: "-db SistemaSFG"; Comment: "Atalho para o sistema SFG."; Tasks: quicklaunchicon

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

;[Components]
;Name: "completa"; Description: "Instalação completa"; Flags: checkablealone exclusive

[Languages]
Name: "pt"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"

[Code]
function SfgLicSvcConDll(Host: PChar; Port: Integer; MsgError: PChar): Integer;
external 'SfgLicenceSvcCon@files:SfgLicenceCon.dll stdcall setuponly';

var DBPage, SvcPage, CliPage: TWizardPage;
    HostSvcEdt, PortSvcEdt, HostEdt, PortaEdt, DataBaseEdt, UsuarioEdt, ClienteEdt: TNewEdit;
    SenhaEdt: TPasswordEdit;
    CheckUseSvc, CheckSvc: TCheckBox;     

procedure BDPagePortKeyPress(Sender: TObject; var Key: Char);
begin
  if not(((Ord(Key) >= 48) and (Ord(Key) <= 57)) or (Key = #8)) then
    Key := #0;
end;

function ShouldSkipPage(PageID: Integer): Boolean;
begin
  { Skip pages that shouldn't be shown }
  if (PageID = CliPage.ID) and (CheckUseSvc.Checked) then
    Result := True
  else
    Result := False;
end;

function EncryptText(Source: String): String;
var I,L : Integer;
    A: Byte;
    Dest: String;
begin 
  L := Length(Source);
  SetLength(Dest, L);

  for I := 1 to L do
  begin
    A := Ord(Source[L - I + 1]);
	  Dest[I] := Chr((270 + I - 1) - A);
  end;
  Result := Dest;
end;
 
function CliPageNextButtonClick(Sender: TWizardPage): Boolean;
begin
  if Length(ClienteEdt.Text) <> 15 then 
  begin
     MsgBox('Informe o código do cliente com 15 digitos para o uso com o arquivo de licença.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
    
  Result := true;
end;

function DBPageNextButtonClick(Sender: TWizardPage): Boolean;
begin
  if HostEdt.Text = '' then 
  begin
     MsgBox('Informe o IP do servidor do banco de dados.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
  if PortaEdt.Text = '' then 
  begin
     MsgBox('Informe a porta do servidor do banco de dados.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
  if DataBaseEdt.Text = '' then 
  begin
     MsgBox('Informe o banco de dados a ser utilizado pela aplicação.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
  if UsuarioEdt.Text = '' then 
  begin
     MsgBox('Informe o usuário para conexão com o servidor do banco de dados.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
    
  Result := true;
end;

function SvcPageNextButtonClick(Sender: TWizardPage): Boolean;
var MsgError: String;
begin
  if not CheckUseSvc.Checked then 
  begin
    Result := true;
    Exit;
  end;
  if HostSvcEdt.Text = '' then 
  begin
     MsgBox('Informe o IP do servidor de licenças.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
  if PortSvcEdt.Text = '' then 
  begin
     MsgBox('Informe a porta do servidor de licenças.', mbInformation, mb_Ok);
     Result := false;
     Exit;
  end;
  if CheckSvc.State = cbChecked then 
  begin
    SetLength(MsgError, 500);
    if (SfgLicSvcConDll(PChar(HostSvcEdt.Text), StrToInt(PortSvcEdt.Text) , PChar(MsgError)) = 0) then
    begin
       MsgBox(MsgError, mbInformation, mb_Ok);
       Result := false;
       Exit;
    end
    else
       MsgBox('Conexão com servidor de licenças estabelecida com sucesso.', mbInformation, mb_Ok);  
  end;     
  Result := true;
end;

procedure CreateTheWizardPages;
var
  StaticText: TNewStaticText;
  PosX: Integer;
begin
  { TButton and others }
  PosX := 70;
  DBPage := CreateCustomPage(wpSelectDir, 'Conexão com Banco de Dados', 'Parâmetros para a conexão com o banco de dados.');
  DBPage.OnNextButtonClick := @DBPageNextButtonClick;
  
  StaticText := TNewStaticText.Create(DBPage);
  StaticText.Top := ScaleY(10);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Host:';
  StaticText.AutoSize := True;
  StaticText.Parent := DBPage.Surface;
  
  HostEdt := TNewEdit.Create(DBPage);
  HostEdt.Top := StaticText.Top - ScaleY(2);
  HostEdt.Left := ScaleX(PosX);
  HostEdt.Width := ScaleX(150);
  HostEdt.Text := '127.0.0.1';
  HostEdt.Parent := DBPage.Surface;

  StaticText := TNewStaticText.Create(DBPage);
  StaticText.Top := HostEdt.Top + HostEdt.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Porta:';
  StaticText.AutoSize := True;
  StaticText.Parent := DBPage.Surface;
  
  PortaEdt := TNewEdit.Create(DBPage);
  PortaEdt.Top := StaticText.Top - ScaleY(2);
  PortaEdt.Left := ScaleX(PosX);
  PortaEdt.Width := ScaleX(80);
  PortaEdt.Text := '3306';
  PortaEdt.Parent := DBPage.Surface;
  PortaEdt.OnKeyPress := @BDPagePortKeyPress;
  
  StaticText := TNewStaticText.Create(DBPage);
  StaticText.Top := PortaEdt.Top + PortaEdt.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Database:';
  StaticText.AutoSize := True;
  StaticText.Parent := DBPage.Surface;

  DataBaseEdt := TNewEdit.Create(DBPage);
  DataBaseEdt.Top := StaticText.Top - ScaleY(2);
  DataBaseEdt.Left := ScaleX(PosX);
  DataBaseEdt.Width := ScaleX(150);
  DataBaseEdt.Text := 'sistemasfg';
  DataBaseEdt.Parent := DBPage.Surface;

  StaticText := TNewStaticText.Create(DBPage);
  StaticText.Top := DataBaseEdt.Top + DataBaseEdt.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Usuário:';
  StaticText.AutoSize := True;
  StaticText.Parent := DBPage.Surface;

  UsuarioEdt := TNewEdit.Create(DBPage);
  UsuarioEdt.Top := StaticText.Top - ScaleY(2);
  UsuarioEdt.Left := ScaleX(PosX);
  UsuarioEdt.Width := ScaleX(150);
  UsuarioEdt.Text := 'root';
  UsuarioEdt.Parent := DBPage.Surface;

  StaticText := TNewStaticText.Create(DBPage);
  StaticText.Top := UsuarioEdt.Top + UsuarioEdt.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Senha:';
  StaticText.AutoSize := True;
  StaticText.Parent := DBPage.Surface;

  SenhaEdt := TPasswordEdit.Create(DBPage);
  SenhaEdt.Top := StaticText.Top - ScaleY(2);
  SenhaEdt.Left := ScaleX(PosX);
  SenhaEdt.Width := ScaleX(150);
  SenhaEdt.Text := '';
  SenhaEdt.Parent := DBPage.Surface;

  PosX := 70;
  SvcPage := CreateCustomPage(DBPage.Id, 'Conexão com Servidor de Licenças', 'Parâmetros para a conexão com o servidor de licenças.');
  SvcPage.OnNextButtonClick := @SvcPageNextButtonClick;

  CheckUseSvc := TCheckBox.Create(SvcPage);
  CheckUseSvc.Top := ScaleY(10);
  CheckUseSvc.Left := ScaleX(PosX);
  CheckUseSvc.Width := ScaleX(230);
  CheckUseSvc.Caption := 'Utilizar servidor de licenças?';
  CheckUseSvc.State := cbChecked;
  CheckUseSvc.Parent := SvcPage.Surface;

  StaticText := TNewStaticText.Create(SvcPage);
  StaticText.Top := CheckUseSvc.Top + CheckUseSvc.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Host:';
  StaticText.AutoSize := True;
  StaticText.Parent := SvcPage.Surface;
  
  HostSvcEdt := TNewEdit.Create(SvcPage);
  HostSvcEdt.Top := StaticText.Top - ScaleY(2);
  HostSvcEdt.Left := ScaleX(PosX);
  HostSvcEdt.Width := ScaleX(150);
  HostSvcEdt.Text := '127.0.0.1';
  HostSvcEdt.Parent := SvcPage.Surface;

  StaticText := TNewStaticText.Create(SvcPage);
  StaticText.Top := HostSvcEdt.Top + HostSvcEdt.Height + ScaleY(6);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Porta:';
  StaticText.AutoSize := True;
  StaticText.Parent := SvcPage.Surface;
  
  PortSvcEdt := TNewEdit.Create(SvcPage);
  PortSvcEdt.Top := StaticText.Top - ScaleY(2);
  PortSvcEdt.Left := ScaleX(PosX);
  PortSvcEdt.Width := ScaleX(80);
  PortSvcEdt.Text := '4596';
  PortSvcEdt.Parent := SvcPage.Surface;
  PortSvcEdt.OnKeyPress := @BDPagePortKeyPress;
  
  CheckSvc := TCheckBox.Create(SvcPage);
  CheckSvc.Top := PortSvcEdt.Top + PortSvcEdt.Height + ScaleY(6);
  CheckSvc.Left := ScaleX(PosX);
  CheckSvc.Width := ScaleX(250);
  CheckSvc.Caption := 'Validar conexão com servidor de licenças?';
  CheckSvc.State := cbChecked;
  CheckSvc.Parent := SvcPage.Surface; 

  PosX := 70;
  CliPage := CreateCustomPage(SvcPage.Id, 'Cliente para Uso de Licenças', 'Parâmetros para validar o arquivo de licenças.');
  CliPage.OnNextButtonClick := @CliPageNextButtonClick;
  
  StaticText := TNewStaticText.Create(CliPage);
  StaticText.Top := ScaleY(10);
  StaticText.Left := ScaleX(10);
  StaticText.Caption := 'Cliente:';
  StaticText.AutoSize := True;
  StaticText.Parent := CliPage.Surface;
  
  ClienteEdt := TNewEdit.Create(CliPage);
  ClienteEdt.Top := StaticText.Top - ScaleY(2);
  ClienteEdt.Left := ScaleX(PosX);
  ClienteEdt.Width := ScaleX(150);
  ClienteEdt.Text := '';
  ClienteEdt.Parent := CliPage.Surface;
  ClienteEdt.MaxLength := 15;
  ClienteEdt.OnKeyPress := @BDPagePortKeyPress;

end;

procedure AboutButtonOnClick(Sender: TObject);
var StrMsg: String;
begin
  StrMsg := 'O sistema SFG possui total controle de estoque com módulos para '+
'controle de entradas e saídas via pedidos de compra e venda contando '+
'ainda com um controle detalhado de movimentações financeiras. '+#10+#13+#10+#13+
'Possui integração com o Microsoft Excel® permitindo a nível gerencial '+
'análises customizadas das movimentações do sistema. '+#10+#13+#10+#13+
'Possui controle personalizado de acesso por usuário e/ou grupo permitindo '+
'assim cada usuário ter acesso somente ao que é necessário. '+#10+#13+#10+#13+
'Possui vários relatórios para análise das informações com possibilidade de '+
'envio de email direto do sistema, bem como exportar para vários formatos '+
'de arquivos diferentes facilitando a troca de informações com outros aplicativos.'
  MsgBox(StrMsg, mbInformation, mb_Ok);
end;

procedure URLLabelOnClick(Sender: TObject);
var
  ErrorCode: Integer;
begin
  ShellExecAsOriginalUser('open', 'http://www.softgreen.inf.br/', '', '', SW_SHOWNORMAL, ewNoWait, ErrorCode);
end;

procedure CreateAboutButtonAndURLLabel(ParentForm: TSetupForm; CancelButton: TNewButton);
var
  AboutButton: TNewButton;
  URLLabel: TNewStaticText;
begin
  AboutButton := TNewButton.Create(ParentForm);
  AboutButton.Left := ParentForm.ClientWidth - CancelButton.Left - CancelButton.Width;
  AboutButton.Top := CancelButton.Top;
  AboutButton.Width := CancelButton.Width;
  AboutButton.Height := CancelButton.Height;
  AboutButton.Caption := '&Sobre...';
  AboutButton.OnClick := @AboutButtonOnClick;
  AboutButton.Parent := ParentForm;

  URLLabel := TNewStaticText.Create(ParentForm);
  URLLabel.Caption := 'www.softgreen.inf.br';
  URLLabel.Cursor := crHand;
  URLLabel.OnClick := @URLLabelOnClick;
  URLLabel.Parent := ParentForm;
  { Alter Font *after* setting Parent so the correct defaults are inherited first }
  URLLabel.Font.Style := URLLabel.Font.Style + [fsUnderline];
  if GetWindowsVersion >= $040A0000 then   { Windows 98 or later? }
    URLLabel.Font.Color := clHotLight
  else
    URLLabel.Font.Color := clBlue;
  URLLabel.Top := AboutButton.Top + AboutButton.Height - URLLabel.Height - 2;
  URLLabel.Left := AboutButton.Left + AboutButton.Width + ScaleX(20);
end;

procedure InitializeWizard();
var
  BackgroundBitmapImage: TBitmapImage;
  BackgroundBitmapText: TNewStaticText;
begin
  { Custom wizard pages }

  CreateTheWizardPages;
  
  { Custom controls }

  CreateAboutButtonAndURLLabel(WizardForm, WizardForm.CancelButton);

end;

procedure AfterInstallIni();
var strIni: String;
begin
  strIni := ExpandConstant('{app}') + '\connection.ini';
  //MsgBox(PortaEdt.Text + ' ' + strIni ,mbInformation, mb_Ok);
  SetIniString('SistemaSFG','protocol','mysql',strIni);
  SetIniString('SistemaSFG','hostname',HostEdt.Text,strIni);
  SetIniString('SistemaSFG','port',PortaEdt.Text,strIni);
  SetIniString('SistemaSFG','database',DataBaseEdt.Text,strIni);
  SetIniString('SistemaSFG','user',EncryptText(UsuarioEdt.Text),strIni);
  if SenhaEdt.Text <> '' then 
    SetIniString('SistemaSFG','password',EncryptText(SenhaEdt.Text),strIni)
  else
    SetIniString('SistemaSFG','password','',strIni)
  //Configurando o servidor de licenças
  SetIniBool('LicenceServer','useserver',CheckUseSvc.State,strIni);
  SetIniString('LicenceServer','address',HostSvcEdt.Text,strIni);
  SetIniString('LicenceServer','port',PortSvcEdt.Text,strIni);
  
  if CheckUseSvc.State = cbUnchecked then
    SetIniString('LicenceClient','cliente',ClienteEdt.Text,strIni);
 
end;
