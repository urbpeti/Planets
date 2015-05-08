#include "Vektor.h"
#include "Bolygo.h"


    //Bolygo helyével tér vissza
    Vektor Bolygo::gethely()const{return hely;}
    //Bolygora hato erovel tér vissza
    Vektor Bolygo::getero()const{return ero;}
    //Bolgyora sebességével térvissza
    Vektor Bolygo::getseb()const{return sebesseg;}
    //Bolygo tomegevel ter vissza
    void Bolygo::settomeg(double tomeg){this->tomeg = tomeg;}
    //Átállítja a bolygo helyet
    void Bolygo::sethely(double x,double y){hely.setX(x);hely.setY(y);}
    //Átállítja a bolygora ható erõt
    void Bolygo::setero(double x, double y){ero.setX(x);ero.setY(y);}
    //Bolygo tömegével tér vissza
    double Bolygo::gettomeg()const {return tomeg;}

    //Globális függvény ami kiírja egy Bolygo adatait
    ostream& operator<<(ostream& o,const Bolygo& B)
    {
        o << B.gethely() << " tomeg= "<< B.gettomeg() << endl;
        return o;
    }
