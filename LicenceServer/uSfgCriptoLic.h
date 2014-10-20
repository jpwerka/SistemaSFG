//---------------------------------------------------------------------------
//Funções para fazer a validação do arquivo de licença
bool  SfgLoadLicenceFile(char *ErrorMsg);
char* SfgGetLicenceSerial();
char* SfgGetLicenceCodClient();
char* SfgGetLicenceDenClient();
long SfgGetLicenceValidade();
int   SfgGetLicenceNumber();
//---------------------------------------------------------------------------
//Funções para fazer a geração do arquivo de licença
//char* GetFirstSerialLic();
char* GetFirstSerialLic(char *ErrorMsg);
bool SfgSaveLicenceFile(char *ErrorMsg);
void SfgSetLicenceSerial(char *pSerial);
void SfgSetLicenceCodClient(char *pCodClient);
void SfgSetLicenceDenClient(char *pDenClient);
void SfgSetLicenceValidade(long lValidade);
void SfgSetLicenceNumber(int iNumber);
//---------------------------------------------------------------------------
extern char *SerialLic;
extern int NumberLic;
extern char *CodCliente;
extern char *DenCliente;
extern long ValidadeLic;



