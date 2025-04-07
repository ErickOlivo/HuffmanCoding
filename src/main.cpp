#include <iostream>
#include "frequency.h"
#include <unordered_map>
#include "HuffmanNode.h"
#include "HuffmanTree.h"
#include "HuffmanUtils.h" // Para deleteTree
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"



int main() {
    std::string texto = "abracadabra";

    std::cout << "Texto original:     " << texto << std::endl;


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
        std::cout << "\nÁrbol de Huffman construido con éxito. " << "Frecuencia total: " << root->frequency << std::endl;
    }
    else {
        std::cout << "No se pudo construir el árbol (texto vacío o error)." << std::endl;
    }

    // 4. Generar códigos
    std::unordered_map<char, std::string> codes = generateHuffmanCodes(root);

    // 5. Mostrar códigos
    std::cout << "\nCódigos Huffman generados:\n";
    for (const auto& pair : codes) {
        std::cout << "Carácter: '" << pair.first << "' => " << pair.second << '\n';
    }

    // 6. Codificar el texto usando los códigos
    std::string encodedText = encodeText(texto, codes);

    // 7. Mostrar resultado
    std::cout << "\nTexto codificado:   " << encodedText << std::endl;

    // 8. Decodificar
    std::string decodedText = decodeText(encodedText, root);
    std::cout << "\nTexto decodificado: " << decodedText << std::endl;

    // Validar que el texto original coincide con el decodificado
    if (decodedText == texto) {
        std::cout << "Decodificación exitosa: El texto decodificado coincide con el original.\n";
    }
    else {
        std::cout << "Error en la decodificación.\n";
    }

    // 9. Liberar la memoria del árbol
    deleteTree(root);

    // Liberar memoria, si usamos punteros crudos
    // (Implementar una función para borrar recursivamente el árbol)

    return 0;
}





//g++ -Iinclude src/main.cpp src/frequency.cpp src/HuffmanTree.cpp src/HuffmanUtils.cpp src/HuffmanCodes.cpp src/HuffmanEncoder.cpp src/HuffmanDecoder.cpp -o main

// g++ -Iinclude src/*.cpp -o main

