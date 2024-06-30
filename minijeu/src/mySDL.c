#include "mySDL.h"

/**
 * @brief Initialise la librairie SDL
 * @return un booleen true si tout la librairie s'est initialisee avec succes, false sinon
 */
bool_t initializeSDL(void) 
{
    bool_t status = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
    {
    	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    	status = false; 
	  }
	return status;
}

/**
 * @brief Permet de charger une texture SDL a partir de son chemin et d'un renderer SDL
 * 
 * @param name chemin d'acces au fichier png
 * @param renderer rendu a dans lequel charger
 */
SDL_Texture* loadTextureFromImage(char *name, SDL_Renderer *renderer) {
	SDL_Texture* texture;
	SDL_Surface* surface;
	
	surface = IMG_Load(name);
	if(surface == NULL) 
  {
    IMG_Quit();
		return NULL;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
  IMG_Quit();
	return texture;
}

/**
 * @brief Permet de fermer toute la sdl et d'indiquer un message d'erreur si il y en a une
 * 
 * @param ok 0 : erreur, 1 :normal
 * @param msg message de fin
 * @param window fenetre a fermer
 * @param renderer rendu a fermer
 */
void quitSDL(bool_t status, char const* msg, SDL_Window* window, SDL_Renderer* renderer) 
{                
  char msg_formated[255];
  int l;

  if (!status) 
  {
    strncpy(msg_formated, msg, 250);                                 
    l = strlen(msg_formated);                                        
    strcpy(msg_formated + l, " : %s\n");                     
    SDL_Log(msg_formated, SDL_GetError());                   
  }                                                               

  if (renderer != NULL) SDL_DestroyRenderer(renderer);                            
  if (window != NULL)   SDL_DestroyWindow(window);                                        

  SDL_Quit();                                                     

  if (!status) 
  {
	  exit(EXIT_FAILURE);                                              
  }                                                               
}