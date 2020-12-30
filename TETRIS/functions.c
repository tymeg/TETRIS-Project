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
    for (int i=0; i<14; i++)
        plansza[0][i] = plansza[23][i] = ' ';

    plansza[1][0] = plansza[1][13] = plansza[22][0] = plansza[22][13] = ' ';

    for (int i=1; i<13; i++)
        plansza[1][i] = plansza[22][i] = 'O';

    for (int j=2; j<22; j++)
    {
        plansza[j][0] = plansza[j][13] = ' ';
        plansza[j][1] = plansza[j][12] = 'O';
        for (int k=2; k<12; k++)
            plansza[j][k] = ' ';
    }
}

void Rysuj(char plansza[WYS][SZER])
{
    for (int i=0; i<WYS; i++)
    {
        for (int j=0; j<SZER; j++)
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

        for (int i=0; i<Obecny->n; i++)
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].y)++;

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

        for (int i=0; i<Obecny->n; i++)
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].x)--;
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

        for (int i=0; i<Obecny->n; i++)
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].x)++;
    }
}

void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr)
{
    int xp, yp;
    xp = sr.x - sr.y + p->y;
    yp = sr.x + sr.y - p->x;
    p->x = xp;
    p->y = yp;
}

void Obrot(char plansza[WYS][SZER], Klocek *Obecny)
{
    if (Obecny->m == 0)
        return;

    Pkt sr;
    if (Obecny->n == 3)   // klocki z siatka 3x3
        sr.x = sr.y = 1;
    else    // klocek I
        sr.x = sr.y = 2;

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
        {
            Pkt pom = {Obecny->kwadraty[i].y - Obecny->siatka[0][0].y, Obecny->kwadraty[i].x - Obecny->siatka[0][0].x};
            ObrotPunktuWzglSrodka(&pom, sr);
            Obecny->kwadraty[i].x = Obecny->siatka[pom.x][pom.y].x;
            Obecny->kwadraty[i].y = Obecny->siatka[pom.x][pom.y].y;
        }
        for (int i=0; i<Obecny->m; i++)
        {
            Pkt pom = {Obecny->zakazane[i].y - Obecny->siatka[0][0].y, Obecny->zakazane[i].x - Obecny->siatka[0][0].x};
            ObrotPunktuWzglSrodka(&pom, sr);
            Obecny->zakazane[i].x = Obecny->siatka[pom.x][pom.y].x;
            Obecny->zakazane[i].y = Obecny->siatka[pom.x][pom.y].y;
        }

        for (int i=0; i<4; i++)
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '+';
    }

}

void UsunWiersz (char plansza[WYS][SZER], int wiersz)
{
    bool pusty = false;

    while (!pusty)  // jesli wiersz-1 jest pusty albo zajety kolkami, to koncz przesuwanie wierszy w dol
    {
        pusty = true;
        for (int j=2; j<12; j++)
            if (plansza[wiersz-1][j] == '#')
            {
                pusty = false;
                break;
            }

        if (plansza[wiersz-1][2] != 'O')
            for (int j=2; j<12; j++)
                plansza[wiersz][j] = plansza[wiersz-1][j];
        else    // najwyzszy wiersz
            for (int j=2; j<12; j++)
                plansza[wiersz][j] = ' ';

        wiersz--;
    }

}

bool SprawdzWiersze (char plansza[WYS][SZER])
{
    bool usunieto = false;

    for (int i=2; i<22; i++)
    {
        bool pelny = true;
        for (int j=2; j<12; j++)
            if (plansza[i][j] == ' ')
            {
                pelny = false;
                break;
            }
        if (pelny)
        {
            usunieto = true;
            UsunWiersz(plansza, i);
        }
    }
    if (usunieto)
        return true;
    else
        return false;
}
