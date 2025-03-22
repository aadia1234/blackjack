#include "../include/Dealer.h"

Dealer::Dealer() : Player("Dealer") {}

bool Dealer::shouldHit() const {
    // Now using hand directly instead of getter
    return hand.getTotalValue() < 17;
}