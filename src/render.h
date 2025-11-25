#ifndef RENDER_H
#define RENDER_H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char *name;
    bool overhead;
    float over_scale;
    float posX;
    float posY;
    float largeur;
    float hauteur;
    SDL_Texture *texture;
} T_Button;

typedef struct {
    SDL_Texture *texture;
} T_Wallpaper;

typedef struct {
    char *name;
    SDL_Texture *texture;
    float posX;
    float posY;
    float largeur;
    float hauteur;
    //SDL_FRect rectangle;
} T_Overlay;

typedef struct {
    T_Wallpaper wallpaper;
    T_Button *listButton;
    unsigned int nbrButton;
    T_Overlay *listOverlay;
    unsigned int nbrOverlay;
} T_Assets;


/*
typedef struct{
    char* PictureObjectName;

    T_Button* PtrOf_PictureObject;
} ItemOf_PictureObject

ItemOf_PictureObject ** ArrayOf_PictureObject;

ItemOf_PictureObject* get_PictureObject(char* get_PictureObjectName);
void add_PictureObject(char * new_PictureObjectName, T_Button* New_PtrOf_PictureObject)
*/


/*Initialise SDL video*/
void Render_InitVideo();
/*Crée la fenetre*/
SDL_Window *Render_Creat_Window(const char *windowTitle, unsigned int sizeX, unsigned int sizeY);
/*Crée le moteur grapique*/
SDL_Renderer *Render_CreatRenderer(SDL_Window *window);
/*Crée le stockage des assets*/
T_Assets Render_CreatAssets();


/*affiche le lobby et retourne le nombre de joueur choisie*/
//unsigned int Render_AfficherLobby(SDL_Window *window, SDL_Renderer *renderer);


/*Crée un Button et l'ajoute au assets qui pouras etre utilisé plus tard*/
void Render_AddButton(T_Assets* assets, SDL_Renderer *renderer, char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY, float over_scale);
/*Crée un Overlay et l'ajoute au assets qui pouras etre utilisé plus tard*/
void Render_AddOverlay(T_Assets* assets, SDL_Renderer *renderer, char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY);
/*Crée le fond ecran, suprimme l'ancien et l'ajoute aux assets*/
void Render_AddWallpaper(T_Assets* assets, SDL_Renderer *renderer, const char *cheminImage);
/*Reset l'entiereter des assets*/
void Render_ResetAllAssets(T_Assets* assets);
/*Detruit le bouton demander*/
void Render_DestroyButton(T_Assets *assets, const char *name);
/*Génère et affiche la scene*/
void Render_RenderScene(SDL_Window *window, SDL_Renderer *renderer, T_Assets *assets);



/*Returne true si le Button est survolé et change le overhead*/
bool Render_ButtonOverhead(SDL_Renderer *renderer, T_Button* button);

/*Controlle la fermeture des rideau de nuage en 60fps*/
void Render_AnimateCloudCurtain(SDL_Window *window, SDL_Renderer *renderer,SDL_Texture *wallpaper, unsigned int nbrFrame, bool hidden);

/*Crée une texture a partire ce qu'il y a à l'ecran*/
SDL_Texture *Render_CaptureScreen(SDL_Renderer *renderer);

/*Change la taille et la position d'un bouton*/
//void Render_ChangeSizeAndPosition(T_Button *button, float positionX, float positionY, float sizeX, float sizeY);
/*Augmente la taille et ajuste la position selon le facteur de grossissement*/
//void Render_IncreasesButtonSize(T_Button *button, float factor);
/*passe du lobby au plateau de jeu*/
//void Render_StartGame(SDL_Window *window, SDL_Renderer *renderer, unsigned int nbrJoueurs);
/*Retourne la tableau avec toute les textures de l'aires de jeu*/
//SDL_Texture *Render_GenerateTexture();
/*Genere la plateau de jeu basique avec le fond et les 4 royaume des chateau*/
//SDL_Texture *Render_GenerateGeneralGameBoard(SDL_Renderer *renderer);
#endif