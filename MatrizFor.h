#ifndef MARIZFORH
#define MARIZFORH

#include"bexcecao.h"
//#include<complex.h>

#pragma option push -A

template<class T>
class MatrizFor
{
    private:
        bool AlocacaoAutomatica;
        T* matrizC;
        static const char* mensagemErro[];
        long nLinhas;
        long nLinhasAlocadas;
        long nColunas;
        long nColunasAlocadas;

    protected:
/*        virtual void AdicionaColunas(long NovasColunas);
        virtual void AdicionaColunas(long NovasColunas, const T& cnst);
        virtual void AdicionaLinhas(long NovasLinhas);
        virtual void AdicionaLinhas(long NovasLinhas, const T& cnst);*/
        inline void TranspoeLineariza(long l, long c, const T** matriz);
        inline void TranspoeLineariza(long l, long c, const T** matriz, long la);

    public:
        //Construtores e destrutor
        inline MatrizFor(void);
        inline MatrizFor(const MatrizFor<T>& MF);
        inline MatrizFor(long l, long c);
        inline MatrizFor(long l, long c, const T** matriz);
        inline MatrizFor(long l, long c, const T& cnst);
        inline MatrizFor(long l, long c, long la, long ca);
        inline MatrizFor(long l, long c, const T** matriz, long la, long ca);
        inline MatrizFor(long l, long c, const T& cnst, long la, long ca);
        virtual ~MatrizFor(void);
        //Operadores
        inline MatrizFor<T>& operator=(const MatrizFor<T>& BF);
        inline T& operator()(long ind);
        inline const T& operator()(long ind) const;
        inline T& operator()(long l, long c);
        inline const T& operator()(long l, long c) const;
        //Manipulacao
        inline void DefAlocacaoAutomatica(bool aa);
        inline bool LeAlocacaoAutomatica(void) const;
        inline T* LeEstruturaDados(void) const;
        inline long NumeroLinhas(void) const;
        inline long NumeroColunas(void) const;
        virtual void Redimensiona(long NovasLinhas, long NovasColunas);
//        virtual void Redimensiona(long NovasLinhas, long NovasColunas,
//            const T& cnst);
        //Excecoes
        class BExDimensoesIncorretas;
        class BExIndiceForaLimites;
        class BExMatrizLinhaColuna;
};

//******************************************************************************
template<class T>
const char* MatrizFor<T>::mensagemErro[] =          ///deve ficar num .cpp?
{
    "", //0
    "Índice fora dos limites.", //1
    "Matriz deve possuir uma linha ou uma coluna.",  //2
    "Matriz alocada com dimensões insuficientes.", //3
    "Valor deve ser maior que zero.", //4
    "Valor deve ser maior ou igual a zero.", //5
    "Dimensões incorretas.", //6
    "Matriz alocada com dimensões insuficientes e sem alocacao automática." //7
};

template<class T>
MatrizFor<T>::MatrizFor(void)
{
    AlocacaoAutomatica = 0;
    matrizC = 0;
    nLinhas = 0;
    nLinhasAlocadas = 0;
    nColunas = 0;
    nColunasAlocadas = 0;
}

