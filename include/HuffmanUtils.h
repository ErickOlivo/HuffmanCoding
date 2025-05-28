#pragma once
#include "HuffmanNode.h"
#include <string>
#include <unordered_map>

/**
 * @brief Libera la memoria de un árbol de Huffman.
 *
 * @param node Puntero al nodo de raíz del árbol.
 */
void deleteTree(HuffmanNode* node);


/**
 * @brief Muestra estadísticas de compresión entre el texto original y codificado.
 *
 * @param original Texto original sin comprimir.
 * @param encoded Texto codificado (en forma de string de bits).
 */
void reportCompressionStats(const std::string& original, const std::string& encoded);


/**
 * @brief Imprime el árbol de Huffman en formato “pretty” ASCII
 *        con ramas diagonales ( `/`  y  `\` ).
 *
 * Ejemplo de salida:
 *        (*, 11)
 *        /     \
 *    ('a', 5)  (*, 6)
 *              /    \
 *         ('b',2)  (*,4)
 *                   /  \
 *              ('c',1) ('d',1)
 *
 * @param root Puntero a la raíz del árbol.
 */
void printHuffmanTreePretty(const HuffmanNode* root);


/**
 * @brief Imprime un histograma ASCII a color con las frecuencias de caracteres.
 * @param freqMap Mapa (carácter -> frecuencia).
 */
void printFrequencyHistogram(const std::unordered_map<char,int>& freqMap);


/**
 * @brief Lee un archivo completo a un std::string.
 * @param path Ruta del archivo.
 * @return Contenido del archivo (lanza std::runtime_error si falla).
 */
std::string readFileToString(const std::string& path);

/**
 * @brief Escribe una cadena de '0'/'1' (bitstream lógico) a un archivo.
 * @param path Ruta de salida.
 * @param bits Cadena con los bits.
 */
void writeBitStringToFile(const std::string& path, const std::string& bits);

