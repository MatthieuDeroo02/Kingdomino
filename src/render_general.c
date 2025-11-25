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

SDL_Texture *Render_CaptureScreen(SDL_Renderer *renderer) {
    int largeur_window, hauteur_window;
    SDL_GetRenderOutputSize(renderer, &largeur_window, &hauteur_window);

    SDL_Rect rect = {0, 0, largeur_window, hauteur_window}; //definit la zone a capturer

    SDL_Surface *surface = SDL_RenderReadPixels(renderer, &rect);
    

    return SDL_CreateTextureFromSurface(renderer, surface);
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




bool Render_ButtonOverhead(SDL_Renderer *renderer, T_Button* button) {
    int largeur_window, hauteur_window;
    SDL_GetRenderOutputSize(renderer, &largeur_window, &hauteur_window);
    float mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);
    if (button->posX*largeur_window <= mouseX && mouseX <= (button->posX + button->largeur)*largeur_window && button->posY*hauteur_window <= mouseY && mouseY <= (button->posY+button->hauteur)*hauteur_window) {
        button->overhead=true;    
        return true;
    }
    button->overhead=false;
    return false;
}

/*
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
*/

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