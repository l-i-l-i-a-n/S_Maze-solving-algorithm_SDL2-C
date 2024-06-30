#pragma once
#include <stdio.h>
#include "bool.h"

/**
 * @brief Structure de grille
 */
typedef struct grid {
    bool_t **grid;
	int x;
	int y;
} grid_t;

/**
 * @brief Alloue l'espace pour une matrice d'entiers de taille x*y
 * 
 * @param x nombre de lignes
 * @param y nombre de colonnes
 * @return grid_t La matrice
 */
grid_t createGrid(int x, int y);

/**
 * @brief Crée une matrice avec des 0 et des 1 aleatoirement
 * 
 * @param grid la matrice à initialiser
 */
void initializeRandomGrid(grid_t grid);

/**
 * @brief Affiche une matrice dans le terminal
 * 
 * @param grid la matrice à afficher
 */
void displayGrid(grid_t grid);

/**
 * @brief Libère une matrice d'entiers
 * 
 * @param grid matrice d'entiers
 */
void freeGrid(grid_t grid);