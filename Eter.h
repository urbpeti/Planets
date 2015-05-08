#ifndef Eterr
#define Eterr
#include "Vektor.h"
#include "Bolygo.h"


const double nagyitas = (pow(10,-10)*6*3);

class Eter{
    //Bolygo tombot tarolok ami
    Bolygo **tomb;
    //T�mbben l�v� elemsz�m
    int db;
    //Gravit�ci�s �lland�
    const double G=6.67428*pow(10,-11);
public:
    Eter(){db=0;tomb = new Bolygo*[0];}
    //Hozz� add egy Bolygot a tomb v�g�re
    void addBolygo(Bolygo* b);
    //Kitorli a k-adik boylg�t
    void torles(int k);
    //Visszadja h�ny bolygo van a t�mbben
    int getdb()const;
    //Vissza adja az i. bolygo-t
    Bolygo getBolygo(int i)const;
    //Meghat�rozza minden bolygora a r� hat� er�t
    void erok();
    //Lepteti a bolygokat
    void lep();

    double gyorsulas1bolygora(int b);
    //Destruktor
    ~Eter();
};

//Glob�lis f�ggv�ny ami ki�rja egy Bolygo adatait
ostream& operator<<(ostream& o,Eter& ur);

#endif //Eterr
