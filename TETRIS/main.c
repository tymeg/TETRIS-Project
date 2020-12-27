#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

int main()
{
    char plansza[22][12];

    for (int i=0; i<12; i++)
        plansza[0][i] = plansza[21][i] = '*';

    for (int j=1; j<21; j++)
    {
        plansza[j][0] = plansza[j][11] = '*';
        for (int k=1; k<11; k++)
            plansza[j][k] = ' ';
    }

    int srodek = 5;

    plansza[1][srodek] = plansza[1][srodek-1] = plansza[1][srodek+1] = plansza[2][srodek] = '#';

    for (int i=0; i<22; i++)
    {
        for (int j=0; j<12; j++)
            printf("%c", plansza[i][j]);
        printf("\n");
    }


}
