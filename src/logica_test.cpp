#include "../include/game_logic/Game.hpp"
#include <iostream>

// Este main é dedicado apenas para testar a lógica central do jogo.
int main() {
    std::cout << "--- INICIANDO TESTE DE LOGICA DE JOGO ---\n";

    // Cria o objeto do jogo. O construtor deve fazer todo o setup.
    Game jogo;

    // Roda o loop principal do jogo. A primeira coisa que ele faz
    // é preparar o turno inicial do jogador.
    jogo.run();

    std::cout << "\n--- FIM DO TESTE DE LOGICA DE JOGO ---\n";
    return 0;
}