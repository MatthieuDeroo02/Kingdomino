#ifndef DOMINO_H
#define DOMINO_H

typedef struct {
    int biome;
    int couronne;
} T_Square;

typedef struct {
    T_Square square[2];
    int orientation;
} T_Domino;


#endif