#include <iostream>
#include <stdexcept>
#include "Vektor.h"
#include "Bolygo.h"
#include "Eter.h"


using namespace std;
    //Hozz� add egy Bolygot a tomb v�g�re
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
    //Kitorli a k-adik boylg�t
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
    //Visszadja h�ny bolygo van a t�mbben
    int Eter::getdb()const{return db;}

    //Vissza adja az i. bolygo-t ha hib�s az index akkor out_of_range-et dob
    Bolygo Eter::getBolygo(int i)const{
        if( i<0 || i>=db) throw out_of_range("Hibas index");
        return *tomb[i];
        }



    //Meghat�rozza minden bolyg�ra az ered� er�t
    void Eter::erok(){
    //Er�ket 0 ra �ll�tja
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i=0; i<db; i++)
        tomb[i]->setero(0,0);
        //Mindegyik bolgy� mindegyik bolygoval kapcsolatban van
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i=0;i<db;i++)
    {
        Vektor irany;
        for(int j=i+1;j<db;j++)
        {
            if(j!=i)
            {
            //Meghat�rrozza az er� ir�ny�t de ez csak az ir�ny �gy csak egys�gvektor k�nt kell nek�nk
            irany = tomb[j]->hely - tomb[i]->hely;
            irany.egysegvektor();
            /*az ir�nyt fel kell szorozni az er� nagys�g�val G gravit�ci�s �lland�t kiemeltem innen �s a v�g�n szoroztam hozz�, mert
            igy csak a k�sz erokhoz szorozza hozz� �gy kevesebb a m�velet
                                            G*(m1*m2)/(r^2)      */
            irany = irany * (/*G **/ tomb[i]->tomeg * tomb[j]->tomeg/(pow((tomb[i]->hely-tomb[j]->hely).hossz(),2)));
            /*Hozz�adjuk a Bolyg�hoz az er�t de �gy ebb�l lesz az ered�
            a m�sik bolyg�hoz meg az ellentett er�t mivel �rv�nyes az er� ellener�*/
            tomb[i]->ero = tomb[i]->ero + irany;
            tomb[j]->ero = tomb[j]->ero - irany;
            }
        }
    }
    for(int i = 0; i< db;i++)
        //Felszorozzuk a G-vel amit kiemeltem az eredeti egyenletb�l
        tomb[i]->ero = tomb[i]->ero*G;
    }







    //Mozgatja a bolyg�kat 1 m�sodperci elmozdul�ssal
    void Eter::lep(){
    //V�gig megy a bolyg�kon �s ha k�zel vannak egym�shoz akkor �sszeolvasztja �ket
    for(int i = 0; i < db; i++)
    {
        for(int j = i+1; j < db; j++)
        {
            if(j!=i)
            {
                //Ha a napunk sugar�n�l k�zelebb megy egym�shoz 2 bolyg� akkor �sszeolvad
                if( (tomb[i]->hely- tomb[j]->hely).hossz() < pow((tomb[j]->tomeg+tomb[i]->tomeg)/(5.9736*pow(10,26)),1.0/3)/nagyitas )
                {
                    //Sebess�g�k az impulzus alapj�n ered� sebess�g
                    tomb[i]->sebesseg = tomb[i]->sebesseg * tomb[i]->tomeg + tomb[j]->sebesseg * tomb[j]->tomeg;
                    //T�meg a 2 Bolygo t�meg�nek �sszege
                    tomb[i]->tomeg = ( tomb[i]->tomeg+ tomb[j]->tomeg);
                    //M�g le kell osztani az �ssz t�meggek.
                    tomb[i]->sebesseg = tomb[i]->sebesseg / tomb[i]->tomeg;
                    //Kitorli a tombben h�tr�bbl�v� bollyg�t
                    torles(j+1);
                }
            }
        }
    }
    //Meghat�rozza minden bolyg�ra az ered� er�t
    this->erok();
    //Minden bolyg�n v�gig megy
    #pragma omp parallel for schedule(dynamic, 8)
    for(int i = 0; i< db; i++)
    {
        // F=m*a, a=v/t,  t=1;  a= v ; F=m*v; v=F/m; + az eredeti sebess�g
        tomb[i]->sebesseg = ((tomb[i]->ero/tomb[i]->tomeg)*60*60*2 + tomb[i]->sebesseg);
        //Az �j hely�re l�p a bolgy�; s=v*t ; t=1; s=v; + a r�gi hely;
        tomb[i]->hely = (tomb[i]->hely + tomb[i]->sebesseg*60*60*2 );
    }
    }

    //Glob�lis f�ggv�ny ami ki�rja az Eterben t�rolt Bolygok adatait
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

