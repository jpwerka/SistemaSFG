//---------------------------------------------------------------------------
#ifndef uDataModuleH
#define uDataModuleH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <DB.hpp>
#include <AppEvnts.hpp>
#include "ZConnection.hpp"
#include "ZAbstractDataset.hpp"
#include "ZAbstractRODataset.hpp"
#include "ZDataset.hpp"
#include "ZSqlMonitor.hpp"
#include <ScktComp.hpp>
#define SFG_MAX_SIZE_MSG 0x00000400
//---------------------------------------------------------------------------
class PACKAGE TSfgDataCenter : public TDataModule
{
__published:	// IDE-managed Components
	TZConnection *AppConnection;
   TZSQLMonitor *SfgSQLMonitor;
   TZQuery *QyTransaction;
   void __fastcall DataModuleDestroy(TObject *Sender);
private:	// User declarations
   bool bWaitSocket;
	bool __fastcall LerConnections();
	bool __fastcall LerLicenceServer();
	bool __fastcall LerLicenceClient();
public:		// User declarations
   bool ExistDataBase;
   bool IsLicenceOK;
   bool InTransaction;
	__fastcall TSfgDataCenter(TComponent* Owner);
   bool __fastcall OpenClientSocket();
   bool __fastcall CloseClientSocket();
   bool __fastcall ClientSocketRead();
   bool __fastcall ClientSocketSend();
   bool __fastcall ValidLicence();
   bool __fastcall ValidDatabase();
   //void __fastcall WaitForSocket();
   //void __fastcall SetSocketToWait(bool bWait);
   bool __fastcall StartTrans();
   bool __fastcall CommitTrans();
   bool __fastcall RollbackTrans();
};
//---------------------------------------------------------------------------
extern PACKAGE TSfgDataCenter *SfgDataCenter;
extern PACKAGE TZConnection *AppConnection;
extern PACKAGE SOCKET AppClientSocket;
//---------------------------------------------------------------------------
#endif
