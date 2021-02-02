#ifndef SHOW_H_INCLUDED
#define SHOW_H_INCLUDED

#include "blocks.h"

void ClearScreen();
void ReturnCursor();
void HideCursor();

void Sleep1Sec();
void Sleep0_2Sec();

void Menu();
char* Pauza();

void Rysuj(char plansza[WYS][SZER], int wynik, double predkosc);

#endif // SHOW_H_INCLUDED
