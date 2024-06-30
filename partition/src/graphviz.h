#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>
#include "partition.h"

/**
 * @brief Creer le fichier .dot et le fichier png pour la partition en parametres
 * 
 * @param partition La partition a representer
 * @param n Le nombre d'elements dans la partition
 * @param name Nom pour les fichiers generes
 */
void drawPartitionGraph(partition_t partition, int n, char *name);
