#include "grapheListeAretes.h"

/**
 * @brief Genere un graphe sous forme de couple liste d'aretes et nombre de noeuds
 * 
 * @param graphe Le graphe genere
 * @param nbNoeuds Le nombre de noeuds du graphe souhaite
 */
void genererGraphe(couples_graphe_t *graphe, int nbNoeuds)
{
    int i, nbAretes = 0, deb, fin;
    graphe->nbNoeuds = nbNoeuds;
    srand(time(NULL));
    nbAretes = rand() % (nbNoeuds * 2) + nbNoeuds / 2;
    graphe->aretes = (arete_t *)malloc(nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL)
    {
        graphe->nbAretes = 0;
        for (i = 0; i < nbAretes; i++)
        {
            graphe->aretes[i].poids = 1;
            do
            {
                deb = rand() % nbNoeuds;
                fin = rand() % (nbNoeuds - deb) + deb;
                graphe->aretes[i].noeudDeb = deb;
                graphe->aretes[i].noeudFin = fin;
            } while (aretePasValide(graphe, deb, fin));

            (graphe->nbAretes)++;
        }
        graphe->nbAretes = nbAretes;
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

/**
 * @brief Ordonne les aretes du graphe dans l'ordre croissant des poids
 * 
 * @param graph Le graphe
 */
void ordonnerAretesCroissant(couples_graphe_t *graph)
{
    qsort(graph->aretes, graph->nbAretes, sizeof(arete_t), comparArete);
}

/**
 * @brief Fonction qui compare 2 aretes selon leur poids
 * 
 * @param arete_1 L'arete a
 * @param arete_2 L'arete b
 * @return int -1 si a<b ; 1 si a>b; 0 si a=b (en terme de poids)
 */
int comparArete(const void *arete_1, const void *arete_2)
{
    const arete_t *ar1 = arete_1;
    const arete_t *ar2 = arete_2;
    if (ar1->poids > ar2->poids)
    {
        return 1;
    }
    else if (ar1->poids == ar2->poids)
    {
        return 0;
    }
    return -1;
}

/**
 * @brief Dit si une arete est valide ou non (on ne veut pas d'arete qui pointe sur son noeud de debut, ou alors si elle a deja ete inseree dans le graphe)
 * 
 * @param graphe Le graphe
 * @param deb Noeud de debut de l'arete
 * @param fin Noeud de fin de l'arete
 * @return bool_t Renvoie True si l'arete est valide, false sinon
 */
bool_t aretePasValide(couples_graphe_t *graphe, int deb, int fin)
{
    bool_t status = false;
    int i;
    if (deb == fin)
    {
        status = true;
    }
    else
    {
        for (i = 0; i < graphe->nbAretes; i++)
        {
            if (graphe->aretes[i].noeudDeb == deb && graphe->aretes[i].noeudFin == fin)
                status = true;
        }
    }
    return status;
}

/**
 * @brief Permet de liberer la memoire d'un graphe 
 * 
 * @param graphe Le graphe
 */
void supprimerGraphe(couples_graphe_t graphe)
{
    free(graphe.aretes);
}

/**
 * @brief Permute deux aretes
 * 
 * @param aretes Tableau d'aretes
 * @param i Indice de la premiere arete
 * @param j Indice de la deuxieme arete
 */
void permute(arete_t aretes[], int i, int j)
{
    arete_t tmp = aretes[i];
    aretes[i] = aretes[j];
    aretes[j] = tmp;
}

/**
 * @brief Effectue Le melange de Fisher Yate sur les aretes d'un graphe
 * 
 * @param graph Le graphe
 */
void fisherYate(couples_graphe_t *graph)
{
    int i, j;
    srand(time(NULL));
    for (i = graph->nbAretes - 1; i > 1; i--)
    {
        j = rand() % i + 1;
        permute(graph->aretes, i, j);
    }
}