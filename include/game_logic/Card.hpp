#pragma once

#include <string>

// A definição do TIPO de efeito deve vir ANTES da classe que o utiliza.
enum class TipoEfeito {
     DANO,
    DEFESA,
    CURA,
    COMPRA_CARTA,
    GERA_MANA 
};

class Card {
public:
    // Construtor: cria uma carta com seus atributos básicos
    // O custo é a "energia" necessária para jogar a carta.
    Card(const std::string& name, const std::string& description, int cost, TipoEfeito tipo, int valor);

    std::string getName() const;
    std::string getDescription() const;
    int getCost() const;

    TipoEfeito getTipo() const;
    int getValor() const;

    // Método para exibir a carta no console
    void display() const;

private:
    std::string name;
    std::string description;
    int cost;
    
    // Novos atributos que definem o poder da carta
    TipoEfeito tipo;
    int valor;
};