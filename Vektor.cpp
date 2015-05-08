#include "Vektor.h"
    //Vissza adja a vektor elsõ elemét
    double Vektor::getX()const{return x;}
    //Vissza adja a vektor masodik elemét
    double Vektor::getY()const {return y;}
    // Vissza adja a vektor hosszát
    double Vektor::hossz(){return sqrt(x*x+y*y);}
    //Vektor egységvektorrá alakítása
    void Vektor::egysegvektor(){double h; h = this->hossz();if(h != 0){y=y/h;x=x/h;}}
    // Vektor 1 értékének beállítása
    void Vektor::setX(double x){this->x = x;}
    //Vektor 2. értékének beállítása
    void Vektor::setY(double y){this->y = y;}
    //Vektor osszeadás
    Vektor Vektor::operator+(const Vektor& jobb) const{
        Vektor szum(x+jobb.getX(),y+jobb.getY());
        return szum;
    }
    //Vektor szorzása skalárral
    Vektor Vektor::operator*(double lambda)const{
        Vektor szorzat(x*lambda,y*lambda);
        return szorzat;
    }
    //Vektor osztás skalárral
    Vektor Vektor::operator/(double lambda)const{
        Vektor hanyados;
        hanyados = *this * (1/lambda);
        return hanyados;
    }
    //Vektor kivonás
    Vektor Vektor::operator-(const Vektor& jobb) const{
        Vektor szum= *this+(jobb*(-1));
        return szum;
    }
    //Vektor kiírása (globális fg)
    ostream& operator<<(ostream& o,const Vektor& vek)
    {
        o << "x= " << vek.getX() << " y= " << vek.getY();
        return o;
    }
