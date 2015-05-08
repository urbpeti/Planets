#include "Vektor.h"
    //Vissza adja a vektor els� elem�t
    double Vektor::getX()const{return x;}
    //Vissza adja a vektor masodik elem�t
    double Vektor::getY()const {return y;}
    // Vissza adja a vektor hossz�t
    double Vektor::hossz(){return sqrt(x*x+y*y);}
    //Vektor egys�gvektorr� alak�t�sa
    void Vektor::egysegvektor(){double h; h = this->hossz();if(h != 0){y=y/h;x=x/h;}}
    // Vektor 1 �rt�k�nek be�ll�t�sa
    void Vektor::setX(double x){this->x = x;}
    //Vektor 2. �rt�k�nek be�ll�t�sa
    void Vektor::setY(double y){this->y = y;}
    //Vektor osszead�s
    Vektor Vektor::operator+(const Vektor& jobb) const{
        Vektor szum(x+jobb.getX(),y+jobb.getY());
        return szum;
    }
    //Vektor szorz�sa skal�rral
    Vektor Vektor::operator*(double lambda)const{
        Vektor szorzat(x*lambda,y*lambda);
        return szorzat;
    }
    //Vektor oszt�s skal�rral
    Vektor Vektor::operator/(double lambda)const{
        Vektor hanyados;
        hanyados = *this * (1/lambda);
        return hanyados;
    }
    //Vektor kivon�s
    Vektor Vektor::operator-(const Vektor& jobb) const{
        Vektor szum= *this+(jobb*(-1));
        return szum;
    }
    //Vektor ki�r�sa (glob�lis fg)
    ostream& operator<<(ostream& o,const Vektor& vek)
    {
        o << "x= " << vek.getX() << " y= " << vek.getY();
        return o;
    }
