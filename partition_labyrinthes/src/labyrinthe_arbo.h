#include <stdio.h>
#include <stdlib.h>
#include "grapheListeAretes.h"
#include "matrice.h"

/**
 * @brief Genere un graphe qui represente un labyrinthe arborescent
 * 
 * @param graphe Le graphe
 * @param size La taille du graphe = nombre de noeuds
 */
void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size);

/**
 * @brief Transforme un arbre couvrant en une matrice d'entiers correspondant aux directions dans lesquelles il y a les murs pour chaque case
 * 
 * @param arbre l'arbre à transformer
 * @param nbAretes le nombre d'aretes de l'arbre
 * @param taille la taille de la matrice à générer
 * @return int** la matrice générée
 */
int** arbreCouvrantToMatrice(arete_t* arbre, int nbAretes, int taille);