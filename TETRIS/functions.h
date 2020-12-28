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

Pkt Spadek(char plansza[WYS][SZER], Pkt srodek);


#endif // FUNCTIONS_H_INCLUDED
