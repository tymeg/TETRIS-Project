#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <stdbool.h>

#include "game_state.h"
#include "show.h"
#include "blocks.h"

const Pkt srodek = {6,2}; // srodek kazdego klocka nowo wstawianego na gore planszy

// utworzenie 7 typow Klockow z odpowiednimi parametrami (patrz: blocks.h)
const Klocek I = { 5, 3, srodek, { {5,2}, srodek, {7,2}, {8,2} }, { {6,1}, {6,3}, {6,4} }, { {{4,0}, {5,0}, {6,0}, {7,0}, {8,0}}, {{4,1}, {5,1}, {6,1}, {7,1}, {8,1}}, {{4,2}, {5,2}, {6,2}, {7,2}, {8,2}}, {{4,3}, {5,3}, {6,3}, {7,3}, {8,3}}, {{4,4}, {5,4}, {6,4}, {7,4}, {8,4}} } };
const Klocek T = { 3, 1, srodek, { {5,2}, srodek, {7,2}, {6,3} }, {{6,1}}, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
const Klocek Kw= { 0, 0, srodek, { srodek, {7,2}, {6,3}, {7,3} }, {}, {} };
const Klocek L = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {5,3} }, { {5,1}, {6,1}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
const Klocek J = { 3, 3, srodek, { {5,2}, srodek, {7,2}, {7,3} }, { {6,1}, {5,3}, {6,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
const Klocek S = { 3, 2, srodek, { {5,3}, {6,3}, srodek, {7,2} }, { {5,1}, {5,2} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };
const Klocek Z = { 3, 2, srodek, { {5,2}, srodek, {6,3}, {7,3} }, { {6,1}, {5,3} }, { {{5,1}, {6,1}, {7,1}}, {{5,2}, {6,2}, {7,2}}, {{5,3}, {6,3}, {7,3}} } };

// utworzenie tablicy 7 typow Klockow, z ktorej beda losowane nowe Klocki
const Klocek tab[TYPY] = {I, T, Kw, L, J, S, Z};

int main()
{
    // INICJALIZACJA PLANSZY I ZMIENNYCH
    char plansza[WYS][SZER];

    srand(time(NULL));
    Klocek Obecny, Cien, Nastepny;
    int wynik, znak;
    double predkosc; // zmienna ta oznacza czestotliwosc samoczynnego spadania klocka w sekundach
    clock_t start;

    HideCursor();
    Menu();
    ClearScreen();

    NowaGra(plansza, tab, &wynik, &predkosc, &start, &Obecny, &Cien, &Nastepny);

    // NIESKONCZONA PETLA - RDZEN ROZGRYWKI
    while (1)
    {
        HideCursor();
        UstawPredkosc(&predkosc, wynik);    // z kazdym automatycznym spadkiem o 1 ustawiaj odpowiednia predkosc w zaleznosci od wyniku
        ReturnCursor();
        Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
        start = clock();    // rozpoczecie liczenia czasu
        while( ( ((double)(clock() - start))/CLOCKS_PER_SEC ) < predkosc )  // oczekiwanie na wejscie z klawiatury uzytkownika przez czas rowny predkosc
        {
            if (kbhit())
            {
                znak = getch(); // wprowadzony znak zostaje przekazany do funkcji Wykonaj
                Wykonaj(znak, plansza, tab, &wynik, &predkosc, &start, &Obecny, &Cien, &Nastepny);
            }
        }
        // koniec czasu na wciskanie klawiszy przez uzytkownika - samoczynny spadek klocka
        Wykonaj(AUTO, plansza, tab, &wynik, &predkosc, &start, &Obecny, &Cien, &Nastepny);
    }

}
