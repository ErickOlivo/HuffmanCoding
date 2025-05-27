#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>            // added for file I/O

#include "frequency.h"
#include "HuffmanNode.h"
#include "HuffmanTree.h"
#include "HuffmanUtils.h"     // for deleteTree and readFileToString
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
#include "CompressedIO.h"     // added for binary compress/decompress

int main(int argc, char* argv[]) {
    // 0. Prepare input and output paths
    std::string inputPath;
    std::string texto = "abracadabra";
    std::string salidaBits = "output.bits";

    if (argc > 1) {
        // Use provided file
        inputPath = argv[1];
        texto = readFileToString(inputPath);
        if (argc > 2) {
            salidaBits = argv[2];
        }
    } else {
        // Write demo text to temporary file
        inputPath = "input_demo.txt";
        std::ofstream tmp(inputPath, std::ios::binary);
        tmp << texto;
        tmp.close();
    }

    std::cout << "Texto original:     " << texto << std::endl;

    // 1. Cálculo de frecuencias
    auto freqMap = computeFrequencies(texto);

    // 1.1 Histograma ASCII a color
    printFrequencyHistogram(freqMap);

    // 2. Construir el árbol de Huffman
    HuffmanNode* root = buildHuffmanTree(freqMap);

    // 2.1 Mostrar árbol “pretty” en la terminal
    std::cout << "\nHuffman tree (pretty):" << std::endl;
    printHuffmanTreePretty(root);

    // 3. Imprimir un mensaje de confirmación
    if (root != nullptr) {
        std::cout << "\nÁrbol de Huffman construido con éxito. "
                  << "Frecuencia total: " << root->frequency << std::endl;
    } else {
        std::cout << "No se pudo construir el árbol (texto vacío o error)." << std::endl;
    }

    // 4. Generar códigos
    auto codes = generateHuffmanCodes(root);

    // 5. Mostrar códigos
    std::cout << "\nCódigos Huffman generados:\n";
    for (const auto& pair : codes) {
        std::cout << "Carácter: '" << pair.first << "' => " << pair.second << '\n';
    }

    // 6. Codificar el texto usando los códigos
    std::string encodedText = encodeText(texto, codes);

    // 6.1 Guardar bitstream lógico
    writeBitStringToFile(salidaBits, encodedText);

    // --- New: compress to real binary format ---
    const std::string binOut = "output.huf";
    if (huffman::util::writeCompressedFile(inputPath, binOut)) {
        std::cout << "\nBinary compressed file written: " << binOut << std::endl;
    } else {
        std::cerr << "\nError writing binary compressed file: " << binOut << std::endl;
    }

    // --- New: decompress and verify ---
    const std::string decompressedFile = "decompressed.txt";
    if (huffman::util::readCompressedFile(binOut, decompressedFile)) {
        std::cout << "Binary file decompressed to: " << decompressedFile << std::endl;

        std::string originalFromFile = readFileToString(inputPath);
        std::string roundtrip = readFileToString(decompressedFile);

        if (roundtrip == originalFromFile) {
            std::cout << "Round-trip verification: SUCCESS" << std::endl;
        } else {
            // std::cout << "Round-trip verification: FAILURE" << std::endl;
            std::cout << "[DEBUG] Original size: " << originalFromFile.size()
                    << ", Decompressed size: " << roundtrip.size() << std::endl;

            size_t mismatchIndex = 0;
            size_t len = std::min(roundtrip.size(), originalFromFile.size());
            for (; mismatchIndex < len; ++mismatchIndex) {
                if (roundtrip[mismatchIndex] != originalFromFile[mismatchIndex]) {
                    std::cout << "[DEBUG] Mismatch at index " << mismatchIndex << ": original = '"
                            << originalFromFile[mismatchIndex] << "' (" << static_cast<int>(originalFromFile[mismatchIndex])
                            << "), decompressed = '" << roundtrip[mismatchIndex] << "' ("
                            << static_cast<int>(roundtrip[mismatchIndex]) << ")\n";
                    break;
                }
            }

            if (roundtrip.size() != originalFromFile.size()) {
                std::cout << "[DEBUG] Sizes differ. Original ends with: '"
                        << originalFromFile.back() << "' ("
                        << static_cast<int>(originalFromFile.back()) << "), "
                        << "Decompressed ends with: '" << roundtrip.back() << "' ("
                        << static_cast<int>(roundtrip.back()) << ")\n";
            }
        }
    }
    // --- end new section ---

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

