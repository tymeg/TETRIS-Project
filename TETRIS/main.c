#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#include "functions.h"
#include "blocks.h"

int main()
{
    ClearScreen();
    HideCursor();

    // INICJALIZACJA PLANSZY
    char plansza[WYS][SZER];
    Inicjalizuj(plansza);

    Pkt srodek = {6,2};

    Klocek I = { 5, 8, srodek, { {5,2}, srodek, {7,2}, {8,2} }, { {5,1}, {6,1}, {6,3}, {7,3}, {8,3}, {6,4}, {7,4}, {8,4} }, { {{4,0}, {5,0}, {6,0}, {7,0}, {8,0}}, {{4,1}, {5,1}, {6,1}, {7,1}, {8,1}}, {{4,2}, {5,2}, {6,2}, {7,2}, {8,2}}, {{4,3}, {5,3}, {6,3}, {7,3}, {8,3}}, {{4,4}, {5,4}, {6,4}, {7,4}, {8,4}} } };
    Klocek T = { 3, 4, srodek, { {5,2}, srodek, {7,2}, {6,3} }, { {5,1}, {6,1}, {5,3}, {7,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Kw= { 0, 0, srodek, { srodek, {7,2}, {6,3}, {7,3} }, {}, {} };
    Klocek L = { 3, 4, srodek, { {5,2}, srodek, {7,2}, {5,3} }, { {5,1}, {6,1}, {6,3}, {7,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek J = { 3, 4, srodek, { {5,2}, srodek, {7,2}, {7,3} }, { {5,1}, {6,1}, {5,3}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek S = { 3, 3, srodek, { {5,3}, {6,3}, srodek, {7,2} }, { {5,1}, {5,2}, {7,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Z = { 3, 3, srodek, { {5,2}, srodek, {6,3}, {7,3} }, { {5,1}, {6,1}, {5,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };

    Klocek tab[7] = {I, T, Kw, L, J, S, Z};

    srand(time(NULL));
    Klocek Obecny = Losuj(plansza, tab);

    int znak;
    time_t now, start;
    while (1)
    {
        Rysuj(plansza);
        start = time(&now);
        while( (time(&now) - start) < 1 ) // Potem powinno przyspieszac
        {
            if (kbhit())
            {
                znak = getch();
                if (znak == 27) // ESC - pause
                    Pauza();
                else if (znak == 'w')
                {
                    Obrot(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 'a')   // Lewo
                {
                    Lewo(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 'd')   // Prawo
                {
                    Prawo(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 's')   // Dol
                {
                    if (Spadek(plansza, &Obecny))
                        Obecny = Losuj(plansza, tab);
                    ClearScreen();
                    Rysuj(plansza);
                }
                else if (znak == 13)   // ENTER - spadek na sam dol
                {
                    while (!Spadek(plansza, &Obecny));
                    Obecny = Losuj(plansza, tab);
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
