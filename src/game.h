#ifndef GAME_H
#define GAME_H

#include <stdlib.h>
#include <SDL3/SDL.h>
#include "player.h"
#include "domino.h"
#include "render.h"

#define sizeArea 7

/*Lance une nouvelle partie*/
void Game_NewGame();
/*Arrete la partie en cours, Close : 0->continue, 1->Exit_Success, 2->Exit_Failure*/
void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer, T_Assets* assets, unsigned int Close);

/*Fonction du lobby*/
void Game_Lobby(SDL_Window *window, SDL_Renderer *renderer, T_Assets assets, unsigned int* nbrJoueur);

/*Return le nom du boutton pressé*/
char *Game_ButtonPressed(const T_Assets *assets);

/*Genere les aire de jeu en debut de partie*/
T_Square* Game_GenerateArea();
/*Genere un square vide sans couronne*/
T_Square Game_GenerateBasiqueSquare();
/*accéde au numero de la case en X/Y*/
unsigned int Game_GetIndiceInArea(unsigned int posX, unsigned int posY);
#endif