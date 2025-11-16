#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "domino.h"
#include <stdlib.h>

typedef struct{
    T_Square *square;
} T_Area;

typedef struct{
    T_Area *area;
    int points;
    int  playerNumber;
    char *Name;
} T_player;



#endif