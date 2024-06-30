#include "labyrinthe_arbo.h"

/**
 * @brief Genere un graphe qui represente un labyrinthe arborescent
 * 
 * @param graphe Le graphe
 * @param size La taille du graphe = nombre de noeuds
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