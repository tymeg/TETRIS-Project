#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#include "blocks.h"
#include "show.h"

// wstawienie na poczatku gry odpowiednich znakow do tablicy plansza - spacje oraz 'O' jako obramowania
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

    // wyswietlenie napisu "TETRIS by TYMEG" w prawym dolnym rogu planszy
    plansza[15][13] = 'T', plansza[15][14] = 'E', plansza[15][15] = 'T', plansza[15][16] = 'R', plansza[15][17] = 'I', plansza[15][18] = 'S';
    plansza[17][14] = 'b', plansza[17][15] = 'y';
    plansza[19][15] = 'T', plansza[19][16] = 'Y', plansza[19][17] = 'M', plansza[19][18] = 'E', plansza[19][19] = 'G';
}

// wstawienie do prawego gornego rogu planszy nastepnego klocka, ktory pojawi sie na gorze planszy
void WstawNastepny(char plansza[WYS][SZER], Klocek Obecny, Klocek Nastepny)
{
    plansza[4][14] = 'N', plansza[4][15] = 'E', plansza[4][16] = 'X', plansza[4][17] = 'T', plansza[4][18] = ':';

    // wyczyszczenie pol zajmowanych przez poprzedni klocek
    for (int i=0; i<KWADRATY; i++)
        plansza[Obecny.kwadraty[i].y+5][Obecny.kwadraty[i].x+10] = ' ';

    // wstawienie '+' na bazie pol kwadraty Klocka Nastepny
    for (int i=0; i<KWADRATY; i++)
        plansza[Nastepny.kwadraty[i].y+5][Nastepny.kwadraty[i].x+10] = '+';
}

// zmiana predkosci samoczynnego spadania klocka po przekraczaniu odpowiednich progow punktowych
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
}

// losowanie klocka sposrod tablicy 7 mozliwych klockow i zwrocenie go
Klocek Losuj(const Klocek tab[TYPY])
{
    int los = rand() % TYPY;
    return tab[los];
}

// wstawienie Klockow Obecny i Cien do planszy, zwrocenie false, jezeli wstawienie jest niemozliwe
bool WstawKlocek(char plansza[WYS][SZER], Klocek Obecny, Klocek Cien)
{
    bool pom = true;

    for (int i=0; i<KWADRATY; i++)
    {
        // wstawienie '-' jako Klocka Cien, jezeli pole nie jest zajete
        if (plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] != '#')
            plansza[Cien.kwadraty[i].y][Cien.kwadraty[i].x] = '-';
        else    // jesli ktorekolwiek pole jest zajete, to nie mozna wstawic
            pom = false;
    }
    for (int i=0; i<KWADRATY; i++)
    {
        // wstawianie '+' nadpisuje ewentualne '-'
        if (plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] != '#')
            plansza[Obecny.kwadraty[i].y][Obecny.kwadraty[i].x] = '+';
    }
    return pom;
}

// przestawianie '+' Klocka o jedno pole w dol w planszy
bool Spadek(char plansza[WYS][SZER], Klocek *Obecny, bool czy_cien)
{
    bool czy_mozna = true;

    // jesli ktores z pol ponizej zajete, to nie mozna wykonac spadku
    for (int i=0; i<KWADRATY; i++)
        if (plansza[Obecny->kwadraty[i].y+1][Obecny->kwadraty[i].x] == '#' || plansza[Obecny->kwadraty[i].y+1][Obecny->kwadraty[i].x] == 'O')
        {
            czy_mozna = false;
            break;
        }

    if (czy_mozna)
    {
        for (int i=0; i<KWADRATY; i++) // wyczyszczenie pol dotychczas zajetych, przesuniecie kwadratow o 1 w dol
        {
            plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
            (Obecny->kwadraty[i].y)++;
        }

        (Obecny->srodek.y)++;   // przesuniecie srodka o 1 w dol

        for (int i=0; i<Obecny->m; i++) // przesuniecie zakazanych o 1 w dol
            (Obecny->zakazane[i].y)++;

        for (int i=0; i<Obecny->n; i++) // przesuniecie siatki o 1 w dol
            for (int j=0; j<Obecny->n; j++)
                (Obecny->siatka[i][j].y)++;

        return false;   // zwraca false, jezeli Klocek jeszcze nie spadl na sam dol
    }
    else
    {
        if (!czy_cien)  // jesli podany do funkcji Klocek nie jest Cieniem, to w przypadku spadku na sam dol wstaw '#'
            for (int i=0; i<KWADRATY; i++)
                plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = '#';

        return true;    // zwraca true, gdy Klocek spadl na sam dol
    }
}


