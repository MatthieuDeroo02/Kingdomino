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
        Game_EndGame(window, renderer, 2);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);

    if (!texture) {
        SDL_Log("Erreur création texture : %s", SDL_GetError());
        Game_EndGame(window, renderer, 2);
    }

    return texture;
}


/*
unsigned int Render_AfficherLobby(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_Texture *fond = Render_LoadAndConvertImage("assets/images/fond_ecran_lobby2.bmp", window, renderer); //Crée la texture du fond d'ecran

    int largeur, hauteur;
    SDL_GetRenderOutputSize(renderer, &largeur, &hauteur);
    T_Button button2Player = Render_AddButton(renderer, "assets/images/button2player.png", 0.281*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur); //Importe les Buttons utilisé lors
    T_Button button3Player = Render_AddButton(renderer, "assets/images/button3player.png", 0.441*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);
    T_Button button4Player = Render_AddButton(renderer, "assets/images/button4player.png", 0.602*largeur, 0.417*hauteur, 0.117*largeur, 0.303*hauteur);


    while (true) {
        SDL_Event event; //Contient les événement SDL
        while (SDL_PollEvent(&event)) { //Remplie avec le prochain evenement
            if (event.type == SDL_EVENT_QUIT) {
                return 0;
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) { // Si un des bouton de la souris a été relaché
                if (event.button.button == SDL_BUTTON_LEFT) { //Si c'est le bouton gauche de la souris
                    if (Render_ButtonOverhead(button2Player)) {
                        return 2;
                    } else if (Render_ButtonOverhead(button3Player)) {
                        return 3;
                    } else if (Render_ButtonOverhead(button4Player)) {
                        return 4;
                    }
                }
            }
        }

        SDL_GetRenderOutputSize(renderer, &largeur, &hauteur); //Récupère 
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

        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, fond, NULL, NULL);  // dessine l'image en plein écran
        SDL_RenderTexture(renderer, button2Player.texture, NULL, &button2Player.rectangle);
        SDL_RenderTexture(renderer, button3Player.texture, NULL, &button3Player.rectangle);
        SDL_RenderTexture(renderer, button4Player.texture, NULL, &button4Player.rectangle);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(button2Player.texture);
    SDL_DestroyTexture(button3Player.texture);
    SDL_DestroyTexture(button4Player.texture);

    return 0;
}
*/


void Render_AddButton(T_Assets* assets, SDL_Renderer *renderer,const char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY) {
    assets->listButton = realloc(assets->listButton, (assets->nbrButton+1) * sizeof(T_Button));
    assets->listButton[assets->nbrButton].overhead = 0;
    assets->listButton[assets->nbrButton].name = name;
    assets->listButton[assets->nbrButton].rectangle.x = positionX;
    assets->listButton[assets->nbrButton].rectangle.y = positionY;
    assets->listButton[assets->nbrButton].rectangle.w = sizeX;
    assets->listButton[assets->nbrButton].rectangle.h = sizeY;
    assets->listButton[assets->nbrButton].texture = IMG_LoadTexture(renderer, cheminImage);
    assets->nbrButton++;
}

void Render_AddWallpaper(T_Assets* assets, SDL_Renderer *renderer, const char *cheminImage) {
    assets->wallpaper.texture = IMG_LoadTexture(renderer, cheminImage);
}

void Render_ResetAllAssets(T_Assets* assets) {
    //Detruit le fond ecran
    SDL_DestroyTexture(assets->wallpaper.texture);
    //Detruit les buttons
    for (unsigned int i=0; i<assets->nbrButton; i++) {
        SDL_DestroyTexture(assets->listButton[i].texture);
    }
    free(assets->listButton);
    assets->nbrButton = 0;
    //Detruit les images
    for (unsigned int i=0; i<assets->nbrOverlay; i++) {
        SDL_DestroyTexture(assets->listOverlay[i].texture);
    }
    free(assets->listOverlay);
    assets->nbrOverlay = 0;
}

