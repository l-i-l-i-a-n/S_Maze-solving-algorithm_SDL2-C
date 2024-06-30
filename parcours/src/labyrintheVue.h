#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "mySDL.h"
#include "grapheListeAretes.h"
#include "parcours.h"
#include "liste_chainee.h"

typedef enum
{
    NORD = 1,
    SUD = 2,
    EST = 4,
    OUEST = 8
} directions;

/**
 * @brief Calcule les dimensions et position du rectangle delimitant le labyrinthe
 * 
 * @param positionLab Le rectangle pour le labyrinthe
 * @param tile Dimensions et position d'une case
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 */
void dimensionsLab(SDL_Rect *positionLab, SDL_Rect tile, int n, int m);

/**
 * @brief Calcule les dimensions et position du rectangle definissant une case
 * 
 * @param tile Le rectangle pour une case
 * @param positionLab Le rectangle delimitant le labyrinthe
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 */
void dimensionTile(SDL_Rect *tile, SDL_Rect positionLab, int n, int m);

/**
 * @brief Calcule les dimensions du rectangle pour le personnage
 * 
 * @param dest Le Rectangle pour le personnage
 * @param tile Le rectangle pour une case
 */
void dimensionPerso(SDL_Rect *perso, SDL_Rect tile);

/**
 * @brief Dessine le personnage sur le rendu
 * 
 * @param renderer Le rendu
 * @param perso La texture pour le personnage
 * @param dest Le rectangle pour le personnage
 * @param ancienX Ancienne position x du personnage
 * @param ancienY Ancienne position y du personnage
 */
void drawperso(SDL_Renderer *renderer, SDL_Texture *perso, SDL_Rect dest, int ancienX, int ancienY);

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
 * @param marques Liste permettant de dessiner des tas de cailloux sur une case si non nulle
 */
void drawLab(SDL_Renderer *renderer, int **grid, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t *marques);

/**
 * @brief Dessine des cailloux a un endroit donne
 * 
 * @param renderer Le rendu
 * @param indiceNoeud L'indice du noeud, pour trouver l'emplacement
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle representant une case
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture pour les cailloux
 * @param debut Savoir si c'est le debut d'un parcours pour l'afficher avec un couleur differente
 */
void drawStone(SDL_Renderer *renderer, int indiceNoeud, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, bool_t debut);

/**
 * @brief Permet de dessiner le fond, le labyrinthe et le perso si non nul
 * 
 * @param marques Liste de booleen pour placer des cailloux
 * @param renderer Le rendu
 * @param n Nombre de lignes de la matrice du labyrinthe
 * @param m Nombre de colonnes de la matrice du labyrinthe
 * @param tile Rectangle pour une case
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param texture La texture a appliquer aux murs et aux sols
 * @param grille La matrice reresentant le labyrinthe
 * @param destPerso Le rectangle pour le personnage
 * @param perso La texture a appliquer au personnage
 */
void drawAll(bool_t *marques, SDL_Renderer *renderer, int n, int m, SDL_Rect tile, SDL_Rect positionLab, SDL_Texture *texture, int **grille, SDL_Rect destPerso, SDL_Texture *perso, int ancienX, int ancienY);

/**
 * @brief Permet d'afficher du texte a l'ecran
 * 
 * @param text Texte souhaite
 * @param dest La rectangle representant l'emplacement du texte
 * @param font La police d'ecriture a appliquer
 * @param renderer Le rendu
 * @return bool_t True si ca a fonctionne, false sinon
 */
bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer);

/**
 * @brief Calcule les dimensions pour les rectangles representant les boutons
 * 
 * @param dijkstra Rectangle pour le bouton dijkstra
 * @param a_etoile Rectangle pour le bouton A*
 * @param profondeur Rectangle pour le bouton profondeur
 * @param quit Rectangle pour le bouton quitter
 * @param positionLab Rectangle delimitant le labyrinthe
 */
void dimensionButtons(SDL_Rect *dijkstra, SDL_Rect *a_etoile, SDL_Rect *profondeur, SDL_Rect *quit, SDL_Rect positionLab);

/**
 * @brief Permet d'afficher le menu a l'ecran
 * 
 * @param renderer Le rendu
 * @param font La police d'ecriture a appliquer
 * @param positionLab Rectangle delimitant le labyrinthe
 * @param dijkstra Rectangle pour le bouton dijkstra
 * @param a_etoile Rectangle pour le bouton A*
 * @param profondeur Rectangle pour le bouton profondeur
 * @param quit Rectangle pour le bouton quitter
 */
void drawMenu(SDL_Renderer *renderer, TTF_Font *font, SDL_Rect positionLab, SDL_Rect dijkstra, SDL_Rect a_etoile, SDL_Rect profondeur, SDL_Rect quit);

/**
 * @brief Dessine le fond
 * 
 * @param renderer Le rendu
 * @param background Texture appliquee au fond
 * @param window_dimensions Dimensions et position de la fenetre
 */
void drawBackground(SDL_Renderer * renderer, SDL_Texture *background, SDL_Rect window_dimensions);

/**
 * @brief Boucle de "jeu" de l'executable
 * 
 * @param window La fenetre
 * @param renderer Le rendu de la fenetre
 * @param font La police d'ecriture a appliquer au texte 
 * @param texture La texture pour les murs et les sols 
 * @param perso La texture pour le personnage
 * @param background Le fond du menu
 * @param graph Le graphe representant le labyrinthe
 * @param n Nombre de lignes de la matrice 
 * @param m Nombre de colonnes de la matrice 
 * @param grille La matrice representant le labyrinthe
 */
void menuLoop(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font, SDL_Texture *texture, SDL_Texture *perso, SDL_Texture* background, couples_graphe_t graph, int n, int m, int **grille);
