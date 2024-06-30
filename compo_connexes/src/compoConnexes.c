#include "compoConnexes.h"

/**
 * @brief Affiche une matrice d'adjacence dans le terminal
 * 
 * @param matrix La matrice
 * @param n La taille de la matrice (carree)
 */
void afficherMatriceAdjacence(graphe_t matrix, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", matrix[i * n + j]);
		}
		printf("\n");
	}
}

/**
 * @brief Cree une matrice d'adjacence qui represente un graphe
 * 
 * @param n La taille de la matrice
 * @return graphe_t 
 */
graphe_t createAdjencyMatrix(int n)
{
	graphe_t matrix = NULL;
	srand(time(NULL));
	matrix = (int *)malloc(n * n * sizeof(int));
	if (matrix != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				matrix[n * i + j] = rand() % 2;
				matrix[n * j + i] = 0 /*matrix[n*i + j]*/;
			}
			matrix[n * i + i] = 0;
		}
	}
	else
	{
		puts("Error: memory allocation\n");
	}
	return matrix;
}

/**
 * @brief Partitionne un graphe en ses composantes connexes
 * 
 * @param graphe Le graphe
 * @param n La taille de la matrice d'adjacence du graphe
 * @return partition_t La partition des composantes connexes
 */
partition_t grapheToPartition(graphe_t graphe, int n)
{
	partition_t partition;
	int i = 0, j = 0;

	partition = creer(n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		fputs("erreur conversion du graphe en partition\n", stderr);
		return partition;
	}
	for (i = 0; i < n; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			if (graphe[i * n + j] == 1)
			{
				fusion(partition, i, j);
			}
		}
	}
	return partition;
}

/**
 * @brief Calcule les noeuds de chacune des composantes connexes du graphe
 * 
 * @param graphe Le graphe
 * @param n La taille de la matrice d'adjacence du graphe
 * @param noeudsI Le nombre de composantes connexes
 * @return element_t** La liste des tableaux d'elements de chaque composante connexe
 */
element_t **noeudsCompoConnexes(graphe_t graphe, int n, int *noeudsI)
{
	partition_t partition;
	element_t **noeud;
	classe_t *classe;
	int i = 0, j;

	partition = grapheToPartition(graphe, n);
	classe = (element_t *)lister_partition(partition, n);
	while (i < n && classe[i] > -1)
	{
		++i;
	}
	noeud = malloc(sizeof(element_t *) * i);
	*noeudsI = i;
	if (noeud == NULL)
	{
		fputs("erreur allocation de memoire noeudcompoconnexe\n", stderr);
		return NULL;
	}
	for (j = 0; j < i; ++j)
	{
		noeud[j] = lister_classe(partition, classe[j], n);
	}
	free(classe);
	detruirePartition(partition);
	return noeud;
}

/**
 * @brief Affiche dans le terminal chaque noeud pour chaque classe
 * 
 * @param noeuds Les noeuds de chacunes de composantes connexes
 * @param n Nombre d'elements max d'une classe
 * @param nclasse Nombre de classes
 */
void afficherNoeudsCompoConnexes(element_t **noeuds, int n, int nclasse)
{
	int i;
	printf("Il y a %d classes : \n", nclasse);
	for (i = 0; i < nclasse; i++)
	{
		printf("Classe %d : ", i);
		afficherClasse(noeuds[i], n);
	}
}
