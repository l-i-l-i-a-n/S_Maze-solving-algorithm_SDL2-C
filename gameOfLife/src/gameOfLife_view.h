#pragma once 
#include <SDL2/SDL.h>
#include "grid.h"
#include "gameOfLife.h"

/**
 * @brief Affiche une grille dans la fenêtre
 * 
 * @param window le fenêtre à utiliser
 * @param renderer le renderer à utiliser
 * @param grid la grille à afficher
 */
void drawGrid(SDL_Window * window, SDL_Renderer *renderer, grid_t grid);

/**
 * @brief Récupère la taille de l'affichage courant
 * 
 * @param height la hauteur de l'éffichage
 * @param width la largeur de l'affichage
 * @return int 0 : erreur, 1 : succès
 */
int screenSize(int *height, int *width);

/**
 * @brief Lance le jeu de la vie sur un nombre d'itérations donné
 * 
 * @param grid la grille du jeu
 * @param rules les règles à utiliser
 * @param iterations le nombre d'itérations à effectuer
 * @param delay le délai entre deux itérations
 * @param window la fenêtre à utiliser pour afficher
 * @param renderer le renderer à utiliser pour afficher
 */
void startGoL(grid_t grid, rules_t* rules, int iterations, int delay, SDL_Window* window, SDL_Renderer* renderer);