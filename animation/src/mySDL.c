#include <stdio.h>
#include "bool.h"
#include "SDL2/SDL.h"

/**
 * @brief Initialise la SDL et indique si l'initialisation s'ets bien passée
 * 
 * @return bool_t false : échec, true : succès
 */
bool_t initializeSDL(void) {
    bool_t status = true;
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    	fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); 
    	status = false; 
	}
	return status;
}

/**
 * @brief Permet de fermer toute la SDL et d'indiquer un message d'erreur si il y en a une
 * 
 * @param status false : erreur, true : normal
 * @param msg message de fin
 * @param window fenêtre à fermer
 * @param renderer rendu à fermer
 */
void quitSDL(bool_t status,                              // fin normale : ok = 0 ; anormale ok = 1
             char const* msg,                            // message à afficher
             SDL_Window* window,                         // fenêtre à fermer
             SDL_Renderer* renderer) {                   // renderer à fermer                           
  char msg_formated[255];
  int l;

  if (!status) {
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
 * @brief Attend la fermeture manuelle de la fenêtre par l'utilisateur
 */
void waitForQuitSDL(void) {
  SDL_Event event;
  SDL_bool exit = SDL_FALSE;
  // Attente de la fermeture de la fenêtre
  while(!exit) {
    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT) exit = SDL_TRUE;    
  }
}