// przestawianie '+' Klocka Obecny o jedno pole w lewo w planszy (Cien przekazujemy tylko po to, by wymazac jego obecna pozycje)
bool Lewo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
{
    // dla kazdego kwadratu Klocka sprawdzanie, czy pole na lewo nie jest zajete przez '#' lub 'O' (moze byc zajete przez '+')
    for (int i=0; i<KWADRATY; i++)
        if (plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x-1] == '#' || plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x-1] == 'O')
            return false;   // nie mozna wykonac ruchu w lewo

    for (int i=0; i<KWADRATY; i++) // wyczyszczenie pol zajetych obecnie przez Klocki Obecny, Cien, przesuniecie kwadratow o 1 w lewo
    {
        plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
        plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
        (Obecny->kwadraty[i].x)--;
    }

    (Obecny->srodek.x)--;   // przesuniecie srodka o 1 w lewo

    for (int i=0; i<Obecny->m; i++) // przesuniecie zakazanych o 1 w lewo
        (Obecny->zakazane[i].x)--;

    for (int i=0; i<Obecny->n; i++) // przesuniecie siatki o 1 w lewo
        for (int j=0; j<Obecny->n; j++)
            (Obecny->siatka[i][j].x)--;

    return true;    // wykonano ruch w lewo
}

// przestawianie '+' Klocka Obecny o jedno pole w prawo w planszy (Cien przekazujemy tylko po to, by wymazac jego obecna pozycje)
bool Prawo(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
{
    // dla kazdego kwadratu Klocka sprawdza, czy pole na prawo nie jest zajete przez '#' lub 'O' (moze byc zajete przez '+')
    for (int i=0; i<KWADRATY; i++)
        if (plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x+1] == '#' || plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x+1] == 'O')
            return false;   // nie mozna wykonac ruchu w prawo

    for (int i=0; i<KWADRATY; i++) // wyczyszczenie pol zajetych obecnie przez Klocki Obecny, Cien, przesuniecie kwadratow o 1 w prawo
    {
        plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
        plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
        (Obecny->kwadraty[i].x)++;
    }

    (Obecny->srodek.x)++;   // przesuniecie srodka o 1 w prawo

    for (int i=0; i<Obecny->m; i++) // przesuniecie zakazanych o 1 w prawo
        (Obecny->zakazane[i].x)++;

    for (int i=0; i<Obecny->n; i++) // przesuniecie siatki o 1 w prawo
        for (int j=0; j<Obecny->n; j++)
            (Obecny->siatka[i][j].x)++;

    return true;    // wykonano ruch w prawo
}

// funkcja pomocnicza, obracajaca punkt wzgledem srodka Klocka
void ObrotPunktuWzglSrodka (Pkt *p, Pkt sr)
{
    int xp, yp;
    xp = sr.x - sr.y + p->y;
    yp = sr.x + sr.y - p->x;
    p->x = xp;
    p->y = yp;
}

