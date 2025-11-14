#include <SDL3/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "render.h"


int main(int argc, char *argv[]) {
    Render_InitVideo();
    SDL_Window *window = Render_Creat_Window("Kingdomino", 1280, 720);
    unsigned int nbrJoueurs = Render_AfficherLobby(window);
    printf("Il y a %d Joueurs.\n", nbrJoueurs);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