void Render_AddOverlay(T_Assets* assets, SDL_Renderer *renderer,const char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY) {
    assets->listOverlay = realloc(assets->listOverlay, (assets->nbrOverlay+1) * sizeof(T_Overlay));
    assets->listOverlay[assets->nbrOverlay].name = name;
    assets->listOverlay[assets->nbrOverlay].rectangle.x = positionX;
    assets->listOverlay[assets->nbrOverlay].rectangle.y = positionY;
    assets->listOverlay[assets->nbrOverlay].rectangle.w = sizeX;
    assets->listOverlay[assets->nbrOverlay].rectangle.h = sizeY;
    assets->listOverlay[assets->nbrOverlay].texture = IMG_LoadTexture(renderer, cheminImage);
    assets->nbrOverlay++;
}

bool Render_ButtonOverhead(T_Button button) {
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (button.rectangle.x <= mouseX && mouseX <= button.rectangle.x + button.rectangle.w && button.rectangle.y <= mouseY && mouseY <= button.rectangle.y + button.rectangle.h) {
        return true;
    }
    return false;
}

void Render_ChangeSizeAndPosition(T_Button *button, float positionX, float positionY, float sizeX, float sizeY) {
    button->rectangle.x = positionX;
    button->rectangle.y = positionY;
    button->rectangle.w = sizeX;
    button->rectangle.h = sizeY;
}

void Render_IncreasesButtonSize(T_Button *button, float factor) {
    float tmpSizeX = button->rectangle.w;
    float tmpSizeY = button->rectangle.h;

    button->rectangle.w *= factor;
    button->rectangle.h *= factor;

    button->rectangle.x -= (button->rectangle.w - tmpSizeX)/2;
    button->rectangle.y -= (button->rectangle.h - tmpSizeY)/2;
}

SDL_Texture *Render_GenerateGeneralGameBoard(SDL_Renderer *renderer) {
    SDL_Texture *wallpaper = IMG_LoadTexture(renderer, "assets/images/InGameWallpaper.png");
    return wallpaper;
}

void Render_AnimateCloudCurtain(SDL_Window *window, SDL_Renderer *renderer,SDL_Texture *wallpaper, unsigned int nbrFrame, bool hidden) {
    SDL_Texture *cloud_right_texture = IMG_LoadTexture(renderer, "assets/images/cloud_Right.png");
    SDL_Texture *cloud_left_texture = IMG_LoadTexture(renderer, "assets/images/cloud_Left.png");

    int largeur_nuage = 1280;

    int largeur_window, hauteur_window;
    SDL_GetRenderOutputSize(renderer, &largeur_window, &hauteur_window);

    float position_cloud_left, position_cloud_right, final_position_cloud_left, final_position_cloud_right;
    if (hidden == true) {
        position_cloud_left = -largeur_nuage;
        position_cloud_right = largeur_window;
        final_position_cloud_left = largeur_window/2 - largeur_nuage;
        final_position_cloud_right = largeur_window/2;
    } else {
        final_position_cloud_left = -largeur_nuage;
        final_position_cloud_right = largeur_window;
        position_cloud_left = largeur_window/2 - largeur_nuage;
        position_cloud_right = largeur_window/2;
    }

    for (int i=0; i<nbrFrame; i++) {
        //On calcule la vitesse du nuage
        float vitesse_cloud_left = (final_position_cloud_left - position_cloud_left)/(nbrFrame-i);
        float vitesse_cloud_right = (final_position_cloud_right - position_cloud_right)/(nbrFrame-i);
        
        //On calcule la prochaine position du nuage
        position_cloud_left += vitesse_cloud_left;
        position_cloud_right += vitesse_cloud_right;

        //on affiche
        SDL_FRect rectangle_cloud_left = {position_cloud_left-largeur_nuage,-10, largeur_nuage, hauteur_window+20}; //x, y, w, h
        SDL_FRect rectangle_cloud_right = {position_cloud_right,-10, largeur_nuage, hauteur_window+20};

        SDL_RenderTexture(renderer, wallpaper, NULL, NULL);
        SDL_RenderTexture(renderer, cloud_right_texture, NULL, &rectangle_cloud_right);
        SDL_RenderTexture(renderer, cloud_left_texture, NULL, &rectangle_cloud_left);

        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // ~60 FPS
    }
    SDL_DestroyTexture(cloud_left_texture);
    SDL_DestroyTexture(cloud_right_texture);
}