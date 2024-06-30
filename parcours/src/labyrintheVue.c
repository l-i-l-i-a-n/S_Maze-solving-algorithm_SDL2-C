#include "labyrintheVue.h"

/**
 * @brief Calcule les dimensions et position du rectangle delimitant le labyrinthe
 * 
 * @param positionLab Le rectangle pour le labyrinthe
 * @param tile Dimensions et position d'une case
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 */
void dimensionsLab(SDL_Rect *positionLab, SDL_Rect tile, int n, int m)
{
    positionLab->x = (positionLab->w - tile.w * m) / 2;
    positionLab->y = (positionLab->h - tile.h * n) / 2;
}

/**
 * @brief Calcule les dimensions et position du rectangle definissant une case
 * 
 * @param tile Le rectangle pour une case
 * @param positionLab Le rectangle delimitant le labyrinthe
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 */
void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m)
{
    int a,
        b;

    a = positionLab.w / m;
    b = positionLab.h / n;
    tile->w = tile->h = a <= b ? a : b;
}

/**
 * @brief Calcule les dimensions du rectangle pour le personnage
 * 
 * @param dest Le Rectangle pour le personnage
 * @param tile Le rectangle pour une case
 */
void dimensionPerso(SDL_Rect *dest, SDL_Rect tile)
{
    dest->w = tile.w * 0.8;
    dest->h = tile.h * 0.8;
}

/**
 * @brief Dessine le personnage sur le rendu
 * 
 * @param renderer Le rendu
 * @param perso La texture pour le personnage
 * @param dest Le rectangle pour le personnage
 * @param ancienX Ancienne position x du personnage
 * @param ancienY Ancienne position y du personnage
 */
void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest, int ancienX, int ancienY)
{
    SDL_Rect droite = {0, 0, 35, 43}, // Sens ou le personnage regarde
             bas = {39, 0, 43, 35},
             gauche = {87, 0, 35, 43},
             haut = {124, 0, 43, 35};

    if(ancienX > dest.x)
    {
        SDL_RenderCopy(renderer, perso, &gauche, &dest);
    }
    else if(ancienX < dest.x)
    {
        SDL_RenderCopy(renderer, perso, &droite, &dest);
    }
    else if(ancienY > dest.y)
    {
        SDL_RenderCopy(renderer, perso, &haut, &dest);
    }
    else if(ancienY < dest.y)
    {
        SDL_RenderCopy(renderer, perso, &bas, &dest);
    }
    else
    {
        SDL_RenderCopy(renderer, perso, &haut, &dest);
    }
}

/**
 * @brief Dessine tout le labyrinthe sur le rendu
 * 
 * @param renderer Le rendu
 * @param grid La matrice representant le labyrinthe
 * @param n Nombre de lignes de la matrice
 * @param m Nombre de colonnes de la matrice
 * @param tile Le rectangle pour une case
 * @param positionLab Le rectangle delimitant le labyrinthe
 * @param texture La texture a appliquer pour le sol et les murs
 * @param marques Liste permettant de dessiner des tas de cailloux sur une case si non nulle
 */
void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t *marques)
{
    SDL_Rect wallNS = {0},              // Nord et Sud destination
        wallEO = {0},                   // Est et Ouest destination
        wallSourceNS = {0, 64, 64, 12}, // Nord et Sud source
        wallSourceEO = {0, 0, 12, 64},  // Est et Ouest source
        groundSource = {96, 126, 64, 64},
             stoneSource = {35, 0, 35, 30};
    int pos,
        i = 0,
        j = 0;

    wallEO.w = tile.w * 0.1;
    wallEO.h = tile.h + (tile.h * 0.1);

    wallNS.w = tile.w + (tile.w * 0.1);
    wallNS.h = tile.h * 0.1;

    positionLab.x = (positionLab.w - tile.w * m) / 2;
    positionLab.y = (positionLab.h - tile.h * n) / 2;

    // Sols
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        for (j = 0; j < m; j++)
        {
            tile.x = positionLab.x + tile.w * j;
            SDL_RenderCopy(renderer, texture, &groundSource, &tile);
            if (marques)
            {
                pos = i * n + j;
                if (marques[pos])
                {
                    SDL_RenderFillRect(renderer, &tile);
                    SDL_RenderCopy(renderer, texture, &stoneSource, &tile);
                }
            }
        }
    }

    // Murs
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        for (j = 0; j < m; j++)
        {
            tile.x = positionLab.x + tile.w * j;

            if (grid[i][j] & SUD)
            {
                wallNS.x = tile.x - (tile.w * 0.1) / 2;
                wallNS.y = tile.y + tile.h - (tile.h * 0.1) / 2;
                SDL_RenderFillRect(renderer, &wallNS);
                SDL_RenderCopy(renderer, texture, &wallSourceNS, &wallNS);
            }
            if (grid[i][j] & EST)
            {
                wallEO.x = tile.x + tile.w - (tile.w * 0.1) / 2;
                wallEO.y = tile.y - (tile.h * 0.1) / 2;
                SDL_RenderFillRect(renderer, &wallEO);
                SDL_RenderCopy(renderer, texture, &wallSourceEO, &wallEO);
            }
        }
    }

    // Grand mur de gauche
    tile.x = positionLab.x;
    wallEO.x = tile.x - (tile.w * 0.1) / 2;
    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        wallEO.y = tile.y - (tile.h * 0.1) / 2;
        SDL_RenderFillRect(renderer, &wallEO);
        SDL_RenderCopy(renderer, texture, &wallSourceEO, &wallEO);
    }

    // Grand mur du haut
    tile.y = positionLab.y;
    wallNS.y = tile.y - (tile.h * 0.1) / 2;
    for (i = 0; i < m; i++)
    {
        tile.x = positionLab.x + tile.w * i;
        wallNS.x = tile.x - (tile.w * 0.1) / 2;
        SDL_RenderFillRect(renderer, &wallNS);
        SDL_RenderCopy(renderer, texture, &wallSourceNS, &wallNS);
    }
}

