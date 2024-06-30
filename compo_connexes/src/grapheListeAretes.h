#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "partition.h"
#include "bool.h"

typedef struct
{
    int poids;
    int noeudDeb;
    int noeudFin;
} arete_t;

typedef struct
{
    int nbNoeuds;
    int nbAretes;
    arete_t *aretes;
} couples_graphe_t;

/**
 * @brief Genere un graphe sous forme de couple liste d'aretes et nombre de noeuds
 * 
 * @param graphe Le graphe genere
 * @param nbNoeuds Le nombre de noeuds du graphe souhaite
 */
void genererGraphe(couples_graphe_t *graphe, int n);

/**
 * @brief Ordonne les aretes du graphe dans l'ordre croissant des poids
 * 
 * @param graph Le graphe
 */
void ordonnerAretesCroissant(couples_graphe_t *graph);

/**
 * @brief Fonction qui compare 2 aretes selon leur poids
 * 
 * @param arete_1 L'arete a
 * @param arete_2 L'arete b
 * @return int -1 si a<b ; 1 si a>b; 0 si a=b (en terme de poids)
 */
int comparArete(const void *arete_1, const void *arete_2);

/**
 * @brief Dit si une arete est valide ou non (on ne veut pas d'arete qui pointe sur son noeud de debut, ou alors si elle a deja ete inseree dans le graphe)
 * 
 * @param graphe Le graphe
 * @param deb Noeud de debut de l'arete
 * @param fin Noeud de fin de l'arete
 * @return bool_t Renvoie True si l'arete est valide, false sinon
 */
bool_t aretePasValide(couples_graphe_t *graphe, int deb, int fin);

/**
 * @brief Permet de liberer la memoire d'un graphe 
 * 
 * @param graphe Le graphe
 */
void supprimerGraphe(couples_graphe_t graphe);
