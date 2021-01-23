#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

// definicja makr - rozmiaru planszy
#define WYS 24
#define SZER 21

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
    Pkt kwadraty[4];
    Pkt zakazane[3]; // punkty, ktore musza byc wolne przy obrocie klocka
    Pkt siatka[5][5]; // lokalny uklad wspolrzednych klocka, potrzebny do dzialania funkcji Obrot
    // poszczegolne pola siatki przechowuja Punkty, ktorym odpowiadaja na planszy

} Klocek;

#endif // BLOCKS_H_INCLUDED
