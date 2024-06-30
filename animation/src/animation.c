#include <stdio.h>
#include "mySDL.h"
#include <SDL2/SDL_image.h>

/**
 * @brief Charge une texture depuis une image
 * 
 * @param file_image_name l'image source
 * @param window la fenêtre courante
 * @param renderer le renderer à utiliser pour dessiner la texture
 * @param status code de retour de la fonction - false : erreur, true : succès
 * @return SDL_Texture* la texture chargée
 */
SDL_Texture *loadTexture(char *file_image_name, SDL_Window *window, SDL_Renderer *renderer, bool_t *status)
{
	SDL_Surface *my_image = NULL;
	SDL_Texture *my_texture = NULL;
	*status = true;

	my_image = IMG_Load(file_image_name);
	if (my_image == NULL)
	{
		quitSDL(0, "Chargement de l'image impossible", window, renderer);
		*status = false;
	}
	if (*status)
	{
		my_texture = SDL_CreateTextureFromSurface(renderer, my_image);
		SDL_FreeSurface(my_image);
		if (my_texture == NULL)
		{
			quitSDL(0, "Echec de la transformation de la surface en texture", window, renderer);
			*status = false;
		}
	}

	return my_texture;
}

/**
 * @brief Affiche les textures du sol
 * 
 * @param window la fenêtre courante
 * @param renderer le renderer à utliser pour dessiner les textures
 * @param ground la texture représentant une tuile de sol
 */
void showTiles(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *ground)
{
	SDL_Rect source = {0},
			 window_dimensions = {0},
			 destination = {0};
	float zoom = 1;
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
	SDL_QueryTexture(ground, NULL, NULL, &source.w, &source.h);

	// Placement des tiles de sol
	for (int i = 0; i < 10; i++)
	{
		destination.w = source.w * zoom;
		destination.h = source.h * zoom;
		destination.x = (window_dimensions.w - destination.w) - i * source.w;
		destination.y = (window_dimensions.h - destination.h);
		SDL_RenderCopy(renderer, ground, &source, &destination);
	}
	for (int i = 0; i < 4; i++)
	{
		destination.w = source.w * zoom;
		destination.h = source.h * zoom;
		destination.x = (window_dimensions.w - destination.w) - i * source.w;
		destination.y = (window_dimensions.h - destination.h) - source.h;
		SDL_RenderCopy(renderer, ground, &source, &destination);

		destination.w = source.w * zoom;
		destination.h = source.h * zoom;
		destination.x = (window_dimensions.w - destination.w) - i * source.w;
		destination.y = (window_dimensions.h - destination.h) - 2 * source.h;
		SDL_RenderCopy(renderer, ground, &source, &destination);
	}
	destination.w = source.w * zoom;
	destination.h = source.h * zoom;
	destination.x = (window_dimensions.w - destination.w) - 4 * source.w;
	destination.y = (window_dimensions.h - destination.h) - 1 * source.h;
	SDL_RenderCopy(renderer, ground, &source, &destination);
}

/**
 * @brief Affiche les textures du ciel
 * 
 * @param window la fenêtre courante
 * @param renderer le renderer à utliser pour dessiner les textures
 * @param sky1 la texture représentant une tuile de ciel avec des montagnes
 * @param sky2 la texture représentant une tuile de ciel
 */
void showSky(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *sky1, SDL_Texture *sky2)
{
	SDL_Rect sky1_source = {0},
			 sky2_source = {0},
			 window_dimensions = {0},
			 destination = {0};
	float zoom = 1;
	SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
	SDL_QueryTexture(sky1, NULL, NULL, &sky1_source.w, &sky1_source.h);
	SDL_QueryTexture(sky2, NULL, NULL, &sky2_source.w, &sky2_source.h);

	// Placement des tiles de ciel
	for (int i = 0; i < 3; i++)
	{
		destination.w = sky2_source.w * zoom;
		destination.h = sky2_source.h * zoom;
		destination.x = i * sky2_source.w;
		destination.y = (window_dimensions.h - destination.h) - 0.46 * sky2_source.h;

		SDL_RenderCopy(renderer, sky2, &sky2_source, &destination);
	}
	// Placement des tiles de ciel avec montagnes
	for (int i = 0; i < 2; i++)
	{
		destination.w = sky1_source.w * zoom;
		destination.h = sky1_source.h * zoom;
		destination.x = i * sky1_source.w;
		destination.y = (window_dimensions.h - destination.h) - 0.2 * sky1_source.h;

		SDL_RenderCopy(renderer, sky1, &sky1_source, &destination);
	}
}

