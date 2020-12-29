#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#include "functions.h"
#include "blocks.h"

#define WYS 22
#define SZER 12

int main()
{
    HideCursor();

    // INICJALIZACJA PLANSZY
    char plansza[WYS][SZER];

    Pkt srodek;
    srodek.x = 5;
    srodek.y = 1;

    Klocek I = { 8, srodek, { {4,1}, srodek, {6,1}, {7,1} }, { {4,0}, {5,0}, {5,2}, {6,2}, {7,2}, {5,3} } };
    Klocek T = { 4, srodek, { {4,1}, srodek, {6,1}, {5,2} }, { {4,0}, {5,0}, {4,2}, {6,2} } };
    Klocek Kw= { 0, srodek, { srodek, {6,1}, {5,2}, {6,2} }, {} };
    Klocek L = { 4, srodek, { {4,1}, srodek, {6,1}, {4,2} }, { {4,0}, {5,0}, {5,2}, {6,2} } };
    Klocek J = { 4, srodek, { {4,1}, srodek, {6,1}, {6,2} }, { {4,0}, {5,0}, {4,2}, {5,2} } };
    Klocek S = { 3, srodek, { {4,2}, {5,2}, srodek, {6,1} }, { {4,0}, {4,1}, {6,2} } };
    Klocek Z = { 3, srodek, { {4,2}, {5,2}, srodek, {6,1} }, { {4,0}, {4,1}, {6,2} } };

    Klocek tab[7] = {I, T, Kw, L, J, S, Z};

    Inicjalizuj(plansza);

    srand(time(NULL));
    Klocek Obecny = Losuj(plansza, tab);

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
                //else if (znak == 'w')
                   // Obrot();
                /*else if (znak == 'a')   // Lewo
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
                }*/
                else if (znak == 's')   // Dol
                {
                    if (Spadek(plansza, &Obecny))
                        Obecny = Losuj(plansza, tab);
                        /*
                        los = rand() % 7;
                        Obecny = tab[los];
                        for (int i=0; i<4; i++)
                            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';
                        */
                    ClearScreen();
                    Rysuj(plansza);
                }
            }
        }
        if (Spadek(plansza, &Obecny))
            Obecny = Losuj(plansza, tab);
        ClearScreen();
        //system("cls");

    }

}
