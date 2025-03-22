#include "../include/Hand.h"

Hand::Hand() : totalValue(0) {}

void Hand::addCard(const Card& card) {
    cards.push_back(card);
    calculateValue();
}

int Hand::getTotalValue() const {
    return totalValue;
}

void Hand::clear() {
    cards.clear();
    totalValue = 0;
}

const std::vector<Card>& Hand::getCards() const {
    return cards;
}

void Hand::calculateValue() {
    totalValue = 0;
    int aceCount = 0;
    
    for (const Card& card : cards) {
        totalValue += card.getValue();
        if (card.getFace() == "Ace") {
            aceCount++;
        }
    }
    
    // Adjust for aces
    while (totalValue > 21 && aceCount > 0) {
        totalValue -= 10;  // Convert Ace from 11 to 1
        aceCount--;
    }
}