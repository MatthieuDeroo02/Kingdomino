#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "domino.h"
#include "render.h"
#include <stdlib.h>
#include <SDL3/SDL.h>

typedef struct{
    T_Square *square;
} T_Area;

typedef struct{
    T_Area *area;
    int points;
    int  playerNumber;
    char *Name;
} T_player;

void Game_NewGame(); //lance une nouvelle partie
void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer); //Arreter la partie

#endif