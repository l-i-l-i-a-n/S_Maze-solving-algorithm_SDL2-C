#include "labyrintheVue.h"

/**
 * @brief Programme principal - Affiche un labyrinthe
 * 
 * @param argc 
 * @param argv 
 * @return int
 */
int main(int argc, char const *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_DisplayMode screen;
    SDL_Texture *texture,
        *perso;
    SDL_Rect positionLab = {0},
             tile = {0};

    (void)argc;
    (void)argv;

    // // INITIALISATION
    if (!initializeSDL())
    {
        quitSDL(false, "Error : SDL initialization", window, renderer);
        exit(EXIT_FAILURE);
    }

    if (SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        quitSDL(false, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE);
    }

    // Création de la fenetre
    window = SDL_CreateWindow("Labyrinthe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        quitSDL(false, "Error : SDL window creation", window, renderer);
        exit(EXIT_FAILURE);
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        quitSDL(false, "Error : SDL renderer creation", window, renderer);
        exit(EXIT_FAILURE);
    }

    texture = loadTextureFromImage("../images/texture.png", renderer);
    if (texture == NULL)
    {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    perso = loadTextureFromImage("../images/persos.png", renderer);
    if (perso == NULL)
    {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    // // TRAITEMENT

    SDL_Rect dest = {0};
    int n = 25, tailleLabyrintheCouvrant, m;
    couples_graphe_t graph;
    arete_t *labyrintheCouvrant;
    int **grille;

    m = n;
    genererGrapheLabyrinthe(&graph, n);
    labyrintheCouvrant = kruskal_non_arbo(graph, &tailleLabyrintheCouvrant, 0.9);
    grille = arbreCouvrantToMatrice(labyrintheCouvrant, tailleLabyrintheCouvrant, n);
    //drawCouplesGraph(graph, "labyrinthe_arbo", labyrintheCouvrant, tailleLabyrintheCouvrant);

    SDL_GetWindowSize(window, &positionLab.w, &positionLab.h);
    dimensionTile(&tile, positionLab, n, m);
    dimensionPerso(&dest, tile);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // fond
    drawLab(renderer, grille, n, m, tile, positionLab, texture);

    drawperso(renderer, perso, dest);

    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    quitSDL(true, "SDL END", window, renderer);

    return 0;
}

/**
 * @brief Calcule les dimensions d'une case du labyrinthe
 * 
 * @param tile Le rectangle qui represente une case
 * @param positionLab Dimensions et position du labyrinthe
 * @param n Nombre de lignes de la matrice qui represente le labyrinthe
 * @param m Nombre de colonnes de la matrice qui repesente le labyrinthe
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
 * @brief Calcule les dimensions du personnage
 * 
 * @param dest Rectangle qui represente le personnage
 * @param tile Rectangle qui represente une case du labyrinthe
 */
void dimensionPerso(SDL_Rect *dest, SDL_Rect tile)
{
    dest->w = tile.w * 0.5;
    dest->h = tile.h * 0.5;
}

/**
 * @brief Dessine le personnage a l'ecran
 * 
 * @param renderer Le rendu
 * @param perso La texture a appliquer au personnage
 * @param dest Rectangle qui represente le personnage
 */
void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest)
{
    SDL_Rect source = {0};

    source.w = 57;
    source.h = 43;
    SDL_RenderCopy(renderer, perso, &source, &dest);
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
 */
void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture)
{
    SDL_Rect wallNS = {0},              // Nord et Sud destination
        wallEO = {0},                   // Est et Ouest destination
        wallSourceNS = {0, 64, 64, 12}, // Nord et Sud source
        wallSourceEO = {0, 0, 12, 64},  // Est et Ouest source
        groundSource = {96, 126, 64, 64};
    int i = 0,
        j = 0;

    wallEO.w = tile.w * 0.1;
    wallEO.h = tile.h + (tile.h * 0.1);

    wallNS.w = tile.w + (tile.w * 0.1);
    wallNS.h = tile.h * 0.1;

    positionLab.x = (positionLab.w - tile.w * m) / 2;
    positionLab.y = (positionLab.h - tile.h * n) / 2;

    for (i = 0; i < n; i++)
    {
        tile.y = positionLab.y + tile.h * i;
        for (j = 0; j < m; j++)
        {
            tile.x = positionLab.x + tile.w * j;
            SDL_RenderCopy(renderer, texture, &groundSource, &tile);

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