// obracanie Klocka Obecny o 90 stopni, zgodnie z ruchem wskazowek zegara (Cien przekazujemy tylko po to, by wymazac jego obecna pozycje)
bool Obrot(char plansza[WYS][SZER], Klocek *Obecny, Klocek *Cien)
{
    if (Obecny->m == 0) // jesli brak zakazanych klockow, to podany do funkcji Klocek jest typu Kw (Kwadrat), ktorego nie ma sensu obracac
        return false;

    Pkt sr;
    if (Obecny->n == 3)   // klocki z siatka 3x3
        sr.x = sr.y = 1;
    else    // klocek I z siatka 5x5
        sr.x = sr.y = 2;

    for (int i=0; i<Obecny->m; i++) // sprawdzenie, czy zakazane pola sa puste
        if (plansza[Obecny->zakazane[i].y][Obecny->zakazane[i].x] == '#' || plansza[Obecny->zakazane[i].y][Obecny->zakazane[i].x] == 'O')
            return false;   // nie mozna wykonac obrotu

    for (int i=0; i<KWADRATY; i++) // wyczyszczenie pol zajetych obecnie przez Klocki Obecny, Cien
    {
        plansza[Obecny->kwadraty[i].y][Obecny->kwadraty[i].x] = ' ';
        plansza[Cien->kwadraty[i].y][Cien->kwadraty[i].x] = ' ';
    }

    for (int i=0; i<KWADRATY; i++) // obrocenie kwadratow wzgledem srodka
    {
        Pkt pom = {Obecny->kwadraty[i].y - Obecny->siatka[0][0].y, Obecny->kwadraty[i].x - Obecny->siatka[0][0].x};
        ObrotPunktuWzglSrodka(&pom, sr);
        Obecny->kwadraty[i].x = Obecny->siatka[pom.x][pom.y].x;
        Obecny->kwadraty[i].y = Obecny->siatka[pom.x][pom.y].y;
    }
    for (int i=0; i<Obecny->m; i++) // obrocenie zakazanych wzgledem srodka
    {
        Pkt pom = {Obecny->zakazane[i].y - Obecny->siatka[0][0].y, Obecny->zakazane[i].x - Obecny->siatka[0][0].x};
        ObrotPunktuWzglSrodka(&pom, sr);
        Obecny->zakazane[i].x = Obecny->siatka[pom.x][pom.y].x;
        Obecny->zakazane[i].y = Obecny->siatka[pom.x][pom.y].y;
    }

    return true;    // wykonano obrot

}

// usuwanie calego wiersza z planszy i przesuwanie wszystkich '#' bedacych wyzej o 1 w dol
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

        if (plansza[wiersz-1][2] != 'O')    // przesuwanie wiersza wyzej (wiersz-1) o 1 w dol
            for (int j=2; j<12; j++)
                plansza[wiersz][j] = plansza[wiersz-1][j];
        else    // najwyzszy wiersz planszy - wyczysc wiersz, nie przestawiaj 'O' w dol
            for (int j=2; j<12; j++)
                plansza[wiersz][j] = ' ';

        wiersz--;
    }

}

// sprawdzanie, czy wiersze sa pelne (poczawszy od wiersza wiersz), i uruchamianie dla nich UsunWiersz, zwracanie true, jesli usunieto jakikolwiek wiersz, false wpp
bool SprawdzWiersze (char plansza[WYS][SZER], int wiersz, int *wynik, double predkosc)
{
    int licz = 0;
    bool usunieto = false;

    for (int i=wiersz; i<22; i++)
    {
        bool pelny = true;
        for (int j=2; j<12; j++) // sprawdzenie, czy wiersz pelny
            if (plansza[i][j] == ' ' || plansza[i][j] == 'O')
            {
                pelny = false;
                break;
            }
        if (pelny)
        {
            for (int j=2; j<12; j++)    // wstawienie 'x' w miejsce usuwanego wiersza
                plansza[i][j] = 'x';
            ReturnCursor();
            Rysuj(plansza, *wynik, predkosc);   // wyswietlenie 'xxxxxxxxxx' na 0.2 sekundy
            Sleep0_2Sec();
            usunieto = true;
            UsunWiersz(plansza, i); // usuwanie wiersza, doliczenie usunietego wiersz do zmiennej licz, wyswietlenie planszy po usunieciu tego wiersza
            licz++;
            ReturnCursor();
            Rysuj(plansza, *wynik, predkosc);
        }
    }
    *wynik += licz*licz*10; // dodawanie do wyniku kwoty (liczba usunietych wierszy)^2 * 10
    return usunieto;
}

