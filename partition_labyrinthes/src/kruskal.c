#include "kruskal.h"

/**
 * @brief Execute l'algorithme de kruskal sur un graphe
 * 
 * @param graph Le graphe
 * @param tailleListe Taille de la liste d'aretes retournee
 * @return arete_t* Liste d'aretes qui represente le chemin trouve par kruskal
 */
arete_t *arbreCouvrantPoidsMin(couples_graphe_t graph, int *tailleListe)
{
    arete_t *listeAretes;
    partition_t partition;
    element_t elem1,
        elem2;
    int i,
        j = 0;

    listeAretes = (arete_t *)malloc(sizeof(arete_t) * graph.nbAretes);
    if (listeAretes)
    {
        ordonnerAretesCroissant(&graph);
        partition = creer(graph.nbNoeuds);

        for (i = 0; i < graph.nbAretes; i++)
        {
            elem1 = graph.aretes[i].noeudDeb;
            elem2 = graph.aretes[i].noeudFin;
            if (classeMere(elem1, partition) != classeMere(elem2, partition))
            {
                fusion(partition, elem1, elem2);
                listeAretes[j] = graph.aretes[i];
                j++;
            }
        }
        *tailleListe = j;
    }

    return listeAretes;
}
