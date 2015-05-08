#ifndef Eterr
#define Eterr
#include "Vektor.h"
#include "Bolygo.h"


const double nagyitas = (pow(10,-10)*6*3);

class Eter{
    //Bolygo tombot tarolok ami
    Bolygo **tomb;
    //Tömbben lévõ elemszám
    int db;
    //Gravitációs állandó
    const double G=6.67428*pow(10,-11);
public:
    Eter(){db=0;tomb = new Bolygo*[0];}
    //Hozzá add egy Bolygot a tomb végére
    void addBolygo(Bolygo* b);
    //Kitorli a k-adik boylgót
    void torles(int k);
    //Visszadja hány bolygo van a tömbben
    int getdb()const;
    //Vissza adja az i. bolygo-t
    Bolygo getBolygo(int i)const;
    //Meghatározza minden bolygora a rá ható erõt
    void erok();
    //Lepteti a bolygokat
    void lep();

    double gyorsulas1bolygora(int b);
    //Destruktor
    ~Eter();
};

//Globális függvény ami kiírja egy Bolygo adatait
ostream& operator<<(ostream& o,Eter& ur);

#endif //Eterr
