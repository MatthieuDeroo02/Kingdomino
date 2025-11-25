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
}



void Game_Lobby(SDL_Window *window, SDL_Renderer *renderer, T_Assets assets, unsigned int* nbrPlayer) {
    printf("Lancement Du Lobby\n");
    Render_AddWallpaper(&assets, renderer, "assets/images/fond_ecran_lobby2.bmp");
    Render_AddButton(&assets, renderer, "2player", "assets/images/button2player.png", 0.281, 0.417, 0.117, 0.303, 1.2);
    Render_AddButton(&assets, renderer, "3player", "assets/images/button3player.png", 0.441, 0.417, 0.117, 0.303, 1.2);
    Render_AddButton(&assets, renderer, "4player", "assets/images/button4player.png", 0.602, 0.417, 0.117, 0.303, 1.2);

    bool endLobby = false;
    while(endLobby == false) {
        Render_RenderScene(window, renderer, &assets);

        SDL_Event event; //Contient les événement SDL
        SDL_PollEvent(&event);
        if (event.type == SDL_EVENT_QUIT) {
            Game_EndGame(window, renderer, &assets, 1);
        } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP && event.button.button == SDL_BUTTON_LEFT) {
            char *buttonPressed = Game_ButtonPressed(&assets);
            if (buttonPressed!=NULL) {
                switch(buttonPressed[0]) {
                    case '2': *nbrPlayer = 2; endLobby = true; break;
                    case '3': *nbrPlayer = 3; endLobby = true; break;
                    case '4': *nbrPlayer = 4; endLobby = true; break;
                }
            }
            free(buttonPressed);
        }
        SDL_Delay(16);  // ~60 FPS
    }

    SDL_Texture *background = Render_CaptureScreen(renderer); //Genere une texture a partir de l'ecran
    if (background == NULL) Game_EndGame(window, renderer, &assets, 2); //Verifi que la generation a marchée

    Render_AnimateCloudCurtain(window, renderer, background, 120, 1);    
}

