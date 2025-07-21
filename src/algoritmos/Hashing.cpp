#include "../../include/algoritmos/Hashing.hpp"
#include <string>
#include <algorithm>

unsigned long Algoritmos::simpleHash(const std::string& texto) {
    unsigned long hash = 5381;
    for (char c : texto) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

    
   unsigned long Algoritmos::shiftFoldingHash(const std::string& texto, int chunkSize) {
    unsigned long somaTotal = 0;
    for (size_t i = 0; i < texto.length(); i += chunkSize) {
        std::string pedaco = texto.substr(i, chunkSize);
        unsigned long valorPedaco = 0;
        // Converte o pedaço em um número somando os valores dos caracteres
        for (char c : pedaco) {
            valorPedaco += c;
        }
        somaTotal += valorPedaco;
    }
    return somaTotal;
}

unsigned long Algoritmos::boundaryFoldingHash(const std::string& texto, int chunkSize) {
    unsigned long somaTotal = 0;
    bool inverter = false;
    for (size_t i = 0; i < texto.length(); i += chunkSize) {
        std::string pedaco = texto.substr(i, chunkSize);

        // Inverte cada segundo pedaço
        if (inverter) {
            std::reverse(pedaco.begin(), pedaco.end());
        }

        unsigned long valorPedaco = 0;
        for (char c : pedaco) {
            valorPedaco += c;
        }
        
        somaTotal += valorPedaco;
        inverter = !inverter; // Alterna para o próximo pedaço
    }
    return somaTotal;
}