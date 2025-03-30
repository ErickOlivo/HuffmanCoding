#include "HuffmanCodes.h"

/**
 * @brief Función recursiva auxiliar para recorrer el árbol y construir los códigos.
 *
 * @param node Puntero al nodo actual.
 * @param currentCode Código binario acumulado hasta este nodo.
 * @param codes Mapa donde se almacenan los pares (carácter -> código binario).
 */

static void buildCodes(HuffmanNode* node, const std::string& currentCode, std::unordered_map<char, std::string>& codes) {
    if (!node) {
        return;
    }

    // Si el nodo hoja (sin hijos), almacenamos el código en el mapa
    if (!node->left && !node->right) {
        // Asignar el código al carácter
        codes[node->character] = currentCode;
        return;
    }

    // Recorrer la rama izquierda, añadiendo '0'
    buildCodes(node->left, currentCode + "0", codes);

    // Recorrer la rama derecha, añadiendo '1'
    buildCodes(node->right, currentCode + "1", codes);
}

std::unordered_map<char, std::string> generateHuffmanCodes(HuffmanNode* root) {
    std::unordered_map<char, std::string> codes;

    // Llamada a la función recursiva para construir los códigos
    buildCodes(root, "", codes);

    return codes;
}
