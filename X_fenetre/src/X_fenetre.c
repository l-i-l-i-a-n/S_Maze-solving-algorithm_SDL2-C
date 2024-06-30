#include "X_fenetre.h"

/**
 * @brief Permet de deplacer une fenetre selon un pas
 * 
 * @param window la fenetre
 * @param pas entier
 */
void deplacerFenetre(SDL_Window  * window, int pas)
{
    SDL_Rect window_dimensions = {0};

    SDL_GetWindowPosition(window, &window_dimensions.x, &window_dimensions.y);
    SDL_SetWindowPosition(window, window_dimensions.x, window_dimensions.y + pas);
}

/**
 * @brief Permet de redimensionner une fenetre selon un pas
 * 
 * @param window la fenetre
 * @param pas entier
 */
void redimensionnerFenetre(SDL_Window  * window, int pas)
{
    SDL_Rect window_dimensions = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    SDL_SetWindowSize(window, window_dimensions.w + pas, window_dimensions.h + pas);
}

/**
 * @brief Affiche plusieurs fenetres a l'ecran, les fait bouger, puis les redimensionnent
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window  * window[NB_FENETRES];
    SDL_DisplayMode screen;
    int           height,
                  weight,
                  pas,
                  j,
                  i = 0,
                  poseX = 0;
    char          nom[2];

    /* Initialisation de la SDL  + gestion de l'échec possible */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Error : SDL initialisation - %s\n", SDL_GetError()); 
        exit(EXIT_FAILURE);
    }

    //Recuperation de la taille de l'ecran
    if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        SDL_Log("Error : SDL Display Mode - %s\n", SDL_GetError()); 
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    weight = screen.w / NB_FENETRES ;
    height = screen.h / NB_FENETRES;

    //Creation de toutes les fenetres
    do 
    {
        sprintf(nom, "%d", i);
        window[i] = SDL_CreateWindow(nom, poseX, screen.h/2 - height/2, weight, height, SDL_WINDOW_RESIZABLE);
        i++;
        poseX += weight;
        SDL_Delay(200);
    }
    while(i < NB_FENETRES && window[i-1] != NULL);
    if(window[i-1] == NULL)
    {
        for(i = i-1; i>=0; i--)
        {
            SDL_DestroyWindow(window[i]);
        }
    }
    else
    {
        //On descend
        for(i=0; i<50; i++)
        {
            SDL_Delay(10);
            pas = 5;
            for(j=0; j<NB_FENETRES; j++)
            {
                deplacerFenetre(window[j], pas);
                pas = -pas;
            }
        }
        //On remonte
        for(i=0; i<50; i++)
        {
            SDL_Delay(10);
            pas = -5;
            for(j=0; j<NB_FENETRES; j++)
            {
                deplacerFenetre(window[j], pas);
                pas = -pas;
            }
        }
        //On agrandi
        for(i=0; i<50; i++)
        {
            SDL_Delay(10);
            pas = 5;
            for(j=0; j<NB_FENETRES; j++)
            {
                redimensionnerFenetre(window[j], pas);
                deplacerFenetre(window[j], -pas/2);
            }
        }

        SDL_Delay(500);

        //Destruction des fenetres
        for(i=0; i<NB_FENETRES; i++)
        {
            SDL_DestroyWindow(window[i]);
        }
    }

    SDL_Quit();
    return EXIT_SUCCESS;
}