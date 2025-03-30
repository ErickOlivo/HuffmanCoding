#pragma once
#include <unordered_map>
#include <string>
#include "HuffmanNode.h"

/**
 * @brief Genera los códigos binarios para cada carácter del árbol de Huffman.
 *
 * @param root Puntero a la raíz del árbol de Huffman.
 * @return std::unordered_map<char, std::string> Mapa de (carácter -> código binario).
 */


 std::unordered_map<char, std::string> generateHuffmanCodes(HuffmanNode* root);
