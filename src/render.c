#include "render.h"

void Render_InitVideo() {
    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Log("Erreur SDL_Init : %s", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Window *Render_Creat_Window(const char *windowTitle, unsigned int sizeX, unsigned int sizeY) {
    SDL_Window *window = SDL_CreateWindow(windowTitle, sizeX, sizeY, SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Log("Erreur création fenêtre : %s", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return window;
}


SDL_Renderer *Render_CreatRenderer(SDL_Window *window) {
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);
    if (!renderer) {
        SDL_Log("Erreur création renderer : %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    return renderer;
}

SDL_Texture *Render_LoadAndConvertImage(const char *cheminImage, SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Surface *surface = SDL_LoadBMP(cheminImage);
    if (!surface) {
        SDL_Log("Erreur chargement image : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Erreur création texture : %s", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    return texture;
}

void Render_AfficherLobby(SDL_Window *window) {
    SDL_Renderer *renderer = Render_CreatRenderer(window); //Crée le moteur graphique du lobby
    SDL_Texture *texture = Render_LoadAndConvertImage("assets/images/fond_ecran_lobby2.bmp", window, renderer);

    int running = 1;
    while (running) {
        SDL_Event event; //Contient les événement SDL
        while (SDL_PollEvent(&event)) { //Remplie avec le prochain evenement
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);  // dessine l'image en plein écran
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}