template<class T>
MatrizFor<T>::MatrizFor(const MatrizFor<T>& MF)
{
    matrizC = new T[MF.nLinhasAlocadas*MF.nColunasAlocadas];
    for (long j=0; j<MF.nColunas; j++)
        memcpy(matrizC+MF.nLinhasAlocadas*j, MF.matrizC+MF.nLinhasAlocadas*j,
        MF.nLinhas*sizeof(T));
    AlocacaoAutomatica = MF.AlocacaoAutomatica;
    nLinhas = MF.nLinhas;
    nLinhasAlocadas = MF.nLinhasAlocadas;
    nColunas = MF.nColunas;
    nColunasAlocadas = MF.nColunasAlocadas;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c)
{
    if(l < 1 || c < 1) throw BExDimensoesIncorretas(mensagemErro[6]);
    matrizC = new T[l*c];
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = l;
    nColunas = c;
    nColunasAlocadas = c;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c, const T** matriz)
{
    if(l < 1 || c < 1) throw BExDimensoesIncorretas(mensagemErro[6]);
    matrizC = new T[l*c];
    TranspoeLineariza(l,c,matriz);
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = l;
    nColunas = c;
    nColunasAlocadas = c;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c, const T& cnst)
{
    long nElem = l*c;

    if(l < 1 || c < 1) throw BExDimensoesIncorretas(mensagemErro[6]);
    matrizC = new T[nElem];
    for(long i=0; i<nElem; i++) matrizC[i] = cnst;
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = l;
    nColunas = c;
    nColunasAlocadas = c;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c, long la, long ca)
{
    if(la < 1 || ca < 1 || l < 1 || c < 1)
        throw BExDimensoesIncorretas(mensagemErro[6]);
    if(la < l || ca < c) throw BExDimensoesIncorretas(mensagemErro[3]);
    matrizC = new T[la*ca];
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = la;
    nColunas = c;
    nColunasAlocadas = ca;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c, const T** matriz, long la, long ca)
{
    if(la < 1 || ca < 1 || l < 1 || c < 1)
        throw BExDimensoesIncorretas(mensagemErro[6]);
    if(la < l || ca < c) throw BExDimensoesIncorretas(mensagemErro[3]);
    matrizC = new T[la*ca];
    TranspoeLineariza(l,c,matriz,la);
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = la;
    nColunas = c;
    nColunasAlocadas = ca;
}

template<class T>
MatrizFor<T>::MatrizFor(long l, long c, const T& cnst, long la, long ca)
{
    if(la < 1 || ca < 1 || l < 1 || c < 1)
        throw BExDimensoesIncorretas(mensagemErro[6]);
    if(la < l || ca < c) throw BExDimensoesIncorretas(mensagemErro[3]);
    matrizC = new T[la*ca];
    for(long j=0; j<c; j++)
        for(long i=0; i<l; i++) matrizC[la*j+i] = cnst;
    AlocacaoAutomatica = 0;
    nLinhas = l;
    nLinhasAlocadas = la;
    nColunas = c;
    nColunasAlocadas = ca;
}

template<class T>
MatrizFor<T>::~MatrizFor(void)
{
    delete[] matrizC;
}

template<class T>
MatrizFor<T>& MatrizFor<T>::operator=(const MatrizFor<T>& MF)
{
    Redimensiona(MF.nLinhas, MF.nColunas); ///Função Redimensiona faz cópia de matriz!
    for (long j=0; j<nColunas; j++)
        memcpy(matrizC+nLinhasAlocadas*j, MF.matrizC+nLinhasAlocadas*j,
        MF.nLinhas*sizeof(T));
    return *this; 
}

#define OPERADORPARENTESE\
    if((nLinhas!=1) && (nColunas!=1))\
        throw BExMatrizLinhaColuna(mensagemErro[2]);\
    if((ind<0)||((nColunas==1) && (ind>=nLinhas)) ||\
        ((nLinhas==1) && (ind>=nColunas)))\
        BExIndiceForaLimites(mensagemErro[1]);\
    return matrizC[ind];

template<class T>
T& MatrizFor<T>::operator()(long ind)
{
    OPERADORPARENTESE
}

template<class T>
const T& MatrizFor<T>::operator()(long ind) const
{
    OPERADORPARENTESE
}

#undef OPERADORPARENTESE

#define OPERADORPARENTESE\
    if((l<0) || (l>=nLinhas) || (c<0) || (c>=nColunas))\
        throw BExIndiceForaLimites(mensagemErro[1]);\
    return matrizC[nLinhasAlocadas*c+l];

template<class T>
T& MatrizFor<T>::operator()(long l, long c)
{
    OPERADORPARENTESE
}

template<class T>
const T& MatrizFor<T>::operator()(long l, long c) const
{
    OPERADORPARENTESE
}

#undef OPERADORPARENTESE

/*template<class T>
void MatrizFor<T>::AdicionaColunas(long NovasColunas)
{
}

template<class T>
void MatrizFor<T>::AdicionaColunas(long NovasColunas, const T& cnst)
{
}

template<class T>
void MatrizFor<T>::AdicionaLinhas(long NovasLinhas)
{
}

template<class T>
void MatrizFor<T>::AdicionaLinhas(long NovasLinhas, const T& cnst)
{
} */

