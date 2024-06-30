#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bool.h"
#include "matrice.h"

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
 * @brief Génère un graphe aléatoire avec nbNoeuds noeuds
 * 
 * @param graphe Le graphe généré
 * @param nbNoeuds Le nombre de noeuds
 */
void genererGraphe(couples_graphe_t *graphe, int nbNoeuds);

/**
 * @brief   Génère un graphe dans lequel tous les noeuds ont une arete avec le noeud suivant, et une avec le noeud en dessous (index du noeud + nbNoeuds)
 *          Le graphe peut donc être vu comme un labyrinthe sans aucun mur. sauf sur les 4 bords.
 *          L'algorithme de kruskal permettra de le transformer en un vrai labyrinthe qui correspondra à l'arbre couvrant trouvé par Kruskal.
 * 
 * @param graphe le graphe
 * @param size la largeur du labyrinthe/graphe voulue
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
int **arbreCouvrantToMatrice(arete_t *arbre, int nbAretes, int taille);

/**
 * @brief Trie une liste d'aretes par ordre croissant (qSort)
 * 
 * @param graph Le graphe contenant les aretes a trier
 */
void ordonnerAretesCroissant(couples_graphe_t *graph);

/**
 * @brief Ordonner les aretes d'un rgaphe de façon aléatoire
 * 
 * @param graph Le graphe
 */
void fisherYate(couples_graphe_t *graph);

/**
 * @brief Compare deux aretes selon leur poids
 * 
 * @param arete_1 La premiere arete
 * @param arete_2 La deuxieme arete
 * @return int Le résultat : 1 si arete_1 > arete_2 ; 0 si égaux ; -1 sinon
 */
int comparArete(const void *arete_1, const void *arete_2);

/**
 * @brief   Lors de la génération du grapheLabyrinthe, vérifie si une arête générée aléatoirement est est valide et peut être ajoutée
 *          Une arête est valide si elle n'a pas déjà été ajoutée et si ce n'est pas une arête d'un noeud vers lui-même
 * 
 * @param graphe Le graphe
 * @param deb le noeud de début de l'arete
 * @param fin le noeud de fin de l'arete
 * @return bool_t true si pas valide ; false si valide
 */
bool_t aretePasValide(couples_graphe_t *graphe, int deb, int fin);

/**
 * @brief Affiche toutes les aretes d'un graphe sur la sortie standard
 * 
 * @param graph le graphe
 */
void printAretes(couples_graphe_t graph);

/**
 * @brief Permute la position de 2 aretes dans un tableau d'aretes
 * 
 * @param aretes le tableau d'aretes
 * @param i indice de la premiere arete
 * @param j indice de la deuxieme arete
 */
void exchange(arete_t *aretes, int i, int j);

/**
 * @brief Renvoie un noeud du graphe choisi aleatoirement
 * 
 * @param graph le graphe
 * @param noeudDeb permet de spécifier un noeud de départ existant pour ue le noeud généré ne soit pas le même que celui de départ
 * @return int le numéro du noeud choisi aléatoirement
 */
int randomNoeud(couples_graphe_t graph, int noeudDeb);

/**
 * @brief Renvoie une liste des numéros des noeuds voisins d'un noeud donné en parametre
 * 
 * @param graphe le graphe
 * @param noeud le noeud pour lequel on cherche ses voisins
 * @param nbVoisins le nombre de voisins trouvés
 * @return int* la liste des voisins trouvés
 */
int *trouverVoisins(couples_graphe_t graphe, int noeud, int *nbVoisins);