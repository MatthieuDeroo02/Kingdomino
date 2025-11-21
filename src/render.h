#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

typedef struct{
    const char *cheminImage;
    bool overhead;
    SDL_FRect rectangle;
    SDL_Texture *texture;
} T_Button;


/*Initialise SDL video*/
void Render_InitVideo();
/*Crée la fenetre*/
SDL_Window *Render_Creat_Window(const char *windowTitle, unsigned int sizeX, unsigned int sizeY);
/*Crée le moteur grapique*/
SDL_Renderer *Render_CreatRenderer(SDL_Window *window);
/*Charge et compile une image*/
SDL_Texture *Render_LoadAndConvertImage(const char *cheminImage, SDL_Window *window, SDL_Renderer *renderer);

/*affiche le lobby et retourne le nombre de joueur choisie*/
unsigned int Render_AfficherLobby(SDL_Window *window, SDL_Renderer *renderer);

/*Crée un Button qui pouras etre utilisé plus tard*/
T_Button Render_AddButton(SDL_Renderer *renderer, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY);
/*Returne true si le Button est survolé*/
bool Render_ButtonOverhead(T_Button button);
//*Change la taille et la position d'un bouton*/
void Render_ChangeSizeAndPosition(T_Button *button, float positionX, float positionY, float sizeX, float sizeY);
/*Augmente la taille et ajuste la position selon le facteur de grossissement*/
void Render_IncreasesButtonSize(T_Button *button, float factor);
/*passe du lobby au plateau de jeu*/
void Render_StartGame(SDL_Window *window, SDL_Renderer *renderer, unsigned int nbrJoueurs);
/*Retourne la tableau avec toute les textures de l'aires de jeu*/
SDL_Texture *Render_GenerateTexture();
/*Genere la plateau de jeu basique avec le fond et les 4 royaume des chateau*/
SDL_Texture *Render_GenerateGeneralGameBoard(SDL_Renderer *renderer);
/*Controlle la fermeture des rideau de nuage en 60fps*/
void Render_AnimateCloudCurtain(SDL_Window *window, SDL_Renderer *renderer,SDL_Texture *wallpaper, unsigned int nbrFrame, bool hidden);
#endif