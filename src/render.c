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

    int largeur, hauteur;
    SDL_GetRenderOutputSize(renderer, &largeur, &hauteur);
    T_Button button2Player = Render_AddButton(renderer, "assets/images/Button2player.png", 0.281*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur); //Importe les Buttons utilisé lors
    T_Button button3Player = Render_AddButton(renderer, "assets/images/Button3player.png", 0.441*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);
    T_Button button4Player = Render_AddButton(renderer, "assets/images/Button4player.png", 0.602*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);


    int running = 1;
    while (running) {
        SDL_Event event; //Contient les événement SDL
        while (SDL_PollEvent(&event)) { //Remplie avec le prochain evenement
            if (event.type == SDL_EVENT_QUIT) {
                running = 0;
            }
        }

        SDL_GetRenderOutputSize(renderer, &largeur, &hauteur);
        Render_ChangeSizeAndPosition(&button2Player, 0.281*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);
        Render_ChangeSizeAndPosition(&button3Player, 0.441*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);
        Render_ChangeSizeAndPosition(&button4Player, 0.602*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);

        if (Render_ButtonOverhead(button2Player)) {
            Render_IncreasesButtonSize(&button2Player, 1.2);
        } else if (Render_ButtonOverhead(button3Player)) {
            Render_IncreasesButtonSize(&button3Player, 1.2);
        } else if (Render_ButtonOverhead(button4Player)) {
            Render_IncreasesButtonSize(&button4Player, 1.2);
        }
        
        printf("posX : %3.f; ", button2Player.rectangle.x);
        printf("posY : %3.f; ", button2Player.rectangle.y);
        printf("sizeX : %3.f; ", button2Player.rectangle.w);
        printf("sizeY : %3.f\n", button2Player.rectangle.h);
        printf("chemin image : %s", button2Player.cheminImage);

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, fond, NULL, NULL);  // dessine l'image en plein écran
        SDL_RenderTexture(renderer, button2Player.texture, NULL, &button2Player.rectangle);
        SDL_RenderTexture(renderer, button3Player.texture, NULL, &button3Player.rectangle);
        SDL_RenderTexture(renderer, button4Player.texture, NULL, &button4Player.rectangle);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyRenderer(renderer);
}


T_Button Render_AddButton(SDL_Renderer *renderer, char *cheminImage, float sizeX, float sizeY, float positionX, float positionY) {
    T_Button button;
    button.overhead = 0;
    button.cheminImage = cheminImage;
    button.rectangle.x = sizeX;
    button.rectangle.y = sizeY;
    button.rectangle.w = positionX;
    button.rectangle.h = positionY;
    button.texture = IMG_LoadTexture(renderer, cheminImage);
    return button;
}

bool Render_ButtonOverhead(T_Button button) {
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (button.rectangle.x <= mouseX && mouseX <= button.rectangle.x + button.rectangle.w && button.rectangle.y <= mouseX && mouseY <= button.rectangle.y + button.rectangle.h) {
        return true;
    }
    return false;
}

void Render_ChangeSizeAndPosition(T_Button *button, float sizeX, float sizeY, float positionX, float positionY) {
    button->rectangle.x = sizeX;
    button->rectangle.y = sizeY;
    button->rectangle.w = positionX;
    button->rectangle.h = positionY;
}

void Render_IncreasesButtonSize(T_Button *button, float factor) {
    int tmpX = button->rectangle.x;
    int tmpY = button->rectangle.y;

    button->rectangle.x *= factor;
    button->rectangle.y *= factor;

    button->rectangle.w += button->rectangle.x - tmpX;
    button->rectangle.h += button->rectangle.y - tmpY;
}