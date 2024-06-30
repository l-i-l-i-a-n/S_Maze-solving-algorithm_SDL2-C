/**********************************************************/
/*Chandeze Marius & Meunier Killian                  2021 */
/*--------------------------------------------------------*/
/*                     liste_chainee.c                    */
/*              Traitement d'une liste chainee            */
/*               Module avec fonctions de base            */
/**********************************************************/

#include "liste_chainee.h"

/**************************************************************************/
/* Initialise une liste a NULL                                            */
/*                                                                        */
/* Principe :                                                             */
/* Retourner NULL                                                         */
/*                                                                        */
/* Lexique :                                                              */
/**************************************************************************/
liste_t initialisation_liste()
{
    return NULL;
}

/**************************************************************************/
/* Creer un maillon a partir d'une valeur                                 */
/*                                                                        */
/* Principe :                                                             */
/* Alloue de l'espace pour un maillon                                     */
/* Si l'espace pour ce maillon a bien ete reserve                         */
/*   On met la valeur en parametre dans le maillon                        */
/*   et on met son suivant a null                                         */
/* Retourner le maillon cree                                              */
/* IMPORTANT : Penser a verifier le maillon apres appel de cette fonction */
/*                                                                        */
/* Lexique :                                                              */
/* val : valeur que contiendra le maillon                                 */
/* u : numero de l'usine                                                  */
/**************************************************************************/
maillon_t *creerMaillon(int val)
{
    maillon_t *elt;

    elt = (maillon_t *)malloc(sizeof(maillon_t));
    if (elt)
    {
        elt->v = val;
        elt->suiv = NULL;
    }

    return elt;
}

/**************************************************************************/
/* Creer une liste, triée dans l'ordre décroissant, des k premières       */
/* valeurs d'une matrice                                                  */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la matrice tant que k > 0                                    */
/* Creer un maillon de la valeur courante de la matrice                   */
/* Et l'ajouter à la liste dans l'ordre décroissant (recherche_prec)      */
/* IMPORTANT : vérifier que k < n*m (taille de la matrice) avant          */
/*                                                                        */
/* Lexique :                                                              */
/* k : Nombre de valeurs dans la liste                                    */
/* matrice : Matrice des valeurs                                          */
/* l : liste vide qu'on va remplir                                        */
/* n : nombre de lignes dans la matrice                                   */
/* m : nombre de colonnes dans la matrice                                 */
/* i : indice courant pour le parcours des lignes de la matrice           */
/* j : indice courant pour le parcours des colonne de la matrice          */
/**************************************************************************/
booleen_t creerListe_kPremierElem_matrice(int k, int **matrice, liste_t *l, int n, int m, int *i, int *j)
{
    booleen_t trouve,
        ok = true;
    liste_t *pos;

    while (*i < n && k > 0 && ok)
    {
        while (*j < m && k > 0 && ok)
        {
            maillon_t *elt;
            elt = creerMaillon(matrice[*i][*j]);
            if (elt)
            {
                pos = recherche_prec(l, matrice[*i][*j], &trouve);
                ajout_lch(pos, elt);
                *j = *j + 1;
                k--;
            }
            else
            {
                ok = false;
            }
        }
        if (*j == m)
        {
            *j = 0;
            *i = *i + 1;
        }
    }

    return ok;
}

/**************************************************************************/
/* Creer une liste des k plus petites valeurs (kppv) d'une matrice        */
/*                                                                        */
/* Principe :                                                             */
/* Creer une liste des k premiers éléments de la matrice                  */
/* Parcourir la matrice à partir de la valeur k + 1                       */
/* Si la valeur courante est supérieure a la premiere valeur de la liste  */
/*   On enleve la tete de la liste                                        */
/*   On change sa valeur par la nouvelle valeur (qui est donc plus petite)*/
/*   On insere de nouveau cette tete au bon endroit (recherche_prec)      */
/* IMPORTANT : vérifier que k < n*m (taille de la matrice) avant          */
/*                                                                        */
/* Lexique :                                                              */
/* k : Nombre de valeurs dans la liste                                    */
/* matrice : Matrice des valeurs                                          */
/* l : liste vide qu'on va remplir                                        */
/* n : nombre de lignes dans la matrice                                   */
/* m : nombre de colonnes dans la matrice                                 */
/**************************************************************************/
booleen_t creerListe_kppv_matrice(int k, int **matrice, liste_t *l, int n, int m)
{
    int i = 0,
        j = 0;
    booleen_t trouve,
        ok;
    liste_t *pos;
    maillon_t *elt;

    ok = creerListe_kPremierElem_matrice(k, matrice, l, n, m, &i, &j);
    if (ok)
    {
        while (i < n && ok)
        {
            while (j < m && ok)
            {
                if (matrice[i][j] < (*l)->v)
                {
                    elt = creerMaillon(matrice[i][j]);
                    if (elt)
                    {
                        supp_lch(l);
                        pos = recherche_prec(l, elt->v, &trouve);
                        ajout_lch(pos, elt);
                    }
                    else
                    {
                        ok = false;
                    }
                }
                j++;
            }
            j = 0;
            i++;
        }
    }

    return ok;
}

