#ifndef vektorr
#define vektorr
#include <iostream>
#include "math.h"

using namespace std;

class Vektor {
    //Vektor v�g�t mutat� koordin�t�k
    double x,y;
public:
    //konstruktor
    Vektor(double x=0,double y=0):x(x),y(y){}
    //Vissza adja a vektor els� elem�t
    double getX()const;
    //Vissza adja a vektor masodik elem�t
    double getY()const;
    // Vissza adja a vektor hossz�t
    double hossz();
    //Vektor egys�gvektorr� alak�t�sa
    void egysegvektor();
    // Vektor 1 �rt�k�nek be�ll�t�sa
    void setX(double);
    //Vektor 2. �rt�k�nek be�ll�t�sa
    void setY(double);
    //Vektor osszead�s
    Vektor operator+(const Vektor& jobb) const;
    //Vektor szorz�sa skal�rral
    Vektor operator*(double lambda)const;
    //Vektor oszt�s skal�rral
    Vektor operator/(double lambda)const;
    //Vektor kivon�s
    Vektor operator-(const Vektor& jobb) const;
};
    //Vektor ki�r�sa (glob�lis fg)
    ostream& operator<<(ostream& o,const Vektor& vek);
#endif //vektorr
