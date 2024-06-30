#include "testCompoConnexe.h"

int main(void)
{
	arete_t *arbreCouvrant;
	couples_graphe_t graph;
	int tailleArbreCouvrant = 10;
	(testCreateAdjencyMatrix() && testGrapheToPartition() && testNoeudsCompoConnexes()) ? puts("tests OK") : puts("echec tests");

	genererGraphe(&graph, 10);

	arbreCouvrant = arbreCouvrantPoidsMin(graph, &tailleArbreCouvrant);
	drawCouplesGraph(graph, "testCouplesGrapheKruskal", arbreCouvrant, tailleArbreCouvrant);

	supprimerGraphe(graph);

	return 0;
}

/**
 * @brief Teste la fontion noeudsCompoConnexe
 * 
 * @return bool_t 
 */
bool_t testNoeudsCompoConnexes()
{
	graphe_t matrix;
	element_t **element;
	int n = 5, nclasses, i;
	char c;

	matrix = createAdjencyMatrix(n);
	element = noeudsCompoConnexes(matrix, n, &nclasses);
	afficherNoeudsCompoConnexes(element, n, nclasses);
	for (i = 0; i < nclasses; ++i)
	{
		free(element[i]);
	}
	free(element);
	free(matrix);
	puts("validation manuelle : y/n");
	fscanf(stdin, "%c%*c", &c);
	if (c == 'y' || c == 'Y')
	{
		return true;
	}
	fputs("erreur noeudcompoconnexe\n", stderr);
	return false;
}

/**
 * @brief Teste la fonction createAdejencyMatrix
 * 
 * @return bool_t 
 */
bool_t testCreateAdjencyMatrix()
{
	graphe_t matrix = NULL;
	int n = 10;

	matrix = createAdjencyMatrix(n);
	if (matrix == NULL)
	{
		fputs("erreur creation matrice adjacente\n", stderr);
		return false;
	}
	free(matrix);
	return true;
}

/**
 * @brief Teste la fonction grapheToPartition
 * 
 * @return bool_t 
 */
bool_t testGrapheToPartition()
{
	graphe_t matrix = NULL;
	partition_t partition;
	int n = 3;
	char c = 0;

	matrix = createAdjencyMatrix(n);
	if (matrix == NULL)
	{
		fputs("erreur creation de la matrice avant test dans grapheToPartition\n", stderr);
		return false;
	}
	partition = grapheToPartition(matrix, n);
	if (partition.foret == NULL || partition.hauteur == NULL)
	{
		free(matrix);
		return false;
	}
	drawAdjencyMatrixGraph(matrix, n, "testGrapheToPartition");
	afficherForet(partition, n);
	puts("validation manuelle : y/n");
	fscanf(stdin, "%c%*c", &c);
	free(matrix);
	detruirePartition(partition);
	if (c == 'y' || c == 'Y')
	{
		return true;
	}
	fputs("graphe non conforme\n", stderr);
	return false;
}
