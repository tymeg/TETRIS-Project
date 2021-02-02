#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

// definicje makr
#define WYS 24  // rozmiar planszy
#define SZER 21

#define KWADRATY 4    // liczba kwadratow skladajacych sie na kazdy klocek
#define TYPY 7  // liczba typow klockow

#define SCORE "score.txt"   // plik do zapisywania scoreboardu

#define ESC 27  // numery klawiszy na Windowsie
#define ENTER 13

// struktura Pkt
typedef struct
{
    int x, y;
} Pkt;

// struktura Klocek
typedef struct
{
    int n; // dlugosc boku siatki
    int m; // ilosc zakazanych pol
    Pkt srodek;
    Pkt kwadraty[KWADRATY];
    Pkt zakazane[3]; // punkty, ktore musza byc wolne przy obrocie klocka
    Pkt siatka[5][5]; // lokalny uklad wspolrzednych klocka, potrzebny do dzialania funkcji Obrot
    // poszczegolne pola siatki przechowuja Punkty, ktorym odpowiadaja na planszy

} Klocek;

#endif // BLOCKS_H_INCLUDED
