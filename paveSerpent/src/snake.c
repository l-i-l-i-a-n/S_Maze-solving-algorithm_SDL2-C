#include "snake.h"

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
 * @brief Affiche 3 rectangles sur une fenetre, qui bougent
 * 
 * @param window La fenetre ou seront les rectangles
 * @param renderer Le rendu de la fenetre ou seront les rectangles
 */
void animationRectangles(SDL_Window * window, SDL_Renderer * renderer)
{
    SDL_Rect    window_dimensions = {0},
                r1 = {0},
                r2 = {0},
                r3 = {0};
    int         pasXr1 = 35,
                pasYr1 = 25, 
                green1 = 255,
                pasR3 = 50;

    SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);      
    
    //Dimensions r1
    r1.w = r1.h = window_dimensions.h/4;
    r1.x = (window_dimensions.w - r1.w)/2; 
    r1.y = (window_dimensions.h - r1.w)/2;
    //Dimensions r2
    r2.w = r2.h = window_dimensions.h/3;
    //Dimensions r3
    r3.w = r3.h = window_dimensions.h/7;
    r3.y = (window_dimensions.h - r3.w)/2;

    for(int i = 0; i< 200 ; i++)
    {
        //Faire "rebondir" r1 sur les bords de la fenetre 
        if(! (r1.x + r1.w + pasXr1 <= window_dimensions.w && r1.x >= 0))
        {
            pasXr1 = -pasXr1;
            green1 = (green1 -30)%255;
        }
        if(! (r1.y + r1.h + pasYr1 <= window_dimensions.h && r1.y >= 0))
        { 
            pasYr1 = -pasYr1; 
            green1 = (green1 -25)%255;
        }

        //Faire "rebondir" r3 sur les bords de la fenetre
        if(! (r3.x + r3.w + pasR3 <= window_dimensions.w && r3.x >= 0))
        {
            pasR3 = -pasR3;
        }

        //Avancer les rectangles
        r1.x = r1.x + pasXr1 ;
        r1.y = r1.y + pasYr1 ;

        r2.x = (r2.x + 40 ) % window_dimensions.w ;
        r2.y = (r2.y + 36) % window_dimensions.h ;
       
        r3.x = (r3.x + pasR3) ;
       
        //Afficher les rectangles dans le rendu
        SDL_SetRenderDrawColor(renderer,65, green1, 0,255);
        SDL_RenderFillRect(renderer, &r1);
        SDL_SetRenderDrawColor(renderer,255, 255, 0,255);
        SDL_RenderFillRect(renderer, &r2);
        SDL_SetRenderDrawColor(renderer,255, 0, 0,255);
        SDL_RenderFillRect(renderer, &r3);
        SDL_SetRenderDrawColor(renderer,255, 255, 255,255);
        
        SDL_RenderPresent(renderer);    
        SDL_Delay(40);
        SDL_RenderClear(renderer);
    }
}

/**
 * @brief Affiche et fait bouger 3 rectangles  l'ecran
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char **argv) 
{
    (void)argc;
    (void)argv;

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_DisplayMode screen;

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

    window = SDL_CreateWindow("Pavé de serpents", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
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

    animationRectangles(window, renderer);

    end_sdl(1, "Normal ending", window, renderer);
    return EXIT_SUCCESS;
}