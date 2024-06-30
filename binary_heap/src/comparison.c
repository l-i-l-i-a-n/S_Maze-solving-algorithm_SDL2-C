#include "comparison.h"

/**
 * @brief Fonction pour comparer 2 nombres utile pour quicksort
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

/**
 * @brief Compare les temps d'execution des 2 methodes de tri (quicksort et heapsort)
 * 
 * @param size Taille des tableaux pour les tris
 */
void comparison(int size)
{
    int i,
        arrayQSort[size];
    binary_heap_t heap;
    clock_t begin,
        end;

    heap.length = size;
    heap.heapSize = heap.length;
    heap.array = (int *)malloc(sizeof(int) * (heap.length + 1));

    if (heap.array)
    {
        srand(time(NULL));
        for (i = 1; i <= size; i++)
        {
            heap.array[i] = rand() % size;
            arrayQSort[i - 1] = heap.array[i];
        }

        begin = clock();
        heapSort(&heap);
        end = clock();
        printf("HEAP SORT TIME : %ld ms\n", (end - begin) * 1000 / CLOCKS_PER_SEC);

        begin = clock();
        qsort(arrayQSort, size, sizeof(int), cmpfunc);
        end = clock();
        printf("QUICK SORT TIME : %ld ms\n", (end - begin) * 1000 / CLOCKS_PER_SEC);

        free(heap.array);
    }
    else
    {
        printf("Error: memory allocation\n");
    }
}
