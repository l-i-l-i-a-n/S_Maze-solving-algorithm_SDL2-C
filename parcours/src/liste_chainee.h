/**********************************************************/
/*Chandeze Marius & Meunier Killian                  2021 */
/*--------------------------------------------------------*/
/*                    liste_chainee.h                     */
/*             Traitement d'une liste chainee             */
/*                   FICHIER D'ENTETE                     */
/**********************************************************/

#ifndef LISTE_CHAINEE_H_
#define LISTE_CHAINEE_H_

#include <stdio.h>
#include <stdlib.h>
#include "bool.h"

/***************************************/
/* Structure d'une liste chainee       */
/***************************************/
typedef struct maillon
{
    int v;
    struct maillon *suiv;
} maillon_t, *liste_t;

/********************/
/* Type booleen     */
/********************/
typedef bool_t booleen_t;

/***************************************/
/* Initialisation d'une liste a NULL   */
/***************************************/
maillon_t *initialisation_liste();

/********************************************/
/* Creer un maillon a partir d'une valeur   */
/********************************************/
maillon_t *creerMaillon(int val);

/******************************************************************************************/
/* Creer une liste, triée dans l'ordre décroissant, des k premières valeurs d'une matrice */
/******************************************************************************************/
booleen_t creerListe_kPremierElem_matrice(int k, int **matrice, liste_t *l, int n, int m, int *i, int *j);

/****************************************************************************************************/
/* Creer une liste, triée dans l'ordre décroissant, des k plus petites valeurs (kppv) d'une matrice */
/****************************************************************************************************/
booleen_t creerListe_kppv_matrice(int k, int **matrice, liste_t *l, int n, int m);

/********************************************************/
/* Retrouve le maillon precedent d'une valeur donnee    */
/********************************************************/
liste_t *recherche_prec(liste_t *l, int val, booleen_t *trouve);

/**************************************/
/* Ajoute un maillon dans une liste   */
/**************************************/
void ajout_lch(liste_t *b, maillon_t *elt);

/****************************************/
/* Supprime un maillon dans une liste   */
/****************************************/
void supp_lch(liste_t *b);

/****************************************/
/* Affiche une liste dans le terminal   */
/****************************************/
void affichageListe(maillon_t *l);

/******************************************/
/* Libere l'espace memoire d'une liste    */
/******************************************/
void libererListe(maillon_t *l);

/**********************************************************/
/* Supprime les valeurs d'une usine specifiee de la liste */
/**********************************************************/
void supprimer_occurrence(int, liste_t *m);

#endif
