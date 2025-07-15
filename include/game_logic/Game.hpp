#pragma once

#include "Player.hpp"
#include "Inimigo.hpp"
#include <vector>

// Enum para controlar o estado principal do jogo
enum class GameState {
    IN_COMBAT,
    GAME_OVER_VICTORY,
    GAME_OVER_DEFEAT
};

class Game {
public:
    Game();
    ~Game();

    // Inicia o loop do jogo
    void run();

private:
    // O loop principal do jogo
    void gameLoop();

    // Funções chamadas a cada ciclo do loop
    void processInput(); // Processa a entrada do jogador (ex: escolher uma carta)
    void update();       // Atualiza a lógica (ex: turno do inimigo)
    void render();       // "Desenha" o estado atual do jogo no console

    // Membros da classe
    bool isRunning;
    GameState currentState;
    
    Player* player;
    Inimigo* currentEnemy;
};