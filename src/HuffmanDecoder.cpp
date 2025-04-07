#include "HuffmanDecoder.h"

std::string decodeText(const std::string& encoded, HuffmanNode* root) {
    std::string decoded;
    if (!root) {
        return decoded; // Si el árbol está vacío, retornamos cadena vacía
    }

    HuffmanNode* current = root;
    for (char bit : encoded) {
        // Desplazarnos en el árbol según el bit
        if (bit == '0') {
            current = current->left;
        } else { // bit == '1'
            current = current->right;
        }

        // Si llegamos a un nodo hoja, agregamos el carácter al resultado
        if (current->left == nullptr && current->right == nullptr) {
            decoded.push_back(current->character);
            // Volvemos a la raíz para decodificar el siguiente símbolo
            current = root;
        }
    }

    return decoded;
}
