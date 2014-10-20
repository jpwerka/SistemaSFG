object SfgDataCenter: TSfgDataCenter
  OldCreateOrder = False
  OnDestroy = DataModuleDestroy
  Left = 528
  Top = 162
  Height = 302
  Width = 436
  object AppConnection: TZConnection
    Protocol = 'mysql'
    HostName = 'localhost'
    Port = 3306
    Database = 'sistemasfg'
    User = 'root'
    Password = 'senha'
    Catalog = 'sistemasfg'
    TransactIsolationLevel = tiReadUncommitted
    Connected = True
    DesignConnection = True
    Left = 24
    Top = 24
  end
  object SfgSQLMonitor: TZSQLMonitor

    AutoSave = True
    FileName = 'sqlmonitor.log'
    MaxTraceCount = 100
    Left = 102
    Top = 24
  end
  object QyTransaction: TZQuery
    Connection = AppConnection
    Params = <>
    Left = 24
    Top = 78
  end
end
