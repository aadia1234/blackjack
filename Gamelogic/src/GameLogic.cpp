#include "../include/GameLogic.h"

bool handledWinnings; 

GameLogic::GameLogic() : currentBet(0), playerMoney(1000), gameOver(false), player("Player") {
    newGame();
}

void GameLogic::newGame() {
    deck.reset();
    deck.shuffle();
    player.hand.clear(); // Clear the player's hand instead of reassigning
    dealer.hand.clear(); // Clear the dealer's hand instead of reassigning
    gameOver = false;
    handledWinnings = false;
}

void GameLogic::placeBet(int amount) {
    if (amount <= playerMoney) {
        currentBet = amount;
        playerMoney -= amount;
        
        // Deal initial cards - directly accessing hand
        player.hand.addCard(deck.dealCard());
        dealer.hand.addCard(deck.dealCard());
        player.hand.addCard(deck.dealCard());
        dealer.hand.addCard(deck.dealCard());
    } else {
        // Handle insufficient funds
        currentBet = 0;
        // Could throw an exception or set an error state
    }
}

bool GameLogic::playerHit() {
    if (!gameOver) {
        // Directly accessing hand
        player.hand.addCard(deck.dealCard());
        
        if (player.isBusted()) {
            gameOver = true;
        }
        return !player.isBusted();
    }
    return false;
}

void GameLogic::playerStand() {
    if (!gameOver) {
        // Dealer's turn - directly accessing hand
        while (dealer.shouldHit()) {
            dealer.hand.addCard(deck.dealCard());
        }
        
        gameOver = true;
    }
}

bool GameLogic::isGameOver() {
    return gameOver;
}

std::vector<Card> GameLogic::getPlayerCards() {
    // Directly accessing hand and cards
    return player.hand.getCards();
}

std::vector<Card> GameLogic::getDealerCards() {
    // Directly accessing hand and cards
    return dealer.hand.getCards();
}

bool GameLogic::shouldHideDealerFirstCard() {
    return !gameOver;
}

int GameLogic::getPlayerMoney() {
    return playerMoney;
}

int GameLogic::getCurrentBet() {
    return currentBet;
}

int GameLogic::getPlayerHandValue() {
    // Directly accessing hand
    return player.hand.getTotalValue();
}

int GameLogic::getDealerHandValue() {
    // Directly accessing hand
    return dealer.hand.getTotalValue();
}

bool GameLogic::didPlayerWin() {
    if (!gameOver) return false;
    
    if (player.isBusted()) return false;
    if (dealer.isBusted()) return true;
    return player.hand.getTotalValue() > dealer.hand.getTotalValue();
}

bool GameLogic::didDealerWin() {
    if (!gameOver) return false;
    
    if (dealer.isBusted()) return false;
    if (player.isBusted()) return true;
    return dealer.hand.getTotalValue() > player.hand.getTotalValue();
}

bool GameLogic::isTie() {
    if (!gameOver) return false;
    
    if (player.isBusted() || dealer.isBusted()) return false;
    return player.hand.getTotalValue() == dealer.hand.getTotalValue();
}


// Rest of the methods remain the same

std::string GameLogic::getGameStateMessage() {
    if (!gameOver) {
        return "Game in progress";
    }
    
    // Remove static variable and use class member instead
    if (didPlayerWin()) {
        if (!handledWinnings) {
            playerMoney += currentBet * 2; // Return original bet + winnings
            handledWinnings = true;
        }
        return "You win!";
    } else if (didDealerWin()) {
        // No money returned on dealer win
        handledWinnings = true;
        return "Dealer wins";
    } else if (isTie()) {
        if (!handledWinnings) {
            playerMoney += currentBet; // Return original bet on tie
            handledWinnings = true;
        }
        return "It's a tie!";
    }
    
    return "Unknown game state";
}