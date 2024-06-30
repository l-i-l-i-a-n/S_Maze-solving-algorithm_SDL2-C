#include "graphviz.h"

/**
 * @brief Creer les differentes chaines de caracteres utiles pour dessiner le graphe
 * 
 * @param name Nom general des fichiers
 * @param dir Chemin du dossier ou stcoker les fichiers
 * @param dotpath Chemin du fichier .dot 
 * @param pngPath Chemin du fichier png
 * @param command Commande pour transformer le .dot en png
 */
void createStrings(char *name, char *dir, char *dotPath, char *pngPath, char *command)
{
    // Chemin du fichier .dot
    strcpy(dotPath, dir);
    strcat(dotPath, name);
    strcat(dotPath, ".dot");
    // Chemin du fichier png
    strcpy(pngPath, dir);
    strcat(pngPath, name);
    strcat(pngPath, ".png");
    // Commande pour le fichier png
    strcpy(command, "dot -Tpng ");
    strcat(command, dotPath);
    strcat(command, " -o ");
    strcat(command, pngPath);
}

/**
 * @brief Libere les choses propres a graphviz
 * 
 * @param graph_context 
 * @param graph 
 */
void freeAll(GVC_t *graph_context, Agraph_t *graph)
{
    //  Libération mémoire du contexte du graphe
    gvFreeLayout(graph_context, graph);
    gvFreeContext(graph_context);
    //  Libération mémoire du graphe
    agclose(graph);
}

/**
 * @brief Genere le fichier .dot du graphe
 * 
 * @param graph_context 
 * @param graph 
 * @param fic 
 */
void generateGraphviz(GVC_t *graph_context, Agraph_t *graph, FILE *fic)
{
    //agwrite(graph, stdout);                      //  Ecriture sur la sortie standard en dot sans formatage
    gvLayout(graph_context, graph, "dot");      //  Permet de dessiner le graphe "correctement"
    gvRender(graph_context, graph, "dot", fic); //  Génération du fichier .dot
}

/**
 * @brief 
 * 
 * @param command Commande système pour generer une image à partir du fichier .dot
 */
void generatePng(char *command)
{
    int sys;

    sys = system(command);
    if (sys != 0)
    {
        fprintf(stderr, "Impossible de lancer la commande : %s\n", command);
    }
}

