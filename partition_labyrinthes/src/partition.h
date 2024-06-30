#pragma once

#include <stdlib.h>
#include <stdio.h>

typedef int ensemble_t;
typedef int classe_t;
typedef int element_t;
typedef int label_t;
typedef struct
{
	classe_t *foret;
	int *hauteur;
} partition_t;

/**
 * @brief Creer une partition a partir d'un ensemble
 * 
 * @param ensemble Ici c'est un entier : nombre d'elements
 * @return partition_t 
 */
partition_t creer(ensemble_t n);

/**
 * @brief Recupere la classe d'un element d'une partition
 * 
 * @param partition 
 * @param element 
 * @return classe_t 
 */
classe_t recuperer_classe(partition_t partition, element_t element);

/**
 * @brief Fusionne deux classes entre elles par le biais de deux elements : on recupere leur classe
 * 
 * @param partition 
 * @param x 
 * @param y 
 * @return partition_t 
 */
partition_t fusion(partition_t partition, element_t x, element_t y);

/**
 * @brief Liste les elements d'une classe
 * 
 * @param partition 
 * @param label nom de la classe (indice)
 * @param n 
 * @return element_t* 
 */
element_t *lister_classe(partition_t partition, label_t labeli, int n);

/**
 * @brief Libere toute une partition
 * 
 * @param partition 
 */
classe_t *lister_partition(partition_t partition, int n);

/**
 * @brief Liste les differentes classes d'une partition
 * 
 * @param partition 
 * @param n 
 * @return classe_t* 
 */
void detruirePartition(partition_t partition);

/**
 * @brief Affiche dans le terminal les elements d'une classe
 * 
 * @param classe 
 * @param n 
 */
void afficherClasse(classe_t *classe, int n);

/**
 * @brief Affiche les element de la foret de la partition, avec leur hauteur
 * 
 * @param partition 
 * @param n 
 */
void afficherForet(partition_t partition, int n);

/**
 * @brief Retourne la classe mere d'un element
 * 
 * @param element 
 * @param partition 
 * @return classe_t 
 */
classe_t classeMere(element_t element, partition_t partition);
