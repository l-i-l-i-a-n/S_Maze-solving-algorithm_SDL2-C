#pragma once

#include <stdio.h>
#include "bool.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

/**
 * @brief Initialise la SDL et indique si l'initialisation s'ets bien passée
 * 
 * @return bool_t false : échec, true : succès
 */
bool_t initializeSDL(void);

/**
 * @brief Permet de fermer toute la SDL et d'indiquer un message d'erreur si il y en a une
 * 
 * @param status false : erreur, true : normal
 * @param msg message de fin
 * @param window fenêtre à fermer
 * @param renderer rendu à fermer
 */
void quitSDL(bool_t status, char const *msg, SDL_Window *window, SDL_Renderer *renderer);

/**
 * @brief Permet de charger une texture SDL a partir de son chemin et d'un renderer SDL
 * 
 * @param name chemin d'acces au fichier png
 * @param renderer rendu a dans lequel charger
 */
SDL_Texture *loadTextureFromImage(char *name, SDL_Renderer *renderer);