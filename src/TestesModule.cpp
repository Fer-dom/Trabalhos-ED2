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

void testarHashing_Interativo() {
    std::cout << "\n\n--- DEMONSTRACAO: HASHING (djb2) ---\n";
    std::cout << "Esta funcao transforma um texto (string) em um numero unico (hash).\n";
    std::cout << "A mesma string sempre produzira o mesmo hash.\n";

    std::string textoEntrada;
    while (true) {
        std::cout << "\nDigite um texto para gerar o hash (ex: 'SeloDoFogo' ou 'sair' para voltar):\n>> ";
        std::getline(std::cin >> std::ws, textoEntrada);

        if (textoEntrada == "sair") break;

        unsigned long hashGerado = Algoritmos::simpleHash(textoEntrada);
        std::cout << "  >> O Hash para '" << textoEntrada << "' e: " << Color::BOLD_YELLOW << hashGerado << Color::RESET << "\n";
    }
}

void testarHuffman_Interativo() {
    std::cout << "\n\n--- DEMONSTRACAO: COMPRESSAO DE HUFFMAN ---\n";
    std::cout << "Este algoritmo comprime dados de texto de forma eficiente.\n";

    std::string textoEntrada;
    while (true) {
        std::cout << "\nDigite um texto para comprimir (ex: 'AAAAABBBCC' ou 'sair' para voltar):\n>> ";
        std::getline(std::cin >> std::ws, textoEntrada);

        if (textoEntrada == "sair") break;

        if (textoEntrada.empty()) {
            std::cout << "Texto vazio, nada a fazer.\n";
            continue;
        }

        // 1. Comprimir
        Algoritmos::HuffmanArchiver arquivador;
        std::string textoComprimido = arquivador.compress(textoEntrada);
        std::cout << "\nTexto Comprimido (bits): " << Color::BOLD_CYAN << textoComprimido << Color::RESET << "\n";

        // 2. Mostrar a Eficiência
        size_t tamanhoOriginalBits = textoEntrada.length() * 8;
        size_t tamanhoComprimidoBits = textoComprimido.length();
        std::cout << "Tamanho Original...: " << tamanhoOriginalBits << " bits\n";
        std::cout << "Tamanho Comprimido: " << tamanhoComprimidoBits << " bits\n";
        if (tamanhoOriginalBits > 0 && tamanhoComprimidoBits < tamanhoOriginalBits) {
            double taxaCompressao = 100.0 * (tamanhoOriginalBits - tamanhoComprimidoBits) / tamanhoOriginalBits;
            std::cout << std::fixed;
            std::cout.precision(2);
            std::cout << "Taxa de Compressao: " << Color::BOLD_GREEN << taxaCompressao << "%" << Color::RESET << "\n";
        } else {
            std::cout << "Nao houve ganho de compressao para este texto.\n";
        }
        
        // 3. Descomprimir - versão interativa
        std::cout << "\nAgora digite o codigo comprimido para descomprimir (ou 'auto' para usar o gerado):\n>> ";
        std::string codigoParaDescomprimir;
        std::getline(std::cin >> std::ws, codigoParaDescomprimir);
        
        if (codigoParaDescomprimir == "auto") {
            codigoParaDescomprimir = textoComprimido;
        }

        try {
            std::string textoRestaurado = arquivador.decompress(codigoParaDescomprimir);
            std::cout << "\nTexto Restaurado: \"" << textoRestaurado << "\"\n";
            
            if (textoEntrada == textoRestaurado) {
                std::cout << Color::BOLD_GREEN << "SUCESSO: O texto restaurado e identico ao original.\n" << Color::RESET;
            } else {
                std::cout << Color::BOLD_RED << "FALHA: O texto restaurado e diferente do original.\n" << Color::RESET;
            }
        } catch (const std::exception& e) {
            std::cout << Color::BOLD_RED << "ERRO na descompressao: " << e.what() << Color::RESET << "\n";
        }
    }
}

void TestModule::runAllTests() {
    int opcao;
    do {
        std::cout << "\n==================== MENU DE TESTES ====================\n";
        std::cout << "1. Busca Sequencial\n";
        std::cout << "2. Busca Binaria\n";
        std::cout << "3. Rabin-Karp\n";
        std::cout << "4. Hashing\n";
        std::cout << "5. Compressao Huffman\n";
        std::cout << "0. Voltar ao menu principal\n";
        std::cout << "=======================================================\n>> ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(opcao) {
            case 1: testarBuscaSequencial_Interativo(); break;
            case 2: testarBuscaBinaria_Interativo(); break;
            case 3: testarBuscaRabinKarp_Interativo(); break;
            case 4: testarHashing_Interativo(); break;
            case 5: testarHuffman_Interativo(); break;
            case 0: std::cout << "Retornando...\n"; break;
            default: std::cout << "Opcao invalida.\n"; break;
        }
    } while (opcao != 0);
}