/**
 * @brief Dessine des cailloux a un endroit donne
 * 
 * @param renderer Le rendu
 * @param indiceNoeud L'indice du noeud, pour trouver l'emplacement
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les cailloux
 * @param debut Savoir si c'est le debut d'un parcours pour l'afficher avec un couleur differente
 */
void drawStone(SDL_Renderer *renderer, int indiceNoeud, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t debut)
{
    int i, j;
    SDL_Rect source = {35, 0, 35, 30};

    i = indiceNoeud / n;
    j = indiceNoeud - i * m;

    tile.y = positionLab.y + tile.h * i + tile.h * 0.1;
    tile.x = positionLab.x + tile.w * j + tile.w * 0.1;
    tile.w = tile.h = tile.w * 0.8;

    if(debut)
    {
        source.x = 82;
    }

    SDL_RenderFillRect(renderer, &tile);
    SDL_RenderCopy(renderer, texture, &source, &tile);
}

/**
 * @brief Permet de dessiner le fond, le labyrinthe et le perso si non nul
 * 
 * @param marques Liste de booleen pour placer des cailloux
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle pour une case
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture a appliquer aux murs et aux sols
 * @param grille La matrice reresentant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 */
void drawAll(bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int ancienX, int ancienY)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(renderer, grille, n, m, tile, positionLab, texture, marques);
    if (perso)
    {
        drawperso(renderer, perso, destPerso, ancienX, ancienY);
    }
}

/**
 * @brief Permet d'afficher du texte a l'ecran
 * 
 * @param text Texte souhaite
 * @param dest La rectangle representant l'emplacement du texte
 * @param font La police d'ecriture a appliquer
 * @param renderer Le rendu
 * @return bool_t True si ca a fonctionne, false sinon
 */
bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer)
{
    SDL_Color color = {255, 255, 255, 255};
    SDL_Rect source = {0};
    SDL_Texture *texture;
    SDL_Surface *surface;

    //color.a = 255;

    surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        fputs("erreur ouverture de la police\n", stderr);
        return false;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        fputs("erreur transformation de la surface de la police en texture\n", stderr);
        SDL_FreeSurface(surface);
        return false;
    }
    SDL_FreeSurface(surface);
    SDL_QueryTexture(texture, NULL, NULL, &source.w, &source.h);
    SDL_RenderCopy(renderer, texture, &source, &dest);
    SDL_DestroyTexture(texture);
    return true;
}

/**
 * @brief Calcule les dimensions pour les rectangles representant les boutons
 * 
 * @param dijkstra Rectangle pour le bouton dijkstra
 * @param a_etoile Rectangle pour le bouton A*
 * @param profondeur Rectangle pour le bouton profondeur
 * @param quit Rectangle pour le bouton quitter
 * @param positionLab Rectangle delimitant le labyrinthe
 */
