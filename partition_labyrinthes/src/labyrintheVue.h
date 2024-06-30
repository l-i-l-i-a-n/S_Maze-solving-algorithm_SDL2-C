#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "mySDL.h"
#include "grapheListeAretes.h"
#include "labyrinthe_arbo.h"
#include "kruskal.h"
#include "graphviz.h"
#include "matrice.h"
#include "labyrinthe_non_arbo.h"

// Type direction (pour savoir quels murs placer)
typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
} directions;

/**
 * @brief Calcule les dimensions d'une case du labyrinthe
 * 
 * @param tile Le rectangle qui represente une case
 * @param positionLab Dimensions et position du labyrinthe
 * @param n Nombre de lignes de la matrice qui represente le labyrinthe
 * @param m Nombre de colonnes de la matrice qui repesente le labyrinthe
 */
void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m);

/**
 * @brief Calcule les dimensions du personnage
 * 
 * @param dest Rectangle qui represente le personnage
 * @param tile Rectangle qui represente une case du labyrinthe
 */
void dimensionPerso(SDL_Rect *perso, SDL_Rect tile);

/**
 * @brief Dessine le personnage a l'ecran
 * 
 * @param renderer Le rendu
 * @param perso La texture a appliquer au personnage
 * @param dest Rectangle qui represente le personnage
 */
void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest);

/**
 * @brief Dessine tout le labyrinthe sur le rendu
 * 
 * @param renderer Le rendu
 * @param grid La matrice representant le labyrinthe
 * @param n Nombre de lignes de la matrice
 * @param m Nombre de colonnes de la matrice
 * @param tile Le rectangle pour une case
 * @param positionLab Le rectangle delimitant le labyrinthe
 * @param texture La texture a appliquer pour le sol et les murs
 */
void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture);
