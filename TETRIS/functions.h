#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "blocks.h"

void ClearScreen();
void HideCursor();

void Inicjalizuj(char plansza[WYS][SZER]);
void WstawNastepny(char plansza[WYS][SZER], Klocek Obecny, Klocek Nastepny);
void Rysuj(char plansza[WYS][SZER], int wynik);

int Pauza();

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7]);
bool RysujKlocek(char plansza[WYS][SZER], Klocek Obecny);

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny);

void Lewo(char plansza[WYS][SZER], Klocek *Obecny);
void Prawo(char plansza[WYS][SZER], Klocek *Obecny);

void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr);
void Obrot(char plansza[WYS][SZER], Klocek *Obecny);

void UsunWiersz (char plansza[WYS][SZER], int wiersz);
bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik);

void KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik);


#endif // FUNCTIONS_H_INCLUDED
