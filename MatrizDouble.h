//---------------------------------------------------------------------------
#ifndef MatrizDoubleH
#define MatrizDoubleH
#include <iostream>
#include "MatrizFor.h"

using namespace std;
//---------------------------------------------------------------------------
class MatrizDouble : public MatrizFor <double>
{
private:

protected:

public:
    MatrizDouble( void ) : MatrizFor<double>() {};
    MatrizDouble( const MatrizDouble& matriz ) : MatrizFor<double>( matriz ) {};
    MatrizDouble( long l , long c ) : MatrizFor<double>( l, c ) {};
    MatrizDouble( long l , long c , const double** matriz ) : MatrizFor<double>( l, c , matriz ) {};
    MatrizDouble( long l , long c , const double& cnst ) : MatrizFor<double>( l, c , cnst) {};
    MatrizDouble( long l , long c , long la, long ca ) : MatrizFor<double>( l, c , la , ca) {};
    MatrizDouble( long l , long c , const double** matriz , long la , long ca ) : MatrizFor<double>( l, c , matriz , la , ca){};
    MatrizDouble( long l , long c , const double& cnst , long la , long ca ) : MatrizFor<double>( l, c , cnst , la , ca ){};
    virtual ~MatrizDouble( void ) {};

    MatrizDouble& Transposta( void );
    friend MatrizDouble Transposta( const MatrizDouble& matriz );
    MatrizDouble operator + ( const MatrizDouble& matriz );
    MatrizDouble operator - ( const MatrizDouble& matriz );
    friend MatrizDouble operator * ( const MatrizDouble& matriz , double value );
    friend MatrizDouble operator * ( double value , const MatrizDouble& matriz );
    MatrizDouble operator * ( const MatrizDouble& matriz );
    MatrizDouble& operator += ( const MatrizDouble& matriz );
    MatrizDouble& operator -= ( const MatrizDouble& matriz );
    MatrizDouble& operator *= ( const MatrizDouble& matriz );
    MatrizDouble& operator *= ( double value );
    MatrizDouble& operator = ( double value );
    MatrizDouble& operator = ( const MatrizDouble& matriz );
    
	//bool operator != ( const MatrizDouble& matriz );
    bool operator == ( const MatrizDouble& matriz );

    friend istream& operator >> ( istream& is , MatrizDouble& M );
    friend ostream& operator << ( ostream& os , const MatrizDouble& M );

    friend MatrizDouble Stack( const MatrizDouble& matriz1 , const MatrizDouble& matriz2 );
    friend MatrizDouble Augment( const MatrizDouble& matriz1 , const MatrizDouble& matriz2 );

};
//---------------------------------------------------------------------------
#endif
