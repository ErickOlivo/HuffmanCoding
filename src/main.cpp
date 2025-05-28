#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <algorithm>

#include "frequency.h"
#include "HuffmanNode.h"
#include "HuffmanTree.h"
#include "HuffmanUtils.h"
#include "HuffmanCodes.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"
#include "CompressedIO.h"

using huffman::util::writeCompressedFile;
using huffman::util::readCompressedFile;

/* ------------------------------------------------------------------------- */
/*  HELP                                                                     */
/* ------------------------------------------------------------------------- */
static void printHelp()
{
    std::cout <<
      "HuffmanCoding — command-line usage\n"
      "  -c <input> <output.huf>   Compress file\n"
      "  -d <input.huf> <output>   Decompress file\n"
      "  -h                        Show this help\n"
      "If no flag is given, a built-in demo with the text \"abracadabra\" runs.\n";
}

/* ------------------------------------------------------------------------- */
/*  DEMO PIPELINE (your entire original flow)                                */
/* ------------------------------------------------------------------------- */
static int runDemo()
{
    std::string texto = "abracadabra";
    std::cout << "Texto original: " << texto << "\n";

    /* 1. Frecuencias + histograma */
    auto freqMap = computeFrequencies(texto);
    printFrequencyHistogram(freqMap);

    /* 2. Árbol */
    HuffmanNode* root = buildHuffmanTree(freqMap);
    std::cout << "\nÁrbol de Huffman (pretty):\n";
    printHuffmanTreePretty(root);

    /* 3. Generar códigos */
    auto codes = generateHuffmanCodes(root);
    std::cout << "\nCódigos Huffman:\n";
    for (auto const& [ch, code] : codes)
        std::cout << "'" << ch << "' => " << code << '\n';

    /* 4. Codificar + stats */
    std::string encoded = encodeText(texto, codes);
    reportCompressionStats(texto, encoded);

    /* 5. Decodificar verificación */
    std::string decoded = decodeText(encoded, root);
    std::cout << "\nTexto decodificado: " << decoded << "\n";
    std::cout << (decoded == texto ?
        "✔ Round-trip OK\n" : "✗ Round-trip failed\n");

    deleteTree(root);
    return 0;
}

/* ------------------------------------------------------------------------- */
/*  MAIN — CLI flags                                                         */
/* ------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
    /* 1. Ayuda */
    if (argc == 2 && std::string(argv[1]) == "-h") {
        printHelp();
        return 0;
    }

    /* 2. Compress: -c in out.huf */
    if (argc == 4 && std::string(argv[1]) == "-c") {
        std::string in  = argv[2];
        std::string out = argv[3];
        if (writeCompressedFile(in, out)) {
            std::cout << "✔ Compressed '" << in << "' → '" << out << "'\n";
            return 0;
        }
        std::cerr << "✗ Compression failed\n";
        return 1;
    }

    /* 3. Decompress: -d in.huf out */
    if (argc == 4 && std::string(argv[1]) == "-d") {
        std::string in  = argv[2];
        std::string out = argv[3];
        if (readCompressedFile(in, out)) {
            std::cout << "✔ Decompressed '" << in << "' → '" << out << "'\n";
            return 0;
        }
        std::cerr << "✗ Decompression failed (corrupt file?)\n";
        return 1;
    }

    /* 4. Sin flags → demo */
    printHelp();
    std::cout << "\n--- Running demo ---\n";
    return runDemo();
}





//g++ -Iinclude src/main.cpp src/frequency.cpp src/HuffmanTree.cpp src/HuffmanUtils.cpp src/HuffmanCodes.cpp src/HuffmanEncoder.cpp src/HuffmanDecoder.cpp -o main

// g++ -Iinclude src/*.cpp -o main


/*
# build
make clean && make all

# show help
./main -h

# compress
./main -c samples/sample_short.txt short.huf

# decompress
./main -d short.huf short_out.txt

# verify
diff samples/sample_short.txt short_out.txt   # no output ⇒ identical
*/
