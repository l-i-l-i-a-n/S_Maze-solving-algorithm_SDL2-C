#include "kruskal_non_arbo.h"

/**
 * @brief Affectue l'algorithme de kruskal de facon non-arborescente (utilisation de fisher yate)
 * 
 * @param graph Le graphe
 * @param tailleListe La taille de la liste d'aretes qui sera retournee
 * @param densite La densite souhaitee (ajuste le nombre de murs du labyrinthe)
 * @return arete_t* La liste d'aretes qui constitue le labyrinthe
 */
arete_t *kruskal_non_arbo(couples_graphe_t graph, int *tailleListe, float densite)
{
    arete_t *listeAretes;
    partition_t partition;
    element_t elem1,
        elem2;
    int i,
        j = 0;

    srand(time(0));
    listeAretes = (arete_t *)malloc(sizeof(arete_t) * graph.nbAretes);
    if (listeAretes)
    {
        //ordonnerAretesCroissant(&graph);
        fisherYate(&graph);
        partition = creer(graph.nbNoeuds);

        for (i = 0; i < graph.nbAretes; i++)
        {
            elem1 = graph.aretes[i].noeudDeb;
            elem2 = graph.aretes[i].noeudFin;
            if (classeMere(elem1, partition) != classeMere(elem2, partition))
            {
                partition = fusion(partition, elem1, elem2);
                listeAretes[j] = graph.aretes[i];
                j++;
            }
            else if ((float)rand() / (float)RAND_MAX > densite)
            {
                listeAretes[j] = graph.aretes[i];
                j++;
            }
        }
        *tailleListe = j;
    }
    detruirePartition(partition);

    return listeAretes;
}
