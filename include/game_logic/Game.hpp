#pragma once

#include "Player.hpp"
#include "Inimigo.hpp"
#include "StageMap.hpp"
#include <vector>

enum class GameState {
    MAP_VIEW,         
    IN_COMBAT,
    POST_COMBAT_REWARD, 
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
    void processInput(); 
    void update();       
    void render();       
    void processMapInput();
    void processRewardInput();
    void awardFragment();
    void purificarFragmento(int indice);
    bool isRunning;
    GameState currentState;
    
    Player* player;
    Inimigo* currentEnemy;
    StageMap* stageMap;
};