#include <stdio.h>
#include <time.h>
#include "gameOfLife_view.h"
#include "gameOfLife.h"
#include "mySDL.h"

/**
 * @brief Programme principal - Affiche une execution du jeu de la vie
 * 
 * @param argc 
 * @param argv 
 * @return int
 */
int main(int argc, char const *argv[]) {
    grid_t grid;
	int x = 20, y = 20, iterations = 30, sheight, swidth, delay = 100;
	rules_t *rules;
	SDL_Window *window;
	SDL_Renderer *renderer;
	bool_t status;

	(void)argc;
	(void)argv;

	rules = malloc(sizeof(rules_t));
	if(rules == NULL) {
        printf("Error : memory allocation failed");
		return 1;
	}
	initLife(rules);	
	
	srand(time(0));
	
	status = initializeSDL();
	if (!status) {
		quitSDL(false, "Error : SDL initialization", NULL, NULL);
		exit(EXIT_FAILURE);
	}
	
    
    if(screenSize(&sheight, &swidth) != 0) {
		free(rules);
		quitSDL(false, "Error : SDL display mode", NULL, NULL);
		exit(EXIT_FAILURE);
    }
	
	// Création de la fenetre
    window = SDL_CreateWindow("Jeu de la vie", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, swidth/2, swidth/2, SDL_WINDOW_SHOWN);
    if (window == NULL) {
		free(rules);
		quitSDL(false, "Error : SDL window creation", window, NULL);
		exit(EXIT_FAILURE);
    }
    
    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        free(rules);
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
		exit(EXIT_FAILURE);
    }
	
	grid = createGrid(x, y);
	if(grid.grid == NULL) {
		free(rules);
		quitSDL(false, "Error : Grid creation", window, renderer);
		exit(EXIT_FAILURE);
	}
	
	initializeRandomGrid(grid);
	drawGrid(window, renderer, grid);

	startGoL(grid, rules, iterations, delay, window, renderer);

	SDL_Delay(delay);
	initMaze(rules);
	startGoL(grid, rules, iterations, delay, window, renderer);

	waitForQuitSDL();
	
	free(rules);
	freeGrid(grid);
	quitSDL(true, "SDL END", window, renderer);

	return 0;
}
