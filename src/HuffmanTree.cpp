#include "HuffmanTree.h"
#include <cstddef>   // std::size_t

/** @brief Pequeño contenedor que agrupa un nodo y el orden (seq) en que se insertó
 *
 * Añadimos la secuencia para romper empates de forma determinista cuando dos
 * nodos tienen la misma frecuencia.  Así, el “min-heap” siempre extrae primero
 * el nodo que llegó antes, garantizando que el árbol resultante sea idéntico
 * en compresión y descompresión.
 */
struct NodeWrap {
    HuffmanNode* node;  ///< Puntero al nodo real del árbol
    std::size_t  seq;   ///< Orden de inserción (creciente)
};

/** @brief Comparador estable para el heap de construcción del árbol
 *
 * - Primero prioriza la menor frecuencia (`frequency`).
 * - Si las frecuencias son iguales, prioriza el menor `seq` (FIFO).
 */
struct Compare {
    bool operator()(const NodeWrap& a, const NodeWrap& b) const {
        if (a.node->frequency != b.node->frequency)
            return a.node->frequency > b.node->frequency;  // heap “min”
        return a.seq > b.seq;                              // estable en empate
    }
};

/** @brief Construye un árbol de Huffman determinista a partir de un mapa de
 *         frecuencias.
 *
 * La función usa una `priority_queue` con un comparador estable, de modo que
 * para un mismo conjunto de frecuencias siempre se obtiene exactamente el
 * mismo árbol.  Esto evita que la fase de descompresión reconstruya un árbol
 * diferente cuando hay símbolos con igual frecuencia.
 *
 * @param freqMap Mapa (carácter → frecuencia) calculado previamente.
 * @return Puntero a la raíz del árbol (o `nullptr` si el mapa está vacío).
 */
HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap)
{
    std::priority_queue<NodeWrap,
                        std::vector<NodeWrap>,
                        Compare> minHeap;

    static std::size_t SEQ = 0;   // contador global para romper empates

    /* 1. Crear una hoja por cada símbolo */
    for (auto const& [ch, freq] : freqMap) {
        minHeap.push({ new HuffmanNode(ch, freq), SEQ++ });
    }

    /* 2. Combinar repetidamente los dos nodos de menor frecuencia */
    while (minHeap.size() > 1) {
        auto left  = minHeap.top(); minHeap.pop();
        auto right = minHeap.top(); minHeap.pop();

        auto parent = new HuffmanNode('\0',
                                      left.node->frequency + right.node->frequency);
        parent->left  = left.node;
        parent->right = right.node;

        minHeap.push({ parent, SEQ++ });
    }

    /* 3. La raíz del árbol es el único nodo restante */
    return minHeap.empty() ? nullptr : minHeap.top().node;
}
