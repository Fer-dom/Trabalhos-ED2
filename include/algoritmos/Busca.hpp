#pragma once 
#include <string>
#include <vector>
#include "../game_logic/Card.hpp" 

namespace Algoritmos {

    Card* buscaSequencial(const std::vector<Card*>& colecao, const std::string& nomeAlvo);
    Card* buscaBinaria(const std::vector<Card*>& colecaoOrdenada, const std::string& nomeAlvo);
    int buscaRabinKarp(const std::string& texto, const std::string& padrao);

} 