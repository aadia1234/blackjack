#include "../include/Card.h"

Card::Card(std::string suit, std::string face, int value) 
    : suit(suit), face(face), value(value) {
    // Convert suit names to Unicode symbols
    if (suit == "Hearts") {
        suitSymbol = "♥";
    } else if (suit == "Diamonds") {
        suitSymbol = "♦";
    } else if (suit == "Clubs") {
        suitSymbol = "♣";
    } else if (suit == "Spades") {
        suitSymbol = "♠";
    }
    
    // Convert face cards to shorter versions if needed
    if (face == "Jack") {
        faceSymbol = "J";
    } else if (face == "Queen") {
        faceSymbol = "Q";
    } else if (face == "King") {
        faceSymbol = "K";
    } else if (face == "Ace") {
        faceSymbol = "A";
    } else {
        faceSymbol = face; // Keep numbers as is
    }
}

std::string Card::getSuit() const {
    return suit;
}

std::string Card::getSuitSymbol() const {
    return suitSymbol;
}

std::string Card::getFace() const {
    return face;
}

std::string Card::getFaceSymbol() const {
    return faceSymbol;
}

int Card::getValue() const {
    return value;
}

std::string Card::toString() const {
    return face + " of " + suit;
}

// Get Unicode card symbol (e.g., "🂡" for Ace of Spades)
std::string Card::getUnicodeSymbol() const {
    // Base values for the Unicode playing cards
    int baseValue = 0;
    
    // Determine base value based on suit
    if (suit == "Spades") {
        baseValue = 0x1F0A0;
    } else if (suit == "Hearts") {
        baseValue = 0x1F0B0;
    } else if (suit == "Diamonds") {
        baseValue = 0x1F0C0;
    } else if (suit == "Clubs") {
        baseValue = 0x1F0D0;
    }
    
    // Determine card value offset
    int offset = 0;
    if (face == "Ace") {
        offset = 1;
    } else if (face == "Jack") {
        offset = 11;
    } else if (face == "Queen") {
        offset = 13;
    } else if (face == "King") {
        offset = 14;
    } else {
        // For number cards
        try {
            offset = std::stoi(face);
        } catch (...) {
            // Default to Ace if conversion fails
            offset = 1;
        }
    }
    
    // Calculate Unicode code point
    int codePoint = baseValue + offset;
    
    // Convert code point to UTF-8
    // This is a simplistic conversion for basic demonstration
    std::string utf8;
    if (codePoint <= 0x7F) {
        utf8.push_back(static_cast<char>(codePoint));
    } else if (codePoint <= 0x7FF) {
        utf8.push_back(static_cast<char>(0xC0 | ((codePoint >> 6) & 0x1F)));
        utf8.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    } else if (codePoint <= 0xFFFF) {
        utf8.push_back(static_cast<char>(0xE0 | ((codePoint >> 12) & 0x0F)));
        utf8.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    } else {
        utf8.push_back(static_cast<char>(0xF0 | ((codePoint >> 18) & 0x07)));
        utf8.push_back(static_cast<char>(0x80 | ((codePoint >> 12) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | ((codePoint >> 6) & 0x3F)));
        utf8.push_back(static_cast<char>(0x80 | (codePoint & 0x3F)));
    }
    
    return utf8;
}