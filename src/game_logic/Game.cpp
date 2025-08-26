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
    CardLibrary library;
    
    // 1. Cria o jogador
    player = new Player(80, 3, library.getStartingDeck());
    
    // 2. Cria e gera o mapa
    stageMap = new StageMap();
    stageMap->generateMap(); // Gera um mapa com profundidade 15

    // 3. O jogo agora começa na tela do mapa
    currentState = GameState::MAP_VIEW;
    currentEnemy = nullptr; // Nenhum inimigo no início
}

Game::~Game() {
    delete player;
    delete currentEnemy;
    delete stageMap; // Libera a memória do mapa
    std::cout << "Jogo finalizado e memoria principal liberada.\n";
}

// --- Métodos Principais do Jogo ---
void Game::run() {
    std::cout << "\n--- INICIANDO JOGO: ARCH ARCANUM ---\n";
    gameLoop();
} 

void Game::gameLoop() {
    while (isRunning) {
        render(); // Renderiza o estado atual (mapa ou combate)

        // Processa a entrada baseada no estado atual
        if (currentState == GameState::MAP_VIEW) {
            processMapInput();
        } else if (currentState == GameState::IN_COMBAT) {
            if (player->getTurnoAtivo()) {
                processInput(); // Turno do jogador
            } else {
                update(); // Turno do inimigo
            }
        } else if (currentState == GameState::POST_COMBAT_REWARD) {
            processRewardInput();
        }

        // Verifica as condições de transição de estado
        if (currentState == GameState::IN_COMBAT) {
             if (!player->estaVivo()) {
                currentState = GameState::GAME_OVER_DEFEAT;
                isRunning = false;
            } else if (currentEnemy && !currentEnemy->estaVivo()) {
                std::cout << Color::BOLD_GREEN << "Inimigo derrotado!" << Color::RESET << std::endl;
                delete currentEnemy;
                currentEnemy = nullptr;
                currentState = GameState::POST_COMBAT_REWARD;
                awardFragment();
            }
        }
    }
    render(); // Renderiza o estado final (tela de vitória/derrota)
}

