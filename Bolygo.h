#ifndef Bolygoh
#define Bolygoh
#include "Vektor.h"


class Bolygo {
    //Hogy ez Eter oszt�ly tudja haszn�lni a v�ltoz�it mivel � kezeli a Bolyg�kat
    friend class Eter;
    //Bolygo t�mege
    double tomeg;
    //Bolygo helye
    Vektor hely;
    //Bolygo pillanatnyi sebess�ge
    Vektor sebesseg;
    //Bolygora hato ero
    Vektor ero;
public:
    //Konstruktor
    Bolygo(double x = 0, double y = 0, double tomeg = 1,double vx =0,double vy=0):hely(x,y),tomeg(tomeg),sebesseg(vx,vy),ero(0,0){}
    //Bolygo hely�vel t�r vissza
    Vektor gethely()const;
    //Bolygora hato erovel t�r vissza
    Vektor getero()const;
    //Bolgyora sebess�g�vel t�rvissza
    Vektor getseb()const;
    //Bolygo tomegevel ter vissza
    void settomeg(double tomeg);
    //�t�ll�tja a bolygo helyet
    void sethely(double x,double y);
    //�t�ll�tja a bolygora hat� er�t
    void setero(double x, double y);
    //Bolygo t�meg�vel t�r vissza
    double gettomeg()const;
};

    //Glob�lis f�ggv�ny ami ki�rja egy Bolygo adatait
    ostream& operator<<(ostream& o,const Bolygo& B);
#endif  // Bolygoh
