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

void Menu()
{
    int znak;
    while(1)
    {
        system("cls");
        printf("\n");
        printf(" ### ### ### ##  # ###\n");
        printf("  #  #    #  # # # #  \n");
        printf("  #  ##   #  ##  # ###\n");
        printf("  #  #    #  # # #   #\n");
        printf("  #  ###  #  # # # ###\n");
        printf("                by    \n");
        printf("                 TYMEG\n\n");
        printf("     [1] START\n");
        printf("     [2] HOW TO PLAY\n");
        printf("     [3] OPTIONS\n");
        printf("     [4] SCOREBOARD\n");
        printf("     [5] EXIT\n");

        while(1)
        {
            HideCursor();
            znak = getch();
            if (znak == '1')    // START
                return;
            else if (znak == '2') // HOW TO PLAY
            {
                system("cls");
                printf("\n [ESC] BACK\n\n\n");
                printf("     W   - Rotate\n");
                printf("     S   - Down\n");
                printf("     A   - Left\n");
                printf("     D   - Right\n");
                printf("   ENTER - Drop\n");

                while(1)
                {
                    znak = getch();
                    if (znak == 27) // ESC
                        goto menu;
                }
            }
            /*
            else if (znak == '3') // OPTIONS
            {

            }
            */
            else if (znak == '4') // SCOREBOARD
            {
                system("cls");
                printf("\n [ESC] BACK\n\n\n");
                FILE *fp;
                fp = fopen("score.txt", "r");

                if (fp == NULL)
                    printf(" 1.");
                else
                {
                    int n, score;
                    fscanf(fp, "%d\n", &n);
                    for (int i=0; i<n; i++)
                    {
                        fscanf(fp, "%d\n", &score);
                        printf("%2d: %d\n", i+1, score);
                    }
                    fclose(fp);
                }

                while(1)
                {
                    znak = getch();
                    if (znak == 27) // ESC
                        goto menu;
                }
            }
            else if (znak == '5') // EXIT
                exit(0);
        }
        menu:;
    }

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

void UstawPredkosc(double *predkosc, int wynik)
{
    if (*predkosc == 1 && wynik >= 500)
        *predkosc = 0.75;
    else if (*predkosc == 0.75 && wynik >= 1000)
        *predkosc = 0.5;
    else if (*predkosc == 0.5 && wynik >= 2000)
        *predkosc = 0.2;
    else if (*predkosc == 0.2 && wynik >= 3000)
        *predkosc = 0.1;
    else if (*predkosc == 0.1 && wynik >= 5000)
        *predkosc = 0.05;
}

void Rysuj(char plansza[WYS][SZER], int wynik, double predkosc)
{
    for (int i=0; i<WYS; i++)
    {
        for (int j=0; j<SZER; j++)
            printf("%c", plansza[i][j]);
        printf("\n");
    }

    if (predkosc == 0.75)
        predkosc = 2;
    else if (predkosc == 0.5)
        predkosc = 3;
    else if (predkosc == 0.2)
        predkosc = 4;
    else if (predkosc == 0.1)
        predkosc = 5;
    printf("SCORE: %d\nSPEED: %d\n\n[ESC] PAUSE", wynik, (int)predkosc);
}

int Pauza()
{
    int znak;
    printf("\rPAUSE      \n[ESC] RESUME\n[R]   RESTART\n[M]   MENU\n[X]   EXIT\n");
    while (1)
    {
        HideCursor();
        znak = getch();
        if (znak == 27) // ESC - resume
            return 0;
        else if (znak == 'r') // R - restart
            return 1;
        else if (znak == 'm') // M - menu
            return 2;
        else if (znak == 'x') // X - exit
            return 3;
    }
}

Klocek Losuj(char plansza[WYS][SZER], Klocek tab[7])
{
    int los = rand() % 7;
    return tab[los];
}

bool WstawKlocek(char plansza[WYS][SZER], Klocek Obecny, Klocek Cien)
{
    bool pom = true;

    for (int i=0; i<4; i++)
    {
        if (plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] != '#')
            plansza[Cien.kwadraty[i].y][Cien.kwadraty[i].x] = '-';
        else
            pom = false;
    }
    for (int i=0; i<4; i++)
    {
        if (plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] != '#')
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';
    }
    return pom;
}

