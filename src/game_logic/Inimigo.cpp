#include "../../include/game_logic/Inimigo.hpp"
#include "../../include/game_logic/Player.hpp" 
#include <iostream>

Inimigo::Inimigo(const std::string& nome, int vidaInicial, TipoInimigo tipo) {
    this->nome = nome;
    this->vida = vidaInicial;
    this->vidaMaxima = vidaInicial;
    this->tipo = tipo;
    this->danoDaProximaAcao = 0;
    this->seloAtivo = true;

    // Configurações específicas para cada tipo de inimigo
    switch (this->tipo) {
        case TipoInimigo::GOBLIN:
            // O Goblin é fraco contra ataques de DANO normais.
            this->seloDefensivo = TipoEfeito::DANO;
            break;
         case TipoInimigo::GOLEM_RUNICO:
        // A fraqueza do Golem agora são cartas de DEFESA
        this->seloDefensivo = TipoEfeito::DEFESA;
        break;
}
}

void Inimigo::planejarAcao() {
    switch (this->tipo) {
        case TipoInimigo::GOBLIN:
            // O Goblin sempre planeja um ataque simples.
            this->danoDaProximaAcao = 8;
            break;
        case TipoInimigo::GOLEM_RUNICO:
            // O Golem tem um ataque mais forte.
            this->danoDaProximaAcao = 15;
            break;
    }
    std::cout << "'" << this->nome << "' planeja sua proxima acao...\n";
}

void Inimigo::receberDano(int quantidade) {
    int danoReal = quantidade;
    if (this->seloAtivo) {
        danoReal /= 2;
        std::cout << "O selo absorveu parte do impacto!\n";
    }
    this->vida -= danoReal;
    
    if (this->vida < 0) {
        this->vida = 0;
    }
    std::cout << "'" << this->nome << "' recebeu " << danoReal << " de dano! (Vida restante: " << this->vida << ")\n";
}

void Inimigo::quebrarSelo() {
    if (this->seloAtivo) {
        std::cout << "'" << this->nome << "' teve seu selo quebrado e esta vulneravel!\n";
        this->seloAtivo = false;
    }
}

void Inimigo::realizarAcao(Player& alvo) {
    std::cout << "'" << this->nome << "' ataca o jogador!\n";
    alvo.receberDano(this->danoDaProximaAcao);
}

void Inimigo::mostrarStatus() const {
    std::cout << "\n--- STATUS DO INIMIGO (" << this->nome << ") ---\n";
    std::cout << "Vida: " << this->vida << "/" << this->vidaMaxima << "\n";
    if (this->seloAtivo) {
        std::cout << "Selo Ativo: Sim\n";
    }
    std::cout << "--------------------------------------\n";
}

std::string Inimigo::getNome() const { return nome; }
int Inimigo::getVida() const { return vida; } 
int Inimigo::getVidaMaxima() const { return vidaMaxima; }
int Inimigo::getDanoIntencao() const { return danoDaProximaAcao; }
bool Inimigo::estaVivo() const { return this->vida > 0; }
bool Inimigo::getSeloAtivo() const { return seloAtivo; }
TipoEfeito Inimigo::getSeloDefensivo() const { return seloDefensivo; }