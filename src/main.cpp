#include <iostream>
#include "frequency.h"
#include <unordered_map>
#include "HuffmanNode.h"
#include "HuffmanTree.h"
#include "HuffmanUtils.h" // Para deleteTree



int main() {
    std::string texto = "abracadabra";

    // 1. Llamada a la función de cálculo de frecuecias
    std::unordered_map<char, int> freqMap = computeFrequencies(texto);

    // Muestra las frecuencias en pantalla
    for (auto& pair : freqMap) {
        std::cout << "Caracter: '" << pair.first << "' - Frecuencia: " << pair.second << std::endl;
    }

    // 2. Construir el árbol de Huffman
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // 3. Imprimir un mensaje de confirmación
    if (root != nullptr) {
        std::cout << "Árbol de Huffman constuisto con éxito. " << "Frecuencia total: " << root->frequency << std::endl;
    }
    else {
        std::cout << "No se pudo construir el árbol (texto vacío o error)." << std::endl;
    }

    // 4. Liberar la memoria del árbol
    deleteTree(root);

    return 0;
}

/*
Desde src/
g++ -I../include main.cpp frequency.cpp -o main


Desde la raíz del proyecto
g++ -Iinclude src/main.cpp src/frequency.cpp -o main

g++ -Iinclude src/main.cpp src/frequency.cpp src/HuffmanTree.cpp src/HuffmanUtils.cpp -o main
*/
