#include "partition.h"

/**
 * @brief Creer une partition a partir d'un ensemble
 * 
 * @param ensemble Ici c'est un entier : nombre d'elements
 * @return partition_t 
 */
partition_t creer(ensemble_t ensemble)
{
	partition_t partition;
	int i;

	partition.foret = malloc(sizeof(classe_t) * ensemble);
	partition.hauteur = malloc(sizeof(int) * ensemble);
	if (partition.hauteur == NULL || partition.foret == NULL)
	{
		return partition;
	}

	for (i = 0; i < (int)ensemble; ++i)
	{
		partition.foret[i] = i;
		partition.hauteur[i] = 1;
	}
	return partition;
}

/**
 * @brief Recupere la classe d'un element d'une partition
 * 
 * @param partition 
 * @param element 
 * @return classe_t 
 */
classe_t recuperer_classe(partition_t partition, element_t element)
{
	return partition.foret[(int)element];
}

/**
 * @brief Fusionne deux classes entre elles par le biais de deux elements : on recupere leur classe
 * 
 * @param partition 
 * @param x 
 * @param y 
 * @return partition_t 
 */
partition_t fusion(partition_t partition, element_t x, element_t y)
{
	classe_t classex, classey, min;

	classex = recuperer_classe(partition, x);
	classey = recuperer_classe(partition, y);
	if (partition.hauteur[(int)classey] == partition.hauteur[(int)classex])
	{
		min = (classex <= classey) ? classex : classey;
		++(partition.hauteur[min]);
	}
	if (partition.hauteur[(int)classey] < partition.hauteur[(int)classex])
	{
		partition.foret[(int)y] = classex;
		partition.foret[(int)classey] = classex;
	}
	else
	{
		partition.foret[(int)x] = classey;
		partition.foret[(int)classex] = classey;
	}
	return partition;
}

/**
 * @brief Liste les elements d'une classe
 * 
 * @param partition 
 * @param label nom de la classe (indice)
 * @param n 
 * @return element_t* 
 */
element_t *lister_classe(partition_t partition, label_t label, int n)
{
	int i, k = 0;
	element_t *liste;

	liste = malloc(sizeof(element_t) * n);
	if (liste == NULL)
	{
		return NULL;
	}

	for (i = 0; i < n; ++i)
	{
		if ((int)partition.foret[i] == (int)label)
		{
			liste[k] = (element_t)i;
			++k;
		}
	}
	if (k < n)
	{
		liste[k] = -1;
	}
	return liste;
}

/**
 * @brief Libere toute une partition
 * 
 * @param partition 
 */
void detruirePartition(partition_t partition)
{
	free(partition.foret);
	free(partition.hauteur);
}

/**
 * @brief Liste les differentes classes d'une partition
 * 
 * @param partition 
 * @param n 
 * @return classe_t* 
 */
classe_t *lister_partition(partition_t partition, int n)
{
	int i, k = 0;
	classe_t *liste;

	liste = malloc(sizeof(classe_t) * n);
	if (liste == NULL)
	{
		return NULL;
	}

	for (i = 0; i < n; ++i)
	{
		if ((int)partition.foret[i] == i)
		{
			liste[k] = (classe_t)partition.foret[i];
			++k;
		}
	}
	if (k < n)
	{
		liste[k] = -1;
	}
	return liste;
}

/**
 * @brief Affiche dans le terminal les elements d'une classe
 * 
 * @param classe 
 * @param n 
 */
void afficherClasse(classe_t *classe, int n)
{
	int i = 0;

	while (i < n && classe[i] != -1)
	{
		printf("%d ", classe[i]);
		++i;
	}
	puts("");
}

/**
 * @brief Affiche les element de la foret de la partition, avec leur hauteur
 * 
 * @param partition 
 * @param n 
 */
void afficherForet(partition_t partition, int n)
{
	int i;

	for (i = 0; i < n; ++i)
	{
		printf("indice[%d] : %d (hauteur %d)\n", i, partition.foret[i], partition.hauteur[i]);
	}
	puts("");
}

/**
 * @brief Retourne la classe mere d'un element
 * 
 * @param element 
 * @param partition 
 * @return classe_t 
 */
classe_t classeMere(element_t element, partition_t partition)
{
	while (partition.foret[element] != element)
	{
		element = partition.foret[element];
	}
	return element;
}
