#define _WIN32_DCOM
#include <windows.h>
#include <comdef.h>
#include <wbemidl.h>
#include <stdio.h>
//#include <Iphlpapi.h>
#include "strsafe.h"
#include "uSfgCriptoLic.h"
//#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "bcbatl.lib")
#pragma comment(lib, "wbemuuid.lib")
static bool bComInitSeg = false;
//---------------------------------------------------------------------------
void __stdcall _com_issue_error(HRESULT hr) throw(_com_error)
{
   RaiseException(EXCEPTION_NONCONTINUABLE_EXCEPTION, EXCEPTION_NONCONTINUABLE, 
		1, (ULONG_PTR *)&hr);
}
void __stdcall _com_issue_errorex(HRESULT hr, IUnknown* pu, REFIID ref) throw(_com_error)
{
	RaiseException(EXCEPTION_NONCONTINUABLE_EXCEPTION, EXCEPTION_NONCONTINUABLE, 
		1, (ULONG_PTR *)&hr);
}
//---------------------------------------------------------------------------
//Guarda as posições das informações em meio ao arquivo texto
//com a licença gerada para o sistema SFG
// -- Endereço MAC dividido em 6 posições de 2 caracteres  --  Não utilizar
//Serial do Processador com 8 posições de 2 caracteres
//Código do cliente dividido em 3 posições de 5 caracteres
//Número de licenças ocupando 1 posição de 6 caracteres
//Denominação do cliente dividido em 2 posições
//    com tamanho de 3 caracteres + descricao limitada a 50 caracteres
//Data de validade na licença no formato HEX dividido em 4 posições de 2 caracteres
//Serial = iPos[0] + iPos[5] + iPos[9] + iPos[6] + iPos[4] + iPos[3] + iPos[17] + iPos[16]
//Código Cliente = iPos[2] + iPos[7] + iPos[1]
//Licenças = iPos[8];
//Denominação Cliente = iPos[11] + iPos[10]
//A denominação do cliente é composta por : Tamanho 000 + Descricao C[N] - Limitado a 50 caracteres
//Portanto deve ter um espaco de 50 caracteres no texto reservado para a denominação - 140 ao 190
//Validade = iPos[12] + iPos[14] + iPos[13] + iPos[15]
int iPos[] = {10 /*até 11*/,45 /*até 49*/,89 /*até 93*/,
              136 /*até 137*/,198 /*até 199*/,222 /*até 223*/,
              256 /*até 257*/,345 /*até 349*/,403 /*até 408*/,
              490 /*até 491*/,140 /*até 189*/,22 /*até 24*/,
              447 /*ate 448*/,312 /*até 313*/,270 /*até 271*/,
              288 /*ate 289*/, 300/*sté 301*/, 502 /*até 503*/};
