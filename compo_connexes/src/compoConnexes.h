#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition.h"

typedef int *graphe_t;

/**
 * @brief Affiche une matrice d'adjacence dans le terminal
 * 
 * @param matrix La matrice
 * @param n La taille de la matrice (carree)
 */
void afficherMatriceAdjacence(graphe_t matrix, int n);

/**
 * @brief Cree une matrice d'adjacence qui represente un graphe
 * 
 * @param n La taille de la matrice
 * @return graphe_t 
 */
graphe_t createAdjencyMatrix(int n);

/**
 * @brief Partitionne un graphe en ses composantes connexes
 * 
 * @param graphe Le graphe
 * @param n La taille de la matrice d'adjacence du graphe
 * @return partition_t La partition des composantes connexes
 */
partition_t grapheToPartition(graphe_t graphe, int n);

/**
 * @brief Calcule les noeuds de chacune des composantes connexes du graphe
 * 
 * @param graphe Le graphe
 * @param n La taille de la matrice d'adjacence du graphe
 * @param noeudsI Le nombre de composantes connexes
 * @return element_t** La liste des tableaux d'elements de chaque composante connexe
 */
element_t **noeudsCompoConnexes(graphe_t graphe, int n, int *noeudsI);

/**
 * @brief Affiche dans le terminal chaque noeud pour chaque classe
 * 
 * @param noeuds Les noeuds de chacunes de composantes connexes
 * @param n Nombre d'elements max d'une classe
 * @param nclasse Nombre de classes
 */
void afficherNoeudsCompoConnexes(element_t **noeuds, int n_noeuds, int n);