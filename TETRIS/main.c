#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

#include "game_state.h"
#include "show.h"
#include "blocks.h"

int main()
{
    HideCursor();
    Menu();
    system("cls");

    // INICJALIZACJA PLANSZY
    char plansza[WYS][SZER];
    Inicjalizuj(plansza);

    Pkt srodek = {6,2}; // srodek kazdego klocka nowo wstawianego na gore planszy

    // utworzenie 7 typow Klockow z odpowiednimi parametrami (patrz: blocks.h)
    Klocek I = { 5, 3, srodek, { {5,2}, srodek, {7,2}, {8,2} }, { {6,1}, {6,3}, {6,4} }, { {{4,0}, {5,0}, {6,0}, {7,0}, {8,0}}, {{4,1}, {5,1}, {6,1}, {7,1}, {8,1}}, {{4,2}, {5,2}, {6,2}, {7,2}, {8,2}}, {{4,3}, {5,3}, {6,3}, {7,3}, {8,3}}, {{4,4}, {5,4}, {6,4}, {7,4}, {8,4}} } };
    Klocek T = { 3, 1, srodek, { {5,2}, srodek, {7,2}, {6,3} }, {{6,1}}, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Kw= { 0, 0, srodek, { srodek, {7,2}, {6,3}, {7,3} }, {}, {} };
    Klocek L = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {5,3} }, { {5,1}, {6,1}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek J = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {7,3} }, { {6,1}, {5,3}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek S = { 3, 2, srodek, { {5,3}, {6,3}, srodek, {7,2} }, { {5,1}, {5,2} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
    Klocek Z = { 3, 2, srodek, { {5,2}, srodek, {6,3}, {7,3} }, { {6,1}, {5,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };

    // utworzenie tablicy 7 typow Klockow, z ktorej beda losowane nowe Klocki
    Klocek tab[7] = {I, T, Kw, L, J, S, Z};

    srand(time(NULL));
    Klocek Obecny = Losuj(tab); // wylosowanie Klocka Obecny
    Klocek Cien = Obecny; // podstawienie Obecny pod Cien
    while(!Spadek(plansza, &Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
    WstawKlocek(plansza, Obecny, Cien); // wstawienie obu Klockow
    Klocek Nastepny = Losuj(tab);   // wylosowanie Klocka Nastepny
    WstawNastepny(plansza, Obecny, Nastepny);   // wstawienie go w prawy gorny rog planszy

    int wynik = 0;  // wynik startowy
    int znak, opcja;
    double predkosc = 1; // predkosc startowa, zmienna ta oznacza czestotliwosc samoczynnego spadania klocka w sekundach
    clock_t start;

    // NIESKONCZONA PETLA - RDZEN ROZGRYWKI
    while (1)
    {
        HideCursor();
        UstawPredkosc(&predkosc, wynik);    // z kazdym automatycznym spadkiem o 1 ustawiaj odpowiednia predkosc w zaleznosci od wyniku
        Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
        start = clock();    // rozpoczecie liczenia czasu
        while( ( ((double)(clock() - start))/CLOCKS_PER_SEC ) < predkosc )  // oczekiwanie na wejscie z klawiatury uzytkownika przez czas rowny predkosc
        {
            if (kbhit())
            {
                znak = getch();
                if (znak == 27) // ESC - PAUSE
                {
                    opcja = Pauza(); // w zaleznosci od wyniku Pauza wyjscie z gry, resume, wyjscie do menu lub restart
                    if (opcja == 3)    // EXIT
                        exit(0);
                    else if (opcja == 0) // RESUME
                    {
                        system("cls");
                        HideCursor();
                        Rysuj(plansza, wynik, predkosc);
                    }
                    else if (opcja == 2)    // MENU
                        Menu();
                    /* RESTART z menu (opcja 1) lub pauzy - inicjalizacja planszy, wylosowanie i wstawienie Klockow Obecny, Cien,
                                                wyzerowanie wyniku i zegaru, ustawienie startowej predkosci */
                    if (opcja == 2 || opcja == 1)
                    {
                        system("cls");
                        Inicjalizuj(plansza);
                        Cien = Obecny = Losuj(tab);
                        while(!Spadek(plansza, &Cien, 1));
                        WstawKlocek(plansza, Obecny, Cien);
                        Nastepny = Losuj(tab);
                        WstawNastepny(plansza, Obecny, Nastepny);
                        wynik = 0;
                        predkosc = 1;
                        Rysuj(plansza, wynik, predkosc);
                        start = clock();
                    }
                }
                else if (znak == 'w')   // OBROT
                {
                    if (Obrot(plansza, &Obecny, &Cien)) // obrocenie klocka Obecny (jesli to mozliwe - wtedy true)
                    {
                        Cien = Obecny;  // podstawienie Obecny pod Cien
                        while(!Spadek(plansza, &Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
                        WstawKlocek(plansza, Obecny, Cien); // wstawienie klockow
                        ClearScreen();
                        Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
                    }
                }
                else if (znak == 'a')   // Lewo
                {
                    if (Lewo(plansza, &Obecny, &Cien))  // przesuniecie klocka Obecny o 1 w lewo (jesli to mozliwe - wtedy true)
                    {
                        Cien = Obecny;  // podstawienie Obecny pod Cien
                        while(!Spadek(plansza, &Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
                        WstawKlocek(plansza, Obecny, Cien); // wstawienie klockow
                        ClearScreen();
                        Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
                    }
                }
                else if (znak == 'd')   // Prawo
                {
                    if (Prawo(plansza, &Obecny, &Cien)) // przesuniecie klocka Obecny o 1 w prawo (jesli to mozliwe - wtedy true)
                    {
                        Cien = Obecny;  // podstawienie Obecny pod Cien
                        while(!Spadek(plansza, &Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
                        WstawKlocek(plansza, Obecny, Cien); // wstawienie klockow
                        ClearScreen();
                        Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
                    }
                }
                else if (znak == 's')   // Dol
                {
                    if (Spadek(plansza, &Obecny, 0))    // wywolanie spadek, true jezeli klocek spadl na sam dol
                    {
                        if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik, predkosc))    // sprawdzenie, czy sa pelne wiersze (od wiersza rownego srodek klocka, ktory spadl - 2)
                        {
                            start = clock();
                            ClearScreen();
                            Rysuj(plansza, wynik, predkosc);
                        }
                        Cien = Obecny = Nastepny;   // Obecny i Cien staja sie Nastepnym
                        while(!Spadek(plansza, &Cien, 1));
                        if (!WstawKlocek(plansza, Obecny, Cien))    // jesli gra nie moze wstawic nowego klocka na gore planszy, to koniec gry
                        {
                            opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                            if (opcja == 2)    // EXIT
                                exit(0);
                            else if (opcja == 1)    // MENU
                                Menu();
                            /* RESTART (opcja == 0) - inicjalizacja planszy, wylosowanie i wstawienie Klockow Obecny, Cien,
                                                    wyzerowanie wyniku i zegaru, ustawienie startowej predkosci */
                            system("cls");
                            Inicjalizuj(plansza);
                            Cien = Obecny = Losuj(tab);
                            while(!Spadek(plansza, &Cien, 1));
                            WstawKlocek(plansza, Obecny, Cien);
                            wynik = 0;
                            predkosc = 1;
                            Rysuj(plansza, wynik, predkosc);
                            start = clock();
                        }
                        Nastepny = Losuj(tab);  // losowanie Klocka Nastepny i wstawienie go w prawy gorny rog planszy
                        WstawNastepny(plansza, Obecny, Nastepny);
                    }
                    else    // klocek nie spadl na sam dol, wtedy wstaw Klocki Obecny i Cien i odswiez plansze
                        WstawKlocek(plansza, Obecny, Cien);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
                else if (znak == 13)   // ENTER - spadek na sam dol
                {
                    while (!Spadek(plansza, &Obecny, 0));   // przesuwanie klocka Obecny w dol tak dlugo, jak to mozliwe
                    if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik, predkosc)) // sprawdzenie, czy sa pelne wiersze (od wiersza rownego srodek klocka, ktory spadl - 2)
                    {
                        start = clock();
                        ClearScreen();
                        Rysuj(plansza, wynik, predkosc);
                    }
                    Cien = Obecny = Nastepny;   // Obecny i Cien staja sie Nastepnym
                    while(!Spadek(plansza, &Cien, 1));
                    if (!WstawKlocek(plansza, Obecny, Cien))    // jesli gra nie moze wstawic nowego klocka na gore planszy, to koniec gry
                    {
                        opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                        if (opcja == 2)    // EXIT
                            exit(0);
                        else if (opcja == 1)    // MENU
                            Menu();
                        /* RESTART (opcja == 0) - inicjalizacja planszy, wylosowanie i wstawienie Klockow Obecny, Cien,
                                                    wyzerowanie wyniku i zegaru, ustawienie startowej predkosci */
                        system("cls");
                        Inicjalizuj(plansza);
                        Cien = Obecny = Losuj(tab);
                        while(!Spadek(plansza, &Cien, 1));
                        WstawKlocek(plansza, Obecny, Cien);
                        wynik = 0;
                        predkosc = 1;
                        Rysuj(plansza, wynik, predkosc);
                        start = clock();
                    }
                    Nastepny = Losuj(tab);
                    WstawNastepny(plansza, Obecny, Nastepny);
                    ClearScreen();
                    Rysuj(plansza, wynik, predkosc);
                }
            }
        }
        // KONIEC CZASU NA WCISKANIE KLAWISZY PRZEZ UZYTKOWNIKA - samoczynny spadek klocka
        if (Spadek(plansza, &Obecny, 0))    // wywolanie spadek, true jezeli klocek spadl na sam dol
        {
            if (SprawdzWiersze(plansza, Obecny.srodek.y - 2, &wynik, predkosc)) // sprawdzenie, czy sa pelne wiersze (od wiersza rownego srodek klocka, ktory spadl - 2)
            {
                ClearScreen();
                Rysuj(plansza, wynik, predkosc);
            }
            Cien = Obecny = Nastepny;   // Obecny i Cien staja sie Nastepnym
            while(!Spadek(plansza, &Cien, 1)); // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
            if (!WstawKlocek(plansza, Obecny, Cien))    // jesli gra nie moze wstawic nowego klocka na gore planszy, to koniec gry
            {
                opcja = KoniecGry(plansza, Obecny, wynik, predkosc);
                if (opcja == 2)    // EXIT
                    exit(0);
                else if (opcja == 1)    // MENU
                    Menu();
                /* RESTART (opcja == 0) - inicjalizacja planszy, wylosowanie i wstawienie Klockow Obecny, Cien,
                                                wyzerowanie wyniku i zegaru, ustawienie startowej predkosci */
                system("cls");
                Inicjalizuj(plansza);
                Cien = Obecny = Losuj(tab);
                while(!Spadek(plansza, &Cien, 1));
                WstawKlocek(plansza, Obecny, Cien);
                wynik = 0;
                predkosc = 1;
                Rysuj(plansza, wynik, predkosc);
                start = clock();
            }
            Nastepny = Losuj(tab);  // losowanie Klocka Nastepny
            WstawNastepny(plansza, Obecny, Nastepny);   // wstawienie klockow
        }
        else    // klocek nie spadl na sam dol, wtedy wstaw klocki Obecny i Cien (ich wyswietlenie nastapi na poczatku kolejnego obrotu glownej petli)
            WstawKlocek(plansza, Obecny, Cien);
        ClearScreen();

    }

}
