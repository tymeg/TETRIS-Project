#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "blocks.h"

#define WYS 22
#define SZER 12

void ClearScreen()
{
COORD cursorPosition;
cursorPosition.X = 0;
cursorPosition.Y = 0;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void HideCursor()
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = FALSE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}




void Inicjalizuj(char plansza[WYS][SZER])
{
    for (int i=0; i<12; i++)
        plansza[0][i] = plansza[21][i] = 'O';

    for (int j=1; j<21; j++)
    {
        plansza[j][0] = plansza[j][11] = 'O';
        for (int k=1; k<11; k++)
            plansza[j][k] = ' ';
    }
}

void Rysuj(char plansza[WYS][SZER])
{
    for (int i=0; i<22; i++)
    {
        for (int j=0; j<12; j++)
            printf("%c", plansza[i][j]);
        printf("\n");
    }
}

void Pauza()
{
    int znak;
    printf("PAUSE\n");
    while (1)
    {
        if (kbhit())
        {
            znak = getch();
            if (znak == 27) // ESC - resume
                return;
            else if (znak == 'm') // M - menu
            {
                printf("MENU\n");
                return;
            }
            else if (znak == 'r') // R - restart
            {
                printf("RESTART\n");
                return;
            }
        }
        else
            Sleep(100);
    }
}

Klocek Spadek(char plansza[WYS][SZER], Klocek Obecny, bool *spadl)
{
    bool czy_mozna = true;

    for (int i=0; i<4; i++)
        if (plansza[Obecny.kwadraty[i].y+1][Obecny.kwadraty[i].x] == '#' || plansza[Obecny.kwadraty[i].y+1][Obecny.kwadraty[i].x] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<4; i++)
        {
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = ' ';
            (Obecny.kwadraty[i].y)++;
        }

        (Obecny.srodek.y)++;
        for (int i=0; i<4; i++)
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';

        for (int i=0; i<Obecny.m; i++)
            (Obecny.zakazane[i].y)++;
    }
    else
    {
        *spadl = true;
        for (int i=0; i<4; i++)
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '#';
    }

    return Obecny;
}

/*
Klocek Lewo(char plansza[WYS][SZER], Klocek Obecny)
{

}

Klocek Prawo(char plansza[WYS][SZER], Klocek Obecny)
{

}

Klocek Obrot(char plansza[WYS][SZER], Klocek Obecny)
{

}
*/
