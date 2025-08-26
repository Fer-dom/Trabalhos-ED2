#pragma once

#include "Relic.hpp"
#include "FragmentoEtereo.hpp"
#include "Status.hpp"
#include "Card.hpp"
#include <vector>
#include <string>

class Inimigo; 

class Player {
public:
    Player(int vidaInicial, int essenciaInicial, std::vector<Card*> deckInicial);
    ~Player();

    void curar(int quantidade);
    int getDeckSize() const;
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
    void adicionarFragmento(const FragmentoEtereo& fragmento);
    void mostrarFragmentos() const;
    void adicionarCartaAoDeck(Card* novaCarta); 
    void aplicarStatus(Status s, int stacks);           
    void tickStatusFimDoTurno();                        
    int ajustarDanoCausado(int base) const;             
    int ajustarDanoRecebido(int base) const; 
    void addRelic(const Relic& r); 
    void onStartTurn_Relics();  
    void onPlayDefense_Relics();          
    const StatusMap& getStatus() const { return statusAtivos; } 
    const std::vector<Card*>& getMao() const;
    const std::vector<Relic>& getRelics() const { return reliquias; } 
    std::vector<FragmentoEtereo>& getFragmentos();

    void addMana(int qtd);           
    int  getMana() const;            
    void addBlock(int qtd);          
    void increaseMaxHP(int qtd);     
    void heal(int qtd);              
    void takeDamage(int qtd);        

private:
    
    int vida;
    int vidaMaxima; 
    int essenciaArcana;
    int armadura;
    bool meuTurno;
    StatusMap statusAtivos;
    std::vector<Relic> reliquias;
    std::vector<FragmentoEtereo> fragmentosColetados;
    std::vector<Card*> deck;
    std::vector<Card*> mao;
    std::vector<Card*> descarte;
};