#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define NB_FENETRES 6

/**
 * @brief Permet de deplacer une fenetre selon un pas
 * 
 * @param window la fenetre
 * @param pas entier
 */
void deplacerFenetre(SDL_Window  * window, int pas);

/**
 * @brief Permet de redimensionner une fenetre selon un pas
 * 
 * @param window la fenetre
 * @param pas entier
 */
void redimensionnerFenetre(SDL_Window  * window, int pas);