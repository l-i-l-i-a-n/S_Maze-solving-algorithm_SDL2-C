#pragma once

#include <stdio.h>
#include "partition.h"

/**
 * @brief Type booleen
 * 
 */
typedef enum
{
    false,
    true
} bool;

/**
 * @brief Teste la fonction creer (pour une partition)
 * 
 * @return true 
 * @return false 
 */
bool testCreer();

/**
 * @brief Teste la fonction recupererClasse
 * 
 * @return true 
 * @return false 
 */
bool testRecupererClasse();

/**
 * @brief Teste la fonction classeMere
 * 
 * @return true 
 * @return false 
 */
bool testClasseMere();

/**
 * @brief Teste la fonction fusion
 * 
 * @return true 
 * @return false 
 */
bool testFusion();

/**
 * @brief Teste la fonction listerClasse
 * 
 * @return true 
 * @return false 
 */
bool testListerClasse();

/**
 * @brief Teste la fonction listerPartition
 * 
 * @return true 
 * @return false 
 */
bool testListerPartition();
