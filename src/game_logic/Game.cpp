#include "../../include/game_logic/Game.hpp"
#include "../../include/game_logic/CardLibrary.hpp" 
#include "../../include/algoritmos/Busca.hpp"   
#include "../../include/algoritmos/Huffman.hpp"
#include "../../include/utils/Color.hpp"
#include <iostream>
#include <string>
#include <limits> 
#include <algorithm>


// --- Construtor e Destrutor ---
Game::Game() {
    isRunning = true;
    currentState = GameState::IN_COMBAT;
    CardLibrary library;
    player = new Player(80, 3, library.getStartingDeck());
    currentEnemy = new Inimigo("Goblin Batedor", 50, TipoInimigo::GOBLIN);
    if (std::cin.peek() == '\n') std::cin.ignore();
}

Game::~Game() {
    delete player;
    delete currentEnemy;
    std::cout << "Jogo finalizado e memoria principal liberada.\n";
}

// --- Métodos Principais do Jogo ---
void Game::run() {
    std::cout << "\n--- INICIANDO JOGO: ARCH ARCANUM ---\n";
    std::cout << "Um " << currentEnemy->getNome() << " selvagem aparece!\n";
    currentEnemy->planejarAcao();
    player->iniciarNovoTurno();
    gameLoop();
} 

void Game::gameLoop() {
    while (isRunning) {
        if (currentState == GameState::IN_COMBAT) {
            render();
            if (player->getTurnoAtivo()) {
            
                processInput();
            } else {
                
                update();
            }
        } else if (currentState == GameState::POST_COMBAT) {
            processRewardInput();
        }

        if (currentState == GameState::IN_COMBAT) {
             if (!player->estaVivo()) {
                currentState = GameState::GAME_OVER_DEFEAT;
                isRunning = false;
            } else if (!currentEnemy->estaVivo()) {
                currentState = GameState::POST_COMBAT;
                awardFragment();
            }
        }
    }
    render();
    if (currentState == GameState::GAME_OVER_VICTORY) {
        std::cout << "\n================ VITORIA! =================\n";
    } else if (currentState == GameState::GAME_OVER_DEFEAT) {
        std::cout << "\n================ DERROTA! =================\n";
    }
}

void Game::processInput() {
    std::cout << "\n--- SEU TURNO --- (Comandos: jogar [nome], passar, analisar, verificar, desistir)\n>> ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "passar" || input == "f") {
        player->finalizarTurno();
        player->setTurnoAtivo(false);
    } else if (input == "desistir" || input == "menu") {
        isRunning = false;
    } else if (input == "analisar") {
        if (input == "analisar") {

            std::cout << "Qual carta da sua mao voce quer analisar?\n>> ";
            std::string nomeCarta;
            std::getline(std::cin, nomeCarta);
                Card* cartaParaAnalisar = Algoritmos::buscaSequencial(player->getMao(), nomeCarta);
                if(cartaParaAnalisar) {
                    std::cout << "Descricao da carta: \"" << cartaParaAnalisar->getDescription() << "\"\n";
                    std::cout << "Qual palavra-chave voce quer procurar na descricao?\n>> ";
                    std::string padrao;
                    std::getline(std::cin, padrao);
            Algoritmos::buscaRabinKarp(cartaParaAnalisar->getDescription(), padrao);
                } else {
                    std::cout << "Carta nao encontrada na sua mao.\n";
                        }
                std::cout << "Pressione Enter para continuar...";
                std::cin.get();
                return;
}
    } else if (input == "verificar") {
        if (input == "verificar") {
     std::cout << "Verificar se uma carta existe no Grimorio completo do jogo.\n";
     std::cout << "Digite o nome da carta a verificar:\n>> ";
     std::string nomeCarta;
     std::getline(std::cin, nomeCarta);

        //Biblioteca de cartas completa para a busca binária
     CardLibrary libCompleta;
     std::vector<Card*> grimorioCompleto;
    grimorioCompleto.push_back(libCompleta.createCard("Raio Etereo"));
    grimorioCompleto.push_back(libCompleta.createCard("Lanca do Vazio"));
    grimorioCompleto.push_back(libCompleta.createCard("Barreira Runica"));
    grimorioCompleto.push_back(libCompleta.createCard("Manto Espectral"));
    grimorioCompleto.push_back(libCompleta.createCard("Toque Curativo"));
    grimorioCompleto.push_back(libCompleta.createCard("Clarividencia"));
    grimorioCompleto.push_back(libCompleta.createCard("Focar Mana"));


        // A busca binária exige que a lista esteja ordenada
     std::sort(grimorioCompleto.begin(), grimorioCompleto.end(), [](Card* a, Card* b){ return a->getName() < b->getName(); });
     std::cout << "Procurando '" << nomeCarta << "' no grimorio completo...\n";
    Algoritmos::buscaBinaria(grimorioCompleto, nomeCarta);


        // Limpeza da memória do grimorio de test
    for(auto c : grimorioCompleto) delete c;
     std::cout << "Pressione Enter para continuar...";
    std::cin.get();
 return;

}
    } else {
        Card* carta = Algoritmos::buscaSequencial(player->getMao(), input);
        if (carta) {
            player->jogarCarta(carta, *currentEnemy);
        } else {
            std::cout << "Comando ou nome de carta invalido.\n";
        }
    }
}

