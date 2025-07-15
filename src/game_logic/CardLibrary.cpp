#include "../../include/game_logic/CardLibrary.hpp"
#include <iostream>

CardLibrary::CardLibrary() {
    // Populamos nossa biblioteca com "modelos" de todas as cartas do jogo aqui.
    // Isso centraliza a criação de cartas em um único lugar.

    // Ataques
    cardTemplates.insert({"Raio Etereo", Card("Raio Etereo", "Causa 6 de dano.", 1, TipoEfeito::DANO, 6)});
    cardTemplates.insert({"Lanca do Vazio", Card("Lanca do Vazio", "Causa 20 de dano.", 3, TipoEfeito::DANO, 20)});

    // Defesas
    cardTemplates.insert({"Barreira Runica", Card("Barreira Runica", "Ganha 7 de armadura.", 1, TipoEfeito::DEFESA, 7)});
    cardTemplates.insert({"Manto Espectral", Card("Manto Espectral", "Ganha 10 de armadura.", 2, TipoEfeito::DEFESA, 10)});

    // Utilidade
    cardTemplates.insert({"Toque Curativo", Card("Toque Curativo", "Cura 7 de vida.", 2, TipoEfeito::CURA, 7)});
    cardTemplates.insert({"Clarividencia", Card("Clarividencia", "Compra 2 cartas.", 1, TipoEfeito::COMPRA_CARTA, 2)});
    cardTemplates.insert({"Focar Mana", Card("Focar Mana", "Ganha 2 de Essencia.", 0, TipoEfeito::GERA_MANA, 2)});
}

// Cria uma NOVA instância de uma carta baseada no modelo
Card* CardLibrary::createCard(const std::string& cardName) {
    auto it = cardTemplates.find(cardName);
    if (it != cardTemplates.end()) {
        return new Card(it->second);
    }
    std::cerr << "AVISO: Carta com o nome '" << cardName << "' nao encontrada na biblioteca!\n";
    return nullptr;
}

// Retorna um vetor de ponteiros para novas cartas para o deck inicial do jogador
std::vector<Card*> CardLibrary::getStartingDeck() {
    std::vector<Card*> startingDeck;
    // Um baralho inicial balanceado
    startingDeck.push_back(createCard("Raio Etereo"));
    startingDeck.push_back(createCard("Raio Etereo"));
    startingDeck.push_back(createCard("Raio Etereo"));
    startingDeck.push_back(createCard("Barreira Runica"));
    startingDeck.push_back(createCard("Barreira Runica"));
    startingDeck.push_back(createCard("Clarividencia"));

    std::cout << "[DEBUG LIB] getStartingDeck esta retornando um deck com " << startingDeck.size() << " cartas.\n";

    return startingDeck;
}