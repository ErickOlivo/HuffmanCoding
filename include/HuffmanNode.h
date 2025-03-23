#pragma once
#include <cstddef>

/**
 * @brief Estructura para representar un nodo del árbol de Huffman.
 *
 * Contiene el carácter (character), la frecuencia (frequency) y punteros
 * a los hijos izquierdo (left) y derecho (right).
 */
struct HuffmanNode {
   char character;
   int frequency;
   HuffmanNode* left;
   HuffmanNode* right;

   /**
    * @brief Contructor que inicializa el nodo con un carácter y su frecuencia.
    *
    * Para nodos internos del árbol (combinación de dos subárboles),
    * se suele usar un carácter centinela (por ejemplo, '\0').
    */
   HuffmanNode(char c, int freq) : character(c), frequency(freq), left(nullptr), right(nullptr) {}
};
