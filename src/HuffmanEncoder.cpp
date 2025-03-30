#include "HuffmanEncoder.h"

std::string encodeText(const std::string& text, const std::unordered_map<char, std::string>& codes) {
    std::string encoded;
    encoded.reserve(text.size() * 2);
    // Reserva inicial de memoria, para optimizar concatenaciones

    for (char c : text) {
        // Agregar la representación binaria correspondiente a cada carácter
        encoded += codes.at(c);
        // Se usa 'codes.at(c)' que lanza excepción si 'c' no está en el mapa
        // (Podrías usar operator[] si quieres una versión sin excepción)
    }

    return encoded;
}
