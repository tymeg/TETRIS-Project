#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#include "blocks.h"

// CZYSCZENIE EKRANU, PRZENOSZENIE KURSORA NA POCZATEK, CHOWANIE KURSORA (korzystaja z windows.h)

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

// WYSWIETLANIE STANOW MENU I PAUZY

void Menu()
{
    int znak;
    while(1)    // wyswietlanie menu
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
        printf("     [3] SCOREBOARD\n");
        printf("     [4] EXIT\n");

        while(1)    // oczekiwanie na wejscie z klawiatury uzytkownika
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

                while(1)    // powrot do menu
                {
                    znak = getch();
                    if (znak == 27) // ESC
                        goto menu;
                }
            }
            else if (znak == '3') // SCOREBOARD - wczytanie z pliku score.txt i wyswietlenie
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

                while(1)    // powrot do menu
                {
                    znak = getch();
                    if (znak == 27) // ESC
                        goto menu;
                }
            }
            else if (znak == '4') // EXIT
                exit(0);
        }
        menu:;
    }

}

// zwraca 0, 1, 2 lub 3
int Pauza()
{
    int znak;
    printf("\rPAUSE      \n[ESC] RESUME\n[R]   RESTART\n[M]   MENU\n[X]   EXIT\n");
    while (1) // oczekiwanie na wejscie z klawiatury uzytkownika
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

// WYSWIETLANIE PLANSZY W KONSOLI

void Rysuj(char plansza[WYS][SZER], int wynik, double predkosc)
{
    for (int i=0; i<WYS; i++)
    {
        for (int j=0; j<SZER; j++)
            printf("%c", plansza[i][j]);
        printf("\n");
    }

    // wyswietlenie na ekranie wyniku i obecnego poziomu predkosci (1-5)
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
