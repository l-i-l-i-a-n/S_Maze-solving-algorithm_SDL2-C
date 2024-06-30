#pragma once
#include <stdio.h>
#include "bool.h"
#include "SDL2/SDL.h"

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
void quitSDL(char ok,
             char const* msg,
             SDL_Window* window,
             SDL_Renderer* renderer);

/**
 * @brief Attend la fermeture manuelle de la fenêtre par l'utilisateur
 */
void waitForQuitSDL(void);