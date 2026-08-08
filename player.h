#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "deck.h"
#include "hand.h"

class Player{
    private: //player profile
    std::string name;
    Hand hand;
    bool busted;

    //betting variables
    int bankroll;
    int currentBet;

    void displayHand() const;

    public:
    //starting bankroll with a default of 1000
    Player(const std::string& playerName, int startingBankroll = 1000);
    ~Player() = default;

    void takeTurn(Deck& deck);
    void resetForRound();

    const std::string& getName() const;
    const Hand& getHand() const;
    Hand& getHand();

    bool isBusted() const;

    //betting methods
    int getBankroll() const;
    int getCurrentBet() const;
    void placeBet(int amount);
    void winBet();
    void loseBet();
    void pushBet();
    bool isBankrupt() const;

};

#endif