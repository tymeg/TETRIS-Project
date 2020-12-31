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
    RysujKlocek(plansza, Obecny);
    Klocek Nastepny = Losuj(plansza, tab);

    WstawNastepny(plansza, Obecny, Nastepny);

    int wynik = 0;
    int znak, opcja;
    time_t now, start;
    while (1)
    {
        Rysuj(plansza, wynik);
        start = time(&now);
        while( (time(&now) - start) < 1 ) // Potem powinno przyspieszac
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
                        Rysuj(plansza, wynik);
                    }
                    else if (opcja == 1) // RESTART
                    {
                        system("cls");
                        HideCursor();
                        Inicjalizuj(plansza);
                        Obecny = Losuj(plansza, tab);
                        RysujKlocek(plansza, Obecny);
                        Nastepny = Losuj(plansza, tab);
                        WstawNastepny(plansza, Obecny, Nastepny);
                        wynik = 0;
                        Rysuj(plansza, wynik);
                        start = time(&now);
                    }
                    /*
                    else    // MENU
                    {

                    }
                    */
                }
                else if (znak == 'w')
                {
                    Obrot(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza, wynik);
                }
                else if (znak == 'a')   // Lewo
                {
                    Lewo(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza, wynik);
                }
                else if (znak == 'd')   // Prawo
                {
                    Prawo(plansza, &Obecny);
                    ClearScreen();
                    Rysuj(plansza, wynik);
                }
                else if (znak == 's')   // Dol
                {
                    if (Spadek(plansza, &Obecny))
                    {
                        if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))    // od wiersza rownego srodek klocka, ktory spadl - 2
                        {
                            ClearScreen();
                            Rysuj(plansza, wynik);
                        }
                        Obecny = Nastepny;
                        if (!RysujKlocek(plansza, Obecny))
                        {
                            opcja = KoniecGry(plansza, Obecny, wynik);
                            if (opcja == 0) // RESTART
                            {
                                system("cls");
                                HideCursor();
                                Inicjalizuj(plansza);
                                Obecny = Losuj(plansza, tab);
                                RysujKlocek(plansza, Obecny);
                                wynik = 0;
                                start = time(&now);
                            }
                            else if (opcja == 1)    // EXIT
                                exit(0);
                        }
                        Nastepny = Losuj(plansza, tab);
                        WstawNastepny(plansza, Obecny, Nastepny);
                    }
                    ClearScreen();
                    Rysuj(plansza, wynik);
                }
                else if (znak == 13)   // ENTER - spadek na sam dol
                {
                    while (!Spadek(plansza, &Obecny));
                    if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))
                    {
                        ClearScreen();
                        Rysuj(plansza, wynik);
                    }
                    Obecny = Nastepny;
                    if (!RysujKlocek(plansza, Obecny))
                    {
                        opcja = KoniecGry(plansza, Obecny, wynik);
                        if (opcja == 0) // RESTART
                        {
                            system("cls");
                            HideCursor();
                            Inicjalizuj(plansza);
                            Obecny = Losuj(plansza, tab);
                            RysujKlocek(plansza, Obecny);
                            wynik = 0;
                            start = time(&now);
                        }
                        else if (opcja == 1) // EXIT
                            exit(0);
                    }
                    Nastepny = Losuj(plansza, tab);
                    WstawNastepny(plansza, Obecny, Nastepny);
                    ClearScreen();
                    Rysuj(plansza, wynik);
                }
            }
        }
        if (Spadek(plansza, &Obecny))
        {

            if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik))
            {
                ClearScreen();
                Rysuj(plansza, wynik);
            }
            Obecny = Nastepny;
            if (!RysujKlocek(plansza, Obecny))
            {
                opcja = KoniecGry(plansza, Obecny, wynik);
                if (opcja == 0) // RESTART
                {
                    system("cls");
                    HideCursor();
                    Inicjalizuj(plansza);
                    Obecny = Losuj(plansza, tab);
                    RysujKlocek(plansza, Obecny);
                    wynik = 0;
                    Rysuj(plansza, wynik);
                    start = time(&now);
                }
                else if (opcja == 1)    // EXIT
                    exit(0);
            }
            Nastepny = Losuj(plansza, tab);
            WstawNastepny(plansza, Obecny, Nastepny);
        }
        ClearScreen();
        //system("cls");

    }

}
