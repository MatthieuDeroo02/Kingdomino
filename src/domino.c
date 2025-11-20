#include "domino.h"

T_Domino *Domino_GenerateDomino() {
    T_Domino *domino = malloc(nbrDomino * sizeof(T_Domino));
    return domino;
}