#pragma once

#include <string>

class Player;

class Inimigo {
public:
    // Construtor: Cria um inimigo com seus status.
    Inimigo(const std::string& nome, int vidaInicial);


    /**
    Aplica dano ao inimigo, reduzindo sua vida.
     */
    void receberDano(int quantidade);

    void mostrarStatus() const;

    /**
    Define o que o inimigo planeja fazer no seu próximo turno.
     */
    void planejarAcao();

    /**
     Executa a ação que foi planejada contra um alvo.
     alvo O jogador que sofrerá a ação.
     */
    void realizarAcao(Player& alvo);


    std::string getNome() const;
    int getVida() const;
    int getVidaMaxima() const;
    int getDanoIntencao() const;

    bool estaVivo() const;

private:
    std::string nome;
    int vida;
    int vidaMaxima;
    int danoDaProximaAcao;
};