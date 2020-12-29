#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#define WYS 22
#define SZER 12

#include "blocks.h"

void ClearScreen();
void HideCursor();

void Inicjalizuj(char plansza[WYS][SZER]);
void Rysuj(char plansza[WYS][SZER]);

void Pauza();

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7]);

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny);
//Klocek Spadek(char plansza[WYS][SZER], Klocek Obecny, bool *spadl);
/*
Klocek Lewo(char plansza[WYS][SZER], Klocek Obecny);
Klocek Prawo(char plansza[WYS][SZER], Klocek Obecny);
Klocek Obrot(char plansza[WYS][SZER], Klocek Obecny);
*/

#endif // FUNCTIONS_H_INCLUDED
