//---------------------------------------------------------------------------
#ifndef uSfgBrowseSupH
#define uSfgBrowseSupH
//---------------------------------------------------------------------------
#include "uSfgBrowse.h"
//---------------------------------------------------------------------------
namespace SfgBrowse {
	void EscolheFornecedor(TForm *pParent, SfgBrowseReturn OnBrowseReturn);
	void EscolheProdutoFornecedor(TForm *pParent, String Fornecedor, SfgBrowseReturn OnBrowseReturn);
};
#endif

