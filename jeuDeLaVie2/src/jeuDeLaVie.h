#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "matrice.h"
#include "rules.h"

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok,char const* msg,SDL_Window* window,SDL_Renderer* renderer); 

/**
 * @brief Affiche une matrice d'entiers dans le rendu
 * 
 * @param renderer 
 * @param grille 
 * @param n 
 * @param m 
 * @param cell
 */
void drawGrid(SDL_Renderer *renderer, int ** grille, int n, int m, SDL_Rect cell); 

/**
 * @brief Permet de calculer les dimensions d'une cellule par rapport a la taille de la fenetre
 * 
 * @param window la fenetre
 * @param cell la cellule (SDL_Rect)
 * @param n nombre de lignes de la grille
 * @param m nombre de colonnes de la grille
 */
void cellDimensions(SDL_Window * window, SDL_Rect * cell, int n, int m);

/**
 * @brief Boucle de jeu du jeu de la vie facon labyrinthe
 * 
 * @param window 
 * @param renderer 
 * @param grid 
 * @param n 
 * @param m 
 * @param rule 
 */
void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** grid, int n, int m, rule_t * rule);