#include <iostream>
#include "frequency.h"

int main() {
    std::string texto = "abracadabra";

    // Llamada a la función de cálculo de frecuecias
    std::unordered_map<char, int> freqMap = computeFrequencies(texto);

    // Muestra las frecuencias en pantalla
    for (auto& pair : freqMap) {
        std::cout << "Caracter: '" << pair.first << "' - Frecuencia: " << pair.second << std::endl;
    }

    return 0;
}

/*
Desde src/
g++ -I../include main.cpp frequency.cpp -o main


Desde la raíz del proyecto
g++ -Iinclude src/main.cpp src/frequency.cpp -o main

*/
