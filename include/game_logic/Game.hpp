#pragma once

#include "Player.hpp"
#include "Inimigo.hpp"
#include <vector>

// Enum para controlar o estado principal do jogo
enum class GameState {
    IN_COMBAT,
    POST_COMBAT,
    GAME_OVER_VICTORY,
    GAME_OVER_DEFEAT
};

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void gameLoop();
    void processCombatInput();
    void updateCombat();
    // Funções chamadas a cada ciclo do loop
    void processInput(); 
    void update();       
    void render();       
    void processRewardInput();
    void awardFragment();
    void purificarFragmento(int indice);
    // Membros da classe
    bool isRunning;
    GameState currentState;
    
    Player* player;
    Inimigo* currentEnemy;
};