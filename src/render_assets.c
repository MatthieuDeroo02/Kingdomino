#include "render.h"

T_Assets Render_CreatAssets() {
    T_Assets assets;
    assets.wallpaper.texture = NULL;
    assets.nbrButton = 0;
    assets.listButton = NULL;
    assets.nbrOverlay = 0;
    assets.listOverlay = NULL;
    return assets;
}

void Render_AddButton(T_Assets* assets, SDL_Renderer *renderer, char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY, float over_scale) {
    assets->listButton = realloc(assets->listButton, (assets->nbrButton+1) * sizeof(T_Button));
    assets->listButton[assets->nbrButton].overhead = 0;
    assets->listButton[assets->nbrButton].name = name;
    assets->listButton[assets->nbrButton].posX = positionX;
    assets->listButton[assets->nbrButton].posY = positionY;
    assets->listButton[assets->nbrButton].largeur = sizeX;
    assets->listButton[assets->nbrButton].hauteur = sizeY;
    assets->listButton[assets->nbrButton].over_scale = over_scale;
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

void Render_AddOverlay(T_Assets* assets, SDL_Renderer *renderer, char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY) {
    assets->listOverlay = realloc(assets->listOverlay, (assets->nbrOverlay+1) * sizeof(T_Overlay));
    assets->listOverlay[assets->nbrOverlay].name = name;
    assets->listOverlay[assets->nbrOverlay].posX = positionX;
    assets->listOverlay[assets->nbrOverlay].posY = positionY;
    assets->listOverlay[assets->nbrOverlay].largeur = sizeX;
    assets->listOverlay[assets->nbrOverlay].hauteur = sizeY;
    assets->listOverlay[assets->nbrOverlay].texture = IMG_LoadTexture(renderer, cheminImage);
    assets->nbrOverlay++;
}

void Render_DestroyButton(T_Assets *assets, const char *name) {
    for (unsigned int i=0; i<assets->nbrButton; i++) {
        if (strcmp(assets->listButton[i].name, name)==0) {
            SDL_DestroyTexture(assets->listButton[i].texture);
            free(assets->listButton[i].name);
            for (unsigned int j=i; j<assets->nbrButton; j++) {
                assets->listButton[j]=assets->listButton[j+1];
            }
            assets->nbrButton--;
            assets->listButton=realloc(assets->listButton, assets->nbrButton*sizeof(T_Button));
            return;
        }
    }
}

void Render_RenderScene(SDL_Window *window, SDL_Renderer *renderer, T_Assets *assets) {
    int largeur_window, hauteur_window;
    SDL_GetRenderOutputSize(renderer, &largeur_window, &hauteur_window);

    SDL_RenderClear(renderer);
    
    SDL_RenderTexture(renderer, assets->wallpaper.texture, NULL, NULL);

    for (unsigned int i=0; i<assets->nbrOverlay; i++) {
        SDL_FRect rectangle;
        rectangle.x = largeur_window * assets->listOverlay[i].posX;
        rectangle.y = hauteur_window * assets->listOverlay[i].posY;
        rectangle.w = largeur_window * assets->listOverlay[i].largeur;
        rectangle.h = hauteur_window * assets->listOverlay[i].hauteur;
        SDL_RenderTexture(renderer, assets->listOverlay[i].texture, NULL, &rectangle);
    }
    
    for (unsigned int i=0; i<assets->nbrButton; i++) {
        SDL_FRect rectangle;
        if (Render_ButtonOverhead(renderer, &assets->listButton[i])==true) {
            rectangle.w = assets->listButton[i].largeur * largeur_window * assets->listButton[i].over_scale;
            rectangle.h = assets->listButton[i].hauteur * hauteur_window * assets->listButton[i].over_scale;
            rectangle.x = assets->listButton[i].posX * largeur_window - ((rectangle.w - assets->listButton[i].largeur * largeur_window)/2);
            rectangle.y = assets->listButton[i].posY * hauteur_window - ((rectangle.h - assets->listButton[i].hauteur * hauteur_window)/2);
        } else {
            rectangle.x = largeur_window * assets->listButton[i].posX;
            rectangle.y = hauteur_window * assets->listButton[i].posY;
            rectangle.w = largeur_window * assets->listButton[i].largeur;
            rectangle.h = hauteur_window * assets->listButton[i].hauteur;
        }

        SDL_RenderTexture(renderer, assets->listButton[i].texture, NULL, &rectangle);
    }
    SDL_RenderPresent(renderer);
}