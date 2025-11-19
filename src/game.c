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
    Game_EndGame(window, renderer);
}

void Game_EndGame(SDL_Window *window, SDL_Renderer *renderer) {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}