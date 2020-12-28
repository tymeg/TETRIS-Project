#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "functions.h"
#include "blocks.h"


#define WYS 22
#define SZER 12

int main()
{
    HideCursor();

    // INICJALIZACJA PLANSZY
    char plansza[WYS][SZER];

    Inicjalizuj(plansza);

    Pkt srodek;
    srodek.x = 5;
    srodek.y = 1;

    // ###
    //  #
    plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = '#';


    int znak;
    time_t now, start;
    while (1)
    {
        Rysuj(plansza);
        start = time(&now);
        while( difftime(time(&now),start) < 1 ) // Potem powinno przyspieszac
        {
            if (kbhit())
            {
                znak = getch();
                if (znak == 27) // ESC - pause
                    Pauza();
                /*
                else if (znak == 'w')
                    Obrot();
                */
                else if (znak == 'a')   // Lewo
                {
                    srodek = Lewo(plansza, srodek);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 'd')   // Prawo
                {
                    srodek = Prawo(plansza, srodek);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 's')   // Dol
                {
                    srodek = Spadek(plansza, srodek);
                    ClearScreen();
                    Rysuj(plansza);
                }
            }
        }
        srodek = Spadek(plansza, srodek);
        ClearScreen();
        //system("cls");

    }


}
