#pragma once
#include <stdio.h>
#include "matrice.h"
#include "booleen.h"

#define TAILLE 9

typedef struct {
	booleen_t survie[TAILLE];
	booleen_t naissance[TAILLE];
} rule_t;

/**
 * @brief Initialise les regles de vie
 * 
 * @param life regles
 */
void initLife(rule_t *life);

/**
 * @brief Initialise les regles de labyrinthe
 * 
 * @param maze regles
 */
void initMaze(rule_t *maze); 

/**
 * @brief Fait evoluer la matrice selon les regles
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param rule regles
 * @return int** la nouvelle matrice
 */
void nextIteration(int *** grid, int n, int m, rule_t *rule);

void change_state(int *** grid, int n, int m, int i, int j);