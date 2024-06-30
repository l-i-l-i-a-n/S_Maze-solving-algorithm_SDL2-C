#include "main.h"

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
        *perso,
        *background;
    TTF_Font *font;

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

    if (TTF_Init() != 0)
    {
        quitSDL(false, "ERROR TTF INIT", window, renderer);
        exit(EXIT_FAILURE);
    }

    font = TTF_OpenFont("../fonts/font.ttf", 500);
    if (font == NULL)
    {
        quitSDL(false, " error font\n", window, renderer);
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
    background = loadTextureFromImage("../images/background.png", renderer);
    if (background == NULL)
    {
        quitSDL(0, " error texture\n", window, renderer);
        exit(EXIT_FAILURE);
    }

    // // TRAITEMENT

    int n = 10, tailleLabyrintheCouvrant, m;
    couples_graphe_t graph;
    int **grille;

    m = n;
    genererGrapheLabyrinthe(&graph, n);
    graph.aretes = kruskal_non_arbo(graph, &tailleLabyrintheCouvrant, 0.9);
    graph.nbAretes = tailleLabyrintheCouvrant;
    grille = arbreCouvrantToMatrice(graph.aretes, tailleLabyrintheCouvrant, n);

    menuLoop(window, renderer, font, texture, perso, background, graph, n, m, grille);

    free(graph.aretes);
    for (int i = 0; i < n; ++i)
    {
        free(grille[i]);
    }
    free(grille);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(perso);
    quitSDL(true, "SDL END", window, renderer);

    return 0;
}
