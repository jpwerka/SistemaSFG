object SfgLicenceSvc: TSfgLicenceSvc
  OldCreateOrder = False
  AllowPause = False
  DisplayName = 'SfgLicenceSvc'
  Interactive = True
  AfterInstall = ServiceAfterInstall
  OnExecute = ServiceExecute
  OnStart = ServiceStart
  OnStop = ServiceStop
  Left = 192
  Top = 114
  Height = 150
  Width = 215
  object ServerSocket: TServerSocket
    Active = False
    Port = 0
    ServerType = stNonBlocking
    OnListen = ServerSocketListen
    OnClientRead = ServerSocketClientRead
    Left = 30
    Top = 6
  end
  object SocketTimer: TTimer
    Enabled = False
    Interval = 180000
    OnTimer = SocketTimerTimer
    Left = 102
    Top = 6
  end
end
