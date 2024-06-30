#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "partition.h"
#include "grapheListeAretes.h"

/**
 * @brief Creer les differentes chaines de caracteres utiles pour dessiner le graphe
 * 
 * @param name Nom general des fichiers
 * @param dir Chemin du dossier ou stcoker les fichiers
 * @param dotpath Chemin du fichier .dot 
 * @param pngPath Chemin du fichier png
 * @param command Commande pour transformer le .dot en png
 */
void createStrings(char *name, char *dir, char *dotPath, char *pngPath, char *command);

/**
 * @brief Libere les choses propres a graphviz
 * 
 * @param graph_context 
 * @param graph 
 */
void freeAll(GVC_t *graph_context, Agraph_t *graph);

/**
 * @brief Genere le fichier .dot du graphe
 * 
 * @param graph_context 
 * @param graph 
 * @param fic 
 */
void generateGraphviz(GVC_t *graph_context, Agraph_t *graph, FILE *fic);

/**
 * @brief 
 * 
 * @param command Commande système pour generer une image à partir du fichier .dot
 */
void generatePng(char *command);

/**
 * @brief Creer le fichier .dot et le fichier png pour la partition en parametres
 * 
 * @param partition La partition a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawPartitionGraph(partition_t partition, int n, char *name);

/**
 * @brief Creer le fichier .dot et le fichier png pour la matrice d'adjacence en parametres
 * 
 * @param matrix La matrice d'adjacence a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawAdjencyMatrixGraph(int *matrix, int n, char *name);

/**
 * @brief Creer le fichier .dot et le fichier png pour le graphe (couple) en parametres
 * 
 * @param sourceGraph Graphe sous forme couple d'arete + nombre de noeuds
 * @param name Nom pour les fichiers generes
 * @param listeA Liste d'aretes a colorier en rouge (exemple : arbre couvrant) peut etre null
 * @param tailleListeA Taille de la liste d'aretes
 */
<<<<<<< HEAD:compo_connexes/src/graphviz.h
void drawCouplesGraph(couples_graphe_t sourceGraph, char *name, arete_t *listeA, int tailleListeA);
=======
void drawCouplesGraph(couples_graphe_t sourceGraph, char *name, arete_t *listeA, int tailleListeA);
>>>>>>> origin/partition_labyrinthes:partition_labyrinthes/src/graphviz.h
