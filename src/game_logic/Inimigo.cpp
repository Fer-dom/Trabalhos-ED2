#include "../../include/game_logic/Inimigo.hpp"
#include "../../include/game_logic/Player.hpp" 
#include "../../include/Utils/Color.hpp"
#include <string>
#include <iostream>

Inimigo::Inimigo(const std::string& nome, int vidaInicial) {
    this->nome = nome;
    this->vida = vidaInicial;
    this->vidaMaxima = vidaInicial;
    this->danoDaProximaAcao = 0; 
}

void Inimigo::receberDano(int quantidade) {
    std::cout << "[DEBUG INIMIGO] Funcao receberDano chamada com quantidade: " << quantidade << std::endl;
    this->vida -= quantidade;
    std::cout << "'" << this->nome << "' recebeu " << quantidade << " de dano, vida restante: " << this->vida << "\n";
    if (this->vida < 0) {
        this->vida = 0;
    }
}

void Inimigo::planejarAcao() {
    this->danoDaProximaAcao = 10;
    std::cout << "'" << this->nome << "' planeja atacar por " << this->danoDaProximaAcao << " de dano.\n";
}

void Inimigo::realizarAcao(Player& alvo) {
    std::cout << "'" << this->nome << "' ataca o jogador!\n";

    alvo.receberDano(this->danoDaProximaAcao);
    std::cout << "O jogador recebeu " << this->danoDaProximaAcao << " de dano.\n";
    this->danoDaProximaAcao = 0;
}

void Inimigo::mostrarStatus() const {
    std::cout << "Vida: " << Color::GREEN << this->vida << "/" << this->vidaMaxima << Color::RESET << "\n";
}

std::string Inimigo::getNome() const { return nome; }
int Inimigo::getVida() const { return vida; } 
int Inimigo::getVidaMaxima() const { return vidaMaxima; }
int Inimigo::getDanoIntencao() const { return danoDaProximaAcao; }

bool Inimigo::estaVivo() const {
    return this->vida > 0;
}