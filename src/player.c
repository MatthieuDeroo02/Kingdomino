#include "player.h"

T_Player *Player_GeneratePlayers(unsigned int nbrPlayer) {
    T_Player *player = malloc(nbrPlayer * sizeof(T_Player));
    for (unsigned int i=0; i<nbrPlayer; i++) {
        player[i].area = Game_GenerateArea();
    }
    return player;
}