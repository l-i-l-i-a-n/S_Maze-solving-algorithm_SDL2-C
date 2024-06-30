#include "rules.h"

/**
 * @brief Initialise les regles de vie
 * 
 * @param life regles
 */
void initLife(rule_t *life) {
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
		life->naissance[i] = false;
		life->survie[i] = false;
	}
	life->naissance[3] = true;
	life->survie[2] = true;
	life->survie[3] = true;
}

/**
 * @brief Initialise les regles de labyrinthe
 * 
 * @param maze regles
 */
void initMaze(rule_t *maze) 
{
	int i;
	
	for(i = 0; i < TAILLE; ++i) {
		switch(i) {
			case 0:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 5:
				maze->survie[i] = 0;
				maze->naissance[i] = 0;
				break;
			case 3:
				maze->naissance[i] = 1;
				maze->survie[i] = 1;
				break;
			default:
				maze->survie[i] = 1;
				maze->naissance[i] = 0;
		}
	}
}

/**
 * @brief Fait evoluer la matrice selon les regles
 * 
 * @param grid matrice d'entiers
 * @param n nombre de lignes
 * @param m nombre de colonnes
 * @param rule regles
 * @return int** la nouvelle matrice
 */
void nextIteration(int *** grid, int n, int m, rule_t *rule) {
	int ** result;
	int    i, 
	       j, 
		   k,
		   l,
		   neighbours;
	
	result = allocGrid(n, m);
	
	for(i = 0; i < n; i++) 
	{
		for(j = 0; j < m; j++) 
		{
			neighbours = 0;
			for(k = -1; k < 2; ++k) 
			{
				for(l = -1; l < 2; ++l) 
				{
					neighbours += (*grid)[(i+k + n) % n][(j+l + m) % m];
				}
			}
			neighbours -= (*grid)[i][j];


			if((*grid)[i][j] == 1) 
			{
				result[i][j] = (int)rule->survie[neighbours];
			}
			else 
			{
				result[i][j] = (int)rule->naissance[neighbours];
			}
		}
	}
	*grid = result;
}

void change_state(int *** grid, int n, int m, int i, int j)
{
	if(i >= 0 && i < m)
	{
		if(j >= 0 && j < n)
		{
			(*grid)[j][i] = !(*grid)[j][i];
		}
	}
}