#ifndef PLAYER_H
#define PLAYER_H

#include "domino.h"
#include "game.h"

typedef struct{
    T_Area *area;
    int points;
    int  playerNumber;
    char *Name;
} T_player;

unsigned int Player_GetNbrJoueur();

#endif