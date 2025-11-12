#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include <stdlib.h>
#include "game.h"

/*Initialise SDL video*/
void Render_InitVideo();
/*Crée la fenetre*/
SDL_Window *Render_Creat_Window(const char *windowTitle, unsigned int sizeX, unsigned int sizeY);
/*Crée le moteur grapique*/
SDL_Renderer *Render_CreatRenderer(SDL_Window *window);
/*Charge et compile une image*/
SDL_Texture *Render_LoadAndConvertImage(const char *cheminImage, SDL_Window *window, SDL_Renderer *renderer);



/*affiche le lobby*/
void Render_AfficherLobby(SDL_Window *window);


#endif