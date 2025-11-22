#include <render.h>

void Render_AddButton(T_Assets* assets, SDL_Renderer *renderer,const char *name, const char *cheminImage, float positionX, float positionY, float sizeX, float sizeY, float over_scale) {
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