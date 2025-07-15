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
    // ... (verificações de mana, etc., continuam iguais) ...

    this->essenciaArcana -= cartaSendoJogada->getCost();
    std::cout << "Jogador jogou '" << cartaSendoJogada->getName() << "'!\n";

    // --- NOVA LÓGICA DE QUEBRA DE SELO ---
    // Verificamos se o inimigo tem um selo ativo E se a fraqueza dele é do tipo DEFESA
    if (alvo.getSeloAtivo() && alvo.getSeloDefensivo() == TipoEfeito::DEFESA) {
        // Se for, verificamos se a carta que estamos jogando é de DEFESA
        if (cartaSendoJogada->getTipo() == TipoEfeito::DEFESA) {
            std::cout << Color::BOLD_YELLOW << "Suas runas defensivas sobrecarregam e quebram o selo do inimigo!\n" << Color::RESET;
            alvo.quebrarSelo(); // Quebra o selo
            alvo.receberDano(15); // Causa um dano extra de "feedback arcano"
            
            // Movemos a carta para o descarte e terminamos a ação aqui,
            // pois a carta foi "consumida" para quebrar o selo em vez de dar armadura.
            auto it = std::find(mao.begin(), mao.end(), cartaSendoJogada);
            if (it != mao.end()) {
                descarte.push_back(cartaSendoJogada);
                mao.erase(it);
            }
            return; // A ação da carta termina aqui.
        }
    }

    // Se a lógica de quebra de selo não foi ativada, o efeito normal da carta acontece
    // (O switch que você já tem)
    switch (cartaSendoJogada->getTipo()) {
        case TipoEfeito::DANO:
            alvo.receberDano(cartaSendoJogada->getValor());
            break;
        case TipoEfeito::DEFESA:
            // Se chegamos aqui, significa que a carta de defesa foi usada normalmente (não para quebrar selo)
            this->ganharArmadura(cartaSendoJogada->getValor());
            break;
        // ... outros cases
    }

    // Move a carta para o descarte (se ainda não foi movida)
    auto it = std::find(mao.begin(), mao.end(), cartaSendoJogada);
    if (it != mao.end()) {
        descarte.push_back(cartaSendoJogada);
        mao.erase(it);
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

void Player::adicionarFragmento(const FragmentoEtereo& fragmento) {
    fragmentosColetados.push_back(fragmento);
    std::cout << "Voce coletou: " << fragmento.nome << "!\n";
}


void Player::mostrarFragmentos() const {
    std::cout << "\n--- Fragmentos Etéreos Coletados ---\n";
    if (fragmentosColetados.empty()) {
        std::cout << "Nenhum fragmento.\n";
    } else {
        for (size_t i = 0; i < fragmentosColetados.size(); ++i) {
            std::cout << "[" << i << "] " << fragmentosColetados[i].nome << "\n";
        }
    }
    std::cout << "--------------------------------------\n";
}

std::vector<FragmentoEtereo>& Player::getFragmentos() {
    return fragmentosColetados;
}

void Player::adicionarCartaAoDeck(Card* novaCarta) {
    if (novaCarta) {
        // A nova carta é adicionada na pilha de descarte,
        // para ser embaralhada no deck no próximo ciclo.
        descarte.push_back(novaCarta);
    }
}

bool Player::estaVivo() const { return this->vida > 0; }
const std::vector<Card*>& Player::getMao() const { return this->mao; }
void Player::setTurnoAtivo(bool estado) { this->meuTurno = estado; }
bool Player::getTurnoAtivo() const { return this->meuTurno; }