/**
 * @brief Exécute l'animation
 * 
 * @param window la fenêtre
 * @param renderer le renderer
 * @param character la texture représentant le personnage à animer
 * @param ground la texture représentant une tuile de sol
 * @param sky1 la texture représentant une tuile de ciel avec des montagnes
 * @param sky2 la texture représentant une tuile de ciel
 */
void animation(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *character, SDL_Texture *ground, SDL_Texture *sky1, SDL_Texture *sky2, bool_t *status)
{
	SDL_Rect character_source = {0},
			 ground_source = {0},
			 window_dimensions = {0},
			 destination = {0},
			 state = {0};
	int offset_y,
		offset_x,
		x,
		speed = 15,
		nb_images = 9;
	float zoom = 2;

	*status = true;
	character = loadTexture("../images/player_tilesheet.png", window, renderer, status);
	if (*status)
		ground = loadTexture("../images/dirt_grass.png", window, renderer, status);
	if (*status)
		sky1 = loadTexture("../images/skybox_sideHills.png", window, renderer, status);
	if (*status)
		sky2 = loadTexture("../images/skybox_top.png", window, renderer, status);

	if (*status)
	{
		SDL_GetWindowSize(window, &window_dimensions.w, &window_dimensions.h);
		SDL_QueryTexture(character, NULL, NULL, &character_source.w, &character_source.h);
		SDL_QueryTexture(ground, NULL, NULL, &ground_source.w, &ground_source.h);

		// Dimensions de la vignette
		offset_x = character_source.w / nb_images,
		offset_y = character_source.h / 3;
		// Dimensions de la vignette
		state.w = offset_x;
		state.h = offset_y;
		// Dimensions du sprite du personnage a l'ecran
		destination.w = offset_x * zoom;
		destination.h = offset_y * zoom;
		// Position au début
		destination.y = window_dimensions.h - offset_y * zoom - ground_source.h;

		for (x = 0; x < window_dimensions.w - destination.w; x += speed)
		{
			destination.x = x;
			if (x > (window_dimensions.w - destination.w) / 2 && x < (window_dimensions.w - destination.w) / 2 + speed)
			{
				destination.y -= ground_source.h;
			}
			if (x > (window_dimensions.w - destination.w) / 2 + 9 * speed && x < (window_dimensions.w - destination.w) / 2 + 10 * speed)
			{
				destination.y -= ground_source.h;
			}
			state.x += offset_x;		   // Vignette suivante
			state.x %= character_source.w; // Revient à la première vignette
			SDL_Delay(100);

			SDL_RenderClear(renderer);
			showSky(window, renderer, sky1, sky2);
			showTiles(window, renderer, ground);
			SDL_RenderCopy(renderer, character, &state, &destination);
			SDL_RenderPresent(renderer);
		}
		SDL_RenderClear(renderer);
	}
}

/**
 * @brief Programme principal : initialise la SDL, les fenêtres, renderer
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *ground = NULL;
	SDL_Texture *character = NULL;
	SDL_Texture *sky1 = NULL;
	SDL_Texture *sky2 = NULL;

	bool_t status;

	(void)argc;
	(void)argv;

	status = initializeSDL();
	if (!status)
		quitSDL(false, "Error : SDL initialization", NULL, NULL);

	window = SDL_CreateWindow("Animation simple", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		quitSDL(false, "Error : SDL window creation", window, renderer);
		exit(EXIT_FAILURE);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		quitSDL(false, "Error : SDL renderer creation", window, renderer);
		exit(EXIT_FAILURE);
	}

	animation(window, renderer, ground, character, sky1, sky2, &status);
	if (!status) {
		quitSDL(status, "Error : texture loading failed", window, renderer);
		exit(EXIT_FAILURE);
	}

	SDL_DestroyTexture(ground);
	SDL_DestroyTexture(character);
	SDL_DestroyTexture(sky1);
	SDL_DestroyTexture(sky2);
	IMG_Quit();

	quitSDL(true, "SDL END", window, renderer);

	return 0;
}
