#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "blocks.h"

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

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7])
{
    int los = rand() % 7;
    Klocek Obecny = tab[los];
    for (int i=0; i<4; i++)
        plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';
    return Obecny;
}


/* funkcja spadek jako funkcja zwracajaca Klocek
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
*/

// funkcja Spadek operujaca wskaznikiem do struktury Klocek
bool Spadek(char plansza[WYS][SZER], Klocek *Obecny)
{
    bool czy_mozna = true;

    for (int i=0; i<4; i++)
        if (plansza[Obecny->kwadraty[i].y+1][Obecny->kwadraty[i].x] == '#' || plansza[Obecny->kwadraty[i].y+1][Obecny->kwadraty[i].x] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<4; i++)
        {
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].y)++;
        }

        (Obecny->srodek.y)++;
        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '+';

        for (int i=0; i<Obecny->m; i++)
            (Obecny->zakazane[i].y)++;

        return false;
    }
    else
    {
        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '#';

        return true;
    }
}




void Lewo(char plansza[WYS][SZER], Klocek *Obecny)
{
    bool czy_mozna = true;

    for (int i=0; i<4; i++)
        if (plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x-1] == '#' || plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x-1] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<4; i++)
        {
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].x)--;
        }

        (Obecny->srodek.x)--;
        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '+';

        for (int i=0; i<Obecny->m; i++)
            (Obecny->zakazane[i].x)--;
    }
}

void Prawo(char plansza[WYS][SZER], Klocek *Obecny)
{
    bool czy_mozna = true;

    for (int i=0; i<4; i++)
        if (plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x+1] == '#' || plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x+1] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<4; i++)
        {
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].x)++;
        }

        (Obecny->srodek.x)++;
        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '+';

        for (int i=0; i<Obecny->m; i++)
            (Obecny->zakazane[i].x)++;
    }
}

void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr)
{
    int xp, yp;
    xp = sr.x - sr.y + p->y;
    yp = sr.x + sr.y + p->x;
    p->x = xp;
    p->y = yp;
}

void Obrot(char plansza[WYS][SZER], Klocek *Obecny)
{
    if (Obecny->m == 0)
        return;

    bool czy_mozna = true;

    for (int i=0; i<Obecny->m; i++)
        if (plansza[Obecny->zakazane[i].y][Obecny->zakazane[i].x] == '#' || plansza[Obecny->zakazane[i].y][Obecny->zakazane[i].x] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';

        for (int i=0; i<4; i++)
            ObrotPunktuWzglSrodka( &(Obecny->kwadraty[i]), Obecny->srodek);
        for (int i=0; i<Obecny->m; i++)
            ObrotPunktuWzglSrodka( &(Obecny->zakazane[i]), Obecny->srodek);

        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '+';
    }

}