// funkcja wywolywana po wybraniu START z menu lub po wybraniu RESTART w grze
void NowaGra(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny)
{
    ClearScreen();
    Inicjalizuj(plansza);
    *Cien = *Obecny = Losuj(tab); // wylosowanie Klocka Obecny
    while(!Spadek(plansza, Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
    WstawKlocek(plansza, *Obecny, *Cien); // wstawienie obu Klockow
    *wynik = 0;
    *predkosc = 1;
    *Nastepny = Losuj(tab);   // wylosowanie Klocka Nastepny
    WstawNastepny(plansza, *Obecny, *Nastepny);   // wstawienie go w prawy gorny rog planszy
    ReturnCursor();
    Rysuj(plansza, *wynik, *predkosc);
    *start = clock();
}

// funkcja wywolana po wcisnieciu znaku 'ESC'
void WykonajPauze(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny)
{
    char *opcja = Pauza(); // w zaleznosci od wyniku Pauza wyjscie z gry, resume, wyjscie do menu lub restart
    if (!strcmp(opcja, "EXIT"))
        exit(0);
    else if (!strcmp(opcja, "RESUME"))
    {
        ClearScreen();
        HideCursor();
        Rysuj(plansza, *wynik, *predkosc);
    }
    else if (!strcmp(opcja, "MENU"))
        Menu();
    if (!strcmp(opcja, "RESTART") || !strcmp(opcja, "MENU"))    // restart z menu lub pauzy
        NowaGra(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
}

// aktualizacja planszy po obrocie, ruchu w lewo lub prawo
void Aktualizuj(char plansza[WYS][SZER], int wynik, double predkosc, Klocek *Obecny, Klocek *Cien)
{
    *Cien = *Obecny;  // podstawienie Obecny pod Cien
    while(!Spadek(plansza, Cien, 1));  // przesuwanie Cienia w dol tak dlugo, jak to mozliwe
    WstawKlocek(plansza, *Obecny, *Cien); // wstawienie klockow
    ReturnCursor();
    Rysuj(plansza, wynik, predkosc);    // wyswietlenie planszy
}


// funkcja uruchamiana przy koncu gry - wczytywanie obecnego scoreboardu, dopisywanie nowego wyniku i wyswietlanie scoreboarda
void Scoreboard (int wynik)
{
    bool high_score = false;
    FILE *fp;   // wczytanie scoreboarda z pliku
    fp = fopen(SCORE, "r");

    int n;
    if (fp == NULL) // brak wynikow (plik ze scoreboardem nie istnieje) - wyswietlenie tylko nowo uzyskanego wyniku, zapisanie go do pliku
    {
        fclose(fp);
        fp = fopen(SCORE, "w");
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

        int pom, wyn_pom;
        int scores[10];

        for (int i=0; i<n; i++) // wpisanie top 10 wynikow do tablicy
        {
            fscanf(fp, "%d\n", &pom);
            scores[i] = pom;
        }
        fclose(fp); // zamkniecie pliku


        if (n<10)   // jesli scoreboard ma mniej niz 10 wynikow, zwieksz liczbe wynikow o 1 i wstaw -1 do ostatniego pola
        {
            n++;
            scores[n-1] = -1;
        }

        if (wynik > scores[0])  // nowy high score
        {
            wyn_pom = wynik;
            high_score = true;
        }

        for (int i=0; i<n; i++) // przeszukanie scoreboarda od najwyzszego do najnizszego wyniku
        {
            if (wynik > scores[i])  // jesli nowy wynik jest lepszy od scores[i], to wstaw go w to miejsce i przesun wszystkie nastepne o 1 w dol (ostatni wynik znika ze scoreboarda, lub zastepuje -1)
            {
                pom = wynik;
                wynik = scores[i];
                scores[i] = pom;
            }
        }

        if (high_score)
           printf("NEW HIGH SCORE!!! %d\n\n\n", wyn_pom);

        // otworzenie pliku .txt w celu wyswietlenia nowego scoreboarda i wpisania go do pliku
        fp = fopen(SCORE, "w");
        fprintf(fp, "%d\n", n);
        printf("SCOREBOARD\n\n");

        for (int i=0; i<n; i++)
        {
            fprintf(fp, "%d\n", scores[i]); // wpisanie do pliku
            printf("%2d. %d\n", i+1, scores[i]); // wypisanie na ekran
        }
        fclose(fp);
    }

}

// funkcja uruchamiana, gdy gra nie moze wstawic calego nowego klocka na gorze planszy
char* KoniecGry(char plansza[WYS][SZER], Klocek Obecny, int wynik, double predkosc)
{
    // wstawienie jeszcze '+' tam gdzie jest wolne pole, wyswietlenie tego, a nastepnie zastapienie '#' i ponowne wyswietlenie
    ReturnCursor();
    Rysuj(plansza, wynik, predkosc);
    Sleep1Sec();
    Spadek(plansza, &Obecny, 0);
    ReturnCursor();
    Rysuj(plansza, wynik, predkosc);
    Sleep1Sec();

    ClearScreen();
    printf("\nGAME OVER!\n\n\n");
    Scoreboard(wynik);  // wyswietlenie zaktualizowanego scoreboarda
    printf("\n\n[R]   RESTART\n[M]   MENU\n[ESC] EXIT");

    int znak;
    while (1)  // oczekiwanie na wejscie z klawiatury uzytkownika
    {
        if (kbhit())
        {
            znak = getch();
            if (znak == 'r')
                return "RESTART";
            else if (znak == 'm')
                return "MENU";
            else if (znak == ESC)
                return "EXIT";
        }
    }
}

// funkcja wywolywana gdy klocek Obecny spadnie na sam dol
void NaDole(char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny)
{
    if (SprawdzWiersze(plansza, Obecny->srodek.y - 2, wynik, *predkosc))    // sprawdzenie, czy sa pelne wiersze (od wiersza rownego srodek klocka, ktory spadl - 2)
    {
        *start = clock();
        ReturnCursor();
        Rysuj(plansza, *wynik, *predkosc);
    }
    *Cien = *Obecny = *Nastepny;   // Obecny i Cien staja sie Nastepnym
    while(!Spadek(plansza, Cien, 1));
    if (!WstawKlocek(plansza, *Obecny, *Cien))    // jesli gra nie moze wstawic nowego klocka na gore planszy, to koniec gry
    {
        char* opcja = KoniecGry(plansza, *Obecny, *wynik, *predkosc);
        if (!strcmp(opcja, "EXIT"))
            exit(0);
        else if (!strcmp(opcja, "MENU"))
            Menu();
        else if (!strcmp(opcja, "RESTART"))
            NowaGra(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
    }
    else    // w przeciwnym wypadku losuj nowy klocek
    {
        *Nastepny = Losuj(tab);  // losowanie Klocka Nastepny i wstawienie go w prawy gorny rog planszy
        WstawNastepny(plansza, *Obecny, *Nastepny);
    }
}

// funkcja wykonujaca ruch wg przekazanego jako argument znaku
void Wykonaj(int znak, char plansza[WYS][SZER], const Klocek tab[TYPY], int *wynik, double *predkosc, clock_t *start, Klocek *Obecny, Klocek *Cien, Klocek *Nastepny)
{
    switch(znak)
    {
    case ESC:
        WykonajPauze(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
        break;
    case 'w':   // obrot
        if (Obrot(plansza, Obecny, Cien)) // obrocenie klocka Obecny (jesli to mozliwe - wtedy true)
            Aktualizuj(plansza, *wynik, *predkosc, Obecny, Cien);
        break;
    case 'a':   // lewo
        if (Lewo(plansza, Obecny, Cien))  // przesuniecie klocka Obecny o 1 w lewo (jesli to mozliwe - wtedy true)
            Aktualizuj(plansza, *wynik, *predkosc, Obecny, Cien);
        break;
    case 'd':   // prawo
        if (Prawo(plansza, Obecny, Cien)) // przesuniecie klocka Obecny o 1 w prawo (jesli to mozliwe - wtedy true)
            Aktualizuj(plansza, *wynik, *predkosc, Obecny, Cien);
        break;
    case 's':   // dol
        if (Spadek(plansza, Obecny, 0))    // wywolanie spadek, true jezeli klocek spadl na sam dol
            NaDole(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
        else    // klocek nie spadl na sam dol, wtedy wstaw Klocki Obecny i Cien i odswiez plansze
            WstawKlocek(plansza, *Obecny, *Cien);
        ReturnCursor();
        Rysuj(plansza, *wynik, *predkosc);
        break;
    case ENTER: // na sam dol
        while (!Spadek(plansza, Obecny, 0));   // przesuwanie klocka Obecny w dol tak dlugo, jak to mozliwe
        NaDole(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
        ReturnCursor();
        Rysuj(plansza, *wynik, *predkosc);
        break;
    case AUTO:  // automatyczny spadek klocka
        if (Spadek(plansza, Obecny, 0))    // wywolanie spadek, true jezeli klocek spadl na sam dol
            NaDole(plansza, tab, wynik, predkosc, start, Obecny, Cien, Nastepny);
        else
            WstawKlocek(plansza, *Obecny, *Cien);
        ReturnCursor();
        break;
    }
}
