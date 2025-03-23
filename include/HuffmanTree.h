#pragma once
#include <unordered_map>
#include <queue>
#include <vector>
#include "HuffmanNode.h"

/**
 * @brief Construye el árbol de Huffman a partir de un mapa de frecuencias.
 *
 * @param freqMap Mapa de frecuencias, donde la clave es el carácter y el valor es la frecuencia.
 * @return HuffanNode* Puntero al nodo raíz del árbol de Huffman.
 */
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap);
