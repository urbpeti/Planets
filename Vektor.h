#ifndef vektorr
#define vektorr
#include <iostream>
#include "math.h"

using namespace std;

class Vektor {
    //Vektor végét mutató koordináták
    double x,y;
public:
    //konstruktor
    Vektor(double x=0,double y=0):x(x),y(y){}
    //Vissza adja a vektor elsõ elemét
    double getX()const;
    //Vissza adja a vektor masodik elemét
    double getY()const;
    // Vissza adja a vektor hosszát
    double hossz();
    //Vektor egységvektorrá alakítása
    void egysegvektor();
    // Vektor 1 értékének beállítása
    void setX(double);
    //Vektor 2. értékének beállítása
    void setY(double);
    //Vektor osszeadás
    Vektor operator+(const Vektor& jobb) const;
    //Vektor szorzása skalárral
    Vektor operator*(double lambda)const;
    //Vektor osztás skalárral
    Vektor operator/(double lambda)const;
    //Vektor kivonás
    Vektor operator-(const Vektor& jobb) const;
};
    //Vektor kiírása (globális fg)
    ostream& operator<<(ostream& o,const Vektor& vek);
#endif //vektorr
