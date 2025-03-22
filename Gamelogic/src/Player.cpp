#include "../include/Player.h"

Player::Player(const std::string& name) : name(name) {}

// Removed getters and setters, keeping only business logic
bool Player::isBusted() const {
    return hand.getTotalValue() > 21;
}