#ifndef PLAYER_H
#define PLAYER_H

#include "Hand.h"
#include <string>

class Player {

public:
    Hand hand;
    std::string name;
    Player(const std::string& name);
    virtual ~Player() = default;
    
    // Removed getters and setters
    bool isBusted() const;
};

#endif // PLAYER_H