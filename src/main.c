#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "render.h"


int main(int argc, char *argv[]) {
    Render_InitVideo();
    SDL_Window *window = Render_Creat_Window("Kingdomino", 1280, 720);
    SDL_Renderer *renderer = Render_CreatRenderer(window); //Crée le moteur graphique
    unsigned int nbrJoueurs = Render_AfficherLobby(window, renderer);
    if (nbrJoueurs == 0) { //Si on appuis sur la croix
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return 0;
    }

    Render_StartGame(window, renderer, nbrJoueurs);

    printf("Il y a %d Joueurs.\n", nbrJoueurs);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}
