#include "../../include/game_logic/Game.hpp"
#include "../../include/game_logic/CardLibrary.hpp" // Incluindo a biblioteca de cartas
#include "../../include/algoritmos/Busca.hpp"   // Incluindo os algoritmos de busca
#include <iostream>
#include <string>
#include <limits> 
#include <algorithm>

// --- Construtor e Destrutor ---

Game::Game() {
    // Inicializa o estado do jogo
    isRunning = true;
    currentState = GameState::IN_COMBAT;

    // --- CRIANDO O DECK DIRETAMENTE, SEM A BIBLIOTECA ---
    std::cout << "[DEBUG] Criando deck diretamente no construtor do Game...\n";
    std::vector<Card*> startingDeck;
    startingDeck.push_back(new Card("Golpe com Espada", "Causa 8 de dano.", 1, TipoEfeito::DANO, 8));
    startingDeck.push_back(new Card("Aparar", "Ganha 6 de armadura.", 1, TipoEfeito::DEFESA, 6));
    startingDeck.push_back(new Card("Clarividencia", "Compra 2 cartas.", 1, TipoEfeito::COMPRA_CARTA, 2));
    startingDeck.push_back(new Card("Raio Etereo", "Causa 6 de dano.", 1, TipoEfeito::DANO, 6));
    startingDeck.push_back(new Card("Barreira Runica", "Ganha 7 de armadura.", 1, TipoEfeito::DEFESA, 7));

    // Criamos o jogador com este deck criado localmente
    player = new Player(80, 3, startingDeck); // Vida, Mana, Deck
    currentEnemy = new Inimigo("Goblin Batedor", 50); // Nome, Vida

    // Limpa qualquer entrada pendente no buffer do cin
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Game::~Game() {
    // A classe Game é "dona" do player e do inimigo, então ela os deleta.
    delete player;
    delete currentEnemy;
    std::cout << "[DEBUG] Jogo finalizado e memoria principal liberada.\n";
}

// --- Métodos Principais do Jogo ---
// O método run inicia o loop principal do jogo.

void Game::run() {
    std::cout << "\n--- INICIANDO JOGO: ARCH ARCANUM ---\n";
    std::cout << "Um " << currentEnemy->getNome() << " selvagem aparece!\n";

    // Prepara o primeiro turno do jogo
    currentEnemy->planejarAcao();
     std::cout << "[DEBUG GAME] Antes de comprar a mao, o deck do jogador tem " << player->getDeckSize() << " cartas.\n";
    player->iniciarNovoTurno();

    gameLoop();
}

void Game::gameLoop() {
    while (isRunning) {
        render(); 

        if (player->getTurnoAtivo()) {
            processInput(); 
        } else {
            update(); 
        }

        // Verifica se o jogo terminou
        if (!player->estaVivo()) {
            currentState = GameState::GAME_OVER_DEFEAT;
            isRunning = false;
        } else if (!currentEnemy->estaVivo()) {
            currentState = GameState::GAME_OVER_VICTORY;
            isRunning = false;
        }
    }

    // Mostra a tela de fim de jogo
    render(); // Mostra o estado final uma última vez
    if (currentState == GameState::GAME_OVER_VICTORY) {
        std::cout << "\n================ VITORIA! =================\n";
        std::cout << "Voce derrotou o " << currentEnemy->getNome() << "!\n";
    } else if (currentState == GameState::GAME_OVER_DEFEAT) {
        std::cout << "\n================ DERROTA! =================\n";
        std::cout << "Voce foi derrotado pelo " << currentEnemy->getNome() << ".\n";
    }
}

void Game::processInput() {
    std::cout << "\n--- SEU TURNO --- (Digite o nome da carta, 'passar', 'analisar', 'verificar' ou 'desistir')\n>> ";
    
    std::string input;
    std::getline(std::cin, input);

    // --- LÓGICA PARA COMANDOS ESPECIAIS ---

    if (input == "passar" || input == "finalizar" || input == "f") {
        player->finalizarTurno();
        player->setTurnoAtivo(false); // Passa o turno para o inimigo
        return;
    }

    if (input == "desistir" || input == "menu" || input == "sair") {
        std::cout << "Voce desistiu do combate.\n";
        isRunning = false; // <<< ISTO QUEBRA O LOOP DO JOGO
        return;
    }

    // --- DEMONSTRAÇÃO DA BUSCA RABIN-KARP ---
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

    // --- DEMONSTRAÇÃO DA BUSCA BINÁRIA ---
    if (input == "verificar") {
        std::cout << "Verificar se uma carta existe no Grimorio completo do jogo.\n";
        std::cout << "Digite o nome da carta a verificar:\n>> ";
        std::string nomeCarta;
        std::getline(std::cin, nomeCarta);

        // Criamos uma "biblioteca mestra" de exemplo para o teste
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

        // Limpeza da memória do grimorio de teste
        for(auto c : grimorioCompleto) delete c;

        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
        return;
    }

    // --- LÓGICA PADRÃO: JOGAR UMA CARTA (BUSCA SEQUENCIAL) ---
    Card* carta = Algoritmos::buscaSequencial(player->getMao(), input);

    if (carta != nullptr) {
        player->jogarCarta(carta, *currentEnemy);
    } else {
        std::cout << "Comando ou nome de carta invalido.\n";
        std::cout << "Pressione Enter para continuar...";
        std::cin.get();
    }
}

void Game::update() {
    // Turno do Inimigo
    std::cout << "\n--- TURNO DO INIMIGO ---\n";
    currentEnemy->realizarAcao(*player);
    
    // Prepara o próximo turno do jogador e do inimigo
    currentEnemy->planejarAcao(); 
    player->iniciarNovoTurno();
    player->setTurnoAtivo(true); // Devolve o turno para o jogador
}

void Game::render() {
    // Truque para "limpar" a tela do console
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