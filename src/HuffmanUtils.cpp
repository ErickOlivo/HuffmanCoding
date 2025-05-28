#include "HuffmanUtils.h"

#include <iostream>
#include <iomanip>  // Para std::setprecision
#include <string>

#include <vector>
#include <sstream>
#include <algorithm>

#include <array>           // paleta de colores ANSI
#include <unordered_map>   // tipo freqMap

#include <fstream>
#include <stdexcept>

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


/**
 * @brief Lee un archivo completo y lo devuelve como std::string.
 * @throws std::runtime_error si no se puede abrir.
 */
std::string readFileToString(const std::string& path)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
        throw std::runtime_error("Cannot open " + path);
    return { std::istreambuf_iterator<char>(in),
             std::istreambuf_iterator<char>() };
}

/**
 * @brief Guarda una cadena de '0'/'1' (bitstream lógico) en un archivo.
 * @throws std::runtime_error si no se puede crear/escribir.
 */
void writeBitStringToFile(const std::string& path, const std::string& bits)
{
    std::ofstream out(path, std::ios::binary);
    if (!out)
        throw std::runtime_error("Cannot open " + path + " for writing");
    out << bits;
    std::cout << "Bitstream written to " << path << '\n';
}



/**
 * @brief Construye recursivamente una representación 2‑D del subárbol.
 *
 * Devuelve: vector de líneas, ancho total, posición del centro, altura.
 * Basado en la idea de https://stackoverflow.com/a/14648290
 */
static std::tuple<std::vector<std::string>, int, int, int>
buildPretty(const HuffmanNode* node)
{
    if (!node) return { {}, 0, 0, 0 };

    // Etiqueta para este nodo
    std::ostringstream oss;
    if (!node->left && !node->right)
        oss << "('" << node->character << "', " << node->frequency << ")";
    else
        oss << "(*, " << node->frequency << ")";
    std::string label = oss.str();
    int labelW = static_cast<int>(label.size());

    // Caso base: hoja
    if (!node->left && !node->right)
        return { { label }, labelW, labelW / 2, 1 };

    // Construir hijos
    auto [leftLines,  leftW,  leftMid,  leftH ] = buildPretty(node->left);
    auto [rightLines, rightW, rightMid, rightH] = buildPretty(node->right);

    int gap = 3;                                  // espacio mínimo entre sub‑árboles
    int width  = leftW + gap + rightW;
    int height = std::max(leftH, rightH) + 2;
    int mid = leftW + gap / 2;                    // centro donde irá el label

    std::vector<std::string> lines(height, std::string(width, ' '));

    // Copiar label centrado
    lines[0].replace(mid - labelW / 2, labelW, label);

    // Ramas “/” y “\”
    if (node->left)  lines[1][leftMid]                = '/';
    if (node->right) lines[1][leftW + gap + rightMid] = '\\';

    // Copiar sub‑líneas
    for (int i = 0; i < leftH; ++i)
        lines[i + 2].replace(0, leftW, leftLines[i]);
    for (int i = 0; i < rightH; ++i)
        lines[i + 2].replace(leftW + gap, rightW, rightLines[i]);

    return { lines, width, mid, height };
}

/**
 * @brief Imprime el árbol de Huffman con ramas diagonales “/ \” y nodos centrados.
 *
 * @param root Puntero a la raíz del árbol.
 */
void printHuffmanTreePretty(const HuffmanNode* root)
{
    auto [lines, width, mid, height] = buildPretty(root);
    for (const auto& l : lines) std::cout << l << '\n';
}


// Paleta básica de 6 colores ANSI (códigos 31‑36)
static const std::array<const char*, 6> COLORS = {
    "\033[31m", "\033[32m", "\033[33m",
    "\033[34m", "\033[35m", "\033[36m"
};

/**
 * @brief Imprime un histograma ASCII a color con las frecuencias de caracteres.
 *
 * Cada barra se dibuja con el bloque Unicode U+2588 y un color ANSI diferente.
 * @param freqMap Mapa (carácter -> frecuencia).
 */
void printFrequencyHistogram(const std::unordered_map<char,int>& freqMap)
{
    if (freqMap.empty()) return;

    int maxFreq = 0;
    for (auto& kv : freqMap)
        maxFreq = std::max(maxFreq, kv.second);

    const int BAR_WIDTH = 40;
    std::cout << "\nFrecuencia de caracteres\n------------------------\n";

    int colorIdx = 0;
    for (auto& kv : freqMap) {
        double ratio  = static_cast<double>(kv.second) / maxFreq;
        int blocks    = static_cast<int>(ratio * BAR_WIDTH);
        const char* c = COLORS[colorIdx++ % COLORS.size()];

        std::cout << "'" << kv.first << "' | "
        << c << std::string(blocks, '#') << "\033[0m "
        << kv.second << '\n';


    }
}

/* ------------------------------------------------------------------ */
/*  Export tree to Graphviz DOT                                       */
/* ------------------------------------------------------------------ */
#include <sstream>   // para std::ostringstream

/** @brief Función recursiva para recorrer el árbol y emitir nodos/aristas. */
static void dotHelper(const HuffmanNode* node,
                      std::ofstream& out,
                      int& counter)
{
    if (!node) return;
    int thisId = counter++;

    std::ostringstream label;
    if (!node->left && !node->right)
        label << node->character << " (" << node->frequency << ")";
    else
        label << "*" << " (" << node->frequency << ")";

    out << "  n" << thisId << " [label=\"" << label.str() << "\"];\n";

    if (node->left) {
        int childId = counter;
        dotHelper(node->left, out, counter);
        out << "  n" << thisId << " -> n" << childId << " [label=\"0\"];\n";
    }
    if (node->right) {
        int childId = counter;
        dotHelper(node->right, out, counter);
        out << "  n" << thisId << " -> n" << childId << " [label=\"1\"];\n";
    }
}

/** @brief Exporta el árbol a un archivo DOT para Graphviz.
 *
 * Luego puedes hacer:
 *     dot -Tsvg tree.dot -o tree.svg
 * para obtener la visualización en SVG.
 */
void exportTreeToDot(const HuffmanNode* root,
                     const std::string& dotPath)
{
    std::ofstream out(dotPath);
    if (!out) {
        std::cerr << "Cannot write DOT file: " << dotPath << '\n';
        return;
    }
    out << "digraph Huffman {\n"
           "  node [shape=ellipse, fontname=\"Courier\"];\n";
    int counter = 0;
    dotHelper(root, out, counter);
    out << "}\n";
    std::cout << "DOT file written: " << dotPath << '\n';
}
