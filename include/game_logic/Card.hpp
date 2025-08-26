#pragma once
#include <string>

enum class TipoEfeito {
     DANO,
    DEFESA,
    CURA,
    COMPRA_CARTA,
    GERA_MANA 
};

class Card {
public:
    Card(const std::string& name, const std::string& description, int cost, TipoEfeito tipo, int valor);
    std::string getName() const;
    std::string getDescription() const;
    int getCost() const;
    TipoEfeito getTipo() const;
    int getValor() const;
    void display() const;

private:
    std::string name;
    std::string description;
    int cost;
    
    TipoEfeito tipo;
    int valor;
};