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
    for (int i=0; i<21; i++)
        plansza[0][i] = plansza[23][i] = ' ';

    plansza[1][0] = plansza[22][0] = ' ';

    for (int i=1; i<21; i++)
        plansza[1][i] = plansza[22][i] = 'O';

    for (int j=2; j<22; j++)
    {
        plansza[j][0] = ' ';
        plansza[j][1] = plansza[j][12] = plansza[j][20] = 'O';
        for (int k=2; k<12; k++)
            plansza[j][k] = ' ';
        for (int k=13; k<20; k++)
            plansza[j][k] = ' ';
    }
    for (int i=13; i<20; i++)
        plansza[12][i] = plansza[11][i] = 'O';

    plansza[15][13] = 'T', plansza[15][14] = 'E', plansza[15][15] = 'T', plansza[15][16] = 'R', plansza[15][17] = 'I', plansza[15][18] = 'S';
    plansza[17][14] = 'b', plansza[17][15] = 'y';
    plansza[19][15] = 'T', plansza[19][16] = 'Y', plansza[19][17] = 'M', plansza[19][18] = 'E', plansza[19][19] = 'G';
}

void WstawNastepny(char plansza[WYS][SZER], Klocek Obecny, Klocek Nastepny)
{
    plansza[4][14] = 'N', plansza[4][15] = 'E', plansza[4][16] = 'X', plansza[4][17] = 'T', plansza[4][18] = ':';

    for (int i=0; i<4; i++)
        plansza[Obecny.kwadraty[i].y+5][Obecny.kwadraty[i].x+10] = ' ';

    for (int i=0; i<4; i++)
        plansza[Nastepny.kwadraty[i].y+5][Nastepny.kwadraty[i].x+10] = '+';
}

void Rysuj(char plansza[WYS][SZER], int wynik)
{
    for (int i=0; i<WYS; i++)
    {
        for (int j=0; j<SZER; j++)
            printf("%c", plansza[i][j]);
        printf("\n");
    }
    printf("SCORE: %d\n\n[ESC] PAUSE", wynik);
}

int Pauza()
{
    int znak;
    printf("\rPAUSE      \n[ESC] RESUME\n[R]   RESTART\n");
    while (1)
    {
        if (kbhit())
        {
            znak = getch();
            if (znak == 27) // ESC - resume
                return 0;
            else if (znak == 'r') // R - restart
                return 1;
            /*
            else if (znak == 'm') // M - menu
                return 2;
            */
        }
        else
            Sleep(100);
    }
}

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7])
{
    int los = rand() % 7;
    return tab[los];
}

bool RysujKlocek(char plansza[WYS][SZER], Klocek Obecny)
{
    bool pom = true;

    for (int i=0; i<4; i++)
    {
        if (plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] != '#')
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';
        else
            pom = false;
    }
    return pom;
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

bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik)
{
    int licz = 0;
    bool usunieto = false;

    for (int i=wiersz; i<22; i++)
    {
        bool pelny = true;
        for (int j=2; j<12; j++)
            if (plansza[i][j] == ' ' || plansza[i][j] == 'O')
            {
                pelny = false;
                break;
            }
        if (pelny)
        {
            usunieto = true;
            UsunWiersz(plansza, i);
            licz++;
        }
    }
    *wynik += licz*licz*10;
    return usunieto;
}

int KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik)
{
    ClearScreen();
    Rysuj(plansza, wynik);
    Sleep(1000);
    Spadek(plansza, &Obecny);
    ClearScreen();
    Rysuj(plansza, wynik);
    Sleep(1000);
    printf("\rGAME OVER  \n\n[R]  RESTART\n[ESC] EXIT");

    int znak;
    while (1)
    {
        if (kbhit())
        {
            znak = getch();
            if (znak == 'r') // R - restart
                return 0;
            else if (znak == 27) // ESC - exit
                return 1;
            /*
            else if (znak == 'm') // M - menu
                return 2;
            */
        }
        else
            Sleep(100);
    }
}
