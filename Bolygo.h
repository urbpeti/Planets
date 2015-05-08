#ifndef Bolygoh
#define Bolygoh
#include "Vektor.h"


class Bolygo {
    //Hogy ez Eter osztály tudja használni a változóit mivel õ kezeli a Bolygókat
    friend class Eter;
    //Bolygo tömege
    double tomeg;
    //Bolygo helye
    Vektor hely;
    //Bolygo pillanatnyi sebessége
    Vektor sebesseg;
    //Bolygora hato ero
    Vektor ero;
public:
    //Konstruktor
    Bolygo(double x = 0, double y = 0, double tomeg = 1,double vx =0,double vy=0):hely(x,y),tomeg(tomeg),sebesseg(vx,vy),ero(0,0){}
    //Bolygo helyével tér vissza
    Vektor gethely()const;
    //Bolygora hato erovel tér vissza
    Vektor getero()const;
    //Bolgyora sebességével térvissza
    Vektor getseb()const;
    //Bolygo tomegevel ter vissza
    void settomeg(double tomeg);
    //Átállítja a bolygo helyet
    void sethely(double x,double y);
    //Átállítja a bolygora ható erõt
    void setero(double x, double y);
    //Bolygo tömegével tér vissza
    double gettomeg()const;
};

    //Globális függvény ami kiírja egy Bolygo adatait
    ostream& operator<<(ostream& o,const Bolygo& B);
#endif  // Bolygoh
