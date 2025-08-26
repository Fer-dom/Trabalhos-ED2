#include "../include/TestesModule.hpp"
#include "../include/algoritmos/Busca.hpp"
#include "../include/algoritmos/Huffman.hpp"
#include "../include/algoritmos/Hashing.hpp"
#include "../include/game_logic/Card.hpp"
#include "../include/utils/Color.hpp"
#include "../include/algoritmos/Graph.hpp" 

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <iomanip>

namespace TestModule {
    void testarBuscaSequencial_Interativo();
    void testarBuscaBinaria_Interativo();
    void testarBuscaRabinKarp_Interativo();
    void testarHuffman_Interativo();
    void testarHashing_Interativo();
    void testarGrafo_Modulo1();
    void testarGrafo_Modulo2_DFS();
    void testarGrafo_Modulo2_BFS();
    void testarGrafo_Modulo2_Dijkstra();
    void testarGrafo_Modulo3_MST();
    void editorDeGrafo();
}

void TestModule::testarBuscaSequencial_Interativo() {
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

void TestModule::testarBuscaBinaria_Interativo() {
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

void TestModule::testarBuscaRabinKarp_Interativo() {
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


void TestModule::testarHuffman_Interativo() {
    std::cout << "\n\n--- DEMONSTRACAO: COMPRESSAO DE HUFFMAN ---\n";
    std::cout << "Este algoritmo comprime e descomprime dados sem perdas.\n";

    std::string textoOriginal;
    std::cout << "\nDigite o texto que voce deseja comprimir:\n>> ";
    std::getline(std::cin >> std::ws, textoOriginal);

    if (textoOriginal.empty()) {
        std::cout << "Texto vazio, nada a fazer.\n";
        return;
    }

    Algoritmos::HuffmanArchiver arquivador;
    std::string textoComprimido = arquivador.compress(textoOriginal);
    std::cout << "\nTexto Comprimido (bits): " << Color::BOLD_CYAN << textoComprimido << Color::RESET << "\n";
    std::cout << "\n--- Teste de Verificacao ---\n";
    std::cout << "Para provar que a descompressao funciona, por favor, copie a string de bits acima\n";
    std::cout << "e cole-a no campo abaixo para decodifica-la de volta:\n>> ";
    
    std::string bitsParaDecodificar;
    std::getline(std::cin, bitsParaDecodificar);

    std::string textoRestaurado = arquivador.decompress(bitsParaDecodificar);
    std::cout << "\nTexto Restaurado: \"" << textoRestaurado << "\"\n";
    if (textoOriginal == textoRestaurado) {
        std::cout << Color::BOLD_GREEN << "SUCESSO: O texto restaurado e identico ao original. O processo funciona!\n" << Color::RESET;
    } else {
        std::cout << Color::BOLD_RED << "FALHA: O texto restaurado e diferente do original.\n" << Color::RESET;
    }
}

void TestModule::testarHashing_Interativo() {
    int opcao;
    std::string textoEntrada;
    int tamanhoDoPedaco = 4;

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

void TestModule::editorDeGrafo() {
    Graph g;
    std::string cmd;
    std::cout << "\n-- Editor de Grafo (addv N | adde A B w [dir=1] | rmv N | rme A B [dir=1] | print | matrix | back)\n";
    while (true) {
        std::cout << ">> ";
        if (!std::getline(std::cin, cmd)) break;
        if (cmd == "back") break;
        std::istringstream iss(cmd);
        std::string op; iss >> op;
        if (op == "addv") {
            std::string n; iss >> n; g.addVertex(n);
        } else if (op == "adde") {
            std::string a,b; int w=1, dir=1; iss >> a >> b >> w >> dir;
            g.addEdge(a,b,w, dir==1?true:false);
        } else if (op == "rmv") {
            std::string n; iss >> n; g.removeVertex(n);
        } else if (op == "rme") {
            std::string a,b; int dir=1; iss >> a >> b >> dir;
            g.removeEdge(a,b, dir==1?true:false);
        } else if (op == "print") {
            g.printAdjList();
        } else if (op == "matrix") {
            g.printAdjMatrix();
        } else {
            std::cout << "Comando invalido.\n";
        }
    }
}

void TestModule::testarGrafo_Modulo1() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 1 - GRAFOS ---\n";
    Graph mapaMundo;
    mapaMundo.addVertex("Capital City");
    mapaMundo.addVertex("Vila do Porto");
    mapaMundo.addVertex("Floresta Sombria");
    mapaMundo.addVertex("Montanhas Geladas");
    mapaMundo.addVertex("Torre do Mago");
    mapaMundo.addEdge("Capital City", "Vila do Porto", 10, false);
    mapaMundo.addEdge("Capital City", "Floresta Sombria", 15, false);
    mapaMundo.addEdge("Floresta Sombria", "Torre do Mago", 20);
    mapaMundo.addEdge("Vila do Porto", "Montanhas Geladas", 25);
    mapaMundo.addEdge("Montanhas Geladas", "Torre do Mago", 10);
    mapaMundo.addEdge("Capital City", "Deserto Perdido", 50);
    
    mapaMundo.printAdjList();
    mapaMundo.printAdjMatrix();

    std::cout << "\nTeste do Módulo 1 do Grafo concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::testarGrafo_Modulo2_DFS() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 2 - DFS (Busca em Profundidade) ---\n";
    Graph mapaMundo;
    mapaMundo.addVertex("A"); mapaMundo.addVertex("B"); mapaMundo.addVertex("C");
    mapaMundo.addVertex("D"); mapaMundo.addVertex("E"); mapaMundo.addVertex("F");

    mapaMundo.addEdge("A", "B", 1);
    mapaMundo.addEdge("A", "C", 1);
    mapaMundo.addEdge("B", "D", 1);
    mapaMundo.addEdge("B", "E", 1);
    mapaMundo.addEdge("C", "F", 1);

    std::cout << "\nGrafo de teste criado:\n";
    mapaMundo.printAdjList();

    std::cout << "\nIniciando DFS a partir do vertice 'A':\n";
    std::vector<std::string> resultadoDfs = mapaMundo.dfs("A");

    std::cout << "Ordem de visitacao: ";
    for (const auto& nome : resultadoDfs) {
        std::cout << nome << " ";
    }
    std::cout << std::endl;

    std::cout << "\nTeste do DFS concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::testarGrafo_Modulo2_BFS() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 2 - BFS (Busca em Largura) ---\n";
    Graph mapaMundo;
    mapaMundo.addVertex("A"); mapaMundo.addVertex("B"); mapaMundo.addVertex("C");
    mapaMundo.addVertex("D"); mapaMundo.addVertex("E"); mapaMundo.addVertex("F");

    // Usando o mesmo grafo do teste de DFS para comparar os resultados
    mapaMundo.addEdge("A", "B", 1);
    mapaMundo.addEdge("A", "C", 1);
    mapaMundo.addEdge("B", "D", 1);
    mapaMundo.addEdge("B", "E", 1);
    mapaMundo.addEdge("C", "F", 1);

    std::cout << "\nGrafo de teste criado:\n";
    mapaMundo.printAdjList();

    std::cout << "\nIniciando BFS a partir do vertice 'A':\n";
    std::vector<std::string> resultadoBfs = mapaMundo.bfs("A");

    std::cout << "Ordem de visitacao: ";
    for (const auto& nome : resultadoBfs) {
        std::cout << nome << " ";
    }
    std::cout << std::endl;

    std::cout << "\nTeste da BFS concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::testarGrafo_Modulo2_Dijkstra() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 2 - DIJKSTRA (Caminho Mais Curto) ---\n";
    Graph mapaMundo;
    mapaMundo.addVertex("A"); mapaMundo.addVertex("B"); mapaMundo.addVertex("C");
    mapaMundo.addVertex("D"); mapaMundo.addVertex("E"); mapaMundo.addVertex("F");

    mapaMundo.addEdge("A", "B", 7);
    mapaMundo.addEdge("A", "C", 9);
    mapaMundo.addEdge("A", "D", 14);
    mapaMundo.addEdge("B", "C", 1);
    mapaMundo.addEdge("B", "E", 2);
    mapaMundo.addEdge("C", "D", 2);
    mapaMundo.addEdge("C", "F", 11);
    mapaMundo.addEdge("D", "F", 9);
    mapaMundo.addEdge("E", "F", 6);
    
    std::cout << "\nGrafo de teste com pesos criado:\n";
    mapaMundo.printAdjList();

    std::string inicio = "A";
    std::string fim = "F";
    std::cout << "\nCalculando o caminho mais barato de '" << inicio << "' para '" << fim << "'...\n";

    auto resultado = mapaMundo.dijkstra(inicio, fim);
    int custo = resultado.first;
    std::vector<std::string> caminho = resultado.second;

    if (custo != -1) {
        std::cout << "Custo total: " << custo << std::endl;
        std::cout << "Caminho: ";
        for (size_t i = 0; i < caminho.size(); ++i) {
            std::cout << caminho[i] << (i == caminho.size() - 1 ? "" : " -> ");
        }
        std::cout << std::endl;
    }

    std::cout << "\nTeste do Dijkstra concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}
void TestModule::testarGrafo_Modulo3_Coloring() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 3 - COLORACAO DE GRAFOS (Welch-Powell) ---\n";
    Graph mapaRegioes;
    
    mapaRegioes.addVertex("Norte");
    mapaRegioes.addVertex("Sul");
    mapaRegioes.addVertex("Leste");
    mapaRegioes.addVertex("Oeste");
    mapaRegioes.addVertex("Centro");
    mapaRegioes.addEdge("Centro", "Norte", 1, false);
    mapaRegioes.addEdge("Centro", "Sul", 1, false);
    mapaRegioes.addEdge("Centro", "Leste", 1, false);
    mapaRegioes.addEdge("Centro", "Oeste", 1, false);
    mapaRegioes.addEdge("Leste", "Norte", 1, false);
    mapaRegioes.addEdge("Leste", "Sul", 1, false);
    mapaRegioes.addEdge("Oeste", "Norte", 1, false);
    mapaRegioes.addEdge("Oeste", "Sul", 1, false);

    std::cout << "\nGrafo de regioes e suas fronteiras criado:\n";
    mapaRegioes.printAdjList();

    std::cout << "\nExecutando o algoritmo de coloracao de Welch-Powell...\n";
    std::map<std::string, int> cores = mapaRegioes.welchPowellColoring();

    std::cout << "Resultado da Coloracao:\n";
    for (const auto& par : cores) {
        std::cout << "  - Regiao: " << std::left << std::setw(10) << par.first 
                  << " \tCor: " << par.second << std::endl;
    }

    std::cout << "\nTeste da Coloracao concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::testarGrafo_Modulo3_TopoSort() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 3 - ORDENACAO TOPOLOGICA (Kahn's) ---\n";
    
    std::cout << "\n--- Teste 1: Arvore de Habilidades (Grafo Valido) ---\n";
    Graph skillTree;
    skillTree.addVertex("Armadura de Couro");
    skillTree.addVertex("Armadura de Ferro");
    skillTree.addVertex("Armadura de Aco");
    skillTree.addVertex("Espada de Bronze");
    skillTree.addVertex("Espada de Ferro");
    skillTree.addVertex("Pocao de Cura");
    skillTree.addEdge("Armadura de Couro", "Armadura de Ferro", 1);
    skillTree.addEdge("Armadura de Ferro", "Armadura de Aco", 1);
    skillTree.addEdge("Espada de Bronze", "Espada de Ferro", 1);
    skillTree.addEdge("Espada de Ferro", "Armadura de Aco", 1);
    std::cout << "\nGrafo de pré-requisitos de habilidades criado:\n";
    skillTree.printAdjList();
    std::cout << "\nExecutando a Ordenacao Topologica...\n";
    std::vector<std::string> ordem = skillTree.topologicalSort();
    std::cout << "Ordem de pesquisa de habilidades sugerida:\n";
    for (const auto& habilidade : ordem) {
        std::cout << habilidade << " -> ";
    }
    std::cout << "FIM\n";
    std::cout << "\n\n--- Teste 2: Grafo com Ciclo (Invalido) ---\n";
    Graph cyclicGraph;
    cyclicGraph.addVertex("Missao A");
    cyclicGraph.addVertex("Missao B");
    cyclicGraph.addVertex("Missao C");
    cyclicGraph.addEdge("Missao A", "Missao B", 1);
    cyclicGraph.addEdge("Missao B", "Missao C", 1);
    cyclicGraph.addEdge("Missao C", "Missao A", 1);
    std::cout << "\nGrafo de missões com ciclo criado:\n";
    cyclicGraph.printAdjList();
    std::cout << "\nExecutando a Ordenacao Topologica (deve falhar)...\n";
    cyclicGraph.topologicalSort();
    std::cout << "\nTeste da Ordenacao Topologica concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::testarGrafo_Modulo3_MST() {
    std::cout << "\n\n--- DEMONSTRACAO: MODULO 3 - ARVORE GERADORA MINIMA (Kruskal) ---\n";
    Graph redeCidades;
    redeCidades.addVertex("A"); redeCidades.addVertex("B"); redeCidades.addVertex("C");
    redeCidades.addVertex("D"); redeCidades.addVertex("E");

    // Arestas não-direcionadas com custos variados
    redeCidades.addEdge("A", "B", 1, false);
    redeCidades.addEdge("A", "C", 5, false);
    redeCidades.addEdge("B", "C", 4, false);
    redeCidades.addEdge("B", "D", 6, false);
    redeCidades.addEdge("C", "D", 2, false);
    redeCidades.addEdge("D", "E", 3, false);
    
    std::cout << "\nRede de cidades original com custos de estrada:\n";
    redeCidades.printAdjList();

    std::cout << "\nCalculando a Arvore Geradora Minima (rede de custo minimo)...\n";
    Graph mst = redeCidades.kruskalMST();

    std::cout << "\nEstradas a serem construidas para a rede de custo minimo:\n";
    mst.printAdjList();

    std::cout << "\nTeste da MST concluído. Pressione Enter para voltar ao menu...";
    if (std::cin.peek() == '\n') std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void TestModule::runAllTests() {
    int opcao;
    
    do {
        if (std::cin.peek() == '\n') {
            std::cin.ignore();
        }
        std::cout << "\n==================== MENU DE TESTES DE ALGORITMOS ====================\n";
        std::cout << "1. Demonstracao de Busca Sequencial\n";
        std::cout << "2. Demonstracao de Busca Binaria\n";
        std::cout << "3. Demonstracao de Busca Rabin-Karp\n";
        std::cout << "4. Demonstracao de Hashing por Dobramento\n";
        std::cout << "5. Demonstracao de Compressao Huffman\n";
        std::cout << "6. Demonstracao de Grafos (Modulo 1)\n";
        std::cout << "7. Demonstracao de Grafos (Modulo 2 - DFS)\n";
        std::cout << "8. Demonstracao de Grafos (Modulo 2 - BFS)\n";
        std::cout << "9. Demonstracao de Grafos (Modulo 2 - Dijkstra)\n";
        std::cout << "10. Demonstracao de Grafos (Modulo 3 - Coloracao)\n";
        std::cout << "11. Demonstracao de Grafos (Modulo 3 - Ord. Topologica)\n";
        std::cout << "12. Demonstracao de Grafos (Modulo 3 - MST Kruskal)\n";
        std::cout << "13. Editor de Grafo (criar/alterar/remover/visualizar)\n";
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
            case 6: testarGrafo_Modulo1(); break;
            case 7: testarGrafo_Modulo2_DFS(); break;
            case 8: testarGrafo_Modulo2_BFS(); break;
            case 9: testarGrafo_Modulo2_Dijkstra(); break;
            case 10: testarGrafo_Modulo3_Coloring(); break;
            case 11: testarGrafo_Modulo3_TopoSort(); break;
            case 12: testarGrafo_Modulo3_MST(); break;
            case 13: editorDeGrafo(); break;
            case 0: std::cout << "Retornando ao menu principal...\n"; break;
            default: std::cout << "Opcao invalida. Tente novamente.\n"; break;

        }
    } while (opcao != 0);
}
