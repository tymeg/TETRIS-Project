#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "functions.h"
#include "blocks.h"

typedef struct
{
    int x;
    int y;
} Pkt;

#define WYS 22
#define SZER 12

int main()
{
    // INICJALIZACJA PLANSZY
    char plansza[WYS][SZER];

    Inicjalizuj(plansza);

    Pkt srodek;
    srodek.x = 1;
    srodek.y = 5;

    // ###
    //  #
    plansza[srodek.x][srodek.y] = plansza[srodek.x][srodek.y-1] = plansza[srodek.x][srodek.y+1] = plansza[srodek.x+1][srodek.y] = '#';

    int znak;
    time_t now, start;
    while (1)
    {
        Rysuj(plansza);
        start = time(&now);
        while( difftime(time(&now),start) < 2 ) // Potem powinno przyspieszac
        {
            if (kbhit())
            {
                znak = getch();
                if (znak == 27) // ESC - pause
                    Pauza();
                /*else if (znak == 'w')
                    Obrot();
                else if (znak == 'a')
                    Lewo();
                else if (znak == 'd')
                    Prawo();
                else if (znak == 's')
                    Dol();*/
            }
        }
        system("cls");
        //Spadek(plansza, srodek);

    }


}
