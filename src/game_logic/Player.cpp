#include "../../include/game_logic/Player.hpp"
#include "../../include/game_logic/Inimigo.hpp" // Necessário para a função jogarCarta
#include "../../include/Utils/Color.hpp" // Para cores no console
#include <iostream>
#include <algorithm> // Para std::shuffle e std::find
#include <random>    // Para o motor de aleatoriedade
#include <chrono>    // Para a semente (seed) do tempo

// --- Construtor ---
Player::Player(int vidaInicial, int essenciaInicial, std::vector<Card*> deckInicial) {
    this->vida = vidaInicial;
    this->vidaMaxima = vidaInicial;
    this->essenciaArcana = essenciaInicial;
    this->armadura = 0;
    this->deck = deckInicial;
    this->meuTurno = true; 
    std::cout << "[DEBUG PLAYER] Construtor recebeu e armazenou um deck com " << this->deck.size() << " cartas.\n";
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->deck.begin(), this->deck.end(), std::default_random_engine(seed));
    
}

// --- Destrutor ---
Player::~Player() {
    std::cout << "\n[DEBUG] Destrutor do Player chamado. Limpando memoria das cartas...\n";
    for (Card* carta : deck) { delete carta; }
    for (Card* carta : mao) { delete carta; }
    for (Card* carta : descarte) { delete carta; }
}

// --- Métodos de Lógica de Jogo ---

int Player::getDeckSize() const { return deck.size(); }

void Player::receberDano(int quantidade) {
    int danoAAplicarNaVida = quantidade - this->armadura;
    this->armadura -= quantidade;
    if (this->armadura < 0) {
        this->armadura = 0;
    }
    
    if (danoAAplicarNaVida > 0) {
        this->vida -= danoAAplicarNaVida;
    }

    std::cout << "O Jogador recebeu " << quantidade << " de dano, vida restante: " << this->vida << "\n";
    
    if (this->vida < 0) {
        this->vida = 0;
    }
}

void Player::comprarCarta() {
    if (mao.size() >= 10) {
        std::cout << "Mao cheia. Impossivel comprar mais cartas.\n";
        return;
    }

    if (deck.empty()) {
        if (descarte.empty()) {
            std::cout << "Nao ha cartas no deck nem no descarte. Impossivel comprar.\n";
            return;
        }
        std::cout << "O deck esta vazio. Embaralhando o descarte para criar um novo deck...\n";
        deck = descarte;
        descarte.clear();

        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    }

    if (!deck.empty()) {
        Card* cartaComprada = deck.back(); 
        mao.push_back(cartaComprada);
        deck.pop_back();
        std::cout << "Voce comprou a carta: " << cartaComprada->getName() << "\n";
    }
}

void Player::jogarCarta(Card* cartaSendoJogada, Inimigo& alvo) {
    // 1. Encontrar o iterador para a carta na mão para poder removê-la
    auto it = std::find(mao.begin(), mao.end(), cartaSendoJogada);
    if (it == mao.end()) {
        std::cout << "Erro: Tentativa de jogar uma carta que nao esta na mao.\n";
        return;
    }

    // 2. Verificar e pagar o custo de mana
    if (this->essenciaArcana < cartaSendoJogada->getCost()) {
        std::cout << "Essencia Arcana insuficiente para jogar " << cartaSendoJogada->getName() << "!\n";
        return;
    }
    this->essenciaArcana -= cartaSendoJogada->getCost();
    std::cout << "Jogador jogou '" << cartaSendoJogada->getName() << "'!\n";

    descarte.push_back(cartaSendoJogada);
    mao.erase(it);

    switch (cartaSendoJogada->getTipo()) {
        case TipoEfeito::DANO:
            alvo.receberDano(cartaSendoJogada->getValor());
            break;
        case TipoEfeito::DEFESA:
            this->ganharArmadura(cartaSendoJogada->getValor());
            break;
        case TipoEfeito::CURA:
            this->vida += cartaSendoJogada->getValor();
            if (this->vida > this->vidaMaxima) this->vida = this->vidaMaxima;
            std::cout << "Jogador se curou em " << cartaSendoJogada->getValor() << ".\n";
            break;
        case TipoEfeito::COMPRA_CARTA:
            std::cout << "Jogador compra " << cartaSendoJogada->getValor() << " cartas.\n";
            for (int i = 0; i < cartaSendoJogada->getValor(); ++i) {
                this->comprarCarta(); // Esta chamada agora é segura.
            }
            break;
        case TipoEfeito::GERA_MANA:
            this->essenciaArcana += cartaSendoJogada->getValor();
            std::cout << "Jogador ganhou " << cartaSendoJogada->getValor() << " de Essencia Arcana.\n";
            break;
    }
}


void Player::finalizarTurno() {
    descarte.insert(descarte.end(), mao.begin(), mao.end());
    mao.clear();
    std::cout << "Finalizando o turno do jogador... Mao descartada.\n";
}

void Player::iniciarNovoTurno() {
    this->armadura = 0;
    this->essenciaArcana = 3; 
    std::cout << "\nIniciando novo turno. Armadura resetada. Mana resetada para 3.\n";
    
    for(int i = 0; i < 5; ++i) {
        comprarCarta();
    }
}

void Player::ganharArmadura(int quantidade) {
    this->armadura += quantidade;
    std::cout << "Jogador ganhou " << quantidade << " de armadura! Total: " << this->armadura << "\n";
}

// --- Métodos de Exibição e Consulta (Getters) ---
void Player::mostrarMao() const {
    std::cout << "\n--- MAO DO JOGADOR ---\n";
    if (mao.empty()) {
        std::cout << "Mao vazia.\n";
    } else {
        for (size_t i = 0; i < mao.size(); ++i) {
            std::cout << "[" << i << "] ";
            mao[i]->display();
        }
    }
    std::cout << "-----------------------\n";
}

void Player::mostrarStatus() const {
    std::cout << "Vida: " << Color::GREEN << vida << "/" << vidaMaxima << Color::RESET
              << " | Armadura: " << Color::BOLD_BLUE << armadura << Color::RESET
              << " | Essencia: " << Color::BOLD_MAGENTA << essenciaArcana << Color::RESET << "\n";
    std::cout << "Cartas no Deck: " << deck.size() << " | Cartas no Descarte: " << descarte.size() << "\n";
}
bool Player::estaVivo() const { return this->vida > 0; }
const std::vector<Card*>& Player::getMao() const { return this->mao; }
void Player::setTurnoAtivo(bool estado) { this->meuTurno = estado; }
bool Player::getTurnoAtivo() const { return this->meuTurno; }