#pragma once

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

/**
 * @brief Libere une matrice d'entiers
 * 
 * @param grid matrice d'entier
 * @param n nombre de lignes de la matrice
 */
void freeGrid(int **grid, int n);

/**
 * @brief Alloue l'espace pour une matrice d'entiers de taille n*m
 * 
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @return int** 
 */
int **allocGrid(int n, int m);

/**
 * @brief Affiche la matrice dans le terminal
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 */
void displayGrid(int **grid, int n, int m);

/**
 * @brief Initialize tous les éléments de la matrice à 0
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 */
void setToZero(int **grid, int n, int m);