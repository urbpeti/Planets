/*
 * InfoC SDL project
 * SDL peldaprogram
 * http://infoc.eet.bme.hu/
 */
#include <iostream>
#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <math.h>

class valami {
    int i;
    int g;
public:
    int getI(){return i;};
};

int main(int argc, char *argv[]) {
    SDL_Event ev;
    SDL_Surface *screen;
    int x, y, r;

    /* SDL inicializálása és ablak megnyitása */
    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode(440, 360, 0, SDL_ANYFORMAT);
    if (!screen) {
        fprintf(stderr, "Nem sikerult megnyitni az ablakot!\n");
        exit(1);
    }
    SDL_WM_SetCaption("SDL peldaprogram", "SDL peldaprogram");

    r=50;

    /* karika */
    x=100; y=100;
    circleRGBA(screen, x, y, r,                                 255, 0, 0, 255);
    circleRGBA(screen, x+r, y, r,                               0, 255, 0, 255);
    circleRGBA(screen, x+r*cos(3.1415/3), y-r*sin(3.1415/3), r, 0, 0, 255, 255);

    /* antialias karika */
    x=280; y=100;
    aacircleRGBA(screen, x, y, r,                                 255, 0, 0, 255);
    aacircleRGBA(screen, x+r, y, r,                               0, 255, 0, 255);
    aacircleRGBA(screen, x+r*cos(3.1415/3), y-r*sin(3.1415/3), r, 0, 0, 255, 255);

    /* kitoltott kor */
    x=100; y=280;
    filledCircleRGBA(screen, x, y, r,                                 255, 0, 0, 255);
    filledCircleRGBA(screen, x+r, y, r,                               0, 255, 0, 255);
    filledCircleRGBA(screen, x+r*cos(3.1415/3), y-r*sin(3.1415/3), r, 0, 0, 255, 255);

    /* attetszo kor */
    x=280; y=280;
    filledCircleRGBA(screen, x, y, r,                                 255, 0, 0, 96);
    filledCircleRGBA(screen, x+r, y, r,                               0, 255, 0, 96);
    filledCircleRGBA(screen, x+r*cos(3.1415/3), y-r*sin(3.1415/3), r, 0, 0, 255, 96);

    /* szoveg */
    stringRGBA(screen, 110, 350, "Kilepeshez: piros x az ablakon", 255, 255, 255, 255);

    /* eddig elvegzett rajzolasok a kepernyore */
    SDL_Flip(screen);

    /* varunk a kilepesre */
    while (SDL_WaitEvent(&ev) && ev.type!=SDL_QUIT) {
    }

    /* ablak bezarasa */
    SDL_Quit();

    return 0;
}
