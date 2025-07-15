#include "../include/TestesModule.hpp"
#include "../include/algoritmos/Busca.hpp"
#include "../include/game_logic/Card.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits> // Para limpar o buffer de entrada

// --- Funções de teste INTERATIVAS ---

void testarBuscaSequencial_Interativo() {
    std::cout << "\n--- DEMONSTRACAO: BUSCA SEQUENCIAL ---\n";
    std::cout << "Esta busca percorre a lista item por item. Ideal para listas pequenas e desordenadas.\n";

    std::vector<Card*> maoDoJogador;
    maoDoJogador.push_back(new Card("Bola de Fogo", "Causa 10 de dano", 3, TipoEfeito::DANO, 10));
    maoDoJogador.push_back(new Card("Escudo Arcano", "Ganha 8 de armadura", 2, TipoEfeito::DEFESA, 8));
    maoDoJogador.push_back(new Card("Raio Congelante", "Causa 5 de dano", 4, TipoEfeito::DANO, 5));
    maoDoJogador.push_back(new Card("Cura Menor", "Restaura 5 de vida", 2, TipoEfeito::CURA, 5));

    std::cout << "\nColecao de dados (Mao do Jogador):\n";
    for (const auto& carta : maoDoJogador) {
        std::cout << " - " << carta->getName() << "\n";
    }

    std::string nomeBusca;
    while (true) {
        std::cout << "\nDigite o nome da carta a procurar (ou 'sair' para voltar ao menu):\n>> ";
        std::getline(std::cin >> std::ws, nomeBusca); // std::ws limpa espaços em branco/quebras de linha

        if (nomeBusca == "sair") break;

        Algoritmos::buscaSequencial(maoDoJogador, nomeBusca);
    }

    for (Card* carta : maoDoJogador) {
        delete carta;
    }
    maoDoJogador.clear();
}

void testarBuscaBinaria_Interativo() {
    std::cout << "\n--- DEMONSTRACAO: BUSCA BINARIA ---\n";
    std::cout << "Esta busca divide a lista ao meio repetidamente. Requer uma lista ORDENADA.\n";

    std::vector<Card*> biblioteca;
    biblioteca.push_back(new Card("Muralha de Gelo", "...", 3, TipoEfeito::DEFESA, 15));
    biblioteca.push_back(new Card("Explosao de Fogo", "...", 5, TipoEfeito::DANO, 20));
    biblioteca.push_back(new Card("Seta Sombria", "...", 2, TipoEfeito::DANO, 8));
    biblioteca.push_back(new Card("Bencao de Luz", "...", 4, TipoEfeito::CURA, 12));
    biblioteca.push_back(new Card("Metamorfose", "...", 1, TipoEfeito::DEFESA, 5));

    std::sort(biblioteca.begin(), biblioteca.end(), [](const Card* a, const Card* b) {
        return a->getName() < b->getName();
    });

    std::cout << "\nColecao de dados (Biblioteca de Feiticos - ja ordenada):\n";
    for(const auto& carta : biblioteca) {
        std::cout << " - " << carta->getName() << "\n";
    }

    std::string nomeBusca;
    while (true) {
        std::cout << "\nDigite o nome da carta a procurar (ou 'sair' para voltar ao menu):\n>> ";
        std::getline(std::cin >> std::ws, nomeBusca);

        if (nomeBusca == "sair") break;

        Algoritmos::buscaBinaria(biblioteca, nomeBusca);
    }
    
    for (Card* carta : biblioteca) {
        delete carta;
    }
    biblioteca.clear();
}

void testarBuscaRabinKarp_Interativo() {
    std::cout << "\n--- DEMONSTRACAO: BUSCA RABIN-KARP ---\n";
    std::cout << "Esta busca encontra um trecho de texto dentro de um texto maior.\n";

    std::string textoPrincipal = "O selo arcano se quebra quando a lua sangrenta ascender no ceu de opalas.";
    std::cout << "\nTexto base para a busca:\n\"" << textoPrincipal << "\"\n";

    std::string padraoBusca;
    while (true) {
        std::cout << "\nDigite o padrao de texto a procurar (ou 'sair' para voltar ao menu):\n>> ";
        std::getline(std::cin >> std::ws, padraoBusca);

        if (padraoBusca == "sair") break;

        Algoritmos::buscaRabinKarp(textoPrincipal, padraoBusca);
    }
}


void TestModule::runAllTests() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "=========================================\n";
    std::cout << "  DEMONSTRACAO DOS ALGORITMOS DE BUSCA \n";
    std::cout << "=========================================\n";

    testarBuscaSequencial_Interativo();
    testarBuscaBinaria_Interativo();
    testarBuscaRabinKarp_Interativo();

    // As chamadas para Huffman e Hashing ficam de fora desta versão.

    std::cout << "\nRetornando ao menu principal...\n";
}