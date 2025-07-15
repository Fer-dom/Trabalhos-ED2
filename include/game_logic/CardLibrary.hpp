#pragma once

#include "Card.hpp" 
#include <vector>
#include <string>
#include <map>

class CardLibrary {
public:
    CardLibrary();
    Card* createCard(const std::string& cardName);
    std::vector<Card*> getStartingDeck();

private:
    std::map<std::string, Card> cardTemplates;
};