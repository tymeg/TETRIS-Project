#ifndef BLOCKS_H_INCLUDED
#define BLOCKS_H_INCLUDED

#define WYS 22
#define SZER 12

typedef struct
{
    int x, y;
} Pkt;

typedef struct
{
    int m;
    Pkt srodek;
    Pkt kwadraty[4];
    Pkt zakazane[8];

} Klocek;

#endif // BLOCKS_H_INCLUDED
