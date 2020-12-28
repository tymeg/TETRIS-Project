#include <stdio.h>
#include <stdlib.h>
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

Pkt Spadek(char plansza[WYS][SZER], Pkt srodek)
{
    if (plansza[srodek.y+2][srodek.x] == ' ' && plansza[srodek.y+1][srodek.x+1] == ' ' && plansza[srodek.y+1][srodek.x-1] == ' ')
    {
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = ' ';
        (srodek.y)++;
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = '#';
    }
    else
    {
        // funkcja nowy klocek (losowanie klocka)
        srodek.y = 1;
        srodek.x = 5;
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = '#';
    }
    return srodek;
}


Pkt Lewo(char plansza[WYS][SZER], Pkt srodek)
{
    if (plansza[srodek.y][srodek.x-2] == ' ' && plansza[srodek.y+1][srodek.x-1] == ' ')
    {
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = ' ';
        (srodek.x)--;
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = '#';
    }
    return srodek;
}

Pkt Prawo(char plansza[WYS][SZER], Pkt srodek)
{
    if (plansza[srodek.y][srodek.x+2] == ' ' && plansza[srodek.y+1][srodek.x+1] == ' ')
    {
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = ' ';
        (srodek.x)++;
        plansza[srodek.y][srodek.x] = plansza[srodek.y][srodek.x-1] = plansza[srodek.y][srodek.x+1] = plansza[srodek.y+1][srodek.x] = '#';
    }
    return srodek;
}

