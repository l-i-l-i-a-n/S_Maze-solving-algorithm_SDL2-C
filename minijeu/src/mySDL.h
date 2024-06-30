#pragma once
#include <stdio.h>
#include "bool.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * @brief Initialise la librairie SDL
 * @return un booleen true si tout la librairie s'est initialisee avec succes, false sinon
 */
bool_t initializeSDL(void);

/**
 * @brief Permet de charger une texture SDL a partir de son chemin et d'un renderer SDL
 * 
 * @param name chemin d'acces au fichier png
 * @param renderer rendu a dans lequel charger
 */
SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer);

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void quitSDL(bool_t status, char const* msg, SDL_Window* window, SDL_Renderer* renderer);