#ifndef DEALER_H
#define DEALER_H

#include "Player.h"

class Dealer : public Player {
public:
    Dealer();
    
    bool shouldHit() const;
};

#endif // DEALER_H