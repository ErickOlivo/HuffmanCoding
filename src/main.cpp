#include <iostream>
#include <string>
#include <unordered_map>

#include "frequency.h"
#include "HuffmanNode.h"
#include "HuffmanTree.h"
#include "HuffmanUtils.h" // Para deleteTree
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"



int main(int argc, char* argv[]) {
    // 0. Texto de entrada: por argumento o demo
    std::string texto = "abracadabra";
    std::string salidaBits = "output.bits";

    if (argc > 1) {                      // se pasó un archivo
        texto = readFileToString(argv[1]);
        if (argc > 2) salidaBits = argv[2];   // nombre de salida opcional
    }

    std::cout << "Texto original:     " << texto << std::endl;

    // 1. Cálculo de frecuencias
    std::unordered_map<char, int> freqMap = computeFrequencies(texto);

    // 1.1 Histograma ASCII a color
    printFrequencyHistogram(freqMap);

    // 2. Construir el árbol de Huffman
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // 2.1 Mostrar árbol “pretty” en la terminal
    std::cout << "\nÁrbol de Huffman (pretty):\n";
    printHuffmanTreePretty(root);

    // 3. Imprimir un mensaje de confirmación
    if (root != nullptr) {
        std::cout << "\nÁrbol de Huffman construido con éxito. "
                  << "Frecuencia total: " << root->frequency << std::endl;
    } else {
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

    // 6.1 Guardar bitstream lógico
    writeBitStringToFile(salidaBits, encodedText);

    // 7. Mostrar resultado
    std::cout << "\nTexto codificado:   " << encodedText << std::endl;

    // 7.1 Estadísticas de compresión
    reportCompressionStats(texto, encodedText);

    // 8. Decodificar
    std::string decodedText = decodeText(encodedText, root);
    std::cout << "\nTexto decodificado: " << decodedText << std::endl;

    // Validar que el texto original coincide con el decodificado
    if (decodedText == texto) {
        std::cout << "Decodificación exitosa: El texto decodificado coincide con el original.\n";
    } else {
        std::cout << "Error en la decodificación.\n";
    }

    // 9. Liberar la memoria del árbol
    deleteTree(root);
    return 0;
}





//g++ -Iinclude src/main.cpp src/frequency.cpp src/HuffmanTree.cpp src/HuffmanUtils.cpp src/HuffmanCodes.cpp src/HuffmanEncoder.cpp src/HuffmanDecoder.cpp -o main

// g++ -Iinclude src/*.cpp -o main

