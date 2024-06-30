#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"

#define M_INFINI -1

/**
 * @brief Type tas binaire
 * 
 */
typedef struct binary_heap
{
    int length;
    int heapSize;
    int *array;
} binary_heap_t;

/**
 * @brief Retourne l'indice du parent de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getParent(int index);

/**
 * @brief Retourne l'indice du fils de gauche de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getLeftChild(int index);

/**
 * @brief Retourne l'indice du fils de droite de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getRightChild(int index);

/**
 * @brief Affiche le tableau du tas binaire dans le terminal 
 * 
 * @param heap Le tas binaire
 */
void printHeap(binary_heap_t heap);

/**
 * @brief Retourne la valeur minimum du tas
 * 
 * @param heap Le tas
 * @return int La valeur minimum
 */
int heap_minimum(binary_heap_t heap);

/**
 * @brief Extrait le plus petit element du tas
 * 
 * @param heap Le tas
 * @return int La valeur de l'element si tas non vide, M_INFINI sinon
 */
int heapExtractMin(binary_heap_t *heap);

/**
 * @brief Ajoute un element de valeur key dans le tas et le fait remonter a la bonne place
 * 
 * @param heap Le tas
 * @param i Indice du nouvel element
 * @param key La valeur de l'element
 */
void heapDecreaseKey(binary_heap_t *heap, int i, int key);

/**
 * @brief Insere un element dans le tas 
 * 
 * @param heap Le tas
 * @param key La valeur de l'element
 */
void minHeapInsert(binary_heap_t *heap, int key);

/**
 * @brief Permute 2 valeurs d'indices i et j dans la tableau array
 * 
 * @param array Tableau de valeurs
 * @param i Indice du premier element
 * @param j Indice du deuxieme element
 */
void permute(int array[], int i, int j);

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t *heap, int val);

/**
 * @brief Construit un tas binaire minimum a partir d'un tas binaire quelconque
 * 
 * @param heap Tas binaire quelconque
 */
void buildMinHeap(binary_heap_t *heap);

/**
 * @brief Cherche si une valeur est présente dans le tas
 * 
 * @param heap le tas binaire
 * @param key la valeur cherchée
 * @param pos la position de l'élément trouvé (-1 si non trouvé)
 * @return bool_t 
 */
bool_t isInHeap(binary_heap_t heap, int key, int *pos);

/**
 * @brief Tri par tas du tableau
 * 
 * @param heap Le tas binaire à trier
 */
void heapSort(binary_heap_t *heap);