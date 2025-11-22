#include "game.h"

void Game_NewGame() {
    Render_InitVideo();
    SDL_Window *window = Render_Creat_Window("Kingdomino", 1280, 720);
    SDL_Renderer *renderer = Render_CreatRenderer(window); //Crée le moteur graphique
    T_Assets assets = Render_CreatAssets();

    /*Lance une partie avec le lobby*/
    unsigned int nbrPlayer;
    Game_Lobby(window, renderer,assets, &nbrPlayer);

    Game_EndGame(window, renderer, &assets, 1);


    /*
    unsigned int nbrJoueurs = Render_AfficherLobby(window, renderer);
    if (nbrJoueurs == 0) { //Si on appuis sur la croix
        Game_EndGame(window, renderer, 1);
    }
    
    Render_StartGame(window, renderer, nbrJoueurs);
    
    printf("Il y a %d Joueurs.\n", nbrJoueurs);
    SDL_Delay(2000); //Pause de 2 secondes avant de fermer la fenêtre
    Game_EndGame(window, renderer, 1);
    */
}



void Game_Lobby(SDL_Window *window, SDL_Renderer *renderer, T_Assets assets, unsigned int* nbrJoueur) {
    printf("Lancement Du Lobby\n");
    Render_AddWallpaper(&assets, renderer, "assets/images/fond_ecran_lobby2.bmp");
    Render_AddButton(&assets, renderer, "2player", "assets/images/button2player.png", 0.281, 0.417, 0.117, 0.303, 1.2);
    Render_AddButton(&assets, renderer, "3player", "assets/images/button3player.png", 0.441, 0.417, 0.117, 0.303, 1.2);
    Render_AddButton(&assets, renderer, "4player", "assets/images/button4player.png", 0.602, 0.417, 0.117, 0.303, 1.2);

    while(true) {
        Render_RenderScene(window, renderer, &assets);

        SDL_Event event; //Contient les événement SDL
        while (SDL_PollEvent(&event)) { //Remplie avec le prochain evenement
            if (event.type == SDL_EVENT_QUIT) {
                Game_EndGame(window, renderer, &assets, 1);
            }
        }
        SDL_Delay(16);  // ~60 FPS
    }

}

