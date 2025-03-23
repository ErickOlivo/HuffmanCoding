#pragma once
#include <unordered_map>
#include <string>

/**
 * @brief Calcula la frecuencia de cada carácter en un texto.
 *
 * @param text Cadena de entrada.
 * @return std::unordered_map<char, int> Mapa con frecuencias (carácter -> cantidad de apariciones).
 */
std::unordered_map<char, int> computeFrequencies(const std::string& text);