void Game::processMapInput() {
    std::cout << "\n--- MAPA DA FASE ---\n";
    MapNode* currentNode = stageMap->getCurrentNode();
    std::cout << "Voce esta na sala " << currentNode->id << ". Tipo: " << (int)currentNode->type << " (Visitada: " << currentNode->visited << ")" << std::endl;

    std::vector<MapNode*> reachableNodes = stageMap->getReachableNodes();
    if (reachableNodes.empty()) {
        // Se o nó atual for o chefe, a vitória já foi determinada ao entrar na sala.
        // Se não for o chefe e não houver saídas, pode ser um bug na geração, mas aqui tratamos como vitória.
        std::cout << "Voce chegou ao fim da sua jornada! Parabens!\n";
        currentState = GameState::GAME_OVER_VICTORY;
        isRunning = false;
        // Pausa para o jogador ver a mensagem antes do loop terminar
        std::cout << "Pressione Enter para finalizar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
        return;
    }

    std::cout << "Escolha seu proximo destino:\n";
    for (size_t i = 0; i < reachableNodes.size(); ++i) {
        std::cout << i + 1 << ". Sala " << reachableNodes[i]->id << " (Tipo: " << (int)reachableNodes[i]->type << ")" << std::endl;
    }
    std::cout << ">> ";

    int choice;
    std::cin >> choice;

    // Tratamento de input inválido
    if (std::cin.fail() || choice <= 0 || choice > reachableNodes.size()) {
        std::cout << "Escolha invalida. Tente novamente.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Pausa para o jogador ver a mensagem de erro
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    MapNode* destination = reachableNodes[choice - 1];
    stageMap->travelToNode(destination->id);
    
    // Lógica para iniciar o evento da sala
    switch (destination->type) {
        case NodeType::COMBATE:
            std::cout << "\nUm inimigo aparece!\n";
            currentEnemy = new Inimigo("Goblin Batedor", 50, TipoInimigo::GOBLIN);
            currentState = GameState::IN_COMBAT;
            currentEnemy->planejarAcao();
            player->iniciarNovoTurno();
            break;

        case NodeType::FOGUEIRA_REPOUSO:
            std::cout << "\nVoce encontra uma fogueira crepitante. Voce decide descansar.\n";
            player->curar(30);
            std::cout << "Pressione Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cin.get();
            currentState = GameState::MAP_VIEW; 
            break;

        case NodeType::CHEFE:
            std::cout << "\nO CHEFE FINAL! Prepare-se!\n";
            currentEnemy = new Inimigo("Golem de Runa Colossal", 150, TipoInimigo::GOLEM_RUNICO);
            currentState = GameState::IN_COMBAT;
            currentEnemy->planejarAcao();
            player->iniciarNovoTurno();
            break;
        // TODO: Adicionar lógica para outros tipos de sala (Mercador, etc.)
        default:
            std::cout << "Voce entra na sala, mas ela ainda esta vazia...\n";
            currentState = GameState::MAP_VIEW;
            std::cout << "Pressione Enter para continuar...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
    }
}

void Game::render() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    std::cout << "================== ARCH ARCANUM ==================\n";
    if (currentState == GameState::IN_COMBAT && currentEnemy) {
        currentEnemy->mostrarStatus();
        std::cout << "--------------------------------------------------\n";
        player->mostrarStatus();
        player->mostrarMao();
    } else if (currentState == GameState::MAP_VIEW) {
        stageMap->displayConsoleMap();
    } else if (currentState == GameState::POST_COMBAT_REWARD) {
        std::cout << "\nBatalha vencida! Escolha sua recompensa.\n";
        player->mostrarFragmentos();
    } else if (currentState == GameState::GAME_OVER_VICTORY) {
        std::cout << "\n================ VITORIA! =================\n";
    } else if (currentState == GameState::GAME_OVER_DEFEAT) {
        std::cout << "\n================ DERROTA! =================\n";
    }
    std::cout << "==================================================\n";
}

void Game::processRewardInput() {
    std::cout << "\nComandos: 'purificar [numero]' ou 'continuar'\n>> ";
    std::string comando;
    std::cin >> comando;

    if (comando == "purificar") {
        int indice;
        std::cin >> indice;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Entrada invalida.\n";
            return;
        }
        purificarFragmento(indice);
        // Após purificar, o estado continua em recompensa até o jogador 'continuar'
    } else if (comando == "continuar") {
        std::cout << "Voce retorna ao mapa...\n";
        currentState = GameState::MAP_VIEW; // VOLTA PARA O MAPA!
        std::cout << "Pressione Enter para continuar...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();
    } else {
        std::cout << "Comando invalido.\n";
    }
}

void Game::processInput() {
    std::cout << "\n--- SEU TURNO --- (Comandos: jogar [nome], passar, analisar, verificar, desistir)\n>> ";
    std::string input;
    if (std::cin.peek() == '\n') std::cin.ignore();
    std::getline(std::cin, input);

    if (input == "passar" || input == "f") {
        player->finalizarTurno();
        player->setTurnoAtivo(false);
    } else if (input == "desistir" || input == "menu") {
        isRunning = false;
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
    if (currentEnemy) {
        currentEnemy->realizarAcao(*player);
        currentEnemy->planejarAcao();
    }
    player->iniciarNovoTurno();
    player->setTurnoAtivo(true);
}

void Game::awardFragment() {
    std::cout << "\n" << Color::BOLD_YELLOW << "O inimigo deixou cair um Fragmento Etereo!" << Color::RESET << "\n";
    FragmentoEtereo recompensa;
    recompensa.nome = "Fragmento Raro de Poder";
    recompensa.dadosSecretos = "Lanca do Vazio";
    player->adicionarFragmento(recompensa);
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