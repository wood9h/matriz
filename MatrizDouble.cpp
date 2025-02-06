//---------------------------------------------------------------------------
#pragma hdrstop
// MatrizDouble
#include "MatrizDouble.h"

#include <iostream>

//using namespace std;

//---------------------------------------------------------------------------
MatrizDouble Transposta( const MatrizDouble& matriz )
{
    MatrizDouble matrizResposta( matriz.NumeroColunas() , matriz.NumeroLinhas() );

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            matrizResposta(j,i) = matriz(i,j);
        }
    }
    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::Transposta( void )
{
    int linhas = (*this).NumeroLinhas();
    int colunas = (*this).NumeroColunas();

    MatrizDouble mTemp( colunas , linhas );

    mTemp = ::Transposta( (*this) );

    (*this).Redimensiona( colunas , linhas );

    for ( int i = 0 ; i < mTemp.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < mTemp.NumeroColunas() ; j++ )
        {
            ( *this )(i,j) = mTemp(i,j);
        }
    }

    return ( *this );
}
//---------------------------------------------------------------------------
MatrizDouble MatrizDouble::operator + ( const MatrizDouble& matriz )
{
    MatrizDouble matrizResposta( matriz.NumeroLinhas() , matriz.NumeroColunas() );

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            matrizResposta(i,j) = (*this)(i,j) + matriz(i,j);
        }
    }

    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble MatrizDouble::operator - ( const MatrizDouble& matriz )
{
    MatrizDouble matrizResposta( matriz.NumeroLinhas() , matriz.NumeroColunas() );

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            matrizResposta(i,j) = (*this)(i,j) - matriz(i,j);
        }
    }

    return ( matrizResposta );                                                                 
}
//---------------------------------------------------------------------------
MatrizDouble operator * ( const MatrizDouble& matriz , double value )
{
    MatrizDouble matrizResposta( matriz.NumeroLinhas() , matriz.NumeroColunas() );

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            matrizResposta(i,j) =  value * matriz(i,j);
        }
    }
    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble operator * ( double value , const MatrizDouble& matriz )
{
    MatrizDouble matrizResposta( matriz.NumeroLinhas() , matriz.NumeroColunas() );

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            matrizResposta(i,j) =  value * matriz(i,j);
        }
    }
    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble MatrizDouble::operator * ( const MatrizDouble& matriz )
{
    // verifica impossibilidade de multiplicação
    if ( (*this).NumeroColunas() != matriz.NumeroLinhas() ) throw BExDimensoesIncorretas( "Dimensões incorretas." );

    MatrizDouble matrizResposta( (*this).NumeroLinhas() , matriz.NumeroColunas() , 0.0 );

    for ( int i = 0 ; i < (*this).NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            for ( int a = 0 ; a < (*this).NumeroColunas() ; a++ )
            {
                matrizResposta(i,j) +=  (*this)(i,a) * matriz(a,j);
            }
        }
    }
    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator += ( const MatrizDouble& matriz )
{
    (*this) = (*this) + matriz;
    return ( *this );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator -= ( const MatrizDouble& matriz )
{
    (*this) = (*this) - matriz;
    return ( *this );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator *= ( const MatrizDouble& matriz )
{
    (*this) = (*this) * matriz;
    return ( *this );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator *= ( double value )
{
    (*this) =  value * (*this);
    return ( *this );
}
//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator = ( double value )
{
    for ( int i = 0 ; i < NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < NumeroColunas() ; j++ )
        {
            (*this)(i,j) = value;
        }
    }
    return ( *this );
}

//---------------------------------------------------------------------------
MatrizDouble& MatrizDouble::operator = ( const MatrizDouble& matriz )
{
   
    for ( int i = 0 ; i < NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < NumeroColunas() ; j++ )
        {
            (*this)(i,j) = (*matriz)(i,j);
		}
    }
   
    return ( *matriz );
}

//---------------------------------------------------------------------------
bool MatrizDouble::operator == ( const MatrizDouble& matriz )
{
    bool bTemporario = true;

    for ( int i = 0 ; i < matriz.NumeroLinhas() ; i++ )
    {
        for ( int j = 0 ; j < matriz.NumeroColunas() ; j++ )
        {
            if (  (*this)(i,j) != matriz(i,j) )
            {
                bTemporario = false;
            }
        }
    }

    return ( bTemporario );
}
//---------------------------------------------------------------------------


std::istream & operator >> ( std::istream & is , MatrizDouble& M )
{
    int m;
    int n;

    is >> m >> n;
    
    M.Redimensiona( m,n );
    
    for ( int i = 0 ; i < m ; i++ )
    {
        for ( int j = 0 ; j < n ; j++ )
        {
            is >> M(i,j);
        }
    }

    return ( is );

}

//---------------------------------------------------------------------------
std::ostream & operator << ( std::ostream & os , const MatrizDouble& M )
{
    int m = M.NumeroLinhas();
    int n = M.NumeroColunas();

    os << m << '\t' << n << std::endl;

    for( int i = 0 ; i < m ; i++ )
    {
        for( int j = 0 ; j < n ; j++ )
        {
            os << M(i,j) << '\t' ;
        }
        os << std::endl;
    }

    return( os );

}

//---------------------------------------------------------------------------
MatrizDouble Stack( const MatrizDouble& matriz1 , const MatrizDouble& matriz2 )
{
    // verifica impossibilidade de multiplicação
//    if ( matriz1.NumeroColunas() != matriz2.NumeroColunas() ) throw BExDimensoesIncorretas( "Dimensões incorretas." );

    MatrizDouble matrizResposta( matriz1.NumeroLinhas() + matriz2.NumeroLinhas() , matriz1.NumeroColunas() );

    for( int i = 0 ; i < matriz1.NumeroColunas() ; i++ )
    {
        for( int j = 0 ; j < matriz1.NumeroLinhas() ; j++ )
        {
            matrizResposta(j,i) = matriz1(j,i);
        }
        for( int j = 0 ; j < matriz2.NumeroLinhas() ; j++ )
        {
            matrizResposta( (matriz1.NumeroLinhas()+j) , i ) = matriz2(j,i);
        }
    }

    return ( matrizResposta );
}
//---------------------------------------------------------------------------
MatrizDouble Augment( const MatrizDouble& matriz1 , const MatrizDouble& matriz2 )
{
    // verifica impossibilidade de multiplicação
//    if ( matriz1.NumeroLinhas() != matriz2.NumeroLinhas() ) throw BExDimensoesIncorretas( "Dimensões incorretas." );

    MatrizDouble matrizResposta( matriz1.NumeroLinhas() , matriz1.NumeroColunas() + matriz2.NumeroColunas() );

    for( int i = 0 ; i < matriz1.NumeroLinhas() ; i++ )
    {
        for( int j = 0 ; j < matriz1.NumeroColunas() ; j++ )
        {
            matrizResposta(i,j) = matriz1(i,j);
        }
        for( int j = 0 ; j < matriz2.NumeroColunas() ; j++ )
        {
            matrizResposta( i , (matriz1.NumeroColunas()+j) ) = matriz2(i,j);
        }
    }
    return ( matrizResposta );
}
//---------------------------------------------------------------------------

