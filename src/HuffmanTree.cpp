#include "HuffmanTree.h"

/**
 * @brief Functor de comparación para la cola de prioridad.
 *        Retorna ture sí lhs->frequency es mayor que rhs->frequency,
 *        de modo que el nodo menor frecuencia tenga mayor prioridad.
 */
struct Compare {
    bool operator()(const HuffmanNode* lhs, const HuffmanNode* rhs) const {
        return lhs->frequency > rhs->frequency;
    }
};

HuffmanNode* buildHuffmanTree(const std::unordered_map<char, int>& freqMap) {
    // Cola de prioridad que guarda punteros a HuffmanNode, ordenados por frecuencia ascendente
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> minHeap;

    // 1. Crear un nodo por cada carácter y frecuencia; insertarlos en la cola
    for (auto& pair : freqMap) {
        HuffmanNode* node = new HuffmanNode(pair.first, pair.second);
        minHeap.push(node);
    }

    // 2. Combinar los dos nodos de menor frecuencia hasta que quede solo uno
    while (minHeap.size() > 1) {
        // Extrae los dos nodos con menor frecuencia
        HuffmanNode* left = minHeap.top();
        minHeap.pop();
        HuffmanNode* right = minHeap.top();
        minHeap.pop();

        // Crear un nodo padre con la frecuecia = suma de las frecuencias de los hijos
        HuffmanNode* parent = new HuffmanNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        // Re-insertar el nodo padre en la cola
        minHeap.push(parent);
    }

    // 3. El único nodo que queda en la cola es la raíz del árbol
    HuffmanNode* root = (minHeap.empty()) ? nullptr : minHeap.top();
    return root;
}
