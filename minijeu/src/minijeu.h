#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "matrice.h"
#include "mySDL.h"

/**
 * @brief Dessine le fond
 * 
 * @param renderer Le rendu
 * @param background Texture appliquee au fond
 * @param window_dimensions Dimensions et position de la fenetre
 */
void drawBackground(SDL_Renderer * renderer, SDL_Texture *background, SDL_Rect window_dimensions, SDL_Rect brick, int m);

/**
 * @brief Dessine l'etoile a l'ecran avec un certain angle
 * 
 * @param renderer Le rendu
 * @param texture La texture appliquee pour l'etoile
 * @param star Dimensions et position de l'etoile
 * @param angle L'angle a appliquer
 */
void drawStar(SDL_Renderer *renderer, SDL_Texture * texture, SDL_Rect star, double angle);

/**
 * @brief Calcule les dimensions de l'etoile
 * 
 * @param star Dimensions et position de l'etoile
 * @param window_dimensions Dimensions et position de la fenetre
 */
void starDimensions (SDL_Rect * star, SDL_Rect window_dimensions);

/**
 * @brief Affiche du texte a l'ecran 
 * 
 * @param text Le texte a afficher
 * @param dest Position et dimensions de destination
 * @param font Police d'ecriture
 * @param renderer Le rendu
 * @return bool_t true si on a reussi, false sinon
 */
bool_t drawText(char *text, SDL_Rect dest, TTF_Font *font, SDL_Renderer *renderer);

/**
 * @brief Permet de calculer les dimensions d'une brique par rapport a la taille de la fenetre
 * 
 * @param window la fenetre
 * @param brick la brique (SDL_Rect)
 * @param n nombre de lignes de la grille
 * @param m nombre de colonnes de la grille
 */
void brickDimensions(SDL_Rect * brick, int n, int m, SDL_Rect window_dimensions);

/**
 * @brief Affiche les briques
 * 
 * @param renderer Le rendu
 * @param bricks La grille d'entier (represente les briques)
 * @param n Nombre de lignes de la grille
 * @param m Nombre de colonnes de la grille
 * @param brick Dimensions d'une brique
 */
void drawBricks(SDL_Renderer *renderer, int ** bricks, int n, int m, SDL_Rect brick, SDL_Texture *texture);

/**
 * @brief Calcule les dimensions du paddle
 * 
 * @param paddle Le paddle
 * @param brick Dimensions d'une brique
 * @param m nombre de colonnes de la grille (de briques vu a l'horizontal)
 */
void paddleDimensions(SDL_Rect * paddle, SDL_Rect brick, int m);

/**
 * @brief Affiche le paddle
 * 
 * @param renderer Le rendu
 * @param paddleDest Dimensions du paddle
 * @param texture Texture appliquee au paddle
 */
void drawPaddle(SDL_Renderer * renderer, SDL_Rect paddleDest, SDL_Texture * texture);

/**
 * @brief Calcule les dimensions de la balle
 * 
 * @param ball La balle
 * @param brick Dimensions d'une brique 
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 */
void ballDimensions(SDL_Rect * ball, SDL_Rect brick, int m);

/**
 * @brief Affiche la balle
 * 
 * @param renderer Le rendu
 * @param ball La balle
 * @param texture La texture appliquee a la balle
 */
void drawBall(SDL_Renderer * renderer, SDL_Rect ball, SDL_Texture *texture);

/**
 * @brief Dessine les bordure de l'espace jouable
 * 
 * @param renderer Le rendu
 * @param brick Dimensions d'une brique
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 * @param window_dimensions Dimensions de la fenetre
 */
void drawLimits(SDL_Renderer *renderer, SDL_Rect brick, int m, SDL_Rect window_dimensions);

/**
 * @brief Fait bouger la balle
 * 
 * @param ball La balle
 * @param speed Vitesse de la balle
 */
void moveBall(SDL_Rect *ball, SDL_Rect speed);

/**
 * @brief "Casse" une brique
 * 
 * @param bricks La grille des briques (entiers)
 * @param n Nombre de lignes de la grille
 * @param m Nombre de colonnes de la grille
 */
void breakBrick(int *** bricks, int n, int m);

/**
 * @brief Calcul les collisions de la balle dans son environnement et modifie sa vitesse en consequence
 * 
 * @param ball La balle
 * @param brick Dimensions d'une brique
 * @param bricks Grille d'entiers qui represente les briques
 * @param n Nombre de lignes de la grille
 * @param m Nombre de colonnes de la grille
 * @param paddle Le paddle
 * @param speed Vitesse de la balle
 * @return bool_t true : une brique a ete cassee, false sinon
 */
bool_t ballCollision(SDL_Rect ball, SDL_Rect brick, int *** bricks, int n, int m, SDL_Rect paddle, SDL_Rect * speed);

/**
 * @brief Fait bouger le paddle
 * 
 * @param paddle Le paddle
 * @param brick Dimensions d'une brique
 * @param m Nombre de colonnes de la grille (de briques vu a l'horizontal)
 * @param step Pas pour le mouvement
 */
void movePaddle(SDL_Rect* paddle, SDL_Rect brick, int m, int step);

/**
 * @brief Met a jour le score de la partie
 * 
 * @param score Le score (entier)
 * @param remainingBricks Le nombre de briques restantes
 * @param ball La balle
 * @param winHeight La hauteur de la fenetre
 * @param brokenBrick Indique si une brique a ete cassee
 * @return bool_t true : la partie est finie, false elle continue
 */
bool_t updateScore(int * score, int * remainingBricks, SDL_Rect ball, int winHeight, bool_t brokenBrick);

/**
 * @brief Boucle de jeu du casse-briques
 * 
 * @param window La fenetre du jeu
 * @param renderer Le rendu de la fenetre
 * @param bricks Grille d'entiers qui represente les briques
 * @param n Nombre de ligne de la grille
 * @param m Nombre de colonnes de la grille
 * @param nbBricks Nombre de briques total
 * @param font Police d'ecriture
 * @param texture Texture pour les images
 * @param background Texture du fond
 */
void gameLoop(SDL_Window * window, SDL_Renderer * renderer, int ** bricks, int n, int m, int nbBricks, TTF_Font *font, SDL_Texture *texture, SDL_Texture *background);
