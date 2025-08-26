#include "../include/game_logic/Game.hpp"
#include <iostream>

int main() {
    std::cout << "--- INICIANDO TESTE DE LOGICA DE JOGO ---\n";
    Game jogo;
    jogo.run();
    std::cout << "\n--- FIM DO TESTE DE LOGICA DE JOGO ---\n";
    return 0;
}