/**
 * @brief Creer le fichier .dot et le fichier png pour la partition en parametres
 * 
 * @param partition La partition a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawPartitionGraph(partition_t partition, int n, char *name)
{
    Agraph_t *graph;
    FILE *fic;
    GVC_t *graph_context;
    int i = 0,
        j = 0;
    char indexClasse[3],
        indexElement[3],
        dotPath[50],
        pngPath[50],
        command[100],
        *dir = "../graphviz/";
    classe_t *classes;
    element_t *elements = NULL;

    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if (fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graph = agopen(name, Agdirected, 0);

            agsafeset(graph, "label", name, "");

            classes = lister_partition(partition, n);

            // Dessine les noeuds
            while (i < n && classes[i] != -1)
            {
                sprintf(indexClasse, "%d", classes[i]);
                agnode(graph, indexClasse, 1);
                i++;
            }

            //Dessine les arretes
            i = 0;
            while (i < n && classes[i] != -1)
            {
                elements = lister_classe(partition, classes[i], n);
                sprintf(indexClasse, "%d", classes[i]);
                while (j < n && elements[j] != -1)
                {
                    sprintf(indexElement, "%d", elements[j]);
                    agedge(graph, agnode(graph, indexElement, 1), agnode(graph, indexClasse, 1), NULL, 1);
                    j++;
                }
                i++;
                j = 0;
            }

            generateGraphviz(graph_context, graph, fic);
            generatePng(command);

            free(classes);
            if (elements != NULL)
            {
                free(elements);
            }
            freeAll(graph_context, graph);
            fclose(fic);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...\n");
        }
    }
    else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}

/**
 * @brief Creer le fichier .dot et le fichier png pour la matrice d'adjacence en parametres
 * 
 * @param matrix La matrice d'adjacence a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawAdjencyMatrixGraph(int *matrix, int n, char *name)
{
    Agraph_t *graph;
    FILE *fic;
    GVC_t *graph_context;
    int i = 0,
        j = 0;
    char nodeName[11],
        nodeName2[11],
        dotPath[50],
        pngPath[50],
        command[100],
        *dir = "../graphviz/";

    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if (fic)
    {
        graph_context = gvContext();
        if (graph_context)
        {
            graph = agopen(name, Agundirected, 0);

            agsafeset(graph, "label", name, "");

            // Dessine les noeuds
            for (i = 0; i < n; i++)
            {
                sprintf(nodeName, "%d", i);
                agnode(graph, nodeName, 1);
            }

            // Dessine les arretes
            for (i = 0; i < n; i++)
            {
                for (j = i; j < n; j++)
                {
                    sprintf(nodeName, "%d", i);
                    if (matrix[i * n + j] == 1)
                    {
                        sprintf(nodeName2, "%d", j);
                        agedge(graph, agnode(graph, nodeName, 1), agnode(graph, nodeName2, 1), NULL, 1);
                    }
                }
            }

            generateGraphviz(graph_context, graph, fic);
            generatePng(command);

            freeAll(graph_context, graph);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...\n");
        }
        fclose(fic);
    }
    else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}

/**
 * @brief Creer le fichier .dot et le fichier png pour le graphe (couple) en parametres
 * 
 * @param sourceGraph Graphe sous forme couple d'arete + nombre de noeuds
 * @param name Nom pour les fichiers generes
 * @param listeA Liste d'aretes a colorier en rouge (exemple : arbre couvrant) peut etre null
 * @param tailleListeA Taille de la liste d'aretes
 */
void drawCouplesGraph(couples_graphe_t sourceGraph, char *name, arete_t *listeA, int tailleListeA)
{
    Agraph_t *graph;
    Agedge_t *edge;
    FILE *fic;
    GVC_t *graph_context;
    int i = 0;
    char nodeName[11],
        nodeName2[11],
        poids[11],
        dotPath[50],
        pngPath[50],
        command[100],
        *dir = "../graphviz/";

    createStrings(name, dir, dotPath, pngPath, command);

    fic = fopen(dotPath, "w");
    if (fic)
    {
        graph_context = gvContext();

        if (graph_context)
        {
            graph = agopen(name, Agundirected, 0);

            agsafeset(graph, "label", name, "");

            for (i = 0; i < sourceGraph.nbNoeuds; i++)
            {
                sprintf(nodeName, "%d", i);
                agnode(graph, nodeName, 1);
            }

            // Dessine les arretes
            for (i = 0; i < sourceGraph.nbAretes; i++)
            {
                sprintf(nodeName, "%d", sourceGraph.aretes[i].noeudDeb);
                sprintf(nodeName2, "%d", sourceGraph.aretes[i].noeudFin);
                edge = agedge(graph, agnode(graph, nodeName, 1), agnode(graph, nodeName2, 1), NULL, 1);
                sprintf(poids, "%d", sourceGraph.aretes[i].poids);
                agsafeset(edge, "label", poids, "");
            }

            if (listeA)
            {
                for (i = 0; i < tailleListeA; i++)
                {
                    sprintf(nodeName, "%d", listeA[i].noeudDeb);
                    sprintf(nodeName2, "%d", listeA[i].noeudFin);
                    sprintf(poids, "%d", listeA[i].poids);
                    agsafeset(agedge(graph, agnode(graph, nodeName, 1), agnode(graph, nodeName2, 1), NULL, 0), "color", "red", "");
                }
            }

            generateGraphviz(graph_context, graph, fic);
            generatePng(command);

            freeAll(graph_context, graph);
            fclose(fic);
        }
        else
        {
            fprintf(stderr, "Impossible de créer le contexte de graphe...");
        }
    }
    else
    {
        fprintf(stderr, "Impossible d'ouvrir le fichier...\n");
    }
}
