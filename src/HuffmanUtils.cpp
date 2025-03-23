#include "HuffmanUtils.h"

/**
 * @brief Libera la memoria de un árbol de Huffman
 *
 * @param node Puntero al nodo raíz del árbol.
 */
void deleteTree(HuffmanNode* node) {
    if (!node) return;              // Si el nodo es nullptr, no hace nada
    deleteTree(node->left);         // Liberar el subárbol izquierdo
    deleteTree(node->right);        // Liberal el subárbol derecho
    delete node;                    // Liberar el nodo actual
}
