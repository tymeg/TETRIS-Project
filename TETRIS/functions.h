#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "blocks.h"

void ClearScreen();
void HideCursor();

void Inicjalizuj(char plansza[WYS][SZER]);
void WstawNastepny(char plansza[WYS][SZER], Klocek Obecny, Klocek Nastepny);
void UstawPredkosc(double *predkosc, int wynik);
void Rysuj(char plansza[WYS][SZER], int wynik, double predkosc);

int Pauza();

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7]);
bool WstawKlocek(char plansza[WYS][SZER], Klocek Obecny, Klocek Cien);

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny, bool czy_cien);

void Lewo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);
void Prawo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);

void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr);
void Obrot(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien);

void UsunWiersz (char plansza[WYS][SZER], int wiersz);
bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik);

int KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik, double predkosc);


#endif // FUNCTIONS_H_INCLUDED
