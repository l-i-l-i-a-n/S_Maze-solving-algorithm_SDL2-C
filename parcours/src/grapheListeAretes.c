#include "grapheListeAretes.h"

/**
 * @brief Génère un graphe aléatoire avec nbNoeuds noeuds
 * 
 * @param graphe Le graphe généré
 * @param nbNoeuds Le nombre de noeuds
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
 * @brief   Génère un graphe dans lequel tous les noeuds ont une arete avec le noeud suivant, et une avec le noeud en dessous (index du noeud + nbNoeuds)
 *          Le graphe peut donc être vu comme un labyrinthe sans aucun mur. sauf sur les 4 bords.
 *          L'algorithme de kruskal permettra de le transformer en un vrai labyrinthe qui correspondra à l'arbre couvrant trouvé par Kruskal.
 * 
 * @param graphe le graphe
 * @param size la largeur du labyrinthe/graphe voulue
 */
void genererGrapheLabyrinthe(couples_graphe_t *graphe, int size)
{
    int i, j = 2;
    graphe->nbNoeuds = size * size;
    graphe->nbAretes = graphe->nbNoeuds * 2 - (size * 2);
    graphe->aretes = (arete_t *)malloc(graphe->nbAretes * sizeof(arete_t));
    if (graphe->aretes != NULL && size > 2)
    {
        graphe->aretes[0].noeudDeb = 0;
        graphe->aretes[0].noeudFin = 1;
        graphe->aretes[0].poids = 1;
        graphe->aretes[1].noeudDeb = 0;
        graphe->aretes[1].noeudFin = size;
        graphe->aretes[1].poids = 1;
        for (i = 1; i < graphe->nbNoeuds - 1; i++)
        {
            if (((i + 1) % size != 0) && (i < (size - 1) * size))
            {
                graphe->aretes[j].noeudDeb = i;
                graphe->aretes[j].noeudFin = i + 1;
                graphe->aretes[j].poids = 1;
                j++;

                graphe->aretes[j].noeudDeb = i;
                graphe->aretes[j].noeudFin = i + size;
                graphe->aretes[j].poids = 1;
                j++;
            }
            else
            {
                if (i % size == size - 1 && (i < (size - 1) * size))
                {
                    graphe->aretes[j].noeudDeb = i;
                    graphe->aretes[j].noeudFin = i + size;
                    graphe->aretes[j].poids = 1;
                    j++;
                }
                else if (i >= (size - 1) * size && i < size * size - 1)
                {
                    graphe->aretes[j].noeudDeb = i;
                    graphe->aretes[j].noeudFin = i + 1;
                    graphe->aretes[j].poids = 1;
                    j++;
                }
            }
        }
    }
    else
    {
        puts("Error: memory allocation failed\n");
    }
}

/**
 * @brief Affiche toutes les aretes d'un graphe sur la sortie standard
 * 
 * @param graph le graphe
 */
void printAretes(couples_graphe_t graph)
{
    int i;
    puts("Affichage des arêtes : \n");
    for (i = 0; i < graph.nbAretes; ++i)
    {
        printf("%d ---%d--> %d\n", graph.aretes[i].noeudDeb, graph.aretes[i].poids, graph.aretes[i].noeudFin);
    }
}

/**
 * @brief Trie une liste d'aretes par ordre croissant (qSort)
 * 
 * @param graph Le graphe contenant les aretes a trier
 */
void ordonnerAretesCroissant(couples_graphe_t *graph)
{
    qsort(graph->aretes, graph->nbAretes, sizeof(arete_t), comparArete);
}

/**
 * @brief Permute la position de 2 aretes dans un tableau d'aretes
 * 
 * @param aretes le tableau d'aretes
 * @param i indice de la premiere arete
 * @param j indice de la deuxieme arete
 */
void exchange(arete_t aretes[], int i, int j)
{
    arete_t tmp = aretes[i];
    aretes[i] = aretes[j];
    aretes[j] = tmp;
}

