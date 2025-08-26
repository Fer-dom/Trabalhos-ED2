#include "../../include/game_logic/Relic.hpp"
#include "../../include/game_logic/Player.hpp"

void Relic::onStartTurn(Player& p) const {
    switch (kind) {
        case RelicKind::ESSENCIA_PLUS:
            p.addMana(1);       
            break;
        default: break;
    }
}

void Relic::onGainRelic(Player& p) const {
    switch (kind) {
        case RelicKind::VIDA_MAX_PLUS:
            p.increaseMaxHP(5);   
            p.heal(5);            
            break;
        default: break;
    }
}

void Relic::onPlayDefense(Player& p) const {
    switch (kind) {
        case RelicKind::ARMADURA_DEFENSE:
            p.addBlock(1);        
            break;
        default: break;
    }
}
