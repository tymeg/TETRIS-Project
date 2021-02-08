#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "blocks.h"

void Inicjalizuj(char plansza[WYS][SZER]);
void WstawNastepny(char plansza[WYS][SZER], Klocek Obecny, Klocek Nastepny);
void UstawPredkosc(double *predkosc, int wynik);

Klocek Losuj(const Klocek tab[7]);
bool WstawKlocek(char plansza[WYS][SZER], Klocek Obecny, Klocek Cien);

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny, bool czy_cien);

bool Lewo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);
bool Prawo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);

void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr);
bool Obrot(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);

void UsunWiersz (char plansza[WYS][SZER], int wiersz);
bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik, double predkosc);

void NowaGra(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny);
void WykonajPauze(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny);
void Aktualizuj(char plansza[WYS][SZER], int wynik, double predkosc, Klocek *Obecny, Klocek *Cien);

void Scoreboard(int wynik);
char* KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik, double predkosc);

void NaDole(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny);
void Wykonaj(int znak, char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny);


#endif // FUNCTIONS_H_INCLUDED
