#pragma once
#include "HuffmanNode.h"

/**
 * @brief Libera la memoria de un árbol de Huffman.
 *
 * @param node Puntero al nodo de raíz del árbol.
 */
void deleteTree(HuffmanNode* node);

/**
 * @brief Muestra estadísticas de compresión entre el texto original y codificado.
 *
 * @param original Texto original sin comprimir.
 * @param encoded Texto codificado (en forma de string de bits).
 */
void reportCompressionStats(const std::string& original, const std::string& encoded);
