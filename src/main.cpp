#include <iostream>
#include <limits>
#include <vector> 
#include "../include/TestesModule.hpp"
#include "../include/game_logic/Game.hpp"

void showMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "               ARCH ARCANUM               \n";
    std::cout << "=========================================\n";
    std::cout << "Selecione uma opcao:\n";
    std::cout << "1. Iniciar combate\n";
    std::cout << "2. Executar Testes de Algoritmos\n";
    std::cout << "0. Sair\n";
    std::cout << ">> ";
}

int main() {
    int choice = -1;
    while (choice != 0) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, insira um numero.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
            {
                Game jogo;
                jogo.run();
                break;
            }
            case 2:
                TestModule::runAllTests();
                break;

            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opcao invalida. Tente novamente.\n";
                break;
        }
    }

    return 0;
}
