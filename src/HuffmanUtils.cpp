#include "HuffmanUtils.h"
#include <iostream>
#include <iomanip>  // Para std::setprecision
#include <string>

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


/**
 * @brief Muestra estadísticas de compresión de texto usando Huffman.
 *
 * Calcula el número de bits en el texto original (asumiendo ASCII, 8 bits por carácter),
 * el número de bits codificados (tamaño de la cadena binaria),
 * y el porcentaje de ahorro de espacio tras la compresión.
 *
 * @param original Texto original sin comprimir.
 * @param encoded Texto codificado como cadena de bits ('0' y '1').
 */
void reportCompressionStats(const std::string& original, const std::string& encoded) {
    std::size_t originalBits = original.size() * 8;
    std::size_t encodedBits = encoded.size();
    double ahorro = (1.0 - static_cast<double>(encodedBits) / originalBits) * 100.0;

    std::cout << "\nBits originales : " << originalBits << " bits";
    std::cout << "\nBits codificados: " << encodedBits  << " bits";
    std::cout << "\nAhorro          : " << std::fixed << std::setprecision(2) << ahorro << "%\n";
}