bool Spadek(char plansza[WYS][SZER], Klocek *Obecny, bool czy_cien)
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

        for (int i=0; i<Obecny->m; i++)
            (Obecny->zakazane[i].y)++;

        for (int i=0; i<Obecny->n; i++)
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].y)++;

        return false;
    }
    else
    {
        if (!czy_cien)
            for (int i=0; i<4; i++)
                plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '#';

        return true;
    }
}



void Lewo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
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
            plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].x)--;
        }

        (Obecny->srodek.x)--;

        for (int i=0; i<Obecny->m; i++)
            (Obecny->zakazane[i].x)--;

        for (int i=0; i<Obecny->n; i++)
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].x)--;
    }
}

void Prawo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
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
            plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].x)++;
        }

        (Obecny->srodek.x)++;

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

void Obrot(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
{
    if (Obecny->m == 0)
        return;

    Pkt sr;
    if (Obecny->n == 3)   // klocki z siatka 3x3
        sr.x = sr.y = 1;
    else    // klocek I z siatka 5x5
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
        {
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
            plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
        }

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

bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik, double predkosc)
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
            for (int j=2; j<12; j++)
                plansza[i][j] = 'x';
            ClearScreen();
            Rysuj(plansza, *wynik, predkosc);
            Sleep(200);
            usunieto = true;
            UsunWiersz(plansza, i);
            licz++;
            ClearScreen();
            Rysuj(plansza, *wynik, predkosc);
        }
    }
    *wynik += licz*licz*10;
    return usunieto;
}

void Scoreboard (int wynik)
{
    FILE *fp;
    fp = fopen("score.txt", "r");

    int n;
    if (fp == NULL) // brak wynikow (score.txt nie istnieje)
    {
        fclose(fp);
        fp = fopen("score.txt", "w");
        fprintf(fp, "1\n%d", wynik);
        fclose(fp);
        n = 1;
        printf("SCOREBOARD\n\n");
        printf(" 1. %d", wynik);
        return;
    }
    else
    {
        fscanf(fp, "%d\n", &n);   // wczytanie liczby wynikow (max 10)

        int pom;
        int scores[10];

        for (int i=0; i<n; i++)
        {
            fscanf(fp, "%d\n", &pom);
            scores[i] = pom;
        }
        fclose(fp);

        if (n<10)
        {
            n++;
            scores[n-1] = -1;
        }

        for (int i=0; i<n; i++)
        {
            if (wynik > scores[i])
            {
                pom = wynik;
                wynik = scores[i];
                scores[i] = pom;
            }
        }

        fp = fopen("score.txt", "w");
        fprintf(fp, "%d\n", n);
        printf("SCOREBOARD\n\n");

        for (int i=0; i<n; i++)
        {
            fprintf(fp, "%d\n", scores[i]);
            printf("%2d. %d\n", i+1, scores[i]);
        }
        fclose(fp);
    }

}

int KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik, double predkosc)
{
    ClearScreen();
    Rysuj(plansza, wynik, predkosc);
    Sleep(1000);
    Spadek(plansza, &Obecny, 0);
    ClearScreen();
    Rysuj(plansza, wynik, predkosc);
    Sleep(1000);
    system("cls");
    printf("\nGAME OVER!\n\n\n");
    Scoreboard(wynik);
    printf("\n\n[R]   RESTART\n[M]   MENU\n[ESC] EXIT");

    int znak;
    while (1)
    {
        if (kbhit())
        {
            znak = getch();
            if (znak == 'r') // R - restart
                return 0;
            else if (znak == 'm') // M - menu
                return 1;
            else if (znak == 27) // ESC - exit
                return 2;
        }
        else
            Sleep(100);
    }
}
