#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#define WYS 24
#define SZER 14

typedef struct
{
    int x, y;
} Pkt;

typedef struct
{
    int n; // dlugosc boku siatki
    int m; // ilosc zakazanych pol
    Pkt srodek;
    Pkt kwadraty[4];
    Pkt zakazane[8];
    Pkt siatka[5][5];

} Klocek;

#endif // BLOCKS_H_INCLUDED
