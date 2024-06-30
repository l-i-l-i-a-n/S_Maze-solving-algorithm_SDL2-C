#pragma once

#include <stdio.h>
#include "compoConnexes.h"
#include "grapheListeAretes.h"
#include "graphviz.h"
#include "kruskal.h"

/**
 * @brief Teste la fontion noeudsCompoConnexe
 * 
 * @return bool_t 
 */
bool_t testNoeudsCompoConnexes();

/**
 * @brief Teste la fonction createAdejencyMatrix
 * 
 * @return bool_t 
 */
bool_t testCreateAdjencyMatrix();

/**
 * @brief Teste la fonction grapheToPartition
 * 
 * @return bool_t 
 */
bool_t testGrapheToPartition();
