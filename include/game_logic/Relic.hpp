#pragma once
#include <string>
class Player; // fwd

enum class RelicKind {
    ESSENCIA_PLUS,     // +1 essência por turno
    VIDA_MAX_PLUS,     // +5 HP máx (e cura +5)
    ARMADURA_DEFENSE   // +1 armadura ao jogar carta de defesa
};

struct Relic {
    RelicKind kind;
    std::string nome;
    std::string descricao;
    // ganchos básicos
    void onStartTurn(Player& p) const; // aplicado a cada turno do player
    void onGainRelic(Player& p) const; // quando pega a relíquia
    void onPlayDefense(Player& p) const; // quando joga carta de defesa
};
