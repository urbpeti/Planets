#include <iostream>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Eter.h"

using namespace std;


Uint32 idozit2(Uint32 ms, void *param)
{
    SDL_Event event;
    event.type = SDL_USEREVENT;
    SDL_PushEvent(&event);
    return ms;
}

double G=6.67428*pow(10,-11);
double randomszam1;
double randomszam2;

int szel = 800, magas = 600;


double xkoord(double x)
{
    return x*nagyitas+szel/2;
}

double ykoord(double y)
{
    return magas/2 - y*nagyitas;
}

double visszaykoord(double y)
{
    return (magas/2-y)/nagyitas;
}

double visszaxkoord(double x)
{
    return (x-szel/2)/nagyitas;
}

int main(int argc, char *argv[]) {
    SDL_Event ev;
    SDL_Surface *screen;
    SDL_TimerID timer;
    srand(time(NULL));

    Eter ur;

      /*ur.addBolygo(new Bolygo(0,0,1.9891*pow(10,30),0,0));  //nap
      ur.addBolygo(new Bolygo(1.5*pow(10,11),0,5.9736*pow(10,24),0,-2.9783*pow(10,4)));  //föld
      ur.addBolygo(new Bolygo(1.5*pow(10,11)*0.72,0,5.9736*pow(10,24)*0.82,0,-3.502*pow(10,4)));  // venusz
      ur.addBolygo(new Bolygo(1.5*pow(10,11)*0.39,0,5.9736*pow(10,24)*0.055,0,-4.787*pow(10,4)));  //merkur
      ur.addBolygo(new Bolygo(1.5*pow(10,11)*1.52,0,5.9736*pow(10,24)*0.11,0,-2.413*pow(10,4)));  // mars
      ur.addBolygo(new Bolygo(1.5*pow(10,11)*1.8,0,5.9736*pow(10,26),0,2.217422348*pow(10,4))); //Péter
      ur.addBolygo(new Bolygo(1.5*pow(10,11)*1.0024,0,7.347673*pow(10,22),0,10.82*pow(10,2)-2.9783*pow(10,4)));  // hold*/


        ur.addBolygo(new Bolygo(1.5*pow(10,11)*0.1,0,1.9891*pow(10,30),0,-9.4077399*pow(10,4)/2));  //uj
        ur.addBolygo(new Bolygo(0,0,1.9891*pow(10,30),0,9.4077399*pow(10,4)/2));
        ur.addBolygo(new Bolygo(1.5*pow(10,11),0,5.9736*pow(10,28),0,-2.9783*pow(10,4))); //1050.227383238650646020813433211
        ur.addBolygo(new Bolygo(1.5*pow(10,11)+3.844*pow(10,9),0,pow(10,27)*5,0,-3.2195*pow(10,4)-2.9783*pow(10,4)));
        ur.addBolygo(new Bolygo(0,0,5.9736*pow(10,24),0,0));  //föld2
        ur.addBolygo(new Bolygo(1.5*pow(10,11)*0.0024,0,7.347673*pow(10,22),0,10.82*pow(10,2)));  // hold2
    srand(time(NULL));
    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    screen=SDL_SetVideoMode(szel, magas, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("Bolygok", "Bolygok");

    timer = SDL_AddTimer(1, idozit2, 0);

    int torol = 1;
    int erok=0;
    int engedely = 1;
    int szamol = 0;
    double gyorsulas;
    /* varunk a kilepesre */
    while (SDL_WaitEvent(&ev) && ev.type!=SDL_QUIT) {
        if(ev.type == SDL_USEREVENT && engedely)
        {
        ur.lep();
            #pragma omp parallel for schedule(dynamic, 8)
            for(int i= 0; i < ur.getdb();i++){
            filledCircleColor(screen,xkoord(ur.getBolygo(i).gethely().getX()),ykoord(ur.getBolygo(i).gethely().getY()),pow(((double)ur.getBolygo(i).gettomeg())/(5.9736*pow(10,26)),1.0/3),0xFFFFFFFF );
            if(erok)
            lineColor(screen  ,  xkoord(ur.getBolygo(i).gethely().getX()) ,  ykoord(ur.getBolygo(i).gethely().getY())  ,xkoord(ur.getBolygo(i).gethely().getX()) + ur.getBolygo(i).getero().getX()*5000/ur.getBolygo(i).gettomeg()  ,ykoord(ur.getBolygo(i).gethely().getY())-ur.getBolygo(i).getero().getY()*5000/ur.getBolygo(i).gettomeg()  ,  0xFF0000FF );
            }
        SDL_Flip(screen);
            /*for(int i= 0; i < ur.getdb();i++){
            filledCircleColor(screen,xkoord(ur.getBolygo(i).gethely().getX()),ykoord(ur.getBolygo(i).gethely().getY()),pow(((double)ur.getBolygo(i).gettomeg())/(5.9736*pow(10,26)),1.0/3),0x000000FF );
            }*/
            if(torol)
                boxColor(screen,0,0,szel,magas,0x000000FF);


        }
        if(ev.type == SDL_MOUSEBUTTONDOWN)
        {
        //     ur.addBolygo(new Bolygo(1.5*pow(10,11),0,5.9736*pow(10,24),0,2.9783*pow(10,4)));
            if(ev.button.button == SDL_BUTTON_LEFT)
            {
               //ur.addBolygo(new Bolygo(visszaxkoord(ev.motion.x) ,visszaykoord(ev.motion.y),5.9736*pow(10,27),sqrt(2)*2.9783*pow(10,4)*randomszam1,sqrt(2)*2.9783*pow(10,4)*randomszam2));
               //ur.addBolygo(new Bolygo(visszaxkoord(ev.motion.x) ,visszaykoord(ev.motion.y),5.9736*pow(10,28)));
               #pragma omp parallel for schedule(dynamic, 8)
               for(int i=0; i<100;i++)
               {
                randomszam1 = (rand()%100-49)/100.0;
                randomszam2 = (rand()%100-49)/100.0;
               ur.addBolygo(new Bolygo(visszaxkoord(rand() % szel) ,visszaykoord(rand()%magas),5.9736*pow(10,27),sqrt(2)*2.9783*pow(10,4)*randomszam1,sqrt(2)*2.9783*pow(10,4)*randomszam2));
               }
            }
            else if(ev.button.button == SDL_BUTTON_RIGHT )
               ur.torles(1);
        }
        if (ev.type == SDL_KEYDOWN)
            if(ev.key.keysym.sym == SDLK_t)
                if(torol)
                    torol = 0;
                else
                    torol = 1;
            else if(ev.key.keysym.sym == SDLK_e)
                if(erok)
                    erok = 0;
                else
                    erok = 1;
            else if(ev.key.keysym.sym == SDLK_SPACE)
                if(engedely)
                {
                    engedely = 0;
                    szamol = 1;
                }
                else
                    engedely = 1;
        if(engedely == 0 && szamol == 1 )
        {
            for(int i=0;i < szel;i++)
                for(int j=0; j< magas;j++)
            {
                ur.addBolygo(new Bolygo(visszaxkoord(i),visszaykoord(j),1,0,0));
                gyorsulas = ur.gyorsulas1bolygora(ur.getdb()-1);
                pixelRGBA(screen,i,j,sqrt(gyorsulas/(gyorsulas+0.25))*255,0,0,255);
                ur.torles(ur.getdb());
            }
            SDL_Flip(screen);
            szamol = 0;
        }
    }
    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}

