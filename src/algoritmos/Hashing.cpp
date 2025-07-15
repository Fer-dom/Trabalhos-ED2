#include "../../include/algoritmos/Hashing.hpp"

unsigned long Algoritmos::simpleHash(const std::string& texto) {
    // 5381 é um número primo escolhido por sua propriedade de
    // gerar poucas colisões. É o "número mágico" do algoritmo djb2.
    unsigned long hash = 5381;

    // Itera sobre cada caractere da string de entrada
    for (char c : texto) {
        // A fórmula principal do djb2: hash = (hash * 33) + c
        // A operação de shift de bits (hash << 5) é uma forma muito rápida
        // que os compiladores usam para multiplicar por 32.
        // Então, (hash << 5) + hash é o mesmo que (hash * 32) + hash, ou seja, hash * 33.
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}