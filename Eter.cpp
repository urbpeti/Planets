#include <iostream>
#include <stdexcept>
#include "Vektor.h"
#include "Bolygo.h"
#include "Eter.h"


using namespace std;
    //Hozzá add egy Bolygot a tomb végére
    void Eter::addBolygo(Bolygo* b){
        db++;
        Bolygo **temp;
        temp = new Bolygo*[db-1];
        for(int i=0;i<db-1;i++)
            temp[i] = tomb[i];
        delete[] tomb;
        tomb = new Bolygo*[db];
        for(int i=0;i<db-1;i++)
            tomb[i] = temp[i];
        tomb[db-1] = b;
        delete[] temp;
    }
    //Kitorli a k-adik boylgót
    void Eter::torles(int k)
    {
        if(db != 0 && k <= db)
        {
        delete tomb[k-1];
        for(int i=k-1;i<db-1;i++)
        {
            tomb[i] = tomb[i+1];
        }
        tomb[db-1] = NULL;
        db--;
        }
    }
    //Visszadja hány bolygo van a tömbben
    int Eter::getdb()const{return db;}

    //Vissza adja az i. bolygo-t ha hibás az index akkor out_of_range-et dob
    Bolygo Eter::getBolygo(int i)const{
        if( i<0 || i>=db) throw out_of_range("Hibas index");
        return *tomb[i];
        }



    //Meghatározza minden bolygóra az eredõ erõt
    void Eter::erok(){
    //Erõket 0 ra állítja
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i=0; i<db; i++)
        tomb[i]->setero(0,0);
        //Mindegyik bolgyó mindegyik bolygoval kapcsolatban van
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i=0;i<db;i++)
    {
        Vektor irany;
        for(int j=i+1;j<db;j++)
        {
            if(j!=i)
            {
            //Meghatárrozza az erõ irányát de ez csak az irány így csak egységvektor ként kell nekünk
            irany = tomb[j]->hely - tomb[i]->hely;
            irany.egysegvektor();
            /*az irányt fel kell szorozni az erõ nagyságával G gravitációs állandót kiemeltem innen és a végén szoroztam hozzá, mert
            igy csak a kész erokhoz szorozza hozzá így kevesebb a mûvelet
                                            G*(m1*m2)/(r^2)      */
            irany = irany * (/*G **/ tomb[i]->tomeg * tomb[j]->tomeg/(pow((tomb[i]->hely-tomb[j]->hely).hossz(),2)));
            /*Hozzáadjuk a Bolygóhoz az erõt de így ebbõl lesz az eredõ
            a másik bolygóhoz meg az ellentett erõt mivel érvényes az erõ ellenerõ*/
            tomb[i]->ero = tomb[i]->ero + irany;
            tomb[j]->ero = tomb[j]->ero - irany;
            }
        }
    }
    for(int i = 0; i< db;i++)
        //Felszorozzuk a G-vel amit kiemeltem az eredeti egyenletbõl
        tomb[i]->ero = tomb[i]->ero*G;
    }







    //Mozgatja a bolygókat 1 másodperci elmozdulással
    void Eter::lep(){
    //Végig megy a bolygókon és ha közel vannak egymáshoz akkor összeolvasztja õket
    for(int i = 0; i < db; i++)
    {
        for(int j = i+1; j < db; j++)
        {
            if(j!=i)
            {
                //Ha a napunk sugaránál közelebb megy egymáshoz 2 bolygó akkor összeolvad
                if( (tomb[i]->hely- tomb[j]->hely).hossz() < pow((tomb[j]->tomeg+tomb[i]->tomeg)/(5.9736*pow(10,26)),1.0/3)/nagyitas )
                {
                    //Sebességük az impulzus alapján eredõ sebesség
                    tomb[i]->sebesseg = tomb[i]->sebesseg * tomb[i]->tomeg + tomb[j]->sebesseg * tomb[j]->tomeg;
                    //Tömeg a 2 Bolygo tömegének összege
                    tomb[i]->tomeg = ( tomb[i]->tomeg+ tomb[j]->tomeg);
                    //Még le kell osztani az össz tömeggek.
                    tomb[i]->sebesseg = tomb[i]->sebesseg / tomb[i]->tomeg;
                    //Kitorli a tombben hátrébblévõ bollygót
                    torles(j+1);
                }
            }
        }
    }
    //Meghatározza minden bolygóra az eredõ erõt
    this->erok();
    //Minden bolygón végig megy
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i = 0; i< db; i++)
    {
        // F=m*a, a=v/t,  t=1;  a= v ; F=m*v; v=F/m; + az eredeti sebesség
        tomb[i]->sebesseg = ((tomb[i]->ero/tomb[i]->tomeg)*60*60*2 + tomb[i]->sebesseg);
        //Az új helyére lép a bolgyó; s=v*t ; t=1; s=v; + a régi hely;
        tomb[i]->hely = (tomb[i]->hely + tomb[i]->sebesseg*60*60*2 );
    }
    }

    //Globális függvény ami kiírja az Eterben tárolt Bolygok adatait
    ostream& operator<<(ostream& o,Eter& ur)
    {
        if(ur.getdb() == 0)
        {
            cout << "Nincsen Bolygo az Eterben";
        }
        else
        {
        for(int i = 0;i<ur.getdb();i++)
           cout << i+1 << ". " << ur.getBolygo(i);
        }
        return o;
    }



    double Eter::gyorsulas1bolygora(int b)
    {
        Vektor irany;
        tomb[b]->setero(0,0);
        for(int i=0;i<db;i++)
        {
            Vektor hely;
            hely = (tomb[b]->hely - tomb[i]->hely);
            if( i != b /*&& hely.hossz() > pow(tomb[i]->gettomeg()/(5.9736*pow(10,26)),1.0/3)/nagyitas*/)
                {
                irany = tomb[i]->hely - tomb[b]->hely;
                irany.egysegvektor();
                irany = irany * (G * tomb[i]->gettomeg()/(pow(hely.hossz(),2)));
                tomb[b]->ero = tomb[b]->ero+irany;
                }
        }
        return tomb[b]->ero.hossz();
    }



    //Destruktor
    Eter::~Eter(){
        int vegig = db;
        for(int i=0;i<vegig;i++)
            torles(1);
        db=0;
        delete[] tomb;
    }

