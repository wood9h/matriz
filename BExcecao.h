//---------------------------------------------------------------------------
#ifndef BExcecaoH
#define BExcecaoH
//---------------------------------------------------------------------------
class BExcecao
{
    private:
        char* pcMsg;
        void DefMensagem(const char* pcMens);

    protected:
        BExcecao(const char* pcMens);

    public:
        BExcecao(void);
        BExcecao(const BExcecao& E);
        virtual ~BExcecao(void);
        virtual const char* Mensagem(void) const;
};
//---------------------------------------------------------------------------
#endif
