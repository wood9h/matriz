//---------------------------------------------------------------------------

#pragma hdrstop
//#include"MatrizFor.h"
#include<fstream.h>
//#include<complex.h>
#include "MatrizDouble.h"
//---------------------------------------------------------------------------
//using namespace std;
//typedef MatrizFor<float> Matriz;
//typedef complex<float> Complex;
//typedef MatrizFor<double> Matriz;
  typedef MatrizDouble Matriz;
//Existe a necessidade de haver uma classe base para as matrizes?
//Exemplo: a função Carrega, abaixo, deveria funcionar para qualquer tipo de matriz.
/*
template<class T>
void Carrega(fstream& Arq, MatrizFor<T>& M)
{
    int m;
    int n;

    Arq >> m >> n;
    M.Redimensiona(m,n);
    for ( int i = 0 ; i < m ; i++ )
    {
        for ( int j = 0 ; j < n ; j++ )
        {
            Arq >> M(i,j);
        }
    }

}

void Imprime( const Matriz& M )
{
    int m = M.NumeroLinhas();
    int n = M.NumeroColunas();

    cout << endl;

    for( int i = 0 ; i < m ; i++ )
    {
        cout << endl;
        for( int j = 0 ; j < n ; j++ )
        {
            cout << ' ' << M(i,j);
        }
    }
}
*/
#pragma argsused
int main( int argc , char* argv[] )
{
    try
    {
        fstream Arq;
        Matriz A( 8 , 8 , 10 , 10 );
        for ( int i = 0 ; i < 8 ; i++ )
        {
            for ( int j = 0 ; j < 8 ; j++ )
            {
                A(i,j) = 0;
            }
        }

        Arq.open ( "Dados2.txt" , ios::out );
        Arq << A;
        Matriz B( 2 , 2 , 10 , 10 );

        B(0,0) = 1;
        B(1,0) = 2;
        B(0,1) = 3;
        B(1,1) = 4;

        //Arq >> B;

//        cout << " A - 2 A " << endl << (A - 2 * A) << endl;
//        cout << "A:" << endl << A << endl << "B:" << endl << B << endl <<"(A*B):" << endl << (A*B) << endl;//<< endl <<"(A*B)T:" << endl << Transposta( (A*B) ) << endl ;

//        cout << " Stack A,Transposta(B)"  << endl << Stack(A,Transposta(B)) << endl;
//        cout << " Augment A,B "<< endl << Augment(A,B) << endl;


        Matriz C( 1 , 1 , 10 , 10 );
      //  C = A*B;

//        cout << "A" << endl << A << endl;
//        cout << "B" << endl << B << endl;
        cout << B << endl;
        cout << Transposta(B) << endl;

//        cout << C.Transposta()<< endl;
//        cout << C << endl;

/*
        cout << (A*B) << endl;

        cout << " C T " << endl<< C.Transposta();

        cout << C << endl;
*/
        Arq.close();

        return ( 0 );
    }

    catch( const BExcecao& e )
    {
        cout << e.Mensagem();
    }

    return ( 1 );
}

