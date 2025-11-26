#ifndef DOMINO_H
#define DOMINO_H

#include <stdlib.h>

#define EmptySpace 0
#define King 1
#define Fields 2
#define Forest 3
#define Grasslands 4
#define Lakes 5
#define Mines 6
#define Swamps 7

#define nbrDomino 48

typedef struct {
    unsigned int biome;
    unsigned int couronne;
} T_Square;

typedef struct {
    T_Square square[2];
    unsigned int orientation;
    unsigned int power;
} T_Domino;

T_Domino *Domino_GenerateDomino();


#endif