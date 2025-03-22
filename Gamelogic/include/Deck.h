#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
private:
    std::vector<Card> cards;
    
public:
    Deck();
    
    void shuffle();
    Card dealCard();
    bool isEmpty() const;
    void reset();
};

#endif // DECK_H