void Game::update() {
    std::cout << "\n--- TURNO DO INIMIGO ---\n";
    currentEnemy->realizarAcao(*player);
    currentEnemy->planejarAcao();
    player->iniciarNovoTurno();
    player->setTurnoAtivo(true);
}

void Game::render() {
    // Truque para limpar a tela do console
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "================== ARCH ARCANUM ==================\n";
    currentEnemy->mostrarStatus();
    std::cout << "INTENCAO: Atacar por " << currentEnemy->getDanoIntencao() << " de dano.\n";
    std::cout << "--------------------------------------------------\n";
    player->mostrarStatus();
    player->mostrarMao();
    std::cout << "==================================================\n";
}

void Game::purificarFragmento(int indice) {
    if (indice < 0 || indice >= player->getFragmentos().size()) {
        std::cout << "Escolha invalida.\n";
        return;
    }

    FragmentoEtereo& fragmento = player->getFragmentos()[indice];
    std::cout << "Iniciando purificacao do " << fragmento.nome << "...\n";
    
    Algoritmos::HuffmanArchiver arquivador;
    std::string comprimido = arquivador.compress(fragmento.dadosSecretos);
    std::string revelado = arquivador.decompress(comprimido);
    std::cout << "Fragmento purificado! O segredo era: " << Color::BOLD_YELLOW << revelado << Color::RESET << "!\n";

    CardLibrary lib;
    Card* novaCarta = lib.createCard(revelado);
    if(novaCarta) {
        player->adicionarCartaAoDeck(novaCarta);
    }
    player->getFragmentos().erase(player->getFragmentos().begin() + indice);
}

void Game::awardFragment() {
    std::cout << "\n" << Color::BOLD_YELLOW << "O inimigo deixou cair um Fragmento Etereo!" << Color::RESET << "\n";
    FragmentoEtereo recompensa;
    recompensa.nome = "Fragmento Raro de Poder";
    recompensa.dadosSecretos = "Lanca do Vazio";
    player->adicionarFragmento(recompensa);
}

void Game::processRewardInput() {
    std::cout << "\n================== FORJA ARCANA ==================\n";
    std::cout << "Batalha vencida! Voce pode purificar um fragmento ou continuar sua jornada.\n";
    player->mostrarFragmentos();
    std::cout << "\nComandos: 'purificar [numero]' ou 'continuar'\n>> ";
    
    std::string comando;
    std::cin >> comando;

    if (comando == "purificar") {
        int indice;
        std::cin >> indice;
        purificarFragmento(indice);
        if (std::cin.peek() == '\n') std::cin.ignore();
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
    } else if (comando == "continuar") {
        std::cout << "Voce segue para o proximo desafio...\n";
        delete currentEnemy;
        currentEnemy = new Inimigo("Golem de Runa", 80, TipoInimigo::GOLEM_RUNICO);
        currentState = GameState::IN_COMBAT;
        currentEnemy->planejarAcao();
        player->iniciarNovoTurno();
        if (std::cin.peek() == '\n') std::cin.ignore();
    } else {
        std::cout << "Comando invalido.\n";
        if (std::cin.peek() == '\n') std::cin.ignore();
    }
}