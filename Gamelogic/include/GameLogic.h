#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"
#include "Player.h"
#include "Dealer.h"

// Making Player and Hand's protected members accessible from GameLogic
class GameLogic {
private:
    Deck deck;
    bool handledWinnings; 
    
public:
    // Making these public for direct access
    Player player;
    Dealer dealer;
    int currentBet;
    int playerMoney;
    bool gameOver;
    
    GameLogic();
    
    // Game control methods
    void newGame();
    void placeBet(int amount);
    bool playerHit();
    void playerStand();
    bool isGameOver();
    
    // Card methods
    std::vector<Card> getPlayerCards();
    std::vector<Card> getDealerCards();
    bool shouldHideDealerFirstCard();
    
    // Game state methods
    int getPlayerMoney();
    int getCurrentBet();
    int getPlayerHandValue();
    int getDealerHandValue();
    bool didPlayerWin();
    bool didDealerWin();
    bool isTie();
    std::string getGameStateMessage();
};

#endif // GAME_LOGIC_H