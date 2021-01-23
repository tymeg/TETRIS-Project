#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED

#include "blocks.h"

void ClearScreen();
void HideCursor();

void Menu();
int Pauza();

void Rysuj(char plansza[WYS][SZER], int wynik, double predkosc);

#endif // SHOW_H_INCLUDED