/**************************************************************************/
/* Recherche du maillon precedent une valeur donnee de la liste triee,    */
/* dans l'ordre decroissant                                               */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la liste avec 2 pointeurs                                    */
/* Un pour le precedent et un pour le courant                             */
/* Si on trouve la valeur donnee, on renvoie le maillon precedent         */
/* Sinon, on renvoie la valeur d'insertion                                */
/*                                                                        */
/* Lexique :                                                              */
/* l : Liste triee dans l'ordre decroissant                               */
/* val : valeur contenu dans le maillon dont on veut le precedent         */
/* trouve : booleen qui permet de dire si on a trouve cette valeur        */
/**************************************************************************/
liste_t *recherche_prec(liste_t *l, int val, booleen_t *trouve)
{
    maillon_t *tmp;
    liste_t *prec;

    tmp = *l;
    prec = l;

    while (tmp && tmp->v > val)
    {
        prec = &(tmp->suiv);
        tmp = tmp->suiv;
    }

    if (tmp && tmp->v == val)
    {
        *trouve = true;
    }
    else
    {
        *trouve = false;
    }

    return prec;
}

/**************************************************************************/
/* Ajout d'un maillon dans une liste                                      */
/*                                                                        */
/* Principe :                                                             */
/* Definir le suivant du maillon a ajouter comme le suivant de maillon ou */
/* on veut ajouter ce nouveau maillon                                     */
/* Puis, remplacer le maillon ou on veut faire l'insertion par le nouveau */
/*                                                                        */
/* Lexique :                                                              */
/* b : pointeur sur le maillon qui va etre la position du nouveau maillon */
/* elt : nouveau maillon a inserer                                        */
/**************************************************************************/
void ajout_lch(liste_t *b, maillon_t *elt)
{
    elt->suiv = *b;
    *b = elt;
}

/**************************************************************************/
/* Supprime un maillon dans une liste                                     */
/*                                                                        */
/* Principe :                                                             */
/* Stocker le maillon a supprimer dans un maillon temporaire              */
/* Redefinir le maillon a supprimer comme son suivant                     */
/* Puis liberer l'espace memoire du maillon temporaire                    */
/*                                                                        */
/* Lexique :                                                              */
/* b : pointeur sur le maillon qui va etre supprime                       */
/**************************************************************************/
void supp_lch(liste_t *b)
{
    maillon_t *tmp;

    tmp = *b;
    *b = (*b)->suiv;
    free(tmp);
}

/**************************************************************************/
/* Affiche une liste dans le terminal                                     */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la liste tant que le maillon courant n'est pas nul           */
/* et afficher chaque valeur de chaque maillon                            */
/*                                                                        */
/* Lexique :                                                              */
/* l : Liste chainee                                                      */
/**************************************************************************/
void affichageListe(liste_t l)
{
    maillon_t *tmp;

    tmp = l;
    while (tmp != NULL)
    {
        printf("-> %d ", tmp->v);
        tmp = tmp->suiv;
    }
    printf("\n");
}

/**************************************************************************/
/* Libere l'espace memoire alloue a la liste en parametre                 */
/*                                                                        */
/* Principe :                                                             */
/* Parcourir la liste tant que le maillon courant n'est pas nul           */
/* et liberer chaque maillon                                              */
/*                                                                        */
/* Lexique :                                                              */
/* l : la liste a liberer                                                 */
/**************************************************************************/
void libererListe(liste_t l)
{
    maillon_t *tmp;

    while (l != NULL)
    {
        tmp = l->suiv;
        free(l);
        l = tmp;
    }
}

/**************************************************************************/
/* Supprime tous les maillons comportant un entier specifique de la liste */
/*                                                                        */
/* Principe :                                                             */
/* Parcourt la liste chainee en verifiant la valeur de chaque maillon     */
/* et le supprime de la liste si le numero correspond a l'entier souhaite */
/*                                                                        */
/* Lexique :                                                              */
/* u valeur                                                                */
/* l liste                                                                */
/**************************************************************************/
void supprimer_occurrence(int u, liste_t *l)
{                  /*********************/
    maillon_t *m;  /* maillon courant   */
    liste_t *prec; /* maillon precedent */
                   /*********************/
    prec = l;
    m = *l;
    while (m != NULL)
    {
        if (m->v == u)
        {
            m = m->suiv;
            supp_lch(prec);
        }
        else
        {
            prec = &(m->suiv);
            m = m->suiv;
        }
    }
}
