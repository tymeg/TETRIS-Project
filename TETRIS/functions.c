#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "blocks.h"

#define WYS 22
#define SZER 12

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
            {
                printf("RESUME\n");
                break;
            }
            else if (znak == 'm') // M - menu
            {
                printf("MENU\n");
                return;
            }
            else if (znak == 'r') // R - restart
            {
                printf("RESTART\n");
                break;
            }
        }
        else
            Sleep(100);
    }
}

/*void Spadek(char plansza[WYS][SZER], Pkt srodek)
{
    plansza[srodek.x][srodek.y] = plansza[srodek.x][srodek.y-1] = plansza[srodek.x][srodek.y+1] = plansza[srodek.x+1][srodek.y] = ' ';
    (srodek.x)++;
    plansza[srodek.x][srodek.y] = plansza[srodek.x][srodek.y-1] = plansza[srodek.x][srodek.y+1] = plansza[srodek.x+1][srodek.y] = '#';

}*/

