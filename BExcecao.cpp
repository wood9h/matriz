#include <string.h>
//---------------------------------------------------------------------------
#pragma hdrstop
#include "BExcecao.h"
//---------------------------------------------------------------------------
BExcecao::BExcecao(void)
{
    DefMensagem("Erro!");
}
//---------------------------------------------------------------------------
BExcecao::BExcecao(const char* pcMens)
{
    DefMensagem(pcMens);
}
//---------------------------------------------------------------------------
BExcecao::BExcecao(const BExcecao& E)
{
    DefMensagem(E.Mensagem());
}
//---------------------------------------------------------------------------
BExcecao::~BExcecao(void)
{
    delete [] pcMsg;
}
//---------------------------------------------------------------------------
void BExcecao::DefMensagem(const char* pcMens)
{
    unsigned uComp = strlen(pcMens);

    pcMsg = new char[uComp+1];
    strcpy(pcMsg,pcMens);
}
//---------------------------------------------------------------------------
const char* BExcecao::Mensagem(void) const
{
    return pcMsg;
}
//---------------------------------------------------------------------------

