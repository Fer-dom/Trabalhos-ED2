#include "../../include/game_logic/Card.hpp"
#include <iostream>

Card::Card(const std::string& name, const std::string& description, int cost, TipoEfeito tipo, int valor) {
    this->name = name; 
    this->description = description;
    this->cost = cost;
    this->tipo = tipo; 
    this->valor = valor; 

    std::cout << "[DEBUG CARD] Criada: '" << name << "', Tipo: " << static_cast<int>(tipo) << ", Valor: " << valor << std::endl;
}


std::string Card::getName() const { return this->name; }
std::string Card::getDescription() const { return this->description; }
int Card::getCost() const { return this->cost; }
TipoEfeito Card::getTipo() const { return this->tipo; }
int Card::getValor() const { return this->valor; }


void Card::display() const {
    // Exibe os detalhes da carta no console
    std::cout << "--- " << this->name << " (Custo: " << this->cost << ") ---\n";
    std::cout << "    " << this->description << " (Valor: " << this->valor << ")\n";
}