template<class T>
void MatrizFor<T>::DefAlocacaoAutomatica(bool aa)
{
    AlocacaoAutomatica = aa;
}

template<class T>
bool MatrizFor<T>::LeAlocacaoAutomatica(void) const
{
    return AlocacaoAutomatica;
}

template<class T>
T* MatrizFor<T>::LeEstruturaDados(void) const
{
    return matrizC;
}

template<class T>
long MatrizFor<T>::NumeroLinhas(void) const
{
    return nLinhas;
}

template<class T>
long MatrizFor<T>::NumeroColunas(void) const
{
    return nColunas;
}

template<class T>
void MatrizFor<T>::Redimensiona(long NovasLinhas, long NovasColunas)
{
    T* matriz;

    if((NovasLinhas<1) || (NovasColunas<1))
        throw BExDimensoesIncorretas(mensagemErro[6]);
    if((NovasLinhas>nLinhasAlocadas) || (NovasColunas>nColunasAlocadas))
    {
        if(!AlocacaoAutomatica) throw BExDimensoesIncorretas(mensagemErro[7]);
        matriz = new T[NovasLinhas*NovasColunas];
        if(NovasLinhas<=nLinhas)
            for(long j=0; j<nColunas; j++)
                memcpy(matriz+NovasLinhas*j,matrizC+nLinhasAlocadas*j,
                NovasLinhas*sizeof(T));
        else
            if(NovasColunas<=nColunas)
                for(long j=0; j<NovasColunas; j++)
                    memcpy(matriz+NovasLinhas*j,matrizC+nLinhasAlocadas*j,
                    nLinhas*sizeof(T));
            else
                for(long j=0; j<nColunas; j++)
                    memcpy(matriz+NovasLinhas*j,matrizC+nLinhasAlocadas*j,
                    nLinhas*sizeof(T));
        delete[] matrizC;
        matrizC = matriz;
        nLinhas = nLinhasAlocadas = NovasLinhas;
        nColunas = nColunasAlocadas = NovasColunas;
    }
    else
    {
        nLinhas = NovasLinhas;
        nColunas = NovasColunas;
    }
}

/*template<class T>
void MatrizFor<T>::Redimensiona(long NovasLinhas, long NovasColunas, const T& cnst)
{
} */

template<class T>
void MatrizFor<T>::TranspoeLineariza(long l, long c, const T** matriz)
{
    for(long j=0; j<c; j++)
        for(long i=0; i<l; i++)
            matrizC[j*l+i] = matriz[i][j];
}

template<class T>
void MatrizFor<T>::TranspoeLineariza(long l, long c, const T** matriz, long la)
{
    for(long j=0; j<c; j++)
        for(long i=0; i<l; i++)
            matrizC[j*la+i] = matriz[i][j];
}



//******************************************************************************

template<class T>
class MatrizFor<T>::BExDimensoesIncorretas : public BExcecao
{
    public:
        BExDimensoesIncorretas(void) : BExcecao() {};
        BExDimensoesIncorretas(const BExDimensoesIncorretas& bEx) :
            BExcecao(bEx.Mensagem()) {};
        BExDimensoesIncorretas(const char* pcMens) : BExcecao(pcMens) {};
        virtual ~BExDimensoesIncorretas(void){};
};

template<class T>
class MatrizFor<T>::BExIndiceForaLimites : public BExcecao
{
    public:
        BExIndiceForaLimites(void) : BExcecao() {};
        BExIndiceForaLimites(const BExIndiceForaLimites& bEx) :
            BExcecao(bEx.Mensagem()) {};
        BExIndiceForaLimites(const char* pcMens) : BExcecao(pcMens) {};
        virtual ~BExIndiceForaLimites(void){};
};

template<class T>
class MatrizFor<T>::BExMatrizLinhaColuna : public BExcecao
{
    public:
        BExMatrizLinhaColuna(void) : BExcecao() {};
        BExMatrizLinhaColuna(const BExMatrizLinhaColuna& bEx) :
            BExcecao(bEx.Mensagem()) {};
        BExMatrizLinhaColuna(const char* pcMens) : BExcecao(pcMens) {};
        virtual ~BExMatrizLinhaColuna(void){};
};

#pragma option pop
#endif
