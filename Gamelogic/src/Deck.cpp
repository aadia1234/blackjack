#include "../include/Deck.h"
#include <algorithm>
#include <random>
#include <chrono>

Deck::Deck() {
    reset();
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(cards.begin(), cards.end(), std::default_random_engine(seed));
}

Card Deck::dealCard() {
    if (isEmpty()) {
        throw std::runtime_error("Deck is empty");
    }
    
    Card card = cards.back();
    cards.pop_back();
    return card;
}

bool Deck::isEmpty() const {
    return cards.empty();
}

void Deck::reset() {
    cards.clear();
    
    std::vector<std::string> suits = {"Hearts", "Diamonds", "Clubs", "Spades"};
    std::vector<std::string> faces = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
    std::vector<int> values = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};
    
    for (const auto& suit : suits) {
        for (size_t i = 0; i < faces.size(); i++) {
            cards.push_back(Card(suit, faces[i], values[i]));
        }
    }
    
    shuffle();
}