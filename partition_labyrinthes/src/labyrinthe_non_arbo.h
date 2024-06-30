#pragma once

#include <stdlib.h>
#include <time.h>
#include "partition.h"
#include "grapheListeAretes.h"

/**
 * @brief Affectue l'algorithme de kruskal de facon non-arborescente (utilisation de fisher yate)
 * 
 * @param graph Le graphe
 * @param tailleListe La taille de la liste d'aretes qui sera retournee
 * @param densite La densite souhaitee (ajuste le nombre de murs du labyrinthe)
 * @return arete_t* La liste d'aretes qui constitue le labyrinthe
 */
arete_t *kruskal_non_arbo(couples_graphe_t graph, int *tailleListe, float densite);
