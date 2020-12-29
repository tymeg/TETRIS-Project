#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "blocks.h"

void ClearScreen();
void HideCursor();

void Inicjalizuj(char plansza[WYS][SZER]);
void Rysuj(char plansza[WYS][SZER]);

void Pauza();

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7]);

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny);
//Klocek Spadek(char plansza[WYS][SZER], Klocek Obecny, bool *spadl);

void Lewo(char plansza[WYS][SZER], Klocek *Obecny);
void Prawo(char plansza[WYS][SZER], Klocek *Obecny);

// Zle
void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr);
void Obrot(char plansza[WYS][SZER], Klocek *Obecny);


#endif // FUNCTIONS_H_INCLUDED