/**
 * @brief Ordonner les aretes d'un rgaphe de façon aléatoire
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
        exchange(graph->aretes, i, j);
    }
}

/**
 * @brief Compare deux aretes selon leur poids
 * 
 * @param arete_1 La premiere arete
 * @param arete_2 La deuxieme arete
 * @return int Le résultat : 1 si arete_1 > arete_2 ; 0 si égaux ; -1 sinon
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
 * @brief   Lors de la génération du grapheLabyrinthe, vérifie si une arête générée aléatoirement est est valide et peut être ajoutée
 *          Une arête est valide si elle n'a pas déjà été ajoutée et si ce n'est pas une arête d'un noeud vers lui-même
 * 
 * @param graphe Le graphe
 * @param deb le noeud de début de l'arete
 * @param fin le noeud de fin de l'arete
 * @return bool_t true si pas valide ; false si valide
 */
bool_t aretePasValide(couples_graphe_t *graphe, int deb, int fin)
{
    bool_t status = false;
    int i;
    if (deb == fin)
        status = true;
    for (i = 0; i < graphe->nbAretes; i++)
    {
        if (graphe->aretes[i].noeudDeb == deb && graphe->aretes[i].noeudFin == fin)
            status = true;
    }
    return status;
}

/**
 * @brief Transforme un arbre couvrant en une matrice d'entiers correspondant aux directions dans lesquelles il y a les murs pour chaque case
 * 
 * @param arbre l'arbre à transformer
 * @param nbAretes le nombre d'aretes de l'arbre
 * @param taille la taille de la matrice à générer
 * @return int** la matrice générée
 */
int **arbreCouvrantToMatrice(arete_t *arbre, int nbAretes, int taille)
{
    int **matrice = NULL;
    int deb, fin, l, c;
    matrice = allocGrid(taille, taille);
    if (matrice != NULL)
    {
        for (int i = 0; i < nbAretes; i++)
        {
            deb = arbre[i].noeudDeb;
            fin = arbre[i].noeudFin;
            l = deb / taille;
            c = deb - l * taille;

            if (fin == deb + 1)
            {
                matrice[l][c] -= 4;
            }
            if (fin == deb + taille)
            {
                matrice[l][c] -= 2;
            }
        }
    }
    return matrice;
}

/**
 * @brief Renvoie un noeud du graphe choisi aleatoirement
 * 
 * @param graph le graphe
 * @param noeudDeb permet de spécifier un noeud de départ existant pour ue le noeud généré ne soit pas le même que celui de départ
 * @return int le numéro du noeud choisi aléatoirement
 */
int randomNoeud(couples_graphe_t graph, int noeudDeb)
{
    int random;
    srand(time(NULL));
    random = rand() % (graph.nbNoeuds);
    while (random == noeudDeb)
    {
        random = rand() % (graph.nbNoeuds);
    }
    return random;
}

/**
 * @brief Renvoie une liste des numéros des noeuds voisins d'un noeud donné en parametre
 * 
 * @param graphe le graphe
 * @param noeud le noeud pour lequel on cherche ses voisins
 * @param nbVoisins le nombre de voisins trouvés
 * @return int* la liste des voisins trouvés
 */
int *trouverVoisins(couples_graphe_t graphe, int noeud, int *nbVoisins)
{
    int i = 0;
    *nbVoisins = 0;
    int *voisins = (int *)malloc(4 * sizeof(int));
    if (voisins != NULL)
    {
        while (i < graphe.nbAretes && *nbVoisins < 4)
        {
            if (graphe.aretes[i].noeudDeb == noeud)
            {
                voisins[*nbVoisins] = graphe.aretes[i].noeudFin;
                (*nbVoisins)++;
            }
            if (graphe.aretes[i].noeudFin == noeud)
            {
                voisins[*nbVoisins] = graphe.aretes[i].noeudDeb;
                (*nbVoisins)++;
            }
            i++;
        }
    }
    else
    {
        printf("Error: malloc failed\n");
    }
    return voisins;
}
