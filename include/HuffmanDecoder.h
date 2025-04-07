#pragma once
#include <string>
#include "HuffmanNode.h"

/**
 * @brief Decodifica un texto binario (string de '0' y '1') usando el árbol de Huffman.
 *
 * @param encoded Texto codificado que consiste en una secuencia de bits ('0' y '1')
 * @param root Nodo raíz del árbol de Huffman.
 * @return std::string Texto original decodificado.
 */
std::string decodeText(const std::string& encoded, HuffmanNode* root);
