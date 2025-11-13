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
    SDL_Texture *fond = Render_LoadAndConvertImage("assets/images/fond_ecran_lobby2.bmp", window, renderer); //Crée la texture du fond d'ecran

    T_Button Button2Player = Render_AddButton(renderer, "assets/images/Button2player.png", 350, 510, 0, 0); //Importe les Buttons utilisé lors
    T_Button Button3Player = Render_AddButton(renderer, "assets/images/Button3player.png", 350, 510, 0, 0);
    T_Button Button4Player = Render_AddButton(renderer, "assets/images/Button4player.png", 350, 510, 0, 0);


    int running = 1;
    while (running) {
        SDL_Event event; //Contient les événement SDL
        while (SDL_PollEvent(&event)) { //Remplie avec le prochain evenement
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        int largeur, hauteur;
        SDL_GetRenderOutputSize(renderer, &largeur, &hauteur);


        //SDL_FRect Button2Player ={ 0.281*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur};
        //SDL_FRect Button3Player ={ 0.441*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur};
        //SDL_FRect Button4Player ={ 0.602*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur};


        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, fond, NULL, NULL);  // dessine l'image en plein écran
        SDL_RenderTexture(renderer, Button2Player.texture, NULL, &Button2Player.rectangle);
        SDL_RenderTexture(renderer, Button3Player.texture, NULL, &Button3Player.rectangle);
        SDL_RenderTexture(renderer, Button4Player.texture, NULL, &Button4Player.rectangle);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(renderer);
}


T_Button Render_AddButton(SDL_Renderer *renderer, const char *cheminImage, float sizeX, float sizeY, float positionX, float positionY) {
    T_Button Button;
    Button.overhead = 0;
    Button.cheminImage = cheminImage;
    Button.rectangle.x = sizeX;
    Button.rectangle.y = sizeY;
    Button.rectangle.w = positionX;
    Button.rectangle.h = positionY;
    Button.texture = IMG_LoadTexture(renderer, cheminImage);
    return Button;
}

bool Render_ButtonOverhead(T_Button button) {
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (button.rectangle.x <= mouseX && mouseX <= button.rectangle.x + button.rectangle.w && button.rectangle.y <= mouseX && mouseY <= button.rectangle.y + button.rectangle.h) {
        return true;
    }
    return false;
}