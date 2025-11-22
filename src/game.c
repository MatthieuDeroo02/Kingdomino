#include "game.h"

void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer, T_Assets* assets, unsigned int Close) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Render_ResetAllAssets(assets);
    SDL_Quit();
    if (Close == 1) exit(EXIT_SUCCESS);
    if (Close == 2) exit(EXIT_FAILURE);
}

T_Square* Game_GenerateArea() {
    T_Square *area = malloc(sizeArea * sizeArea * sizeof(T_Square));
    for (unsigned int i = 0; i < (sizeArea*sizeArea); i++) {
        area[i] = Game_GenerateBasiqueSquare();
    }
    area[Game_GetIndiceInArea(3, 3)].biome = King;
    return area;
}

T_Square Game_GenerateBasiqueSquare() {
    T_Square square = {EmptySpace, 0};
    return square;
}

unsigned int Game_GetIndiceInArea(unsigned int posX, unsigned int posY) {
    unsigned int indice = posY*sizeArea + posX;
    return indice;
}

char *Game_ButtonPressed(const T_Assets *assets) {
    for (unsigned int i=0; i<assets->nbrButton; i++) {
        if (assets->listButton[i].overhead == true) {
            return assets->listButton[i].name;
        }
    }
    return NULL;
}