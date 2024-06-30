#include <stdio.h>
#include <SDL2/SDL.h>
#include "grid.h"
#include "gameOfLife.h"

/**
 * @brief Affiche une grille dans la fenêtre
 * 
 * @param window le fenêtre à utiliser
 * @param renderer le renderer à utiliser
 * @param grid la grille à afficher
 */
void drawGrid(SDL_Window * window, SDL_Renderer *renderer, grid_t grid) {
	int               i,
                      j,
                      poseX,
                      poseY;
	SDL_Rect          window_dimensions = {0},
                      rectangle;
	
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h); 

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 0);
	SDL_RenderClear(renderer);
	
	rectangle.w = window_dimensions.w / grid.x ;
	rectangle.h = window_dimensions.h / grid.y ;
    poseX = (window_dimensions.w - rectangle.w * grid.x) / 2 ;
    poseY = (window_dimensions.h - rectangle.h * grid.y) / 2 ;

	for(i = 0; i < grid.x; i++) {
		rectangle.y = poseY + rectangle.w * i;
		for(j = 0; j < grid.y; j++) {
			rectangle.x = poseX + rectangle.h * j;
			SDL_SetRenderDrawColor(renderer, !grid.grid[i][j]*255, !grid.grid[i][j]*255, !grid.grid[i][j]*255, 255);
			SDL_RenderFillRect(renderer, &rectangle);
		}
	}
	SDL_RenderPresent(renderer);
}

/**
 * @brief Récupère la taille de l'affichage courant
 * 
 * @param height la hauteur de l'éffichage
 * @param width la largeur de l'affichage
 * @return int 0 : erreur, 1 : succès
 */
int screenSize(int *h, int* w) {
	SDL_DisplayMode current;
	int code = 0;

	if(SDL_GetCurrentDisplayMode(0, &current) != 0) {
		code = 1;
	}
	else {
		*h = current.h;
		*w = current.w;
	}
	return code;
}

void startGoL(grid_t grid, rules_t* rules, int iterations, int delay, SDL_Window* window, SDL_Renderer* renderer) {
	int i;
	for(i = 0; i < iterations; ++i) {
		nextIteration(&grid, rules);
		drawGrid(window, renderer, grid);
		SDL_Delay(delay);
	}
}