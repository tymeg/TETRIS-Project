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

    Klocek I = { 5, 3, srodek, { {5,2}, srodek, {7,2}, {8,2} }, { {6,1}, {6,3}, {6,4} }, { {{4,0}, {5,0}, {6,0}, {7,0}, {8,0}}, {{4,1}, {5,1}, {6,1}, {7,1}, {8,1}}, {{4,2}, {5,2}, {6,2}, {7,2}, {8,2}}, {{4,3}, {5,3}, {6,3}, {7,3}, {8,3}}, {{4,4}, {5,4}, {6,4}, {7,4}, {8,4}} } };
    Klocek T = { 3, 1, srodek, { {5,2}, srodek, {7,2}, {6,3} }, {{6,1}}, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Kw= { 0, 0, srodek, { srodek, {7,2}, {6,3}, {7,3} }, {}, {} };
    Klocek L = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {5,3} }, { {5,1}, {6,1}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek J = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {7,3} }, { {6,1}, {5,3}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek S = { 3, 2, srodek, { {5,3}, {6,3}, srodek, {7,2} }, { {5,1}, {5,2} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Z = { 3, 2, srodek, { {5,2}, srodek, {6,3}, {7,3} }, { {6,1}, {5,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };

    Klocek tab[7] = {I, T, Kw, L, J, S, Z};

    srand(time(NULL));
    Klocek Obecny = Losuj(plansza, tab);
    Klocek Cien = Obecny;
    while(!Spadek(plansza, &Cien, 1));
    WstawKlocek(plansza, Obecny, Cien);
    Klocek Nastepny = Losuj(plansza, tab);

    WstawNastepny(plansza, Obecny, Nastepny);

    int wynik = 0;
    int znak, opcja;
    double predkosc = 1;
    clock_t start;
    while (1)
    {
        UstawPredkosc(&predkosc, wynik);
        Rysuj(plansza, wynik, predkosc);
        start = clock();
        while( ( ((double)(clock() - start))/CLOCKS_PER_SEC ) < predkosc )
        {
            if (kbhit())
            {
                znak = getch();
                if (znak == 27) // ESC - pause
                {
                    opcja = Pauza();
                    if (opcja == 0) // RESUME
                    {
                        system("cls");
                        HideCursor();
                        Rysuj(plansza, wynik, predkosc);
                    }
                    else if (opcja == 1) // RESTART
                    {
                        system("cls");
                        HideCursor();
                        Inicjalizuj(plansza);
                        Cien = Obecny = Losuj(plansza, tab);
                        while(!Spadek(plansza, &Cien, 1));
                        WstawKlocek(plansza, Obecny, Cien);
                        Nastepny = Losuj(plansza, tab);
                        WstawNastepny(plansza, Obecny, Nastepny);
                        wynik = 0;
                        predkosc = 1;
                        Rysuj(plansza, wynik, predkosc);
                        start = clock();
                    }
                    /*
                    else    // MENU
                    {

                    }
                    */
                }
                else if (znak == 'w')   // Obrot
                {
                    Obrot(plansza, &Obecny, &Cien);
                    Cien = Obecny;
                    while(!Spadek(plansza, &Cien, 1));
                    WstawKlocek(plansza, Obecny, Cien);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
                else if (znak == 'a')   // Lewo
                {
                    Lewo(plansza, &Obecny, &Cien);
                    Cien = Obecny;
                    while(!Spadek(plansza, &Cien, 1));
                    WstawKlocek(plansza, Obecny, Cien);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
                else if (znak == 'd')   // Prawo
                {
                    Prawo(plansza, &Obecny, &Cien);
                    Cien = Obecny;
                    while(!Spadek(plansza, &Cien, 1));
                    WstawKlocek(plansza, Obecny, Cien);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
                else if (znak == 's')   // Dol
                {
                    if (Spadek(plansza, &Obecny, 0))
                    {
                        if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))    // od wiersza rownego srodek klocka, ktory spadl - 2
                        {
                            ClearScreen();
                            Rysuj(plansza, wynik, predkosc);
                        }
                        Cien = Obecny = Nastepny;
                        while(!Spadek(plansza, &Cien, 1));
                        if (!WstawKlocek(plansza, Obecny, Cien))
                        {
                            opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                            if (opcja == 0) // RESTART
                            {
                                system("cls");
                                HideCursor();
                                Inicjalizuj(plansza);
                                Cien = Obecny = Losuj(plansza, tab);
                                while(!Spadek(plansza, &Cien, 1));
                                WstawKlocek(plansza, Obecny, Cien);
                                predkosc = 1;
                                wynik = 0;
                                start = clock();
                            }
                            else if (opcja == 1)    // EXIT
                                exit(0);
                        }
                        Nastepny = Losuj(plansza, tab);
                        WstawNastepny(plansza, Obecny, Nastepny);
                    }
                    else
                        WstawKlocek(plansza, Obecny, Cien);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
                else if (znak == 13)   // ENTER - spadek na sam dol
                {
                    while (!Spadek(plansza, &Obecny, 0));
                    if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))
                    {
                        ClearScreen();
                        Rysuj(plansza, wynik, predkosc);
                    }
                    Cien = Obecny = Nastepny;
                    while(!Spadek(plansza, &Cien, 1));
                    if (!WstawKlocek(plansza, Obecny, Cien))
                    {
                        opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                        if (opcja == 0) // RESTART
                        {
                            system("cls");
                            HideCursor();
                            Inicjalizuj(plansza);
                            Cien = Obecny = Losuj(plansza, tab);
                            while(!Spadek(plansza, &Cien, 1));
                            WstawKlocek(plansza, Obecny, Cien);
                            predkosc = 1;
                            wynik = 0;
                            start = clock();
                        }
                        else if (opcja == 1) // EXIT
                            exit(0);
                    }
                    Nastepny = Losuj(plansza, tab);
                    WstawNastepny(plansza, Obecny, Nastepny);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
            }
        }
        if (Spadek(plansza, &Obecny, 0))
        {
            if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))
            {
                ClearScreen();
                Rysuj(plansza, wynik, predkosc);
            }
            Cien = Obecny = Nastepny;
            while(!Spadek(plansza, &Cien, 1));
            if (!WstawKlocek(plansza, Obecny, Cien))
            {
                opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                if (opcja == 0) // RESTART
                {
                    system("cls");
                    HideCursor();
                    Inicjalizuj(plansza);
                    Cien = Obecny = Losuj(plansza, tab);
                    while(!Spadek(plansza, &Cien, 1));
                    WstawKlocek(plansza, Obecny, Cien);
                    wynik = 0;
                    predkosc = 1;
                    Rysuj(plansza, wynik, predkosc);
                    start = clock();
                }
                else if (opcja == 1)    // EXIT
                    exit(0);
            }
            Nastepny = Losuj(plansza, tab);
            WstawNastepny(plansza, Obecny, Nastepny);
        }
        else
            WstawKlocek(plansza, Obecny, Cien);
        ClearScreen();
        //system("cls");

    }

}
