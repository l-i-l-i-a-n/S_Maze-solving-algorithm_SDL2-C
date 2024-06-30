#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "binary_heap.h"

/**
 * @brief Fonction pour comparer 2 nombres utile pour quicksort
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmpfunc(const void *a, const void *b);

/**
 * @brief Compare les temps d'execution des 2 methodes de tri (quicksort et heapsort)
 * 
 * @param size Taille des tableaux pour les tris
 */
void comparison(int size);