void dimensionButtons(SDL_Rect *dijkstra, SDL_Rect *a_etoile, SDL_Rect *profondeur, SDL_Rect *quit, SDL_Rect positionLab)
{
    dijkstra->w = positionLab.w * 0.3;
    dijkstra->h = positionLab.h * 0.1;
    dijkstra->x = (positionLab.w - dijkstra->w) / 2;
    dijkstra->y = positionLab.h * 0.2 + dijkstra->h / 2;
    a_etoile->w = positionLab.w * 0.1;
    a_etoile->h = positionLab.h * 0.1;
    a_etoile->x = (positionLab.w - a_etoile->w) / 2;
    a_etoile->y = dijkstra->y + dijkstra->h + a_etoile->h / 2;
    profondeur->w = positionLab.w * 0.3;
    profondeur->h = positionLab.h * 0.1;
    profondeur->x = (positionLab.w - profondeur->w) / 2;
    profondeur->y = a_etoile->y + a_etoile->h + profondeur->h / 2;
    quit->w = positionLab.w * 0.3;
    quit->h = positionLab.h * 0.1;
    quit->x = (positionLab.w - quit->w) / 2;
    quit->y = positionLab.h - quit->h * 1.5;
}

/**
 * @brief Permet d'afficher le menu a l'ecran
 * 
 * @param renderer Le rendu
 * @param font La police d'ecriture a appliquer
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param dijkstra Rectangle pour le bouton dijkstra
 * @param a_etoile Rectangle pour le bouton A*
 * @param profondeur Rectangle pour le bouton profondeur
 * @param quit Rectangle pour le bouton quitter
 */
void drawMenu(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect positionLab, SDL_Rect dijkstra, SDL_Rect a_etoile, SDL_Rect profondeur, SDL_Rect quit)
{
    SDL_Rect titre = {0};

    titre.w = positionLab.w * 0.5;
    titre.h = positionLab.h * 0.2;
    titre.x = (positionLab.w - titre.w) / 2;

    /*SDL_SetRenderDrawColor(renderer, 140, 120, 120, 128);
    SDL_RenderFillRect(renderer, &dijkstra);
    SDL_RenderFillRect(renderer, &a_etoile);
    SDL_RenderFillRect(renderer, &profondeur);*/

    SDL_SetRenderDrawColor(renderer, 185, 25, 10, 128);
    SDL_RenderFillRect(renderer, &quit);

    drawText("Parcours !", titre, font, renderer);
    drawText("Dijkstra", dijkstra, font, renderer);
    drawText("A*", a_etoile, font, renderer);
    drawText("Profondeur", profondeur, font, renderer);
    drawText("Quitter", quit, font, renderer);
}

/**
 * @brief Dessine le fond
 * 
 * @param renderer Le rendu
 * @param background Texture appliquee au fond
 * @param window_dimensions Dimensions et position de la fenetre
 */
void drawBackground(SDL_Renderer * renderer, SDL_Texture *background, SDL_Rect window_dimensions)
{
    SDL_Rect source = {0},
             dest = {0};
    
    dest.w = window_dimensions.w;
    dest.h = window_dimensions.h;
    SDL_QueryTexture(background, NULL, NULL, &source.w, &source.h); 
    SDL_RenderCopy(renderer, background, &source, &dest);
}

/**
 * @brief Boucle de "jeu" de l'executable
 * 
 * @param window La fenetre
 * @param renderer Le rendu de la fenetre
 * @param font La police d'ecriture a appliquer au texte 
 * @param texture La texture pour les murs et les sols 
 * @param perso La texture pour le personnage
 * @param graph Le graphe representant le labyrinthe
 * @param n Nombre de lignes de la matrice 
 * @param m Nombre de colonnes de la matrice 
 * @param grille La matrice representant le labyrinthe
 */
