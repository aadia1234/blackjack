#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand {
public:
    // Making members public to allow direct access
    std::vector<Card> cards;
    int totalValue;

    Hand();
    
    void addCard(const Card& card);
    int getTotalValue() const;
    void clear();
    const std::vector<Card>& getCards() const;
    
private:
    void calculateValue();
};

#endif // HAND_H