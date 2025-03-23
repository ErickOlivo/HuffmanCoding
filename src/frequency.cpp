#include "frequency.h"

std::unordered_map<char, int> computeFrequencies(const std::string& text) {
    std::unordered_map<char, int> frequencyMap;

    for (char c : text) {
        frequencyMap[c]++;
    }

    return frequencyMap;
}
