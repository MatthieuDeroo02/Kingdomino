#ifndef PLAYER_H
#define PLAYER_H

#include "domino.h"

typedef struct{
    T_Square *area;
} T_Area;

typedef struct{
    T_Area *area;
    int points;
    int  playerNumber;
    char *Name;
} T_player;

#endif