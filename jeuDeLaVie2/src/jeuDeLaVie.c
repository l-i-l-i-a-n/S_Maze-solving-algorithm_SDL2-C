#include "jeuDeLaVie.h"

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void end_sdl(char ok, char const* msg, SDL_Window* window, SDL_Renderer* renderer)
{                           
  char msg_formated[255];                                         
  int l;                                                          

  if (!ok) 
  {                                                      
         strncpy(msg_formated, msg, 250);                                 
         l = strlen(msg_formated);                                        
         strcpy(msg_formated + l, " : %s\n");                     
         SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                            
}


/**
 * @brief Affiche une matrice d'entiers dans le rendu
 * 
 * @param renderer 
 * @param grille 
 * @param n 
 * @param m 
 * @param cell
 */
void drawGrid(SDL_Renderer *renderer, int ** grille, int n, int m, SDL_Rect cell) 
{
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          rectangle;

	rectangle.w = cell.w;
	rectangle.h = cell.h;
    poseX = cell.x;
    poseY = cell.y;

	for(i = 0; i < n; i++) {
		rectangle.y = poseY + rectangle.h * i;
		for(j = 0; j < m; j++) {
			rectangle.x = poseX + rectangle.w * j;
            
            SDL_SetRenderDrawColor(renderer, !grille[i][j] * 255, !grille[i][j] * 255, !grille[i][j] * 255, 255);
			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
	SDL_RenderPresent(renderer);
}

/**
 * @brief Permet de calculer les dimensions d'une cellule par rapport a la taille de la fenetre
 * 
 * @param window la fenetre
 * @param cell la cellule (SDL_Rect)
 * @param n nombre de lignes de la grille
 * @param m nombre de colonnes de la grille
 */
void cellDimensions(SDL_Window * window, SDL_Rect * cell, int n, int m)
{
    SDL_Rect window_dimensions = {0};

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
    cell->w = window_dimensions.h / m ;
    cell->h = window_dimensions.h / n ;    
    cell->x = (window_dimensions.w - cell->w * m) / 2 ;
    cell->y = (window_dimensions.h - cell->h * n) / 2 ;
}

/**
 * @brief Boucle de jeu du jeu de la vie facon labyrinthe
 * 
 * @param window 
 * @param renderer 
 * @param grid 
 * @param n 
 * @param m 
 * @param rule 
 */
void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** grid, int n, int m, rule_t * rule)
{
    SDL_bool  program_on = SDL_TRUE,                          // Booléen pour dire que le programme doit continuer
              paused = SDL_FALSE;                             // Booléen pour dire que le programme est en pause
    SDL_Rect  mouse = {0},
              cell = {0};

    // Initialisation des coordonnees
    cellDimensions(window, &cell, n, m);

    while (program_on) 
    {                                   // La boucle des évènements
        SDL_Event event;                // Evènement à traiter

        while (program_on && SDL_PollEvent(&event)) 
        {                               // Tant que la file des évènements stockés n'est pas vide et qu'on n'a pas
                                        // terminé le programme Défiler l'élément en tête de file dans 'event'
            switch (event.type) 
            {      
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_RESIZED)
                    {
                        // Calcul des dimensions d'une cellule quand la fenetre change de taille
                        cellDimensions(window, &cell, n, m);
                    }
                    break;
                case SDL_QUIT:                         
                    program_on = 0;                   
                    break;
                case SDL_KEYDOWN:                              
                    switch (event.key.keysym.sym) 
                    {             
                        case SDLK_p:                                // 'p'
                        case SDLK_SPACE:                            // 'SPC'
                            paused = !paused;                       // basculement pause/unpause
                            break;
                        case SDLK_ESCAPE:                           // 'ESCAPE'  
                        case SDLK_q:                                // 'q'
                            program_on = 0;                                                         
                            break;
                        default:                      
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:     
                    SDL_GetMouseState(&mouse.x, &mouse.y);
                    //Calcul des coordonnees par rapport a l'emplacement du labyrinthe
                    mouse.x = (mouse.x - cell.x) / cell.w;
                    mouse.y = (mouse.y - cell.y) / cell.h;
                    if (SDL_BUTTON(SDL_BUTTON_LEFT) ) 
                    {                       
                        change_state(&grid, n, m, mouse.x, mouse.y);
                    } 
                    else if (SDL_BUTTON(SDL_BUTTON_RIGHT) ) 
                    {                                           
                        change_state(&grid, n, m, mouse.x, mouse.y);          
                    }
                    break;
                default:                                            
                    break;
            }
        }
        // Changement du fond en fonction de la position de la souris
        SDL_GetMouseState(&mouse.x, &mouse.y);
        SDL_SetRenderDrawColor(renderer, (mouse.x/3) % 255, ((mouse.x + mouse.y) / 3) % 255, (mouse.y/3) % 255, 255);
	    SDL_RenderClear(renderer);

        drawGrid(renderer, grid, n, m, cell);        
        if (!paused) 
        {                                  
            nextIteration(&grid, n, m, rule);             // la vie continue... 
        }
        SDL_Delay(50);                                  
    }
}

/**
 * @brief Affiche le jeu de la vie facon labyrinthe
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window       * window = NULL;
    SDL_Renderer     * renderer = NULL;
    SDL_DisplayMode    screen;
    int             ** grid,
                       n = 50,
                       m = 50;
    rule_t           * rule;

    /* INITIALISATIONS */

    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
        end_sdl(0, "ERROR SDL INIT", window, renderer);
        exit(EXIT_FAILURE); 
    }

    if(SDL_GetCurrentDisplayMode(0, &screen) != 0)
    {
        end_sdl(0, "ERROR GET_DISPLAY_MODE", window, renderer);
        exit(EXIT_FAILURE); 
    }

    window = SDL_CreateWindow("Jeu de la vie 2 (Labyrinthe)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                screen.w * 0.8, screen.h * 0.8, SDL_WINDOW_RESIZABLE);
    if (window == NULL) 
    {
        end_sdl(0, "ERROR WINDOW CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) 
    {
        end_sdl(0, "ERROR RENDERER CREATION", window, renderer);
        exit(EXIT_FAILURE); 
    }

    /*TRAITEMENT*/

    rule = malloc(sizeof(rule_t));
	if(rule) 
    {
        grid = allocGrid(n,m);
        if(grid)
        {
            grid = createRandomGrid(grid, n, m);
            initMaze(rule);	

            gameLoop(window, renderer, grid, n, m, rule);
            
            free(rule);
            freeGrid(grid, n);
        }
    }

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}
