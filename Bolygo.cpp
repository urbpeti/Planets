#include "Vektor.h"
#include "Bolygo.h"


    //Bolygo hely�vel t�r vissza
    Vektor Bolygo::gethely()const{return hely;}
    //Bolygora hato erovel t�r vissza
    Vektor Bolygo::getero()const{return ero;}
    //Bolgyora sebess�g�vel t�rvissza
    Vektor Bolygo::getseb()const{return sebesseg;}
    //Bolygo tomegevel ter vissza
    void Bolygo::settomeg(double tomeg){this->tomeg = tomeg;}
    //�t�ll�tja a bolygo helyet
    void Bolygo::sethely(double x,double y){hely.setX(x);hely.setY(y);}
    //�t�ll�tja a bolygora hat� er�t
    void Bolygo::setero(double x, double y){ero.setX(x);ero.setY(y);}
    //Bolygo t�meg�vel t�r vissza
    double Bolygo::gettomeg()const {return tomeg;}

    //Glob�lis f�ggv�ny ami ki�rja egy Bolygo adatait
    ostream& operator<<(ostream& o,const Bolygo& B)
    {
        o << B.gethely() << " tomeg= "<< B.gettomeg() << endl;
        return o;
    }
