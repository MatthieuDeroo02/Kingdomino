#include <SDL3/SDL.h>
#include "game.h"

void Game_NewGame() {
    Render_InitVideo();
    SDL_Window *window = Render_Creat_Window("Kingdomino", 1280, 720);
    SDL_Renderer *renderer = Render_CreatRenderer(window); //Crée le moteur graphique
    unsigned int nbrJoueurs = Render_AfficherLobby(window, renderer);
    if (nbrJoueurs == 0) { //Si on appuis sur la croix
        Game_EndGame(window, renderer);
    }

    Render_StartGame(window, renderer, nbrJoueurs);

    printf("Il y a %d Joueurs.\n", nbrJoueurs);
    SDL_Delay(2000); //Pause de 2 secondes avant de fermer la fenêtre
    Game_EndGame(window, renderer);
}

void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
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