#pragma once

#include <string>
#include "Card.hpp" 

enum class TipoInimigo {
    GOBLIN,
    GOLEM_RUNICO
};

class Player;

class Inimigo {
public:
    Inimigo(const std::string& nome, int vidaInicial, TipoInimigo tipo);
    void receberDano(int quantidade);
    void mostrarStatus() const;
    void planejarAcao();
    void realizarAcao(Player& alvo);
    void quebrarSelo();
    std::string getNome() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getDanoIntencao() const;
    bool estaVivo() const;
    bool getSeloAtivo() const; 
    TipoEfeito getSeloDefensivo() const; 

private:
    std::string nome;
    int vida;
    int vidaMaxima;
    int danoDaProximaAcao;
    TipoInimigo tipo; 
    TipoEfeito seloDefensivo;
    bool seloAtivo;
};