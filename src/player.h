#ifndef PLAYER_H
#define PLAYER_H

#include "domino.h"
#include "game.h"

/*
typedef struct{
    T_Square *square;
} T_Area;
 */

typedef struct{
    //T_Area area;
    T_Square *area;
    unsigned int points;
    const char *Name;
} T_Player;

T_Player *Player_GeneratePlayers(unsigned int nbrPlayer);

#endif