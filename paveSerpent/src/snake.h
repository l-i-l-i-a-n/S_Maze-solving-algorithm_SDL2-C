#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer);

/**
 * @brief Affiche 3 rectangles sur une fenetre, qui bougent
 * 
 * @param window La fenetre ou seront les rectangles
 * @param renderer Le rendu de la fenetre ou seront les rectangles
 */
void animationRectangles(SDL_Window * window, SDL_Renderer * renderer);  