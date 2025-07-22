#include "../include/TestesModule.hpp"
#include "../include/algoritmos/Busca.hpp"
#include "../include/algoritmos/Huffman.hpp"
#include "../include/algoritmos/Hashing.hpp"
#include "../include/game_logic/Card.hpp"
#include "../include/utils/Color.hpp" 

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>

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
        std::getline(std::cin >> std::ws, nomeBusca);

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
    biblioteca.push_back(new Card("Bola de Fogo", "...", 5, TipoEfeito::DANO, 20));
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

    std::string textoPrincipal = "O selo arcano se quebra quando a lua sangrenta ascender no ceu.";
    std::cout << "\nTexto base para a busca:\n\"" << textoPrincipal << "\"\n";

    std::string padraoBusca;
    while (true) {
        std::cout << "\nDigite o padrao de texto a procurar (ou 'sair' para voltar ao menu):\n>> ";
        std::getline(std::cin >> std::ws, padraoBusca);

        if (padraoBusca == "sair") break;

        Algoritmos::buscaRabinKarp(textoPrincipal, padraoBusca);
    }
}


void testarHuffman_Interativo() {
    std::cout << "\n\n--- DEMONSTRACAO: COMPRESSAO DE HUFFMAN ---\n";
    std::cout << "Este algoritmo comprime e descomprime dados sem perdas.\n";

    std::string textoOriginal;
    std::cout << "\nDigite o texto que voce deseja comprimir:\n>> ";
    std::getline(std::cin >> std::ws, textoOriginal);

    if (textoOriginal.empty()) {
        std::cout << "Texto vazio, nada a fazer.\n";
        return;
    }

    // 1. Comprimir
    Algoritmos::HuffmanArchiver arquivador;
    std::string textoComprimido = arquivador.compress(textoOriginal);
    std::cout << "\nTexto Comprimido (bits): " << Color::BOLD_CYAN << textoComprimido << Color::RESET << "\n";
    std::cout << "\n--- Teste de Verificacao ---\n";
    std::cout << "Para provar que a descompressao funciona, por favor, copie a string de bits acima\n";
    std::cout << "e cole-a no campo abaixo para decodifica-la de volta:\n>> ";
    
    std::string bitsParaDecodificar;
    std::getline(std::cin, bitsParaDecodificar);

    //Descomprimir e Verificar
    std::string textoRestaurado = arquivador.decompress(bitsParaDecodificar);
    std::cout << "\nTexto Restaurado: \"" << textoRestaurado << "\"\n";
    if (textoOriginal == textoRestaurado) {
        std::cout << Color::BOLD_GREEN << "SUCESSO: O texto restaurado e identico ao original. O processo funciona!\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "FALHA: O texto restaurado e diferente do original.\n" << Color::RESET;
    }
}

void testarHashing_Interativo() {
    int opcao;
    std::string textoEntrada;
    int tamanhoDoPedaco = 4; // Um valor padrão razoável

    do {
        std::cout << "\n\n--- DEMONSTRACAO: HASHING POR DOBRAMENTO (FOLDING) ---\n";
        std::cout << "Escolha a tecnica que deseja demonstrar:\n";
        std::cout << "1. Enlaceamento Deslocado (Shift Folding)\n";
        std::cout << "2. Enlaceamento Limite (Boundary Folding)\n";
        std::cout << "0. Voltar ao menu de testes\n";
        std::cout << "======================================================\n>> ";

        std::string input;
        std::getline(std::cin >> std::ws, input);
        try {
            opcao = std::stoi(input);
        } catch (const std::exception& e) {
            opcao = -1;
        }

        if (opcao == 1 || opcao == 2) {
            std::cout << "\nDigite um texto para gerar o hash (ex: 'Arch Arcanum'):\n>> ";
            std::getline(std::cin, textoEntrada);
        }

        switch(opcao) {
            case 1: {
                std::cout << "\nCalculando com Enlaceamento Deslocado...\n";
                unsigned long hashGerado = Algoritmos::shiftFoldingHash(textoEntrada, tamanhoDoPedaco);
                std::cout << "  >> O Hash para '" << textoEntrada << "' e: " << Color::BOLD_YELLOW << hashGerado << Color::RESET << "\n";
                std::cout << "Pressione Enter para continuar...";
                std::cin.get();
                break;
            }
            case 2: {
                std::cout << "\nCalculando com Enlaceamento Limite...\n";
                unsigned long hashGerado = Algoritmos::boundaryFoldingHash(textoEntrada, tamanhoDoPedaco);
                std::cout << "  >> O Hash para '" << textoEntrada << "' e: " << Color::BOLD_CYAN << hashGerado << Color::RESET << "\n";
                std::cout << "Pressione Enter para continuar...";
                std::cin.get();
                break;
            }
            case 0:
                std::cout << "Retornando...\n";
                break;
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    } while (opcao != 0);
}

void TestModule::runAllTests() {
    int opcao;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    do {
        std::cout << "\n==================== MENU DE TESTES DE ALGORITMOS ====================\n";
        std::cout << "1. Demonstracao de Busca Sequencial\n";
        std::cout << "2. Demonstracao de Busca Binaria\n";
        std::cout << "3. Demonstracao de Busca Rabin-Karp\n";
        std::cout << "4. Demonstracao de Hashing por Dobramento\n";
        std::cout << "5. Demonstracao de Compressao Huffman\n";
        std::cout << "0. Voltar ao menu principal\n";
        std::cout << "====================================================================\n>> ";
        
        std::string input;
        std::getline(std::cin, input);

        try {
            opcao = std::stoi(input);
        } catch (const std::exception& e) {
            opcao = -1;
        }

        switch(opcao) {
            case 1: testarBuscaSequencial_Interativo(); break;
            case 2: testarBuscaBinaria_Interativo(); break;
            case 3: testarBuscaRabinKarp_Interativo(); break;
            case 4: testarHashing_Interativo(); break;
            case 5: testarHuffman_Interativo(); break;
            case 0: std::cout << "Retornando ao menu principal...\n"; break;
            default: std::cout << "Opcao invalida. Tente novamente.\n"; break;
        }
    } while (opcao != 0);
}
