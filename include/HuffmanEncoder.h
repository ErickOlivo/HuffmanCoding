#pragma once
#include <string>
#include <unordered_map>

/**
 * @brief Codifica un texto usando un mapa de códigos de Huffman.
 *
 * @param text Texto original a codificar.
 * @param codes Mapa (carácter -> código binario) generado previamente.
 * @return std::string Cadena de bits representando el texto codificado.
 */
std::string encodeText(const std::string& text, const std::unordered_map<char, std::string>& codes);