void menuLoop(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *texture, SDL_Texture *perso, SDL_Texture* background, couples_graphe_t graph, int n, int m, int **grille)
{
    SDL_Rect positionLab = {0},
             tile = {0},
             destPerso = {0},
             dijkstraR = {0},
             a_etoile = {0},
             profondeur = {0},
             quit = {0},
             mouse = {0};
    SDL_bool program_on = SDL_TRUE,
             paused = SDL_FALSE;
    int deb,
        fin;
    liste_t chemin;

    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
    dimensionTile(&tile, positionLab, n, m);
    dimensionsLab(&positionLab, tile, n, m);
    dimensionPerso(&destPerso, tile);
    dimensionButtons(&dijkstraR, &a_etoile, &profondeur, &quit, positionLab);

    while (program_on)
    {
        SDL_Event event; // Evènement à traiter

        while (program_on && SDL_PollEvent(&event))
        { // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
            // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    // Calcul des dimensions quand la fenetre change de taille
                    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
                    dimensionTile(&tile, positionLab, n, m);
                    dimensionsLab(&positionLab, tile, n, m);
                    dimensionPerso(&destPerso, tile);
                    dimensionButtons(&dijkstraR, &a_etoile, &profondeur, &quit, positionLab);
                }
                break;
            case SDL_QUIT:
                program_on = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE: // 'ESCAPE'
                case SDLK_q:      // 'q'
                    program_on = SDL_FALSE;
                    break;
                default:
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&mouse.x, &mouse.y);
                //Calcul des coordonnees par rapport a l'emplacement du labyrinthe

                if (SDL_BUTTON(SDL_BUTTON_LEFT))
                {
                    if (mouse.x >= dijkstraR.x && mouse.x <= dijkstraR.x + dijkstraR.w && mouse.y >= dijkstraR.y && mouse.y <= dijkstraR.y + dijkstraR.h)
                    {
                        paused = SDL_TRUE;
                        deb = randomNoeud(graph, -1);
                        fin = randomNoeud(graph, deb);
                        drawLab(renderer, grille, n, m, tile, positionLab, texture, NULL);
                        drawStone(renderer, deb, n, m, tile, positionLab, texture, true);
                        drawStone(renderer, fin, n, m, tile, positionLab, texture, false);
                        SDL_RenderPresent(renderer);
                        // Effectue Dijkstra 5 fois en partant de l'ancien point de fin à chaque fois
                        for (int i = 0; i < 5; i++)
                        {
                            if (dijkstra(graph, deb, fin, &chemin, n * m))
                            {
                                supp_lch(&chemin);
                                SDL_Delay(500);
                                drawLab(renderer, grille, n, m, tile, positionLab, texture, NULL);
                                drawStone(renderer, deb, n, m, tile, positionLab, texture, true);
                                drawStone(renderer, fin, n, m, tile, positionLab, texture, false);
                                while (chemin != NULL)
                                {
                                    drawStone(renderer, chemin->v, n, m, tile, positionLab, texture, false);
                                    supp_lch(&chemin);
                                    SDL_RenderPresent(renderer);
                                    SDL_Delay(200);
                                }
                                libererListe(chemin);
                                SDL_RenderClear(renderer);
                                SDL_Delay(500);
                                paused = SDL_FALSE;
                            }
                            else
                            {
                                fprintf(stderr, "erreur dijkstra\n");
                            }
                            deb = fin;
                            fin = randomNoeud(graph, deb);
                        }
                    }
                    else if (mouse.x >= a_etoile.x && mouse.x <= a_etoile.x + a_etoile.w && mouse.y >= a_etoile.y && mouse.y <= a_etoile.y + a_etoile.h)
                    {
                        paused = SDL_TRUE;
                        deb = randomNoeud(graph, -1);
                        fin = randomNoeud(graph, deb);
                        drawLab(renderer, grille, n, m, tile, positionLab, texture, NULL);
                        drawStone(renderer, deb, n, m, tile, positionLab, texture, true);
                        drawStone(renderer, fin, n, m, tile, positionLab, texture, false);
                        SDL_RenderPresent(renderer);
                        if (astar(graph, deb, fin, &chemin, n, m))
                        {
                            supp_lch(&chemin);
                            SDL_Delay(1000);
                            while (chemin != NULL)
                            {
                                drawStone(renderer, chemin->v, n, m, tile, positionLab, texture, false);
                                supp_lch(&chemin);
                                SDL_RenderPresent(renderer);
                                SDL_Delay(200);
                            }
                            libererListe(chemin);
                            SDL_RenderClear(renderer);
                            SDL_Delay(2000);
                            paused = SDL_FALSE;
                        }
                        else
                        {
                            paused = SDL_FALSE;
                            SDL_RenderClear(renderer);
                            fprintf(stderr, "erreur astar\n");
                        }
                    }
                    else if (mouse.x >= profondeur.x && mouse.x <= profondeur.x + profondeur.w && mouse.y >= profondeur.y && mouse.y <= profondeur.y + profondeur.h)
                    {
                        paused = SDL_TRUE;
                        deb = randomNoeud(graph, -1);
                        drawLab(renderer, grille, n, m, tile, positionLab, texture, NULL);
                        drawStone(renderer, deb, n, m, tile, positionLab, texture, true);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(1000);
                        parcoursEnProfondeur(graph, deb, renderer, n, m, tile, positionLab, texture, grille, destPerso, perso, 150);
                        SDL_RenderClear(renderer);
                        SDL_Delay(1000);
                        paused = SDL_FALSE;
                    }
                    else if (mouse.x >= quit.x && mouse.x <= quit.x + quit.w && mouse.y >= quit.y && mouse.y <= quit.y + quit.h)
                    {
                        program_on = SDL_FALSE;
                    }
                }
                break;
            default:
                break;
            }
        }
        if (!paused)
        {
            drawBackground(renderer, background, positionLab);
            drawMenu(renderer, font, positionLab, dijkstraR, a_etoile, profondeur, quit);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
            SDL_RenderPresent(renderer);
            SDL_RenderClear(renderer);
        }
        SDL_Delay(50);
    }
}