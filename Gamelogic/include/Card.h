#pragma once
#include <string>

class Card {
private:
    std::string suit;
    std::string face;
    std::string suitSymbol; // Unicode symbol for suit
    std::string faceSymbol; // Short symbol for face
    int value;

public:
    Card(std::string suit, std::string face, int value);
    
    std::string getSuit() const;
    std::string getSuitSymbol() const;
    std::string getFace() const;
    std::string getFaceSymbol() const;
    int getValue() const;
    std::string toString() const;
    std::string getUnicodeSymbol() const;
};