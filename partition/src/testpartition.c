#include "testpartition.h"

/**
 * @brief Teste la fonction creer (pour une partition)
 * 
 * @return true 
 * @return false 
 */
bool testCreer()
{
	int i, n = 11;
	partition_t test;
	bool code = true;

	test = creer(n);
	for (i = 0; i < n; ++i)
	{
		if (test.foret[i] != i || test.hauteur[i] != 1)
		{
			code = false;
			puts("echec creation\n");
		}
	}
	puts("creer OK");
	detruirePartition(test);
	return code;
}

/**
 * @brief Teste la fonction recupererClasse
 * 
 * @return true 
 * @return false 
 */
bool testRecupererClasse()
{
	partition_t partition;
	int n = 12;

	partition = creer(n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		fputs("erreur memoire\n", stderr);
		return false;
	}
	if (recuperer_classe(partition, 1) != 1)
	{
		puts("echec recuperer classe initiale\n");
		detruirePartition(partition);
		return false;
	}
	partition = fusion(partition, 0, 1);
	if (recuperer_classe(partition, 1) != 0)
	{
		puts("echec recuperer classe apres fusion\n");
		printf("classe de 0 : %d\nclasse de 1 : %d\n", (int)recuperer_classe(partition, 0), (int)recuperer_classe(partition, 1));
		detruirePartition(partition);
		return false;
	}
	detruirePartition(partition);
	puts("recuperer classe OK");
	return true;
}

/**
 * @brief Teste la fonction classeMere
 * 
 * @return true 
 * @return false 
 */
bool testClasseMere()
{
	partition_t partition;
	int n = 11;

	partition = creer(n);
	partition = fusion(partition, 0, 1);
	partition = fusion(partition, 2, 3);
	partition = fusion(partition, 10, 3);
	partition = fusion(partition, 5, 9);
	partition = fusion(partition, 4, 6);
	partition = fusion(partition, 8, 7);
	partition = fusion(partition, 8, 9);
	partition = fusion(partition, 6, 8);
	if (classeMere(10, partition) != 2 || classeMere(5, partition) != 5)
	{
		puts("erreur classe mere");
		return false;
	}
	puts("classe mere OK");
	detruirePartition(partition);
	return true;
}

/**
 * @brief Teste la fonction fusion
 * 
 * @return true 
 * @return false 
 */
bool testFusion()
{
	partition_t partition;
	int n = 11;

	partition = creer(n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		fputs("erreur memoire\n", stderr);
		return false;
	}
	partition = fusion(partition, 0, 1);
	if (recuperer_classe(partition, 1) != 0)
	{
		puts("echec fusion simple\n");
		detruirePartition(partition);
		return false;
	}
	partition = fusion(partition, 2, 3);
	partition = fusion(partition, 10, 3);
	if (recuperer_classe(partition, 10) != 2)
	{
		puts("echec fusions combinees\n");
		afficherForet(partition, n);
		detruirePartition(partition);
		return false;
	}
	partition = fusion(partition, 5, 9);
	partition = fusion(partition, 4, 6);
	partition = fusion(partition, 8, 7);
	if (recuperer_classe(partition, 8) != 7)
	{
		puts("echec fusions combinees\n");
		afficherForet(partition, n);
		detruirePartition(partition);
		return false;
	}
	partition = fusion(partition, 8, 9);
	if (recuperer_classe(partition, 5) != 5 || recuperer_classe(partition, 7) != 5 || recuperer_classe(partition, 9) != 5)
	{
		puts("echec fusions combinees\n");
		afficherForet(partition, n);
		detruirePartition(partition);
		return false;
	}
	partition = fusion(partition, 6, 8);
	if (recuperer_classe(partition, 4) != 5)
	{
		puts("echec fusions combinees\n");
		afficherForet(partition, n);
		detruirePartition(partition);
		return false;
	}
	puts("fusion OK");
	detruirePartition(partition);
	return true;
}

/**
 * @brief Teste la fonction listerClasse
 * 
 * @return true 
 * @return false 
 */
bool testListerClasse()
{
	partition_t partition;
	element_t *element;
	int n = 11;

	partition = creer(n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		fputs("erreur memoire\n", stderr);
		return false;
	}
	partition = fusion(partition, 0, 1);
	element = lister_classe(partition, 0, n);
	if (element[0] != 0 || element[1] != 1 || element[2] != -1)
	{
		afficherForet(partition, n);
		puts("echec listage classes\n");
		detruirePartition(partition);
		return false;
	}
	puts("liste classe OK");
	detruirePartition(partition);
	free(element);
	return true;
}

/**
 * @brief Teste la fonction listerPartition
 * 
 * @return true 
 * @return false 
 */
bool testListerPartition()
{
	partition_t partition;
	classe_t *classe;
	int i, n = 11, k = 0;

	partition = creer(n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		fputs("erreur memoire\n", stderr);
		return false;
	}
	for (i = 1; i < 2 * n / 3; ++i)
	{
		partition = fusion(partition, 0, i);
	}
	classe = lister_partition(partition, n);
	while (k < n && k > -1)
	{
		++k;
	}
	if (classe[0] != 0 || classe[k] == n - 1)
	{
		afficherForet(partition, n);
		afficherClasse(classe, n);
		puts("echec listage partition\n");
		detruirePartition(partition);
		return false;
	}
	puts("liste partition OK");
	detruirePartition(partition);
	free(classe);
	return true;
}
