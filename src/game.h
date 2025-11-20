#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "domino.h"
#include "render.h"
#include <stdlib.h>
#include <SDL3/SDL.h>

#define sizeArea 7

/*Lance une nouvelle partie*/
void Game_NewGame();
/*Arrete la partie en cours*/
void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer);



/*Genere les aire de jeu en debut de partie*/
T_Square* Game_GenerateArea();
/*Genere un square vide sans couronne*/
T_Square Game_GenerateBasiqueSquare();
/*accéde au numero de la case en X/Y*/
unsigned int Game_GetIndiceInArea(unsigned int posX, unsigned int posY);
#endif