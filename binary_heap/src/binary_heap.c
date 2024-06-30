#include "binary_heap.h"

/**
 * @brief Retourne l'indice du parent de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getParent(int index)
{
    return index / 2;
}

/**
 * @brief Retourne l'indice du fils de gauche de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getLeftChild(int index)
{
    return 2 * index;
}

/**
 * @brief Retourne l'indice du fils de droite de l'indice index
 * 
 * @param index 
 * @return int 
 */
int getRightChild(int index)
{
    return 2 * index + 1;
}

/**
 * @brief Affiche le tableau du tas binaire dans le terminal 
 * 
 * @param heap Le tas binaire
 */
void printHeap(binary_heap_t heap)
{
    int i;
    printf("heap size = %d\n", heap.length);
    for (i = 1; i <= heap.length; i++)
    {
        printf("%d ", heap.array[i]);
    }
    printf("\n");
}

/**
 * @brief Retourne la valeur minimum du tas
 * 
 * @param heap Le tas
 * @return int La valeur minimum
 */
int heap_minimum(binary_heap_t heap)
{
    return heap.array[1];
}

/**
 * @brief Extrait le plus petit element du tas
 * 
 * @param heap Le tas
 * @return int La valeur de l'element si tas non vide, M_INFINI sinon
 */
int heapExtractMin(binary_heap_t *heap)
{
    int min;

    if (heap->heapSize < 1)
    {
        fprintf(stderr, "heap underflow");
        min = M_INFINI;
    }
    else
    {
        min = heap->array[1];
        heap->array[1] = heap->array[heap->heapSize];
        heap->heapSize = heap->heapSize - 1;
        minHeapify(heap, 1);
    }
    return min;
}

/**
 * @brief Ajoute un element de valeur key dans le tas et le fait remonter a la bonne place
 * 
 * @param heap Le tas
 * @param i Indice du nouvel element
 * @param key La valeur de l'element
 */
void heapDecreaseKey(binary_heap_t *heap, int i, int key)
{
    if (key > heap->array[i])
    {
        fprintf(stderr, "new key is greater than current key");
    }
    else
    {
        heap->array[i] = key;
        while (i > 1 && heap->array[getParent(i)] > heap->array[i])
        {
            permute(heap->array, i, getParent(i));
            i = getParent(i);
        }
    }
}

/**
 * @brief Insere un element dans le tas 
 * 
 * @param heap Le tas
 * @param key La valeur de l'element
 */
void minHeapInsert(binary_heap_t *heap, int key)
{
    heap->heapSize = heap->heapSize + 1;
    heap->array[heap->heapSize] = M_INFINI;
    heapDecreaseKey(heap, heap->heapSize, key);
}

/**
 * @brief Permet de deplacer une valeur a la bonne place dans le tas
 * 
 * @param heap Le tas binaire
 * @param val Indice de la valeur a deplacer
 */
void minHeapify(binary_heap_t *heap, int val)
{
    int left,
        right,
        min;

    left = getLeftChild(val);
    right = getRightChild(val);

    if (left <= heap->heapSize && heap->array[left] < heap->array[val])
    {
        min = left;
    }
    else
    {
        min = val;
    }
    if (right <= heap->heapSize && heap->array[right] < heap->array[min])
    {
        min = right;
    }
    if (min != val)
    {
        permute(heap->array, val, min);
        minHeapify(heap, min);
    }
}

/**
 * @brief Construit un tas binaire minimum a partir d'un tas binaire quelconque
 * 
 * @param heap Tas binaire quelconque
 */
void buildMinHeap(binary_heap_t *heap)
{
    int i;

    heap->heapSize = heap->length;
    for (i = (heap->length / 2); i > 0; i--)
    {
        minHeapify(heap, i);
    }
}

/**
 * @brief Permute 2 valeurs d'indices i et j dans la tableau array
 * 
 * @param array Tableau de valeurs
 * @param i Indice du premier element
 * @param j Indice du deuxieme element
 */
void permute(int array[], int i, int j)
{
    int tmp = array[i];
    array[i] = array[j];
    array[j] = tmp;
}

/**
 * @brief Cherche si une valeur est présente dans le tas
 * 
 * @param heap le tas binaire
 * @param key la valeur cherchée
 * @param pos la position de l'élément trouvé (-1 si non trouvé)
 * @return bool_t 
 */
bool_t isInHeap(binary_heap_t heap, int key, int *pos)
{
    int curr = 1;
    bool_t trouve = false;
    *pos = -1;
    while (curr < heap.heapSize && heap.array[curr] != key)
    {
        curr++;
    }
    if (heap.array[curr] == key)
    {
        trouve = true;
        *pos = curr;
    }
    return trouve;
}

/**
 * @brief Tri par tas du tableau
 * 
 * @param heap Le tas binaire à trier
 */
void heapSort(binary_heap_t *heap)
{
    buildMinHeap(heap);
    for (int i = heap->length; i > 1; i--)
    {
        permute(heap->array, 1, i);
        (heap->heapSize)--;
        minHeapify(heap, 1);
    }
}
