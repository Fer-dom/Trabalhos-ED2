#pragma once

#include <vector>
#include <string>
#include "Card.hpp"

class Inimigo; 

class Player {
public:
    Player(int vidaInicial, int essenciaInicial, std::vector<Card*> deckInicial);
    ~Player();

    // --- Métodos de Lógica de Jogo ---
    void comprarCarta();
    void jogarCarta(Card* carta, Inimigo& alvo);
    void finalizarTurno();
    void mostrarMao() const;
    void mostrarStatus() const;
    void ganharArmadura(int quantidade);
    void receberDano(int quantidade);
    bool estaVivo() const;
    void setTurnoAtivo(bool estado);
    bool getTurnoAtivo() const;
    void iniciarNovoTurno();
    int getDeckSize() const;
    
    const std::vector<Card*>& getMao() const;
    

private:
    // Atributos de status
    int vida; // Vida atual do jogador
    int vidaMaxima; // Vida máxima do jogador
    int essenciaArcana; // Essência Arcana é a "energia" do jogador para jogar cartas
    int armadura; // Armadura é a defesa temporária do jogador
    bool meuTurno; // Indica se é o turno do jogador
    // As coleções de cartas
    std::vector<Card*> deck;
    std::vector<Card*> mao;
    std::vector<Card*> descarte;
};