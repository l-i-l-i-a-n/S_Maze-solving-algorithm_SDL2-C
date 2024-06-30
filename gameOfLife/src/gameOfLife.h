#pragma once
#include "bool.h"
#include "grid.h"

/**
 * @brief Structure pour stoker les tableaux de règles du jeu de la vie
 */
typedef struct {
	bool_t survie[9];
	bool_t naissance[9];
} rules_t;

/**
 * @brief Initialise les règles de vie
 * 
 * @param life les règles
 */
void initLife(rules_t *life);

/**
 * @brief Initialise les règles de labyrinthe
 * 
 * @param maze les règles
 */
void initMaze(rules_t *maze);

/**
 * @brief Gère l'évolution de la grille d'une itération i à l'itération suivante i+1 selon les règles
 * 
 * @param grid la grille
 * @param rules les règles à utiliser
 */
void nextIteration(grid_t *grid, rules_t *rules);