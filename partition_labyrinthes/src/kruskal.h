#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "grapheListeAretes.h"

/**
 * @brief Execute l'algorithme de kruskal sur un graphe
 * 
 * @param graph Le graphe
 * @param tailleListe Taille de la liste d'aretes retournee
 * @return arete_t* Liste d'aretes qui represente le chemin trouve par kruskal
 */
arete_t *arbreCouvrantPoidsMin(couples_graphe_t graph, int *tailleListe);