char *Buffer = NULL;
char *TextBase = {"\
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecena\
s sagittis tristique nisl, ut sagittis arcu aliquet et. Nam nec \
purus nisi, sit amet auctor lacus. Nam eget libero quis eros por\
ta dapibus. Curabitur ultrices purus ut arcu feugiat vel convall\
is diam molestie. Ut adipiscing augue eget ante imperdiet lobort\
is. Etiam feugiat neque sit amet massa placerat volutpat. Curabi\
tur neque purus, lobortis nec cursus vitae, gravida sit amet est\
. Vestibulum varius varius aliquam. Integer vel erat eget comodo"
};
int TextTable[] = {
   300,  1,134,396,177,108,197,399,408,166,182, 31,326,273,260,322,
   309,357,201,307,406, 89,212,371, 50,392,484,445,285, 45,286,356,
    51,208,476, 35,461, 75,469,227,222,377,234,252,282,343, 37,178,
   209,509,291,104,230,430,128, 85,117,240,100,479,186,213,420,416,
   436, 10,332,253, 47,248,499,389, 20,488,403,308,494,451,370,402,
   204,200,147,119,395,135, 54,241,237, 14,183, 29,287,194,239,159,
    34, 83,412,348,390, 93,438,372,190, 67,317,232,279,320, 78,288,
     9, 92,382,  4,277,267, 87, 70,491,511,294,255,142,109,455,265,
   188,330,304,  8,319, 44, 25, 68,424,502,185,338,477,393,271,  2,
   376,297,155,264,407,422,161,123,350,250,470,141,417,247,217,496,
     7, 52,351,391,146, 79,206,482,489,180,481,274,169,323,385,103,
   251,505,321,238,440,244,150,352, 69,342,361,490,328,495,500,345,
   283,411,278,483,281,293, 38, 95, 64, 11,258,199, 80,378, 12,296,
   373,449,116,174,280,485,443,487, 63,374, 98,380,221,363,165,269,
   145,442, 13,214,259,105,302, 74,358,316,127,226,460, 96,493,510,
   158,233,458,507,138, 30,179,275,401,295,457, 32,480,193,344,263,
   228,439,299, 39,450,444,459,195, 19,121,375,349, 28, 58,337,148,
   415,215,311, 56,149,152,347,472,454,115,224, 24, 81,428,289,303,
    22, 99,189,111,173,429,276, 59,325,486,431,388,268,467, 72,306,
   172,335,198,331,164,359,112,181,492,202,129,203,101,102,272,262,
   211, 61,379, 88,124,171,125,419,192,471, 46, 86,137,410,225,318,
   421, 41,339,218, 21,468,362, 65,162,312,497,397,292,114,216,301,
   386,122,446,425,187,136,381,366,113, 66,220,139, 18,456,167,427,
   131,140, 84,270, 42, 91,353,340,503, 73,313,473,447, 48,413,364,
   354, 27, 57,441,110,120,236,418,157, 77,  0,261,463,462, 43,423,
   144,432,314, 16, 40,394,368,365,242,132,170,341, 97,414,346,219,
   130,256,163,387, 76,452,398,151,223, 94,118,254,506,435,154, 90,
   334,355,210,266, 49,400,466, 23,336, 55,465, 17,  3,243,504,437,
    62,508,229,448,107, 71, 36,475,384,191,106,405,478,329,245,156,
   383,143,404,327,367,315, 26,434,133,501,498,426,474,298, 60,175,
     6,464,  5,284,310,184,168, 53,231,246,235,360,126,333, 33,153,
   290,324,433,196,453,176,305,249,409, 82,160,369,205,257, 15,207
};
//---------------------------------------------------------------------------
char *SerialLic;
int NumberLic;
char *CodCliente;
char *DenCliente;
long ValidadeLic;
//---------------------------------------------------------------------------
char* EncryptText(char *Source);
//---------------------------------------------------------------------------
bool SfgLoadLicenceFile(char *ErrorMsg)
{
   HANDLE hFile;
   DWORD dwBytesRead;
   char *BufferAux;
   char *FirstSerialLic;
   char cHex[5];
   int iSizeH, iSizeT, iAsc;

   char bfPath[MAX_PATH];
   char *pPath;
   ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

   if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
      pPath = strrchr(bfPath,'\\');
      pPath++;
   } else {
      pPath = bfPath;
   }
   StringCchCopy(pPath,strlen("SfgLicence.lic")+1,"SfgLicence.lic");
   //Abre o arquivo de licença para validar o sistema
   hFile = CreateFile(bfPath,    // create SfgLicence.lic
             GENERIC_READ,                 // open for reading
             0,                            // do not share
             NULL,                         // no security
             OPEN_EXISTING,                // open existing
             FILE_ATTRIBUTE_NORMAL,        // normal file
             NULL);                        // no attr. template

   if (hFile == INVALID_HANDLE_VALUE) {
      char *pErrorMsg = {"Não foi possível encontrar o arquivo de licenças."};
      StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      return false;
   }
   if (Buffer)
      //delete[] Buffer;
      HeapFree(GetProcessHeap(),0,Buffer);
   //Cria um Buffer suficiente para ler o arquivo
   iSizeH = (strlen(TextBase)*2)+1;
   Buffer = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSizeH*sizeof(char)); //new char[iSizeH];
   //ZeroMemory(Buffer,iSizeH*sizeof(char));
   if (!ReadFile(hFile, Buffer, iSizeH*sizeof(char), &dwBytesRead, NULL)) {
      char *pErrorMsg = {"Não foi possível efetuar a leitura o arquivo de licenças."};
      StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      return false;
   }
   CloseHandle(hFile);
   //Deve transformar o texto que está em HEX para ASC
   iSizeT = strlen(TextBase)+1;
   BufferAux = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSizeT*sizeof(char)); //new char[iSizeT];
   cHex[0] = '0';
   cHex[1] = 'x';
   cHex[4] = '\0';
   //ZeroMemory(BufferAux,iSizeT*sizeof(char));
   for (int i=0; i < iSizeH-1; i+=2) {
      cHex[2] = Buffer[i];
      cHex[3] = Buffer[i+1];
      sscanf( cHex, "%i", &iAsc );
      BufferAux[TextTable[i/2]] = (char)iAsc;
   }

   HeapFree(GetProcessHeap(),0,Buffer);  //Apaga o Buffer em HEX
   Buffer = BufferAux; //Atribui o novo Buffer agora em ASC
   //Busca as informações de licença do Buffer
   SerialLic = SfgGetLicenceSerial();
   CodCliente = SfgGetLicenceCodClient();
   DenCliente = SfgGetLicenceDenClient();
   ValidadeLic = SfgGetLicenceValidade();
   NumberLic = SfgGetLicenceNumber();
   HeapFree(GetProcessHeap(),0,Buffer);;  //Apaga o Buffer em ASC
   Buffer = NULL;

   FirstSerialLic = GetFirstSerialLic(ErrorMsg);
   if (FirstSerialLic == NULL) {
      if (strlen(ErrorMsg) <= 0) {
         char *pErrorMsg = {"Não foi possível recuperar as informações da máquina servidor."};
         StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      }
      return false;
   }

   if (strcmp(FirstSerialLic, SerialLic) != 0) {
      char *pErrorMsg = {"O arquivo de licenças encontrado não é valido para esta máquina como servidor."};
      StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      HeapFree(GetProcessHeap(),0,FirstSerialLic);
      return false;
   }
   HeapFree(GetProcessHeap(),0,FirstSerialLic);

   return true;
}
//---------------------------------------------------------------------------
char* SfgGetLicenceSerial()
{
   char *pSerialLic;
   if (Buffer == NULL)
      return NULL;
   //Aloca a memória suficiente para o Serial e zera a mesma
   pSerialLic = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,17*sizeof(char));
   //Copia do Buffer para o Serial conforme as posições espalhadas
   //Serial = iPos[0] + iPos[5] + iPos[9] + iPos[6] + iPos[4] + iPos[3] + iPos[17] + iPos[16]
   for (int i=0; i<16; i++) {
      if (i < 2)
         pSerialLic[i] = Buffer[iPos[0]+i];
      else if (i < 4)
         pSerialLic[i] = Buffer[iPos[5]+i-2];
      else if (i < 6)
         pSerialLic[i] = Buffer[iPos[9]+i-4];
      else if (i < 8)
         pSerialLic[i] = Buffer[iPos[6]+i-6];
      else if (i < 10)
         pSerialLic[i] = Buffer[iPos[4]+i-8];
      else if (i < 12)
         pSerialLic[i] = Buffer[iPos[3]+i-10];
      else if (i < 14)
         pSerialLic[i] = Buffer[iPos[17]+i-12];
      else
         pSerialLic[i] = Buffer[iPos[16]+i-14];
   }
   return pSerialLic;
}
//---------------------------------------------------------------------------
char* SfgGetLicenceCodClient()
{
   char *pCodClient;
   int iPosl = 0;
   if (Buffer == NULL)
      return NULL;
   //Aloca a memória suficiente para o cliente e zera a mesma
   pCodClient = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,16*sizeof(char));
   //Copia do Buffer para o Cliente conforme as posições espalhadas
   //Cliente = iPos[2] + iPos[7] + iPos[1]
   for (int i=0; i<15; i++) {
      if (i < 5) {
         iPosl = iPos[2]+i;
      } else if (i < 10) {
         iPosl = iPos[7]+i-5;
      } else {
         iPosl = iPos[1]+i-10;
      }
      pCodClient[i] = Buffer[iPosl];
   }
   pCodClient[15] = '\0';
   return pCodClient;
}
//---------------------------------------------------------------------------
char* SfgGetLicenceDenClient()
{
   char *pDenClient;
   if (Buffer == NULL)
      return NULL;

   //DenClient = iPos[11] + iPos[10]
   char cNumber[4];
   for (int i=0; i<3; i++) {
      cNumber[i] = Buffer[iPos[11]+i];
   }
   int iSize = atoi(cNumber);
   //Aloca a memória suficiente para o cliente e zera a mesma
   pDenClient = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(iSize+1)*sizeof(char));
   for (int i=0; i<iSize; i++) {
      pDenClient[i] = Buffer[iPos[10]+i];
   }
   pDenClient[iSize] = '\0';
   return pDenClient;
}
//---------------------------------------------------------------------------
long SfgGetLicenceValidade()
{
   char cHex[11];
   long lNumber = 0;
   int iPosl = 0;
   if (Buffer == NULL)
      return 0;
   cHex[0] = '0';
   cHex[1] = 'x';
   //Copia do Buffer para a Validade conforme as posições espalhadas
   //Validade = iPos[12] + iPos[14] + iPos[13] + iPos[15]
   for (int i=0; i<8; i++) {
      if (i < 2) {
         iPosl = iPos[12]+i;
      } else if (i < 4) {
         iPosl = iPos[14]+i-2;
      } else if (i < 6) {
         iPosl = iPos[13]+i-4;
      } else {
         iPosl = iPos[15]+i-6;
      }
      cHex[i+2] = Buffer[iPosl];
   }
   cHex[10] = '\0';
   //Transforma o HEX em INT
   sscanf( cHex, "%i", &lNumber );
   return lNumber;
}
//---------------------------------------------------------------------------
int SfgGetLicenceNumber()
{
   char cHex[9];
   int iNumber = 0;
   if (Buffer == NULL)
      return 0;
   cHex[0] = '0';
   cHex[1] = 'x';
   //Copia do Buffer para o HEX conforme as posições espalhadas
   //Licenças = iPos[8];
   for (int i=0; i<6; i++) {
      cHex[i+2] = Buffer[iPos[8]+i];
   }
   cHex[8] = '\0';
   //Transforma o HEX em INT
   sscanf( cHex, "%i", &iNumber );
   return iNumber;
}
//---------------------------------------------------------------------------
bool  SfgSaveLicenceFile(char *ErrorMsg)
{
   HANDLE hFile;
   DWORD dwBytesWritten, dwPos;
   int iSizeT, iSizeH;
   char *pSerialLic, *BufferAux;

   char bfPath[MAX_PATH];
   char *pPath;
   ZeroMemory( bfPath, sizeof(char)*MAX_PATH);

   if(GetModuleFileName(NULL,bfPath,MAX_PATH)) {
      pPath = strrchr(bfPath,'\\');
      pPath++;
   } else {
      pPath = bfPath;
   }
   StringCchCopy(pPath,strlen("SfgLicence.lic")+1,"SfgLicence.lic");

   //Aloca espaço, zera o Buffer e copia o texto base para o Buffer
   iSizeT = strlen(TextBase)+1;
   Buffer = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,iSizeT*sizeof(char));
   //ZeroMemory(Buffer,iSizeT*sizeof(char));
   StringCchCopy(Buffer,iSizeT,TextBase);
   //Mistura as informações no meio do Buffer
   SfgSetLicenceSerial(SerialLic);
   SfgSetLicenceCodClient(CodCliente);
   SfgSetLicenceDenClient(DenCliente);
   SfgSetLicenceValidade(ValidadeLic);
   SfgSetLicenceNumber(NumberLic);
   //Transforma o Buffer de ASC para HEX colocando cada ASC como um HEX de 2 digitos
   BufferAux = EncryptText(Buffer);
   HeapFree(GetProcessHeap(),0,Buffer); //Apaga o Buffer em ASC
   Buffer = BufferAux; //Atribui o novo Buffer agora em HEX
   //Cria um arquivo para salvar os dados da licença
   hFile = CreateFile(bfPath,    // create SfgLicence.lic
             GENERIC_WRITE,                // open for writing
             0,                            // do not share
             NULL,                         // no security
             CREATE_ALWAYS,                // overwrite existing
             FILE_ATTRIBUTE_NORMAL,        // normal file
             NULL);                        // no attr. template

   if (hFile == INVALID_HANDLE_VALUE) {
      char *pErrorMsg = {"Não foi possível efetuar a criação o arquivo de licenças."};
      StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      delete pErrorMsg;
      return false;
   }
   //Grava no arquivo o texto em HEX agora com o dobro do tamanho
   iSizeH = strlen(Buffer);
   dwPos = SetFilePointer(hFile, 0, NULL, FILE_END);

   LockFile(hFile, dwPos, 0, dwPos + iSizeH*sizeof(char), 0);
   if (!WriteFile(hFile, Buffer, iSizeH*sizeof(char), &dwBytesWritten, NULL)) {
      char *pErrorMsg = {"Não foi possível efetuar a gravação o arquivo de licenças."};
      StringCchCopy(ErrorMsg,strlen(pErrorMsg)+1,pErrorMsg);
      return false;
   }
   UnlockFile(hFile, dwPos, 0, dwPos + iSizeH*sizeof(char), 0);
   CloseHandle(hFile);

   HeapFree(GetProcessHeap(),0,Buffer); //Apaga o Buffer em HEX
   Buffer = NULL;
   
   return true;
}
//---------------------------------------------------------------------------
void SfgSetLicenceSerial(char *pSerialLic)
{
   if (Buffer == NULL)
      return;
   //Serial = iPos[0] + iPos[5] + iPos[9] + iPos[6] + iPos[4] + iPos[3] + iPos[17] + iPos[16]
   for (int i=0; i<16; i++) {
      if (i < 2)
         Buffer[iPos[0]+i] = pSerialLic[i];
      else if (i < 4)
         Buffer[iPos[5]+i-2] = pSerialLic[i];
      else if (i < 6)
         Buffer[iPos[9]+i-4] = pSerialLic[i];
      else if (i < 8)
         Buffer[iPos[6]+i-6] = pSerialLic[i];
      else if (i < 10)
         Buffer[iPos[4]+i-8] = pSerialLic[i];
      else if (i < 12)
         Buffer[iPos[3]+i-10] = pSerialLic[i];
      else if (i < 14)
         Buffer[iPos[17]+i-12] = pSerialLic[i];
      else
         Buffer[iPos[16]+i-14] = pSerialLic[i];
   }
}
//---------------------------------------------------------------------------
void SfgSetLicenceCodClient(char *pCodClient)
{
   if (Buffer == NULL)
      return;
   //CodCliente = iPos[2] + iPos[7] + iPos[1]
   for (int i=0; i<15; i++) {
      if (i < 5)
         Buffer[iPos[2]+i] = pCodClient[i];
      else if (i < 10)
         Buffer[iPos[7]+i-5] = pCodClient[i];
      else
         Buffer[iPos[1]+i-10] = pCodClient[i];
   }
}
//---------------------------------------------------------------------------
void SfgSetLicenceDenClient(char *pDenClient)
{
   if (Buffer == NULL)
      return;
   //DenClient = iPos[11] + iPos[10]
   int iSize = strlen(pDenClient);
   char cNumber[4];
   StringCbPrintf(cNumber,4*sizeof(char),"%03d",iSize);
   for (int i=0; i<3; i++) {
      Buffer[iPos[11]+i] = cNumber[i];
   }
   for (int i=0; i<iSize; i++) {
      Buffer[iPos[10]+i] = pDenClient[i];
   }
}
//---------------------------------------------------------------------------
void SfgSetLicenceValidade(long lValidade)
{
   if (Buffer == NULL)
      return;
   char cNumberHex[9];
   StringCbPrintf(cNumberHex,9*sizeof(char),"%08X",lValidade);
   //Validade = iPos[12] + iPos[14] + iPos[13] + iPos[15]
   for (int i=0; i<8; i++) {
      if (i < 2)
         Buffer[iPos[12]+i] = cNumberHex[i];
      else if (i < 4)
         Buffer[iPos[14]+i-2] = cNumberHex[i];
      else if (i < 6)
         Buffer[iPos[13]+i-4] = cNumberHex[i];
      else
         Buffer[iPos[15]+i-6] = cNumberHex[i];
   }
}
//---------------------------------------------------------------------------
void SfgSetLicenceNumber(int iNumber)
{
   if (Buffer == NULL)
      return;
   char cNumberHex[7];
   StringCbPrintf(cNumberHex,7*sizeof(char),"%06X",iNumber);
   //Licenças = iPos[8];
   for (int i=0; i<6; i++) {
      Buffer[iPos[8]+i] = cNumberHex[i];
   }
}
//---------------------------------------------------------------------------
char *EncryptText(char *Source)
{
  char *Dest;
  int I,L;
  unsigned char A;
  char cHex[3];

  L = strlen(Source);
  Dest = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,((L*2)+2)*sizeof(char));//new char[((L*2)+1)];

  for(I = 0; I < L; I++) {
      A = Source[TextTable[I]];
      StringCbPrintf(cHex,3*sizeof(char),"%02X%",(int)A);
      Dest[I*2] = cHex[0];
      Dest[(I*2)+1] = cHex[1];
  }

  Dest[(I*2)+1] = '\0';
  return Dest;
}
//---------------------------------------------------------------------------
//char* GetFirstSerialLic() {
//   // Get the buffer length required for IP_ADAPTER_INFO.
//   ULONG BufferLength = 0;
//   BYTE* pBuffer = 0;
//   char* pSerialLic;
//   if( ERROR_BUFFER_OVERFLOW == GetAdaptersInfo( 0, &BufferLength ))
//   {
//       // Now the BufferLength contain the required buffer length.
//       // Allocate necessary buffer.
//       pBuffer = (BYTE*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,BufferLength*sizeof(BYTE)); //new BYTE[ BufferLength ];
//   }
//   else
//   {
//       // Error occurred. handle it accordingly.
//       return NULL;
//   }
//   pSerialLic = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,13*sizeof(char));//new char[13];
//   //ZeroMemory(pSerialLic,13*sizeof(char));
//
//   // Get the Adapter Information.
//   PIP_ADAPTER_INFO pAdapterInfo = reinterpret_cast<PIP_ADAPTER_INFO>(pBuffer);
//   GetAdaptersInfo( pAdapterInfo, &BufferLength );
//   // Iterate the network adapters and print their MAC address.
//   while( pAdapterInfo )
//   {
//      // Assuming pAdapterInfo->AddressLength is 6.
//      if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET) {
//         StringCbPrintf(pSerialLic,13*sizeof(char),
//                        "%02X%02X%02X%02X%02X%02X",
//                           pAdapterInfo->Address[0],
//                           pAdapterInfo->Address[1],
//                           pAdapterInfo->Address[2],
//                           pAdapterInfo->Address[3],
//                           pAdapterInfo->Address[4],
//                           pAdapterInfo->Address[5]);
//         break;
//      }
//      // Get next adapter info.
//      pAdapterInfo = pAdapterInfo->Next;
//   }
//   // deallocate the buffer.
//   HeapFree(GetProcessHeap(),0,pBuffer);
//   return pSerialLic;
//}
//---------------------------------------------------------------------------
char* ConvertBSTRToStringEx(WCHAR* pSrc)
{
	char *Temp;
	int T = SysStringLen(pSrc)+1;
	Temp = (char*)HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,T*sizeof(char));
	WideCharToMultiByte(CP_ACP,0,pSrc,T,Temp,T,NULL,NULL);
	return Temp;
}
//---------------------------------------------------------------------------
char* GetFirstSerialLic(char *ErrorMsg) {
   HRESULT hres;
   char *cRet = NULL;

   // Initialize COM.
   hres = CoInitialize(NULL); //CoInitializeEx(NULL, COINIT_MULTITHREADED);
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao inicializar a biblioteca COM. Erro Nº 0x%08X"};
     StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
     return NULL;              // Program has failed.
   }

   if (!bComInitSeg) {
      // Initialize
      hres =  CoInitializeSecurity(
          NULL,     
          -1,      // COM negotiates service                  
          NULL,    // Authentication services
          NULL,    // Reserved
          RPC_C_AUTHN_LEVEL_DEFAULT,    // authentication
          RPC_C_IMP_LEVEL_IMPERSONATE,  // Impersonation
          NULL,             // Authentication info 
          EOAC_NONE,        // Additional capabilities
          NULL              // Reserved
          );
                        
      if (FAILED(hres))
      {
        char *pErrorMsg = {"Falha ao inicializar a segurança COM. Erro Nº 0x%08X"};
        StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
        CoUninitialize();
        return NULL;          // Program has failed.
      }
      bComInitSeg = true;
   }
   
   // Obtain the initial locator to Windows Management
   // on a particular host computer.
   IWbemLocator *pLoc = 0;
   
   hres = CoCreateInstance(
       CLSID_WbemLocator,             
       0, 
       CLSCTX_INPROC_SERVER, 
       IID_IWbemLocator, (LPVOID *) &pLoc);
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao criar o objeto IWbemLocator. Erro Nº 0x%08X"};
     StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
     CoUninitialize();
     return NULL;       // Program has failed.
   }
   
   IWbemServices *pSvc = 0;
   
   // Connect to the root\cimv2 namespace with the
   // current user and obtain pointer pSvc
   // to make IWbemServices calls.
   
   hres = pLoc->ConnectServer(       
       _bstr_t(L"ROOT\\CIMV2"), // WMI namespace
       NULL,                    // User name
       NULL,                    // User password
       0,                       // Locale
       NULL,                    // Security flags                 
       0,                       // Authority       
       0,                       // Context object
       &pSvc                    // IWbemServices proxy
       );                              
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Não foi possível conectar ao WMI. Erro Nº 0x%08X"};
     StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
     pLoc->Release();
     CoUninitialize();
     return NULL;                // Program has failed.
   }
   // Set the IWbemServices proxy so that impersonation
   // of the user (client) occurs.
   hres = CoSetProxyBlanket(      
      pSvc,                         // the proxy to set
      RPC_C_AUTHN_WINNT,            // authentication service
      RPC_C_AUTHZ_NONE,             // authorization service
      NULL,                         // Server principal name
      RPC_C_AUTHN_LEVEL_CALL,       // authentication level
      RPC_C_IMP_LEVEL_IMPERSONATE,  // impersonation level
      NULL,                         // client identity 
      EOAC_NONE                     // proxy capabilities     
   );
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Não foi possível setar o proxi blanket. Erro Nº 0x%08X"};
     StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
     pSvc->Release();
     pLoc->Release();
     CoUninitialize();
     return NULL;               // Program has failed.
   }

   // Use the IWbemServices pointer to make requests of WMI. 
   // Make requests here:

   // For example, query for all the running processes
   IEnumWbemClassObject* pEnumerator = NULL;
   hres = pSvc->ExecQuery(
       bstr_t("WQL"), 
       bstr_t("SELECT * FROM Win32_Processor WHERE ProcessorType = 3"),
       WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
       NULL,
       &pEnumerator);
   
   if (FAILED(hres))
   {
     char *pErrorMsg = {"Falha ao executar a consulta das informações da máquina. Erro Nº 0x%08X"};
     StringCbPrintf(ErrorMsg,strlen(pErrorMsg)+5,pErrorMsg,hres);
     pSvc->Release();
     pLoc->Release();     
     CoUninitialize();
     return NULL;               // Program has failed.
   }
   else
   { 
      IWbemClassObject *pclsObj;
      ULONG uReturn = 0;
   
      while (pEnumerator)
      {
         hres = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
         if(0 == uReturn)
         {
             break;
         }

         VARIANT vtProp;

         // Get the value of the Name property
         hres = pclsObj->Get(L"ProcessorID", 0, &vtProp, 0, 0);
         cRet = ConvertBSTRToStringEx(vtProp.bstrVal);
         VariantClear(&vtProp);
      }

   }
 
   // Cleanup
   // ========
   pSvc->Release();
   pLoc->Release();
   CoUninitialize();

   return cRet;
}




